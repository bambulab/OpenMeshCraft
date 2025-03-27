#pragma once

#include "OpenMeshCraft/Geometry/Predicates/IndirectDefinitions.h"

#include "OpenMeshCraft/Geometry/Primitives/GenericPoint3T.h"
#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"
#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
#define CHECK_FOR_XYZERFLOWS

namespace OMC {

/*********************************************************************/
/* Forward Declarations (hand)****************************************/
/*********************************************************************/

/*************** LessThanOnAll (wrap to LessThanOnX/Y/Z) *******************/

inline std::array<Sign, 3> lessThanOnAll_EE(double x1, double y1, double z1,
                                            double x2, double y2, double z2);

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_EE(const GenericPoint3T<IT, ET> &a,
                                     const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_IE(const GenericPoint3T<IT, ET> &p1,
                                     double x2, double y2, double z2,
                                     PntArr3 arr);

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_IE(const GenericPoint3T<IT, ET> &a,
                                     const GenericPoint3T<IT, ET> &b,
                                     PntArr3                       arr);

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_II(const GenericPoint3T<IT, ET> &p1,
                                     const GenericPoint3T<IT, ET> &p2,
                                     PntArr3                       arr);

/*************** LessThan (wrap to LessThanOnX/Y/Z) *******************/

inline Sign lessThan_EE(double x1, double y1, double z1, double x2, double y2,
                        double z2);

template <typename IT, typename ET>
Sign lessThan_EE(const GenericPoint3T<IT, ET> &a,
                 const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
Sign lessThan_IE(const GenericPoint3T<IT, ET> &p1, double x2, double y2,
                 double z2);

template <typename IT, typename ET>
Sign lessThan_IE(const GenericPoint3T<IT, ET> &a,
                 const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
Sign lessThan_II(const GenericPoint3T<IT, ET> &p1,
                 const GenericPoint3T<IT, ET> &p2);

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

template <typename IT, typename ET>
Sign lessThanOnX_IE_interval(const GenericPoint3T<IT, ET> &p1, IT bx);

template <typename IT, typename ET>
Sign lessThanOnX_IE_exact(const GenericPoint3T<IT, ET> &p1, ET bx);

template <typename IT, typename ET>
Sign lessThanOnX_IE_expansion(const GenericPoint3T<IT, ET> &p1, double bx);

template <typename IT, typename ET>
Sign lessThanOnX_IE(const GenericPoint3T<IT, ET> &p1, double bx);

template <typename IT, typename ET>
Sign lessThanOnX_IE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
Sign lessThanOnX_II_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnX_II_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnX_II_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnX_II(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnY_IE_interval(const GenericPoint3T<IT, ET> &p1, IT by);

template <typename IT, typename ET>
Sign lessThanOnY_IE_exact(const GenericPoint3T<IT, ET> &p1, ET by);

template <typename IT, typename ET>
Sign lessThanOnY_IE_expansion(const GenericPoint3T<IT, ET> &p1, double by);

template <typename IT, typename ET>
Sign lessThanOnY_IE(const GenericPoint3T<IT, ET> &p1, double by);

template <typename IT, typename ET>
Sign lessThanOnY_IE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
Sign lessThanOnY_II_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnY_II_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnY_II_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnY_II(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnZ_IE_interval(const GenericPoint3T<IT, ET> &p1, IT bz);

template <typename IT, typename ET>
Sign lessThanOnZ_IE_exact(const GenericPoint3T<IT, ET> &p1, ET bz);

template <typename IT, typename ET>
Sign lessThanOnZ_IE_expansion(const GenericPoint3T<IT, ET> &p1, double bz);

template <typename IT, typename ET>
Sign lessThanOnZ_IE(const GenericPoint3T<IT, ET> &p1, double bz);

template <typename IT, typename ET>
Sign lessThanOnZ_IE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &b);

template <typename IT, typename ET>
Sign lessThanOnZ_II_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnZ_II_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnZ_II_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2);

template <typename IT, typename ET>
Sign lessThanOnZ_II(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline std::array<Sign, 3> lessThanOnAll_EE(double x1, double y1, double z1,
                                            double x2, double y2, double z2)
{
  return std::array<Sign, 3>{static_cast<Sign>((x1 > x2) - (x1 < x2)),
                             static_cast<Sign>((y1 > y2) - (y1 < y2)),
                             static_cast<Sign>((z1 > z2) - (z1 < z2))};
}

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_EE(const GenericPoint3T<IT, ET> &a,
                                     const GenericPoint3T<IT, ET> &b)
{
  return lessThanOnAll_EE(a.x(), a.y(), a.z(), b.x(), b.y(), b.z());
}

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_IE(const GenericPoint3T<IT, ET> &p1,
                                     double x2, double y2, double z2)
{
  Sign retx = lessThanOnX_IE<IT, ET>(p1, x2);
  Sign rety = lessThanOnY_IE<IT, ET>(p1, y2);
  Sign retz = lessThanOnZ_IE<IT, ET>(p1, z2);
  return std::array<Sign, 3>{retx, rety, retz};
}

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_IE(const GenericPoint3T<IT, ET> &a,
                                     const GenericPoint3T<IT, ET> &b)
{
  return lessThanOnAll_IE<IT, ET>(a, b.x(), b.y(), b.z());
}

template <typename IT, typename ET>
std::array<Sign, 3> lessThanOnAll_II(const GenericPoint3T<IT, ET> &p1,
                                     const GenericPoint3T<IT, ET> &p2)
{
  Sign retx = lessThanOnX_II<IT, ET>(p1, p2);
  Sign rety = lessThanOnY_II<IT, ET>(p1, p2);
  Sign retz = lessThanOnZ_II<IT, ET>(p1, p2);
  return std::array<Sign, 3>{retx, rety, retz};
}

inline Sign lessThan_EE(double x1, double y1, double z1, double x2, double y2,
                        double z2)
{
  int ret = (x1 > x2) - (x1 < x2);
  if (ret)
    return static_cast<Sign>(ret);
  ret = (y1 > y2) - (y1 < y2);
  if (ret)
    return static_cast<Sign>(ret);
  return static_cast<Sign>((z1 > z2) - (z1 < z2));
}

template <typename IT, typename ET>
Sign lessThan_EE(const GenericPoint3T<IT, ET> &a,
                 const GenericPoint3T<IT, ET> &b)
{
  return lessThan_EE(a.x(), a.y(), a.z(), b.x(), b.y(), b.z());
}

template <typename IT, typename ET>
Sign lessThan_IE(const GenericPoint3T<IT, ET> &p1, double x2, double y2,
                 double z2)
{
  Sign ret = lessThanOnX_IE<IT, ET>(p1, x2);
  if (is_sign_posneg(ret))
    return ret;
  ret = lessThanOnY_IE<IT, ET>(p1, y2);
  if (is_sign_posneg(ret))
    return ret;
  return lessThanOnZ_IE<IT, ET>(p1, z2);
}

template <typename IT, typename ET>
Sign lessThan_IE(const GenericPoint3T<IT, ET> &a,
                 const GenericPoint3T<IT, ET> &b)
{
  return lessThan_IE<IT, ET>(a, b.x(), b.y(), b.z());
}

template <typename IT, typename ET>
Sign lessThan_II(const GenericPoint3T<IT, ET> &p1,
                 const GenericPoint3T<IT, ET> &p2)
{
  Sign ret;
  ret = lessThanOnX_II<IT, ET>(p1, p2);
  if (is_sign_posneg(ret))
    return ret;
  ret = lessThanOnY_II<IT, ET>(p1, p2);
  if (is_sign_posneg(ret))
    return ret;
  return lessThanOnZ_II<IT, ET>(p1, p2);
}

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

template <typename IT, typename ET>
Sign lessThanOnX_IE_interval(const GenericPoint3T<IT, ET> &p1, IT bx)
{
  IT l1x, l1y, l1z, d1;
  if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
    return Sign::UNCERTAIN;

  typename IT::Protector P;

  IT dbx = bx * d1;
  IT kx  = l1x - dbx;
  if (!kx.is_sign_reliable())
    return Sign::UNCERTAIN;
  return OMC::sign(kx);
}

template <typename IT, typename ET>
Sign lessThanOnX_IE_exact(const GenericPoint3T<IT, ET> &p1, ET bx)
{
  ET l1x, l1y, l1z, d1;
  p1.getExactLambda(l1x, l1y, l1z, d1);
  ET dbx = bx * d1;
  ET kx  = l1x - dbx;
  return OMC::sign(kx);
}

template <typename IT, typename ET>
Sign lessThanOnX_IE_expansion(const GenericPoint3T<IT, ET> &p1, double bx)
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
    double          dbx_p[128], *dbx = dbx_p;
    int    dbx_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, bx, &dbx, 128);
    double kx_p[128], *kx = kx_p;
    int kx_len = o.Gen_Diff_With_PreAlloc(l1x_len, l1x, dbx_len, dbx, &kx, 128);

    return_value = kx[kx_len - 1];
    if (kx_p != kx)
      FreeDoubles(kx);
    if (dbx_p != dbx)
      FreeDoubles(dbx);
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
    return lessThanOnX_IE_exact<IT, ET>(p1, bx);
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
Sign lessThanOnX_IE(const GenericPoint3T<IT, ET> &p1, double bx)
{
  OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_lessThanOnX_IE);
  Sign ret;
  ret = lessThanOnX_IE_interval<IT, ET>(p1, bx);
  if (is_sign_reliable(ret))
    return ret;
  OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_lessThanOnX_IE);
  return lessThanOnX_IE_expansion<IT, ET>(p1, bx);
}

template <typename IT, typename ET>
Sign lessThanOnX_IE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &b)
{
  return lessThanOnX_IE<IT, ET>(p1, b.x());
}

template <typename IT, typename ET>
Sign lessThanOnX_II_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2)
{
  IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
  if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
      !p2.getIntervalLambda(l2x, l2y, l2z, d2))
    return Sign::UNCERTAIN;

  typename IT::Protector P;

  IT k1 = d2 * l1x;
  IT k2 = d1 * l2x;
  IT kx = k1 - k2;
  if (!kx.is_sign_reliable())
    return Sign::UNCERTAIN;
  return OMC::sign(kx);
}

template <typename IT, typename ET>
Sign lessThanOnX_II_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2)
{
  ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
  p1.getExactLambda(l1x, l1y, l1z, d1);
  p2.getExactLambda(l2x, l2y, l2z, d2);
  ET k1 = d2 * l1x;
  ET k2 = d1 * l2x;
  ET kx = k1 - k2;
  return OMC::sign(kx);
}

template <typename IT, typename ET>
Sign lessThanOnX_II_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2)
{
  double return_value = NAN;
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
  if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
  {
    expansionObject o;
    double          k1_p[128], *k1 = k1_p;
    int             k1_len =
      o.Gen_Product_With_PreAlloc(d2_len, d2, l1x_len, l1x, &k1, 128);
    double k2_p[128], *k2 = k2_p;
    int    k2_len =
      o.Gen_Product_With_PreAlloc(d1_len, d1, l2x_len, l2x, &k2, 128);
    double kx_p[128], *kx = kx_p;
    int    kx_len = o.Gen_Diff_With_PreAlloc(k1_len, k1, k2_len, k2, &kx, 128);

    return_value = kx[kx_len - 1];
    if (kx_p != kx)
      FreeDoubles(kx);
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
    return lessThanOnX_II_exact<IT, ET>(p1, p2);
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
Sign lessThanOnX_II(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2)
{
  OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_lessThanOnX_II);
  Sign ret;
  ret = lessThanOnX_II_interval<IT, ET>(p1, p2);
  if (is_sign_reliable(ret))
    return ret;
  OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_lessThanOnX_II);
  return lessThanOnX_II_expansion<IT, ET>(p1, p2);
}

template <typename IT, typename ET>
Sign lessThanOnY_IE_interval(const GenericPoint3T<IT, ET> &p1, IT by)
{
  IT l1x, l1y, l1z, d1;
  if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
    return Sign::UNCERTAIN;

  typename IT::Protector P;

  IT dby = by * d1;
  IT ky  = l1y - dby;
  if (!ky.is_sign_reliable())
    return Sign::UNCERTAIN;
  return OMC::sign(ky);
}

template <typename IT, typename ET>
Sign lessThanOnY_IE_exact(const GenericPoint3T<IT, ET> &p1, ET by)
{
  ET l1x, l1y, l1z, d1;
  p1.getExactLambda(l1x, l1y, l1z, d1);
  ET dby = by * d1;
  ET ky  = l1y - dby;
  return OMC::sign(ky);
}

template <typename IT, typename ET>
Sign lessThanOnY_IE_expansion(const GenericPoint3T<IT, ET> &p1, double by)
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
    double          dby_p[128], *dby = dby_p;
    int    dby_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, by, &dby, 128);
    double ky_p[128], *ky = ky_p;
    int ky_len = o.Gen_Diff_With_PreAlloc(l1y_len, l1y, dby_len, dby, &ky, 128);

    return_value = ky[ky_len - 1];
    if (ky_p != ky)
      FreeDoubles(ky);
    if (dby_p != dby)
      FreeDoubles(dby);
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
    return lessThanOnY_IE_exact<IT, ET>(p1, by);
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
Sign lessThanOnY_IE(const GenericPoint3T<IT, ET> &p1, double by)
{
  OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_lessThanOnY_IE);
  Sign ret;
  ret = lessThanOnY_IE_interval<IT, ET>(p1, by);
  if (is_sign_reliable(ret))
    return ret;
  OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_lessThanOnY_IE);
  return lessThanOnY_IE_expansion<IT, ET>(p1, by);
}

template <typename IT, typename ET>
Sign lessThanOnY_IE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &b)
{
  return lessThanOnY_IE<IT, ET>(p1, b.y());
}

template <typename IT, typename ET>
Sign lessThanOnY_II_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2)
{
  IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
  if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
      !p2.getIntervalLambda(l2x, l2y, l2z, d2))
    return Sign::UNCERTAIN;

  typename IT::Protector P;

  IT k1 = d2 * l1y;
  IT k2 = d1 * l2y;
  IT ky = k1 - k2;
  if (!ky.is_sign_reliable())
    return Sign::UNCERTAIN;
  return OMC::sign(ky);
}

template <typename IT, typename ET>
Sign lessThanOnY_II_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2)
{
  ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
  p1.getExactLambda(l1x, l1y, l1z, d1);
  p2.getExactLambda(l2x, l2y, l2z, d2);
  ET k1 = d2 * l1y;
  ET k2 = d1 * l2y;
  ET ky = k1 - k2;
  return OMC::sign(ky);
}

template <typename IT, typename ET>
Sign lessThanOnY_II_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2)
{
  double return_value = NAN;
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
  if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
  {
    expansionObject o;
    double          k1_p[128], *k1 = k1_p;
    int             k1_len =
      o.Gen_Product_With_PreAlloc(d2_len, d2, l1y_len, l1y, &k1, 128);
    double k2_p[128], *k2 = k2_p;
    int    k2_len =
      o.Gen_Product_With_PreAlloc(d1_len, d1, l2y_len, l2y, &k2, 128);
    double ky_p[128], *ky = ky_p;
    int    ky_len = o.Gen_Diff_With_PreAlloc(k1_len, k1, k2_len, k2, &ky, 128);

    return_value = ky[ky_len - 1];
    if (ky_p != ky)
      FreeDoubles(ky);
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
    return lessThanOnY_II_exact<IT, ET>(p1, p2);
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
Sign lessThanOnY_II(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2)
{
  OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_lessThanOnY_II);
  Sign ret;
  ret = lessThanOnY_II_interval<IT, ET>(p1, p2);
  if (is_sign_reliable(ret))
    return ret;
  OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_lessThanOnY_II);
  return lessThanOnY_II_expansion<IT, ET>(p1, p2);
}

template <typename IT, typename ET>
Sign lessThanOnZ_IE_interval(const GenericPoint3T<IT, ET> &p1, IT bz)
{
  IT l1x, l1y, l1z, d1;
  if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
    return Sign::UNCERTAIN;

  typename IT::Protector P;

  IT dbz = bz * d1;
  IT kz  = l1z - dbz;
  if (!kz.is_sign_reliable())
    return Sign::UNCERTAIN;
  return OMC::sign(kz);
}

template <typename IT, typename ET>
Sign lessThanOnZ_IE_exact(const GenericPoint3T<IT, ET> &p1, ET bz)
{
  ET l1x, l1y, l1z, d1;
  p1.getExactLambda(l1x, l1y, l1z, d1);
  ET dbz = bz * d1;
  ET kz  = l1z - dbz;
  return OMC::sign(kz);
}

template <typename IT, typename ET>
Sign lessThanOnZ_IE_expansion(const GenericPoint3T<IT, ET> &p1, double bz)
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
    double          dbz_p[128], *dbz = dbz_p;
    int    dbz_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, bz, &dbz, 128);
    double kz_p[128], *kz = kz_p;
    int kz_len = o.Gen_Diff_With_PreAlloc(l1z_len, l1z, dbz_len, dbz, &kz, 128);

    return_value = kz[kz_len - 1];
    if (kz_p != kz)
      FreeDoubles(kz);
    if (dbz_p != dbz)
      FreeDoubles(dbz);
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
    return lessThanOnZ_IE_exact<IT, ET>(p1, bz);
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
Sign lessThanOnZ_IE(const GenericPoint3T<IT, ET> &p1, double bz)
{
  OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_lessThanOnZ_IE);
  Sign ret;
  ret = lessThanOnZ_IE_interval<IT, ET>(p1, bz);
  if (is_sign_reliable(ret))
    return ret;
  OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_lessThanOnZ_IE);
  return lessThanOnZ_IE_expansion<IT, ET>(p1, bz);
}

template <typename IT, typename ET>
Sign lessThanOnZ_IE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &b)
{
  return lessThanOnZ_IE<IT, ET>(p1, b.z());
}

template <typename IT, typename ET>
Sign lessThanOnZ_II_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2)
{
  IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
  if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
      !p2.getIntervalLambda(l2x, l2y, l2z, d2))
    return Sign::UNCERTAIN;

  typename IT::Protector P;

  IT k1 = d2 * l1z;
  IT k2 = d1 * l2z;
  IT kz = k1 - k2;
  if (!kz.is_sign_reliable())
    return Sign::UNCERTAIN;
  return OMC::sign(kz);
}

template <typename IT, typename ET>
Sign lessThanOnZ_II_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2)
{
  ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
  p1.getExactLambda(l1x, l1y, l1z, d1);
  p2.getExactLambda(l2x, l2y, l2z, d2);
  ET k1 = d2 * l1z;
  ET k2 = d1 * l2z;
  ET kz = k1 - k2;
  return OMC::sign(kz);
}

template <typename IT, typename ET>
Sign lessThanOnZ_II_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2)
{
  double return_value = NAN;
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
  if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
  {
    expansionObject o;
    double          k1_p[128], *k1 = k1_p;
    int             k1_len =
      o.Gen_Product_With_PreAlloc(d2_len, d2, l1z_len, l1z, &k1, 128);
    double k2_p[128], *k2 = k2_p;
    int    k2_len =
      o.Gen_Product_With_PreAlloc(d1_len, d1, l2z_len, l2z, &k2, 128);
    double kz_p[128], *kz = kz_p;
    int    kz_len = o.Gen_Diff_With_PreAlloc(k1_len, k1, k2_len, k2, &kz, 128);

    return_value = kz[kz_len - 1];
    if (kz_p != kz)
      FreeDoubles(kz);
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
    return lessThanOnZ_II_exact<IT, ET>(p1, p2);
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
Sign lessThanOnZ_II(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2)
{
  OMC_PRED_PROFILE_INC_FILTER(PredicateNames::_lessThanOnZ_II);
  Sign ret;
  ret = lessThanOnZ_II_interval<IT, ET>(p1, p2);
  if (is_sign_reliable(ret))
    return ret;
  OMC_PRED_PROFILE_INC_DFAIL(PredicateNames::_lessThanOnZ_II);
  return lessThanOnZ_II_expansion<IT, ET>(p1, p2);
}

} // namespace OMC