#pragma once

#include "IntersectionUtils.h"

namespace OMC {

/**
 * @brief Check if Sphere3 and Point3 intersect.
 * @tparam Kernel
 */
template <typename Kernel>
class Sphere3_Point3_Do_Intersect
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using VecT    = typename K::Vec3;
	using GPointT = typename K::GPoint3;
	using SphereT = typename K::Sphere3;

	using SquaredDistance = typename K::SquaredDistance3D;

public:
	/**
	 * @brief Check if sphere and point intersect.
	 */
	bool operator()(const SphereT &sphere, const GPointT &pnt) const;

	/**
	 * @brief Check if sphere and point intersect.
	 * @param center The center of the sphere.
	 * @param squared_radius The squared radius of the sphere
	 * @param p point
	 */
	bool operator()(const GPointT &center, NT squared_radius,
	                const GPointT &p) const;

	/**
	 * @brief Get the intersection type between tetrahedron and point.
	 */
	PointInType intersection_type(const SphereT &sphere,
	                              const GPointT &pnt) const;

	/**
	 * @brief Get the intersection type between tetrahedron and point.
	 * @param center The center of the sphere.
	 * @param squared_radius The squared radius of the sphere
	 * @param p point
	 */
	PointInType intersection_type(const GPointT &center, NT squared_radius,
	                              const GPointT &p) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "Sphere3_Point3.inl"
#endif