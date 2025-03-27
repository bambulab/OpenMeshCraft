#pragma once

#include "IntersectionUtils.h"

namespace OMC {

/**
 * @brief Check if Segment3 and Point3 intersect.
 *
 * From the simplex view, the intersection can be classified into 3 types:
 *
 * - DO_NOT_INTERSECT : the segment and point do not intersect.
 *
 * - SIMPLICIAL_COMPLEX : the point is one of the vertices of the segment.
 *
 * - INTERSECT : the point is on the interior of the segment.
 *
 * The last two types are considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Segment3_Point3_DoIntersectK
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using GPoint3  = typename K::GPoint3;
  using Segment3 = typename K::Segment3;

  using OrientOn2D       = typename K::OrientOn2D;
  using Orient3D         = typename K::Orient3D;
  using CollinearPoints3 = typename K::CollinearPoints3;
  using LessThan3D       = typename K::LessThan3D;

public:
  /**
   * @brief Check if segment and point intersect.
   */
  bool operator()(const Segment3 &seg, const GPoint3 &pnt) const;

  /**
   * @brief Check if segment and point intersect.
   */
  bool operator()(const GPoint3 &s0, const GPoint3 &s1,
                  const GPoint3 &pnt) const;

  /**
   * @brief Get the relative position of point to segment.
   * @return relative position of point to segment.
   */
  PointInType in_segment(const Segment3 &seg, const GPoint3 &pnt) const;

  /**
   * @brief Get the relative position of point to segment.
   * @param s0_s1 two vertices of the segment.
   * @param pnt point.
   * @return relative position of point to segment.
   */
  PointInType in_segment(const GPoint3 &s0, const GPoint3 &s1,
                         const GPoint3 &pnt) const;

  /**
   * @brief Get the relative position of point to segment.
   * @return relative position of point to segment.
   * @note this function assume that segment and point are collinear.
   */
  PointInType in_segment_collinear(const Segment3 &seg,
                                   const GPoint3  &pnt) const;

  /**
   * @brief Get the relative position of point to segment.
   * @param s0_s1 two vertices of the segment.
   * @param pnt point.
   * @return relative position of point to segment.
   * @note this function assume that three points are collinear.
   */
  PointInType in_segment_collinear(const GPoint3 &s0, const GPoint3 &s1,
                                   const GPoint3 &pnt) const;

  /**
   * @brief Get the intersection type between segment and point.
   */
  PointInSimplexType intersection_type(const Segment3 &seg,
                                       const GPoint3  &pnt) const;

  /**
   * @brief Get the intersection type between segment and point.
   * @param s0_s1 two vertices of segment
   * @param p point
   */
  PointInSimplexType intersection_type(const GPoint3 &s0, const GPoint3 &s1,
                                       const GPoint3 &p) const;

  /**
   * @brief Get the intersection type between segment and point.
   * @param s0_s1 two vertices of segment
   * @param p point
   */
  PointInSimplexType intersection_type(const NT *s0, const NT *s1,
                                       const NT *p) const;

  // Equivalent but faster. They assume that the
  // dominant normal component is n_max (see MaxComponentInTriangleNormal).

  bool operator()(const Segment3 &seg, const GPoint3 &pnt, int n_max) const;

  PointInType in_segment(const Segment3 &seg, const GPoint3 &pnt,
                         int n_max) const;

  PointInType in_segment(const GPoint3 &s0, const GPoint3 &s1,
                         const GPoint3 &pnt, int n_max) const;

  PointInSimplexType intersection_type(const GPoint3 &s0, const GPoint3 &s1,
                                       const GPoint3 &p, int n_max) const;

  PointInSimplexType intersection_type(const NT *s0, const NT *s1, const NT *p,
                                       int n_max) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Segment3_Point3.inl"
#endif