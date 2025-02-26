#pragma once

#include "Orient2D.inl"
#include "Shewchuk.h"

#include "OpenMeshCraft/Geometry/Predicates/IndirectDefinitions.h"

#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"
#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"
#include "OpenMeshCraft/NumberTypes/LazyNumber.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
#define CHECK_FOR_XYZERFLOWS

namespace OMC {

/*********************************************************************/
/* Forward Declarations (hand)****************************************/
/*********************************************************************/

/* On explicit points ************************************************/

inline Sign orient2dxy(double p1x, double p1y, double p2x, double p2y,
                       double p3x, double p3y);

inline Sign orient2dxy(const double *p1, const double *p2, const double *p3);

template <typename IT, typename ET>
Sign orient2dxy(const GenericPoint3T<IT, ET> &p1,
                const GenericPoint3T<IT, ET> &p2,
                const GenericPoint3T<IT, ET> &p3);

inline Sign orient2dyz(double p1y, double p1z, double p2y, double p2z,
                       double p3y, double p3z);

inline Sign orient2dyz(const double *p1, const double *p2, const double *p3);

template <typename IT, typename ET>
Sign orient2dyz(const GenericPoint3T<IT, ET> &p1,
                const GenericPoint3T<IT, ET> &p2,
                const GenericPoint3T<IT, ET> &p3);

inline Sign orient2dzx(double p1x, double p1z, double p2x, double p2z,
                       double p3x, double p3z);

inline Sign orient2dzx(const double *p1, const double *p2, const double *p3);

template <typename IT, typename ET>
Sign orient2dzx(const GenericPoint3T<IT, ET> &p1,
                const GenericPoint3T<IT, ET> &p2,
                const GenericPoint3T<IT, ET> &p3);

/* OrienOn2D xy/yz/zx  IIE/III ****************************************/

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2, double op3x,
                                double op3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_III_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2,
                                const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2, double op3y,
                                double op3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_III_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2,
                                const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2, double op3x,
                                double op3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_III_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2,
                                const GenericPoint3T<IT, ET> &p3);

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2x, IT p2y,
                               IT p3x, IT p3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2x, ET p2y,
                            ET p3x, ET p3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2x,
                                double p2y, double p3x, double p3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE(const GenericPoint3T<IT, ET> &p1, double p2x, double p2y,
                      double p3x, double p3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, IT op3x,
                               IT op3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, ET op3x, ET op3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2, double op3x,
                      double op3y);

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &op3);

template <typename IT, typename ET>
Sign orientOn2Dxy_III_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dxy_III_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dxy_III(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2y, IT p2z,
                               IT p3y, IT p3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2y, ET p2z,
                            ET p3y, ET p3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2y,
                                double p2z, double p3y, double p3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE(const GenericPoint3T<IT, ET> &p1, double p2y, double p2z,
                      double p3y, double p3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, IT op3y,
                               IT op3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, ET op3y, ET op3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2, double op3y,
                      double op3z);

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &op3);

template <typename IT, typename ET>
Sign orientOn2Dyz_III_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dyz_III_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dyz_III(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2x, IT p2z,
                               IT p3x, IT p3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2x, ET p2z,
                            ET p3x, ET p3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2x,
                                double p2z, double p3x, double p3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE(const GenericPoint3T<IT, ET> &p1, double p2x, double p2z,
                      double p3x, double p3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, IT op3x,
                               IT op3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, ET op3x, ET op3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2, double op3x,
                      double op3z);

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &op3);

template <typename IT, typename ET>
Sign orientOn2Dzx_III_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dzx_III_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orientOn2Dzx_III(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline Sign orient2dxy(double p1x, double p1y, double p2x, double p2y,
                       double p3x, double p3y)
{
	Sign ret;
	ret = orient2d_filtered(p1x, p1y, p2x, p2y, p3x, p3y);
	if (is_sign_reliable(ret))
		return ret;
	return orient2d_expansion(p1x, p1y, p2x, p2y, p3x, p3y);
}

inline Sign orient2dxy(const double *p1, const double *p2, const double *p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2d(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);
#else
	return OMC::sign(::orient2d(p1, p2, p3));
#endif
}

template <typename IT, typename ET>
Sign orient2dxy(const GenericPoint3T<IT, ET> &p1,
                const GenericPoint3T<IT, ET> &p2,
                const GenericPoint3T<IT, ET> &p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2dxy(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
#else
	return OMC::sign(::orient2d(p1.data(), p2.data(), p3.data()));
#endif
}

Sign orient2dyz(double p1y, double p1z, double p2y, double p2z, double p3y,
                double p3z)
{
	Sign ret;
	ret = orient2d_filtered(p1y, p1z, p2y, p2z, p3y, p3z);
	if (is_sign_reliable(ret))
		return ret;
	return orient2d_expansion(p1y, p1z, p2y, p2z, p3y, p3z);
}

inline Sign orient2dyz(const double *p1, const double *p2, const double *p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2dyz(p1[1], p1[2], p2[1], p2[2], p3[1], p3[2]);
#else
	return OMC::sign(::orient2d(p1 + 1, p2 + 1, p3 + 1));
#endif
}

template <typename IT, typename ET>
Sign orient2dyz(const GenericPoint3T<IT, ET> &p1,
                const GenericPoint3T<IT, ET> &p2,
                const GenericPoint3T<IT, ET> &p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2dyz(p1.y(), p1.z(), p2.y(), p2.z(), p3.y(), p3.z());
#else
	return OMC::sign(::orient2d(p1.data() + 1, p2.data() + 1, p3.data() + 1));
#endif
}

Sign orient2dzx(double p1x, double p1z, double p2x, double p2z, double p3x,
                double p3z)
{
	Sign ret;
	ret = orient2d_filtered(p1z, p1x, p2z, p2x, p3z, p3x);
	if (is_sign_reliable(ret))
		return ret;
	return orient2d_expansion(p1z, p1x, p2z, p2x, p3z, p3x);
}

inline Sign orient2dzx(const double *p1, const double *p2, const double *p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2dzx(p1[0], p1[2], p2[0], p2[2], p3[0], p3[2]);
#else
	double _p1[2] = {p1[2], p1[0]};
	double _p2[2] = {p2[2], p2[0]};
	double _p3[2] = {p3[2], p3[0]};
	return OMC::sign(::orient2d(_p1, _p2, _p3));
#endif
}

template <typename IT, typename ET>
Sign orient2dzx(const GenericPoint3T<IT, ET> &p1,
                const GenericPoint3T<IT, ET> &p2,
                const GenericPoint3T<IT, ET> &p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2dzx(p1.x(), p1.z(), p2.x(), p2.z(), p3.x(), p3.z());
#else
	double _p1[2] = {p1[2], p1[0]};
	double _p2[2] = {p2[2], p2[0]};
	double _p3[2] = {p3[2], p3[0]};
	return OMC::sign(::orient2d(_p1, _p2, _p3));
#endif
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2, double op3x,
                                double op3y)
{
	Sign return_sign = Sign::UNCERTAIN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p, l2x_p[64], *l2x = l2x_p,
	                  l2y_p[64], *l2y = l2y_p, l2z_p[64], *l2z = l2z_p, d2_p[64],
	                  *d2 = d2_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64, l2x_len = 64,
	    l2y_len = 64, l2z_len = 64, d2_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &b, 64);
		double c_p[64], *c = c_p;
		int    c_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, op3y, &c, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &f, 64);
		double g_p[64], *g = g_p;
		int    g_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, op3x, &g, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, l1y_len, l1y, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, l1x_len, l1x, &gh, 64);

#ifdef OMC_COMPRESS_EXPANSION
		o.CompressIf(ab_len, ab);
		o.CompressIf(cd_len, cd);
		o.CompressIf(ef_len, ef);
		o.CompressIf(gh_len, gh);
#endif

		double abcd_p[64], *abcd = abcd_p;
		double efgh_p[64], *efgh = efgh_p;
		double L_p[64], *L       = L_p;
		int    abcd_len, efgh_len, L_len;

#ifdef OMC_LIMIT_EXPANSION_LENGTH
		if (ab_len * cd_len <= OMC_EXPANSION_LENGTH_THRES &&
		    ef_len * gh_len <= OMC_EXPANSION_LENGTH_THRES)
#endif
		{
			abcd_len = o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
			efgh_len = o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
			L_len = o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);
			double return_value = L[L_len - 1];
			if (return_value > 0)
				return_sign = Sign::POSITIVE;
			if (return_value < 0)
				return_sign = Sign::NEGATIVE;
			if (return_value == 0)
				return_sign = Sign::ZERO;
		}
#ifdef OMC_LIMIT_EXPANSION_LENGTH
		else if (ab_len <= OMC_SUM_LENGTH_THRES && cd_len <= OMC_SUM_LENGTH_THRES &&
		         ef_len <= OMC_SUM_LENGTH_THRES && gh_len <= OMC_SUM_LENGTH_THRES)
		{
			ET ab_et = 0, cd_et = 0, ef_et = 0, gh_et = 0;
			// clang-format off
			for (int i = 0; i < ab_len; i++) ab_et += ab[i];
			for (int i = 0; i < cd_len; i++) cd_et += cd[i];
			for (int i = 0; i < ef_len; i++) ef_et += ef[i];
			for (int i = 0; i < gh_len; i++) gh_et += gh[i];
			// clang-format on
			ET abcd_et  = ab_et * cd_et;
			ET efgh_et  = ef_et * gh_et;
			ET L_et     = abcd_et - efgh_et;
			return_sign = OMC::sign(L_et);
		}
		else
		{
			return_sign = orientOn2Dxy_IIE_exact<IT, ET>(p1, p2, op3x, op3y);
		}
#endif

		if (L_p != L)
			FreeDoubles(L);
		if (efgh_p != efgh)
			FreeDoubles(efgh);
		if (abcd_p != abcd)
			FreeDoubles(abcd);
		if (gh_p != gh)
			FreeDoubles(gh);
		if (ef_p != ef)
			FreeDoubles(ef);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (g_p != g)
			FreeDoubles(g);
		if (f_p != f)
			FreeDoubles(f);
		if (e_p != e)
			FreeDoubles(e);
		if (c_p != c)
			FreeDoubles(c);
		if (b_p != b)
			FreeDoubles(b);
		if (a_p != a)
			FreeDoubles(a);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dxy_IIE_exact<IT, ET>(p1, p2, op3x, op3y);
#endif

	return return_sign;
}

template <typename IT, typename ET>
Sign orientOn2Dxy_III_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2,
                                const GenericPoint3T<IT, ET> &p3)
{
	Sign return_sign = Sign::UNCERTAIN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p, l2x_p[64], *l2x = l2x_p,
	                  l2y_p[64], *l2y = l2y_p, l2z_p[64], *l2z = l2z_p, d2_p[64],
	                  *d2 = d2_p, l3x_p[64], *l3x = l3x_p, l3y_p[64],
	                  *l3y = l3y_p, l3z_p[64], *l3z = l3z_p, d3_p[64], *d3 = d3_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64, l2x_len = 64,
	    l2y_len = 64, l2z_len = 64, d2_len = 64, l3x_len = 64, l3y_len = 64,
	    l3z_len = 64, d3_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &b, 64);
		double c_p[64], *c = c_p;
		int c_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l3y_len, l3y, &c, 64);
		double d_p[64], *d = d_p;
		int d_len = o.Gen_Product_With_PreAlloc(d3_len, d3, l1y_len, l1y, &d, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &f, 64);
		double g_p[64], *g = g_p;
		int g_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l3x_len, l3x, &g, 64);
		double h_p[64], *h = h_p;
		int h_len = o.Gen_Product_With_PreAlloc(d3_len, d3, l1x_len, l1x, &h, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, d_len, d, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, h_len, h, &gh, 64);

		double abcd_p[64], *abcd = abcd_p;
		double efgh_p[64], *efgh = efgh_p;
		double L_p[64], *L       = L_p;
		int    abcd_len, efgh_len, L_len;

#ifdef OMC_COMPRESS_EXPANSION
		o.CompressIf(ab_len, ab);
		o.CompressIf(cd_len, cd);
		o.CompressIf(ef_len, ef);
		o.CompressIf(gh_len, gh);
#endif

		// clang-format off
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, ab_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, cd_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, ef_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, gh_len);
		// clang-format on

#ifdef OMC_LIMIT_EXPANSION_LENGTH
		if (ab_len * cd_len <= OMC_EXPANSION_LENGTH_THRES &&
		    ef_len * gh_len <= OMC_EXPANSION_LENGTH_THRES)
#endif
		{
			abcd_len = o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
			efgh_len = o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
			L_len = o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);
			double return_value = L[L_len - 1];
			if (return_value > 0)
				return_sign = Sign::POSITIVE;
			if (return_value < 0)
				return_sign = Sign::NEGATIVE;
			if (return_value == 0)
				return_sign = Sign::ZERO;
		}
#ifdef OMC_LIMIT_EXPANSION_LENGTH
		else if (ab_len <= OMC_SUM_LENGTH_THRES && cd_len <= OMC_SUM_LENGTH_THRES &&
		         ef_len <= OMC_SUM_LENGTH_THRES && gh_len <= OMC_SUM_LENGTH_THRES)
		{
			ET ab_et = 0, cd_et = 0, ef_et = 0, gh_et = 0;
			// clang-format off
			for (int i = 0; i < ab_len; i++) ab_et += ab[i];
			for (int i = 0; i < cd_len; i++) cd_et += cd[i];
			for (int i = 0; i < ef_len; i++) ef_et += ef[i];
			for (int i = 0; i < gh_len; i++) gh_et += gh[i];
			// clang-format on
			ET abcd_et  = ab_et * cd_et;
			ET efgh_et  = ef_et * gh_et;
			ET L_et     = abcd_et - efgh_et;
			return_sign = OMC::sign(L_et);
		}
		else
		{
			return_sign = orientOn2Dxy_III_exact<IT, ET>(p1, p2, p3);
		}
#endif

		if (L_p != L)
			FreeDoubles(L);
		if (efgh_p != efgh)
			FreeDoubles(efgh);
		if (abcd_p != abcd)
			FreeDoubles(abcd);
		if (gh_p != gh)
			FreeDoubles(gh);
		if (ef_p != ef)
			FreeDoubles(ef);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (h_p != h)
			FreeDoubles(h);
		if (g_p != g)
			FreeDoubles(g);
		if (f_p != f)
			FreeDoubles(f);
		if (e_p != e)
			FreeDoubles(e);
		if (d_p != d)
			FreeDoubles(d);
		if (c_p != c)
			FreeDoubles(c);
		if (b_p != b)
			FreeDoubles(b);
		if (a_p != a)
			FreeDoubles(a);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dxy_III_exact<IT, ET>(p1, p2, p3);
#endif

	return return_sign;
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2, double op3y,
                                double op3z)
{
	Sign return_sign = Sign::UNCERTAIN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p, l2x_p[64], *l2x = l2x_p,
	                  l2y_p[64], *l2y = l2y_p, l2z_p[64], *l2z = l2z_p, d2_p[64],
	                  *d2 = d2_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64, l2x_len = 64,
	    l2y_len = 64, l2z_len = 64, d2_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &b, 64);
		double c_p[64], *c = c_p;
		int    c_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, op3z, &c, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2z_len, l2z, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1z_len, l1z, &f, 64);
		double g_p[64], *g = g_p;
		int    g_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, op3y, &g, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, l1z_len, l1z, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, l1y_len, l1y, &gh, 64);

#ifdef OMC_COMPRESS_EXPANSION
		o.CompressIf(ab_len, ab);
		o.CompressIf(cd_len, cd);
		o.CompressIf(ef_len, ef);
		o.CompressIf(gh_len, gh);
#endif

		double abcd_p[64], *abcd = abcd_p;
		double efgh_p[64], *efgh = efgh_p;
		double L_p[64], *L       = L_p;
		int    abcd_len, efgh_len, L_len;

#ifdef OMC_LIMIT_EXPANSION_LENGTH
		if (ab_len * cd_len <= OMC_EXPANSION_LENGTH_THRES &&
		    ef_len * gh_len <= OMC_EXPANSION_LENGTH_THRES)
#endif
		{
			abcd_len = o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
			efgh_len = o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
			L_len = o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);
			double return_value = L[L_len - 1];
			if (return_value > 0)
				return_sign = Sign::POSITIVE;
			if (return_value < 0)
				return_sign = Sign::NEGATIVE;
			if (return_value == 0)
				return_sign = Sign::ZERO;
		}
#ifdef OMC_LIMIT_EXPANSION_LENGTH
		else if (ab_len <= OMC_SUM_LENGTH_THRES && cd_len <= OMC_SUM_LENGTH_THRES &&
		         ef_len <= OMC_SUM_LENGTH_THRES && gh_len <= OMC_SUM_LENGTH_THRES)
		{
			ET ab_et = 0, cd_et = 0, ef_et = 0, gh_et = 0;
			// clang-format off
			for (int i = 0; i < ab_len; i++) ab_et += ab[i];
			for (int i = 0; i < cd_len; i++) cd_et += cd[i];
			for (int i = 0; i < ef_len; i++) ef_et += ef[i];
			for (int i = 0; i < gh_len; i++) gh_et += gh[i];
			// clang-format on
			ET abcd_et  = ab_et * cd_et;
			ET efgh_et  = ef_et * gh_et;
			ET L_et     = abcd_et - efgh_et;
			return_sign = OMC::sign(L_et);
		}
		else
		{
			return_sign = orientOn2Dyz_IIE_exact<IT, ET>(p1, p2, op3y, op3z);
		}
#endif

		if (L_p != L)
			FreeDoubles(L);
		if (efgh_p != efgh)
			FreeDoubles(efgh);
		if (abcd_p != abcd)
			FreeDoubles(abcd);
		if (gh_p != gh)
			FreeDoubles(gh);
		if (ef_p != ef)
			FreeDoubles(ef);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (g_p != g)
			FreeDoubles(g);
		if (f_p != f)
			FreeDoubles(f);
		if (e_p != e)
			FreeDoubles(e);
		if (c_p != c)
			FreeDoubles(c);
		if (b_p != b)
			FreeDoubles(b);
		if (a_p != a)
			FreeDoubles(a);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dyz_IIE_exact<IT, ET>(p1, p2, op3y, op3z);
#endif

	return return_sign;
}

template <typename IT, typename ET>
Sign orientOn2Dyz_III_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2,
                                const GenericPoint3T<IT, ET> &p3)
{
	Sign return_sign = Sign::UNCERTAIN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p, l2x_p[64], *l2x = l2x_p,
	                  l2y_p[64], *l2y = l2y_p, l2z_p[64], *l2z = l2z_p, d2_p[64],
	                  *d2 = d2_p, l3x_p[64], *l3x = l3x_p, l3y_p[64],
	                  *l3y = l3y_p, l3z_p[64], *l3z = l3z_p, d3_p[64], *d3 = d3_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64, l2x_len = 64,
	    l2y_len = 64, l2z_len = 64, d2_len = 64, l3x_len = 64, l3y_len = 64,
	    l3z_len = 64, d3_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &b, 64);
		double c_p[64], *c = c_p;
		int c_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l3z_len, l3z, &c, 64);
		double d_p[64], *d = d_p;
		int d_len = o.Gen_Product_With_PreAlloc(d3_len, d3, l1z_len, l1z, &d, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2z_len, l2z, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1z_len, l1z, &f, 64);
		double g_p[64], *g = g_p;
		int g_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l3y_len, l3y, &g, 64);
		double h_p[64], *h = h_p;
		int h_len = o.Gen_Product_With_PreAlloc(d3_len, d3, l1y_len, l1y, &h, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, d_len, d, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, h_len, h, &gh, 64);

#ifdef OMC_COMPRESS_EXPANSION
		o.CompressIf(ab_len, ab);
		o.CompressIf(cd_len, cd);
		o.CompressIf(ef_len, ef);
		o.CompressIf(gh_len, gh);
#endif

		// clang-format off
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, ab_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, cd_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, ef_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, gh_len);
		// clang-format on

		double abcd_p[64], *abcd = abcd_p;
		double efgh_p[64], *efgh = efgh_p;
		double L_p[64], *L       = L_p;
		int    abcd_len, efgh_len, L_len;

#ifdef OMC_LIMIT_EXPANSION_LENGTH
		if (ab_len * cd_len <= OMC_EXPANSION_LENGTH_THRES &&
		    ef_len * gh_len <= OMC_EXPANSION_LENGTH_THRES)
#endif
		{
			abcd_len = o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
			efgh_len = o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
			L_len = o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);
			double return_value = L[L_len - 1];
			if (return_value > 0)
				return_sign = Sign::POSITIVE;
			if (return_value < 0)
				return_sign = Sign::NEGATIVE;
			if (return_value == 0)
				return_sign = Sign::ZERO;
		}
#ifdef OMC_LIMIT_EXPANSION_LENGTH
		else if (ab_len <= OMC_SUM_LENGTH_THRES && cd_len <= OMC_SUM_LENGTH_THRES &&
		         ef_len <= OMC_SUM_LENGTH_THRES && gh_len <= OMC_SUM_LENGTH_THRES)
		{
			ET ab_et = 0, cd_et = 0, ef_et = 0, gh_et = 0;
			// clang-format off
			for (int i = 0; i < ab_len; i++) ab_et += ab[i];
			for (int i = 0; i < cd_len; i++) cd_et += cd[i];
			for (int i = 0; i < ef_len; i++) ef_et += ef[i];
			for (int i = 0; i < gh_len; i++) gh_et += gh[i];
			// clang-format on
			ET abcd_et  = ab_et * cd_et;
			ET efgh_et  = ef_et * gh_et;
			ET L_et     = abcd_et - efgh_et;
			return_sign = OMC::sign(L_et);
		}
		else
		{
			return_sign = orientOn2Dyz_III_exact<IT, ET>(p1, p2, p3);
		}
#endif

		if (L_p != L)
			FreeDoubles(L);
		if (efgh_p != efgh)
			FreeDoubles(efgh);
		if (abcd_p != abcd)
			FreeDoubles(abcd);
		if (gh_p != gh)
			FreeDoubles(gh);
		if (ef_p != ef)
			FreeDoubles(ef);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (h_p != h)
			FreeDoubles(h);
		if (g_p != g)
			FreeDoubles(g);
		if (f_p != f)
			FreeDoubles(f);
		if (e_p != e)
			FreeDoubles(e);
		if (d_p != d)
			FreeDoubles(d);
		if (c_p != c)
			FreeDoubles(c);
		if (b_p != b)
			FreeDoubles(b);
		if (a_p != a)
			FreeDoubles(a);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dyz_III_exact<IT, ET>(p1, p2, p3);
#endif

	return return_sign;
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2, double op3x,
                                double op3z)
{
	Sign return_sign = Sign::UNCERTAIN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p, l2x_p[64], *l2x = l2x_p,
	                  l2y_p[64], *l2y = l2y_p, l2z_p[64], *l2z = l2z_p, d2_p[64],
	                  *d2 = d2_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64, l2x_len = 64,
	    l2y_len = 64, l2z_len = 64, d2_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2z_len, l2z, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1z_len, l1z, &b, 64);
		double c_p[64], *c = c_p;
		int    c_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, op3x, &c, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &f, 64);
		double g_p[64], *g = g_p;
		int    g_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, op3z, &g, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, l1x_len, l1x, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, l1z_len, l1z, &gh, 64);

#ifdef OMC_COMPRESS_EXPANSION
		o.CompressIf(ab_len, ab);
		o.CompressIf(cd_len, cd);
		o.CompressIf(ef_len, ef);
		o.CompressIf(gh_len, gh);
#endif

		double abcd_p[64], *abcd = abcd_p;
		double efgh_p[64], *efgh = efgh_p;
		double L_p[64], *L       = L_p;
		int    abcd_len, efgh_len, L_len;

#ifdef OMC_LIMIT_EXPANSION_LENGTH
		if (ab_len * cd_len <= OMC_EXPANSION_LENGTH_THRES &&
		    ef_len * gh_len <= OMC_EXPANSION_LENGTH_THRES)
#endif
		{
			abcd_len = o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
			efgh_len = o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
			L_len = o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);
			double return_value = L[L_len - 1];
			if (return_value > 0)
				return_sign = Sign::POSITIVE;
			if (return_value < 0)
				return_sign = Sign::NEGATIVE;
			if (return_value == 0)
				return_sign = Sign::ZERO;
		}
#ifdef OMC_LIMIT_EXPANSION_LENGTH
		else if (ab_len <= OMC_SUM_LENGTH_THRES && cd_len <= OMC_SUM_LENGTH_THRES &&
		         ef_len <= OMC_SUM_LENGTH_THRES && gh_len <= OMC_SUM_LENGTH_THRES)
		{
			ET ab_et = 0, cd_et = 0, ef_et = 0, gh_et = 0;
			// clang-format off
			for (int i = 0; i < ab_len; i++) ab_et += ab[i];
			for (int i = 0; i < cd_len; i++) cd_et += cd[i];
			for (int i = 0; i < ef_len; i++) ef_et += ef[i];
			for (int i = 0; i < gh_len; i++) gh_et += gh[i];
			// clang-format on
			ET abcd_et  = ab_et * cd_et;
			ET efgh_et  = ef_et * gh_et;
			ET L_et     = abcd_et - efgh_et;
			return_sign = OMC::sign(L_et);
		}
		else
		{
			return_sign = orientOn2Dzx_IIE_exact<IT, ET>(p1, p2, op3x, op3z);
		}
#endif

		if (L_p != L)
			FreeDoubles(L);
		if (efgh_p != efgh)
			FreeDoubles(efgh);
		if (abcd_p != abcd)
			FreeDoubles(abcd);
		if (gh_p != gh)
			FreeDoubles(gh);
		if (ef_p != ef)
			FreeDoubles(ef);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (g_p != g)
			FreeDoubles(g);
		if (f_p != f)
			FreeDoubles(f);
		if (e_p != e)
			FreeDoubles(e);
		if (c_p != c)
			FreeDoubles(c);
		if (b_p != b)
			FreeDoubles(b);
		if (a_p != a)
			FreeDoubles(a);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dzx_IIE_exact<IT, ET>(p1, p2, op3x, op3z);
#endif

	return return_sign;
}

template <typename IT, typename ET>
Sign orientOn2Dzx_III_expansion(const GenericPoint3T<IT, ET> &p1,
                                const GenericPoint3T<IT, ET> &p2,
                                const GenericPoint3T<IT, ET> &p3)
{
	Sign return_sign = Sign::UNCERTAIN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p, l2x_p[64], *l2x = l2x_p,
	                  l2y_p[64], *l2y = l2y_p, l2z_p[64], *l2z = l2z_p, d2_p[64],
	                  *d2 = d2_p, l3x_p[64], *l3x = l3x_p, l3y_p[64],
	                  *l3y = l3y_p, l3z_p[64], *l3z = l3z_p, d3_p[64], *d3 = d3_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64, l2x_len = 64,
	    l2y_len = 64, l2z_len = 64, d2_len = 64, l3x_len = 64, l3y_len = 64,
	    l3z_len = 64, d3_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2z_len, l2z, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1z_len, l1z, &b, 64);
		double c_p[64], *c = c_p;
		int c_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l3x_len, l3x, &c, 64);
		double d_p[64], *d = d_p;
		int d_len = o.Gen_Product_With_PreAlloc(d3_len, d3, l1x_len, l1x, &d, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &f, 64);
		double g_p[64], *g = g_p;
		int g_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l3z_len, l3z, &g, 64);
		double h_p[64], *h = h_p;
		int h_len = o.Gen_Product_With_PreAlloc(d3_len, d3, l1z_len, l1z, &h, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, d_len, d, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, h_len, h, &gh, 64);

#ifdef OMC_COMPRESS_EXPANSION
		o.CompressIf(ab_len, ab);
		o.CompressIf(cd_len, cd);
		o.CompressIf(ef_len, ef);
		o.CompressIf(gh_len, gh);
#endif

		// clang-format off
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, ab_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, cd_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, ef_len);
		OMC_PRED_PROFILE_INC_LEN(PredicateNames::_orientOn2D_III, gh_len);
		// clang-format on

		double abcd_p[64], *abcd = abcd_p;
		double efgh_p[64], *efgh = efgh_p;
		double L_p[64], *L       = L_p;
		int    abcd_len, efgh_len, L_len;

#ifdef OMC_LIMIT_EXPANSION_LENGTH
		if (ab_len * cd_len <= OMC_EXPANSION_LENGTH_THRES &&
		    ef_len * gh_len <= OMC_EXPANSION_LENGTH_THRES)
#endif
		{
			abcd_len = o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
			efgh_len = o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
			L_len = o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);
			double return_value = L[L_len - 1];
			if (return_value > 0)
				return_sign = Sign::POSITIVE;
			if (return_value < 0)
				return_sign = Sign::NEGATIVE;
			if (return_value == 0)
				return_sign = Sign::ZERO;
		}
#ifdef OMC_LIMIT_EXPANSION_LENGTH
		else if (ab_len <= OMC_SUM_LENGTH_THRES && cd_len <= OMC_SUM_LENGTH_THRES &&
		         ef_len <= OMC_SUM_LENGTH_THRES && gh_len <= OMC_SUM_LENGTH_THRES)
		{
			ET ab_et = 0, cd_et = 0, ef_et = 0, gh_et = 0;
			// clang-format off
			for (int i = 0; i < ab_len; i++) ab_et += ab[i];
			for (int i = 0; i < cd_len; i++) cd_et += cd[i];
			for (int i = 0; i < ef_len; i++) ef_et += ef[i];
			for (int i = 0; i < gh_len; i++) gh_et += gh[i];
			// clang-format on
			ET abcd_et  = ab_et * cd_et;
			ET efgh_et  = ef_et * gh_et;
			ET L_et     = abcd_et - efgh_et;
			return_sign = OMC::sign(L_et);
		}
		else
		{
			return_sign = orientOn2Dzx_III_exact<IT, ET>(p1, p2, p3);
		}
#endif

		if (L_p != L)
			FreeDoubles(L);
		if (efgh_p != efgh)
			FreeDoubles(efgh);
		if (abcd_p != abcd)
			FreeDoubles(abcd);
		if (gh_p != gh)
			FreeDoubles(gh);
		if (ef_p != ef)
			FreeDoubles(ef);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (h_p != h)
			FreeDoubles(h);
		if (g_p != g)
			FreeDoubles(g);
		if (f_p != f)
			FreeDoubles(f);
		if (e_p != e)
			FreeDoubles(e);
		if (d_p != d)
			FreeDoubles(d);
		if (c_p != c)
			FreeDoubles(c);
		if (b_p != b)
			FreeDoubles(b);
		if (a_p != a)
			FreeDoubles(a);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dzx_III_exact<IT, ET>(p1, p2, p3);
#endif

	return return_sign;
}

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2x, IT p2y,
                               IT p3x, IT p3y)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT t1x = p2y - p3y;
	IT t1y = p3x - p2x;
	IT e2  = l1x * t1x;
	IT e3  = l1y * t1y;
	IT e   = e2 + e3;
	IT pr1 = p2x * p3y;
	IT pr2 = p2y * p3x;
	IT pr  = pr1 - pr2;
	IT dpr = d1 * pr;
	IT det = dpr + e;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2x, ET p2y,
                            ET p3x, ET p3y)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET t1x = p2y - p3y;
	ET t1y = p3x - p2x;
	ET e2  = l1x * t1x;
	ET e3  = l1y * t1y;
	ET e   = e2 + e3;
	ET pr1 = p2x * p3y;
	ET pr2 = p2y * p3x;
	ET pr  = pr1 - pr2;
	ET dpr = d1 * pr;
	ET det = dpr + e;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2x,
                                double p2y, double p3x, double p3y)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[128], *l1x = l1x_p, l1y_p[128], *l1y = l1y_p, l1z_p[128],
	                   *l1z = l1z_p, d1_p[128], *d1 = d1_p;
	int l1x_len = 128, l1y_len = 128, l1z_len = 128, d1_len = 128;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          t1x[2];
		o.Two_Diff(p2y, p3y, t1x);
		double t1y[2];
		o.Two_Diff(p3x, p2x, t1y);
		double e2_p[128], *e2 = e2_p;
		int    e2_len = o.Gen_Product_With_PreAlloc(l1x_len, l1x, 2, t1x, &e2, 128);
		double e3_p[128], *e3 = e3_p;
		int    e3_len = o.Gen_Product_With_PreAlloc(l1y_len, l1y, 2, t1y, &e3, 128);
		double e_p[128], *e = e_p;
		int    e_len = o.Gen_Sum_With_PreAlloc(e2_len, e2, e3_len, e3, &e, 128);
		double pr1[2];
		o.Two_Prod(p2x, p3y, pr1);
		double pr2[2];
		o.Two_Prod(p2y, p3x, pr2);
		double pr[4];
		o.Two_Two_Diff(pr1, pr2, pr);
		double dpr_p[128], *dpr = dpr_p;
		int    dpr_len = o.Gen_Product_With_PreAlloc(d1_len, d1, 4, pr, &dpr, 128);
		double det_p[128], *det = det_p;
		int    det_len = o.Gen_Sum_With_PreAlloc(dpr_len, dpr, e_len, e, &det, 128);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dpr_p != dpr)
			FreeDoubles(dpr);
		if (e_p != e)
			FreeDoubles(e);
		if (e3_p != e3)
			FreeDoubles(e3);
		if (e2_p != e2)
			FreeDoubles(e2);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dxy_IEE_exact<IT, ET>(p1, p2x, p2y, p3x, p3y);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE(const GenericPoint3T<IT, ET> &p1, double p2x, double p2y,
                      double p3x, double p3y)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dxy_IEE);
	Sign ret;
	ret = orientOn2Dxy_IEE_interval<IT, ET>(p1, p2x, p2y, p3x, p3y);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dxy_IEE);
	return orientOn2Dxy_IEE_expansion<IT, ET>(p1, p2x, p2y, p3x, p3y);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IEE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3)
{
	return orientOn2Dxy_IEE<IT, ET>(p1, p2.x(), p2.y(), p3.x(), p3.y());
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, IT op3x,
                               IT op3y)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2x;
	IT b    = d2 * l1x;
	IT c    = d1 * op3y;
	IT e    = d1 * l2y;
	IT f    = d2 * l1y;
	IT g    = d1 * op3x;
	IT ab   = a - b;
	IT cd   = c - l1y;
	IT ef   = e - f;
	IT gh   = g - l1x;
	IT abcd = ab * cd;
	IT efgh = ef * gh;
	IT L    = abcd - efgh;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, ET op3x, ET op3y)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET a    = d1 * l2x;
	ET b    = d2 * l1x;
	ET c    = d1 * op3y;
	ET e    = d1 * l2y;
	ET f    = d2 * l1y;
	ET g    = d1 * op3x;
	ET ab   = a - b;
	ET cd   = c - l1y;
	ET ef   = e - f;
	ET gh   = g - l1x;
	ET abcd = ab * cd;
	ET efgh = ef * gh;
	ET L    = abcd - efgh;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2, double op3x,
                      double op3y)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dxy_IIE);
	Sign ret;
	ret = orientOn2Dxy_IIE_interval<IT, ET>(p1, p2, op3x, op3y);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dxy_IIE);
	return orientOn2Dxy_IIE_expansion<IT, ET>(p1, p2, op3x, op3y);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &op3)
{
	return orientOn2Dxy_IIE<IT, ET>(p1, p2, op3.x(), op3.y());
}

template <typename IT, typename ET>
Sign orientOn2Dxy_III_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2x;
	IT b    = d2 * l1x;
	IT c    = d1 * l3y;
	IT d    = d3 * l1y;
	IT e    = d1 * l2y;
	IT f    = d2 * l1y;
	IT g    = d1 * l3x;
	IT h    = d3 * l1x;
	IT ab   = a - b;
	IT cd   = c - d;
	IT ef   = e - f;
	IT gh   = g - h;
	IT abcd = ab * cd;
	IT efgh = ef * gh;
	IT L    = abcd - efgh;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_III_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET a    = d1 * l2x;
	ET b    = d2 * l1x;
	ET c    = d1 * l3y;
	ET d    = d3 * l1y;
	ET e    = d1 * l2y;
	ET f    = d2 * l1y;
	ET g    = d1 * l3x;
	ET h    = d3 * l1x;
	ET ab   = a - b;
	ET cd   = c - d;
	ET ef   = e - f;
	ET gh   = g - h;
	ET abcd = ab * cd;
	ET efgh = ef * gh;
	ET L    = abcd - efgh;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dxy_III(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dxy_III);
	Sign ret;
	ret = orientOn2Dxy_III_interval<IT, ET>(p1, p2, p3);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dxy_III);
	return orientOn2Dxy_III_expansion<IT, ET>(p1, p2, p3);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2y, IT p2z,
                               IT p3y, IT p3z)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT t1y = p2z - p3z;
	IT t1z = p3y - p2y;
	IT e2  = l1y * t1y;
	IT e3  = l1z * t1z;
	IT e   = e2 + e3;
	IT pr1 = p2y * p3z;
	IT pr2 = p2z * p3y;
	IT pr  = pr1 - pr2;
	IT dpr = d1 * pr;
	IT det = dpr + e;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2y, ET p2z,
                            ET p3y, ET p3z)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET t1y = p2z - p3z;
	ET t1z = p3y - p2y;
	ET e2  = l1y * t1y;
	ET e3  = l1z * t1z;
	ET e   = e2 + e3;
	ET pr1 = p2y * p3z;
	ET pr2 = p2z * p3y;
	ET pr  = pr1 - pr2;
	ET dpr = d1 * pr;
	ET det = dpr + e;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2y,
                                double p2z, double p3y, double p3z)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[128], *l1x = l1x_p, l1y_p[128], *l1y = l1y_p, l1z_p[128],
	                   *l1z = l1z_p, d1_p[128], *d1 = d1_p;
	int l1x_len = 128, l1y_len = 128, l1z_len = 128, d1_len = 128;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          t1y[2];
		o.Two_Diff(p2z, p3z, t1y);
		double t1z[2];
		o.Two_Diff(p3y, p2y, t1z);
		double e2_p[128], *e2 = e2_p;
		int    e2_len = o.Gen_Product_With_PreAlloc(l1y_len, l1y, 2, t1y, &e2, 128);
		double e3_p[128], *e3 = e3_p;
		int    e3_len = o.Gen_Product_With_PreAlloc(l1z_len, l1z, 2, t1z, &e3, 128);
		double e_p[128], *e = e_p;
		int    e_len = o.Gen_Sum_With_PreAlloc(e2_len, e2, e3_len, e3, &e, 128);
		double pr1[2];
		o.Two_Prod(p2y, p3z, pr1);
		double pr2[2];
		o.Two_Prod(p2z, p3y, pr2);
		double pr[4];
		o.Two_Two_Diff(pr1, pr2, pr);
		double dpr_p[128], *dpr = dpr_p;
		int    dpr_len = o.Gen_Product_With_PreAlloc(d1_len, d1, 4, pr, &dpr, 128);
		double det_p[128], *det = det_p;
		int    det_len = o.Gen_Sum_With_PreAlloc(dpr_len, dpr, e_len, e, &det, 128);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dpr_p != dpr)
			FreeDoubles(dpr);
		if (e_p != e)
			FreeDoubles(e);
		if (e3_p != e3)
			FreeDoubles(e3);
		if (e2_p != e2)
			FreeDoubles(e2);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dyz_IEE_exact<IT, ET>(p1, p2y, p2z, p3y, p3z);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE(const GenericPoint3T<IT, ET> &p1, double p2y, double p2z,
                      double p3y, double p3z)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dyz_IEE);
	Sign ret;
	ret = orientOn2Dyz_IEE_interval<IT, ET>(p1, p2y, p2z, p3y, p3z);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dyz_IEE);
	return orientOn2Dyz_IEE_expansion<IT, ET>(p1, p2y, p2z, p3y, p3z);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IEE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3)
{
	return orientOn2Dyz_IEE<IT, ET>(p1, p2.y(), p2.z(), p3.y(), p3.z());
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, IT op3y,
                               IT op3z)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2y;
	IT b    = d2 * l1y;
	IT c    = d1 * op3z;
	IT e    = d1 * l2z;
	IT f    = d2 * l1z;
	IT g    = d1 * op3y;
	IT ab   = a - b;
	IT cd   = c - l1z;
	IT ef   = e - f;
	IT gh   = g - l1y;
	IT abcd = ab * cd;
	IT efgh = ef * gh;
	IT L    = abcd - efgh;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, ET op3y, ET op3z)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET a    = d1 * l2y;
	ET b    = d2 * l1y;
	ET c    = d1 * op3z;
	ET e    = d1 * l2z;
	ET f    = d2 * l1z;
	ET g    = d1 * op3y;
	ET ab   = a - b;
	ET cd   = c - l1z;
	ET ef   = e - f;
	ET gh   = g - l1y;
	ET abcd = ab * cd;
	ET efgh = ef * gh;
	ET L    = abcd - efgh;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2, double op3y,
                      double op3z)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dyz_IIE);
	Sign ret;
	ret = orientOn2Dyz_IIE_interval<IT, ET>(p1, p2, op3y, op3z);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dyz_IIE);
	return orientOn2Dyz_IIE_expansion<IT, ET>(p1, p2, op3y, op3z);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &op3)
{
	return orientOn2Dyz_IIE<IT, ET>(p1, p2, op3.y(), op3.z());
}

template <typename IT, typename ET>
Sign orientOn2Dyz_III_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2y;
	IT b    = d2 * l1y;
	IT c    = d1 * l3z;
	IT d    = d3 * l1z;
	IT e    = d1 * l2z;
	IT f    = d2 * l1z;
	IT g    = d1 * l3y;
	IT h    = d3 * l1y;
	IT ab   = a - b;
	IT cd   = c - d;
	IT ef   = e - f;
	IT gh   = g - h;
	IT abcd = ab * cd;
	IT efgh = ef * gh;
	IT L    = abcd - efgh;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_III_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET a    = d1 * l2y;
	ET b    = d2 * l1y;
	ET c    = d1 * l3z;
	ET d    = d3 * l1z;
	ET e    = d1 * l2z;
	ET f    = d2 * l1z;
	ET g    = d1 * l3y;
	ET h    = d3 * l1y;
	ET ab   = a - b;
	ET cd   = c - d;
	ET ef   = e - f;
	ET gh   = g - h;
	ET abcd = ab * cd;
	ET efgh = ef * gh;
	ET L    = abcd - efgh;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dyz_III(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dyz_III);
	Sign ret;
	ret = orientOn2Dyz_III_interval<IT, ET>(p1, p2, p3);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dyz_III);
	return orientOn2Dyz_III_expansion<IT, ET>(p1, p2, p3);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2x, IT p2z,
                               IT p3x, IT p3z)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT t1z = p2x - p3x;
	IT t1x = p3z - p2z;
	IT e2  = l1z * t1z;
	IT e3  = l1x * t1x;
	IT e   = e2 + e3;
	IT pr1 = p2z * p3x;
	IT pr2 = p2x * p3z;
	IT pr  = pr1 - pr2;
	IT dpr = d1 * pr;
	IT det = dpr + e;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2x, ET p2z,
                            ET p3x, ET p3z)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET t1z = p2x - p3x;
	ET t1x = p3z - p2z;
	ET e2  = l1z * t1z;
	ET e3  = l1x * t1x;
	ET e   = e2 + e3;
	ET pr1 = p2z * p3x;
	ET pr2 = p2x * p3z;
	ET pr  = pr1 - pr2;
	ET dpr = d1 * pr;
	ET det = dpr + e;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2x,
                                double p2z, double p3x, double p3z)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[128], *l1x = l1x_p, l1y_p[128], *l1y = l1y_p, l1z_p[128],
	                   *l1z = l1z_p, d1_p[128], *d1 = d1_p;
	int l1x_len = 128, l1y_len = 128, l1z_len = 128, d1_len = 128;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          t1z[2];
		o.Two_Diff(p2x, p3x, t1z);
		double t1x[2];
		o.Two_Diff(p3z, p2z, t1x);
		double e2_p[128], *e2 = e2_p;
		int    e2_len = o.Gen_Product_With_PreAlloc(l1z_len, l1z, 2, t1z, &e2, 128);
		double e3_p[128], *e3 = e3_p;
		int    e3_len = o.Gen_Product_With_PreAlloc(l1x_len, l1x, 2, t1x, &e3, 128);
		double e_p[128], *e = e_p;
		int    e_len = o.Gen_Sum_With_PreAlloc(e2_len, e2, e3_len, e3, &e, 128);
		double pr1[2];
		o.Two_Prod(p2z, p3x, pr1);
		double pr2[2];
		o.Two_Prod(p2x, p3z, pr2);
		double pr[4];
		o.Two_Two_Diff(pr1, pr2, pr);
		double dpr_p[128], *dpr = dpr_p;
		int    dpr_len = o.Gen_Product_With_PreAlloc(d1_len, d1, 4, pr, &dpr, 128);
		double det_p[128], *det = det_p;
		int    det_len = o.Gen_Sum_With_PreAlloc(dpr_len, dpr, e_len, e, &det, 128);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dpr_p != dpr)
			FreeDoubles(dpr);
		if (e_p != e)
			FreeDoubles(e);
		if (e3_p != e3)
			FreeDoubles(e3);
		if (e2_p != e2)
			FreeDoubles(e2);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orientOn2Dzx_IEE_exact<IT, ET>(p1, p2x, p2z, p3x, p3z);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE(const GenericPoint3T<IT, ET> &p1, double p2x, double p2z,
                      double p3x, double p3z)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dzx_IEE);
	Sign ret;
	ret = orientOn2Dzx_IEE_interval<IT, ET>(p1, p2x, p2z, p3x, p3z);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dzx_IEE);
	return orientOn2Dzx_IEE_expansion<IT, ET>(p1, p2x, p2z, p3x, p3z);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IEE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3)
{
	return orientOn2Dzx_IEE<IT, ET>(p1, p2.x(), p2.z(), p3.x(), p3.z());
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, IT op3x,
                               IT op3z)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2z;
	IT b    = d2 * l1z;
	IT c    = d1 * op3x;
	IT e    = d1 * l2x;
	IT f    = d2 * l1x;
	IT g    = d1 * op3z;
	IT ab   = a - b;
	IT cd   = c - l1x;
	IT ef   = e - f;
	IT gh   = g - l1z;
	IT abcd = ab * cd;
	IT efgh = ef * gh;
	IT L    = abcd - efgh;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, ET op3x, ET op3z)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET a    = d1 * l2z;
	ET b    = d2 * l1z;
	ET c    = d1 * op3x;
	ET e    = d1 * l2x;
	ET f    = d2 * l1x;
	ET g    = d1 * op3z;
	ET ab   = a - b;
	ET cd   = c - l1x;
	ET ef   = e - f;
	ET gh   = g - l1z;
	ET abcd = ab * cd;
	ET efgh = ef * gh;
	ET L    = abcd - efgh;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2, double op3x,
                      double op3z)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dzx_IIE);
	Sign ret;
	ret = orientOn2Dzx_IIE_interval<IT, ET>(p1, p2, op3x, op3z);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dzx_IIE);
	return orientOn2Dzx_IIE_expansion<IT, ET>(p1, p2, op3x, op3z);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_IIE(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &op3)
{
	return orientOn2Dzx_IIE<IT, ET>(p1, p2, op3.x(), op3.z());
}

template <typename IT, typename ET>
Sign orientOn2Dzx_III_interval(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2z;
	IT b    = d2 * l1z;
	IT c    = d1 * l3x;
	IT d    = d3 * l1x;
	IT e    = d1 * l2x;
	IT f    = d2 * l1x;
	IT g    = d1 * l3z;
	IT h    = d3 * l1z;
	IT ab   = a - b;
	IT cd   = c - d;
	IT ef   = e - f;
	IT gh   = g - h;
	IT abcd = ab * cd;
	IT efgh = ef * gh;
	IT L    = abcd - efgh;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_III_exact(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET a    = d1 * l2z;
	ET b    = d2 * l1z;
	ET c    = d1 * l3x;
	ET d    = d3 * l1x;
	ET e    = d1 * l2x;
	ET f    = d2 * l1x;
	ET g    = d1 * l3z;
	ET h    = d3 * l1z;
	ET ab   = a - b;
	ET cd   = c - d;
	ET ef   = e - f;
	ET gh   = g - h;
	ET abcd = ab * cd;
	ET efgh = ef * gh;
	ET L    = abcd - efgh;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign orientOn2Dzx_III(const GenericPoint3T<IT, ET> &p1,
                      const GenericPoint3T<IT, ET> &p2,
                      const GenericPoint3T<IT, ET> &p3)
{
	OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_orientOn2Dzx_III);
	Sign ret;
	ret = orientOn2Dzx_III_interval<IT, ET>(p1, p2, p3);
	if (is_sign_reliable(ret))
		return ret;
	OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_orientOn2Dzx_III);
	return orientOn2Dzx_III_expansion<IT, ET>(p1, p2, p3);
}

} // namespace OMC