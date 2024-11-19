#pragma once

#include "Sphere3_Point3.h"

namespace OMC {

template <typename Kernel>
bool Sphere3_Point3_Do_Intersect<Kernel>::operator()(const SphereT &sphere,
                                                     const GPointT &pnt) const
{
  return operator()(sphere.center(), sphere.squared_radius(), pnt);
}

template <typename Kernel>
bool Sphere3_Point3_Do_Intersect<Kernel>::operator()(const GPointT &center,
                                                     NT squared_radius,
                                                     const GPointT &p) const
{
	return intersection_type(center, squared_radius, p) !=
	       PointInType::STRICTLY_OUTSIDE;
}

template <typename Kernel>
PointInType
Sphere3_Point3_Do_Intersect<Kernel>::intersection_type(const SphereT &sphere,
                                                       const GPointT &pnt) const
{
	return intersection_type(sphere.center(), sphere.squared_radius(), pnt);
}

template <typename Kernel>
PointInType Sphere3_Point3_Do_Intersect<Kernel>::intersection_type(
  const GPointT &center, NT squared_radius, const GPointT &p) const
{
	Sign sign = SquaredDistance()(center, p, squared_radius);
	return sign == Sign::POSITIVE
	         ? (PointInType::STRICTLY_OUTSIDE)
	         : (sign == Sign::ZERO ? PointInType::ON_BOUNDARY
	                               : PointInType::STRICTLY_INSIDE);
}

} // namespace OMC