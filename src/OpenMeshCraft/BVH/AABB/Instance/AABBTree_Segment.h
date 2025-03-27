#pragma once

#include "OpenMeshCraft/Utils/ExtendedTypeTraits.h"

namespace OMC {

/************************************************/
/* 1. Define the reference point of the segment */
/************************************************/

/**
 * @brief The type of reference point for segment.
 */
enum class AABB_Seg_ReferencePointType
{
  Start,   /// The start point of the segment.
  End,     /// The end point of the segment.
  Centroid /// The centroid of the segment.
};

/**
 * @class AABB_Seg_ReferencePoint
 * @brief A class template to compute a reference point for a segment
 * based on the specified reference point type.
 *
 * @tparam SegT The type of the segment.
 * @tparam RefPntType The type of the reference point.
 */
template <typename SegT, AABB_Seg_ReferencePointType RefPntType>
class AABB_Seg_ReferencePoint
{
public:
  using PointT = remove_cvref_t<decltype(std::declval<SegT>().start())>;
  using NT     = typename PointT::NT;

public:
  PointT operator()(const SegT &seg)
  {
    if constexpr (RefPntType == AABB_Seg_ReferencePointType::Start)
    {
      return seg.start();
    }
    else if constexpr (RefPntType == AABB_Seg_ReferencePointType::End)
    {
      return seg.end();
    }
    else if constexpr (RefPntType == AABB_Seg_ReferencePointType::Centroid)
    {
      return (seg.start() + seg.end()) * NT(0.5);
    }
  }
};

} // namespace OMC