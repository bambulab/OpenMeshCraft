#pragma once

#include "AABBTree_Segment.h"

#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTree.h"

namespace OMC {

/***********************************************/
/* 2. Define minimum set of AABB traits        */
/***********************************************/

template <typename _SegmentT, typename _CalcBbox>
class DAABBMinimumTraits_SegSphere_Intersection
{
public:
	/* Belows are used by AABBTree */

	// Primitive type
	using SegmentT = _SegmentT;
	using PrimT    = SegmentT;

	// Calculate bounding box
	using CalcBbox = _CalcBbox;

	// Primitive reference point
	using PrimReferencePoint =
	  AABB_Seg_ReferencePoint<PrimT, AABB_Seg_ReferencePointType::Centroid>;
};

/****************************************************/
/* 3. Automatically deduce the complete AABB traits */
/****************************************************/

template <typename _SegmentT, typename _CalcBbox>
using DAABBTraits_SegSphere_Intersection = DAABBAutoDeduceTraits<
  DAABBMinimumTraits_SegSphere_Intersection<_SegmentT, _CalcBbox>>;

/****************************************************/
/* 4. Define the AABB Tree used for intersection.   */
/****************************************************/

template <typename _SegmentT, typename _CalcBbox, typename _DoIntersect>
class DAABBTree_SegSphere_Intersection
  : public DAABBTree<DAABBTraits_SegSphere_Intersection<_SegmentT, _CalcBbox>>
{
public:
	using Traits = DAABBTraits_SegSphere_Intersection<_SegmentT, _CalcBbox>;
	using BaseT  = DAABBTree<Traits>;
	using ThisT =
	  DAABBTree_SegSphere_Intersection<_SegmentT, _CalcBbox, _DoIntersect>;

	using PrimT = typename Traits::PrimT;

public:
	template <typename QPrimT, typename Indices>
	void all_intersections(const QPrimT &query, Indices &results) const
	{
		BoxTrav<QPrimT> box_trav(query);
		this->traverse(box_trav);

		const typename BoxTrav<QPrimT>::Indices &prim_ids = box_trav.result();
		results.insert(results.end(), prim_ids.begin(), prim_ids.end());
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
	using BoxTrav = DAABB_BoxInterTraversal<BoxInterTraits<QPrimT>>;
};

} // namespace OMC
