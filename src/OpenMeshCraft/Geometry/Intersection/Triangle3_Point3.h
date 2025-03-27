#pragma once

#include "IntersectionUtils.h"
#include "Segment3_Point3.h"

namespace OMC {

/**
 * @brief Check if Triangle3 and Point3 intersect.
 *
 * From the simplex and bounded side views, the intersection can be classified
 * into 3 types:
 *
 * - DO_NOT_INTERSECT : the triangle does not intersect the point.
 *
 * - SIMPLICIAL_COMPLEX : the point is a vertex of the triangle.
 *
 * - INTERSECT : the point is on the edge or inside the triangle.
 *
 * The last two types are considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Triangle3_Point3_DoIntersectK
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using GPoint3   = typename K::GPoint3;
  using Triangle3 = typename K::Triangle3;

  using LessThan3D       = typename K::LessThan3D;
  using OrientOn2D       = typename K::OrientOn2D;
  using Orient3D         = typename K::Orient3D;
  using CollinearPoints3 = typename K::CollinearPoints3;

  using Segment3_Point3_DoInter = Segment3_Point3_DoIntersectK<Kernel>;

public:
  /**
   * @brief Check if triangle and point intersect.
   * @note assume that triangle is not degenerate.
   */
  bool operator()(const Triangle3 &tri, const GPoint3 &pnt) const;

  /**
   * @brief Check if triangle and point intersect.
   * @param v0_v1_v2 three vertices of triangle
   * @param p point
   * @note assume that triangle is not degenerate.
   */
  bool operator()(const GPoint3 &v0, const GPoint3 &v1, const GPoint3 &v2,
                  const GPoint3 &p) const;

  // Equivalent but faster. They assume that the
  // dominant normal component is n_max (see MaxComponentInTriangleNormal).

  bool operator()(const Triangle3 &tri, const GPoint3 &pnt, int n_max) const;

  /*************************************************************************/
  /* NOTE below functions all assume that point is COPLANAR to triangle!!! */
  /*************************************************************************/

  /**
   * @brief Get the relative position of point to triangle.
   * @return Sign indicating relative position of point to triangle.
   * @note assume that point is coplanar to triangle.
   * @note assume that triangle is not degenerate.
   */
  PointInType in_triangle(const Triangle3 &tri, const GPoint3 &pnt) const;

  /**
   * @brief Get the relative position of point to triangle.
   * @param v0_v1_v2 three vertices of triangle
   * @param p point
   * @return Sign indicating relative position of point to triangle.
   * @note assume that point is coplanar to triangle.
   * @note assume that triangle is not degenerate.
   */
  PointInType in_triangle(const GPoint3 &v0, const GPoint3 &v1,
                          const GPoint3 &v2, const GPoint3 &p) const;

  /**
   * @brief Get the relative position of point to triangle.
   * @param v0_v1_v2 three vertices of triangle
   * @param p point
   * @return Sign indicating relative position of point to triangle.
   * @note assume that point is coplanar to triangle.
   * @note assume that triangle is not degenerate.
   */
  PointInType in_triangle(const NT *v0, const NT *v1, const NT *v2,
                          const NT *p) const;

  /**
   * @brief Get the intersection type between triangle and point.
   * @note assume that point is coplanar to triangle.
   * @note assume that triangle is not degenerate.
   */
  PointInSimplexType intersection_type(const Triangle3 &tri,
                                       const GPoint3   &pnt) const;

  /**
   * @brief Get the intersection type between triangle and point.
   * @param v0_v1_v2 three vertices of triangle
   * @param p point
   * @note assume that point is coplanar to triangle.
   * @note assume that triangle is not degenerate.
   */
  PointInSimplexType intersection_type(const GPoint3 &v0, const GPoint3 &v1,
                                       const GPoint3 &v2,
                                       const GPoint3 &p) const;

  /**
   * @brief Get the intersection type between triangle and point.
   * @param v0_v1_v2 three vertices of triangle
   * @param p point
   * @note assume that point is coplanar to triangle.
   * @note assume that triangle is not degenerate.
   */
  PointInSimplexType intersection_type(const NT *v0, const NT *v1, const NT *v2,
                                       const NT *p) const;

  // Equivalent but faster. They assume that the
  // dominant normal component is n_max (see MaxComponentInTriangleNormal).

  PointInType in_triangle(const Triangle3 &tri, const GPoint3 &pnt,
                          int n_max) const;

  PointInType in_triangle(const GPoint3 &v0, const GPoint3 &v1,
                          const GPoint3 &v2, const GPoint3 &p, int n_max) const;

  PointInType in_triangle(const NT *v0, const NT *v1, const NT *v2, const NT *p,
                          int n_max) const;

  PointInSimplexType intersection_type(const NT *v0, const NT *v1, const NT *v2,
                                       const NT *p, int n_max) const;

protected:
  PointInType check_inout(Sign o1, Sign o2, Sign o3) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Triangle3_Point3.inl"
#endif