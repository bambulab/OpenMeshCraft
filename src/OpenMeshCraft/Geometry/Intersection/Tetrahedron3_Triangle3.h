#pragma once

#include "IntersectionUtils.h"
#include "Tetrahedron3_Segment3.h"
#include "Triangle3_Triangle3.h"

namespace OMC {

/**
 * @brief Check if Tetrahedron3 and Triangle3 intersect.
 *
 * From the simplex and bounded side views, the intersection can be classified
 * into 3 types:
 *
 * - DO_NOT_INTERSECT : the triangle does not intersect the tetrahedron.
 *
 * - SIMPLICIAL_COMPLEX : the triangle shares only a face, an edge or a vertex
 * of the tetrahedron.
 *
 * - INTERSECT : the segment intersects tetrahedron at at least a point
 * (vertex, edge, face, or interior) except the SIMPLICIAL_COMPLEX case.
 *
 * The last two types are considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Tetrahedron3_Triangle3_DoIntersectK
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using GPoint3      = typename K::GPoint3;
  using Segment3     = typename K::Segment3;
  using Triangle3    = typename K::Triangle3;
  using Tetrahedron3 = typename K::Tetrahedron3;

  using LessThan3D       = typename K::LessThan3D;
  using OrientOn2D       = typename K::OrientOn2D;
  using Orient3D         = typename K::Orient3D;
  using CollinearPoints3 = typename K::CollinearPoints3;

  using Triangle3_Triangle3_DoInter = Triangle3_Triangle3_DoIntersectK<Kernel>;
  using Tetrahedron3_Point3_DoInter = Tetrahedron3_Point3_DoIntersectK<Kernel>;
  using Tetrahedron3_Segment3_DoInter =
    Tetrahedron3_Segment3_DoIntersectK<Kernel>;

public:
  /**
   * @brief Check if a tetrahedron and a triangle intersect.
   * @note Assume that no tetrahedron or triangle is degenerate.
   */
  bool operator()(const Tetrahedron3 &tet, const Triangle3 &tri) const;

  /**
   * @brief Check if a tetrahedron and a triangle intersect.
   * @param t0_t1_t2_t3 four vertices of the tetrahedron.
   * @param v0_v1_v2 three vertices of the triangle.
   * @note Assume that no tetrahedron or triangle is degenerate.
   */
  bool operator()(const GPoint3 &t0, const GPoint3 &t1, const GPoint3 &t2,
                  const GPoint3 &t3, const GPoint3 &v0, const GPoint3 &v1,
                  const GPoint3 &v2) const;

  /**
   * @brief Get the intersection type between a tetrahedron and a triangle.
   * @note Assume that no tetrahedron or triangle is degenerate.
   */
  SimplexIntersectionType intersection_type(const Tetrahedron3 &tet,
                                            const Triangle3    &tri) const;

  /**
   * @brief Get the intersection type between a tetrahedron and a triangle.
   * @param t0_t1_t2_t3 four vertices of the tetrahedron.
   * @param v0_v1_v2 three vertices of the triangle.
   * @note Assume that no tetrahedron or triangle is degenerate.
   */
  SimplexIntersectionType
  intersection_type(const GPoint3 &t0, const GPoint3 &t1, const GPoint3 &t2,
                    const GPoint3 &t3, const GPoint3 &v0, const GPoint3 &v1,
                    const GPoint3 &v2) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Tetrahedron3_Triangle3.inl"
#endif