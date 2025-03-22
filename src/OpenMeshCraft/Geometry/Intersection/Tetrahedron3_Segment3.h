#pragma once

#include "IntersectionUtils.h"
#include "Segment3_Segment3.h"
#include "Tetrahedron3_Point3.h"
#include "Triangle3_Segment3.h"

namespace OMC {

/**
 * @brief Check if Tetrahedron3 and Segment3 intersect.
 *
 * From the simplex and bounded side views, the intersection can be classified
 * into 3 types:
 *
 * - DO_NOT_INTERSECT : the segment does not intersect the tetrahedron.
 *
 * - SIMPLICIAL_COMPLEX : the segment shares only an edge or a vertex of the
 * tetrahedron.
 *
 * - INTERSECT : the segment intersects tetrahedron at at least a point
 * (vertex, edge, face, or interior) except the SIMPLICIAL_COMPLEX case.
 *
 * The last two types are considered as intersect.
 *
 * @tparam Kernel
 */
template <typename Kernel>
class Tetrahedron3_Segment3_DoIntersectK
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using GPoint3      = typename K::GPoint3;
	using Segment3     = typename K::Segment3;
	using Triangle3    = typename K::Triangle3;
	using Tetrahedron3 = typename K::Tetrahedron3;

	using LessThan3D       = typename K::LessThan3D;
	using OrientOn2D       = typename K::OrientOn2D;
	using Orient3D         = typename K::Orient3D;
	using CollinearPoints3 = typename K::CollinearPoints3;

	using Tetrahedron3_Point3_DoInter = Tetrahedron3_Point3_DoIntersectK<Kernel>;
	using Triangle3_Segment3_DoInter  = Triangle3_Segment3_DoIntersectK<Kernel>;
	using Segment3_Segment3_DoInter   = Segment3_Segment3_DoIntersectK<Kernel>;

public:
	/**
	 * @brief Check if tetrahedron and segment intersect.
	 * @note Assume no one is degenerate.
	 */
	bool operator()(const Tetrahedron3 &tet, const Segment3 &seg) const;

	/**
	 * @brief Check if tetrahedron and segment intersect.
	 * @param v0_v1_v2_v3 four vertices of tetrahedron
	 * @param s0_s1 two vertices of segment
	 * @note Assume no one is degenerate.
	 */
	bool operator()(const GPoint3 &t0, const GPoint3 &t1, const GPoint3 &t2,
	                const GPoint3 &t3, const GPoint3 &s0,
	                const GPoint3 &s1) const;

	/**
	 * @brief Get the intersection type between tetrahedron and segment.
	 * @note Assume no one is degenerate.
	 */
	SimplexIntersectionType intersection_type(const Tetrahedron3 &tet,
	                                          const Segment3     &seg) const;

	/**
	 * @brief Get the intersection type between tetrahedron and segment.
	 * @param v0_v1_v2_v3 four vertices of tetrahedron
	 * @param s0_s1 two vertices of segment
	 * @note Assume no one is degenerate.
	 */
	SimplexIntersectionType
	intersection_type(const GPoint3 &t0, const GPoint3 &t1, const GPoint3 &t2,
	                  const GPoint3 &t3, const GPoint3 &s0,
	                  const GPoint3 &s1) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "Tetrahedron3_Segment3.inl"
#endif