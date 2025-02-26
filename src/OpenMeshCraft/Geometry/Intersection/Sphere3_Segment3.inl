#pragma once

#include "Sphere3_Segment3.h"

namespace OMC {

template <typename Kernel>
bool Sphere3_Segment3_Do_Intersect<Kernel>::operator()(
  const SphereT &sphere, const SegmentT &seg) const
{
	return operator()(sphere.center(), sphere.squared_radius(), seg.start(),
	                  seg.end());
}

template <typename Kernel>
bool Sphere3_Segment3_Do_Intersect<Kernel>::operator()(const GPointT &center,
                                                       NT squared_radius,
                                                       const GPointT &s0,
                                                       const GPointT &s1) const
{
	return intersection_type(center, squared_radius, s0, s1) !=
	       IntersectionType::DO_NOT_INTERSECT;
}

template <typename Kernel>
IntersectionType Sphere3_Segment3_Do_Intersect<Kernel>::intersection_type(
  const SphereT &sphere, const SegmentT &seg) const
{
	return intersection_type(sphere.center(), sphere.squared_radius(),
	                         seg.start(), seg.end());
}

template <typename Kernel>
IntersectionType Sphere3_Segment3_Do_Intersect<Kernel>::intersection_type(
  const GPointT &center, NT squared_radius, const GPointT &s0,
  const GPointT &s1) const
{
	if (Sphere3_Point3_DoInter()(center, squared_radius, s0) ||
	    Sphere3_Point3_DoInter()(center, squared_radius, s1))
	{
		return IntersectionType::INTERSECT;
	}

	// `s0` and `s1` are both outside the sphere, but the segment may still
	// intersect the sphere. Compute the squared distance between the center of
	// the sphere and the segment. If the squared distance is less than the
	// squared radius of the sphere, then the segment intersects the sphere.

	if (DotProductSign()(s1, center, s0) <= Sign::ZERO)
	{ // (s1 - s0) dot (center - s0) <= 0
		// s0 is the closest point to the sphere
		return SquaredDistance()(center, s0, squared_radius) <= Sign::ZERO
		         ? IntersectionType::INTERSECT
		         : IntersectionType::DO_NOT_INTERSECT;
	}
	else if (DotProductSign()(s0, center, s1) <= Sign::ZERO)
	{ // (s0 - s1) dot (center - s1) <= 0
		// s1 is the closest point to the sphere
		return SquaredDistance()(center, s1, squared_radius) <= Sign::ZERO
		         ? IntersectionType::INTERSECT
		         : IntersectionType::DO_NOT_INTERSECT;
	}
	else
	{
		// The closest point to the center is on the segment.
		// We need to compute the projecting distance between the center and the
		// line formed by s0 and s1.
		return SquaredDistance()(s0, s1, center, squared_radius) <= Sign::ZERO
		         ? IntersectionType::INTERSECT
		         : IntersectionType::DO_NOT_INTERSECT;
	}
}

} // namespace OMC