#pragma once

#include "OpenMeshCraft/Geometry/Predicates/IndirectDefinitions.h"

#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"
#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"
#include "OpenMeshCraft/NumberTypes/LazyNumber.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
#define CHECK_FOR_XYZERFLOWS

namespace OMC {

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

/*===================================================================*/

inline Sign squaredDistance2D_filtered(double px, double py, double qx,
                                       double qy, double dis);

template <typename IT>
Sign squaredDistance2D_interval(IT px, IT py, IT qx, IT qy, IT dis);

template <typename ET>
Sign squaredDistance2D_exact(ET px, ET py, ET qx, ET qy, ET dis);

inline Sign squaredDistance2D_expansion(double px, double py, double qx,
                                        double qy, double dis);

template <typename IT, typename ET>
Sign squaredDistance2D(double px, double py, double qx, double qy, double dis);

template <typename IT, typename ET>
Sign squaredDistance2D(const GenericPoint2T<IT, ET> &p,
                       const GenericPoint2T<IT, ET> &q, double dis);

/*===================================================================*/

inline Sign squaredDistance3D_filtered(double px, double py, double pz,
                                       double qx, double qy, double qz,
                                       double dis);

template <typename IT>
Sign squaredDistance3D_interval(IT px, IT py, IT pz, IT qx, IT qy, IT qz,
                                IT dis);

template <typename ET>
Sign squaredDistance3D_exact(ET px, ET py, ET pz, ET qx, ET qy, ET qz, ET dis);

inline Sign squaredDistance3D_expansion(double px, double py, double pz,
                                        double qx, double qy, double qz,
                                        double dis);

template <typename IT, typename ET>
Sign squaredDistance3D(double px, double py, double pz, double qx, double qy,
                       double qz, double dis);

template <typename IT, typename ET>
Sign squaredDistance3D(const GenericPoint3T<IT, ET> &p,
                       const GenericPoint3T<IT, ET> &q, double dis);

/*===================================================================*/

template <typename IT>
Sign squaredDistance3D3p_interval(IT pax, IT pay, IT paz, IT pbx, IT pby,
                                  IT pbz, IT pcx, IT pcy, IT pcz, int ab_scale);

template <typename ET>
Sign squaredDistance3D3p_exact(ET pax, ET pay, ET paz, ET pbx, ET pby, ET pbz,
                               ET pcx, ET pcy, ET pcz, int ab_scale);

inline Sign squaredDistance3D3p_expansion(double pax, double pay, double paz,
                                          double pbx, double pby, double pbz,
                                          double pcx, double pcy, double pcz,
                                          int ab_scale);

template <typename IT, typename ET>
Sign squaredDistance3D3p(double pax, double pay, double paz, double pbx,
                         double pby, double pbz, double pcx, double pcy,
                         double pcz, int ab_scale);

template <typename IT, typename ET>
Sign squaredDistance3D3p(const GenericPoint3T<IT, ET> &pa,
                         const GenericPoint3T<IT, ET> &pb,
                         const GenericPoint3T<IT, ET> &pc, int ab_scale);

/*===================================================================*/

template <typename IT, typename ET>
Sign squaredDistance2D_IE_interval(const GenericPoint2T<IT, ET> &p, IT qx,
                                   IT qy, IT dis);

template <typename IT, typename ET>
Sign squaredDistance2D_IE_exact(const GenericPoint2T<IT, ET> &p, ET qx, ET qy,
                                ET dis);

template <typename IT, typename ET>
Sign squaredDistance2D_IE_expansion(const GenericPoint2T<IT, ET> &p, double qx,
                                    double qy, double dis);

template <typename IT, typename ET>
Sign squaredDistance2D_IE(const GenericPoint2T<IT, ET> &p, double qx, double qy,
                          double dis);

template <typename IT, typename ET>
Sign squaredDistance2D_IE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q, double dis);

/*===================================================================*/

template <typename IT, typename ET>
Sign squaredDistance2D_II_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &q, IT dis);

template <typename IT, typename ET>
Sign squaredDistance2D_II_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &q, ET dis);

template <typename IT, typename ET>
Sign squaredDistance2D_II_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &q,
                                    double                        dis);

template <typename IT, typename ET>
Sign squaredDistance2D_II(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q, double dis);

/*===================================================================*/

template <typename IT, typename ET>
Sign squaredDistance3D_IE_interval(const GenericPoint3T<IT, ET> &p, IT qx,
                                   IT qy, IT qz, IT dis);

template <typename IT, typename ET>
Sign squaredDistance3D_IE_exact(const GenericPoint3T<IT, ET> &p, ET qx, ET qy,
                                ET qz, ET dis);

template <typename IT, typename ET>
Sign squaredDistance3D_IE_expansion(const GenericPoint3T<IT, ET> &p, double qx,
                                    double qy, double qz, double dis);

template <typename IT, typename ET>
Sign squaredDistance3D_IE(const GenericPoint3T<IT, ET> &p, double qx, double qy,
                          double qz, double dis);

template <typename IT, typename ET>
Sign squaredDistance3D_IE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q, double dis);

/*===================================================================*/

template <typename IT, typename ET>
Sign squaredDistance3D_II_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &q, IT dis);

template <typename IT, typename ET>
Sign squaredDistance3D_II_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &q, ET dis);

template <typename IT, typename ET>
Sign squaredDistance3D_II_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &q,
                                    double                        dis);

template <typename IT, typename ET>
Sign squaredDistance3D_II(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q, double dis);

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

inline Sign squaredDistance2D_filtered(double px, double py, double qx,
                                       double qy, double dis)
{
	double lx      = px - qx;
	double ly      = py - qy;
	double lx2     = lx * lx;
	double ly2     = ly * ly;
	double sqrnorm = lx2 + ly2;
	double diff    = sqrnorm - dis;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(dis)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 1.1102230246251565e-15;

	return filter_sign(diff, epsilon);
}

template <typename IT>
Sign squaredDistance2D_interval(IT px, IT py, IT qx, IT qy, IT dis)
{
	typename IT::Protector P;

	IT lx      = px - qx;
	IT ly      = py - qy;
	IT lx2     = lx * lx;
	IT ly2     = ly * ly;
	IT sqrnorm = lx2 + ly2;
	IT diff    = sqrnorm - dis;
	if (!diff.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(diff);
}

template <typename ET>
Sign squaredDistance2D_exact(ET px, ET py, ET qx, ET qy, ET dis)
{
	ET lx      = px - qx;
	ET ly      = py - qy;
	ET lx2     = lx * lx;
	ET ly2     = ly * ly;
	ET sqrnorm = lx2 + ly2;
	ET diff    = sqrnorm - dis;
	return OMC::sign(diff);
}

Sign squaredDistance2D_expansion(double px, double py, double qx, double qy,
                                 double dis)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double lx2[8];
	int    lx2_len = o.Gen_Product(2, lx, 2, lx, lx2);
	double ly2[8];
	int    ly2_len = o.Gen_Product(2, ly, 2, ly, ly2);
	double sqrnorm[16];
	int    sqrnorm_len = o.Gen_Sum(lx2_len, lx2, ly2_len, ly2, sqrnorm);
	double diff[17];
	int    diff_len = o.Gen_Diff(sqrnorm_len, sqrnorm, 1, &dis, diff);

	double return_value = diff[diff_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign squaredDistance2D(double px, double py, double qx, double qy, double dis)
{
	Sign ret;
	ret = squaredDistance2D_filtered(px, py, qx, qy, dis);
	if (is_sign_reliable(ret))
		return ret;
	ret = squaredDistance2D_interval<IT>(px, py, qx, qy, dis);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance2D_expansion(px, py, qx, qy, dis);
}

template <typename IT, typename ET>
Sign squaredDistance2D(const GenericPoint2T<IT, ET> &p,
                       const GenericPoint2T<IT, ET> &q, double dis)
{
	return squaredDistance2D<IT, ET>(p.x(), p.y(), q.x(), q.y(), dis);
}

inline Sign squaredDistance3D_filtered(double px, double py, double pz,
                                       double qx, double qy, double qz,
                                       double dis)
{
	double lx        = px - qx;
	double ly        = py - qy;
	double lz        = pz - qz;
	double lx2       = lx * lx;
	double ly2       = ly * ly;
	double lz2       = lz * lz;
	double sqrnormxy = lx2 + ly2;
	double sqrnorm   = sqrnormxy + lz2;
	double diff      = sqrnorm - dis;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(dis)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lz)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 1.887379141862766e-15;

	return filter_sign(diff, epsilon);
}

template <typename IT>
Sign squaredDistance3D_interval(IT px, IT py, IT pz, IT qx, IT qy, IT qz,
                                IT dis)
{
	typename IT::Protector P;

	IT lx        = px - qx;
	IT ly        = py - qy;
	IT lz        = pz - qz;
	IT lx2       = lx * lx;
	IT ly2       = ly * ly;
	IT lz2       = lz * lz;
	IT sqrnormxy = lx2 + ly2;
	IT sqrnorm   = sqrnormxy + lz2;
	IT diff      = sqrnorm - dis;
	if (!diff.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(diff);
}

template <typename ET>
Sign squaredDistance3D_exact(ET px, ET py, ET pz, ET qx, ET qy, ET qz, ET dis)
{
	ET lx        = px - qx;
	ET ly        = py - qy;
	ET lz        = pz - qz;
	ET lx2       = lx * lx;
	ET ly2       = ly * ly;
	ET lz2       = lz * lz;
	ET sqrnormxy = lx2 + ly2;
	ET sqrnorm   = sqrnormxy + lz2;
	ET diff      = sqrnorm - dis;
	return OMC::sign(diff);
}

Sign squaredDistance3D_expansion(double px, double py, double pz, double qx,
                                 double qy, double qz, double dis)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double lz[2];
	o.Two_Diff(pz, qz, lz);
	double lx2[8];
	int    lx2_len = o.Gen_Product(2, lx, 2, lx, lx2);
	double ly2[8];
	int    ly2_len = o.Gen_Product(2, ly, 2, ly, ly2);
	double lz2[8];
	int    lz2_len = o.Gen_Product(2, lz, 2, lz, lz2);
	double sqrnormxy[16];
	int    sqrnormxy_len = o.Gen_Sum(lx2_len, lx2, ly2_len, ly2, sqrnormxy);
	double sqrnorm[24];
	int sqrnorm_len = o.Gen_Sum(sqrnormxy_len, sqrnormxy, lz2_len, lz2, sqrnorm);
	double diff[25];
	int    diff_len = o.Gen_Diff(sqrnorm_len, sqrnorm, 1, &dis, diff);

	double return_value = diff[diff_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign squaredDistance3D(double px, double py, double pz, double qx, double qy,
                       double qz, double dis)
{
	Sign ret;
	ret = squaredDistance3D_filtered(px, py, pz, qx, qy, qz, dis);
	if (is_sign_reliable(ret))
		return ret;
	ret = squaredDistance3D_interval<IT>(px, py, pz, qx, qy, qz, dis);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance3D_expansion(px, py, pz, qx, qy, qz, dis);
}

template <typename IT, typename ET>
Sign squaredDistance3D(const GenericPoint3T<IT, ET> &p,
                       const GenericPoint3T<IT, ET> &q, double dis)
{
	return squaredDistance3D<IT, ET>(p.x(), p.y(), p.z(), q.x(), q.y(), q.z(),
	                                 dis);
}

template <typename IT>
Sign squaredDistance3D3p_interval(IT pax, IT pay, IT paz, IT pbx, IT pby,
                                  IT pbz, IT pcx, IT pcy, IT pcz, int ab_scale)
{
	typename IT::Protector P;

	IT abx   = pbx - pax;
	IT aby   = pby - pay;
	IT abz   = pbz - paz;
	IT abx2  = abx * abx;
	IT aby2  = aby * aby;
	IT abz2  = abz * abz;
	IT t0    = abx2 + aby2;
	IT absqr = t0 + abz2;
	IT acx   = pcx - pax;
	IT acy   = pcy - pay;
	IT acz   = pcz - paz;
	IT acx2  = acx * acx;
	IT acy2  = acy * acy;
	IT acz2  = acz * acz;
	IT t1    = acx2 + acy2;
	IT acsqr = t1 + acz2;
	absqr    = absqr * ab_scale; // add by hand
	IT d     = absqr - acsqr;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign squaredDistance3D3p_exact(ET pax, ET pay, ET paz, ET pbx, ET pby, ET pbz,
                               ET pcx, ET pcy, ET pcz, int ab_scale)
{
	ET abx   = pbx - pax;
	ET aby   = pby - pay;
	ET abz   = pbz - paz;
	ET abx2  = abx * abx;
	ET aby2  = aby * aby;
	ET abz2  = abz * abz;
	ET t0    = abx2 + aby2;
	ET absqr = t0 + abz2;
	ET acx   = pcx - pax;
	ET acy   = pcy - pay;
	ET acz   = pcz - paz;
	ET acx2  = acx * acx;
	ET acy2  = acy * acy;
	ET acz2  = acz * acz;
	ET t1    = acx2 + acy2;
	ET acsqr = t1 + acz2;
	absqr    = absqr * ab_scale; // add by hand
	ET d     = absqr - acsqr;
	return OMC::sign(d);
}

Sign squaredDistance3D3p_expansion(double pax, double pay, double paz,
                                   double pbx, double pby, double pbz,
                                   double pcx, double pcy, double pcz,
                                   int ab_scale)
{
	expansionObject o;
	double          abx[2];
	o.Two_Diff(pbx, pax, abx);
	double aby[2];
	o.Two_Diff(pby, pay, aby);
	double abz[2];
	o.Two_Diff(pbz, paz, abz);
	double abx2[8];
	int    abx2_len = o.Gen_Product(2, abx, 2, abx, abx2);
	double aby2[8];
	int    aby2_len = o.Gen_Product(2, aby, 2, aby, aby2);
	double abz2[8];
	int    abz2_len = o.Gen_Product(2, abz, 2, abz, abz2);
	double t0[16];
	int    t0_len = o.Gen_Sum(abx2_len, abx2, aby2_len, aby2, t0);
	double absqr[24];
	int    absqr_len = o.Gen_Sum(t0_len, t0, abz2_len, abz2, absqr);
	double acx[2];
	o.Two_Diff(pcx, pax, acx);
	double acy[2];
	o.Two_Diff(pcy, pay, acy);
	double acz[2];
	o.Two_Diff(pcz, paz, acz);
	double acx2[8];
	int    acx2_len = o.Gen_Product(2, acx, 2, acx, acx2);
	double acy2[8];
	int    acy2_len = o.Gen_Product(2, acy, 2, acy, acy2);
	double acz2[8];
	int    acz2_len = o.Gen_Product(2, acz, 2, acz, acz2);
	double t1[16];
	int    t1_len = o.Gen_Sum(acx2_len, acx2, acy2_len, acy2, t1);
	double acsqr[24];
	int    acsqr_len = o.Gen_Sum(t1_len, t1, acz2_len, acz2, acsqr);
	// Add by hand
	if (ab_scale > 1) // exactly if ab_scale is power of 2.
		o.ExactScale(absqr_len, absqr, ab_scale);
	double d[48];
	int    d_len = o.Gen_Diff(absqr_len, absqr, acsqr_len, acsqr, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign squaredDistance3D3p(double pax, double pay, double paz, double pbx,
                         double pby, double pbz, double pcx, double pcy,
                         double pcz, int ab_scale)
{
	Sign ret;
	ret = squaredDistance3D3p_interval<IT>(pax, pay, paz, pbx, pby, pbz, pcx, pcy,
	                                       pcz, ab_scale);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance3D3p_expansion(pax, pay, paz, pbx, pby, pbz, pcx, pcy,
	                                     pcz, ab_scale);
}

template <typename IT, typename ET>
Sign squaredDistance3D3p(const GenericPoint3T<IT, ET> &pa,
                         const GenericPoint3T<IT, ET> &pb,
                         const GenericPoint3T<IT, ET> &pc, const int ab_scale)
{
	return squaredDistance3D3p<IT, ET>(pa.x(), pa.y(), pa.z(), pb.x(), pb.y(),
	                                   pb.z(), pc.x(), pc.y(), pc.z(), ab_scale);
}

template <typename IT, typename ET>
Sign squaredDistance2D_IE_interval(const GenericPoint2T<IT, ET> &p, IT qx,
                                   IT qy, IT dis)
{
	IT px, py, d;
	if (!p.getIntervalLambda(px, py, d))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dqx     = d * qx;
	IT dqy     = d * qy;
	IT lx      = px - dqx;
	IT ly      = py - dqy;
	IT lx2     = lx * lx;
	IT ly2     = ly * ly;
	IT sqrnorm = lx2 + ly2;
	IT d2      = d * d;
	IT d2dis   = d2 * dis;
	IT diff    = sqrnorm - d2dis;
	if (!diff.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance2D_IE_exact(const GenericPoint2T<IT, ET> &p, ET qx, ET qy,
                                ET dis)
{
	ET px, py, d;
	p.getExactLambda(px, py, d);
	ET dqx     = d * qx;
	ET dqy     = d * qy;
	ET lx      = px - dqx;
	ET ly      = py - dqy;
	ET lx2     = lx * lx;
	ET ly2     = ly * ly;
	ET sqrnorm = lx2 + ly2;
	ET d2      = d * d;
	ET d2dis   = d2 * dis;
	ET diff    = sqrnorm - d2dis;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance2D_IE_expansion(const GenericPoint2T<IT, ET> &p, double qx,
                                    double qy, double dis)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double px_p[128], *px = px_p, py_p[128], *py = py_p, d_p[128], *d = d_p;
	int    px_len = 128, py_len = 128, d_len = 128;
	p.getExpansionLambda(&px, px_len, &py, py_len, &d, d_len);
	if ((d[d_len - 1] != 0))
	{
		expansionObject o;
		double          dqx_p[128], *dqx = dqx_p;
		int    dqx_len = o.Gen_Scale_With_PreAlloc(d_len, d, qx, &dqx, 128);
		double dqy_p[128], *dqy = dqy_p;
		int    dqy_len = o.Gen_Scale_With_PreAlloc(d_len, d, qy, &dqy, 128);
		double lx_p[128], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(px_len, px, dqx_len, dqx, &lx, 128);
		double ly_p[128], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(py_len, py, dqy_len, dqy, &ly, 128);
		double lx2_p[128], *lx2 = lx2_p;
		int    lx2_len =
		  o.Gen_Product_With_PreAlloc(lx_len, lx, lx_len, lx, &lx2, 128);
		double ly2_p[128], *ly2 = ly2_p;
		int    ly2_len =
		  o.Gen_Product_With_PreAlloc(ly_len, ly, ly_len, ly, &ly2, 128);
		double sqrnorm_p[128], *sqrnorm = sqrnorm_p;
		int    sqrnorm_len =
		  o.Gen_Sum_With_PreAlloc(lx2_len, lx2, ly2_len, ly2, &sqrnorm, 128);
		double d2_p[128], *d2 = d2_p;
		int    d2_len = o.Gen_Product_With_PreAlloc(d_len, d, d_len, d, &d2, 128);
		double d2dis_p[128], *d2dis = d2dis_p;
		int    d2dis_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, dis, &d2dis, 128);
		double diff_p[128], *diff = diff_p;
		int    diff_len = o.Gen_Diff_With_PreAlloc(sqrnorm_len, sqrnorm, d2dis_len,
		                                           d2dis, &diff, 128);

		return_value = diff[diff_len - 1];
		if (diff_p != diff)
			FreeDoubles(diff);
		if (d2dis_p != d2dis)
			FreeDoubles(d2dis);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (sqrnorm_p != sqrnorm)
			FreeDoubles(sqrnorm);
		if (ly2_p != ly2)
			FreeDoubles(ly2);
		if (lx2_p != lx2)
			FreeDoubles(lx2);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (dqy_p != dqy)
			FreeDoubles(dqy);
		if (dqx_p != dqx)
			FreeDoubles(dqx);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (px_p != px)
			FreeDoubles(px);
		if (py_p != py)
			FreeDoubles(py);
		if (d_p != d)
			FreeDoubles(d);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return squaredDistance2D_IE_exact<IT, ET>(p, qx, qy, dis);
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
Sign squaredDistance2D_IE(const GenericPoint2T<IT, ET> &p, double qx, double qy,
                          double dis)
{
	Sign ret;
	ret = squaredDistance2D_IE_interval<IT, ET>(p, qx, qy, dis);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance2D_IE_expansion<IT, ET>(p, qx, qy, dis);
}

template <typename IT, typename ET>
Sign squaredDistance2D_IE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q, double dis)
{
	return squaredDistance2D_IE<IT, ET>(p, q.x(), q.y(), dis);
}

template <typename IT, typename ET>
Sign squaredDistance2D_II_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &q, IT dis)
{
	IT px, py, dp, qx, qy, dq;
	if (!p.getIntervalLambda(px, py, dp) || !q.getIntervalLambda(qx, qy, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dqx     = dp * qx;
	IT dqy     = dp * qy;
	IT dpx     = dq * px;
	IT dpy     = dq * py;
	IT lx      = dpx - dqx;
	IT ly      = dpy - dqy;
	IT lx2     = lx * lx;
	IT ly2     = ly * ly;
	IT sqrnorm = lx2 + ly2;
	IT dp2     = dp * dp;
	IT dq2     = dq * dq;
	IT d2      = dp2 * dq2;
	IT d2dis   = d2 * dis;
	IT diff    = sqrnorm - d2dis;
	if (!diff.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance2D_II_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &q, ET dis)
{
	ET px, py, dp, qx, qy, dq;
	p.getExactLambda(px, py, dp);
	q.getExactLambda(qx, qy, dq);
	ET dqx     = dp * qx;
	ET dqy     = dp * qy;
	ET dpx     = dq * px;
	ET dpy     = dq * py;
	ET lx      = dpx - dqx;
	ET ly      = dpy - dqy;
	ET lx2     = lx * lx;
	ET ly2     = ly * ly;
	ET sqrnorm = lx2 + ly2;
	ET dp2     = dp * dp;
	ET dq2     = dq * dq;
	ET d2      = dp2 * dq2;
	ET d2dis   = d2 * dis;
	ET diff    = sqrnorm - d2dis;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance2D_II_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &q, double dis)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double px_p[64], *px = px_p, py_p[64], *py = py_p, dp_p[64], *dp = dp_p,
	                 qx_p[64], *qx = qx_p, qy_p[64], *qy = qy_p, dq_p[64],
	                 *dq = dq_p;
	int px_len = 64, py_len = 64, dp_len = 64, qx_len = 64, qy_len = 64,
	    dq_len = 64;
	p.getExpansionLambda(&px, px_len, &py, py_len, &dp, dp_len);
	q.getExpansionLambda(&qx, qx_len, &qy, qy_len, &dq, dq_len);
	if ((dp[dp_len - 1] != 0) && (dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          dqx_p[64], *dqx = dqx_p;
		int dqx_len = o.Gen_Product_With_PreAlloc(dp_len, dp, qx_len, qx, &dqx, 64);
		double dqy_p[64], *dqy = dqy_p;
		int dqy_len = o.Gen_Product_With_PreAlloc(dp_len, dp, qy_len, qy, &dqy, 64);
		double dpx_p[64], *dpx = dpx_p;
		int dpx_len = o.Gen_Product_With_PreAlloc(dq_len, dq, px_len, px, &dpx, 64);
		double dpy_p[64], *dpy = dpy_p;
		int dpy_len = o.Gen_Product_With_PreAlloc(dq_len, dq, py_len, py, &dpy, 64);
		double lx_p[64], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(dpx_len, dpx, dqx_len, dqx, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(dpy_len, dpy, dqy_len, dqy, &ly, 64);
		double lx2_p[64], *lx2 = lx2_p;
		int lx2_len = o.Gen_Product_With_PreAlloc(lx_len, lx, lx_len, lx, &lx2, 64);
		double ly2_p[64], *ly2 = ly2_p;
		int ly2_len = o.Gen_Product_With_PreAlloc(ly_len, ly, ly_len, ly, &ly2, 64);
		double sqrnorm_p[64], *sqrnorm = sqrnorm_p;
		int    sqrnorm_len =
		  o.Gen_Sum_With_PreAlloc(lx2_len, lx2, ly2_len, ly2, &sqrnorm, 64);
		double dp2_p[64], *dp2 = dp2_p;
		int dp2_len = o.Gen_Product_With_PreAlloc(dp_len, dp, dp_len, dp, &dp2, 64);
		double dq2_p[64], *dq2 = dq2_p;
		int dq2_len = o.Gen_Product_With_PreAlloc(dq_len, dq, dq_len, dq, &dq2, 64);
		double d2_p[64], *d2 = d2_p;
		int    d2_len =
		  o.Gen_Product_With_PreAlloc(dp2_len, dp2, dq2_len, dq2, &d2, 64);
		double d2dis_p[64], *d2dis = d2dis_p;
		int    d2dis_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, dis, &d2dis, 64);
		double diff_p[64], *diff = diff_p;
		int    diff_len = o.Gen_Diff_With_PreAlloc(sqrnorm_len, sqrnorm, d2dis_len,
		                                           d2dis, &diff, 64);

		return_value = diff[diff_len - 1];
		if (diff_p != diff)
			FreeDoubles(diff);
		if (d2dis_p != d2dis)
			FreeDoubles(d2dis);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (dq2_p != dq2)
			FreeDoubles(dq2);
		if (dp2_p != dp2)
			FreeDoubles(dp2);
		if (sqrnorm_p != sqrnorm)
			FreeDoubles(sqrnorm);
		if (ly2_p != ly2)
			FreeDoubles(ly2);
		if (lx2_p != lx2)
			FreeDoubles(lx2);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (dpy_p != dpy)
			FreeDoubles(dpy);
		if (dpx_p != dpx)
			FreeDoubles(dpx);
		if (dqy_p != dqy)
			FreeDoubles(dqy);
		if (dqx_p != dqx)
			FreeDoubles(dqx);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (px_p != px)
			FreeDoubles(px);
		if (py_p != py)
			FreeDoubles(py);
		if (dp_p != dp)
			FreeDoubles(dp);
		if (qx_p != qx)
			FreeDoubles(qx);
		if (qy_p != qy)
			FreeDoubles(qy);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return squaredDistance2D_II_exact<IT, ET>(p, q, dis);
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
Sign squaredDistance2D_II(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q, double dis)
{
	Sign ret;
	ret = squaredDistance2D_II_interval<IT, ET>(p, q, dis);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance2D_II_expansion<IT, ET>(p, q, dis);
}

template <typename IT, typename ET>
Sign squaredDistance3D_IE_interval(const GenericPoint3T<IT, ET> &p, IT qx,
                                   IT qy, IT qz, IT dis)
{
	IT px, py, pz, d;
	if (!p.getIntervalLambda(px, py, pz, d))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dqx       = d * qx;
	IT dqy       = d * qy;
	IT dqz       = d * qz;
	IT lx        = px - dqx;
	IT ly        = py - dqy;
	IT lz        = pz - dqz;
	IT lx2       = lx * lx;
	IT ly2       = ly * ly;
	IT lz2       = lz * lz;
	IT sqrnormxy = lx2 + ly2;
	IT sqrnorm   = sqrnormxy + lz2;
	IT d2        = d * d;
	IT d2dis     = d2 * dis;
	IT diff      = sqrnorm - d2dis;
	if (!diff.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance3D_IE_exact(const GenericPoint3T<IT, ET> &p, ET qx, ET qy,
                                ET qz, ET dis)
{
	ET px, py, pz, d;
	p.getExactLambda(px, py, pz, d);
	ET dqx       = d * qx;
	ET dqy       = d * qy;
	ET dqz       = d * qz;
	ET lx        = px - dqx;
	ET ly        = py - dqy;
	ET lz        = pz - dqz;
	ET lx2       = lx * lx;
	ET ly2       = ly * ly;
	ET lz2       = lz * lz;
	ET sqrnormxy = lx2 + ly2;
	ET sqrnorm   = sqrnormxy + lz2;
	ET d2        = d * d;
	ET d2dis     = d2 * dis;
	ET diff      = sqrnorm - d2dis;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance3D_IE_expansion(const GenericPoint3T<IT, ET> &p, double qx,
                                    double qy, double qz, double dis)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double px_p[64], *px = px_p, py_p[64], *py = py_p, pz_p[64], *pz = pz_p,
	                 d_p[64], *d = d_p;
	int px_len = 64, py_len = 64, pz_len = 64, d_len = 64;
	p.getExpansionLambda(&px, px_len, &py, py_len, &pz, pz_len, &d, d_len);
	if ((d[d_len - 1] != 0))
	{
		expansionObject o;
		double          dqx_p[64], *dqx = dqx_p;
		int             dqx_len = o.Gen_Scale_With_PreAlloc(d_len, d, qx, &dqx, 64);
		double          dqy_p[64], *dqy = dqy_p;
		int             dqy_len = o.Gen_Scale_With_PreAlloc(d_len, d, qy, &dqy, 64);
		double          dqz_p[64], *dqz = dqz_p;
		int             dqz_len = o.Gen_Scale_With_PreAlloc(d_len, d, qz, &dqz, 64);
		double          lx_p[64], *lx = lx_p;
		int    lx_len = o.Gen_Diff_With_PreAlloc(px_len, px, dqx_len, dqx, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int    ly_len = o.Gen_Diff_With_PreAlloc(py_len, py, dqy_len, dqy, &ly, 64);
		double lz_p[64], *lz = lz_p;
		int    lz_len = o.Gen_Diff_With_PreAlloc(pz_len, pz, dqz_len, dqz, &lz, 64);
		double lx2_p[64], *lx2 = lx2_p;
		int lx2_len = o.Gen_Product_With_PreAlloc(lx_len, lx, lx_len, lx, &lx2, 64);
		double ly2_p[64], *ly2 = ly2_p;
		int ly2_len = o.Gen_Product_With_PreAlloc(ly_len, ly, ly_len, ly, &ly2, 64);
		double lz2_p[64], *lz2 = lz2_p;
		int lz2_len = o.Gen_Product_With_PreAlloc(lz_len, lz, lz_len, lz, &lz2, 64);
		double sqrnormxy_p[64], *sqrnormxy = sqrnormxy_p;
		int    sqrnormxy_len =
		  o.Gen_Sum_With_PreAlloc(lx2_len, lx2, ly2_len, ly2, &sqrnormxy, 64);
		double sqrnorm_p[64], *sqrnorm = sqrnorm_p;
		int sqrnorm_len = o.Gen_Sum_With_PreAlloc(sqrnormxy_len, sqrnormxy, lz2_len,
		                                          lz2, &sqrnorm, 64);
		double d2_p[64], *d2 = d2_p;
		int    d2_len = o.Gen_Product_With_PreAlloc(d_len, d, d_len, d, &d2, 64);
		double d2dis_p[64], *d2dis = d2dis_p;
		int    d2dis_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, dis, &d2dis, 64);
		double diff_p[64], *diff = diff_p;
		int    diff_len = o.Gen_Diff_With_PreAlloc(sqrnorm_len, sqrnorm, d2dis_len,
		                                           d2dis, &diff, 64);

		return_value = diff[diff_len - 1];
		if (diff_p != diff)
			FreeDoubles(diff);
		if (d2dis_p != d2dis)
			FreeDoubles(d2dis);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (sqrnorm_p != sqrnorm)
			FreeDoubles(sqrnorm);
		if (sqrnormxy_p != sqrnormxy)
			FreeDoubles(sqrnormxy);
		if (lz2_p != lz2)
			FreeDoubles(lz2);
		if (ly2_p != ly2)
			FreeDoubles(ly2);
		if (lx2_p != lx2)
			FreeDoubles(lx2);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (dqz_p != dqz)
			FreeDoubles(dqz);
		if (dqy_p != dqy)
			FreeDoubles(dqy);
		if (dqx_p != dqx)
			FreeDoubles(dqx);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (px_p != px)
			FreeDoubles(px);
		if (py_p != py)
			FreeDoubles(py);
		if (pz_p != pz)
			FreeDoubles(pz);
		if (d_p != d)
			FreeDoubles(d);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return squaredDistance3D_IE_exact<IT, ET>(p, qx, qy, qz, dis);
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
Sign squaredDistance3D_IE(const GenericPoint3T<IT, ET> &p, double qx, double qy,
                          double qz, double dis)
{
	Sign ret;
	ret = squaredDistance3D_IE_interval<IT, ET>(p, qx, qy, qz, dis);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance3D_IE_expansion<IT, ET>(p, qx, qy, qz, dis);
}

template <typename IT, typename ET>
Sign squaredDistance3D_IE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q, double dis)
{
	return squaredDistance3D_IE<IT, ET>(p, q.x(), q.y(), q.z(), dis);
}

template <typename IT, typename ET>
Sign squaredDistance3D_II_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &q, IT dis)
{
	IT px, py, pz, dp, qx, qy, qz, dq;
	if (!p.getIntervalLambda(px, py, pz, dp) ||
	    !q.getIntervalLambda(qx, qy, qz, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dqx       = dp * qx;
	IT dqy       = dp * qy;
	IT dqz       = dp * qz;
	IT dpx       = dq * qx;
	IT dpy       = dq * qy;
	IT dpz       = dq * qz;
	IT lx        = dpx - dqx;
	IT ly        = dpy - dqy;
	IT lz        = dpz - dqz;
	IT lx2       = lx * lx;
	IT ly2       = ly * ly;
	IT lz2       = lz * lz;
	IT sqrnormxy = lx2 + ly2;
	IT sqrnorm   = sqrnormxy + lz2;
	IT dp2       = dp * dp;
	IT dq2       = dq * dq;
	IT d2        = dp2 * dq2;
	IT d2dis     = d2 * dis;
	IT diff      = sqrnorm - d2dis;
	if (!diff.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance3D_II_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &q, ET dis)
{
	ET px, py, pz, dp, qx, qy, qz, dq;
	p.getExactLambda(px, py, pz, dp);
	q.getExactLambda(qx, qy, qz, dq);
	ET dqx       = dp * qx;
	ET dqy       = dp * qy;
	ET dqz       = dp * qz;
	ET dpx       = dq * qx;
	ET dpy       = dq * qy;
	ET dpz       = dq * qz;
	ET lx        = dpx - dqx;
	ET ly        = dpy - dqy;
	ET lz        = dpz - dqz;
	ET lx2       = lx * lx;
	ET ly2       = ly * ly;
	ET lz2       = lz * lz;
	ET sqrnormxy = lx2 + ly2;
	ET sqrnorm   = sqrnormxy + lz2;
	ET dp2       = dp * dp;
	ET dq2       = dq * dq;
	ET d2        = dp2 * dq2;
	ET d2dis     = d2 * dis;
	ET diff      = sqrnorm - d2dis;
	return OMC::sign(diff);
}

template <typename IT, typename ET>
Sign squaredDistance3D_II_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &q, double dis)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double px_p[64], *px = px_p, py_p[64], *py = py_p, pz_p[64], *pz = pz_p,
	                 dp_p[64], *dp = dp_p, qx_p[64], *qx = qx_p, qy_p[64],
	                 *qy = qy_p, qz_p[64], *qz = qz_p, dq_p[64], *dq = dq_p;
	int px_len = 64, py_len = 64, pz_len = 64, dp_len = 64, qx_len = 64,
	    qy_len = 64, qz_len = 64, dq_len = 64;
	p.getExpansionLambda(&px, px_len, &py, py_len, &pz, pz_len, &dp, dp_len);
	q.getExpansionLambda(&qx, qx_len, &qy, qy_len, &qz, qz_len, &dq, dq_len);
	if ((dp[dp_len - 1] != 0) && (dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          dqx_p[64], *dqx = dqx_p;
		int dqx_len = o.Gen_Product_With_PreAlloc(dp_len, dp, qx_len, qx, &dqx, 64);
		double dqy_p[64], *dqy = dqy_p;
		int dqy_len = o.Gen_Product_With_PreAlloc(dp_len, dp, qy_len, qy, &dqy, 64);
		double dqz_p[64], *dqz = dqz_p;
		int dqz_len = o.Gen_Product_With_PreAlloc(dp_len, dp, qz_len, qz, &dqz, 64);
		double dpx_p[64], *dpx = dpx_p;
		int dpx_len = o.Gen_Product_With_PreAlloc(dq_len, dq, qx_len, qx, &dpx, 64);
		double dpy_p[64], *dpy = dpy_p;
		int dpy_len = o.Gen_Product_With_PreAlloc(dq_len, dq, qy_len, qy, &dpy, 64);
		double dpz_p[64], *dpz = dpz_p;
		int dpz_len = o.Gen_Product_With_PreAlloc(dq_len, dq, qz_len, qz, &dpz, 64);
		double lx_p[64], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(dpx_len, dpx, dqx_len, dqx, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(dpy_len, dpy, dqy_len, dqy, &ly, 64);
		double lz_p[64], *lz = lz_p;
		int lz_len = o.Gen_Diff_With_PreAlloc(dpz_len, dpz, dqz_len, dqz, &lz, 64);
		double lx2_p[64], *lx2 = lx2_p;
		int lx2_len = o.Gen_Product_With_PreAlloc(lx_len, lx, lx_len, lx, &lx2, 64);
		double ly2_p[64], *ly2 = ly2_p;
		int ly2_len = o.Gen_Product_With_PreAlloc(ly_len, ly, ly_len, ly, &ly2, 64);
		double lz2_p[64], *lz2 = lz2_p;
		int lz2_len = o.Gen_Product_With_PreAlloc(lz_len, lz, lz_len, lz, &lz2, 64);
		double sqrnormxy_p[64], *sqrnormxy = sqrnormxy_p;
		int    sqrnormxy_len =
		  o.Gen_Sum_With_PreAlloc(lx2_len, lx2, ly2_len, ly2, &sqrnormxy, 64);
		double sqrnorm_p[64], *sqrnorm = sqrnorm_p;
		int sqrnorm_len = o.Gen_Sum_With_PreAlloc(sqrnormxy_len, sqrnormxy, lz2_len,
		                                          lz2, &sqrnorm, 64);
		double dp2_p[64], *dp2 = dp2_p;
		int dp2_len = o.Gen_Product_With_PreAlloc(dp_len, dp, dp_len, dp, &dp2, 64);
		double dq2_p[64], *dq2 = dq2_p;
		int dq2_len = o.Gen_Product_With_PreAlloc(dq_len, dq, dq_len, dq, &dq2, 64);
		double d2_p[64], *d2 = d2_p;
		int    d2_len =
		  o.Gen_Product_With_PreAlloc(dp2_len, dp2, dq2_len, dq2, &d2, 64);
		double d2dis_p[64], *d2dis = d2dis_p;
		int    d2dis_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, dis, &d2dis, 64);
		double diff_p[64], *diff = diff_p;
		int    diff_len = o.Gen_Diff_With_PreAlloc(sqrnorm_len, sqrnorm, d2dis_len,
		                                           d2dis, &diff, 64);

		return_value = diff[diff_len - 1];
		if (diff_p != diff)
			FreeDoubles(diff);
		if (d2dis_p != d2dis)
			FreeDoubles(d2dis);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (dq2_p != dq2)
			FreeDoubles(dq2);
		if (dp2_p != dp2)
			FreeDoubles(dp2);
		if (sqrnorm_p != sqrnorm)
			FreeDoubles(sqrnorm);
		if (sqrnormxy_p != sqrnormxy)
			FreeDoubles(sqrnormxy);
		if (lz2_p != lz2)
			FreeDoubles(lz2);
		if (ly2_p != ly2)
			FreeDoubles(ly2);
		if (lx2_p != lx2)
			FreeDoubles(lx2);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (dpz_p != dpz)
			FreeDoubles(dpz);
		if (dpy_p != dpy)
			FreeDoubles(dpy);
		if (dpx_p != dpx)
			FreeDoubles(dpx);
		if (dqz_p != dqz)
			FreeDoubles(dqz);
		if (dqy_p != dqy)
			FreeDoubles(dqy);
		if (dqx_p != dqx)
			FreeDoubles(dqx);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (px_p != px)
			FreeDoubles(px);
		if (py_p != py)
			FreeDoubles(py);
		if (pz_p != pz)
			FreeDoubles(pz);
		if (dp_p != dp)
			FreeDoubles(dp);
		if (qx_p != qx)
			FreeDoubles(qx);
		if (qy_p != qy)
			FreeDoubles(qy);
		if (qz_p != qz)
			FreeDoubles(qz);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return squaredDistance3D_II_exact<IT, ET>(p, q, dis);
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
Sign squaredDistance3D_II(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q, double dis)
{
	Sign ret;
	ret = squaredDistance3D_II_interval<IT, ET>(p, q, dis);
	if (is_sign_reliable(ret))
		return ret;
	return squaredDistance3D_II_expansion<IT, ET>(p, q, dis);
}
} // namespace OMC