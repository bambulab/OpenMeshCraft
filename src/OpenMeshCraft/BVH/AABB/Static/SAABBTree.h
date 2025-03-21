#pragma once

#include "SAABBNode.h"

#include <vector>

namespace OMC {

/**
 * @brief Static Axis-Aligned Bounding Box Tree.
 * The `static` means the tree's topology is fixed after construction,
 * but the geometry is allowed to change.
 * @tparam Traits The traits defines tree's behaviors.
 */
template <typename Traits>
class SAABBTree
{
public: /* Types ************************************************************/
	/* The tratis should provide followings: */

	using PrimT = typename Traits::PrimT;
	using BboxT = typename Traits::BboxT;

	using CalcBbox           = typename Traits::CalcBbox;
	using PrimSplitPred      = typename Traits::PrimSplitPred;
	using PrimReferencePoint = typename Traits::PrimReferencePoint;

	/* Types used by AABB tree */

	// primitives
	using PrimPtr   = PrimT *;
	using PrimCPtr  = const PrimT *;
	using PrimRef   = PrimT &;
	using PrimCRef  = const PrimT &;
	using Prims     = std::vector<PrimT>;
	using PrimsIter = typename Prims::iterator;

	// bounding boxes
	using Boxes     = std::vector<BboxT>;
	using BoxesIter = typename Boxes::iterator;

	// Indices
	using Indices     = std::vector<index_t>;
	using IndicesIter = typename Indices::iterator;

	// AABB Node
	using NodeT    = SAABBNode<BboxT>;
	using NodePtr  = NodeT *;
	using NodeCPtr = const NodeT *;
	using NodeRef  = NodeT &;
	using NodeCRef = const NodeT &;
	// container to store nodes
	using Nodes    = std::vector<NodeT>;

public: /* Constructor and Destructor ***************************************/
	SAABBTree() {}

	SAABBTree(Prims &&primitives);

	template <typename PrimsIterT>
	SAABBTree(PrimsIterT first, PrimsIterT beyond);

	~SAABBTree();

	/// @brief Insert primitives to the tree. Won't call build.
	void insert(Prims &&primitives);

	/// @brief Insert primitives to the tree. Won't call build.
	template <typename PrimsIter>
	void insert(PrimsIter first, PrimsIter beyond);

	/// @brief Build the AABB tree with given primitives (by insert).
	void build(bool parallel = true);

	/// @brief Update the whole tree's geometry after the geometry of primitives
	/// are updated externally (topology will not be updated).
	void update(bool parallel = true);

	void clear();

public: /* Query and Traversal ***********************************************/
	size_t size() const { return m_primitives.size(); }
	bool   empty() const { return m_primitives.empty(); }

	Prims       &primitives() { return m_primitives; }
	const Prims &primitives() const { return m_primitives; }

	PrimRef  primitive(index_t prim_id) { return m_primitives[prim_id]; }
	PrimCRef primitive(index_t prim_id) const { return m_primitives[prim_id]; }

	BboxT       &bbox(index_t prim_id) { return m_prim_boxes[prim_id]; }
	const BboxT &bbox(index_t prim_id) const { return m_prim_boxes[prim_id]; }

	NodeRef  node(index_t node_id) { return m_nodes[node_id]; }
	NodeCRef node(index_t node_id) const { return m_nodes[node_id]; }

	/// @brief Traverse the tree with given traversal traits.
	template <typename TraversalTrait>
	void traverse(TraversalTrait &traits) const;

protected: /* Internal help functions ****************************************/
	/* Help functions for building */

	void update_boxes(bool parallel);

	IndicesIter expand(index_t node_id, IndicesIter first, IndicesIter beyond,
	                   bool parallel, bool recursive);

	size_t split_primitives(IndicesIter first, IndicesIter beyond,
	                        IndicesIter &middle, const BboxT &box, bool parallel);

	/* Help functions for updating */

	void update_recursive(index_t node_id, size_t nb_primitives);

	/* Help functions for traversal */

	template <typename TraversalTrait>
	bool traverse_node(index_t node_id, TraversalTrait &traits,
	                   size_t nb_primitives) const;

protected:
	/// The primitives to be stored in the tree.
	/// The tree will take the ownership of the primitives,
	/// but the order of the primitives will keep unchanged.
	Prims m_primitives;

	/// The bounding boxes of the primitives.
	Boxes m_prim_boxes;

	/// The nodes of the tree.
	Nodes m_nodes;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "SAABBTree.inl"
#endif