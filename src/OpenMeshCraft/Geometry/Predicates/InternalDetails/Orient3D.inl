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

inline Sign orient3d_filtered(double px, double py, double pz, double qx,
                              double qy, double qz, double rx, double ry,
                              double rz, double sx, double sy, double sz);

inline Sign orient3d_expansion(double px, double py, double pz, double qx,
                               double qy, double qz, double rx, double ry,
                               double rz, double sx, double sy, double sz);

inline Sign orient3d(double px, double py, double pz, double qx, double qy,
                     double qz, double rx, double ry, double rz, double sx,
                     double sy, double sz);

inline Sign orient3d(const double *p, const double *q, const double *r,
                     const double *s);

template <typename IT, typename ET>
Sign orient3d(const GenericPoint3T<IT, ET> &p, const GenericPoint3T<IT, ET> &q,
              const GenericPoint3T<IT, ET> &r, const GenericPoint3T<IT, ET> &s);

// generally, pb, pc and pd come from three vertices of a triangle.
// this convention keeps consistent with shewchuk predicates.
inline void orient3d_get_minors(const double *pa, const double *pb,
                                const double *pc, double *minor, double *perm);

// generally, pb, pc and pd come from three vertices of a triangle,
// pa is the fourth query point.
// this convention keeps consistent with shewchuk predicates.
inline Sign orient3d_with_cached_minors(const double *pa, const double *pb,
                                        const double *pc, const double *pd,
                                        const double *minor,
                                        const double *perm);

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

template <typename IT, typename ET>
Sign orient3D_IEEE_interval(const GenericPoint3T<IT, ET> &p1, IT ax, IT ay,
                            IT az, IT bx, IT by, IT bz, IT cx, IT cy, IT cz);

template <typename IT, typename ET>
Sign orient3D_IEEE_exact(const GenericPoint3T<IT, ET> &p1, ET ax, ET ay, ET az,
                         ET bx, ET by, ET bz, ET cx, ET cy, ET cz);

template <typename IT, typename ET>
Sign orient3D_IEEE_expansion(const GenericPoint3T<IT, ET> &p1, double ax,
                             double ay, double az, double bx, double by,
                             double bz, double cx, double cy, double cz);

template <typename IT, typename ET>
Sign orient3D_IEEE(const GenericPoint3T<IT, ET> &p1, double ax, double ay,
                   double az, double bx, double by, double bz, double cx,
                   double cy, double cz);

template <typename IT, typename ET>
Sign orient3D_IEEE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &a,
                   const GenericPoint3T<IT, ET> &b,
                   const GenericPoint3T<IT, ET> &c);

template <typename IT, typename ET>
Sign orient3D_IIEE_interval(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, IT p3x, IT p3y,
                            IT p3z, IT p4x, IT p4y, IT p4z);

template <typename IT, typename ET>
Sign orient3D_IIEE_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2, ET p3x, ET p3y,
                         ET p3z, ET p4x, ET p4y, ET p4z);

template <typename IT, typename ET>
Sign orient3D_IIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2, double p3x,
                             double p3y, double p3z, double p4x, double p4y,
                             double p4z);

template <typename IT, typename ET>
Sign orient3D_IIEE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2, double p3x, double p3y,
                   double p3z, double p4x, double p4y, double p4z);

template <typename IT, typename ET>
Sign orient3D_IIEE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign orient3D_IIIE_interval(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3, IT p4x, IT p4y,
                            IT p4z);

template <typename IT, typename ET>
Sign orient3D_IIIE_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3, ET p4x, ET p4y,
                         ET p4z);

template <typename IT, typename ET>
Sign orient3D_IIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3, double p4x,
                             double p4y, double p4z);

template <typename IT, typename ET>
Sign orient3D_IIIE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3, double p4x, double p4y,
                   double p4z);

template <typename IT, typename ET>
Sign orient3D_IIIE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign orient3D_IIII_interval(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3,
                            const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign orient3D_IIII_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign orient3D_IIII_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3,
                             const GenericPoint3T<IT, ET> &p4);

template <typename IT, typename ET>
Sign orient3D_IIII(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline Sign orient3d_filtered(double px, double py, double pz, double qx,
                              double qy, double qz, double rx, double ry,
                              double rz, double sx, double sy, double sz)
{
	double fadx, fbdx, fcdx, fady, fbdy, fcdy, fadz, fbdz, fcdz, eb;
	double fbdxcdy, fcdxbdy, fcdxady, fadxcdy, fadxbdy, fbdxady, det;

	fadx = qx - px;
	fbdx = rx - px;
	fcdx = sx - px;
	fady = qy - py;
	fbdy = ry - py;
	fcdy = sy - py;
	fadz = qz - pz;
	fbdz = rz - pz;
	fcdz = sz - pz;

	fbdxcdy = fbdx * fcdy * fadz;
	fcdxbdy = fcdx * fbdy * fadz;
	fcdxady = fcdx * fady * fbdz;
	fadxcdy = fadx * fcdy * fbdz;
	fadxbdy = fadx * fbdy * fcdz;
	fbdxady = fbdx * fady * fcdz;

	det = (fbdxcdy - fcdxbdy) + (fcdxady - fadxcdy) + (fadxbdy - fbdxady);
	eb =
	  7.7715611723761027e-016 * (fabs(fbdxcdy) + fabs(fcdxbdy) + fabs(fcdxady) +
	                             fabs(fadxcdy) + fabs(fadxbdy) + fabs(fbdxady));
	return filter_sign(det, eb);
}

inline void supo3d1(double *c1, double *c2, double *c3, double *c4, double *c5,
                    double *c6, double *a1, double *a2, double &i, double *k1,
                    double *k2, double *k3, double *k4, int &l1, int &l2)
{
	expansionObject o;
	if (c1[0] == 0.0)
	{
		if (c2[0] == 0.0)
		{
			a1[0] = a2[0] = 0.0;
			l1 = l2 = 1;
		}
		else
		{
			i = -c2[0];
			o.Two_Prod(i, c3[1], a1);
			o.Two_Prod(c2[0], c4[1], a2);
			l1 = l2 = 2;
		}
	}
	else
	{
		if (c2[0] == 0.0)
		{
			i = -c1[0];
			o.Two_Prod(c1[0], c5[1], a1);
			o.Two_Prod(i, c6[1], a2);
			l1 = l2 = 2;
		}
		else
		{
			o.Two_Prod(c1[0], c5[1], k1);
			o.Two_Prod(c2[0], c3[1], k2);
			o.Two_Two_Diff(k1, k2, a1);
			o.Two_Prod(c2[0], c4[1], k3);
			o.Two_Prod(c1[0], c6[1], k4);
			o.Two_Two_Diff(k3, k4, a2);
			l1 = l2 = 4;
		}
	}
}

inline void supo3d2(double *c1, double *c2, double *c3, double *c4, double *u,
                    int &fl, double fin[2][192], int &wh, double *c5, double &i,
                    double *c6, double *c7)

{
	expansionObject o;
	if (c1[0] != 0.0)
	{
		if (c2[0] != 0.0)
		{
			o.Two_Prod(c1[0], c2[0], c3);
			o.Two_One_Prod(c3, c4[1], u);
			fl = o.Gen_Sum(fl, fin[wh], 4, u, fin[!wh]);
			wh = !wh;
			if (c4[0] != 0.0)
			{
				o.Two_One_Prod(c3, c4[0], u);
				fl = o.Gen_Sum(fl, fin[wh], 4, u, fin[!wh]);
				wh = !wh;
			}
		}
		if (c5[0] != 0.0)
		{
			i = -c1[0];
			o.Two_Prod(i, c5[0], c6);
			o.Two_One_Prod(c6, c7[1], u);
			fl = o.Gen_Sum(fl, fin[wh], 4, u, fin[!wh]);
			wh = !wh;
			if (c7[0] != 0.0)
			{
				o.Two_One_Prod(c6, c7[0], u);
				fl = o.Gen_Sum(fl, fin[wh], 4, u, fin[!wh]);
				wh = !wh;
			}
		}
	}
}

inline Sign orient3d_expansion(double pdx, double pdy, double pdz, double pax,
                               double pay, double paz, double pbx, double pby,
                               double pbz, double pcx, double pcy, double pcz)
{
	expansionObject o;
	double          eb, det;
	double adx[2], bdx[2], cdx[2], ady[2], bdy[2], cdy[2], adz[2], bdz[2], cdz[2];
	double bdxcdy[2], cdxbdy[2], cdxady[2], adxcdy[2], adxbdy[2], bdxady[2];
	double bc[4], ca[4], ab[4];
	double bdxt_cdy[2], cdxt_bdy[2], cdxt_ady[2];
	double adxt_cdy[2], adxt_bdy[2], bdxt_ady[2];
	double bdyt_cdx[2], cdyt_bdx[2], cdyt_adx[2];
	double adyt_cdx[2], adyt_bdx[2], bdyt_adx[2];
	double bdxt_cdyt[2], cdxt_bdyt[2], cdxt_adyt[2];
	double adxt_cdyt[2], adxt_bdyt[2], bdxt_adyt[2];
	double u[4], v[12], w[16];
	double adet[8], bdet[8], cdet[8], abdet[16];
	double fin[2][192];
	int    wh = 0;
	double at_b[4], at_c[4], bt_c[4], bt_a[4], ct_a[4], ct_b[4];
	double bct[8], cat[8], abt[8];
	int    alen, blen, clen, finlen, vlen, wlen;
	int    at_blen, at_clen, bt_clen, bt_alen, ct_alen, ct_blen;
	int    bctlen, catlen, abtlen;
	int    ablen;
	double inv;
	int    ri;

	adx[1] = pax - pdx;
	bdx[1] = pbx - pdx;
	cdx[1] = pcx - pdx;
	ady[1] = pay - pdy;
	bdy[1] = pby - pdy;
	cdy[1] = pcy - pdy;
	adz[1] = paz - pdz;
	bdz[1] = pbz - pdz;
	cdz[1] = pcz - pdz;

	o.Two_Prod(bdx[1], cdy[1], bdxcdy);
	o.Two_Prod(cdx[1], bdy[1], cdxbdy);
	o.Two_Two_Diff(bdxcdy, cdxbdy, bc);
	alen = o.Gen_Scale(4, bc, adz[1], adet);

	o.Two_Prod(cdx[1], ady[1], cdxady);
	o.Two_Prod(adx[1], cdy[1], adxcdy);
	o.Two_Two_Diff(cdxady, adxcdy, ca);
	blen = o.Gen_Scale(4, ca, bdz[1], bdet);

	o.Two_Prod(adx[1], bdy[1], adxbdy);
	o.Two_Prod(bdx[1], ady[1], bdxady);
	o.Two_Two_Diff(adxbdy, bdxady, ab);
	clen = o.Gen_Scale(4, ab, cdz[1], cdet);

	ablen  = o.Gen_Sum(alen, adet, blen, bdet, abdet);
	finlen = o.Gen_Sum(ablen, abdet, clen, cdet, fin[wh]);

	double xx1 = bdxcdy[1] * adz[1];
	double xx2 = cdxbdy[1] * adz[1];
	double yy1 = cdxady[1] * bdz[1];
	double yy2 = adxcdy[1] * bdz[1];
	double zz1 = adxbdy[1] * cdz[1];
	double zz2 = bdxady[1] * cdz[1];
	double pm =
	  fabs(xx1) + fabs(xx2) + fabs(yy1) + fabs(yy2) + fabs(zz1) + fabs(zz2);

	det = o.To_Double(finlen, fin[wh]);
	eb  = 3.3306690738754731e-016 * pm;
	ri  = (det >= eb) - (-det >= eb);
	if (ri)
		return static_cast<Sign>(ri);

	o.Two_Diff_Back(pax, pdx, adx);
	o.Two_Diff_Back(pbx, pdx, bdx);
	o.Two_Diff_Back(pcx, pdx, cdx);
	o.Two_Diff_Back(pay, pdy, ady);
	o.Two_Diff_Back(pby, pdy, bdy);
	o.Two_Diff_Back(pcy, pdy, cdy);
	o.Two_Diff_Back(paz, pdz, adz);
	o.Two_Diff_Back(pbz, pdz, bdz);
	o.Two_Diff_Back(pcz, pdz, cdz);

	if ((adx[0] == 0.0) && (bdx[0] == 0.0) && (cdx[0] == 0.0) &&
	    (ady[0] == 0.0) && (bdy[0] == 0.0) && (cdy[0] == 0.0) &&
	    (adz[0] == 0.0) && (bdz[0] == 0.0) && (cdz[0] == 0.0))
		return static_cast<Sign>((det > 0) - (det < 0));

	eb = 3.2047474274603644e-031 * pm + 1.1102230246251565e-016 * fabs(det);
	det += (adz[1] * ((bdx[1] * cdy[0] + cdy[1] * bdx[0]) -
	                  (bdy[1] * cdx[0] + cdx[1] * bdy[0])) +
	        adz[0] * (bdx[1] * cdy[1] - bdy[1] * cdx[1])) +
	       (bdz[1] * ((cdx[1] * ady[0] + ady[1] * cdx[0]) -
	                  (cdy[1] * adx[0] + adx[1] * cdy[0])) +
	        bdz[0] * (cdx[1] * ady[1] - cdy[1] * adx[1])) +
	       (cdz[1] * ((adx[1] * bdy[0] + bdy[1] * adx[0]) -
	                  (ady[1] * bdx[0] + bdx[1] * ady[0])) +
	        cdz[0] * (adx[1] * bdy[1] - ady[1] * bdx[1]));
	ri = (det >= eb) - (-det >= eb);
	if (ri)
		return static_cast<Sign>(ri);

	// Filters did not work. Compute exactly...
	supo3d1(adx, ady, bdx, cdx, bdy, cdy, at_b, at_c, inv, adxt_bdy, adyt_bdx,
	        adyt_cdx, adxt_cdy, at_blen, at_clen);

	supo3d1(bdx, bdy, cdx, adx, cdy, ady, bt_c, bt_a, inv, bdxt_cdy, bdyt_cdx,
	        bdyt_adx, bdxt_ady, bt_alen, bt_clen);

	supo3d1(cdx, cdy, adx, bdx, ady, bdy, ct_a, ct_b, inv, cdxt_ady, cdyt_adx,
	        cdyt_bdx, cdxt_bdy, ct_alen, ct_blen);

	bctlen = o.Gen_Sum(bt_clen, bt_c, ct_blen, ct_b, bct);
	wlen   = o.Gen_Scale(bctlen, bct, adz[1], w);
	finlen = o.Gen_Sum(finlen, fin[wh], wlen, w, fin[(!wh)]);
	wh     = !wh;

	catlen = o.Gen_Sum(ct_alen, ct_a, at_clen, at_c, cat);
	wlen   = o.Gen_Scale(catlen, cat, bdz[1], w);
	finlen = o.Gen_Sum(finlen, fin[wh], wlen, w, fin[(!wh)]);
	wh     = !wh;

	abtlen = o.Gen_Sum(at_blen, at_b, bt_alen, bt_a, abt);
	wlen   = o.Gen_Scale(abtlen, abt, cdz[1], w);
	finlen = o.Gen_Sum(finlen, fin[wh], wlen, w, fin[(!wh)]);
	wh     = !wh;

	if (adz[0] != 0.0)
	{
		vlen   = o.Gen_Scale(4, bc, adz[0], v);
		finlen = o.Gen_Sum(finlen, fin[wh], vlen, v, fin[(!wh)]);
		wh     = !wh;
	}
	if (bdz[0] != 0.0)
	{
		vlen   = o.Gen_Scale(4, ca, bdz[0], v);
		finlen = o.Gen_Sum(finlen, fin[wh], vlen, v, fin[(!wh)]);
		wh     = !wh;
	}
	if (cdz[0] != 0.0)
	{
		vlen   = o.Gen_Scale(4, ab, cdz[0], v);
		finlen = o.Gen_Sum(finlen, fin[wh], vlen, v, fin[(!wh)]);
		wh     = !wh;
	}

	supo3d2(adx, bdy, adxt_bdyt, cdz, u, finlen, fin, wh, cdy, inv, adxt_cdyt,
	        bdz);
	supo3d2(bdx, cdy, bdxt_cdyt, adz, u, finlen, fin, wh, ady, inv, bdxt_adyt,
	        cdz);
	supo3d2(cdx, ady, cdxt_adyt, bdz, u, finlen, fin, wh, bdy, inv, cdxt_bdyt,
	        adz);

	if (adz[0] != 0.0)
	{
		wlen   = o.Gen_Scale(bctlen, bct, adz[0], w);
		finlen = o.Gen_Sum(finlen, fin[wh], wlen, w, fin[!wh]);
		wh     = !wh;
	}
	if (bdz[0] != 0.0)
	{
		wlen   = o.Gen_Scale(catlen, cat, bdz[0], w);
		finlen = o.Gen_Sum(finlen, fin[wh], wlen, w, fin[!wh]);
		wh     = !wh;
	}
	if (cdz[0] != 0.0)
	{
		wlen   = o.Gen_Scale(abtlen, abt, cdz[0], w);
		finlen = o.Gen_Sum(finlen, fin[wh], wlen, w, fin[!wh]);
		wh     = !wh;
	}

	det = fin[wh][finlen - 1];
	return static_cast<Sign>((det > 0) - (det < 0));
}

inline Sign orient3d(double px, double py, double pz, double qx, double qy,
                     double qz, double rx, double ry, double rz, double sx,
                     double sy, double sz)
{
	Sign ret;
	ret = orient3d_filtered(px, py, pz, qx, qy, qz, rx, ry, rz, sx, sy, sz);
	if (is_sign_reliable(ret))
		return ret;
	return orient3d_expansion(px, py, pz, qx, qy, qz, rx, ry, rz, sx, sy, sz);
}

inline Sign orient3d(const double *p, const double *q, const double *r,
                     const double *s)
{
#ifdef OMC_NO_SHEWCHUK
	return orient3d(p[0], p[1], p[2], q[0], q[1], q[2], r[0], r[1], r[2], s[0],
	                s[1], s[2]);
#else
	return OMC::sign(::orient3d(s, q, r, p));
#endif
}

template <typename IT, typename ET>
Sign orient3d(const GenericPoint3T<IT, ET> &p, const GenericPoint3T<IT, ET> &q,
              const GenericPoint3T<IT, ET> &r, const GenericPoint3T<IT, ET> &s)
{
#ifdef OMC_NO_SHEWCHUK
	return orient3d(p.x(), p.y(), p.z(), q.x(), q.y(), q.z(), r.x(), r.y(), r.z(),
	                s.x(), s.y(), s.z());
#else
	return OMC::sign(::orient3d(s.data(), q.data(), r.data(), p.data()));
#endif
}

inline void orient3d_get_minors(const double *pa, const double *pb,
                                const double *pc, double *minor, double *perm)
{
#ifdef OMC_NO_SHEWCHUK
	const double bax = pb[0] - pa[0];
	const double cax = pc[0] - pa[0];
	const double bay = pb[1] - pa[1];
	const double cay = pc[1] - pa[1];
	const double baz = pb[2] - pa[2];
	const double caz = pc[2] - pa[2];

	const double baxcaz = bax * caz;
	const double caybaz = cay * baz;
	minor[0]            = baxcaz - caybaz;
	perm[0]             = OMC::abs(baxcaz) + OMC::abs(caybaz);

	const double baxcaz = bax * caz;
	const double caxbaz = cax * baz;
	minor[1]            = caxbaz - baxcaz;
	perm[1]             = OMC::abs(caxbaz) + OMC::abs(baxcaz);

	const double baxcay = bax * cay;
	const double caxbax = cax * bax;
	minor[2]            = baxcay - caxbax;
	perm[2]             = OMC::abs(baxcay) + OMC::abs(caxbax);
#else
	::orient3d_get_minors(pb, pc, pa, minor, perm);
#endif
}

inline Sign orient3d_with_cached_minors(const double *pa, const double *pb,
                                        const double *pc, const double *pd,
                                        const double *minor, const double *perm)
{
#ifdef OMC_NO_SHEWCHUK
	const double dax = pd[0] - pa[0];
	const double day = pd[1] - pa[1];
	const double daz = pd[2] - pa[2];

	const double det = dax * minor[0] + day * minor[1] + daz * minor[2];

	const double permanent =
	  OMC::abs(adx) * perm[0] + OMC::abs(ady) * perm[1] + OMC::abs(adz) * perm[2];

	const double errbound = 7.7715611723761027e-16 * permanent;
	if ((det > errbound) || (-det > errbound))
	{
		return OMC::sign(det);
	}

	return orient3d_expansion(pa[0], pa[1], pa[2], pb[0], pb[1], pb[2], pc[0],
	                          pc[1], pc[2], pd[0], pd[1], pd[2]);
#else
	return OMC::sign(::orient3d_with_cached_minors(
	  pd, pb, pc, pa, const_cast<double *>(minor), const_cast<double *>(perm)));
#endif
}

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

template <typename IT, typename ET>
Sign orient3D_IEEE_interval(const GenericPoint3T<IT, ET> &p1, IT p2x, IT p2y,
                            IT p2z, IT p3x, IT p3y, IT p3z, IT p4x, IT p4y,
                            IT p4z)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dp4x    = d1 * p4x;
	IT dp4y    = d1 * p4y;
	IT dp4z    = d1 * p4z;
	IT ix_p4x  = l1x - dp4x;
	IT iy_p4y  = l1y - dp4y;
	IT iz_p4z  = l1z - dp4z;
	IT p2x_p4x = p2x - p4x;
	IT p2y_p4y = p2y - p4y;
	IT p2z_p4z = p2z - p4z;
	IT p3x_p4x = p3x - p4x;
	IT p3y_p4y = p3y - p4y;
	IT p3z_p4z = p3z - p4z;
	IT t0      = ix_p4x * p2y_p4y;
	IT t1      = iy_p4y * p2x_p4x;
	IT m01     = t0 - t1;
	IT t2      = ix_p4x * p2z_p4z;
	IT t3      = iz_p4z * p2x_p4x;
	IT m02     = t2 - t3;
	IT t4      = iy_p4y * p2z_p4z;
	IT t5      = iz_p4z * p2y_p4y;
	IT m12     = t4 - t5;
	IT mt1     = m01 * p3z_p4z;
	IT mt2     = m02 * p3y_p4y;
	IT mt3     = m12 * p3x_p4x;
	IT mtt     = mt2 - mt1;
	IT m012    = mtt - mt3;
	if (!m012.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IEEE_exact(const GenericPoint3T<IT, ET> &p1, ET p2x, ET p2y,
                         ET p2z, ET p3x, ET p3y, ET p3z, ET p4x, ET p4y, ET p4z)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET dp4x    = d1 * p4x;
	ET dp4y    = d1 * p4y;
	ET dp4z    = d1 * p4z;
	ET ix_p4x  = l1x - dp4x;
	ET iy_p4y  = l1y - dp4y;
	ET iz_p4z  = l1z - dp4z;
	ET p2x_p4x = p2x - p4x;
	ET p2y_p4y = p2y - p4y;
	ET p2z_p4z = p2z - p4z;
	ET p3x_p4x = p3x - p4x;
	ET p3y_p4y = p3y - p4y;
	ET p3z_p4z = p3z - p4z;
	ET t0      = ix_p4x * p2y_p4y;
	ET t1      = iy_p4y * p2x_p4x;
	ET m01     = t0 - t1;
	ET t2      = ix_p4x * p2z_p4z;
	ET t3      = iz_p4z * p2x_p4x;
	ET m02     = t2 - t3;
	ET t4      = iy_p4y * p2z_p4z;
	ET t5      = iz_p4z * p2y_p4y;
	ET m12     = t4 - t5;
	ET mt1     = m01 * p3z_p4z;
	ET mt2     = m02 * p3y_p4y;
	ET mt3     = m12 * p3x_p4x;
	ET mtt     = mt2 - mt1;
	ET m012    = mtt - mt3;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IEEE_expansion(const GenericPoint3T<IT, ET> &p1, double p2x,
                             double p2y, double p2z, double p3x, double p3y,
                             double p3z, double p4x, double p4y, double p4z)
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
		double          dp4x_p[64], *dp4x = dp4x_p;
		int    dp4x_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4x, &dp4x, 64);
		double dp4y_p[64], *dp4y = dp4y_p;
		int    dp4y_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4y, &dp4y, 64);
		double dp4z_p[64], *dp4z = dp4z_p;
		int    dp4z_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4z, &dp4z, 64);
		double ix_p4x_p[64], *ix_p4x = ix_p4x_p;
		int    ix_p4x_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, dp4x_len, dp4x, &ix_p4x, 64);
		double iy_p4y_p[64], *iy_p4y = iy_p4y_p;
		int    iy_p4y_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, dp4y_len, dp4y, &iy_p4y, 64);
		double iz_p4z_p[64], *iz_p4z = iz_p4z_p;
		int    iz_p4z_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, dp4z_len, dp4z, &iz_p4z, 64);
		double p2x_p4x[2];
		o.Two_Diff(p2x, p4x, p2x_p4x);
		double p2y_p4y[2];
		o.Two_Diff(p2y, p4y, p2y_p4y);
		double p2z_p4z[2];
		o.Two_Diff(p2z, p4z, p2z_p4z);
		double p3x_p4x[2];
		o.Two_Diff(p3x, p4x, p3x_p4x);
		double p3y_p4y[2];
		o.Two_Diff(p3y, p4y, p3y_p4y);
		double p3z_p4z[2];
		o.Two_Diff(p3z, p4z, p3z_p4z);
		double t0_p[64], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Product_With_PreAlloc(ix_p4x_len, ix_p4x, 2, p2y_p4y, &t0, 64);
		double t1_p[64], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Product_With_PreAlloc(iy_p4y_len, iy_p4y, 2, p2x_p4x, &t1, 64);
		double m01_p[64], *m01 = m01_p;
		int    m01_len = o.Gen_Diff_With_PreAlloc(t0_len, t0, t1_len, t1, &m01, 64);
		double t2_p[64], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Product_With_PreAlloc(ix_p4x_len, ix_p4x, 2, p2z_p4z, &t2, 64);
		double t3_p[64], *t3 = t3_p;
		int    t3_len =
		  o.Gen_Product_With_PreAlloc(iz_p4z_len, iz_p4z, 2, p2x_p4x, &t3, 64);
		double m02_p[64], *m02 = m02_p;
		int    m02_len = o.Gen_Diff_With_PreAlloc(t2_len, t2, t3_len, t3, &m02, 64);
		double t4_p[64], *t4 = t4_p;
		int    t4_len =
		  o.Gen_Product_With_PreAlloc(iy_p4y_len, iy_p4y, 2, p2z_p4z, &t4, 64);
		double t5_p[64], *t5 = t5_p;
		int    t5_len =
		  o.Gen_Product_With_PreAlloc(iz_p4z_len, iz_p4z, 2, p2y_p4y, &t5, 64);
		double m12_p[64], *m12 = m12_p;
		int    m12_len = o.Gen_Diff_With_PreAlloc(t4_len, t4, t5_len, t5, &m12, 64);
		double mt1_p[64], *mt1 = mt1_p;
		int    mt1_len =
		  o.Gen_Product_With_PreAlloc(m01_len, m01, 2, p3z_p4z, &mt1, 64);
		double mt2_p[64], *mt2 = mt2_p;
		int    mt2_len =
		  o.Gen_Product_With_PreAlloc(m02_len, m02, 2, p3y_p4y, &mt2, 64);
		double mt3_p[64], *mt3 = mt3_p;
		int    mt3_len =
		  o.Gen_Product_With_PreAlloc(m12_len, m12, 2, p3x_p4x, &mt3, 64);
		double mtt_p[64], *mtt = mtt_p;
		int    mtt_len =
		  o.Gen_Diff_With_PreAlloc(mt2_len, mt2, mt1_len, mt1, &mtt, 64);
		double m012_p[64], *m012 = m012_p;
		int    m012_len =
		  o.Gen_Diff_With_PreAlloc(mtt_len, mtt, mt3_len, mt3, &m012, 64);

		return_value = m012[m012_len - 1];
		if (m012_p != m012)
			FreeDoubles(m012);
		if (mtt_p != mtt)
			FreeDoubles(mtt);
		if (mt3_p != mt3)
			FreeDoubles(mt3);
		if (mt2_p != mt2)
			FreeDoubles(mt2);
		if (mt1_p != mt1)
			FreeDoubles(mt1);
		if (m12_p != m12)
			FreeDoubles(m12);
		if (t5_p != t5)
			FreeDoubles(t5);
		if (t4_p != t4)
			FreeDoubles(t4);
		if (m02_p != m02)
			FreeDoubles(m02);
		if (t3_p != t3)
			FreeDoubles(t3);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (m01_p != m01)
			FreeDoubles(m01);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (iz_p4z_p != iz_p4z)
			FreeDoubles(iz_p4z);
		if (iy_p4y_p != iy_p4y)
			FreeDoubles(iy_p4y);
		if (ix_p4x_p != ix_p4x)
			FreeDoubles(ix_p4x);
		if (dp4z_p != dp4z)
			FreeDoubles(dp4z);
		if (dp4y_p != dp4y)
			FreeDoubles(dp4y);
		if (dp4x_p != dp4x)
			FreeDoubles(dp4x);
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
		return orient3D_IEEE_exact<IT, ET>(p1, p2x, p2y, p2z, p3x, p3y, p3z, p4x,
		                                   p4y, p4z);
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
Sign orient3D_IEEE(const GenericPoint3T<IT, ET> &p1, double p2x, double p2y,
                   double p2z, double p3x, double p3y, double p3z, double p4x,
                   double p4y, double p4z)
{
	Sign ret;
	ret = orient3D_IEEE_interval<IT, ET>(p1, p2x, p2y, p2z, p3x, p3y, p3z, p4x,
	                                     p4y, p4z);
	if (is_sign_reliable(ret))
		return ret;
	return orient3D_IEEE_expansion<IT, ET>(p1, p2x, p2y, p2z, p3x, p3y, p3z, p4x,
	                                       p4y, p4z);
}

template <typename IT, typename ET>
Sign orient3D_IEEE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4)
{
	return orient3D_IEEE<IT, ET>(p1, p2.x(), p2.y(), p2.z(), p3.x(), p3.y(),
	                             p3.z(), p4.x(), p4.y(), p4.z());
}

template <typename IT, typename ET>
Sign orient3D_IIEE_interval(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2, IT p3x, IT p3y,
                            IT p3z, IT p4x, IT p4y, IT p4z)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT d1p4x = d1 * p4x;
	IT d1p4y = d1 * p4y;
	IT d1p4z = d1 * p4z;
	IT d2p4x = d2 * p4x;
	IT d2p4y = d2 * p4y;
	IT d2p4z = d2 * p4z;
	IT p1p4x = l1x - d1p4x;
	IT p1p4y = l1y - d1p4y;
	IT p1p4z = l1z - d1p4z;
	IT p2p4x = l2x - d2p4x;
	IT p2p4y = l2y - d2p4y;
	IT p2p4z = l2z - d2p4z;
	IT p3p4x = p3x - p4x;
	IT p3p4y = p3y - p4y;
	IT p3p4z = p3z - p4z;
	IT t0    = p1p4x * p2p4y;
	IT t1    = p1p4y * p2p4x;
	IT m01   = t0 - t1;
	IT t2    = p1p4x * p2p4z;
	IT t3    = p1p4z * p2p4x;
	IT m02   = t2 - t3;
	IT t4    = p1p4y * p2p4z;
	IT t5    = p1p4z * p2p4y;
	IT m12   = t4 - t5;
	IT mt1   = m01 * p3p4z;
	IT mt2   = m02 * p3p4y;
	IT mt3   = m12 * p3p4x;
	IT mtt   = mt2 - mt1;
	IT m012  = mtt - mt3;
	if (!m012.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IIEE_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2, ET p3x, ET p3y,
                         ET p3z, ET p4x, ET p4y, ET p4z)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET d1p4x = d1 * p4x;
	ET d1p4y = d1 * p4y;
	ET d1p4z = d1 * p4z;
	ET d2p4x = d2 * p4x;
	ET d2p4y = d2 * p4y;
	ET d2p4z = d2 * p4z;
	ET p1p4x = l1x - d1p4x;
	ET p1p4y = l1y - d1p4y;
	ET p1p4z = l1z - d1p4z;
	ET p2p4x = l2x - d2p4x;
	ET p2p4y = l2y - d2p4y;
	ET p2p4z = l2z - d2p4z;
	ET p3p4x = p3x - p4x;
	ET p3p4y = p3y - p4y;
	ET p3p4z = p3z - p4z;
	ET t0    = p1p4x * p2p4y;
	ET t1    = p1p4y * p2p4x;
	ET m01   = t0 - t1;
	ET t2    = p1p4x * p2p4z;
	ET t3    = p1p4z * p2p4x;
	ET m02   = t2 - t3;
	ET t4    = p1p4y * p2p4z;
	ET t5    = p1p4z * p2p4y;
	ET m12   = t4 - t5;
	ET mt1   = m01 * p3p4z;
	ET mt2   = m02 * p3p4y;
	ET mt3   = m12 * p3p4x;
	ET mtt   = mt2 - mt1;
	ET m012  = mtt - mt3;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2, double p3x,
                             double p3y, double p3z, double p4x, double p4y,
                             double p4z)
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
		double          d1p4x_p[32], *d1p4x = d1p4x_p;
		int    d1p4x_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4x, &d1p4x, 32);
		double d1p4y_p[32], *d1p4y = d1p4y_p;
		int    d1p4y_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4y, &d1p4y, 32);
		double d1p4z_p[32], *d1p4z = d1p4z_p;
		int    d1p4z_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4z, &d1p4z, 32);
		double d2p4x_p[32], *d2p4x = d2p4x_p;
		int    d2p4x_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, p4x, &d2p4x, 32);
		double d2p4y_p[32], *d2p4y = d2p4y_p;
		int    d2p4y_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, p4y, &d2p4y, 32);
		double d2p4z_p[32], *d2p4z = d2p4z_p;
		int    d2p4z_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, p4z, &d2p4z, 32);
		double p1p4x_p[32], *p1p4x = p1p4x_p;
		int    p1p4x_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, d1p4x_len, d1p4x, &p1p4x, 32);
		double p1p4y_p[32], *p1p4y = p1p4y_p;
		int    p1p4y_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, d1p4y_len, d1p4y, &p1p4y, 32);
		double p1p4z_p[32], *p1p4z = p1p4z_p;
		int    p1p4z_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, d1p4z_len, d1p4z, &p1p4z, 32);
		double p2p4x_p[32], *p2p4x = p2p4x_p;
		int    p2p4x_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, d2p4x_len, d2p4x, &p2p4x, 32);
		double p2p4y_p[32], *p2p4y = p2p4y_p;
		int    p2p4y_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, d2p4y_len, d2p4y, &p2p4y, 32);
		double p2p4z_p[32], *p2p4z = p2p4z_p;
		int    p2p4z_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, d2p4z_len, d2p4z, &p2p4z, 32);
		double p3p4x[2];
		o.Two_Diff(p3x, p4x, p3p4x);
		double p3p4y[2];
		o.Two_Diff(p3y, p4y, p3p4y);
		double p3p4z[2];
		o.Two_Diff(p3z, p4z, p3p4z);
		double t0_p[32], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Product_With_PreAlloc(p1p4x_len, p1p4x, p2p4y_len, p2p4y, &t0, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Product_With_PreAlloc(p1p4y_len, p1p4y, p2p4x_len, p2p4x, &t1, 32);
		double m01_p[32], *m01 = m01_p;
		int    m01_len = o.Gen_Diff_With_PreAlloc(t0_len, t0, t1_len, t1, &m01, 32);
		double t2_p[32], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Product_With_PreAlloc(p1p4x_len, p1p4x, p2p4z_len, p2p4z, &t2, 32);
		double t3_p[32], *t3 = t3_p;
		int    t3_len =
		  o.Gen_Product_With_PreAlloc(p1p4z_len, p1p4z, p2p4x_len, p2p4x, &t3, 32);
		double m02_p[32], *m02 = m02_p;
		int    m02_len = o.Gen_Diff_With_PreAlloc(t2_len, t2, t3_len, t3, &m02, 32);
		double t4_p[32], *t4 = t4_p;
		int    t4_len =
		  o.Gen_Product_With_PreAlloc(p1p4y_len, p1p4y, p2p4z_len, p2p4z, &t4, 32);
		double t5_p[32], *t5 = t5_p;
		int    t5_len =
		  o.Gen_Product_With_PreAlloc(p1p4z_len, p1p4z, p2p4y_len, p2p4y, &t5, 32);
		double m12_p[32], *m12 = m12_p;
		int    m12_len = o.Gen_Diff_With_PreAlloc(t4_len, t4, t5_len, t5, &m12, 32);
		double mt1_p[32], *mt1 = mt1_p;
		int mt1_len = o.Gen_Product_With_PreAlloc(m01_len, m01, 2, p3p4z, &mt1, 32);
		double mt2_p[32], *mt2 = mt2_p;
		int mt2_len = o.Gen_Product_With_PreAlloc(m02_len, m02, 2, p3p4y, &mt2, 32);
		double mt3_p[32], *mt3 = mt3_p;
		int mt3_len = o.Gen_Product_With_PreAlloc(m12_len, m12, 2, p3p4x, &mt3, 32);
		double mtt_p[32], *mtt = mtt_p;
		int    mtt_len =
		  o.Gen_Diff_With_PreAlloc(mt2_len, mt2, mt1_len, mt1, &mtt, 32);
		double m012_p[32], *m012 = m012_p;
		int    m012_len =
		  o.Gen_Diff_With_PreAlloc(mtt_len, mtt, mt3_len, mt3, &m012, 32);

		return_value = m012[m012_len - 1];
		if (m012_p != m012)
			FreeDoubles(m012);
		if (mtt_p != mtt)
			FreeDoubles(mtt);
		if (mt3_p != mt3)
			FreeDoubles(mt3);
		if (mt2_p != mt2)
			FreeDoubles(mt2);
		if (mt1_p != mt1)
			FreeDoubles(mt1);
		if (m12_p != m12)
			FreeDoubles(m12);
		if (t5_p != t5)
			FreeDoubles(t5);
		if (t4_p != t4)
			FreeDoubles(t4);
		if (m02_p != m02)
			FreeDoubles(m02);
		if (t3_p != t3)
			FreeDoubles(t3);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (m01_p != m01)
			FreeDoubles(m01);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (p2p4z_p != p2p4z)
			FreeDoubles(p2p4z);
		if (p2p4y_p != p2p4y)
			FreeDoubles(p2p4y);
		if (p2p4x_p != p2p4x)
			FreeDoubles(p2p4x);
		if (p1p4z_p != p1p4z)
			FreeDoubles(p1p4z);
		if (p1p4y_p != p1p4y)
			FreeDoubles(p1p4y);
		if (p1p4x_p != p1p4x)
			FreeDoubles(p1p4x);
		if (d2p4z_p != d2p4z)
			FreeDoubles(d2p4z);
		if (d2p4y_p != d2p4y)
			FreeDoubles(d2p4y);
		if (d2p4x_p != d2p4x)
			FreeDoubles(d2p4x);
		if (d1p4z_p != d1p4z)
			FreeDoubles(d1p4z);
		if (d1p4y_p != d1p4y)
			FreeDoubles(d1p4y);
		if (d1p4x_p != d1p4x)
			FreeDoubles(d1p4x);
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
		return orient3D_IIEE_exact<IT, ET>(p1, p2, p3x, p3y, p3z, p4x, p4y, p4z);
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
Sign orient3D_IIEE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2, double p3x, double p3y,
                   double p3z, double p4x, double p4y, double p4z)
{
	Sign ret;
	ret = orient3D_IIEE_interval<IT, ET>(p1, p2, p3x, p3y, p3z, p4x, p4y, p4z);
	if (is_sign_reliable(ret))
		return ret;
	return orient3D_IIEE_expansion<IT, ET>(p1, p2, p3x, p3y, p3z, p4x, p4y, p4z);
}

template <typename IT, typename ET>
Sign orient3D_IIEE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4)
{
	return orient3D_IIEE<IT, ET>(p1, p2, p3.x(), p3.y(), p3.z(), p4.x(), p4.y(),
	                             p4.z());
}

template <typename IT, typename ET>
Sign orient3D_IIIE_interval(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2,
                            const GenericPoint3T<IT, ET> &p3, IT p4x, IT p4y,
                            IT p4z)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT d1p4x = d1 * p4x;
	IT d1p4y = d1 * p4y;
	IT d1p4z = d1 * p4z;
	IT d2p4x = d2 * p4x;
	IT d2p4y = d2 * p4y;
	IT d2p4z = d2 * p4z;
	IT d3p4x = d3 * p4x;
	IT d3p4y = d3 * p4y;
	IT d3p4z = d3 * p4z;
	IT p1p4x = l1x - d1p4x;
	IT p1p4y = l1y - d1p4y;
	IT p1p4z = l1z - d1p4z;
	IT p2p4x = l2x - d2p4x;
	IT p2p4y = l2y - d2p4y;
	IT p2p4z = l2z - d2p4z;
	IT p3p4x = l3x - d3p4x;
	IT p3p4y = l3y - d3p4y;
	IT p3p4z = l3z - d3p4z;
	IT t0    = p1p4x * p2p4y;
	IT t1    = p1p4y * p2p4x;
	IT m01   = t0 - t1;
	IT t2    = p1p4x * p2p4z;
	IT t3    = p1p4z * p2p4x;
	IT m02   = t2 - t3;
	IT t4    = p1p4y * p2p4z;
	IT t5    = p1p4z * p2p4y;
	IT m12   = t4 - t5;
	IT mt1   = m01 * p3p4z;
	IT mt2   = m02 * p3p4y;
	IT mt3   = m12 * p3p4x;
	IT mtt   = mt2 - mt1;
	IT m012  = mtt - mt3;
	if (!m012.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IIIE_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3, ET p4x, ET p4y,
                         ET p4z)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET d1p4x = d1 * p4x;
	ET d1p4y = d1 * p4y;
	ET d1p4z = d1 * p4z;
	ET d2p4x = d2 * p4x;
	ET d2p4y = d2 * p4y;
	ET d2p4z = d2 * p4z;
	ET d3p4x = d3 * p4x;
	ET d3p4y = d3 * p4y;
	ET d3p4z = d3 * p4z;
	ET p1p4x = l1x - d1p4x;
	ET p1p4y = l1y - d1p4y;
	ET p1p4z = l1z - d1p4z;
	ET p2p4x = l2x - d2p4x;
	ET p2p4y = l2y - d2p4y;
	ET p2p4z = l2z - d2p4z;
	ET p3p4x = l3x - d3p4x;
	ET p3p4y = l3y - d3p4y;
	ET p3p4z = l3z - d3p4z;
	ET t0    = p1p4x * p2p4y;
	ET t1    = p1p4y * p2p4x;
	ET m01   = t0 - t1;
	ET t2    = p1p4x * p2p4z;
	ET t3    = p1p4z * p2p4x;
	ET m02   = t2 - t3;
	ET t4    = p1p4y * p2p4z;
	ET t5    = p1p4z * p2p4y;
	ET m12   = t4 - t5;
	ET mt1   = m01 * p3p4z;
	ET mt2   = m02 * p3p4y;
	ET mt3   = m12 * p3p4x;
	ET mtt   = mt2 - mt1;
	ET m012  = mtt - mt3;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3, double p4x,
                             double p4y, double p4z)
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
		double          d1p4x_p[32], *d1p4x = d1p4x_p;
		int    d1p4x_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4x, &d1p4x, 32);
		double d1p4y_p[32], *d1p4y = d1p4y_p;
		int    d1p4y_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4y, &d1p4y, 32);
		double d1p4z_p[32], *d1p4z = d1p4z_p;
		int    d1p4z_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, p4z, &d1p4z, 32);
		double d2p4x_p[32], *d2p4x = d2p4x_p;
		int    d2p4x_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, p4x, &d2p4x, 32);
		double d2p4y_p[32], *d2p4y = d2p4y_p;
		int    d2p4y_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, p4y, &d2p4y, 32);
		double d2p4z_p[32], *d2p4z = d2p4z_p;
		int    d2p4z_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, p4z, &d2p4z, 32);
		double d3p4x_p[32], *d3p4x = d3p4x_p;
		int    d3p4x_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, p4x, &d3p4x, 32);
		double d3p4y_p[32], *d3p4y = d3p4y_p;
		int    d3p4y_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, p4y, &d3p4y, 32);
		double d3p4z_p[32], *d3p4z = d3p4z_p;
		int    d3p4z_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, p4z, &d3p4z, 32);
		double p1p4x_p[32], *p1p4x = p1p4x_p;
		int    p1p4x_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, d1p4x_len, d1p4x, &p1p4x, 32);
		double p1p4y_p[32], *p1p4y = p1p4y_p;
		int    p1p4y_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, d1p4y_len, d1p4y, &p1p4y, 32);
		double p1p4z_p[32], *p1p4z = p1p4z_p;
		int    p1p4z_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, d1p4z_len, d1p4z, &p1p4z, 32);
		double p2p4x_p[32], *p2p4x = p2p4x_p;
		int    p2p4x_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, d2p4x_len, d2p4x, &p2p4x, 32);
		double p2p4y_p[32], *p2p4y = p2p4y_p;
		int    p2p4y_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, d2p4y_len, d2p4y, &p2p4y, 32);
		double p2p4z_p[32], *p2p4z = p2p4z_p;
		int    p2p4z_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, d2p4z_len, d2p4z, &p2p4z, 32);
		double p3p4x_p[32], *p3p4x = p3p4x_p;
		int    p3p4x_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, d3p4x_len, d3p4x, &p3p4x, 32);
		double p3p4y_p[32], *p3p4y = p3p4y_p;
		int    p3p4y_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, d3p4y_len, d3p4y, &p3p4y, 32);
		double p3p4z_p[32], *p3p4z = p3p4z_p;
		int    p3p4z_len =
		  o.Gen_Diff_With_PreAlloc(l3z_len, l3z, d3p4z_len, d3p4z, &p3p4z, 32);
		double t0_p[32], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Product_With_PreAlloc(p1p4x_len, p1p4x, p2p4y_len, p2p4y, &t0, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Product_With_PreAlloc(p1p4y_len, p1p4y, p2p4x_len, p2p4x, &t1, 32);
		double m01_p[32], *m01 = m01_p;
		int    m01_len = o.Gen_Diff_With_PreAlloc(t0_len, t0, t1_len, t1, &m01, 32);
		double t2_p[32], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Product_With_PreAlloc(p1p4x_len, p1p4x, p2p4z_len, p2p4z, &t2, 32);
		double t3_p[32], *t3 = t3_p;
		int    t3_len =
		  o.Gen_Product_With_PreAlloc(p1p4z_len, p1p4z, p2p4x_len, p2p4x, &t3, 32);
		double m02_p[32], *m02 = m02_p;
		int    m02_len = o.Gen_Diff_With_PreAlloc(t2_len, t2, t3_len, t3, &m02, 32);
		double t4_p[32], *t4 = t4_p;
		int    t4_len =
		  o.Gen_Product_With_PreAlloc(p1p4y_len, p1p4y, p2p4z_len, p2p4z, &t4, 32);
		double t5_p[32], *t5 = t5_p;
		int    t5_len =
		  o.Gen_Product_With_PreAlloc(p1p4z_len, p1p4z, p2p4y_len, p2p4y, &t5, 32);
		double m12_p[32], *m12 = m12_p;
		int    m12_len = o.Gen_Diff_With_PreAlloc(t4_len, t4, t5_len, t5, &m12, 32);
		double mt1_p[32], *mt1 = mt1_p;
		int    mt1_len =
		  o.Gen_Product_With_PreAlloc(m01_len, m01, p3p4z_len, p3p4z, &mt1, 32);
		double mt2_p[32], *mt2 = mt2_p;
		int    mt2_len =
		  o.Gen_Product_With_PreAlloc(m02_len, m02, p3p4y_len, p3p4y, &mt2, 32);
		double mt3_p[32], *mt3 = mt3_p;
		int    mt3_len =
		  o.Gen_Product_With_PreAlloc(m12_len, m12, p3p4x_len, p3p4x, &mt3, 32);
		double mtt_p[32], *mtt = mtt_p;
		int    mtt_len =
		  o.Gen_Diff_With_PreAlloc(mt2_len, mt2, mt1_len, mt1, &mtt, 32);
		double m012_p[32], *m012 = m012_p;
		int    m012_len =
		  o.Gen_Diff_With_PreAlloc(mtt_len, mtt, mt3_len, mt3, &m012, 32);

		return_value = m012[m012_len - 1];
		if (m012_p != m012)
			FreeDoubles(m012);
		if (mtt_p != mtt)
			FreeDoubles(mtt);
		if (mt3_p != mt3)
			FreeDoubles(mt3);
		if (mt2_p != mt2)
			FreeDoubles(mt2);
		if (mt1_p != mt1)
			FreeDoubles(mt1);
		if (m12_p != m12)
			FreeDoubles(m12);
		if (t5_p != t5)
			FreeDoubles(t5);
		if (t4_p != t4)
			FreeDoubles(t4);
		if (m02_p != m02)
			FreeDoubles(m02);
		if (t3_p != t3)
			FreeDoubles(t3);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (m01_p != m01)
			FreeDoubles(m01);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (p3p4z_p != p3p4z)
			FreeDoubles(p3p4z);
		if (p3p4y_p != p3p4y)
			FreeDoubles(p3p4y);
		if (p3p4x_p != p3p4x)
			FreeDoubles(p3p4x);
		if (p2p4z_p != p2p4z)
			FreeDoubles(p2p4z);
		if (p2p4y_p != p2p4y)
			FreeDoubles(p2p4y);
		if (p2p4x_p != p2p4x)
			FreeDoubles(p2p4x);
		if (p1p4z_p != p1p4z)
			FreeDoubles(p1p4z);
		if (p1p4y_p != p1p4y)
			FreeDoubles(p1p4y);
		if (p1p4x_p != p1p4x)
			FreeDoubles(p1p4x);
		if (d3p4z_p != d3p4z)
			FreeDoubles(d3p4z);
		if (d3p4y_p != d3p4y)
			FreeDoubles(d3p4y);
		if (d3p4x_p != d3p4x)
			FreeDoubles(d3p4x);
		if (d2p4z_p != d2p4z)
			FreeDoubles(d2p4z);
		if (d2p4y_p != d2p4y)
			FreeDoubles(d2p4y);
		if (d2p4x_p != d2p4x)
			FreeDoubles(d2p4x);
		if (d1p4z_p != d1p4z)
			FreeDoubles(d1p4z);
		if (d1p4y_p != d1p4y)
			FreeDoubles(d1p4y);
		if (d1p4x_p != d1p4x)
			FreeDoubles(d1p4x);
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
		return orient3D_IIIE_exact<IT, ET>(p1, p2, p3, p4x, p4y, p4z);
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
Sign orient3D_IIIE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3, double p4x, double p4y,
                   double p4z)
{
	Sign ret;
	ret = orient3D_IIIE_interval<IT, ET>(p1, p2, p3, p4x, p4y, p4z);
	if (is_sign_reliable(ret))
		return ret;
	return orient3D_IIIE_expansion<IT, ET>(p1, p2, p3, p4x, p4y, p4z);
}

template <typename IT, typename ET>
Sign orient3D_IIIE(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4)
{
	return orient3D_IIIE<IT, ET>(p1, p2, p3, p4.x(), p4.y(), p4.z());
}

template <typename IT, typename ET>
Sign orient3D_IIII_interval(const GenericPoint3T<IT, ET> &p1,
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

	IT d1p4x = d1 * l4x;
	IT d1p4y = d1 * l4y;
	IT d1p4z = d1 * l4z;
	IT d2p4x = d2 * l4x;
	IT d2p4y = d2 * l4y;
	IT d2p4z = d2 * l4z;
	IT d3p4x = d3 * l4x;
	IT d3p4y = d3 * l4y;
	IT d3p4z = d3 * l4z;
	IT d4l1x = d4 * l1x;
	IT d4l1y = d4 * l1y;
	IT d4l1z = d4 * l1z;
	IT d4l2x = d4 * l2x;
	IT d4l2y = d4 * l2y;
	IT d4l2z = d4 * l2z;
	IT d4l3x = d4 * l3x;
	IT d4l3y = d4 * l3y;
	IT d4l3z = d4 * l3z;
	IT p1p4x = d4l1x - d1p4x;
	IT p1p4y = d4l1y - d1p4y;
	IT p1p4z = d4l1z - d1p4z;
	IT p2p4x = d4l2x - d2p4x;
	IT p2p4y = d4l2y - d2p4y;
	IT p2p4z = d4l2z - d2p4z;
	IT p3p4x = d4l3x - d3p4x;
	IT p3p4y = d4l3y - d3p4y;
	IT p3p4z = d4l3z - d3p4z;
	IT t0    = p1p4x * p2p4y;
	IT t1    = p1p4y * p2p4x;
	IT m01   = t0 - t1;
	IT t2    = p1p4x * p2p4z;
	IT t3    = p1p4z * p2p4x;
	IT m02   = t2 - t3;
	IT t4    = p1p4y * p2p4z;
	IT t5    = p1p4z * p2p4y;
	IT m12   = t4 - t5;
	IT mt1   = m01 * p3p4z;
	IT mt2   = m02 * p3p4y;
	IT mt3   = m12 * p3p4x;
	IT mtt   = mt2 - mt1;
	IT m012  = mtt - mt3;
	if (!m012.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IIII_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	p4.getExactLambda(l4x, l4y, l4z, d4);
	ET d1p4x = d1 * l4x;
	ET d1p4y = d1 * l4y;
	ET d1p4z = d1 * l4z;
	ET d2p4x = d2 * l4x;
	ET d2p4y = d2 * l4y;
	ET d2p4z = d2 * l4z;
	ET d3p4x = d3 * l4x;
	ET d3p4y = d3 * l4y;
	ET d3p4z = d3 * l4z;
	ET d4l1x = d4 * l1x;
	ET d4l1y = d4 * l1y;
	ET d4l1z = d4 * l1z;
	ET d4l2x = d4 * l2x;
	ET d4l2y = d4 * l2y;
	ET d4l2z = d4 * l2z;
	ET d4l3x = d4 * l3x;
	ET d4l3y = d4 * l3y;
	ET d4l3z = d4 * l3z;
	ET p1p4x = d4l1x - d1p4x;
	ET p1p4y = d4l1y - d1p4y;
	ET p1p4z = d4l1z - d1p4z;
	ET p2p4x = d4l2x - d2p4x;
	ET p2p4y = d4l2y - d2p4y;
	ET p2p4z = d4l2z - d2p4z;
	ET p3p4x = d4l3x - d3p4x;
	ET p3p4y = d4l3y - d3p4y;
	ET p3p4z = d4l3z - d3p4z;
	ET t0    = p1p4x * p2p4y;
	ET t1    = p1p4y * p2p4x;
	ET m01   = t0 - t1;
	ET t2    = p1p4x * p2p4z;
	ET t3    = p1p4z * p2p4x;
	ET m02   = t2 - t3;
	ET t4    = p1p4y * p2p4z;
	ET t5    = p1p4z * p2p4y;
	ET m12   = t4 - t5;
	ET mt1   = m01 * p3p4z;
	ET mt2   = m02 * p3p4y;
	ET mt3   = m12 * p3p4x;
	ET mtt   = mt2 - mt1;
	ET m012  = mtt - mt3;
	return OMC::sign(m012);
}

template <typename IT, typename ET>
Sign orient3D_IIII_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3,
                             const GenericPoint3T<IT, ET> &p4)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[32],
	  *l1x = l1x_p, l1y_p[32], *l1y = l1y_p, l1z_p[32], *l1z = l1z_p, d1_p[32],
	  *d1 = d1_p, l2x_p[32], *l2x = l2x_p, l2y_p[32], *l2y = l2y_p, l2z_p[32],
	  *l2z = l2z_p, d2_p[32], *d2 = d2_p, l3x_p[32], *l3x = l3x_p, l3y_p[32],
	  *l3y = l3y_p, l3z_p[32], *l3z = l3z_p, d3_p[32], *d3 = d3_p, l4x_p[32],
	  *l4x = l4x_p, l4y_p[32], *l4y = l4y_p, l4z_p[32], *l4z = l4z_p, d4_p[32],
	  *d4       = d4_p;
	int l1x_len = 32, l1y_len = 32, l1z_len = 32, d1_len = 32, l2x_len = 32,
	    l2y_len = 32, l2z_len = 32, d2_len = 32, l3x_len = 32, l3y_len = 32,
	    l3z_len = 32, d3_len = 32, l4x_len = 32, l4y_len = 32, l4z_len = 32,
	    d4_len = 32;
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
		double          d1p4x_p[32], *d1p4x = d1p4x_p;
		int             d1p4x_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, l4x_len, l4x, &d1p4x, 32);
		double d1p4y_p[32], *d1p4y = d1p4y_p;
		int    d1p4y_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, l4y_len, l4y, &d1p4y, 32);
		double d1p4z_p[32], *d1p4z = d1p4z_p;
		int    d1p4z_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, l4z_len, l4z, &d1p4z, 32);
		double d2p4x_p[32], *d2p4x = d2p4x_p;
		int    d2p4x_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, l4x_len, l4x, &d2p4x, 32);
		double d2p4y_p[32], *d2p4y = d2p4y_p;
		int    d2p4y_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, l4y_len, l4y, &d2p4y, 32);
		double d2p4z_p[32], *d2p4z = d2p4z_p;
		int    d2p4z_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, l4z_len, l4z, &d2p4z, 32);
		double d3p4x_p[32], *d3p4x = d3p4x_p;
		int    d3p4x_len =
		  o.Gen_Product_With_PreAlloc(d3_len, d3, l4x_len, l4x, &d3p4x, 32);
		double d3p4y_p[32], *d3p4y = d3p4y_p;
		int    d3p4y_len =
		  o.Gen_Product_With_PreAlloc(d3_len, d3, l4y_len, l4y, &d3p4y, 32);
		double d3p4z_p[32], *d3p4z = d3p4z_p;
		int    d3p4z_len =
		  o.Gen_Product_With_PreAlloc(d3_len, d3, l4z_len, l4z, &d3p4z, 32);
		double d4l1x_p[32], *d4l1x = d4l1x_p;
		int    d4l1x_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l1x_len, l1x, &d4l1x, 32);
		double d4l1y_p[32], *d4l1y = d4l1y_p;
		int    d4l1y_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l1y_len, l1y, &d4l1y, 32);
		double d4l1z_p[32], *d4l1z = d4l1z_p;
		int    d4l1z_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l1z_len, l1z, &d4l1z, 32);
		double d4l2x_p[32], *d4l2x = d4l2x_p;
		int    d4l2x_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l2x_len, l2x, &d4l2x, 32);
		double d4l2y_p[32], *d4l2y = d4l2y_p;
		int    d4l2y_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l2y_len, l2y, &d4l2y, 32);
		double d4l2z_p[32], *d4l2z = d4l2z_p;
		int    d4l2z_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l2z_len, l2z, &d4l2z, 32);
		double d4l3x_p[32], *d4l3x = d4l3x_p;
		int    d4l3x_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l3x_len, l3x, &d4l3x, 32);
		double d4l3y_p[32], *d4l3y = d4l3y_p;
		int    d4l3y_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l3y_len, l3y, &d4l3y, 32);
		double d4l3z_p[32], *d4l3z = d4l3z_p;
		int    d4l3z_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, l3z_len, l3z, &d4l3z, 32);
		double p1p4x_p[32], *p1p4x = p1p4x_p;
		int    p1p4x_len =
		  o.Gen_Diff_With_PreAlloc(d4l1x_len, d4l1x, d1p4x_len, d1p4x, &p1p4x, 32);
		double p1p4y_p[32], *p1p4y = p1p4y_p;
		int    p1p4y_len =
		  o.Gen_Diff_With_PreAlloc(d4l1y_len, d4l1y, d1p4y_len, d1p4y, &p1p4y, 32);
		double p1p4z_p[32], *p1p4z = p1p4z_p;
		int    p1p4z_len =
		  o.Gen_Diff_With_PreAlloc(d4l1z_len, d4l1z, d1p4z_len, d1p4z, &p1p4z, 32);
		double p2p4x_p[32], *p2p4x = p2p4x_p;
		int    p2p4x_len =
		  o.Gen_Diff_With_PreAlloc(d4l2x_len, d4l2x, d2p4x_len, d2p4x, &p2p4x, 32);
		double p2p4y_p[32], *p2p4y = p2p4y_p;
		int    p2p4y_len =
		  o.Gen_Diff_With_PreAlloc(d4l2y_len, d4l2y, d2p4y_len, d2p4y, &p2p4y, 32);
		double p2p4z_p[32], *p2p4z = p2p4z_p;
		int    p2p4z_len =
		  o.Gen_Diff_With_PreAlloc(d4l2z_len, d4l2z, d2p4z_len, d2p4z, &p2p4z, 32);
		double p3p4x_p[32], *p3p4x = p3p4x_p;
		int    p3p4x_len =
		  o.Gen_Diff_With_PreAlloc(d4l3x_len, d4l3x, d3p4x_len, d3p4x, &p3p4x, 32);
		double p3p4y_p[32], *p3p4y = p3p4y_p;
		int    p3p4y_len =
		  o.Gen_Diff_With_PreAlloc(d4l3y_len, d4l3y, d3p4y_len, d3p4y, &p3p4y, 32);
		double p3p4z_p[32], *p3p4z = p3p4z_p;
		int    p3p4z_len =
		  o.Gen_Diff_With_PreAlloc(d4l3z_len, d4l3z, d3p4z_len, d3p4z, &p3p4z, 32);
		double t0_p[32], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Product_With_PreAlloc(p1p4x_len, p1p4x, p2p4y_len, p2p4y, &t0, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Product_With_PreAlloc(p1p4y_len, p1p4y, p2p4x_len, p2p4x, &t1, 32);
		double m01_p[32], *m01 = m01_p;
		int    m01_len = o.Gen_Diff_With_PreAlloc(t0_len, t0, t1_len, t1, &m01, 32);
		double t2_p[32], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Product_With_PreAlloc(p1p4x_len, p1p4x, p2p4z_len, p2p4z, &t2, 32);
		double t3_p[32], *t3 = t3_p;
		int    t3_len =
		  o.Gen_Product_With_PreAlloc(p1p4z_len, p1p4z, p2p4x_len, p2p4x, &t3, 32);
		double m02_p[32], *m02 = m02_p;
		int    m02_len = o.Gen_Diff_With_PreAlloc(t2_len, t2, t3_len, t3, &m02, 32);
		double t4_p[32], *t4 = t4_p;
		int    t4_len =
		  o.Gen_Product_With_PreAlloc(p1p4y_len, p1p4y, p2p4z_len, p2p4z, &t4, 32);
		double t5_p[32], *t5 = t5_p;
		int    t5_len =
		  o.Gen_Product_With_PreAlloc(p1p4z_len, p1p4z, p2p4y_len, p2p4y, &t5, 32);
		double m12_p[32], *m12 = m12_p;
		int    m12_len = o.Gen_Diff_With_PreAlloc(t4_len, t4, t5_len, t5, &m12, 32);
		double mt1_p[32], *mt1 = mt1_p;
		int    mt1_len =
		  o.Gen_Product_With_PreAlloc(m01_len, m01, p3p4z_len, p3p4z, &mt1, 32);
		double mt2_p[32], *mt2 = mt2_p;
		int    mt2_len =
		  o.Gen_Product_With_PreAlloc(m02_len, m02, p3p4y_len, p3p4y, &mt2, 32);
		double mt3_p[32], *mt3 = mt3_p;
		int    mt3_len =
		  o.Gen_Product_With_PreAlloc(m12_len, m12, p3p4x_len, p3p4x, &mt3, 32);
		double mtt_p[32], *mtt = mtt_p;
		int    mtt_len =
		  o.Gen_Diff_With_PreAlloc(mt2_len, mt2, mt1_len, mt1, &mtt, 32);
		double m012_p[32], *m012 = m012_p;
		int    m012_len =
		  o.Gen_Diff_With_PreAlloc(mtt_len, mtt, mt3_len, mt3, &m012, 32);

		return_value = m012[m012_len - 1];
		if (m012_p != m012)
			FreeDoubles(m012);
		if (mtt_p != mtt)
			FreeDoubles(mtt);
		if (mt3_p != mt3)
			FreeDoubles(mt3);
		if (mt2_p != mt2)
			FreeDoubles(mt2);
		if (mt1_p != mt1)
			FreeDoubles(mt1);
		if (m12_p != m12)
			FreeDoubles(m12);
		if (t5_p != t5)
			FreeDoubles(t5);
		if (t4_p != t4)
			FreeDoubles(t4);
		if (m02_p != m02)
			FreeDoubles(m02);
		if (t3_p != t3)
			FreeDoubles(t3);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (m01_p != m01)
			FreeDoubles(m01);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (p3p4z_p != p3p4z)
			FreeDoubles(p3p4z);
		if (p3p4y_p != p3p4y)
			FreeDoubles(p3p4y);
		if (p3p4x_p != p3p4x)
			FreeDoubles(p3p4x);
		if (p2p4z_p != p2p4z)
			FreeDoubles(p2p4z);
		if (p2p4y_p != p2p4y)
			FreeDoubles(p2p4y);
		if (p2p4x_p != p2p4x)
			FreeDoubles(p2p4x);
		if (p1p4z_p != p1p4z)
			FreeDoubles(p1p4z);
		if (p1p4y_p != p1p4y)
			FreeDoubles(p1p4y);
		if (p1p4x_p != p1p4x)
			FreeDoubles(p1p4x);
		if (d4l3z_p != d4l3z)
			FreeDoubles(d4l3z);
		if (d4l3y_p != d4l3y)
			FreeDoubles(d4l3y);
		if (d4l3x_p != d4l3x)
			FreeDoubles(d4l3x);
		if (d4l2z_p != d4l2z)
			FreeDoubles(d4l2z);
		if (d4l2y_p != d4l2y)
			FreeDoubles(d4l2y);
		if (d4l2x_p != d4l2x)
			FreeDoubles(d4l2x);
		if (d4l1z_p != d4l1z)
			FreeDoubles(d4l1z);
		if (d4l1y_p != d4l1y)
			FreeDoubles(d4l1y);
		if (d4l1x_p != d4l1x)
			FreeDoubles(d4l1x);
		if (d3p4z_p != d3p4z)
			FreeDoubles(d3p4z);
		if (d3p4y_p != d3p4y)
			FreeDoubles(d3p4y);
		if (d3p4x_p != d3p4x)
			FreeDoubles(d3p4x);
		if (d2p4z_p != d2p4z)
			FreeDoubles(d2p4z);
		if (d2p4y_p != d2p4y)
			FreeDoubles(d2p4y);
		if (d2p4x_p != d2p4x)
			FreeDoubles(d2p4x);
		if (d1p4z_p != d1p4z)
			FreeDoubles(d1p4z);
		if (d1p4y_p != d1p4y)
			FreeDoubles(d1p4y);
		if (d1p4x_p != d1p4x)
			FreeDoubles(d1p4x);
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
		return orient3D_IIII_exact<IT, ET>(p1, p2, p3, p4);
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
Sign orient3D_IIII(const GenericPoint3T<IT, ET> &p1,
                   const GenericPoint3T<IT, ET> &p2,
                   const GenericPoint3T<IT, ET> &p3,
                   const GenericPoint3T<IT, ET> &p4)
{
	Sign ret;
	ret = orient3D_IIII_interval<IT, ET>(p1, p2, p3, p4);
	if (is_sign_reliable(ret))
		return ret;
	return orient3D_IIII_expansion<IT, ET>(p1, p2, p3, p4);
}

} // namespace OMC