#pragma once

#include "PointBound.h"

#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"

namespace OMC {

/**
 * @brief Calculate bounding box for given primitives.
 * @tparam Kernel
 */
template <typename Kernel>
class CalcBoundingBox3K
{
public:
	using K = Kernel;

	using IT = IntervalNumber<std::true_type>;

	using EPointT = typename K::EPoint3;
	using GPointT = typename K::GPoint3;

	using SphereT   = typename K::Sphere3;
	using SegmentT  = typename K::Segment3;
	using TriangleT = typename K::Triangle3;
	using BboxT     = typename K::BoundingBox3;

public:
	/* Below functions calculate box for given primitives and update reference
	 * box. */

	/// @brief Special version for implicit/generic points.
	template <typename GPT,
	          typename = std::enable_if_t<std::is_same_v<GPT, GPointT> &&
	                                      !std::is_same_v<GPT, EPointT>>>
	void operator()(BboxT &box, const GPT &gp);

	void operator()(BboxT &box, const EPointT &point);
	void operator()(BboxT &box, const SegmentT &segment);
	void operator()(BboxT &box, const TriangleT &triangle);
	void operator()(BboxT &box, const SphereT &sphere);

	/**
	 * @brief Calculate a bounding box for a given primitive.
	 * @tparam PrimitiveT Any geometry primitive.
	 * @param primitive The given primitive.
	 * @return The resulting bounding box.
	 */
	template <typename PrimitiveT>
	BboxT operator()(const PrimitiveT &primitive)
	{
		BboxT box;
		(*this)(box, primitive);
		return box;
	}
};

template <typename Kernel>
template <typename GPT, typename /*SFINAE*/>
void CalcBoundingBox3K<Kernel>::operator()(BboxT &box, const GPT &gp)
{
	auto [minb, maxb] = PointBound<GPointT, EPointT>().both_bounds(gp);
	box.min_bound()   = minb;
	box.max_bound()   = maxb;
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BboxT &box, const EPointT &point)
{
	box.min_bound() = point;
	box.max_bound() = point;
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BboxT &box, const SegmentT &segment)
{
	box.min_bound() = segment.start();
	box.min_bound().minimize(segment.end());
	box.max_bound() = segment.start();
	box.max_bound().maximize(segment.end());
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BboxT           &box,
                                           const TriangleT &triangle)
{
	box.min_bound() = triangle.v0();
	box.max_bound() = triangle.v0();
	box.min_bound().minimize(triangle.v1());
	box.min_bound().minimize(triangle.v2());
	box.max_bound().maximize(triangle.v1());
	box.max_bound().maximize(triangle.v2());
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BboxT &box, const SphereT &sphere)
{
	IT::Protector it_protecter;

	IT cx(sphere.center().x());
	IT cy(sphere.center().y());
	IT cz(sphere.center().z());
	IT sr(sphere.squared_radius());

	IT r    = sr.sqrt();
	IT minx = cx - r, miny = cy - r, minz = cz - r;
	IT maxx = cx + r, maxy = cy + r, maxz = cz + r;

	box.min_bound() = EPointT(minx.inf(), miny.inf(), minz.inf());
	box.max_bound() = EPointT(maxx.sup(), maxy.sup(), maxz.sup());
}

} // namespace OMC