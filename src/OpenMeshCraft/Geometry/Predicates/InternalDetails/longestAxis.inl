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
/* Forward Declarations (hand)****************************************/
/*********************************************************************/

template <typename IT, typename ET>
int longestAxis_IE(const GenericPoint3T<IT, ET> &a,
                   const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
int longestAxis_II(const GenericPoint3T<IT, ET> &a,
                   const GenericPoint3T<IT, ET> &b);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

template <typename IT, typename ET>
int longestAxis_IE_interval(const GenericPoint3T<IT, ET> &p1, IT bx, IT by,
                            IT bz)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return -1;

	typename IT::Protector P;

	IT dbx = bx * d1;
	IT kx  = l1x - dbx;

	IT dby = by * d1;
	IT ky  = l1y - dby;

	IT dbz = bz * d1;
	IT kz  = l1z - dbz;

	int    axis = -1;
	double k   = 0.;
	if (kx.is_sign_reliable() && fabs(kx.inf() + kx.sup()) > k)
	{
		k   = fabs(kx.inf() + kx.sup());
		axis = 0;
	}
	if (ky.is_sign_reliable() && fabs(ky.inf() + ky.sup()) > k)
	{
		k   = fabs(ky.inf() + ky.sup());
		axis = 1;
	}
	if (kz.is_sign_reliable() && fabs(kz.inf() + kz.sup()) > k)
	{
		k   = fabs(kz.inf() + kz.sup());
		axis = 2;
	}

	return axis;
}

template <typename IT, typename ET>
int longestAxis_IE_exact(const GenericPoint3T<IT, ET> &p1, ET bx, ET by, ET bz)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);

	ET dbx = bx * d1;
	ET kx  = l1x - dbx;
	kx     = OMC::abs(kx);

	ET dby = by * d1;
	ET ky  = l1y - dby;
	ky     = OMC::abs(ky);

	ET dbz = bz * d1;
	ET kz  = l1z - dbz;
	kz     = OMC::abs(kz);

	if (ky > kx)
		return kz > ky ? 2 : 1;
	else
		return kz > kx ? 2 : 0;
}

template <typename IT, typename ET>
int longestAxis_IE_expansion(const GenericPoint3T<IT, ET> &p1, double bx,
                             double by, double bz)
{
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[128], *l1x = l1x_p, l1y_p[128], *l1y = l1y_p, l1z_p[128],
	                   *l1z = l1z_p, d1_p[128], *d1 = d1_p;
	int l1x_len = 128, l1y_len = 128, l1z_len = 128, d1_len = 128;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	double diff_kx = NAN, diff_ky = NAN, diff_kz = NAN;
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;

		// x
		double db_p[128], *db = db_p;
		int    db_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, bx, &db, 128);
		double k_p[128], *k = k_p;
		int    k_len = o.Gen_Diff_With_PreAlloc(l1x_len, l1x, db_len, db, &k, 128);
		diff_kx      = fabs(k[k_len - 1]);
		if (k_p != k)
			FreeDoubles(k);
		if (db_p != db)
			FreeDoubles(db);
		// y
		db      = db_p;
		db_len  = o.Gen_Scale_With_PreAlloc(d1_len, d1, by, &db, 128);
		k       = k_p;
		k_len   = o.Gen_Diff_With_PreAlloc(l1y_len, l1y, db_len, db, &k, 128);
		diff_ky = fabs(k[k_len - 1]);
		if (k_p != k)
			FreeDoubles(k);
		if (db_p != db)
			FreeDoubles(db);
		// z
		db      = db_p;
		db_len  = o.Gen_Scale_With_PreAlloc(d1_len, d1, bz, &db, 128);
		k       = k_p;
		k_len   = o.Gen_Diff_With_PreAlloc(l1z_len, l1z, db_len, db, &k, 128);
		diff_kz = fabs(k[k_len - 1]);
		if (k_p != k)
			FreeDoubles(k);
		if (db_p != db)
			FreeDoubles(db);
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
		return longestAxis_IE_exact<IT, ET>(p1, bx, by, bz);
#endif

	if (diff_ky > diff_kx)
		return diff_kz > diff_ky ? 2 : 1;
	else
		return diff_kz > diff_kx ? 2 : 0;
}

template <typename IT, typename ET>
int longestAxis_IE(const GenericPoint3T<IT, ET> &a,
                   const GenericPoint3T<IT, ET> &b)
{
	int ret;
	ret = longestAxis_IE_interval<IT, ET>(a, b.x(), b.y(), b.z());
	if (ret >= 0)
		return ret;
	return longestAxis_IE_expansion<IT, ET>(a, b.x(), b.y(), b.z());
}

template <typename IT, typename ET>
int longestAxis_II_interval(const GenericPoint3T<IT, ET> &p1,
                            const GenericPoint3T<IT, ET> &p2)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return -1;

	typename IT::Protector P;

	IT k1 = d2 * l1x;
	IT k2 = d1 * l2x;
	IT kx = k1 - k2;

	k1    = d2 * l1y;
	k2    = d1 * l2y;
	IT ky = k1 - k2;

	k1    = d2 * l1z;
	k2    = d1 * l2z;
	IT kz = k1 - k2;

	int    axis = -1;
	double k   = 0.;
	if (kx.is_sign_reliable() && fabs(kx.inf() + kx.sup()) > k)
	{
		k   = fabs(kx.inf() + kx.sup());
		axis = 0;
	}
	if (ky.is_sign_reliable() && fabs(ky.inf() + ky.sup()) > k)
	{
		k   = fabs(ky.inf() + ky.sup());
		axis = 1;
	}
	if (kz.is_sign_reliable() && fabs(kz.inf() + kz.sup()) > k)
	{
		k   = fabs(kz.inf() + kz.sup());
		axis = 2;
	}

	return axis;
}

template <typename IT, typename ET>
int longestAxis_II_exact(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);

	ET k1 = d2 * l1x;
	ET k2 = d1 * l2x;
	ET kx = k1 - k2;
	kx    = OMC::abs(kx);

	k1    = d2 * l1y;
	k2    = d1 * l2y;
	ET ky = k1 - k2;
	ky    = OMC::abs(ky);

	k1    = d2 * l1z;
	k2    = d1 * l2z;
	ET kz = k1 - k2;
	kz    = OMC::abs(kz);

	if (ky > kx)
		return kz > ky ? 2 : 1;
	else
		return kz > kx ? 2 : 0;
}

template <typename IT, typename ET>
int longestAxis_II_expansion(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2)
{
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[128], *l1x = l1x_p, l1y_p[128], *l1y = l1y_p, l1z_p[128],
	                   *l1z = l1z_p, d1_p[128], *d1 = d1_p, l2x_p[128],
	                   *l2x = l2x_p, l2y_p[128], *l2y = l2y_p, l2z_p[128],
	                   *l2z = l2z_p, d2_p[128], *d2 = d2_p;
	int l1x_len = 128, l1y_len = 128, l1z_len = 128, d1_len = 128, l2x_len = 128,
	    l2y_len = 128, l2z_len = 128, d2_len = 128;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	double diff_kx = NAN, diff_ky = NAN, diff_kz = NAN;
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;

		// x
		double k1_p[128], *k1 = k1_p;
		int    k1_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &k1, 128);
		double k2_p[128], *k2 = k2_p;
		int    k2_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &k2, 128);
		double k_p[128], *k = k_p;
		int    k_len = o.Gen_Diff_With_PreAlloc(k1_len, k1, k2_len, k2, &k, 128);
		diff_kx      = fabs(k[k_len - 1]);
		if (k_p != k)
			FreeDoubles(k);
		if (k2_p != k2)
			FreeDoubles(k2);
		if (k1_p != k1)
			FreeDoubles(k1);
		// y
		k1      = k1_p;
		k1_len  = o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &k1, 128);
		k2      = k2_p;
		k2_len  = o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &k2, 128);
		k       = k_p;
		k_len   = o.Gen_Diff_With_PreAlloc(k1_len, k1, k2_len, k2, &k, 128);
		diff_ky = fabs(k[k_len - 1]);
		if (k_p != k)
			FreeDoubles(k);
		if (k2_p != k2)
			FreeDoubles(k2);
		if (k1_p != k1)
			FreeDoubles(k1);
		// z
		k1      = k1_p;
		k1_len  = o.Gen_Product_With_PreAlloc(d2_len, d2, l1z_len, l1z, &k1, 128);
		k2      = k2_p;
		k2_len  = o.Gen_Product_With_PreAlloc(d1_len, d1, l2z_len, l2z, &k2, 128);
		k       = k_p;
		k_len   = o.Gen_Diff_With_PreAlloc(k1_len, k1, k2_len, k2, &k, 128);
		diff_kz = fabs(k[k_len - 1]);
		if (k_p != k)
			FreeDoubles(k);
		if (k2_p != k2)
			FreeDoubles(k2);
		if (k1_p != k1)
			FreeDoubles(k1);
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
		return longestAxis_II_exact<IT, ET>(p1, p2);
#endif

	if (diff_ky > diff_kx)
		return diff_kz > diff_ky ? 2 : 1;
	else
		return diff_kz > diff_kx ? 2 : 0;
}

template <typename IT, typename ET>
int longestAxis_II(const GenericPoint3T<IT, ET> &a,
                   const GenericPoint3T<IT, ET> &b)
{
	int ret;
	ret = longestAxis_II_interval<IT, ET>(a, b);
	if (ret >= 0)
		return ret;
	return longestAxis_II_expansion<IT, ET>(a, b);
}

} // namespace OMC