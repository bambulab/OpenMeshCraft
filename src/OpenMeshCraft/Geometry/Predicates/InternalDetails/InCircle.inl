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

inline Sign inCircle(const double *a, const double *b, const double *c,
                     const double *d);

template <typename IT, typename ET>
Sign inCircle(const GenericPoint2T<IT, ET> &a, const GenericPoint2T<IT, ET> &b,
              const GenericPoint2T<IT, ET> &c, const GenericPoint2T<IT, ET> &d);

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

inline Sign inCircle_filtered(double pax, double pay, double pbx, double pby,
                              double pcx, double pcy, double pdx, double pdy);

template <typename IT>
Sign inCircle_interval(IT pax, IT pay, IT pbx, IT pby, IT pcx, IT pcy, IT pdx,
                       IT pdy);

template <typename ET>
Sign inCircle_exact(ET pax, ET pay, ET pbx, ET pby, ET pcx, ET pcy, ET pdx,
                    ET pdy);

inline Sign inCircle_expansion(double pax, double pay, double pbx, double pby,
                               double pcx, double pcy, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCircle(double pax, double pay, double pbx, double pby, double pcx,
              double pcy, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCircle(const GenericPoint2T<IT, ET> &pa,
              const GenericPoint2T<IT, ET> &pb,
              const GenericPoint2T<IT, ET> &pc,
              const GenericPoint2T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCircle_IEEE_interval(const GenericPoint2T<IT, ET> &p1, IT pbx, IT pby,
                            IT pcx, IT pcy, IT pdx, IT pdy);

template <typename IT, typename ET>
Sign inCircle_IEEE_exact(const GenericPoint2T<IT, ET> &p1, ET pbx, ET pby,
                         ET pcx, ET pcy, ET pdx, ET pdy);

template <typename IT, typename ET>
Sign inCircle_IEEE_expansion(const GenericPoint2T<IT, ET> &p1, double pbx,
                             double pby, double pcx, double pcy, double pdx,
                             double pdy);

template <typename IT, typename ET>
Sign inCircle_IEEE(const GenericPoint2T<IT, ET> &p1, double pbx, double pby,
                   double pcx, double pcy, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCircle_IEEE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &pb,
                   const GenericPoint2T<IT, ET> &pc,
                   const GenericPoint2T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCircle_IIEE_interval(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2, IT pcx, IT pcy,
                            IT pdx, IT pdy);

template <typename IT, typename ET>
Sign inCircle_IIEE_exact(const GenericPoint2T<IT, ET> &p1,
                         const GenericPoint2T<IT, ET> &p2, ET pcx, ET pcy,
                         ET pdx, ET pdy);

template <typename IT, typename ET>
Sign inCircle_IIEE_expansion(const GenericPoint2T<IT, ET> &p1,
                             const GenericPoint2T<IT, ET> &p2, double pcx,
                             double pcy, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCircle_IIEE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2, double pcx, double pcy,
                   double pdx, double pdy);

template <typename IT, typename ET>
Sign inCircle_IIEE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &pc,
                   const GenericPoint2T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCircle_IIIE_interval(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2,
                            const GenericPoint2T<IT, ET> &p3, IT pdx, IT pdy);

template <typename IT, typename ET>
Sign inCircle_IIIE_exact(const GenericPoint2T<IT, ET> &p1,
                         const GenericPoint2T<IT, ET> &p2,
                         const GenericPoint2T<IT, ET> &p3, ET pdx, ET pdy);

template <typename IT, typename ET>
Sign inCircle_IIIE_expansion(const GenericPoint2T<IT, ET> &p1,
                             const GenericPoint2T<IT, ET> &p2,
                             const GenericPoint2T<IT, ET> &p3, double pdx,
                             double pdy);

template <typename IT, typename ET>
Sign inCircle_IIIE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &p3, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCircle_IIIE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &p3,
                   const GenericPoint2T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCircle_IIII_interval(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2,
                            const GenericPoint2T<IT, ET> &p3,
                            const GenericPoint2T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCircle_IIII_exact(const GenericPoint2T<IT, ET> &p1,
                         const GenericPoint2T<IT, ET> &p2,
                         const GenericPoint2T<IT, ET> &p3,
                         const GenericPoint2T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCircle_IIII_expansion(const GenericPoint2T<IT, ET> &p1,
                             const GenericPoint2T<IT, ET> &p2,
                             const GenericPoint2T<IT, ET> &p3,
                             const GenericPoint2T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCircle_IIII(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &p3,
                   const GenericPoint2T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCirclexy_IEEE_interval(const GenericPoint3T<IT, ET> &p1, IT pbx, IT pby,
                              IT pcx, IT pcy, IT pdx, IT pdy);

template <typename IT, typename ET>
Sign inCirclexy_IEEE_exact(const GenericPoint3T<IT, ET> &p1, ET pbx, ET pby,
                           ET pcx, ET pcy, ET pdx, ET pdy);

template <typename IT, typename ET>
Sign inCirclexy_IEEE_expansion(const GenericPoint3T<IT, ET> &p1, double pbx,
                               double pby, double pcx, double pcy, double pdx,
                               double pdy);

template <typename IT, typename ET>
Sign inCirclexy_IEEE(const GenericPoint3T<IT, ET> &p1, double pbx, double pby,
                     double pcx, double pcy, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCirclexy_IEEE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &pb,
                     const GenericPoint3T<IT, ET> &pc,
                     const GenericPoint3T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCirclexy_IIEE_interval(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2, IT pcx, IT pcy,
                              IT pdx, IT pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIEE_exact(const GenericPoint3T<IT, ET> &p1,
                           const GenericPoint3T<IT, ET> &p2, ET pcx, ET pcy,
                           ET pdx, ET pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, double pcx,
                               double pcy, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIEE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2, double pcx, double pcy,
                     double pdx, double pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIEE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &pc,
                     const GenericPoint3T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCirclexy_IIIE_interval(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3, IT pdx, IT pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIIE_exact(const GenericPoint3T<IT, ET> &p1,
                           const GenericPoint3T<IT, ET> &p2,
                           const GenericPoint3T<IT, ET> &p3, ET pdx, ET pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3, double pdx,
                               double pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIIE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &p3, double pdx, double pdy);

template <typename IT, typename ET>
Sign inCirclexy_IIIE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &p3,
                     const GenericPoint3T<IT, ET> &pd);

template <typename IT, typename ET>
Sign inCirclexy_IIII_interval(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3,
                              const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCirclexy_IIII_exact(const GenericPoint3T<IT, ET> &p1,
                           const GenericPoint3T<IT, ET> &p2,
                           const GenericPoint3T<IT, ET> &p3,
                           const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCirclexy_IIII_expansion(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3,
                               const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign inCirclexy_IIII(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &p3,
                     const GenericPoint3T<IT, ET> &p4);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline Sign inCircle(const double *a, const double *b, const double *c,
                     const double *d)
{
#ifdef OMC_NO_SHEWCHUK
	return inCircle(a[0], a[1], b[0], b[1], c[0], c[1], d[0], d[1]);
#else
	return OMC::sign(::incircle(a, b, c, d));
#endif
}

template <typename IT, typename ET>
Sign inCircle(const GenericPoint2T<IT, ET> &a, const GenericPoint2T<IT, ET> &b,
              const GenericPoint2T<IT, ET> &c, const GenericPoint2T<IT, ET> &d)
{
#ifdef OMC_NO_SHEWCHUK
	return inCircle(a.x(), a.y(), b.x(), b.y(), c.x(), c.y(), d.x(), d.y());
#else
	return OMC::sign(::incircle(a.data(), b.data(), c.data(), d.data()));
#endif
}

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

inline Sign inCircle_filtered(double pax, double pay, double pbx, double pby,
                              double pcx, double pcy, double pdx, double pdy)
{
	double adx    = pax - pdx;
	double ady    = pay - pdy;
	double bdx    = pbx - pdx;
	double bdy    = pby - pdy;
	double cdx    = pcx - pdx;
	double cdy    = pcy - pdy;
	double abdeta = adx * bdy;
	double abdetb = bdx * ady;
	double abdet  = abdeta - abdetb;
	double bcdeta = bdx * cdy;
	double bcdetb = cdx * bdy;
	double bcdet  = bcdeta - bcdetb;
	double cadeta = cdx * ady;
	double cadetb = adx * cdy;
	double cadet  = cadeta - cadetb;
	double alifta = adx * adx;
	double aliftb = ady * ady;
	double alift  = alifta + aliftb;
	double blifta = bdx * bdx;
	double bliftb = bdy * bdy;
	double blift  = blifta + bliftb;
	double clifta = cdx * cdx;
	double cliftb = cdy * cdy;
	double clift  = clifta + cliftb;
	double la     = alift * bcdet;
	double lb     = blift * cadet;
	double lc     = clift * abdet;
	double lab    = la + lb;
	double L      = lab + lc;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(adx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ady)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bdx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bdy)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cdx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cdy)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= epsilon;
	epsilon *= 1.3766765505351944e-14;

	return filter_sign(L, epsilon);
}

template <typename IT>
Sign inCircle_interval(IT pax, IT pay, IT pbx, IT pby, IT pcx, IT pcy, IT pdx,
                       IT pdy)
{
	typename IT::Protector P;

	IT adx    = pax - pdx;
	IT ady    = pay - pdy;
	IT bdx    = pbx - pdx;
	IT bdy    = pby - pdy;
	IT cdx    = pcx - pdx;
	IT cdy    = pcy - pdy;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT alift  = alifta + aliftb;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT blift  = blifta + bliftb;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT clift  = clifta + cliftb;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab    = la + lb;
	IT L      = lab + lc;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename ET>
Sign inCircle_exact(ET pax, ET pay, ET pbx, ET pby, ET pcx, ET pcy, ET pdx,
                    ET pdy)
{
	ET adx    = pax - pdx;
	ET ady    = pay - pdy;
	ET bdx    = pbx - pdx;
	ET bdy    = pby - pdy;
	ET cdx    = pcx - pdx;
	ET cdy    = pcy - pdy;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET alift  = alifta + aliftb;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET blift  = blifta + bliftb;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET clift  = clifta + cliftb;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab    = la + lb;
	ET L      = lab + lc;
	return OMC::sign(L);
}

Sign inCircle_expansion(double pax, double pay, double pbx, double pby,
                        double pcx, double pcy, double pdx, double pdy)
{
	expansionObject o;
	double          adx[2];
	o.Two_Diff(pax, pdx, adx);
	double ady[2];
	o.Two_Diff(pay, pdy, ady);
	double bdx[2];
	o.Two_Diff(pbx, pdx, bdx);
	double bdy[2];
	o.Two_Diff(pby, pdy, bdy);
	double cdx[2];
	o.Two_Diff(pcx, pdx, cdx);
	double cdy[2];
	o.Two_Diff(pcy, pdy, cdy);
	double abdeta[8];
	int    abdeta_len = o.Gen_Product(2, adx, 2, bdy, abdeta);
	double abdetb[8];
	int    abdetb_len = o.Gen_Product(2, bdx, 2, ady, abdetb);
	double abdet[16];
	int    abdet_len = o.Gen_Diff(abdeta_len, abdeta, abdetb_len, abdetb, abdet);
	double bcdeta[8];
	int    bcdeta_len = o.Gen_Product(2, bdx, 2, cdy, bcdeta);
	double bcdetb[8];
	int    bcdetb_len = o.Gen_Product(2, cdx, 2, bdy, bcdetb);
	double bcdet[16];
	int    bcdet_len = o.Gen_Diff(bcdeta_len, bcdeta, bcdetb_len, bcdetb, bcdet);
	double cadeta[8];
	int    cadeta_len = o.Gen_Product(2, cdx, 2, ady, cadeta);
	double cadetb[8];
	int    cadetb_len = o.Gen_Product(2, adx, 2, cdy, cadetb);
	double cadet[16];
	int    cadet_len = o.Gen_Diff(cadeta_len, cadeta, cadetb_len, cadetb, cadet);
	double alifta[8];
	int    alifta_len = o.Gen_Product(2, adx, 2, adx, alifta);
	double aliftb[8];
	int    aliftb_len = o.Gen_Product(2, ady, 2, ady, aliftb);
	double alift[16];
	int    alift_len = o.Gen_Sum(alifta_len, alifta, aliftb_len, aliftb, alift);
	double blifta[8];
	int    blifta_len = o.Gen_Product(2, bdx, 2, bdx, blifta);
	double bliftb[8];
	int    bliftb_len = o.Gen_Product(2, bdy, 2, bdy, bliftb);
	double blift[16];
	int    blift_len = o.Gen_Sum(blifta_len, blifta, bliftb_len, bliftb, blift);
	double clifta[8];
	int    clifta_len = o.Gen_Product(2, cdx, 2, cdx, clifta);
	double cliftb[8];
	int    cliftb_len = o.Gen_Product(2, cdy, 2, cdy, cliftb);
	double clift[16];
	int    clift_len = o.Gen_Sum(clifta_len, clifta, cliftb_len, cliftb, clift);
	double la_p[128], *la = la_p;
	int    la_len =
	  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 128);
	double lb_p[128], *lb = lb_p;
	int    lb_len =
	  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 128);
	double lc_p[128], *lc = lc_p;
	int    lc_len =
	  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 128);
	double lab_p[128], *lab = lab_p;
	int    lab_len = o.Gen_Sum_With_PreAlloc(la_len, la, lb_len, lb, &lab, 128);
	double L_p[128], *L = L_p;
	int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, lc_len, lc, &L, 128);

	double return_value = L[L_len - 1];
	if (L_p != L)
		FreeDoubles(L);
	if (lab_p != lab)
		FreeDoubles(lab);
	if (lc_p != lc)
		FreeDoubles(lc);
	if (lb_p != lb)
		FreeDoubles(lb);
	if (la_p != la)
		FreeDoubles(la);

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inCircle(double pax, double pay, double pbx, double pby, double pcx,
              double pcy, double pdx, double pdy)
{
	Sign ret;
	ret = inCircle_filtered(pax, pay, pbx, pby, pcx, pcy, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	ret = inCircle_interval<IT>(pax, pay, pbx, pby, pcx, pcy, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCircle_expansion(pax, pay, pbx, pby, pcx, pcy, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCircle_IEEE_interval(const GenericPoint2T<IT, ET> &p1, IT pbx, IT pby,
                            IT pcx, IT pcy, IT pdx, IT pdy)
{
	IT l1x, l1y, d1;
	if (!p1.getIntervalLambda(l1x, l1y, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pdxt   = pdx * d1;
	IT pdyt   = pdy * d1;
	IT adx    = l1x - pdxt;
	IT ady    = l1y - pdyt;
	IT bdx    = pbx - pdx;
	IT bdy    = pby - pdy;
	IT cdx    = pcx - pdx;
	IT cdy    = pcy - pdy;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT alift  = alifta + aliftb;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT blift  = blifta + bliftb;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT clift  = clifta + cliftb;
	IT la     = alift * bcdet;
	IT lbt    = blift * cadet;
	IT lb     = lbt * d1;
	IT lct    = clift * abdet;
	IT lc     = lct * d1;
	IT lab    = la + lb;
	IT L      = lab + lc;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IEEE_exact(const GenericPoint2T<IT, ET> &p1, ET pbx, ET pby,
                         ET pcx, ET pcy, ET pdx, ET pdy)
{
	ET l1x, l1y, d1;
	p1.getExactLambda(l1x, l1y, d1);
	ET pdxt   = pdx * d1;
	ET pdyt   = pdy * d1;
	ET adx    = l1x - pdxt;
	ET ady    = l1y - pdyt;
	ET bdx    = pbx - pdx;
	ET bdy    = pby - pdy;
	ET cdx    = pcx - pdx;
	ET cdy    = pcy - pdy;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET alift  = alifta + aliftb;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET blift  = blifta + bliftb;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET clift  = clifta + cliftb;
	ET la     = alift * bcdet;
	ET lbt    = blift * cadet;
	ET lb     = lbt * d1;
	ET lct    = clift * abdet;
	ET lc     = lct * d1;
	ET lab    = la + lb;
	ET L      = lab + lc;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IEEE_expansion(const GenericPoint2T<IT, ET> &p1, double pbx,
                             double pby, double pcx, double pcy, double pdx,
                             double pdy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, d1_p[64], *d1 = d1_p;
	int    l1x_len = 64, l1y_len = 64, d1_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          pdxt_p[64], *pdxt = pdxt_p;
		int    pdxt_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdx, &pdxt, 64);
		double pdyt_p[64], *pdyt = pdyt_p;
		int    pdyt_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdy, &pdyt, 64);
		double adx_p[64], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pdxt_len, pdxt, &adx, 64);
		double ady_p[64], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, pdyt_len, pdyt, &ady, 64);
		double bdx[2];
		o.Two_Diff(pbx, pdx, bdx);
		double bdy[2];
		o.Two_Diff(pby, pdy, bdy);
		double cdx[2];
		o.Two_Diff(pcx, pdx, cdx);
		double cdy[2];
		o.Two_Diff(pcy, pdy, cdy);
		double abdeta_p[64], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, 2, bdy, &abdeta, 64);
		double abdetb_p[64], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(2, bdx, ady_len, ady, &abdetb, 64);
		double abdet_p[64], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 64);
		double bcdeta[8];
		int    bcdeta_len = o.Gen_Product(2, bdx, 2, cdy, bcdeta);
		double bcdetb[8];
		int    bcdetb_len = o.Gen_Product(2, cdx, 2, bdy, bcdetb);
		double bcdet[16];
		int bcdet_len = o.Gen_Diff(bcdeta_len, bcdeta, bcdetb_len, bcdetb, bcdet);
		double cadeta_p[64], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(2, cdx, ady_len, ady, &cadeta, 64);
		double cadetb_p[64], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, 2, cdy, &cadetb, 64);
		double cadet_p[64], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 64);
		double alifta_p[64], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 64);
		double aliftb_p[64], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 64);
		double alift_p[64], *alift = alift_p;
		int    alift_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                           aliftb, &alift, 64);
		double blifta[8];
		int    blifta_len = o.Gen_Product(2, bdx, 2, bdx, blifta);
		double bliftb[8];
		int    bliftb_len = o.Gen_Product(2, bdy, 2, bdy, bliftb);
		double blift[16];
		int    blift_len = o.Gen_Sum(blifta_len, blifta, bliftb_len, bliftb, blift);
		double clifta[8];
		int    clifta_len = o.Gen_Product(2, cdx, 2, cdx, clifta);
		double cliftb[8];
		int    cliftb_len = o.Gen_Product(2, cdy, 2, cdy, cliftb);
		double clift[16];
		int    clift_len = o.Gen_Sum(clifta_len, clifta, cliftb_len, cliftb, clift);
		double la_p[64], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 64);
		double lbt_p[64], *lbt = lbt_p;
		int    lbt_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lbt, 64);
		double lb_p[64], *lb = lb_p;
		int lb_len = o.Gen_Product_With_PreAlloc(lbt_len, lbt, d1_len, d1, &lb, 64);
		double lct_p[64], *lct = lct_p;
		int    lct_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lct, 64);
		double lc_p[64], *lc = lc_p;
		int lc_len = o.Gen_Product_With_PreAlloc(lct_len, lct, d1_len, d1, &lc, 64);
		double lab_p[64], *lab = lab_p;
		int    lab_len = o.Gen_Sum_With_PreAlloc(la_len, la, lb_len, lb, &lab, 64);
		double L_p[64], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, lc_len, lc, &L, 64);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lct_p != lct)
			FreeDoubles(lct);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (lbt_p != lbt)
			FreeDoubles(lbt);
		if (la_p != la)
			FreeDoubles(la);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (pdyt_p != pdyt)
			FreeDoubles(pdyt);
		if (pdxt_p != pdxt)
			FreeDoubles(pdxt);
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
		return inCircle_IEEE_exact<IT, ET>(p1, pbx, pby, pcx, pcy, pdx, pdy);
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
Sign inCircle_IEEE(const GenericPoint2T<IT, ET> &p1, double pbx, double pby,
                   double pcx, double pcy, double pdx, double pdy)
{
	Sign ret;
	ret = inCircle_IEEE_interval<IT, ET>(p1, pbx, pby, pcx, pcy, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCircle_IEEE_expansion<IT, ET>(p1, pbx, pby, pcx, pcy, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCircle_IEEE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &pb,
                   const GenericPoint2T<IT, ET> &pc,
                   const GenericPoint2T<IT, ET> &pd)
{
	return inCircle_IEEE<IT, ET>(p1, pb.x(), pb.y(), pc.x(), pc.y(), pd.x(),
	                             pd.y());
}

template <typename IT, typename ET>
Sign inCircle_IIEE_interval(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2, IT pcx, IT pcy,
                            IT pdx, IT pdy)
{
	IT l1x, l1y, d1, l2x, l2y, d2;
	if (!p1.getIntervalLambda(l1x, l1y, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pdx1   = pdx * d1;
	IT pdy1   = pdy * d1;
	IT adx    = l1x - pdx1;
	IT ady    = l1y - pdy1;
	IT pdx2   = pdx * d2;
	IT pdy2   = pdy * d2;
	IT bdx    = l2x - pdx2;
	IT bdy    = l2y - pdy2;
	IT cdx    = pcx - pdx;
	IT cdy    = pcy - pdy;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT aliftt = alifta + aliftb;
	IT alift  = aliftt * d2;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT blift  = blifta + bliftb;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT cliftt = clifta + cliftb;
	IT clift  = cliftt * d2;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab    = lc + lb;
	IT lab2   = lab * d1;
	IT L      = lab2 + la;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IIEE_exact(const GenericPoint2T<IT, ET> &p1,
                         const GenericPoint2T<IT, ET> &p2, ET pcx, ET pcy,
                         ET pdx, ET pdy)
{
	ET l1x, l1y, d1, l2x, l2y, d2;
	p1.getExactLambda(l1x, l1y, d1);
	p2.getExactLambda(l2x, l2y, d2);
	ET pdx1   = pdx * d1;
	ET pdy1   = pdy * d1;
	ET adx    = l1x - pdx1;
	ET ady    = l1y - pdy1;
	ET pdx2   = pdx * d2;
	ET pdy2   = pdy * d2;
	ET bdx    = l2x - pdx2;
	ET bdy    = l2y - pdy2;
	ET cdx    = pcx - pdx;
	ET cdy    = pcy - pdy;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET aliftt = alifta + aliftb;
	ET alift  = aliftt * d2;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET blift  = blifta + bliftb;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET cliftt = clifta + cliftb;
	ET clift  = cliftt * d2;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab    = lc + lb;
	ET lab2   = lab * d1;
	ET L      = lab2 + la;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IIEE_expansion(const GenericPoint2T<IT, ET> &p1,
                             const GenericPoint2T<IT, ET> &p2, double pcx,
                             double pcy, double pdx, double pdy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[32], *l1x = l1x_p, l1y_p[32], *l1y = l1y_p, d1_p[32], *d1 = d1_p,
	                  l2x_p[32], *l2x = l2x_p, l2y_p[32], *l2y = l2y_p, d2_p[32],
	                  *d2 = d2_p;
	int l1x_len = 32, l1y_len = 32, d1_len = 32, l2x_len = 32, l2y_len = 32,
	    d2_len = 32;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &d2, d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          pdx1_p[32], *pdx1 = pdx1_p;
		int    pdx1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdx, &pdx1, 32);
		double pdy1_p[32], *pdy1 = pdy1_p;
		int    pdy1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdy, &pdy1, 32);
		double adx_p[32], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pdx1_len, pdx1, &adx, 32);
		double ady_p[32], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, pdy1_len, pdy1, &ady, 32);
		double pdx2_p[32], *pdx2 = pdx2_p;
		int    pdx2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdx, &pdx2, 32);
		double pdy2_p[32], *pdy2 = pdy2_p;
		int    pdy2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdy, &pdy2, 32);
		double bdx_p[32], *bdx = bdx_p;
		int    bdx_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pdx2_len, pdx2, &bdx, 32);
		double bdy_p[32], *bdy = bdy_p;
		int    bdy_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, pdy2_len, pdy2, &bdy, 32);
		double cdx[2];
		o.Two_Diff(pcx, pdx, cdx);
		double cdy[2];
		o.Two_Diff(pcy, pdy, cdy);
		double abdeta_p[32], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, bdy_len, bdy, &abdeta, 32);
		double abdetb_p[32], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, ady_len, ady, &abdetb, 32);
		double abdet_p[32], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 32);
		double bcdeta_p[32], *bcdeta = bcdeta_p;
		int    bcdeta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, 2, cdy, &bcdeta, 32);
		double bcdetb_p[32], *bcdetb = bcdetb_p;
		int    bcdetb_len =
		  o.Gen_Product_With_PreAlloc(2, cdx, bdy_len, bdy, &bcdetb, 32);
		double bcdet_p[32], *bcdet = bcdet_p;
		int    bcdet_len = o.Gen_Diff_With_PreAlloc(bcdeta_len, bcdeta, bcdetb_len,
		                                            bcdetb, &bcdet, 32);
		double cadeta_p[32], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(2, cdx, ady_len, ady, &cadeta, 32);
		double cadetb_p[32], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, 2, cdy, &cadetb, 32);
		double cadet_p[32], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 32);
		double alifta_p[32], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 32);
		double aliftb_p[32], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 32);
		double aliftt_p[32], *aliftt = aliftt_p;
		int    aliftt_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                            aliftb, &aliftt, 32);
		double alift_p[32], *alift = alift_p;
		int    alift_len =
		  o.Gen_Product_With_PreAlloc(aliftt_len, aliftt, d2_len, d2, &alift, 32);
		double blifta_p[32], *blifta = blifta_p;
		int    blifta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, bdx_len, bdx, &blifta, 32);
		double bliftb_p[32], *bliftb = bliftb_p;
		int    bliftb_len =
		  o.Gen_Product_With_PreAlloc(bdy_len, bdy, bdy_len, bdy, &bliftb, 32);
		double blift_p[32], *blift = blift_p;
		int    blift_len = o.Gen_Sum_With_PreAlloc(blifta_len, blifta, bliftb_len,
		                                           bliftb, &blift, 32);
		double clifta[8];
		int    clifta_len = o.Gen_Product(2, cdx, 2, cdx, clifta);
		double cliftb[8];
		int    cliftb_len = o.Gen_Product(2, cdy, 2, cdy, cliftb);
		double cliftt[16];
		int cliftt_len = o.Gen_Sum(clifta_len, clifta, cliftb_len, cliftb, cliftt);
		double clift_p[32], *clift = clift_p;
		int    clift_len =
		  o.Gen_Product_With_PreAlloc(cliftt_len, cliftt, d2_len, d2, &clift, 32);
		double la_p[32], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 32);
		double lb_p[32], *lb = lb_p;
		int    lb_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 32);
		double lc_p[32], *lc = lc_p;
		int    lc_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 32);
		double lab_p[32], *lab = lab_p;
		int    lab_len = o.Gen_Sum_With_PreAlloc(lc_len, lc, lb_len, lb, &lab, 32);
		double lab2_p[32], *lab2 = lab2_p;
		int    lab2_len =
		  o.Gen_Product_With_PreAlloc(lab_len, lab, d1_len, d1, &lab2, 32);
		double L_p[32], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab2_len, lab2, la_len, la, &L, 32);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab2_p != lab2)
			FreeDoubles(lab2);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (la_p != la)
			FreeDoubles(la);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bliftb_p != bliftb)
			FreeDoubles(bliftb);
		if (blifta_p != blifta)
			FreeDoubles(blifta);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (aliftt_p != aliftt)
			FreeDoubles(aliftt);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (bcdet_p != bcdet)
			FreeDoubles(bcdet);
		if (bcdetb_p != bcdetb)
			FreeDoubles(bcdetb);
		if (bcdeta_p != bcdeta)
			FreeDoubles(bcdeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (bdy_p != bdy)
			FreeDoubles(bdy);
		if (bdx_p != bdx)
			FreeDoubles(bdx);
		if (pdy2_p != pdy2)
			FreeDoubles(pdy2);
		if (pdx2_p != pdx2)
			FreeDoubles(pdx2);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (pdy1_p != pdy1)
			FreeDoubles(pdy1);
		if (pdx1_p != pdx1)
			FreeDoubles(pdx1);
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
		return inCircle_IIEE_exact<IT, ET>(p1, p2, pcx, pcy, pdx, pdy);
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
Sign inCircle_IIEE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2, double pcx, double pcy,
                   double pdx, double pdy)
{
	Sign ret;
	ret = inCircle_IIEE_interval<IT, ET>(p1, p2, pcx, pcy, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCircle_IIEE_expansion<IT, ET>(p1, p2, pcx, pcy, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCircle_IIEE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &pc,
                   const GenericPoint2T<IT, ET> &pd)
{
	return inCircle_IIEE<IT, ET>(p1, p2, pc.x(), pc.y(), pd.x(), pd.y());
}

template <typename IT, typename ET>
Sign inCircle_IIIE_interval(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2,
                            const GenericPoint2T<IT, ET> &p3, IT pdx, IT pdy)
{
	IT l1x, l1y, d1, l2x, l2y, d2, l3x, l3y, d3;
	if (!p1.getIntervalLambda(l1x, l1y, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pdx1   = pdx * d1;
	IT pdy1   = pdy * d1;
	IT adx    = l1x - pdx1;
	IT ady    = l1y - pdy1;
	IT pdx2   = pdx * d2;
	IT pdy2   = pdy * d2;
	IT bdx    = l2x - pdx2;
	IT bdy    = l2y - pdy2;
	IT pdx3   = pdx * d3;
	IT pdy3   = pdy * d3;
	IT cdx    = l3x - pdx3;
	IT cdy    = l3y - pdy3;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT aliftt = alifta + aliftb;
	IT alift2 = aliftt * d2;
	IT alift  = alift2 * d3;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT bliftt = blifta + bliftb;
	IT blift  = bliftt * d3;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT cliftt = clifta + cliftb;
	IT clift  = cliftt * d2;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab2   = lc + lb;
	IT lab    = lab2 * d1;
	IT L      = lab + la;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IIIE_exact(const GenericPoint2T<IT, ET> &p1,
                         const GenericPoint2T<IT, ET> &p2,
                         const GenericPoint2T<IT, ET> &p3, ET pdx, ET pdy)
{
	ET l1x, l1y, d1, l2x, l2y, d2, l3x, l3y, d3;
	p1.getExactLambda(l1x, l1y, d1);
	p2.getExactLambda(l2x, l2y, d2);
	p3.getExactLambda(l3x, l3y, d3);
	ET pdx1   = pdx * d1;
	ET pdy1   = pdy * d1;
	ET adx    = l1x - pdx1;
	ET ady    = l1y - pdy1;
	ET pdx2   = pdx * d2;
	ET pdy2   = pdy * d2;
	ET bdx    = l2x - pdx2;
	ET bdy    = l2y - pdy2;
	ET pdx3   = pdx * d3;
	ET pdy3   = pdy * d3;
	ET cdx    = l3x - pdx3;
	ET cdy    = l3y - pdy3;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET aliftt = alifta + aliftb;
	ET alift2 = aliftt * d2;
	ET alift  = alift2 * d3;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET bliftt = blifta + bliftb;
	ET blift  = bliftt * d3;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET cliftt = clifta + cliftb;
	ET clift  = cliftt * d2;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab2   = lc + lb;
	ET lab    = lab2 * d1;
	ET L      = lab + la;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IIIE_expansion(const GenericPoint2T<IT, ET> &p1,
                             const GenericPoint2T<IT, ET> &p2,
                             const GenericPoint2T<IT, ET> &p3, double pdx,
                             double pdy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[32], *l1x = l1x_p, l1y_p[32], *l1y = l1y_p, d1_p[32], *d1 = d1_p,
	                  l2x_p[32], *l2x = l2x_p, l2y_p[32], *l2y = l2y_p, d2_p[32],
	                  *d2 = d2_p, l3x_p[32], *l3x = l3x_p, l3y_p[32],
	                  *l3y = l3y_p, d3_p[32], *d3 = d3_p;
	int l1x_len = 32, l1y_len = 32, d1_len = 32, l2x_len = 32, l2y_len = 32,
	    d2_len = 32, l3x_len = 32, l3y_len = 32, d3_len = 32;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &d2, d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &d3, d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          pdx1_p[32], *pdx1 = pdx1_p;
		int    pdx1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdx, &pdx1, 32);
		double pdy1_p[32], *pdy1 = pdy1_p;
		int    pdy1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdy, &pdy1, 32);
		double adx_p[32], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pdx1_len, pdx1, &adx, 32);
		double ady_p[32], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, pdy1_len, pdy1, &ady, 32);
		double pdx2_p[32], *pdx2 = pdx2_p;
		int    pdx2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdx, &pdx2, 32);
		double pdy2_p[32], *pdy2 = pdy2_p;
		int    pdy2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdy, &pdy2, 32);
		double bdx_p[32], *bdx = bdx_p;
		int    bdx_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pdx2_len, pdx2, &bdx, 32);
		double bdy_p[32], *bdy = bdy_p;
		int    bdy_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, pdy2_len, pdy2, &bdy, 32);
		double pdx3_p[32], *pdx3 = pdx3_p;
		int    pdx3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pdx, &pdx3, 32);
		double pdy3_p[32], *pdy3 = pdy3_p;
		int    pdy3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pdy, &pdy3, 32);
		double cdx_p[32], *cdx = cdx_p;
		int    cdx_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, pdx3_len, pdx3, &cdx, 32);
		double cdy_p[32], *cdy = cdy_p;
		int    cdy_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, pdy3_len, pdy3, &cdy, 32);
		double abdeta_p[32], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, bdy_len, bdy, &abdeta, 32);
		double abdetb_p[32], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, ady_len, ady, &abdetb, 32);
		double abdet_p[32], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 32);
		double bcdeta_p[32], *bcdeta = bcdeta_p;
		int    bcdeta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, cdy_len, cdy, &bcdeta, 32);
		double bcdetb_p[32], *bcdetb = bcdetb_p;
		int    bcdetb_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, bdy_len, bdy, &bcdetb, 32);
		double bcdet_p[32], *bcdet = bcdet_p;
		int    bcdet_len = o.Gen_Diff_With_PreAlloc(bcdeta_len, bcdeta, bcdetb_len,
		                                            bcdetb, &bcdet, 32);
		double cadeta_p[32], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, ady_len, ady, &cadeta, 32);
		double cadetb_p[32], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, cdy_len, cdy, &cadetb, 32);
		double cadet_p[32], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 32);
		double alifta_p[32], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 32);
		double aliftb_p[32], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 32);
		double aliftt_p[32], *aliftt = aliftt_p;
		int    aliftt_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                            aliftb, &aliftt, 32);
		double alift2_p[32], *alift2 = alift2_p;
		int    alift2_len =
		  o.Gen_Product_With_PreAlloc(aliftt_len, aliftt, d2_len, d2, &alift2, 32);
		double alift_p[32], *alift = alift_p;
		int    alift_len =
		  o.Gen_Product_With_PreAlloc(alift2_len, alift2, d3_len, d3, &alift, 32);
		double blifta_p[32], *blifta = blifta_p;
		int    blifta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, bdx_len, bdx, &blifta, 32);
		double bliftb_p[32], *bliftb = bliftb_p;
		int    bliftb_len =
		  o.Gen_Product_With_PreAlloc(bdy_len, bdy, bdy_len, bdy, &bliftb, 32);
		double bliftt_p[32], *bliftt = bliftt_p;
		int    bliftt_len = o.Gen_Sum_With_PreAlloc(blifta_len, blifta, bliftb_len,
		                                            bliftb, &bliftt, 32);
		double blift_p[32], *blift = blift_p;
		int    blift_len =
		  o.Gen_Product_With_PreAlloc(bliftt_len, bliftt, d3_len, d3, &blift, 32);
		double clifta_p[32], *clifta = clifta_p;
		int    clifta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, cdx_len, cdx, &clifta, 32);
		double cliftb_p[32], *cliftb = cliftb_p;
		int    cliftb_len =
		  o.Gen_Product_With_PreAlloc(cdy_len, cdy, cdy_len, cdy, &cliftb, 32);
		double cliftt_p[32], *cliftt = cliftt_p;
		int    cliftt_len = o.Gen_Sum_With_PreAlloc(clifta_len, clifta, cliftb_len,
		                                            cliftb, &cliftt, 32);
		double clift_p[32], *clift = clift_p;
		int    clift_len =
		  o.Gen_Product_With_PreAlloc(cliftt_len, cliftt, d2_len, d2, &clift, 32);
		double la_p[32], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 32);
		double lb_p[32], *lb = lb_p;
		int    lb_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 32);
		double lc_p[32], *lc = lc_p;
		int    lc_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 32);
		double lab2_p[32], *lab2 = lab2_p;
		int lab2_len = o.Gen_Sum_With_PreAlloc(lc_len, lc, lb_len, lb, &lab2, 32);
		double lab_p[32], *lab = lab_p;
		int    lab_len =
		  o.Gen_Product_With_PreAlloc(lab2_len, lab2, d1_len, d1, &lab, 32);
		double L_p[32], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, la_len, la, &L, 32);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lab2_p != lab2)
			FreeDoubles(lab2);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (la_p != la)
			FreeDoubles(la);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cliftt_p != cliftt)
			FreeDoubles(cliftt);
		if (cliftb_p != cliftb)
			FreeDoubles(cliftb);
		if (clifta_p != clifta)
			FreeDoubles(clifta);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bliftt_p != bliftt)
			FreeDoubles(bliftt);
		if (bliftb_p != bliftb)
			FreeDoubles(bliftb);
		if (blifta_p != blifta)
			FreeDoubles(blifta);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (alift2_p != alift2)
			FreeDoubles(alift2);
		if (aliftt_p != aliftt)
			FreeDoubles(aliftt);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (bcdet_p != bcdet)
			FreeDoubles(bcdet);
		if (bcdetb_p != bcdetb)
			FreeDoubles(bcdetb);
		if (bcdeta_p != bcdeta)
			FreeDoubles(bcdeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (cdy_p != cdy)
			FreeDoubles(cdy);
		if (cdx_p != cdx)
			FreeDoubles(cdx);
		if (pdy3_p != pdy3)
			FreeDoubles(pdy3);
		if (pdx3_p != pdx3)
			FreeDoubles(pdx3);
		if (bdy_p != bdy)
			FreeDoubles(bdy);
		if (bdx_p != bdx)
			FreeDoubles(bdx);
		if (pdy2_p != pdy2)
			FreeDoubles(pdy2);
		if (pdx2_p != pdx2)
			FreeDoubles(pdx2);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (pdy1_p != pdy1)
			FreeDoubles(pdy1);
		if (pdx1_p != pdx1)
			FreeDoubles(pdx1);
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
		return inCircle_IIIE_exact<IT, ET>(p1, p2, p3, pdx, pdy);
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
Sign inCircle_IIIE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &p3, double pdx, double pdy)
{
	Sign ret;
	ret = inCircle_IIIE_interval<IT, ET>(p1, p2, p3, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCircle_IIIE_expansion<IT, ET>(p1, p2, p3, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCircle_IIIE(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &p3,
                   const GenericPoint2T<IT, ET> &pd)
{
	return inCircle_IIIE<IT, ET>(p1, p2, p3, pd.x(), pd.y());
}

template <typename IT, typename ET>
Sign inCircle_IIII_interval(const GenericPoint2T<IT, ET> &p1,
                            const GenericPoint2T<IT, ET> &p2,
                            const GenericPoint2T<IT, ET> &p3,
                            const GenericPoint2T<IT, ET> &p4)
{
	IT l1x, l1y, d1, l2x, l2y, d2, l3x, l3y, d3, l4x, l4y, d4;
	if (!p1.getIntervalLambda(l1x, l1y, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, d3) ||
	    !p4.getIntervalLambda(l4x, l4y, d4))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT l1xt   = l1x * d4;
	IT l1yt   = l1y * d4;
	IT l2xt   = l2x * d4;
	IT l2yt   = l2y * d4;
	IT l3xt   = l3x * d4;
	IT l3yt   = l3y * d4;
	IT l4x1   = l4x * d1;
	IT l4y1   = l4y * d1;
	IT adx    = l1xt - l4x1;
	IT ady    = l1yt - l4y1;
	IT l4x2   = l4x * d2;
	IT l4y2   = l4y * d2;
	IT bdx    = l2xt - l4x2;
	IT bdy    = l2yt - l4y2;
	IT l4x3   = l4x * d3;
	IT l4y3   = l4y * d3;
	IT cdx    = l3xt - l4x3;
	IT cdy    = l3yt - l4y3;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT aliftt = alifta + aliftb;
	IT alift2 = aliftt * d2;
	IT alift  = alift2 * d3;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT bliftt = blifta + bliftb;
	IT blift  = bliftt * d3;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT cliftt = clifta + cliftb;
	IT clift  = cliftt * d2;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab2   = lc + lb;
	IT lab    = lab2 * d1;
	IT L      = lab + la;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IIII_exact(const GenericPoint2T<IT, ET> &p1,
                         const GenericPoint2T<IT, ET> &p2,
                         const GenericPoint2T<IT, ET> &p3,
                         const GenericPoint2T<IT, ET> &p4)
{
	ET l1x, l1y, d1, l2x, l2y, d2, l3x, l3y, d3, l4x, l4y, d4;
	p1.getExactLambda(l1x, l1y, d1);
	p2.getExactLambda(l2x, l2y, d2);
	p3.getExactLambda(l3x, l3y, d3);
	p4.getExactLambda(l4x, l4y, d4);
	ET l1xt   = l1x * d4;
	ET l1yt   = l1y * d4;
	ET l2xt   = l2x * d4;
	ET l2yt   = l2y * d4;
	ET l3xt   = l3x * d4;
	ET l3yt   = l3y * d4;
	ET l4x1   = l4x * d1;
	ET l4y1   = l4y * d1;
	ET adx    = l1xt - l4x1;
	ET ady    = l1yt - l4y1;
	ET l4x2   = l4x * d2;
	ET l4y2   = l4y * d2;
	ET bdx    = l2xt - l4x2;
	ET bdy    = l2yt - l4y2;
	ET l4x3   = l4x * d3;
	ET l4y3   = l4y * d3;
	ET cdx    = l3xt - l4x3;
	ET cdy    = l3yt - l4y3;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET aliftt = alifta + aliftb;
	ET alift2 = aliftt * d2;
	ET alift  = alift2 * d3;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET bliftt = blifta + bliftb;
	ET blift  = bliftt * d3;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET cliftt = clifta + cliftb;
	ET clift  = cliftt * d2;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab2   = lc + lb;
	ET lab    = lab2 * d1;
	ET L      = lab + la;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCircle_IIII_expansion(const GenericPoint2T<IT, ET> &p1,
                             const GenericPoint2T<IT, ET> &p2,
                             const GenericPoint2T<IT, ET> &p3,
                             const GenericPoint2T<IT, ET> &p4)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[32], *l1x = l1x_p, l1y_p[32], *l1y = l1y_p, d1_p[32], *d1 = d1_p,
	                  l2x_p[32], *l2x = l2x_p, l2y_p[32], *l2y = l2y_p, d2_p[32],
	                  *d2 = d2_p, l3x_p[32], *l3x = l3x_p, l3y_p[32],
	                  *l3y = l3y_p, d3_p[32], *d3 = d3_p, l4x_p[32], *l4x = l4x_p,
	                  l4y_p[32], *l4y = l4y_p, d4_p[32], *d4 = d4_p;
	int l1x_len = 32, l1y_len = 32, d1_len = 32, l2x_len = 32, l2y_len = 32,
	    d2_len = 32, l3x_len = 32, l3y_len = 32, d3_len = 32, l4x_len = 32,
	    l4y_len = 32, d4_len = 32;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &d1, d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &d2, d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &d3, d3_len);
	p4.getExpansionLambda(&l4x, l4x_len, &l4y, l4y_len, &d4, d4_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0) &&
	    (d4[d4_len - 1] != 0))
	{
		expansionObject o;
		double          l1xt_p[32], *l1xt = l1xt_p;
		int             l1xt_len =
		  o.Gen_Product_With_PreAlloc(l1x_len, l1x, d4_len, d4, &l1xt, 32);
		double l1yt_p[32], *l1yt = l1yt_p;
		int    l1yt_len =
		  o.Gen_Product_With_PreAlloc(l1y_len, l1y, d4_len, d4, &l1yt, 32);
		double l2xt_p[32], *l2xt = l2xt_p;
		int    l2xt_len =
		  o.Gen_Product_With_PreAlloc(l2x_len, l2x, d4_len, d4, &l2xt, 32);
		double l2yt_p[32], *l2yt = l2yt_p;
		int    l2yt_len =
		  o.Gen_Product_With_PreAlloc(l2y_len, l2y, d4_len, d4, &l2yt, 32);
		double l3xt_p[32], *l3xt = l3xt_p;
		int    l3xt_len =
		  o.Gen_Product_With_PreAlloc(l3x_len, l3x, d4_len, d4, &l3xt, 32);
		double l3yt_p[32], *l3yt = l3yt_p;
		int    l3yt_len =
		  o.Gen_Product_With_PreAlloc(l3y_len, l3y, d4_len, d4, &l3yt, 32);
		double l4x1_p[32], *l4x1 = l4x1_p;
		int    l4x1_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d1_len, d1, &l4x1, 32);
		double l4y1_p[32], *l4y1 = l4y1_p;
		int    l4y1_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d1_len, d1, &l4y1, 32);
		double adx_p[32], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1xt_len, l1xt, l4x1_len, l4x1, &adx, 32);
		double ady_p[32], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1yt_len, l1yt, l4y1_len, l4y1, &ady, 32);
		double l4x2_p[32], *l4x2 = l4x2_p;
		int    l4x2_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d2_len, d2, &l4x2, 32);
		double l4y2_p[32], *l4y2 = l4y2_p;
		int    l4y2_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d2_len, d2, &l4y2, 32);
		double bdx_p[32], *bdx = bdx_p;
		int    bdx_len =
		  o.Gen_Diff_With_PreAlloc(l2xt_len, l2xt, l4x2_len, l4x2, &bdx, 32);
		double bdy_p[32], *bdy = bdy_p;
		int    bdy_len =
		  o.Gen_Diff_With_PreAlloc(l2yt_len, l2yt, l4y2_len, l4y2, &bdy, 32);
		double l4x3_p[32], *l4x3 = l4x3_p;
		int    l4x3_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d3_len, d3, &l4x3, 32);
		double l4y3_p[32], *l4y3 = l4y3_p;
		int    l4y3_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d3_len, d3, &l4y3, 32);
		double cdx_p[32], *cdx = cdx_p;
		int    cdx_len =
		  o.Gen_Diff_With_PreAlloc(l3xt_len, l3xt, l4x3_len, l4x3, &cdx, 32);
		double cdy_p[32], *cdy = cdy_p;
		int    cdy_len =
		  o.Gen_Diff_With_PreAlloc(l3yt_len, l3yt, l4y3_len, l4y3, &cdy, 32);
		double abdeta_p[32], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, bdy_len, bdy, &abdeta, 32);
		double abdetb_p[32], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, ady_len, ady, &abdetb, 32);
		double abdet_p[32], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 32);
		double bcdeta_p[32], *bcdeta = bcdeta_p;
		int    bcdeta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, cdy_len, cdy, &bcdeta, 32);
		double bcdetb_p[32], *bcdetb = bcdetb_p;
		int    bcdetb_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, bdy_len, bdy, &bcdetb, 32);
		double bcdet_p[32], *bcdet = bcdet_p;
		int    bcdet_len = o.Gen_Diff_With_PreAlloc(bcdeta_len, bcdeta, bcdetb_len,
		                                            bcdetb, &bcdet, 32);
		double cadeta_p[32], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, ady_len, ady, &cadeta, 32);
		double cadetb_p[32], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, cdy_len, cdy, &cadetb, 32);
		double cadet_p[32], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 32);
		double alifta_p[32], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 32);
		double aliftb_p[32], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 32);
		double aliftt_p[32], *aliftt = aliftt_p;
		int    aliftt_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                            aliftb, &aliftt, 32);
		double alift2_p[32], *alift2 = alift2_p;
		int    alift2_len =
		  o.Gen_Product_With_PreAlloc(aliftt_len, aliftt, d2_len, d2, &alift2, 32);
		double alift_p[32], *alift = alift_p;
		int    alift_len =
		  o.Gen_Product_With_PreAlloc(alift2_len, alift2, d3_len, d3, &alift, 32);
		double blifta_p[32], *blifta = blifta_p;
		int    blifta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, bdx_len, bdx, &blifta, 32);
		double bliftb_p[32], *bliftb = bliftb_p;
		int    bliftb_len =
		  o.Gen_Product_With_PreAlloc(bdy_len, bdy, bdy_len, bdy, &bliftb, 32);
		double bliftt_p[32], *bliftt = bliftt_p;
		int    bliftt_len = o.Gen_Sum_With_PreAlloc(blifta_len, blifta, bliftb_len,
		                                            bliftb, &bliftt, 32);
		double blift_p[32], *blift = blift_p;
		int    blift_len =
		  o.Gen_Product_With_PreAlloc(bliftt_len, bliftt, d3_len, d3, &blift, 32);
		double clifta_p[32], *clifta = clifta_p;
		int    clifta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, cdx_len, cdx, &clifta, 32);
		double cliftb_p[32], *cliftb = cliftb_p;
		int    cliftb_len =
		  o.Gen_Product_With_PreAlloc(cdy_len, cdy, cdy_len, cdy, &cliftb, 32);
		double cliftt_p[32], *cliftt = cliftt_p;
		int    cliftt_len = o.Gen_Sum_With_PreAlloc(clifta_len, clifta, cliftb_len,
		                                            cliftb, &cliftt, 32);
		double clift_p[32], *clift = clift_p;
		int    clift_len =
		  o.Gen_Product_With_PreAlloc(cliftt_len, cliftt, d2_len, d2, &clift, 32);
		double la_p[32], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 32);
		double lb_p[32], *lb = lb_p;
		int    lb_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 32);
		double lc_p[32], *lc = lc_p;
		int    lc_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 32);
		double lab2_p[32], *lab2 = lab2_p;
		int lab2_len = o.Gen_Sum_With_PreAlloc(lc_len, lc, lb_len, lb, &lab2, 32);
		double lab_p[32], *lab = lab_p;
		int    lab_len =
		  o.Gen_Product_With_PreAlloc(lab2_len, lab2, d1_len, d1, &lab, 32);
		double L_p[32], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, la_len, la, &L, 32);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lab2_p != lab2)
			FreeDoubles(lab2);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (la_p != la)
			FreeDoubles(la);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cliftt_p != cliftt)
			FreeDoubles(cliftt);
		if (cliftb_p != cliftb)
			FreeDoubles(cliftb);
		if (clifta_p != clifta)
			FreeDoubles(clifta);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bliftt_p != bliftt)
			FreeDoubles(bliftt);
		if (bliftb_p != bliftb)
			FreeDoubles(bliftb);
		if (blifta_p != blifta)
			FreeDoubles(blifta);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (alift2_p != alift2)
			FreeDoubles(alift2);
		if (aliftt_p != aliftt)
			FreeDoubles(aliftt);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (bcdet_p != bcdet)
			FreeDoubles(bcdet);
		if (bcdetb_p != bcdetb)
			FreeDoubles(bcdetb);
		if (bcdeta_p != bcdeta)
			FreeDoubles(bcdeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (cdy_p != cdy)
			FreeDoubles(cdy);
		if (cdx_p != cdx)
			FreeDoubles(cdx);
		if (l4y3_p != l4y3)
			FreeDoubles(l4y3);
		if (l4x3_p != l4x3)
			FreeDoubles(l4x3);
		if (bdy_p != bdy)
			FreeDoubles(bdy);
		if (bdx_p != bdx)
			FreeDoubles(bdx);
		if (l4y2_p != l4y2)
			FreeDoubles(l4y2);
		if (l4x2_p != l4x2)
			FreeDoubles(l4x2);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (l4y1_p != l4y1)
			FreeDoubles(l4y1);
		if (l4x1_p != l4x1)
			FreeDoubles(l4x1);
		if (l3yt_p != l3yt)
			FreeDoubles(l3yt);
		if (l3xt_p != l3xt)
			FreeDoubles(l3xt);
		if (l2yt_p != l2yt)
			FreeDoubles(l2yt);
		if (l2xt_p != l2xt)
			FreeDoubles(l2xt);
		if (l1yt_p != l1yt)
			FreeDoubles(l1yt);
		if (l1xt_p != l1xt)
			FreeDoubles(l1xt);
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
		if (l4x_p != l4x)
			FreeDoubles(l4x);
		if (l4y_p != l4y)
			FreeDoubles(l4y);
		if (d4_p != d4)
			FreeDoubles(d4);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inCircle_IIII_exact<IT, ET>(p1, p2, p3, p4);
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
Sign inCircle_IIII(const GenericPoint2T<IT, ET> &p1,
                   const GenericPoint2T<IT, ET> &p2,
                   const GenericPoint2T<IT, ET> &p3,
                   const GenericPoint2T<IT, ET> &p4)
{
	Sign ret;
	ret = inCircle_IIII_interval<IT, ET>(p1, p2, p3, p4);
	if (is_sign_reliable(ret))
		return ret;
	return inCircle_IIII_expansion<IT, ET>(p1, p2, p3, p4);
}

template <typename IT, typename ET>
Sign inCirclexy_IEEE_interval(const GenericPoint3T<IT, ET> &p1, IT pbx, IT pby,
                              IT pcx, IT pcy, IT pdx, IT pdy)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pdxt   = pdx * d1;
	IT pdyt   = pdy * d1;
	IT adx    = l1x - pdxt;
	IT ady    = l1y - pdyt;
	IT bdx    = pbx - pdx;
	IT bdy    = pby - pdy;
	IT cdx    = pcx - pdx;
	IT cdy    = pcy - pdy;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT alift  = alifta + aliftb;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT blift  = blifta + bliftb;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT clift  = clifta + cliftb;
	IT la     = alift * bcdet;
	IT lbt    = blift * cadet;
	IT lb     = lbt * d1;
	IT lct    = clift * abdet;
	IT lc     = lct * d1;
	IT lab    = la + lb;
	IT L      = lab + lc;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IEEE_exact(const GenericPoint3T<IT, ET> &p1, ET pbx, ET pby,
                           ET pcx, ET pcy, ET pdx, ET pdy)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET pdxt   = pdx * d1;
	ET pdyt   = pdy * d1;
	ET adx    = l1x - pdxt;
	ET ady    = l1y - pdyt;
	ET bdx    = pbx - pdx;
	ET bdy    = pby - pdy;
	ET cdx    = pcx - pdx;
	ET cdy    = pcy - pdy;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET alift  = alifta + aliftb;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET blift  = blifta + bliftb;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET clift  = clifta + cliftb;
	ET la     = alift * bcdet;
	ET lbt    = blift * cadet;
	ET lb     = lbt * d1;
	ET lct    = clift * abdet;
	ET lc     = lct * d1;
	ET lab    = la + lb;
	ET L      = lab + lc;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IEEE_expansion(const GenericPoint3T<IT, ET> &p1, double pbx,
                               double pby, double pcx, double pcy, double pdx,
                               double pdy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[64], *l1x = l1x_p, l1y_p[64], *l1y = l1y_p, l1z_p[64],
	                  *l1z = l1z_p, d1_p[64], *d1 = d1_p;
	int l1x_len = 64, l1y_len = 64, l1z_len = 64, d1_len = 64;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          pdxt_p[64], *pdxt = pdxt_p;
		int    pdxt_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdx, &pdxt, 64);
		double pdyt_p[64], *pdyt = pdyt_p;
		int    pdyt_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdy, &pdyt, 64);
		double adx_p[64], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pdxt_len, pdxt, &adx, 64);
		double ady_p[64], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, pdyt_len, pdyt, &ady, 64);
		double bdx[2];
		o.Two_Diff(pbx, pdx, bdx);
		double bdy[2];
		o.Two_Diff(pby, pdy, bdy);
		double cdx[2];
		o.Two_Diff(pcx, pdx, cdx);
		double cdy[2];
		o.Two_Diff(pcy, pdy, cdy);
		double abdeta_p[64], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, 2, bdy, &abdeta, 64);
		double abdetb_p[64], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(2, bdx, ady_len, ady, &abdetb, 64);
		double abdet_p[64], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 64);
		double bcdeta[8];
		int    bcdeta_len = o.Gen_Product(2, bdx, 2, cdy, bcdeta);
		double bcdetb[8];
		int    bcdetb_len = o.Gen_Product(2, cdx, 2, bdy, bcdetb);
		double bcdet[16];
		int bcdet_len = o.Gen_Diff(bcdeta_len, bcdeta, bcdetb_len, bcdetb, bcdet);
		double cadeta_p[64], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(2, cdx, ady_len, ady, &cadeta, 64);
		double cadetb_p[64], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, 2, cdy, &cadetb, 64);
		double cadet_p[64], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 64);
		double alifta_p[64], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 64);
		double aliftb_p[64], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 64);
		double alift_p[64], *alift = alift_p;
		int    alift_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                           aliftb, &alift, 64);
		double blifta[8];
		int    blifta_len = o.Gen_Product(2, bdx, 2, bdx, blifta);
		double bliftb[8];
		int    bliftb_len = o.Gen_Product(2, bdy, 2, bdy, bliftb);
		double blift[16];
		int    blift_len = o.Gen_Sum(blifta_len, blifta, bliftb_len, bliftb, blift);
		double clifta[8];
		int    clifta_len = o.Gen_Product(2, cdx, 2, cdx, clifta);
		double cliftb[8];
		int    cliftb_len = o.Gen_Product(2, cdy, 2, cdy, cliftb);
		double clift[16];
		int    clift_len = o.Gen_Sum(clifta_len, clifta, cliftb_len, cliftb, clift);
		double la_p[64], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 64);
		double lbt_p[64], *lbt = lbt_p;
		int    lbt_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lbt, 64);
		double lb_p[64], *lb = lb_p;
		int lb_len = o.Gen_Product_With_PreAlloc(lbt_len, lbt, d1_len, d1, &lb, 64);
		double lct_p[64], *lct = lct_p;
		int    lct_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lct, 64);
		double lc_p[64], *lc = lc_p;
		int lc_len = o.Gen_Product_With_PreAlloc(lct_len, lct, d1_len, d1, &lc, 64);
		double lab_p[64], *lab = lab_p;
		int    lab_len = o.Gen_Sum_With_PreAlloc(la_len, la, lb_len, lb, &lab, 64);
		double L_p[64], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, lc_len, lc, &L, 64);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lct_p != lct)
			FreeDoubles(lct);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (lbt_p != lbt)
			FreeDoubles(lbt);
		if (la_p != la)
			FreeDoubles(la);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (pdyt_p != pdyt)
			FreeDoubles(pdyt);
		if (pdxt_p != pdxt)
			FreeDoubles(pdxt);
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
		return inCirclexy_IEEE_exact<IT, ET>(p1, pbx, pby, pcx, pcy, pdx, pdy);
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
Sign inCirclexy_IEEE(const GenericPoint3T<IT, ET> &p1, double pbx, double pby,
                     double pcx, double pcy, double pdx, double pdy)
{
	Sign ret;
	ret = inCirclexy_IEEE_interval<IT, ET>(p1, pbx, pby, pcx, pcy, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCirclexy_IEEE_expansion<IT, ET>(p1, pbx, pby, pcx, pcy, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCirclexy_IEEE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &pb,
                     const GenericPoint3T<IT, ET> &pc,
                     const GenericPoint3T<IT, ET> &pd)
{
	return inCirclexy_IEEE<IT, ET>(p1, pb.x(), pb.y(), pc.x(), pc.y(), pd.x(),
	                               pd.y());
}

template <typename IT, typename ET>
Sign inCirclexy_IIEE_interval(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2, IT pcx, IT pcy,
                              IT pdx, IT pdy)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pdx1   = pdx * d1;
	IT pdy1   = pdy * d1;
	IT adx    = l1x - pdx1;
	IT ady    = l1y - pdy1;
	IT pdx2   = pdx * d2;
	IT pdy2   = pdy * d2;
	IT bdx    = l2x - pdx2;
	IT bdy    = l2y - pdy2;
	IT cdx    = pcx - pdx;
	IT cdy    = pcy - pdy;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT aliftt = alifta + aliftb;
	IT alift  = aliftt * d2;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT blift  = blifta + bliftb;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT cliftt = clifta + cliftb;
	IT clift  = cliftt * d2;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab    = lc + lb;
	IT lab2   = lab * d1;
	IT L      = lab2 + la;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IIEE_exact(const GenericPoint3T<IT, ET> &p1,
                           const GenericPoint3T<IT, ET> &p2, ET pcx, ET pcy,
                           ET pdx, ET pdy)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET pdx1   = pdx * d1;
	ET pdy1   = pdy * d1;
	ET adx    = l1x - pdx1;
	ET ady    = l1y - pdy1;
	ET pdx2   = pdx * d2;
	ET pdy2   = pdy * d2;
	ET bdx    = l2x - pdx2;
	ET bdy    = l2y - pdy2;
	ET cdx    = pcx - pdx;
	ET cdy    = pcy - pdy;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET aliftt = alifta + aliftb;
	ET alift  = aliftt * d2;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET blift  = blifta + bliftb;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET cliftt = clifta + cliftb;
	ET clift  = cliftt * d2;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab    = lc + lb;
	ET lab2   = lab * d1;
	ET L      = lab2 + la;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, double pcx,
                               double pcy, double pdx, double pdy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[32], *l1x = l1x_p, l1y_p[32], *l1y = l1y_p, l1z_p[32],
	                  *l1z = l1z_p, d1_p[32], *d1 = d1_p, l2x_p[32], *l2x = l2x_p,
	                  l2y_p[32], *l2y = l2y_p, l2z_p[32], *l2z = l2z_p, d2_p[32],
	                  *d2 = d2_p;
	int l1x_len = 32, l1y_len = 32, l1z_len = 32, d1_len = 32, l2x_len = 32,
	    l2y_len = 32, l2z_len = 32, d2_len = 32;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          pdx1_p[32], *pdx1 = pdx1_p;
		int    pdx1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdx, &pdx1, 32);
		double pdy1_p[32], *pdy1 = pdy1_p;
		int    pdy1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdy, &pdy1, 32);
		double adx_p[32], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pdx1_len, pdx1, &adx, 32);
		double ady_p[32], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, pdy1_len, pdy1, &ady, 32);
		double pdx2_p[32], *pdx2 = pdx2_p;
		int    pdx2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdx, &pdx2, 32);
		double pdy2_p[32], *pdy2 = pdy2_p;
		int    pdy2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdy, &pdy2, 32);
		double bdx_p[32], *bdx = bdx_p;
		int    bdx_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pdx2_len, pdx2, &bdx, 32);
		double bdy_p[32], *bdy = bdy_p;
		int    bdy_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, pdy2_len, pdy2, &bdy, 32);
		double cdx[2];
		o.Two_Diff(pcx, pdx, cdx);
		double cdy[2];
		o.Two_Diff(pcy, pdy, cdy);
		double abdeta_p[32], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, bdy_len, bdy, &abdeta, 32);
		double abdetb_p[32], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, ady_len, ady, &abdetb, 32);
		double abdet_p[32], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 32);
		double bcdeta_p[32], *bcdeta = bcdeta_p;
		int    bcdeta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, 2, cdy, &bcdeta, 32);
		double bcdetb_p[32], *bcdetb = bcdetb_p;
		int    bcdetb_len =
		  o.Gen_Product_With_PreAlloc(2, cdx, bdy_len, bdy, &bcdetb, 32);
		double bcdet_p[32], *bcdet = bcdet_p;
		int    bcdet_len = o.Gen_Diff_With_PreAlloc(bcdeta_len, bcdeta, bcdetb_len,
		                                            bcdetb, &bcdet, 32);
		double cadeta_p[32], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(2, cdx, ady_len, ady, &cadeta, 32);
		double cadetb_p[32], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, 2, cdy, &cadetb, 32);
		double cadet_p[32], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 32);
		double alifta_p[32], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 32);
		double aliftb_p[32], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 32);
		double aliftt_p[32], *aliftt = aliftt_p;
		int    aliftt_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                            aliftb, &aliftt, 32);
		double alift_p[32], *alift = alift_p;
		int    alift_len =
		  o.Gen_Product_With_PreAlloc(aliftt_len, aliftt, d2_len, d2, &alift, 32);
		double blifta_p[32], *blifta = blifta_p;
		int    blifta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, bdx_len, bdx, &blifta, 32);
		double bliftb_p[32], *bliftb = bliftb_p;
		int    bliftb_len =
		  o.Gen_Product_With_PreAlloc(bdy_len, bdy, bdy_len, bdy, &bliftb, 32);
		double blift_p[32], *blift = blift_p;
		int    blift_len = o.Gen_Sum_With_PreAlloc(blifta_len, blifta, bliftb_len,
		                                           bliftb, &blift, 32);
		double clifta[8];
		int    clifta_len = o.Gen_Product(2, cdx, 2, cdx, clifta);
		double cliftb[8];
		int    cliftb_len = o.Gen_Product(2, cdy, 2, cdy, cliftb);
		double cliftt[16];
		int cliftt_len = o.Gen_Sum(clifta_len, clifta, cliftb_len, cliftb, cliftt);
		double clift_p[32], *clift = clift_p;
		int    clift_len =
		  o.Gen_Product_With_PreAlloc(cliftt_len, cliftt, d2_len, d2, &clift, 32);
		double la_p[32], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 32);
		double lb_p[32], *lb = lb_p;
		int    lb_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 32);
		double lc_p[32], *lc = lc_p;
		int    lc_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 32);
		double lab_p[32], *lab = lab_p;
		int    lab_len = o.Gen_Sum_With_PreAlloc(lc_len, lc, lb_len, lb, &lab, 32);
		double lab2_p[32], *lab2 = lab2_p;
		int    lab2_len =
		  o.Gen_Product_With_PreAlloc(lab_len, lab, d1_len, d1, &lab2, 32);
		double L_p[32], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab2_len, lab2, la_len, la, &L, 32);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab2_p != lab2)
			FreeDoubles(lab2);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (la_p != la)
			FreeDoubles(la);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bliftb_p != bliftb)
			FreeDoubles(bliftb);
		if (blifta_p != blifta)
			FreeDoubles(blifta);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (aliftt_p != aliftt)
			FreeDoubles(aliftt);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (bcdet_p != bcdet)
			FreeDoubles(bcdet);
		if (bcdetb_p != bcdetb)
			FreeDoubles(bcdetb);
		if (bcdeta_p != bcdeta)
			FreeDoubles(bcdeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (bdy_p != bdy)
			FreeDoubles(bdy);
		if (bdx_p != bdx)
			FreeDoubles(bdx);
		if (pdy2_p != pdy2)
			FreeDoubles(pdy2);
		if (pdx2_p != pdx2)
			FreeDoubles(pdx2);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (pdy1_p != pdy1)
			FreeDoubles(pdy1);
		if (pdx1_p != pdx1)
			FreeDoubles(pdx1);
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
		return inCirclexy_IIEE_exact<IT, ET>(p1, p2, pcx, pcy, pdx, pdy);
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
Sign inCirclexy_IIEE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2, double pcx, double pcy,
                     double pdx, double pdy)
{
	Sign ret;
	ret = inCirclexy_IIEE_interval<IT, ET>(p1, p2, pcx, pcy, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCirclexy_IIEE_expansion<IT, ET>(p1, p2, pcx, pcy, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCirclexy_IIEE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &pc,
                     const GenericPoint3T<IT, ET> &pd)
{
	return inCirclexy_IIEE<IT, ET>(p1, p2, pc.x(), pc.y(), pd.x(), pd.y());
}

template <typename IT, typename ET>
Sign inCirclexy_IIIE_interval(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3, IT pdx, IT pdy)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pdx1   = pdx * d1;
	IT pdy1   = pdy * d1;
	IT adx    = l1x - pdx1;
	IT ady    = l1y - pdy1;
	IT pdx2   = pdx * d2;
	IT pdy2   = pdy * d2;
	IT bdx    = l2x - pdx2;
	IT bdy    = l2y - pdy2;
	IT pdx3   = pdx * d3;
	IT pdy3   = pdy * d3;
	IT cdx    = l3x - pdx3;
	IT cdy    = l3y - pdy3;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT aliftt = alifta + aliftb;
	IT alift2 = aliftt * d2;
	IT alift  = alift2 * d3;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT bliftt = blifta + bliftb;
	IT blift  = bliftt * d3;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT cliftt = clifta + cliftb;
	IT clift  = cliftt * d2;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab2   = lc + lb;
	IT lab    = lab2 * d1;
	IT L      = lab + la;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IIIE_exact(const GenericPoint3T<IT, ET> &p1,
                           const GenericPoint3T<IT, ET> &p2,
                           const GenericPoint3T<IT, ET> &p3, ET pdx, ET pdy)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET pdx1   = pdx * d1;
	ET pdy1   = pdy * d1;
	ET adx    = l1x - pdx1;
	ET ady    = l1y - pdy1;
	ET pdx2   = pdx * d2;
	ET pdy2   = pdy * d2;
	ET bdx    = l2x - pdx2;
	ET bdy    = l2y - pdy2;
	ET pdx3   = pdx * d3;
	ET pdy3   = pdy * d3;
	ET cdx    = l3x - pdx3;
	ET cdy    = l3y - pdy3;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET aliftt = alifta + aliftb;
	ET alift2 = aliftt * d2;
	ET alift  = alift2 * d3;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET bliftt = blifta + bliftb;
	ET blift  = bliftt * d3;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET cliftt = clifta + cliftb;
	ET clift  = cliftt * d2;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab2   = lc + lb;
	ET lab    = lab2 * d1;
	ET L      = lab + la;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3, double pdx,
                               double pdy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[32], *l1x = l1x_p, l1y_p[32], *l1y = l1y_p, l1z_p[32],
	                  *l1z = l1z_p, d1_p[32], *d1 = d1_p, l2x_p[32], *l2x = l2x_p,
	                  l2y_p[32], *l2y = l2y_p, l2z_p[32], *l2z = l2z_p, d2_p[32],
	                  *d2 = d2_p, l3x_p[32], *l3x = l3x_p, l3y_p[32],
	                  *l3y = l3y_p, l3z_p[32], *l3z = l3z_p, d3_p[32], *d3 = d3_p;
	int l1x_len = 32, l1y_len = 32, l1z_len = 32, d1_len = 32, l2x_len = 32,
	    l2y_len = 32, l2z_len = 32, d2_len = 32, l3x_len = 32, l3y_len = 32,
	    l3z_len = 32, d3_len = 32;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          pdx1_p[32], *pdx1 = pdx1_p;
		int    pdx1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdx, &pdx1, 32);
		double pdy1_p[32], *pdy1 = pdy1_p;
		int    pdy1_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pdy, &pdy1, 32);
		double adx_p[32], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pdx1_len, pdx1, &adx, 32);
		double ady_p[32], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, pdy1_len, pdy1, &ady, 32);
		double pdx2_p[32], *pdx2 = pdx2_p;
		int    pdx2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdx, &pdx2, 32);
		double pdy2_p[32], *pdy2 = pdy2_p;
		int    pdy2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pdy, &pdy2, 32);
		double bdx_p[32], *bdx = bdx_p;
		int    bdx_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pdx2_len, pdx2, &bdx, 32);
		double bdy_p[32], *bdy = bdy_p;
		int    bdy_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, pdy2_len, pdy2, &bdy, 32);
		double pdx3_p[32], *pdx3 = pdx3_p;
		int    pdx3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pdx, &pdx3, 32);
		double pdy3_p[32], *pdy3 = pdy3_p;
		int    pdy3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pdy, &pdy3, 32);
		double cdx_p[32], *cdx = cdx_p;
		int    cdx_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, pdx3_len, pdx3, &cdx, 32);
		double cdy_p[32], *cdy = cdy_p;
		int    cdy_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, pdy3_len, pdy3, &cdy, 32);
		double abdeta_p[32], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, bdy_len, bdy, &abdeta, 32);
		double abdetb_p[32], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, ady_len, ady, &abdetb, 32);
		double abdet_p[32], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 32);
		double bcdeta_p[32], *bcdeta = bcdeta_p;
		int    bcdeta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, cdy_len, cdy, &bcdeta, 32);
		double bcdetb_p[32], *bcdetb = bcdetb_p;
		int    bcdetb_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, bdy_len, bdy, &bcdetb, 32);
		double bcdet_p[32], *bcdet = bcdet_p;
		int    bcdet_len = o.Gen_Diff_With_PreAlloc(bcdeta_len, bcdeta, bcdetb_len,
		                                            bcdetb, &bcdet, 32);
		double cadeta_p[32], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, ady_len, ady, &cadeta, 32);
		double cadetb_p[32], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, cdy_len, cdy, &cadetb, 32);
		double cadet_p[32], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 32);
		double alifta_p[32], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 32);
		double aliftb_p[32], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 32);
		double aliftt_p[32], *aliftt = aliftt_p;
		int    aliftt_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                            aliftb, &aliftt, 32);
		double alift2_p[32], *alift2 = alift2_p;
		int    alift2_len =
		  o.Gen_Product_With_PreAlloc(aliftt_len, aliftt, d2_len, d2, &alift2, 32);
		double alift_p[32], *alift = alift_p;
		int    alift_len =
		  o.Gen_Product_With_PreAlloc(alift2_len, alift2, d3_len, d3, &alift, 32);
		double blifta_p[32], *blifta = blifta_p;
		int    blifta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, bdx_len, bdx, &blifta, 32);
		double bliftb_p[32], *bliftb = bliftb_p;
		int    bliftb_len =
		  o.Gen_Product_With_PreAlloc(bdy_len, bdy, bdy_len, bdy, &bliftb, 32);
		double bliftt_p[32], *bliftt = bliftt_p;
		int    bliftt_len = o.Gen_Sum_With_PreAlloc(blifta_len, blifta, bliftb_len,
		                                            bliftb, &bliftt, 32);
		double blift_p[32], *blift = blift_p;
		int    blift_len =
		  o.Gen_Product_With_PreAlloc(bliftt_len, bliftt, d3_len, d3, &blift, 32);
		double clifta_p[32], *clifta = clifta_p;
		int    clifta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, cdx_len, cdx, &clifta, 32);
		double cliftb_p[32], *cliftb = cliftb_p;
		int    cliftb_len =
		  o.Gen_Product_With_PreAlloc(cdy_len, cdy, cdy_len, cdy, &cliftb, 32);
		double cliftt_p[32], *cliftt = cliftt_p;
		int    cliftt_len = o.Gen_Sum_With_PreAlloc(clifta_len, clifta, cliftb_len,
		                                            cliftb, &cliftt, 32);
		double clift_p[32], *clift = clift_p;
		int    clift_len =
		  o.Gen_Product_With_PreAlloc(cliftt_len, cliftt, d2_len, d2, &clift, 32);
		double la_p[32], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 32);
		double lb_p[32], *lb = lb_p;
		int    lb_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 32);
		double lc_p[32], *lc = lc_p;
		int    lc_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 32);
		double lab2_p[32], *lab2 = lab2_p;
		int lab2_len = o.Gen_Sum_With_PreAlloc(lc_len, lc, lb_len, lb, &lab2, 32);
		double lab_p[32], *lab = lab_p;
		int    lab_len =
		  o.Gen_Product_With_PreAlloc(lab2_len, lab2, d1_len, d1, &lab, 32);
		double L_p[32], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, la_len, la, &L, 32);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lab2_p != lab2)
			FreeDoubles(lab2);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (la_p != la)
			FreeDoubles(la);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cliftt_p != cliftt)
			FreeDoubles(cliftt);
		if (cliftb_p != cliftb)
			FreeDoubles(cliftb);
		if (clifta_p != clifta)
			FreeDoubles(clifta);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bliftt_p != bliftt)
			FreeDoubles(bliftt);
		if (bliftb_p != bliftb)
			FreeDoubles(bliftb);
		if (blifta_p != blifta)
			FreeDoubles(blifta);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (alift2_p != alift2)
			FreeDoubles(alift2);
		if (aliftt_p != aliftt)
			FreeDoubles(aliftt);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (bcdet_p != bcdet)
			FreeDoubles(bcdet);
		if (bcdetb_p != bcdetb)
			FreeDoubles(bcdetb);
		if (bcdeta_p != bcdeta)
			FreeDoubles(bcdeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (cdy_p != cdy)
			FreeDoubles(cdy);
		if (cdx_p != cdx)
			FreeDoubles(cdx);
		if (pdy3_p != pdy3)
			FreeDoubles(pdy3);
		if (pdx3_p != pdx3)
			FreeDoubles(pdx3);
		if (bdy_p != bdy)
			FreeDoubles(bdy);
		if (bdx_p != bdx)
			FreeDoubles(bdx);
		if (pdy2_p != pdy2)
			FreeDoubles(pdy2);
		if (pdx2_p != pdx2)
			FreeDoubles(pdx2);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (pdy1_p != pdy1)
			FreeDoubles(pdy1);
		if (pdx1_p != pdx1)
			FreeDoubles(pdx1);
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
		return inCirclexy_IIIE_exact<IT, ET>(p1, p2, p3, pdx, pdy);
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
Sign inCirclexy_IIIE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &p3, double pdx, double pdy)
{
	Sign ret;
	ret = inCirclexy_IIIE_interval<IT, ET>(p1, p2, p3, pdx, pdy);
	if (is_sign_reliable(ret))
		return ret;
	return inCirclexy_IIIE_expansion<IT, ET>(p1, p2, p3, pdx, pdy);
}

template <typename IT, typename ET>
Sign inCirclexy_IIIE(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &p3,
                     const GenericPoint3T<IT, ET> &pd)
{
	return inCirclexy_IIIE<IT, ET>(p1, p2, p3, pd.x(), pd.y());
}

template <typename IT, typename ET>
Sign inCirclexy_IIII_interval(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3,
                              const GenericPoint3T<IT, ET> &p4)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3) ||
	    !p4.getIntervalLambda(l4x, l4y, l4z, d4))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT l1xt   = l1x * d4;
	IT l1yt   = l1y * d4;
	IT l2xt   = l2x * d4;
	IT l2yt   = l2y * d4;
	IT l3xt   = l3x * d4;
	IT l3yt   = l3y * d4;
	IT l4x1   = l4x * d1;
	IT l4y1   = l4y * d1;
	IT adx    = l1xt - l4x1;
	IT ady    = l1yt - l4y1;
	IT l4x2   = l4x * d2;
	IT l4y2   = l4y * d2;
	IT bdx    = l2xt - l4x2;
	IT bdy    = l2yt - l4y2;
	IT l4x3   = l4x * d3;
	IT l4y3   = l4y * d3;
	IT cdx    = l3xt - l4x3;
	IT cdy    = l3yt - l4y3;
	IT abdeta = adx * bdy;
	IT abdetb = bdx * ady;
	IT abdet  = abdeta - abdetb;
	IT bcdeta = bdx * cdy;
	IT bcdetb = cdx * bdy;
	IT bcdet  = bcdeta - bcdetb;
	IT cadeta = cdx * ady;
	IT cadetb = adx * cdy;
	IT cadet  = cadeta - cadetb;
	IT alifta = adx * adx;
	IT aliftb = ady * ady;
	IT aliftt = alifta + aliftb;
	IT alift2 = aliftt * d2;
	IT alift  = alift2 * d3;
	IT blifta = bdx * bdx;
	IT bliftb = bdy * bdy;
	IT bliftt = blifta + bliftb;
	IT blift  = bliftt * d3;
	IT clifta = cdx * cdx;
	IT cliftb = cdy * cdy;
	IT cliftt = clifta + cliftb;
	IT clift  = cliftt * d2;
	IT la     = alift * bcdet;
	IT lb     = blift * cadet;
	IT lc     = clift * abdet;
	IT lab2   = lc + lb;
	IT lab    = lab2 * d1;
	IT L      = lab + la;
	if (!L.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IIII_exact(const GenericPoint3T<IT, ET> &p1,
                           const GenericPoint3T<IT, ET> &p2,
                           const GenericPoint3T<IT, ET> &p3,
                           const GenericPoint3T<IT, ET> &p4)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	p4.getExactLambda(l4x, l4y, l4z, d4);
	ET l1xt   = l1x * d4;
	ET l1yt   = l1y * d4;
	ET l2xt   = l2x * d4;
	ET l2yt   = l2y * d4;
	ET l3xt   = l3x * d4;
	ET l3yt   = l3y * d4;
	ET l4x1   = l4x * d1;
	ET l4y1   = l4y * d1;
	ET adx    = l1xt - l4x1;
	ET ady    = l1yt - l4y1;
	ET l4x2   = l4x * d2;
	ET l4y2   = l4y * d2;
	ET bdx    = l2xt - l4x2;
	ET bdy    = l2yt - l4y2;
	ET l4x3   = l4x * d3;
	ET l4y3   = l4y * d3;
	ET cdx    = l3xt - l4x3;
	ET cdy    = l3yt - l4y3;
	ET abdeta = adx * bdy;
	ET abdetb = bdx * ady;
	ET abdet  = abdeta - abdetb;
	ET bcdeta = bdx * cdy;
	ET bcdetb = cdx * bdy;
	ET bcdet  = bcdeta - bcdetb;
	ET cadeta = cdx * ady;
	ET cadetb = adx * cdy;
	ET cadet  = cadeta - cadetb;
	ET alifta = adx * adx;
	ET aliftb = ady * ady;
	ET aliftt = alifta + aliftb;
	ET alift2 = aliftt * d2;
	ET alift  = alift2 * d3;
	ET blifta = bdx * bdx;
	ET bliftb = bdy * bdy;
	ET bliftt = blifta + bliftb;
	ET blift  = bliftt * d3;
	ET clifta = cdx * cdx;
	ET cliftb = cdy * cdy;
	ET cliftt = clifta + cliftb;
	ET clift  = cliftt * d2;
	ET la     = alift * bcdet;
	ET lb     = blift * cadet;
	ET lc     = clift * abdet;
	ET lab2   = lc + lb;
	ET lab    = lab2 * d1;
	ET L      = lab + la;
	return OMC::sign(L);
}

template <typename IT, typename ET>
Sign inCirclexy_IIII_expansion(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3,
                               const GenericPoint3T<IT, ET> &p4)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16],
	  *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16], *l1z = l1z_p, d1_p[16],
	  *d1 = d1_p, l2x_p[16], *l2x = l2x_p, l2y_p[16], *l2y = l2y_p, l2z_p[16],
	  *l2z = l2z_p, d2_p[16], *d2 = d2_p, l3x_p[16], *l3x = l3x_p, l3y_p[16],
	  *l3y = l3y_p, l3z_p[16], *l3z = l3z_p, d3_p[16], *d3 = d3_p, l4x_p[16],
	  *l4x = l4x_p, l4y_p[16], *l4y = l4y_p, l4z_p[16], *l4z = l4z_p, d4_p[16],
	  *d4       = d4_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16, l2x_len = 16,
	    l2y_len = 16, l2z_len = 16, d2_len = 16, l3x_len = 16, l3y_len = 16,
	    l3z_len = 16, d3_len = 16, l4x_len = 16, l4y_len = 16, l4z_len = 16,
	    d4_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	p4.getExpansionLambda(&l4x, l4x_len, &l4y, l4y_len, &l4z, l4z_len, &d4,
	                      d4_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0) &&
	    (d4[d4_len - 1] != 0))
	{
		expansionObject o;
		double          l1xt_p[16], *l1xt = l1xt_p;
		int             l1xt_len =
		  o.Gen_Product_With_PreAlloc(l1x_len, l1x, d4_len, d4, &l1xt, 16);
		double l1yt_p[16], *l1yt = l1yt_p;
		int    l1yt_len =
		  o.Gen_Product_With_PreAlloc(l1y_len, l1y, d4_len, d4, &l1yt, 16);
		double l2xt_p[16], *l2xt = l2xt_p;
		int    l2xt_len =
		  o.Gen_Product_With_PreAlloc(l2x_len, l2x, d4_len, d4, &l2xt, 16);
		double l2yt_p[16], *l2yt = l2yt_p;
		int    l2yt_len =
		  o.Gen_Product_With_PreAlloc(l2y_len, l2y, d4_len, d4, &l2yt, 16);
		double l3xt_p[16], *l3xt = l3xt_p;
		int    l3xt_len =
		  o.Gen_Product_With_PreAlloc(l3x_len, l3x, d4_len, d4, &l3xt, 16);
		double l3yt_p[16], *l3yt = l3yt_p;
		int    l3yt_len =
		  o.Gen_Product_With_PreAlloc(l3y_len, l3y, d4_len, d4, &l3yt, 16);
		double l4x1_p[16], *l4x1 = l4x1_p;
		int    l4x1_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d1_len, d1, &l4x1, 16);
		double l4y1_p[16], *l4y1 = l4y1_p;
		int    l4y1_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d1_len, d1, &l4y1, 16);
		double adx_p[16], *adx = adx_p;
		int    adx_len =
		  o.Gen_Diff_With_PreAlloc(l1xt_len, l1xt, l4x1_len, l4x1, &adx, 16);
		double ady_p[16], *ady = ady_p;
		int    ady_len =
		  o.Gen_Diff_With_PreAlloc(l1yt_len, l1yt, l4y1_len, l4y1, &ady, 16);
		double l4x2_p[16], *l4x2 = l4x2_p;
		int    l4x2_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d2_len, d2, &l4x2, 16);
		double l4y2_p[16], *l4y2 = l4y2_p;
		int    l4y2_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d2_len, d2, &l4y2, 16);
		double bdx_p[16], *bdx = bdx_p;
		int    bdx_len =
		  o.Gen_Diff_With_PreAlloc(l2xt_len, l2xt, l4x2_len, l4x2, &bdx, 16);
		double bdy_p[16], *bdy = bdy_p;
		int    bdy_len =
		  o.Gen_Diff_With_PreAlloc(l2yt_len, l2yt, l4y2_len, l4y2, &bdy, 16);
		double l4x3_p[16], *l4x3 = l4x3_p;
		int    l4x3_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d3_len, d3, &l4x3, 16);
		double l4y3_p[16], *l4y3 = l4y3_p;
		int    l4y3_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d3_len, d3, &l4y3, 16);
		double cdx_p[16], *cdx = cdx_p;
		int    cdx_len =
		  o.Gen_Diff_With_PreAlloc(l3xt_len, l3xt, l4x3_len, l4x3, &cdx, 16);
		double cdy_p[16], *cdy = cdy_p;
		int    cdy_len =
		  o.Gen_Diff_With_PreAlloc(l3yt_len, l3yt, l4y3_len, l4y3, &cdy, 16);
		double abdeta_p[16], *abdeta = abdeta_p;
		int    abdeta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, bdy_len, bdy, &abdeta, 16);
		double abdetb_p[16], *abdetb = abdetb_p;
		int    abdetb_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, ady_len, ady, &abdetb, 16);
		double abdet_p[16], *abdet = abdet_p;
		int    abdet_len = o.Gen_Diff_With_PreAlloc(abdeta_len, abdeta, abdetb_len,
		                                            abdetb, &abdet, 16);
		double bcdeta_p[16], *bcdeta = bcdeta_p;
		int    bcdeta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, cdy_len, cdy, &bcdeta, 16);
		double bcdetb_p[16], *bcdetb = bcdetb_p;
		int    bcdetb_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, bdy_len, bdy, &bcdetb, 16);
		double bcdet_p[16], *bcdet = bcdet_p;
		int    bcdet_len = o.Gen_Diff_With_PreAlloc(bcdeta_len, bcdeta, bcdetb_len,
		                                            bcdetb, &bcdet, 16);
		double cadeta_p[16], *cadeta = cadeta_p;
		int    cadeta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, ady_len, ady, &cadeta, 16);
		double cadetb_p[16], *cadetb = cadetb_p;
		int    cadetb_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, cdy_len, cdy, &cadetb, 16);
		double cadet_p[16], *cadet = cadet_p;
		int    cadet_len = o.Gen_Diff_With_PreAlloc(cadeta_len, cadeta, cadetb_len,
		                                            cadetb, &cadet, 16);
		double alifta_p[16], *alifta = alifta_p;
		int    alifta_len =
		  o.Gen_Product_With_PreAlloc(adx_len, adx, adx_len, adx, &alifta, 16);
		double aliftb_p[16], *aliftb = aliftb_p;
		int    aliftb_len =
		  o.Gen_Product_With_PreAlloc(ady_len, ady, ady_len, ady, &aliftb, 16);
		double aliftt_p[16], *aliftt = aliftt_p;
		int    aliftt_len = o.Gen_Sum_With_PreAlloc(alifta_len, alifta, aliftb_len,
		                                            aliftb, &aliftt, 16);
		double alift2_p[16], *alift2 = alift2_p;
		int    alift2_len =
		  o.Gen_Product_With_PreAlloc(aliftt_len, aliftt, d2_len, d2, &alift2, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Product_With_PreAlloc(alift2_len, alift2, d3_len, d3, &alift, 16);
		double blifta_p[16], *blifta = blifta_p;
		int    blifta_len =
		  o.Gen_Product_With_PreAlloc(bdx_len, bdx, bdx_len, bdx, &blifta, 16);
		double bliftb_p[16], *bliftb = bliftb_p;
		int    bliftb_len =
		  o.Gen_Product_With_PreAlloc(bdy_len, bdy, bdy_len, bdy, &bliftb, 16);
		double bliftt_p[16], *bliftt = bliftt_p;
		int    bliftt_len = o.Gen_Sum_With_PreAlloc(blifta_len, blifta, bliftb_len,
		                                            bliftb, &bliftt, 16);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Product_With_PreAlloc(bliftt_len, bliftt, d3_len, d3, &blift, 16);
		double clifta_p[16], *clifta = clifta_p;
		int    clifta_len =
		  o.Gen_Product_With_PreAlloc(cdx_len, cdx, cdx_len, cdx, &clifta, 16);
		double cliftb_p[16], *cliftb = cliftb_p;
		int    cliftb_len =
		  o.Gen_Product_With_PreAlloc(cdy_len, cdy, cdy_len, cdy, &cliftb, 16);
		double cliftt_p[16], *cliftt = cliftt_p;
		int    cliftt_len = o.Gen_Sum_With_PreAlloc(clifta_len, clifta, cliftb_len,
		                                            cliftb, &cliftt, 16);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Product_With_PreAlloc(cliftt_len, cliftt, d2_len, d2, &clift, 16);
		double la_p[16], *la = la_p;
		int    la_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcdet_len, bcdet, &la, 16);
		double lb_p[16], *lb = lb_p;
		int    lb_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cadet_len, cadet, &lb, 16);
		double lc_p[16], *lc = lc_p;
		int    lc_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, abdet_len, abdet, &lc, 16);
		double lab2_p[16], *lab2 = lab2_p;
		int lab2_len = o.Gen_Sum_With_PreAlloc(lc_len, lc, lb_len, lb, &lab2, 16);
		double lab_p[16], *lab = lab_p;
		int    lab_len =
		  o.Gen_Product_With_PreAlloc(lab2_len, lab2, d1_len, d1, &lab, 16);
		double L_p[16], *L = L_p;
		int    L_len = o.Gen_Sum_With_PreAlloc(lab_len, lab, la_len, la, &L, 16);

		return_value = L[L_len - 1];
		if (L_p != L)
			FreeDoubles(L);
		if (lab_p != lab)
			FreeDoubles(lab);
		if (lab2_p != lab2)
			FreeDoubles(lab2);
		if (lc_p != lc)
			FreeDoubles(lc);
		if (lb_p != lb)
			FreeDoubles(lb);
		if (la_p != la)
			FreeDoubles(la);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cliftt_p != cliftt)
			FreeDoubles(cliftt);
		if (cliftb_p != cliftb)
			FreeDoubles(cliftb);
		if (clifta_p != clifta)
			FreeDoubles(clifta);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bliftt_p != bliftt)
			FreeDoubles(bliftt);
		if (bliftb_p != bliftb)
			FreeDoubles(bliftb);
		if (blifta_p != blifta)
			FreeDoubles(blifta);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (alift2_p != alift2)
			FreeDoubles(alift2);
		if (aliftt_p != aliftt)
			FreeDoubles(aliftt);
		if (aliftb_p != aliftb)
			FreeDoubles(aliftb);
		if (alifta_p != alifta)
			FreeDoubles(alifta);
		if (cadet_p != cadet)
			FreeDoubles(cadet);
		if (cadetb_p != cadetb)
			FreeDoubles(cadetb);
		if (cadeta_p != cadeta)
			FreeDoubles(cadeta);
		if (bcdet_p != bcdet)
			FreeDoubles(bcdet);
		if (bcdetb_p != bcdetb)
			FreeDoubles(bcdetb);
		if (bcdeta_p != bcdeta)
			FreeDoubles(bcdeta);
		if (abdet_p != abdet)
			FreeDoubles(abdet);
		if (abdetb_p != abdetb)
			FreeDoubles(abdetb);
		if (abdeta_p != abdeta)
			FreeDoubles(abdeta);
		if (cdy_p != cdy)
			FreeDoubles(cdy);
		if (cdx_p != cdx)
			FreeDoubles(cdx);
		if (l4y3_p != l4y3)
			FreeDoubles(l4y3);
		if (l4x3_p != l4x3)
			FreeDoubles(l4x3);
		if (bdy_p != bdy)
			FreeDoubles(bdy);
		if (bdx_p != bdx)
			FreeDoubles(bdx);
		if (l4y2_p != l4y2)
			FreeDoubles(l4y2);
		if (l4x2_p != l4x2)
			FreeDoubles(l4x2);
		if (ady_p != ady)
			FreeDoubles(ady);
		if (adx_p != adx)
			FreeDoubles(adx);
		if (l4y1_p != l4y1)
			FreeDoubles(l4y1);
		if (l4x1_p != l4x1)
			FreeDoubles(l4x1);
		if (l3yt_p != l3yt)
			FreeDoubles(l3yt);
		if (l3xt_p != l3xt)
			FreeDoubles(l3xt);
		if (l2yt_p != l2yt)
			FreeDoubles(l2yt);
		if (l2xt_p != l2xt)
			FreeDoubles(l2xt);
		if (l1yt_p != l1yt)
			FreeDoubles(l1yt);
		if (l1xt_p != l1xt)
			FreeDoubles(l1xt);
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
		if (l4x_p != l4x)
			FreeDoubles(l4x);
		if (l4y_p != l4y)
			FreeDoubles(l4y);
		if (l4z_p != l4z)
			FreeDoubles(l4z);
		if (d4_p != d4)
			FreeDoubles(d4);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inCirclexy_IIII_exact<IT, ET>(p1, p2, p3, p4);
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
Sign inCirclexy_IIII(const GenericPoint3T<IT, ET> &p1,
                     const GenericPoint3T<IT, ET> &p2,
                     const GenericPoint3T<IT, ET> &p3,
                     const GenericPoint3T<IT, ET> &p4)
{
	Sign ret;
	ret = inCirclexy_IIII_interval<IT, ET>(p1, p2, p3, p4);
	if (is_sign_reliable(ret))
		return ret;
	return inCirclexy_IIII_expansion<IT, ET>(p1, p2, p3, p4);
}
} // namespace OMC