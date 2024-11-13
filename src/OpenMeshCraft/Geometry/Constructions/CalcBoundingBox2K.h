#pragma once

#include "PointBound.h"

namespace OMC {

/**
 * @brief Calculate bounding box for given primitives.
 * @tparam Kernel
 */
template <typename Kernel>
class CalcBoundingBox2K
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using EPointT = typename K::EPoint2;
	using GPointT = typename K::GPoint2;

	using SegmentT  = typename K::Segment2;
	using TriangleT = typename K::Triangle2;
	using BboxT     = typename K::BoundingBox2;

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
void CalcBoundingBox2K<Kernel>::operator()(BboxT &box, const GPT &gp)
{
	box.min_bound() = PointBound<GPointT, EPointT>().lower_bound(gp);
	box.max_bound() = PointBound<GPointT, EPointT>().upper_bound(gp);
}

template <typename Kernel>
void CalcBoundingBox2K<Kernel>::operator()(BboxT &box, const EPointT &point)
{
	box.min_bound() = point;
	box.max_bound() = point;
}

template <typename Kernel>
void CalcBoundingBox2K<Kernel>::operator()(BboxT &box, const SegmentT &segment)
{
	box.min_bound() = segment.start();
	box.min_bound().minimize(segment.end());
	box.max_bound() = segment.start();
	box.max_bound().maximize(segment.end());
}

template <typename Kernel>
void CalcBoundingBox2K<Kernel>::operator()(BboxT           &box,
                                           const TriangleT &triangle)
{
	box.min_bound() = triangle.v0();
	box.max_bound() = triangle.v0();
	box.min_bound().minimize(triangle.v1());
	box.min_bound().minimize(triangle.v2());
	box.max_bound().maximize(triangle.v1());
	box.max_bound().maximize(triangle.v2());
}

} // namespace OMC