#pragma once

#include "IntersectionUtils.h"
#include "Segment2_Segment2.h"

namespace OMC {

/**
 * @brief Check if two Segment3 intersect.
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
class Segment3_Segment3_DoIntersectK
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using GPoint3  = typename K::GPoint3;
  using Segment3 = typename K::Segment3;

  using LessThan3D = typename K::LessThan3D;
  using OrientOn2D = typename K::OrientOn2D;
  using Orient3D   = typename K::Orient3D;

  using Segment2_Segment2_DoInter = Segment2_Segment2_DoIntersectK<Kernel>;

public:
  /**
   * @brief Check if two segments intersect. Two segments
   * are assumed to be coplanar, otherwise the result is undetermined.
   * @note Assume that no segment is degenerate.
   */
  bool operator()(const Segment3 &seg0, const Segment3 &seg1) const;

  /**
   * @brief Check if two segments intersect. Two segments
   * are assumed to be coplanar, otherwise the result is undetermined.
   * @param AB Point A and B form the first segment
   * @param PQ Point P and Q form the second segment
   * @note Assume that no segment is degenerate.
   */
  bool operator()(const GPoint3 &A, const GPoint3 &B, const GPoint3 &P,
                  const GPoint3 &Q) const;

  /*************************************************************************/
  /******* Below functions all assume that two segments are coplanar *******/
  /*************************************************************************/

  /**
   * @brief Check if the closure of two segments intersect at a single point
   * (overlap is excluded). Two segments are assumed to be coplanar, otherwise
   * the result is undetermined.
   * @return TRUE if the closure of two segments intersect at a single point.
   * @note Assume that no segment is degenerate and two segments are coplanar.
   */
  bool cross(const Segment3 &seg0, const Segment3 &seg1) const;

  /**
   * @brief Check if the interior of two segments in 3D intersect at a single
   * point (overlap is excluded). Two segments are assumed to be coplanar,
   * otherwise the result is undetermined.
   * @return TRUE if the interior of two segments intersect at a single point.
   * @note Assume that no segment is degenerate and two segments are coplanar.
   */
  bool cross_inner(const Segment3 &seg0, const Segment3 &seg1) const;

  /**
   * @brief Check if the closure of two segments intersect at a single point
   * (overlap is excluded). Two segments are assumed to be coplanar, otherwise
   * the result is undetermined.
   * @param AB Point A and B form the first segment
   * @param PQ Point P and Q form the second segment
   * @return TRUE if the closure of two segments intersect at a single point.
   * @note Assume that no segment is degenerate and two segments are coplanar.
   */
  bool cross(const GPoint3 &A, const GPoint3 &B, const GPoint3 &P,
             const GPoint3 &Q) const;

  /**
   * @brief Check if the interior of two segments in 3D intersect at a single
   * point (overlap is excluded). Two segments are assumed to be coplanar,
   * otherwise the result is undetermined.
   * @param AB Point A and B form the first segment
   * @param PQ Point P and Q form the second segment
   * @return TRUE if the interior of two segments intersect at a single point.
   * @note Assume that no segment is degenerate and two segments are coplanar.
   */
  bool cross_inner(const GPoint3 &A, const GPoint3 &B, const GPoint3 &P,
                   const GPoint3 &Q) const;

  // Equivalent but faster. They assume that points are coplanar and the
  // dominant normal component is n_max (see MaxComponentInTriangleNormal).

  bool cross(const GPoint3 &A, const GPoint3 &B, const GPoint3 &P,
             const GPoint3 &Q, int n_max) const;

  bool cross_inner(const GPoint3 &A, const GPoint3 &B, const GPoint3 &P,
                   const GPoint3 &Q, int n_max) const;

  /**
   * @brief Get the intersection type between two segments.
   * @note Assume that two segments are coplanar.
   */
  SimplexIntersectionType intersection_type(const Segment3 &seg0,
                                            const Segment3 &seg1) const;

  /**
   * @brief Get the intersection type between two segments.
   * @param AB two points form the first segment.
   * @param PQ two points form the second segment.
   * @note Assume that two segments are coplanar.
   */
  SimplexIntersectionType intersection_type(const GPoint3 &A, const GPoint3 &B,
                                            const GPoint3 &P,
                                            const GPoint3 &Q) const;

  /**
   * @brief Get the intersection type between two segments.
   * @param AB two points form the first segment.
   * @param PQ two points form the second segment.
   * @note Assume that two segments are coplanar.
   */
  SimplexIntersectionType intersection_type(const NT *A, const NT *B,
                                            const NT *P, const NT *Q) const;

  // Equivalent but faster. They assume that the
  // dominant normal component is n_max (see MaxComponentInTriangleNormal).

  /**
   * @brief Get the intersection type between two segments.
   * @param AB two points form the first segment.
   * @param PQ two points form the second segment.
   * @param n1_max max normal component of the triangle that segment PQ belongs
   * to. It indicates a plane where the segments are projected to, and the
   * projection won't be degenerate if the segments are not degenerate
   * originally.
   * @note Assume that two segments are coplanar.
   */
  SimplexIntersectionType intersection_type(const NT *A, const NT *B,
                                            const NT *P, const NT *Q,
                                            int n1_max) const;

protected:
  /**
   * @brief Get the intersection type between two segments on 2D plane.
   * @param AB two points form the first segment.
   * @param PQ two points form the second segment.
   * @param on2d 0: yz plane; 1: zx plane; 2: xy plane.
   * @note almostly same as Segment2_Segment2_DoIntersectK.
   */
  SimplexIntersectionType
  intersection_type_on2d(const GPoint3 &A, const GPoint3 &B, const GPoint3 &P,
                         const GPoint3 &Q, int on2d) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Segment3_Segment3.inl"
#endif