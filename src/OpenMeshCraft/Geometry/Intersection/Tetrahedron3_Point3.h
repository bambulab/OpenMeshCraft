#pragma once

#include "IntersectionUtils.h"

namespace OMC {

/**
 * @brief Check if Tetrahedron3 and Point3 intersect.
 *
 * From the simplex and bounded side views, the intersection can be classified
 * into 3 types:
 *
 * - DO_NOT_INTERSECT : the point is strictly outside the tetrahedron.
 *
 * - SIMPLICIAL_COMPLEX : the point is one of the vertices of the tetrahedron.
 *
 * - INTERSECT : the point is on the edge, face, or inside the tetrahedron.
 *
 * The last two types are considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Tetrahedron3_Point3_DoIntersectK
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using GPoint3      = typename K::GPoint3;
	using Tetrahedron3 = typename K::Tetrahedron3;

	using LessThan3D       = typename K::LessThan3D;
	using OrientOn2D       = typename K::OrientOn2D;
	using Orient3D         = typename K::Orient3D;
	using CollinearPoints3 = typename K::CollinearPoints3;

public:
	/**
	 * @brief Check if tetrahedron and point intersect.
	 * @note assume that tetrahedron is not degenerate.
	 */
	bool operator()(const Tetrahedron3 &tet, const GPoint3 &pnt) const;

	/**
	 * @brief Check if tetrahedron and point intersect.
	 * @param v0_v1_v2_v3 four vertices of tetrahedron
	 * @param p point
	 * @note assume that tetrahedron is not degenerate.
	 */
	bool operator()(const GPoint3 &v0, const GPoint3 &v1, const GPoint3 &v2,
	                const GPoint3 &v3, const GPoint3 &p) const;

	/**
	 * @brief Get the intersection type between tetrahedron and point.
	 * @note assume that tetrahedron is not degenerate.
	 */
	PointInSimplexType intersection_type(const Tetrahedron3 &tet,
	                                     const GPoint3      &pnt) const;

	/**
	 * @brief Get the intersection type between tetrahedron and point.
	 * @param v0_v1_v2_v3 four vertices of tetrahedron
	 * @param p point
	 * @note assume that tetrahedron is not degenerate.
	 */
	PointInSimplexType intersection_type(const GPoint3 &v0, const GPoint3 &v1,
	                                     const GPoint3 &v2, const GPoint3 &v3,
	                                     const GPoint3 &p) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "Tetrahedron3_Point3.inl"
#endif