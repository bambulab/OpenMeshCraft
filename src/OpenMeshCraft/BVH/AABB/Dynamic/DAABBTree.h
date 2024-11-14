#pragma once

#include "DAABBNode.h"

#include <vector>

namespace OMC {

/**
 * @brief Dynamic Axis-Aligned Bounding Box Tree.
 * @tparam Traits The traits defines tree's behaviors.
 */
template <typename Traits>
class DAABBTree
{
public: /* Types *************************************************************/
	/* The tratis should provide followings: */

	using NT        = typename Traits::NT;
	using PointT    = typename Traits::PointT;
	using PrimT     = typename Traits::PrimT;
	using BboxT     = typename Traits::BboxT;

	using CalcBbox   = typename Traits::CalcBbox;
	using SplitPrims = typename Traits::SplitPrims;

	/* Types used by dynamic AABB tree */

	/// Tree type
	using ThisT = typename DAABBTree<Traits>;

	/// Primitives
	using Prims = std::vector<PrimT>;

	/// DAABB Node
	using NodeT = DAABBNode<PrimT, BboxT>;
	using Nodes = std::vector<NodeT>;

	/// Indices
	using Indices = std::vector<index_t>;

public: /* Constructors and Destructors *************************************/
	DAABBTree() {}

	/// @brief Insert primitives to the tree and build.
	template<typename PrimsIterT>
	DAABBTree(PrimsIterT first, PrimsIterT beyond);

	/// @brief Insert primitives to the tree and build.
	DAABBTree(Prims &&primitives);

	/// @brief Insert primitives to the tree. Won't call build.
	template<typename PrimsIterT>
	void insert(PrimsIterT first, PrimsIterT beyond);

	/// @brief Insert primitives to the tree. Won't call build.
	void insert(Prims &&primitives);

	/// @brief Build the AABB tree with given primitives (by insert).
	void build();

	/// @brief Clear nodes and rebuild the AABB tree with stored primitives.
	void rebuild();

	void clear();

public: /* Interfaces ********************************************************/
	/*** Query ***/

	/// @brief Get the size of stored primitives
	inline size_t size() const { return m_primitives.size(); }
	/// @brief Check if the stored primitives are empty
	inline bool   empty() const { return m_primitives.empty(); }

	/*** Dynamic modifications ***/

	/// @brief Insert a primitive to the tree.
	virtual void insert(const PrimT &prim);
	/// @brief Remove a primitive from the tree.
	virtual void remove(index_t prim_idx);
	/// @brief Update a primitive in the tree (update its bounding box
	/// and propogate change to ancestors).
	virtual void update(index_t prim_idx, const PrimT &new_prim);
	/// @brief Split a primitive to two children in the tree.
	virtual void split(index_t prim_idx, const PrimT &subprim0,
	                   const PrimT &subprim1);

	/**
	 * @brief Really remove deleted primitives and nodes in the tree.
	 * @note Make sure the order of primitives changes as expected.
	 */
	void collect_garbage();

	/*** Traverse the tree ***/

	template <typename TraversalTrait>
	void traverse(TraversalTrait &trait);

public: /* Internal interfaces ***********************************************/
	/*** Query ***/

	inline NodeT   &node(index_t node_idx) { return m_nodes[node_idx]; }
	inline PrimT   &primitive(index_t p_idx) { return m_primitives[p_idx]; }
	inline index_t &mapto(index_t p_idx) { return m_primitive_map2_node[p_idx]; }

	/*** Help functions about building ***/

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
	 * @return index_t The index of the expanded node.
	 */
	template <typename IndicesIter>
	index_t expand(IndicesIter first, IndicesIter beyond, index_t parent_idx);

	/*** Help functions about insertion ***/

	/// @brief Insert a primitive to the tree and return its index.
	index_t insert_a_primitive(const PrimT &prim);
	/// @brief Create a node and return its index.
	index_t create_a_node();
	/// @brief Insert a primitive (with its bounding box) to a node.
	void    insert_to_node(index_t prim_idx, BboxT &prim_box, index_t node_idx);

	/*** Help functions about deletion ***/

	/// @brief Remove a primitive from a node.
	void remove_from_node(index_t prim_idx, index_t node_idx);
	/// @brief remove a node. removed node must have no primitives.
	void remove_node(index_t node_idx);
	/// @brief parent of this node only has one child, which is this node.
	/// so replace parent with this node.
	void moveup_node(index_t node_idx);
	/// @brief Swap two nodes in the tree.
	void swap_node(index_t n0, index_t n1);

	/*** Help functions about updating ***/

	/// @brief Update the bounding box of a node and propogate the change.
	void update_node(index_t node_idx);

	/*** Help functions about splitting ***/

	void split_node(index_t node_idx, index_t subprim0_idx, index_t subprim1_idx);

	/*** Help functions about traversal ***/
	template <typename Trait>
	bool traverse_node(Trait &trait, index_t node_idx);

public: /* Data **************************************************************/
	/// Primitives stored in the tree.
	Prims m_primitives;
	/// Nodes stored in the tree.
	Nodes m_nodes;

	/// A reverse map from primitive index to node index.
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