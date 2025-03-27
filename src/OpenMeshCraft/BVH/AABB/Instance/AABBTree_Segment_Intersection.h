#pragma once

#include "AABBTree_Segment.h"

#include "OpenMeshCraft/BVH/AABB/Static/SAABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTree.h"

#include "OpenMeshCraft/Geometry/Primitives/PrimitiveWithAttribute.h"

namespace OMC {

/***********************************************/
/* 2. Define minimum set of AABB traits        */
/***********************************************/

template <typename _SegmentT, typename _CalcBbox>
class SAABBMinimumTraits_Segment_Intersection
{
public:
  /* Belows are used by AABBTree */

  // Primitive type
  using SegmentT = _SegmentT;

  // Attribute type
  using PrimAttrT = index_t;
  // Primitive type
  using PrimT     = PrimitiveWithAttribute<SegmentT, PrimAttrT>;

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
using SAABBTraits_Segment_Intersection = SAABBAutoDeduceTraits<
  SAABBMinimumTraits_Segment_Intersection<_SegmentT, _CalcBbox>>;

/****************************************************/
/* 4. Define the AABB Tree used for intersection.   */
/****************************************************/

template <typename _SegmentT, typename _CalcBbox, typename _DoIntersect>
class SAABBTree_Segment_Intersection
  : public SAABBTree<SAABBTraits_Segment_Intersection<_SegmentT, _CalcBbox>>
{
public:
  using Traits = SAABBTraits_Segment_Intersection<_SegmentT, _CalcBbox>;
  using BaseT  = SAABBTree<Traits>;
  using ThisT =
    SAABBTree_Segment_Intersection<_SegmentT, _CalcBbox, _DoIntersect>;

  using PrimT = typename Traits::PrimT;

public:
  template <typename QPrimT, typename Indices>
  void all_intersections(const QPrimT &query, Indices &results) const
  {
    BoxTrav<QPrimT> box_trav(query);
    this->traverse(box_trav);

    auto &prim_ptrs = box_trav.result();
    results.reserve(prim_ptrs.size());
    for (auto pp : prim_ptrs)
      results.push_back(pp->attribute());
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
  using BoxTrav = SAABB_BoxInterTraversal<BoxInterTraits<QPrimT>>;
};

} // namespace OMC
