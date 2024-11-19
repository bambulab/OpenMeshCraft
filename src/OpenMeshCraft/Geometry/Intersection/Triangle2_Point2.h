#pragma once

#include "IntersectionUtils.h"

namespace OMC {

/**
 * @brief Check if Triangle2 and Point2 intersect.
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
class Triangle2_Point2_Do_Intersect
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using VecT      = typename K::Vec2;
	using GPointT   = typename K::GPoint2;
	using TriangleT = typename K::Triangle2;

	using LessThan2D = typename K::LessThan2D;
	using Orient2D   = typename K::Orient2D;

public:
	/**
	 * @brief Check if triangle and point intersect.
	 * @note Assume that triangle is not degenerate.
	 */
	bool operator()(const TriangleT &tri, const GPointT &pnt) const;

	/**
	 * @brief Get the relative position of point to triangle.
	 * @return Sign indicating relative position of point to triangle.
	 * @note Assume that triangle is not degenerate.
	 */
	PointInType in_triangle(const TriangleT &tri, const GPointT &pnt) const;

	/**
	 * @brief Get the intersection type between triangle and point.
	 */
	PointInSimplexType intersection_type(const TriangleT &tri,
	                                     const GPointT   &pnt) const;

	/**
	 * @brief Get the intersection type between triangle and point.
	 * @param t0_t1_t2 three vertices of the triangle
	 * @param p point
	 * @note Assume that triangle is not degenerate.
	 */
	PointInSimplexType intersection_type(const GPointT &t0, const GPointT &t1,
	                                     const GPointT &t2,
	                                     const GPointT &p) const;

	/**
	 * @brief Get the intersection type between triangle and point.
	 * @param t0_t1_t2 three vertices of the triangle.
	 * @param p point.
	 * @note Assume that triangle is not degenerate.
	 */
	PointInSimplexType intersection_type(const NT *t0, const NT *t1, const NT *t2,
	                                     const NT *p) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "Triangle2_Point2.inl"
#endif