#pragma once

#include "IntersectionUtils.h"
#include "Sphere3_Point3.h"

namespace OMC {

/**
 * @brief Check if Sphere3 and Segment3 intersect.
 *
 * From the bounded side view, the intersection can be classified into 3 types:
 *
 * - STRICTLY_INSIDE : the segment is strictly inside the sphere (two endpoints
 *   are strictly inside the sphere).
 *
 * - CROSS : the segment intersects the sphere's boundary at at least one point
 *  (at most two points).
 *
 * - STRICTLY_OUTSIDE : the segment is strictly outside the sphere.
 * 
 * The first two types are considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Sphere3_Segment3_Do_Intersect
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using VecT     = typename K::Vec3;
	using GPointT  = typename K::GPoint3;
	using SphereT  = typename K::Sphere3;
	using SegmentT = typename K::Segment3;

	using DotProductSign  = typename K::DotProductSign3D;
	using SquaredDistance = typename K::SquaredDistance3D;

	using Sphere3_Point3_DoInter = Sphere3_Point3_Do_Intersect<K>;

public:
	/**
	 * @brief Check if sphere and segment intersect.
	 * @note Assume no one is degenerate.
	 */
	bool operator()(const SphereT &sphere, const SegmentT &seg) const;

	/**
	 * @brief Check if sphere and segment intersect.
	 * @param center The center of the sphere.
	 * @param squared_radius The squared radius of the sphere
	 * @param s0_s1 two vertices of segment
	 * @note Assume no one is degenerate.
	 */
	bool operator()(const GPointT &center, NT squared_radius, const GPointT &s0,
	                const GPointT &s1) const;

	/**
	 * @brief Get the intersection type between segment and segment.
	 * @note Assume no one is degenerate.
	 */
	IntersectionType intersection_type(const SphereT  &sphere,
	                                   const SegmentT &seg) const;

	/**
	 * @brief Get the intersection type between segment and segment.
	 * @param center The center of the sphere.
	 * @param squared_radius The squared radius of the sphere
	 * @param s0_s1 two vertices of segment
	 * @note Assume no one is degenerate.
	 */
	IntersectionType intersection_type(const GPointT &center, NT squared_radius,
	                                   const GPointT &s0,
	                                   const GPointT &s1) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "Sphere3_Segment3.inl"
#endif