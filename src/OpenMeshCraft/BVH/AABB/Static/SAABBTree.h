#pragma once

#include "SAABBNode.h"

#include <vector>

namespace OMC {

/**
 * @brief Axis-Aligned Bounding Box Tree.
 * @tparam Traits The traits defines tree's behaviors.
 */
template <typename Traits>
class SAABBTree
{
public: /* Types ************************************************************/
	/* The tratis should provide followings: */

	using PrimT  = typename Traits::PrimT;
	using BboxT  = typename Traits::BboxT;

	using CalcBbox           = typename Traits::CalcBbox;
	using SplitPrims         = typename Traits::SplitPrims;
	using PrimReferencePoint = typename Traits::PrimReferencePoint;

	/* Types used by AABB tree */

	// primitives
	using Prims = std::vector<PrimT>;
	using PrimsIter = typename Prims::iterator;

	// AABB Node
	using NodeT    = SAABBNode<PrimT, BboxT>;
	using NodePtr  = NodeT *;
	using NodeCPtr = const NodeT *;
	// container to store nodes
	using Nodes    = std::vector<NodeT>;

public: /* Constructor and Destructor ***************************************/
	SAABBTree() {}

	SAABBTree(Prims &&primitives);

	template<typename PrimsIterT>
	SAABBTree(PrimsIterT first, PrimsIterT beyond);

	~SAABBTree();

	/// @brief Insert primitives to the tree. Won't call build.
	void insert(Prims &&primitives);

	/// @brief Insert primitives to the tree. Won't call build.
	template<typename PrimsIter>
	void insert(PrimsIter first, PrimsIter beyond);

	/// @brief Build the AABB tree with given primitives (by insert).
	void build();

	void clear();

public: /* Query and Traversal ***********************************************/
	inline size_t size() const { return m_primitives.size(); }
	inline bool   empty() const { return m_primitives.empty(); }

	template <typename TraversalTrait>
	void traverse(TraversalTrait &traits) const;

protected: /* Internal help functions ****************************************/
	/* Help functions for building */

	void expand(NodePtr node, PrimsIter first, PrimsIter beyond);

	/* Help functions for traversal */

	template <typename TraversalTrait>
	bool traverse_node(NodeCPtr node, TraversalTrait &traits,
	                   const size_t nb_primitives) const;

protected:
	Prims m_primitives;
	Nodes m_nodes;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "SAABBTree.inl"
#endif