#pragma once

#include "DAABBNode.h"

#include <vector>

namespace OMC {

/**
 * @brief Dynamic Axis-Aligned Bounding Box Tree (DAABBTree).
 *
 * - The DAABBTree supports dynamic modifications, including insertion, removal,
 *   updating, and splitting of primitives. It also provides mechanisms for
 *   traversing the tree and performing various queries.
 *
 * - The DAABBTree provides a map from external indices to internal primitives,
 *   which is useful for updating, splitting and removing primitives.
 *
 * @tparam Traits The traits class that defines the tree's behaviors and types.
 */
template <typename Traits>
class DAABBTree
{
public: /* Types *************************************************************/
	/* The traits should provide the following: */

	using PrimT = typename Traits::PrimT;
	using BboxT = typename Traits::BboxT;

	using CalcBbox   = typename Traits::CalcBbox;
	using SplitPrims = typename Traits::SplitPrims;
	friend SplitPrims;

	using IndexMap = typename Traits::IndexMap;

	/* Types used by dynamic AABB tree */

	/// Tree type
	using ThisT = typename DAABBTree<Traits>;

	/// Primitives
	using Prims = std::vector<PrimT>;

	/// DAABB Node
	using NodeT = DAABBNode<PrimT, BboxT>;
	using Nodes = std::vector<NodeT>;

public: /* Constructors and Destructors *************************************/
	DAABBTree() = default;

	/**
	 * @brief Insert primitives and corresponding external indices to the tree.
	 * Won't call build.
	 * @param pfirst The iterator to the first primitive.
	 * @param pbeyond The iterator to the end of the primitives.
	 * @param ifirst The iterator to the first index.
	 * @param ibeyond The iterator to the end of the indices.
	 * @note `insert` can be called multiple times to insert primitives.
	 */
	template <typename PrimsIterT, typename IndicesIter>
	void insert(PrimsIterT pfirst, PrimsIterT pbeyond, IndicesIter ifirst,
	            IndicesIter ibeyond);

	/// @brief Build the AABB tree with given primitives (by insert).
	void build();

	void clear();

public: /* Interfaces ********************************************************/
	/*** Query ***/

	/// @brief Get the size of stored primitives
	size_t size() const { return m_primitives.size(); }
	/// @brief Check if the stored primitives are empty
	bool   empty() const { return m_primitives.empty(); }

	/// @brief Check if the primitive exists in the tree.
	bool prim_exists(index_t ex_prim_idx) const
	{
		return is_valid_idx(ex2in(ex_prim_idx));
	}

	/*** Dynamic modifications ***/

	/**
	 * @brief Insert a primitive to the tree.
	 * @param prim The primitive to be inserted.
	 * @param ex_prim_idx The external index of the primitive.
	 */
	virtual void insert(const PrimT &prim, index_t ex_prim_idx);

	/**
	 * @brief Remove a primitive from the tree.
	 * @param ex_prim_idx The external index of the primitive.
	 */
	virtual void remove(index_t ex_prim_idx);

	/**
	 * @brief Update a primitive in the tree (update its bounding box
	 * and propogate change to ancestors).
	 * @param ex_prim_idx The external index of the primitive.
	 * @param new_prim The new primitive.
	 */
	virtual void update(index_t ex_prim_idx, const PrimT &new_prim);

	/**
	 * @brief Split a primitive to two children in the tree.
	 * @param ex_prim_idx The external index of the primitive.
	 * @param ex_subp0_idx The external index of the first child primitive.
	 * @param subprim0 The first child primitive.
	 * @param ex_subp1_idx The external index of the second child primitive
	 * @param subprim1 The second child primitive.
	 */
	virtual void split(index_t ex_prim_idx, index_t ex_subp0_idx,
	                   const PrimT &subprim0, index_t ex_subp1_idx,
	                   const PrimT &subprim1);

	/**
	 * @brief Really remove deleted primitives and nodes in the tree.
	 * @note Make sure the order of primitives changes as expected.
	 */
	void collect_garbage();

	/*** Traverse the tree ***/

	template <typename TraversalTrait>
	void traverse(TraversalTrait &trait) const;

protected: /* Internal interfaces *******************************************/
	/*** Query ***/

	NodeT       &node(index_t node_idx) { return m_nodes[node_idx]; }
	const NodeT &node(index_t node_idx) const { return m_nodes[node_idx]; }

	PrimT       &primitive(index_t p_idx) { return m_primitives[p_idx]; }
	const PrimT &primitive(index_t p_idx) const { return m_primitives[p_idx]; }

	/// primitive deleted
	uint8_t &pdeleted(index_t p_idx) { return m_primitive_deleted[p_idx]; }
	uint8_t  pdeleted(index_t p_idx) const { return m_primitive_deleted[p_idx]; }

	/// node deleted
	uint8_t &ndeleted(index_t n_idx) { return m_node_deleted[n_idx]; }
	uint8_t  ndeleted(index_t n_idx) const { return m_node_deleted[n_idx]; }

	/// external index to internal index
	index_t &ex2in(index_t ex_pidx) { return m_ex_map2_in[ex_pidx]; }
	index_t  ex2in(index_t ex_pidx) const { return m_ex_map2_in.at(ex_pidx); }

	/// internal index to external index
	index_t &in2ex(index_t ex_pidx) { return m_in_map2_ex[ex_pidx]; }
	index_t  in2ex(index_t ex_pidx) const { return m_in_map2_ex.at(ex_pidx); }

	/// internal index to node index
	index_t &in2nd(index_t in_pidx) { return m_primitive_map2_node[in_pidx]; }
	index_t  in2nd(index_t in_pidx) const
	{
		return m_primitive_map2_node[in_pidx];
	}

	/*** Help functions about building ***/

	/**
	 * @brief Build mapping between external and internal indices.
	 * @param ex_prim_idx external primitive index
	 * @param in_prim_idx internal primitive index
	 */
	void connect(index_t ex_prim_idx, index_t in_prim_idx);

	/**
	 * @brief Calculate the bounding box of a set of primitives.
	 * @return The bounding box of the set of primitives.
	 */
	template <typename IndicesIter>
	BboxT calc_bbox(IndicesIter first, IndicesIter beyond);

	/// @brief Split the primitives along the longest axis of the bounding box.
	template <typename IndicesIter>
	int split_primitives(IndicesIter first, IndicesIter beyond,
	                     IndicesIter &middle, const BboxT &box);

	/**
	 * @brief Expand a node with a set of primitives.
	 * @param first The iterator to the internal index of the first primitive.
	 * @param beyond The iterator to the internal index of the last primitive.
	 * @param parent_idx The parent node index.
	 * @return index_t The index of the expanded node.
	 */
	template <typename IndicesIter>
	index_t expand(IndicesIter first, IndicesIter beyond, index_t parent_idx);

	/*** Help functions about insertion ***/

	/**
	 * @brief Insert a primitive to the tree and return its index.
	 * @return The internal index of the inserted primitive.
	 */
	index_t insert_a_primitive(const PrimT &prim);

	/**
	 * @brief Create a node and return its index.
	 * @return The internal index of the created node.
	 */
	index_t create_a_node();

	/**
	 * @brief Insert a primitive (with its bounding box) to a node.
	 * @param in_prim_idx The internal index of the primitive.
	 * @param prim_box The bounding box of the primitive.
	 * @param node_idx The internal index of the node.
	 */
	void insert_to_node(index_t in_prim_idx, BboxT &prim_box, index_t node_idx);

	/*** Help functions about deletion ***/

	/// @brief Remove a primitive from the corresponding leaf node.
	void remove_from_leaf_node(index_t in_prim_idx);
	/// @brief remove a node. removed node must have no primitives.
	void remove_node(index_t node_idx);
	/// @brief parent of this node only has one child, which is this node.
	/// so replace parent with this node.
	void moveup_node(index_t node_idx);

	/*** Help functions about updating ***/

	/// @brief Update the bounding box of a node and propogate the change.
	void update_node_box(index_t node_idx);

	/*** Help functions about splitting ***/

	void split_node(index_t node_idx, index_t subprim0_idx, index_t subprim1_idx);

	/*** Help functions about traversal ***/
	template <typename TraversalTrait>
	bool traverse_node(TraversalTrait &trait, index_t node_idx) const;

public: /* Data **************************************************************/
	/// Primitives stored in the tree.
	Prims m_primitives;
	/// Nodes stored in the tree.
	Nodes m_nodes;

	/// A map from external index to internal primitive index
	IndexMap             m_ex_map2_in;
	/// A map from internal primitive index to external index
	std::vector<index_t> m_in_map2_ex;

	/// A reverse map from internal primitive index to node index.
	std::vector<index_t> m_primitive_map2_node;

	/// deleted status of primitives
	std::vector<uint8_t> m_primitive_deleted;
	/// deleted status of nodes
	std::vector<uint8_t> m_node_deleted;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "DAABBTree.inl"
#endif