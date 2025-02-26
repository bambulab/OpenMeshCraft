#pragma once

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

inline Sign orient2d_filtered(double p1x, double p1y, double p2x, double p2y,
                              double p3x, double p3y);

inline Sign orient2d_expansion(double p1x, double p1y, double p2x, double p2y,
                               double p3x, double p3y);

inline Sign orient2d(double p1x, double p1y, double p2x, double p2y, double p3x,
                     double p3y);

inline Sign orient2d(const double *p1, const double *p2, const double *p3);

template <typename IT, typename ET>
Sign orient2d(const GenericPoint2T<IT, ET> &p1,
              const GenericPoint2T<IT, ET> &p2,
              const GenericPoint2T<IT, ET> &p3);

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

template <typename IT, typename ET>
Sign orient2D_IEE_interval(const GenericPoint2T<IT, ET> &p1, IT p2x, IT p2y,
                           IT p3x, IT p3y);

template <typename IT, typename ET>
Sign orient2D_IEE_exact(const GenericPoint2T<IT, ET> &p1, ET p2x, ET p2y,
                        ET p3x, ET p3y);

template <typename IT, typename ET>
Sign orient2D_IEE_expansion(const GenericPoint2T<IT, ET> &p1, double p2x,
                            double p2y, double p3x, double p3y);

template <typename IT, typename ET>
Sign orient2D_IEE(const GenericPoint2T<IT, ET> &p1, double p2x, double p2y,
                  double p3x, double p3y);

template <typename IT, typename ET>
Sign orient2D_IEE(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2,
                  const GenericPoint2T<IT, ET> &p3);

/*===================================================================*/

template <typename IT, typename ET>
Sign orient2D_IIE_interval(const GenericPoint2T<IT, ET> &p1,
                           const GenericPoint2T<IT, ET> &p2, IT p3x, IT p3y);

template <typename IT, typename ET>
Sign orient2D_IIE_exact(const GenericPoint2T<IT, ET> &p1,
                        const GenericPoint2T<IT, ET> &p2, ET p3x, ET p3y);

template <typename IT, typename ET>
Sign orient2D_IIE_expansion(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2, double p3x,
                            double p3y);

template <typename IT, typename ET>
Sign orient2D_IIE(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2, double p3x, double p3y);

template <typename IT, typename ET>
Sign orient2D_IIE(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2,
                  const GenericPoint2T<IT, ET> &p3);

/*===================================================================*/

template <typename IT, typename ET>
Sign orient2D_III_interval(const GenericPoint2T<IT, ET> &p1,
                           const GenericPoint2T<IT, ET> &p2,
                           const GenericPoint2T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orient2D_III_exact(const GenericPoint2T<IT, ET> &p1,
                        const GenericPoint2T<IT, ET> &p2,
                        const GenericPoint2T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orient2D_III_expansion(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2,
                            const GenericPoint2T<IT, ET> &p3);

template <typename IT, typename ET>
Sign orient2D_III(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2,
                  const GenericPoint2T<IT, ET> &p3);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline Sign orient2d_filtered(double p1x, double p1y, double p2x, double p2y,
                              double p3x, double p3y)
{
	double dl  = (p2x - p1x) * (p3y - p1y);
	double dr  = (p2y - p1y) * (p3x - p1x);
	double det = dl - dr;
	double eb  = 3.3306690738754706e-016 * (fabs(dl) + fabs(dr));
	return filter_sign(det, eb);
}

inline Sign orient2d_expansion(double p1x, double p1y, double p2x, double p2y,
                               double p3x, double p3y)
{
	expansionObject o;
	double          acx[2], acy[2], bcx[2], bcy[2], dtl[2], dtr[2], B[4];
	double          s[2], t[2], u[4], C1[8], C2[12], D[16];
	int             C1l, C2l, Dl;

	acx[1] = (p1x - p3x);
	bcx[1] = (p2x - p3x);
	acy[1] = (p1y - p3y);
	bcy[1] = (p2y - p3y);

	o.Two_Prod(acx[1], bcy[1], dtl);
	o.Two_Prod(acy[1], bcx[1], dtr);
	o.Two_Two_Diff(dtl, dtr, B);

	double dsm = (fabs(dtl[1]) + fabs(dtr[1]));
	double det = o.To_Double(4, B);
	double eb  = 2.2204460492503146e-16 * dsm;
	Dl         = ((det >= eb) - (-det >= eb));
	if (Dl)
		return static_cast<Sign>(Dl);

	o.Two_Diff_Back(p1x, p3x, acx);
	o.Two_Diff_Back(p2x, p3x, bcx);
	o.Two_Diff_Back(p1y, p3y, acy);
	o.Two_Diff_Back(p2y, p3y, bcy);

	if ((acx[0] == 0.0) && (acy[0] == 0.0) && (bcx[0] == 0.0) && (bcy[0] == 0.0))
		return static_cast<Sign>((det > 0) - (det < 0));

	eb = 1.1093356479670487e-31 * dsm + 3.3306690738754706e-16 * fabs(det);
	det +=
	  (acx[1] * bcy[0] + bcy[1] * acx[0]) - (acy[1] * bcx[0] + bcx[1] * acy[0]);
	Dl = ((det >= eb) - (-det >= eb));
	if (Dl)
		return static_cast<Sign>(Dl);

	o.Two_Prod(acx[0], bcy[1], s);
	o.Two_Prod(acy[0], bcx[1], t);
	o.Two_Two_Diff(s, t, u);
	C1l = o.Gen_Sum(4, B, 4, u, C1);

	o.Two_Prod(acx[1], bcy[0], s);
	o.Two_Prod(acy[1], bcx[0], t);
	o.Two_Two_Diff(s, t, u);
	C2l = o.Gen_Sum(C1l, C1, 4, u, C2);

	o.Two_Prod(acx[0], bcy[0], s);
	o.Two_Prod(acy[0], bcx[0], t);
	o.Two_Two_Diff(s, t, u);
	Dl = o.Gen_Sum(C2l, C2, 4, u, D);

	det = D[Dl - 1];
	return static_cast<Sign>((det >= eb) - (-det >= eb));
}

inline Sign orient2d(double p1x, double p1y, double p2x, double p2y, double p3x,
                     double p3y)
{
	Sign ret = orient2d_filtered(p1x, p1y, p2x, p2y, p3x, p3y);
	if (is_sign_reliable(ret))
		return ret;
	return orient2d_expansion(p1x, p1y, p2x, p2y, p3x, p3y);
}

inline Sign orient2d(const double *p1, const double *p2, const double *p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2d(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);
#else
	return OMC::sign(::orient2d(p1, p2, p3));
#endif
}

template <typename IT, typename ET>
Sign orient2d(const GenericPoint2T<IT, ET> &p1,
              const GenericPoint2T<IT, ET> &p2,
              const GenericPoint2T<IT, ET> &p3)
{
#ifdef OMC_NO_SHEWCHUK
	return orient2d(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
#else
	return OMC::sign(::orient2d(p1.data(), p2.data(), p3.data()));
#endif
}

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

template <typename IT, typename ET>
Sign orient2D_IEE_interval(const GenericPoint2T<IT, ET> &p1, IT p2x, IT p2y,
                           IT p3x, IT p3y)
{
	IT l1x, l1y, d1;
	if (!p1.getIntervalLambda(l1x, l1y, d1))
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
Sign orient2D_IEE_exact(const GenericPoint2T<IT, ET> &p1, ET p2x, ET p2y,
                        ET p3x, ET p3y)
{
	ET l1x, l1y, d1;
	p1.getExactLambda(l1x, l1y, d1);
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
Sign orient2D_IEE_expansion(const GenericPoint2T<IT, ET> &p1, double p2x,
                            double p2y, double p3x, double p3y)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[128], *l1x = l1x_p, l1y_p[128], *l1y = l1y_p, d1_p[128],
	                   *d1 = d1_p;
	int l1x_len = 128, l1y_len = 128, d1_len = 128;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
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

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (d1_p != d1)
			FreeDoubles(d1);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orient2D_IEE_exact<IT, ET>(p1, p2x, p2y, p3x, p3y);
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
Sign orient2D_IEE(const GenericPoint2T<IT, ET> &p1, double p2x, double p2y,
                  double p3x, double p3y)
{
	Sign ret;
	ret = orient2D_IEE_interval<IT, ET>(p1, p2x, p2y, p3x, p3y);
	if (is_sign_reliable(ret))
		return ret;
	return orient2D_IEE_expansion<IT, ET>(p1, p2x, p2y, p3x, p3y);
}

template <typename IT, typename ET>
Sign orient2D_IEE(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2,
                  const GenericPoint2T<IT, ET> &p3)
{
	return orient2D_IEE<IT, ET>(p1, p2.x(), p2.y(), p3.x(), p3.y());
}

template <typename IT, typename ET>
Sign orient2D_IIE_interval(const GenericPoint2T<IT, ET> &p1,
                           const GenericPoint2T<IT, ET> &p2, IT p3x, IT p3y)
{
	IT l1x, l1y, d1, l2x, l2y, d2;
	if (!p1.getIntervalLambda(l1x, l1y, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT a    = d1 * l2x;
	IT b    = d2 * l1x;
	IT c    = d1 * p3y;
	IT e    = d1 * l2y;
	IT f    = d2 * l1y;
	IT g    = d1 * p3x;
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
Sign orient2D_IIE_exact(const GenericPoint2T<IT, ET> &p1,
                        const GenericPoint2T<IT, ET> &p2, ET p3x, ET p3y)
{
	ET l1x, l1y, d1, l2x, l2y, d2;
	p1.getExactLambda(l1x, l1y, d1);
	p2.getExactLambda(l2x, l2y, d2);
	ET a    = d1 * l2x;
	ET b    = d2 * l1x;
	ET c    = d1 * p3y;
	ET e    = d1 * l2y;
	ET f    = d2 * l1y;
	ET g    = d1 * p3x;
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
Sign orient2D_IIE_expansion(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2, double p3x,
                            double p3y)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, d1_p[64], *d1 = d1_p,
	                  l2x_p[64], *l2x = l2x_p, l2y_p[64], *l2y = l2y_p, d2_p[64],
	                  *d2 = d2_p;
	int l1x_len = 64, l1y_len = 64, d1_len = 64, l2x_len = 64, l2y_len = 64,
	    d2_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &d2, d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          a_p[64], *a = a_p;
		int a_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &a, 64);
		double b_p[64], *b = b_p;
		int b_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &b, 64);
		double c_p[64], *c = c_p;
		int    c_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p3y, &c, 64);
		double e_p[64], *e = e_p;
		int e_len = o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &e, 64);
		double f_p[64], *f = f_p;
		int f_len = o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &f, 64);
		double g_p[64], *g = g_p;
		int    g_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p3x, &g, 64);
		double ab_p[64], *ab = ab_p;
		int    ab_len = o.Gen_Diff_With_PreAlloc(a_len, a, b_len, b, &ab, 64);
		double cd_p[64], *cd = cd_p;
		int    cd_len = o.Gen_Diff_With_PreAlloc(c_len, c, l1y_len, l1y, &cd, 64);
		double ef_p[64], *ef = ef_p;
		int    ef_len = o.Gen_Diff_With_PreAlloc(e_len, e, f_len, f, &ef, 64);
		double gh_p[64], *gh = gh_p;
		int    gh_len = o.Gen_Diff_With_PreAlloc(g_len, g, l1x_len, l1x, &gh, 64);
		double abcd_p[64], *abcd = abcd_p;
		int    abcd_len =
		  o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
		double efgh_p[64], *efgh = efgh_p;
		int    efgh_len =
		  o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
		double L_p[64], *L = L_p;
		int    L_len =
		  o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);

		return_value = L[L_len - 1];
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

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (d2_p != d2)
			FreeDoubles(d2);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orient2D_IIE_exact<IT, ET>(p1, p2, p3x, p3y);
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
Sign orient2D_IIE(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2, double p3x, double p3y)
{
	Sign ret;
	ret = orient2D_IIE_interval<IT, ET>(p1, p2, p3x, p3y);
	if (is_sign_reliable(ret))
		return ret;
	return orient2D_IIE_expansion<IT, ET>(p1, p2, p3x, p3y);
}

template <typename IT, typename ET>
Sign orient2D_IIE(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2,
                  const GenericPoint2T<IT, ET> &p3)
{
	return orient2D_IIE<IT, ET>(p1, p2, p3.x(), p3.y());
}

template <typename IT, typename ET>
Sign orient2D_III_interval(const GenericPoint2T<IT, ET> &p1,
                           const GenericPoint2T<IT, ET> &p2,
                           const GenericPoint2T<IT, ET> &p3)
{
	IT l1x, l1y, d1, l2x, l2y, d2, l3x, l3y, d3;
	if (!p1.getIntervalLambda(l1x, l1y, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, d3))
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
Sign orient2D_III_exact(const GenericPoint2T<IT, ET> &p1,
                        const GenericPoint2T<IT, ET> &p2,
                        const GenericPoint2T<IT, ET> &p3)
{
	ET l1x, l1y, d1, l2x, l2y, d2, l3x, l3y, d3;
	p1.getExactLambda(l1x, l1y, d1);
	p2.getExactLambda(l2x, l2y, d2);
	p3.getExactLambda(l3x, l3y, d3);
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
Sign orient2D_III_expansion(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2,
                            const GenericPoint2T<IT, ET> &p3)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, d1_p[64], *d1 = d1_p,
	                  l2x_p[64], *l2x = l2x_p, l2y_p[64], *l2y = l2y_p, d2_p[64],
	                  *d2 = d2_p, l3x_p[64], *l3x = l3x_p, l3y_p[64],
	                  *l3y = l3y_p, d3_p[64], *d3 = d3_p;
	int l1x_len = 64, l1y_len = 64, d1_len = 64, l2x_len = 64, l2y_len = 64,
	    d2_len = 64, l3x_len = 64, l3y_len = 64, d3_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &d2, d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &d3, d3_len);
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
		int    abcd_len =
		  o.Gen_Product_With_PreAlloc(ab_len, ab, cd_len, cd, &abcd, 64);
		double efgh_p[64], *efgh = efgh_p;
		int    efgh_len =
		  o.Gen_Product_With_PreAlloc(ef_len, ef, gh_len, gh, &efgh, 64);
		double L_p[64], *L = L_p;
		int    L_len =
		  o.Gen_Diff_With_PreAlloc(abcd_len, abcd, efgh_len, efgh, &L, 64);

		return_value = L[L_len - 1];
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

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (d3_p != d3)
			FreeDoubles(d3);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return orient2D_III_exact<IT, ET>(p1, p2, p3);
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
Sign orient2D_III(const GenericPoint2T<IT, ET> &p1,
                  const GenericPoint2T<IT, ET> &p2,
                  const GenericPoint2T<IT, ET> &p3)
{
	Sign ret;
	ret = orient2D_III_interval<IT, ET>(p1, p2, p3);
	if (is_sign_reliable(ret))
		return ret;
	return orient2D_III_expansion<IT, ET>(p1, p2, p3);
}

} // namespace OMC