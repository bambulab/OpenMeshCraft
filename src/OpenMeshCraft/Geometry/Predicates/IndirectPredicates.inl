#pragma once

#include "IndirectPredicates.h"

#include "InternalDetails/DotProductSign.inl"
#include "InternalDetails/InCircle.inl"
#include "InternalDetails/InSphere.inl"
#include "InternalDetails/LessThan.inl"
#include "InternalDetails/LongestAxis.inl"
#include "InternalDetails/Orient2D.inl"
#include "InternalDetails/Orient3D.inl"
#include "InternalDetails/OrientOn2D.inl"
#include "InternalDetails/SquaredDistance.inl"
#include "InternalDetails/TriangleNormal.inl"

#include "OpenMeshCraft/Utils/Exception.h"

#include <bitset>

namespace OMC {

#define TEMPLATE_DECL template <typename FT, typename IT, typename ET>
#define TP IT, ET // Template Parameters
#define PntType(p) static_cast<uint32_t>(p.point_type())

/******************************************************************************/
/* Dot Product ****************************************************************/
/******************************************************************************/

TEMPLATE_DECL
Sign DotProductSign2D_Indirect<FT, IT, ET>::operator()(const PointT &p,
                                                       const PointT &r,
                                                       const PointT &q)
{
	PntArr2 arr = get_pnts_arr2(PntType(p), PntType(r), PntType(q));

	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr2::EEE:
		return dotProductSign2D<TP>(p, r, q);
	case PntArr2::EEI: // swap q due to EEI
		return dotProductSign2D_EEI<TP>(q, p, r);
	case PntArr2::EIE:
		return dotProductSign2D_IEE<TP>(r, p, q);
	case PntArr2::EII: // swap p and q due to IEI
		return dotProductSign2D_IEI<TP>(r, q, p);
	case PntArr2::IEE:
		return dotProductSign2D_IEE<TP>(p, r, q);
	case PntArr2::IEI: // swap r and q due to IEI
		return dotProductSign2D_IEI<TP>(p, q, r);
	case PntArr2::IIE:
		return dotProductSign2D_IIE<TP>(p, r, q);
	default: // PntArr2::III
		return dotProductSign2D_III<TP>(p, r, q);
	}
}

TEMPLATE_DECL
Sign DotProductSign2D_Indirect<FT, IT, ET>::operator()(const PointT &p,
                                                       const PointT &r,
                                                       const PointT &q,
                                                       const PointT &s)
{
	PntArr2 arr = get_pnts_arr2(PntType(p), PntType(r), PntType(q), PntType(s));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr2::EEEE:
		return dotProductSign2D4P<TP>(p, r, q, s);
	default:
		OMC_EXIT("DotProductSign2D4P - should not happen");
		return Sign::ZERO; // warning killer
	}
}

TEMPLATE_DECL
Sign DotProductSign3D_Indirect<FT, IT, ET>::operator()(const PointT &p,
                                                       const PointT &r,
                                                       const PointT &q)
{
	PntArr3 arr = get_pnts_arr3(PntType(p), PntType(r), PntType(q));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::EEE:
		return dotProductSign3D<TP>(p, r, q);
	case PntArr3::EEI: // swap q due to EEI
		return dotProductSign3D_EEI<TP>(q, p, r);
	case PntArr3::EIE:
		return dotProductSign3D_IEE<TP>(r, p, q);
	case PntArr3::EII: // swap q and p due to IEI
		return dotProductSign3D_IEI<TP>(r, q, p);
	case PntArr3::IEE:
		return dotProductSign3D_IEE<TP>(p, r, q);
	case PntArr3::IEI: // swap r and q due to IEI
		return dotProductSign3D_IEI<TP>(p, q, r);
	case PntArr3::IIE:
		return dotProductSign3D_IIE<TP>(p, r, q);
	default: // PntArr3::III
		return dotProductSign3D_III<TP>(p, r, q);
	}
}

TEMPLATE_DECL
Sign DotProductSign3D_Indirect<FT, IT, ET>::operator()(const PointT &p,
                                                       const PointT &r,
                                                       const PointT &q,
                                                       const PointT &s)
{
	PntArr3 arr = get_pnts_arr3(PntType(p), PntType(r), PntType(q), PntType(s));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::EEEE:
		return dotProductSign3D4P<TP>(p, r, q, s);
	default:
		OMC_EXIT("DotProductSign3D4P - should not happen");
		return Sign::ZERO; // warning killer
	}
}

TEMPLATE_DECL
Sign DotProductSignOn2D_Indirect<FT, IT, ET>::on_xy(const PointT &p,
                                                    const PointT &r,
                                                    const PointT &q)
{
	OMC_EXIT("DotProductSignOn2Dxy - should not happen");
	return Sign::ZERO; // warning killer
}

TEMPLATE_DECL
Sign DotProductSignOn2D_Indirect<FT, IT, ET>::on_xy(const PointT &p,
                                                    const PointT &r,
                                                    const PointT &q,
                                                    const PointT &s)
{
	PntArr3 arr = get_pnts_arr3(PntType(p), PntType(r), PntType(q), PntType(s));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::EEEE:
		return dotProductSignOn2Dxy4P<TP>(p, r, q, s);
	default:
		OMC_EXIT("DotProductSignOn2Dxy4P - should not happen");
		return Sign::ZERO; // warning killer
	}
}

TEMPLATE_DECL
Sign DotProductSignOn2D_Indirect<FT, IT, ET>::on_yz(const PointT &p,
                                                    const PointT &r,
                                                    const PointT &q)
{
	OMC_EXIT("DotProductSignOn2Dyz - should not happen");
	return Sign::ZERO; // warning killer
}

TEMPLATE_DECL
Sign DotProductSignOn2D_Indirect<FT, IT, ET>::on_yz(const PointT &p,
                                                    const PointT &r,
                                                    const PointT &q,
                                                    const PointT &s)
{
	PntArr3 arr = get_pnts_arr3(PntType(p), PntType(r), PntType(q), PntType(s));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::EEEE:
		return dotProductSignOn2Dyz4P<TP>(p, r, q, s);
	default:
		OMC_EXIT("DotProductSignOn2Dyz4P - should not happen");
		return Sign::ZERO; // warning killer
	}
}

TEMPLATE_DECL
Sign DotProductSignOn2D_Indirect<FT, IT, ET>::on_zx(const PointT &p,
                                                    const PointT &r,
                                                    const PointT &q)
{
	OMC_EXIT("DotProductSignOn2Dzx - should not happen");
	return Sign::ZERO; // warning killer
}

TEMPLATE_DECL
Sign DotProductSignOn2D_Indirect<FT, IT, ET>::on_zx(const PointT &p,
                                                    const PointT &r,
                                                    const PointT &q,
                                                    const PointT &s)
{
	PntArr3 arr = get_pnts_arr3(PntType(p), PntType(r), PntType(q), PntType(s));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::EEEE:
		return dotProductSignOn2Dzx4P<TP>(p, r, q, s);
	default:
		OMC_EXIT("DotProductSignOn2Dzx4P - should not happen");
		return Sign::ZERO; // warning killer
	}
}

/******************************************************************************/
/* Distance *******************************************************************/
/******************************************************************************/

TEMPLATE_DECL
Sign SquaredDistance2D_Indirect<FT, IT, ET>::operator()(const PointT &p,
                                                        const PointT &q,
                                                        FT            sqr_dis)
{
	PntArr2 arr = get_pnts_arr2(PntType(p), PntType(q));
	// SquaredDistance is simple now, expand it by hand.
	switch (arr)
	{
	case PntArr2::EE:
		return squaredDistance2D<TP>(p, q, sqr_dis);
	case PntArr2::EI:
		return squaredDistance2D_IE<TP>(q, p, sqr_dis);
	case PntArr2::IE:
		return squaredDistance2D_IE<TP>(p, q, sqr_dis);
	case PntArr2::II:
		return squaredDistance2D_II<TP>(q, p, sqr_dis);
	default:
		OMC_ASSERT(false, "SquaredDistance2D - should not happen");
		return Sign::ZERO; // warning killer
	}
}

TEMPLATE_DECL
Sign SquaredDistance3D_Indirect<FT, IT, ET>::operator()(const PointT &p,
                                                        const PointT &q,
                                                        FT            sqr_dis)
{
	PntArr3 arr = get_pnts_arr3(PntType(p), PntType(q));
	// SquaredDistance is simple now, expand it by hand.
	switch (arr)
	{
	case PntArr3::EE:
		return squaredDistance3D<TP>(p, q, sqr_dis);
	case PntArr3::EI:
		return squaredDistance3D_IE<TP>(q, p, sqr_dis);
	case PntArr3::IE:
		return squaredDistance3D_IE<TP>(p, q, sqr_dis);
	case PntArr3::II:
		return squaredDistance3D_II<TP>(q, p, sqr_dis);
	default:
		OMC_ASSERT(false, "SquaredDistance3D - should not happen");
		return Sign::ZERO; // warning killer
	}
}

TEMPLATE_DECL
Sign SquaredDistance3D_Indirect<FT, IT, ET>::operator()(const PointT &a,
                                                        const PointT &b,
                                                        const PointT &c,
                                                        int           ab_scale)
{
	if (a.is_explicit() && b.is_explicit() && c.is_explicit())
		return squaredDistance3D3p(a, b, c, ab_scale);

	OMC_ASSERT(false, "SquaredDistance3D3p - should not happen");
	return Sign::ZERO; // warning killer
}

TEMPLATE_DECL
Sign SquaredDistance3D_Indirect<FT, IT, ET>::operator()(const PointT &a,
                                                        const PointT &b,
                                                        const PointT &c,
                                                        FT sqr_dis)
{
	if (a.is_explicit() && b.is_explicit() && c.is_explicit())
		return squaredDistance3Dseg(a, b, c, sqr_dis);

	OMC_ASSERT(false, "SquaredDistance3Dseg - should not happen");
	return Sign::ZERO; // warning killer
}

/******************************************************************************/
/* Orientation ****************************************************************/
/******************************************************************************/

TEMPLATE_DECL
Sign Orient2D_Indirect<FT, IT, ET>::operator()(const PointT &p, const PointT &q,
                                               const PointT &query)
{
	PntArr2 arr = get_pnts_arr2(PntType(p), PntType(q), PntType(query));
	// Orient2D is simple now, expand it by hand.
	switch (arr)
	{
	case PntArr2::EEE:
		return orient2d<TP>(p, q, query);
	case PntArr2::EEI:
		return orient2D_IEE<TP>(query, p, q);
	case PntArr2::EIE:
		return orient2D_IEE<TP>(q, query, p);
	case PntArr2::IEE:
		return orient2D_IEE<TP>(p, q, query);
	case PntArr2::EII:
		return orient2D_IIE<TP>(q, query, p);
	case PntArr2::IEI:
		return orient2D_IIE<TP>(query, p, q);
	case PntArr2::IIE:
		return orient2D_IIE<TP>(p, q, query);
	case PntArr2::III:
		return orient2D_III<TP>(p, q, query);
	default:
		OMC_EXIT("Orient2D - should not happen");
	}
}

TEMPLATE_DECL
Sign Orient2D_Indirect<FT, IT, ET>::operator()(const FT *p, const FT *q,
                                               const FT *query)
{
	return orient2d(p, q, query);
}

TEMPLATE_DECL
Sign Orient3D_Indirect<FT, IT, ET>::operator()(const PointT &a, const PointT &b,
                                               const PointT &c, const PointT &d)
{
	// Here we implicitly assume that points are 3D. Do not check.
	// clang-format off
	int i = a.is_explicit() + b.is_explicit() + c.is_explicit() + d.is_explicit();

	if (i == 4) return orient3d<TP>(a, b, c, d);
	
	if (i == 3)
	{
		if (!a.is_explicit()) return orient3D_IEEE<TP>(a, b, c, d);
		if (!b.is_explicit()) return orient3D_IEEE<TP>(b, c, a, d);
		if (!c.is_explicit()) return orient3D_IEEE<TP>(c, d, a, b);
		/*if (!d.is_explicit())*/ return orient3D_IEEE<TP>(d, a, c, b);
	}
	else if (i == 2)
	{
		if (c.is_explicit() && d.is_explicit()) return orient3D_IIEE<TP>(a, b, c, d);
		if (b.is_explicit() && d.is_explicit()) return orient3D_IIEE<TP>(a, c, d, b);
		if (a.is_explicit() && d.is_explicit()) return orient3D_IIEE<TP>(b, c, a, d);
		if (b.is_explicit() && c.is_explicit()) return orient3D_IIEE<TP>(d, a, c, b);
		if (a.is_explicit() && c.is_explicit()) return orient3D_IIEE<TP>(d, b, a, c);
		/*if (a.is_explicit() && b.is_explicit())*/ return orient3D_IIEE<TP>(c, d, a, b);
	}
	else if (i == 1)
	{
		if (d.is_explicit()) return orient3D_IIIE<TP>(a, b, c, d);
		if (c.is_explicit()) return orient3D_IIIE<TP>(d, b, a, c);
		if (b.is_explicit()) return orient3D_IIIE<TP>(a, c, d, b);
		/*if (a.is_explicit())*/ return orient3D_IIIE<TP>(b, d, c, a);
	}
	else
	{
		return orient3D_IIII<TP>(a, b, c, d);
	}
	// clang-format on
}

TEMPLATE_DECL
Sign Orient3D_Indirect<FT, IT, ET>::operator()(const FT *a, const FT *b,
                                               const FT *c, const FT *d)
{
	return orient3d(a, b, c, d);
}

TEMPLATE_DECL
Sign Orient3D_Indirect<FT, IT, ET>::operator()(const FT *a, const FT *b,
                                               const FT *c, const PointT &d)
{
	if (d.is_explicit())
		return orient3d(a, b, c, d.data());
	else
		return orient3D_IEEE<TP>(d, a[0], a[1], a[2], c[0], c[1], c[2], b[0], b[1],
		                         b[2]);
}

TEMPLATE_DECL
void Orient3D_Indirect<FT, IT, ET>::get_minors(const FT *a, const FT *b,
                                               const FT *c, FT *minor, FT *perm)
{
	orient3d_get_minors(a, b, c, minor, perm);
}

TEMPLATE_DECL
Sign Orient3D_Indirect<FT, IT, ET>::with_cached_minors(
  const FT *pa, const FT *pb, const FT *pc, const FT *pd, const FT *minor,
  const FT *perm)
{
	return orient3d_with_cached_minors(pa, pb, pc, pd, minor, perm);
}

TEMPLATE_DECL
Sign Orient3D_Indirect<FT, IT, ET>::filter(const FT *a, const FT *b,
                                           const FT *c, const FT *d)
{
	return orient3d_filtered(a[0], a[1], a[2], b[0], b[1], b[2], c[0], c[1], c[2],
	                         d[0], d[1], d[2]);
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::operator()(const PointT &a,
                                                 const PointT &b,
                                                 const PointT &c, int n_max)
{
	if (n_max == 0)
		return on_yz(a, b, c);
	else if (n_max == 1)
		return on_zx(a, b, c);
	else
		return on_xy(a, b, c);
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::on_xy(const PointT &a, const PointT &b,
                                            const PointT &c)
{
	if (a.is_explicit() && b.is_explicit() && c.is_explicit())
		return orient2dxy<TP>(a, b, c);

	PntArr3 arr = get_pnts_arr3(PntType(a), PntType(b), PntType(c));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::IEE:
		return orientOn2Dxy_IEE<TP>(a, b, c);
	case PntArr3::EIE:
		return orientOn2Dxy_IEE<TP>(b, c, a);
	case PntArr3::EEI:
		return orientOn2Dxy_IEE<TP>(c, a, b);
	case PntArr3::IIE:
		return orientOn2Dxy_IIE<TP>(a, b, c);
	case PntArr3::IEI:
		return orientOn2Dxy_IIE<TP>(c, a, b);
	case PntArr3::EII:
		return orientOn2Dxy_IIE<TP>(b, c, a);
	default: // PntArr3::III
		return orientOn2Dxy_III<TP>(a, b, c);
	}
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::on_yz(const PointT &a, const PointT &b,
                                            const PointT &c)
{
	if (a.is_explicit() && b.is_explicit() && c.is_explicit())
		return orient2dyz<TP>(a, b, c);

	PntArr3 arr = get_pnts_arr3(PntType(a), PntType(b), PntType(c));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::IEE:
		return orientOn2Dyz_IEE<TP>(a, b, c);
	case PntArr3::EIE:
		return orientOn2Dyz_IEE<TP>(b, c, a);
	case PntArr3::EEI:
		return orientOn2Dyz_IEE<TP>(c, a, b);
	case PntArr3::IIE:
		return orientOn2Dyz_IIE<TP>(a, b, c);
	case PntArr3::IEI:
		return orientOn2Dyz_IIE<TP>(c, a, b);
	case PntArr3::EII:
		return orientOn2Dyz_IIE<TP>(b, c, a);
	default: // PntArr3::III
		return orientOn2Dyz_III<TP>(a, b, c);
	}
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::on_zx(const PointT &a, const PointT &b,
                                            const PointT &c)
{
	if (a.is_explicit() && b.is_explicit() && c.is_explicit())
		return orient2dzx<TP>(a, b, c);

	PntArr3 arr = get_pnts_arr3(PntType(a), PntType(b), PntType(c));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::IEE:
		return orientOn2Dzx_IEE<TP>(a, b, c);
	case PntArr3::EIE:
		return orientOn2Dzx_IEE<TP>(b, c, a);
	case PntArr3::EEI:
		return orientOn2Dzx_IEE<TP>(c, a, b);
	case PntArr3::IIE:
		return orientOn2Dzx_IIE<TP>(a, b, c);
	case PntArr3::IEI:
		return orientOn2Dzx_IIE<TP>(c, a, b);
	case PntArr3::EII:
		return orientOn2Dzx_IIE<TP>(b, c, a);
	default: // PntArr3::III
		return orientOn2Dzx_III<TP>(a, b, c);
	}
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::operator()(const FT *a, const FT *b,
                                                 const PointT &c, int n_max)
{
	if (c.is_explicit())
		return operator()(a, b, c.data(), n_max);

	if (n_max == 0) // yz
		return orientOn2Dyz_IEE<TP>(c, a[1], a[2], b[1], b[2]);
	else if (n_max == 1) // zx
		return orientOn2Dzx_IEE<TP>(c, a[0], a[2], b[0], b[2]);
	else // xy
		return orientOn2Dxy_IEE<TP>(c, a[0], a[1], b[0], b[1]);
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::operator()(const FT *a, const FT *b,
                                                 const FT *c, int n_max)
{
	if (n_max == 0)
		return on_yz(a, b, c);
	else if (n_max == 1)
		return on_zx(a, b, c);
	else
		return on_xy(a, b, c);
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::on_xy(const FT *a, const FT *b,
                                            const FT *c)
{
	return orient2dxy(a, b, c);
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::on_yz(const FT *a, const FT *b,
                                            const FT *c)
{
	return orient2dyz(a, b, c);
}

TEMPLATE_DECL
Sign OrientOn2D_Indirect<FT, IT, ET>::on_zx(const FT *a, const FT *b,
                                            const FT *c)
{
	return orient2dzx(a, b, c);
}

/******************************************************************************/
/* Less Than ******************************************************************/
/******************************************************************************/

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_x(const PointT &a, const PointT &b)
{
	if (a.is_explicit() && b.is_explicit())
		return static_cast<Sign>(((a.x() > b.x()) - (a.x() < b.x())));

	// cases are simple, expand them by hand.
	if (!a.is_explicit() && b.is_explicit())
		return lessThanOnX_IE<TP>(a, b);
	if (a.is_explicit() && !b.is_explicit())
		return reverse_sign(lessThanOnX_IE<TP>(b, a));
	return lessThanOnX_II<TP>(a, b);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_y(const PointT &a, const PointT &b)
{
	if (a.is_explicit() && b.is_explicit())
		return static_cast<Sign>(((a.y() > b.y()) - (a.y() < b.y())));

	// cases are simple, expand them by hand.
	if (!a.is_explicit() && b.is_explicit())
		return lessThanOnY_IE<TP>(a, b);
	if (a.is_explicit() && !b.is_explicit())
		return reverse_sign(lessThanOnY_IE<TP>(b, a));
	return lessThanOnY_II<TP>(a, b);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_z(const PointT &a, const PointT &b)
{
	if (a.is_explicit() && b.is_explicit())
		return static_cast<Sign>(((a.z() > b.z()) - (a.z() < b.z())));

	if (!a.is_explicit() && b.is_explicit())
		return lessThanOnZ_IE<TP>(a, b);
	if (a.is_explicit() && !b.is_explicit())
		return reverse_sign(lessThanOnZ_IE<TP>(b, a));
	return lessThanOnZ_II<TP>(a, b);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on(const PointT &a, const PointT &b,
                                         size_t axis)
{
	if (axis == 0)
		return on_x(a, b);
	if (axis == 1)
		return on_y(a, b);
	if (axis == 2)
		return on_z(a, b);
	OMC_EXIT("should not happen");
}

TEMPLATE_DECL
std::array<Sign, 3> LessThan3D_Indirect<FT, IT, ET>::on_all(const PointT &a,
                                                            const PointT &b)
{
	if (a.is_explicit() && b.is_explicit())
		return lessThanOnAll_EE(a.x(), a.y(), a.z(), b.x(), b.y(), b.z());

	if (!a.is_explicit() && b.is_explicit())
		return lessThanOnAll_IE<TP>(a, b);
	if (a.is_explicit() && !b.is_explicit())
		return reverse_signs(lessThanOnAll_IE<TP>(b, a));
	return lessThanOnAll_II<TP>(a, b);

	OMC_EXIT("LessThan3D - should not happen");
	return std::array<Sign, 3>{Sign::ZERO, Sign::ZERO, Sign::ZERO};
	// warning killer
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_x(const PointT &a, const FT *b)
{
	return on_x(a, b[0]);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_y(const PointT &a, const FT *b)
{
	return on_y(a, b[1]);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_z(const PointT &a, const FT *b)
{
	return on_z(a, b[2]);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on(const PointT &a, const FT *b,
                                         size_t axis)
{
	return on(a, b[axis], axis);
}

TEMPLATE_DECL
std::array<Sign, 3> LessThan3D_Indirect<FT, IT, ET>::on_all(const PointT &a,
                                                            const FT     *b)
{
	if (a.is_explicit())
		return lessThanOnAll_EE(a.x(), a.y(), a.z(), b[0], b[1], b[2]);
	else
		return lessThanOnAll_IE<TP>(a, b[0], b[1], b[2]);

	OMC_EXIT("LessThan3D - should not happen");
	return std::array<Sign, 3>{Sign::ZERO, Sign::ZERO, Sign::ZERO};
	// warning killer
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_x(const PointT &a, const FT b)
{
	if (a.is_explicit())
		return static_cast<Sign>(((a.x() > b) - (a.x() < b)));
	else
		return lessThanOnX_IE<TP>(a, b);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_y(const PointT &a, const FT b)
{
	if (a.is_explicit())
		return static_cast<Sign>(((a.y() > b) - (a.y() < b)));
	else
		return lessThanOnY_IE<TP>(a, b);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on_z(const PointT &a, const FT b)
{
	if (a.is_explicit())
		return static_cast<Sign>(((a.z() > b) - (a.z() < b)));
	else
		return lessThanOnZ_IE<TP>(a, b);
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::on(const PointT &a, const FT b,
                                         size_t axis)
{
	if (axis == 0)
		return on_x(a, b);
	if (axis == 1)
		return on_y(a, b);
	if (axis == 2)
		return on_z(a, b);

	OMC_EXIT("LessThan3D - should not happen");
}

TEMPLATE_DECL
Sign LessThan3D_Indirect<FT, IT, ET>::operator()(const PointT &a,
                                                 const PointT &b)
{
	if (a.is_explicit() && b.is_explicit())
		return lessThan_EE<TP>(a, b);

	// cases are simple, expand them by hand.
	if (!a.is_explicit() && b.is_explicit())
		return lessThan_IE<TP>(a, b);
	if (a.is_explicit() && !b.is_explicit())
		return reverse_sign(lessThan_IE<TP>(b, a));
	return lessThan_II<TP>(a, b);
}

/******************************************************************************/
/* Triangle Normal & Segment Axis *********************************************/
/******************************************************************************/

TEMPLATE_DECL
int MaxComponentInTriangleNormal<FT, IT, ET>::operator()(FT ov1x, FT ov1y,
                                                         FT ov1z, FT ov2x,
                                                         FT ov2y, FT ov2z,
                                                         FT ov3x, FT ov3y,
                                                         FT ov3z)
{
	return maxComponentInTriangleNormal(ov1x, ov1y, ov1z, ov2x, ov2y, ov2z, ov3x,
	                                    ov3y, ov3z);
}

TEMPLATE_DECL
int LongestAxis_Indirect<FT, IT, ET>::operator()(const PointT &a,
                                                 const PointT &b)
{
	if (a.is_explicit() && b.is_explicit())
	{
		double diff_x = fabs(a.x() - b.x());
		double diff_y = fabs(a.y() - b.y());
		double diff_z = fabs(a.z() - b.z());
		return diff_y > diff_x ? (diff_z > diff_y ? 2 : 1)
		                       : (diff_z > diff_x ? 2 : 0);
	}

	// cases are simple, expand them by hand.
	if (!a.is_explicit() && b.is_explicit())
		return longestAxis_IE<TP>(a, b);
	if (a.is_explicit() && !b.is_explicit())
		return longestAxis_IE<TP>(b, a);
	return longestAxis_II<TP>(a, b);
}

/******************************************************************************/
/* Circle & Sphere ************************************************************/
/******************************************************************************/

TEMPLATE_DECL
Sign InCircle_Indirect<FT, IT, ET>::operator()(const PointT &a, const PointT &b,
                                               const PointT &c, const PointT &d)
{
	int i = a.is_explicit() + b.is_explicit() + c.is_explicit() + d.is_explicit();
	// InCircle is simple now, expand it by hand.
	if (i == 4)
		return inCircle<TP>(a, b, c, d);
	if (i == 3)
	{
		if (!a.is_explicit())
			return inCircle_IEEE<TP>(a, b, c, d);
		if (!b.is_explicit())
			return inCircle_IEEE<TP>(b, c, a, d);
		if (!c.is_explicit())
			return inCircle_IEEE<TP>(c, d, a, b);
		return inCircle_IEEE<TP>(d, a, c, b);
	}
	if (i == 2)
	{
		if (c.is_explicit() && d.is_explicit())
			return inCircle_IIEE<TP>(a, b, c, d);
		if (b.is_explicit() && d.is_explicit())
			return inCircle_IIEE<TP>(a, c, d, b);
		if (a.is_explicit() && d.is_explicit())
			return inCircle_IIEE<TP>(b, c, a, d);
		if (b.is_explicit() && c.is_explicit())
			return inCircle_IIEE<TP>(d, a, c, b);
		if (a.is_explicit() && c.is_explicit())
			return inCircle_IIEE<TP>(d, b, a, c);
		return inCircle_IIEE<TP>(c, d, a, b);
	}
	if (i == 1)
	{
		if (d.is_explicit())
			return inCircle_IIIE<TP>(a, b, c, d);
		if (c.is_explicit())
			return inCircle_IIIE<TP>(d, b, a, c);
		if (b.is_explicit())
			return inCircle_IIIE<TP>(a, c, d, b);
		return inCircle_IIIE<TP>(b, d, c, a);
	}
	return inCircle_IIII<TP>(a, b, c, d);
}

TEMPLATE_DECL
Sign InCircle_Indirect<FT, IT, ET>::operator()(const FT *a, const FT *b,
                                               const FT *c, const FT *d)
{
	return inCircle(a, b, c, d);
}

TEMPLATE_DECL
Sign InSphere_Indirect<FT, IT, ET>::operator()(const PointT &a, const PointT &b,
                                               const PointT &c, const PointT &d,
                                               const PointT &e)
{
	const int num_explicit = a.is_explicit() + b.is_explicit() + c.is_explicit() +
	                         d.is_explicit() + e.is_explicit();
	if (num_explicit == 5)
		return inSphere<TP>(a, b, c, d, e);

	// clang-format off
	std::array<uint32_t, 5> pos{0, 1, 2, 3, 4},
	  types{static_cast<uint32_t>(a.is_explicit() ? PointT::PointType::Explicit : PointT::PointType::Implicit),
	        static_cast<uint32_t>(b.is_explicit() ? PointT::PointType::Explicit : PointT::PointType::Implicit),
	        static_cast<uint32_t>(c.is_explicit() ? PointT::PointType::Explicit : PointT::PointType::Implicit),
	        static_cast<uint32_t>(d.is_explicit() ? PointT::PointType::Explicit : PointT::PointType::Implicit),
	        static_cast<uint32_t>(e.is_explicit() ? PointT::PointType::Explicit : PointT::PointType::Implicit)};
	uint32_t swap_cnt;
	sort_pnts_arr3(types, pos, swap_cnt);
	const PointT *A[5] = {&a, &b, &c, &d, &e};
	Sign sign;
	if (num_explicit == 4) sign = inSphere_IEEEE<TP>(*A[pos[0]], *A[pos[1]], *A[pos[2]], *A[pos[3]], *A[pos[4]]);
	else if (num_explicit == 3) sign = inSphere_IIEEE<TP>(*A[pos[0]], *A[pos[1]], *A[pos[2]], *A[pos[3]], *A[pos[4]]);
	else if (num_explicit == 2) sign = inSphere_IIIEE<TP>(*A[pos[0]], *A[pos[1]], *A[pos[2]], *A[pos[3]], *A[pos[4]]);
	else if (num_explicit == 1) sign = inSphere_IIIIE<TP>(*A[pos[0]], *A[pos[1]], *A[pos[2]], *A[pos[3]], *A[pos[4]]);
	else sign = inSphere_IIIII<TP>(*A[pos[0]], *A[pos[1]], *A[pos[2]], *A[pos[3]], *A[pos[4]]);
	// clang-format on
	return swap_cnt % 2 == 1 ? reverse_sign(sign) : sign;
}

TEMPLATE_DECL
Sign InSphere_Indirect<FT, IT, ET>::operator()(const FT *a, const FT *b,
                                               const FT *c, const FT *d,
                                               const FT *e)
{
	return inSphere<TP>(a, b, c, d, e);
}

TEMPLATE_DECL
Sign InSphere_Indirect<FT, IT, ET>::operator()(const PointT &a, const PointT &b,
                                               const PointT &c)
{
	PntArr3 arr = get_pnts_arr3(PntType(a), PntType(b), PntType(c));
	// cases are simple, expand them by hand.
	switch (arr)
	{
	case PntArr3::EEE:
		return inSphere3p<TP>(a, b, c);
	case PntArr3::EEI: // swap c due to EEI
		return inSphere3p_EEI<TP>(c, a, b);
	case PntArr3::EIE:
		return inSphere3p_IEE<TP>(b, a, c);
	case PntArr3::EII: // swap a and c due to IEI
		return inSphere3p_IEI<TP>(b, c, a);
	case PntArr3::IEE:
		return inSphere3p_IEE<TP>(a, b, c);
	case PntArr3::IEI: // swap b and c due to IEI
		return inSphere3p_IEI<TP>(a, c, b);
	case PntArr3::IIE:
		return inSphere3p_IIE<TP>(a, b, c);
	default: // PntArr3::III
		return inSphere3p_III<TP>(a, b, c);
	}
}

TEMPLATE_DECL
Sign InSphere_Indirect<FT, IT, ET>::largerSphere(const PointT &a,
                                                 const PointT &b,
                                                 const PointT &c,
                                                 const PointT &d)
{
	if (a.is_explicit() && b.is_explicit() && c.is_explicit() && d.is_explicit())
		return largerSphere3p(a, b, c, d);

	OMC_ASSERT(false, "largerSphere - should not happen");
	return Sign::ZERO; // warning killer
}

#undef TEMPLATE_TYPE
#undef TP
#undef PntType

} // namespace OMC