#pragma once

#include "AABBTree_Segment.h"

#include "OpenMeshCraft/BVH/AABB/AABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/AABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTree.h"

#include "OpenMeshCraft/Geometry/Primitives/PrimitiveWithAttribute.h"

namespace OMC {

/***********************************************/
/* 2. Define minimum set of AABB traits        */
/***********************************************/

template <typename _SegmentT, typename _CalcBbox>
class AABBMinimumTraits_SegSphere_Intersection
{
public:
	/* Belows are used by AABBTree */

	using SegmentT = _SegmentT;
	using CalcBbox = _CalcBbox;

	// Attribute type
	using PrimAttrT = index_t;
	// Primitive type
	using PrimT     = PrimitiveWithAttribute<SegmentT, PrimAttrT>;
	// Primitive reference point
	using PrimReferencePoint =
	  AABB_Seg_ReferencePoint<PrimT, AABB_Seg_ReferencePointType::Centroid>;
};

/****************************************************/
/* 3. Automatically deduce the complete AABB traits */
/****************************************************/

template <typename _SegmentT, typename _CalcBbox>
using AABBTraits_SegSphere_Intersection = AABBAutoDeduceTraits<
  AABBMinimumTraits_SegSphere_Intersection<_SegmentT, _CalcBbox>>;

/****************************************************/
/* 4. Define the AABB Tree used for intersection.   */
/****************************************************/

template <typename _SegmentT, typename _CalcBbox, typename _DoIntersect>
class DAABBTree_SegSphere_Intersection
  : public DAABBTree<AABBTraits_SegSphere_Intersection<_SegmentT, _CalcBbox>>
{
public:
	using Traits = AABBTraits_SegSphere_Intersection<_SegmentT, _CalcBbox>;
	using BaseT  = DAABBTree<Traits>;
	using ThisT =
	  DAABBTree_SegSphere_Intersection<_SegmentT, _CalcBbox, _DoIntersect>;

	using SegmentT  = typename Traits::SegmentT;
	using PrimT     = typename Traits::PrimT;
	using PrimAttrT = typename Traits::PrimAttrT;

	using Indices = std::vector<index_t>;

public:
	template <typename QPrimT>
	void all_intersections(const QPrimT &query, Indices &results) const
	{
		BoxTrav<QPrimT> box_trav(query);
		this->traverse(box_trav);

		auto &prim_ptrs = box_trav.result();
		results.reserve(prim_ptrs.size());
		for (auto pp : prim_ptrs)
			results.push_back(pp->attribute());
	}

	const typename BaseT::BboxT &get_Bbox(const index_t i) const
	{
		return this->m_nodes[i].bbox();
	}

protected:
	template <typename _QPrimT>
	class BoxInterTraits
	{
	public:
		using QPrimT = _QPrimT;

		using PrimT = typename Traits::PrimT;
		using BboxT = typename Traits::BboxT;

		using DoIntersect = _DoIntersect;
		using CalcBbox    = _CalcBbox;
	};

	template <typename QPrimT>
	using BoxTrav = AABB_BoxInterTraversal<BoxInterTraits<QPrimT>>;
};

} // namespace OMC
