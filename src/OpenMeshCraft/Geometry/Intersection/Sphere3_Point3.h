#pragma once

#include "IntersectionUtils.h"

namespace OMC {

/**
 * @brief Check if Sphere3 and Point3 intersect.
 *
 * From the bounded side view, the intersection can be classified into 3 types:
 * STRICTLY_INSIDE, ON_BOUNDARY, and STRICTLY_OUTSIDE.
 *
 * The first two types are considered as intersect.
 * @tparam Kernel
 */
template <typename Kernel>
class Sphere3_Point3_DoIntersectK
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using GPoint3 = typename K::GPoint3;
  using Sphere3 = typename K::Sphere3;

  using SquaredDistance3D = typename K::SquaredDistance3D;

public:
  /**
   * @brief Check if sphere and point intersect.
   */
  bool operator()(const Sphere3 &sphere, const GPoint3 &pnt) const;

  /**
   * @brief Check if sphere and point intersect.
   * @param center The center of the sphere.
   * @param squared_radius The squared radius of the sphere
   * @param p point
   */
  bool operator()(const GPoint3 &center, NT squared_radius,
                  const GPoint3 &p) const;

  /**
   * @brief Get the intersection type between tetrahedron and point.
   */
  PointInType intersection_type(const Sphere3 &sphere,
                                const GPoint3 &pnt) const;

  /**
   * @brief Get the intersection type between tetrahedron and point.
   * @param center The center of the sphere.
   * @param squared_radius The squared radius of the sphere
   * @param p point
   */
  PointInType intersection_type(const GPoint3 &center, NT squared_radius,
                                const GPoint3 &p) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Sphere3_Point3.inl"
#endif