#pragma once

#include "IntersectionUtils.h"

namespace OMC {

/**
 * @brief Check if Segment2 and Segment2 intersect.
 *
 * From the simplex view, the intersection can be classified into 4 types:
 *
 * - DO_NOT_INTERSECT : two segments do not intersect at any point.
 *
 * - SIMPLICIAL_COMPLEX : two segments intersect only at a common vertex
 * or at both vertices (i.e., the same segment).
 *
 * - INTERSECT : two segments intersect at a single interior point.
 *
 * - OVERLAP : two segments partially overlap.
 *
 * The last three types are all considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Segment2_Segment2_DoIntersectK
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using GPoint2  = typename K::GPoint2;
  using Segment2 = typename K::Segment2;

  using LessThan2D = typename K::LessThan2D;
  using Orient2D   = typename K::Orient2D;

public:
  /**
   * @brief Check if segment and segment intersect.
   * @note assume thant no segment is degenerate.
   */
  bool operator()(const Segment2 &seg0, const Segment2 &seg1) const;

  /**
   * @brief Get the intersection type between segment and segment.
   * @note assume thant no segment is degenerate.
   */
  SimplexIntersectionType intersection_type(const Segment2 &seg0,
                                            const Segment2 &seg1) const;

  /**
   * @brief Get the intersection type between segment and segment.
   * @param s00_s01 two vertices of the segment
   * @param s10_s11 two vertices of the segment
   * @note assume thant no segment is degenerate.
   */
  SimplexIntersectionType intersection_type(const GPoint2 &s00,
                                            const GPoint2 &s01,
                                            const GPoint2 &s10,
                                            const GPoint2 &s11) const;

  /**
   * @brief Get the intersection type between segment and segment.
   * @param s00_s01 two vertices of the segment
   * @param s10_s11 two vertices of the segment
   * @note assume thant no segment is degenerate.
   */
  SimplexIntersectionType intersection_type(const NT *s00, const NT *s01,
                                            const NT *s10, const NT *s11) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Segment2_Segment2.inl"
#endif