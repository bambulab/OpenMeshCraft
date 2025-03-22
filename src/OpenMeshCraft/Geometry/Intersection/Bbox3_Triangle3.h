#pragma once

namespace OMC {

/**
 * @brief Check if BoundingBox3 and Triangle3 intersect.
 * @tparam Kernel
 * @todo Implement an standard box-triangle intersection test.
 * @fixme This predicate is inexact in all kernels with inexact construction.
 * Because current implementation containts inexact construction.
 */
template <typename Kernel>
class Bbox3_Triangle3_DoIntersectK
{
public:
	using K  = Kernel;
	using NT = typename K::NT;

	using EPoint3   = typename K::EPoint3;
	using Vec3      = typename K::Vec3;
	using Bbox3     = typename K::BoundingBox3;
	using Triangle3 = typename K::Triangle3;

public:
	bool operator()(const Bbox3 &box, const Triangle3 &triangle) const;

	bool TestAxisEdges(const EPoint3 *v[], const Vec3 &e,
	                   const NT *box_length) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "Bbox3_Triangle3.inl"
#endif