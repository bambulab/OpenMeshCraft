#pragma once

#include "Sphere3_Point3.h"

#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

namespace OMC {

template <typename Kernel>
bool Sphere3_Point3_DoIntersectK<Kernel>::operator()(const Sphere3 &sphere,
                                                     const GPoint3 &pnt) const
{
  return operator()(sphere.center(), sphere.squared_radius(), pnt);
}

template <typename Kernel>
bool Sphere3_Point3_DoIntersectK<Kernel>::operator()(const GPoint3 &center,
                                                     NT squared_radius,
                                                     const GPoint3 &p) const
{
  return intersection_type(center, squared_radius, p) !=
         PointInType::STRICTLY_OUTSIDE;
}

template <typename Kernel>
PointInType
Sphere3_Point3_DoIntersectK<Kernel>::intersection_type(const Sphere3 &sphere,
                                                       const GPoint3 &pnt) const
{
  return intersection_type(sphere.center(), sphere.squared_radius(), pnt);
}

template <typename Kernel>
PointInType Sphere3_Point3_DoIntersectK<Kernel>::intersection_type(
  const GPoint3 &center, NT squared_radius, const GPoint3 &p) const
{
  Sign sign = SquaredDistance3D()(center, p, squared_radius);
  return sign == Sign::POSITIVE
           ? (PointInType::STRICTLY_OUTSIDE)
           : (sign == Sign::ZERO ? PointInType::ON_BOUNDARY
                                 : PointInType::STRICTLY_INSIDE);
}

} // namespace OMC