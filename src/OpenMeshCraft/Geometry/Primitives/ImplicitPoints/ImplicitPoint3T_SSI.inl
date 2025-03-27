#pragma once

#include "OpenMeshCraft/Geometry/Predicates/InternalDetails/ImplicitPointPredicates.inl"
#include "OpenMeshCraft/Geometry/Primitives/ImplicitPoint3T.h"

namespace OMC {

template <typename IT, typename ET>
ImplicitPoint3T_SSI<IT, ET>::ImplicitPoint3T_SSI() noexcept
  : GP(PointType::SSI)
  , ia(nullptr)
  , ib(nullptr)
  , ip(nullptr)
  , iq(nullptr)
  , plane(-1)
{
}

template <typename IT, typename ET>
ImplicitPoint3T_SSI<IT, ET>::ImplicitPoint3T_SSI(const EP &_a, const EP &_b,
                                                 const EP &_p, const EP &_q,
                                                 int _plane) noexcept
  : GP(PointType::SSI)
  , ia(&_a)
  , ib(&_b)
  , ip(&_p)
  , iq(&_q)
  , plane(_plane)
{
#ifdef OMC_CACHE_DF
  if (plane == 0) // YZ
  {
    // first yz, then x
    if (!lambda3d_SSI_interval<IT>(A().y(), A().z(), A().x(), B().y(), B().z(),
                                   B().x(), P().y(), P().z(), Q().y(), Q().z(),
                                   m_ly, m_lz, m_lx, m_d))
      m_d = 0;
  }
  else if (plane == 1) // ZX
  {
    // first zx, then y
    if (!lambda3d_SSI_interval<IT>(A().z(), A().x(), A().y(), B().z(), B().x(),
                                   B().y(), P().z(), P().x(), Q().z(), Q().x(),
                                   m_lz, m_lx, m_ly, m_d))
      m_d = 0;
  }
  else if (plane == 2) // XY
  {
    // first xy, then z
    if (!lambda3d_SSI_interval<IT>(A().x(), A().y(), A().z(), B().x(), B().y(),
                                   B().z(), P().x(), P().y(), Q().x(), Q().y(),
                                   m_lx, m_ly, m_lz, m_d))
      m_d = 0;
  }
  else
  {
    OMC_EXIT("wrong plane in SSI.");
  }

  if (m_d.is_negative())
    m_lx = -m_lx, m_ly = -m_ly, m_lz = -m_lz, m_d = -m_d;
#endif
}

template <typename IT, typename ET>
ImplicitPoint3T_SSI<IT, ET>::~ImplicitPoint3T_SSI() noexcept
{
}

template <typename IT, typename ET>
ImplicitPoint3T_SSI<IT, ET>::ImplicitPoint3T_SSI(const IP &rhs) noexcept
  : GP(static_cast<const GP &>(rhs))
  , ia(rhs.ia)
  , ib(rhs.ib)
  , ip(rhs.ip)
  , iq(rhs.iq)
  , plane(rhs.plane)
{
#ifdef OMC_CACHE_DF
  m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
}

template <typename IT, typename ET>
ImplicitPoint3T_SSI<IT, ET>::ImplicitPoint3T_SSI(IP &&rhs) noexcept
  : GP(static_cast<GP &&>(rhs))
  , ia(rhs.ia)
  , ib(rhs.ib)
  , ip(rhs.ip)
  , iq(rhs.iq)
  , plane(rhs.plane)
{
#ifdef OMC_CACHE_DF
  m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
}

template <typename IT, typename ET>
auto ImplicitPoint3T_SSI<IT, ET>::operator=(const IP &rhs) -> IP &
{
  *static_cast<GP *>(this) = (static_cast<const GP &>(rhs));
  ia = rhs.ia, ib = rhs.ib, ip = rhs.ip, iq = rhs.iq, plane = rhs.plane;
#ifdef OMC_CACHE_DF
  m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
  return *this;
}

template <typename IT, typename ET>
auto ImplicitPoint3T_SSI<IT, ET>::operator=(IP &&rhs) -> IP &
{
  *static_cast<GP *>(this) = (static_cast<GP &&>(rhs));
  ia = rhs.ia, ib = rhs.ib, ip = rhs.ip, iq = rhs.iq, plane = rhs.plane;
#ifdef OMC_CACHE_DF
  m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
  return *this;
}

template <typename IT, typename ET>
bool ImplicitPoint3T_SSI<IT, ET>::getIntervalLambda(IT &lx, IT &ly, IT &lz,
                                                    IT &d) const
{
#ifdef OMC_CACHE_DF
  lx = m_lx, ly = m_ly, lz = m_lz, d = m_d;
  return (d.is_sign_reliable());
#else
  bool gcv_enabled = this->gcv().is_enabled();

  typename GP::GCV::OnePointCachedValues *cv =
    gcv_enabled ? &(this->gcv().get((void *)this)) : nullptr;

  // if lambda values are cached, return them
  if (gcv_enabled && cv->dfilter_cached)
  {
    lx = cv->dfilter_lx, ly = cv->dfilter_ly, lz = cv->dfilter_lz,
    d = cv->dfilter_d;
    return d.is_sign_reliable();
  }

  // otherwise, calculate the lambda values
  if (plane == 0) // YZ, first yz, then x
    lambda3d_SSI_interval<IT>(A().y(), A().z(), A().x(), B().y(), B().z(),
                              B().x(), P().y(), P().z(), Q().y(), Q().z(), ly,
                              lz, lx, d);
  else if (plane == 1) // ZX, first zx, then y
    lambda3d_SSI_interval<IT>(A().z(), A().x(), A().y(), B().z(), B().x(),
                              B().y(), P().z(), P().x(), Q().z(), Q().x(), lz,
                              lx, ly, d);
  else if (plane == 2) // XY, first xy, then z
    lambda3d_SSI_interval<IT>(A().x(), A().y(), A().z(), B().x(), B().y(),
                              B().z(), P().x(), P().y(), Q().x(), Q().y(), lx,
                              ly, lz, d);
  else
  {
    OMC_ASSERT(false, "plane is not initialized.");
  }

  if (d.is_negative())
    lx.invert(), ly.invert(), lz.invert(), d.invert();

  // then, cache the lambda values
  if (gcv_enabled && !cv->dfilter_cached)
  {
    cv->dfilter_lx = lx, cv->dfilter_ly = ly, cv->dfilter_lz = lz,
    cv->dfilter_d = d, cv->dfilter_cached = true;
  }

  return d.is_sign_reliable();
#endif
}

template <typename IT, typename ET>
void ImplicitPoint3T_SSI<IT, ET>::getExactLambda(ET &lx, ET &ly, ET &lz,
                                                 ET &d) const
{
  bool gcv_enabled = this->gcv().is_enabled();

  typename GP::GCV::OnePointCachedValues *cv =
    gcv_enabled ? &(this->gcv().get((void *)this)) : nullptr;

  // if lambda values are cached, return them
  if (gcv_enabled && cv->exact_cached)
  {
    lx = *cv->exact_lx, ly = *cv->exact_ly, lz = *cv->exact_lz,
    d = *cv->exact_d;
    return;
  }

  // otherwise, calculate the lambda values
  if (plane == 0) // yz, first yz, then x
    lambda3d_SSI_exact<ET>(A().y(), A().z(), A().x(), B().y(), B().z(), B().x(),
                           P().y(), P().z(), Q().y(), Q().z(), ly, lz, lx, d);
  else if (plane == 1) // zx, first zx, then y
    lambda3d_SSI_exact<ET>(A().z(), A().x(), A().y(), B().z(), B().x(), B().y(),
                           P().z(), P().x(), Q().z(), Q().x(), lz, lx, ly, d);
  else if (plane == 2) // xy, first xy, then z
    lambda3d_SSI_exact<ET>(A().x(), A().y(), A().z(), B().x(), B().y(), B().z(),
                           P().x(), P().y(), Q().x(), Q().y(), lx, ly, lz, d);
  else
  {
    OMC_ASSERT(false, "plane not initialized.");
  }

  if (OMC::sign(d) == Sign::NEGATIVE)
    lx = -lx, ly = -ly, lz = -lz, d = -d;

  // then, cache the lambda values
  if (gcv_enabled && !cv->exact_cached)
  {
    cv->alloc_exact();
    *cv->exact_lx = lx, *cv->exact_ly = ly, *cv->exact_lz = lz,
    *cv->exact_d = d, cv->exact_cached = true;
  }
}

template <typename IT, typename ET>
void ImplicitPoint3T_SSI<IT, ET>::getExpansionLambda(NT **lx, int &lx_len,
                                                     NT **ly, int &ly_len,
                                                     NT **lz, int &lz_len,
                                                     NT **d, int &d_len) const
{
  bool gcv_enabled = this->gcv().is_enabled();

  typename GP::GCV::OnePointCachedValues *cv =
    gcv_enabled ? &(this->gcv().get((void *)this)) : nullptr;

  // if lambda values are cached, return them
  if (gcv_enabled && cv->expansion_cached)
  {
    *lx = cv->expansion_lx, *ly = cv->expansion_ly, *lz = cv->expansion_lz,
    *d = cv->expansion_d, lx_len = cv->expansion_lx_len,
    ly_len = cv->expansion_ly_len, lz_len = cv->expansion_lz_len,
    d_len = cv->expansion_d_len;
    return;
  }

  // if cache is enabled, allocate new memory for lambda values
  if (gcv_enabled)
    lx_len = 0, ly_len = 0, lz_len = 0, d_len = 0;

  // otherwise, calculate the lambda values
  if (plane == 0) // YZ, first yz, then x
    lambda3d_SSI_expansion(A().y(), A().z(), A().x(), B().y(), B().z(), B().x(),
                           P().y(), P().z(), Q().y(), Q().z(), ly, ly_len, lz,
                           lz_len, lx, lx_len, d, d_len);
  else if (plane == 1) // ZX, first zx, then y
    lambda3d_SSI_expansion(A().z(), A().x(), A().y(), B().z(), B().x(), B().y(),
                           P().z(), P().x(), Q().z(), Q().x(), lz, lz_len, lx,
                           lx_len, ly, ly_len, d, d_len);
  else if (plane == 2) // XY, first xy, then z
    lambda3d_SSI_expansion(A().x(), A().y(), A().z(), B().x(), B().y(), B().z(),
                           P().x(), P().y(), Q().x(), Q().y(), lx, lx_len, ly,
                           ly_len, lz, lz_len, d, d_len);
  else
  {
    OMC_ASSERT(false, "plane not initialized.");
  }
  expansionObject o;

  // compress the expansion if necessary
#ifdef OMC_COMPRESS_EXPANSION
  o.CompressIf(lx_len, *lx);
  o.CompressIf(ly_len, *ly);
  o.CompressIf(lz_len, *lz);
  o.CompressIf(d_len, *d);
#endif

  // if d is negative, invert all lambda values
  if ((*d)[d_len - 1] < 0)
  {
    o.Gen_Invert(lx_len, *lx);
    o.Gen_Invert(ly_len, *ly);
    o.Gen_Invert(lz_len, *lz);
    o.Gen_Invert(d_len, *d);
  }
  normalizeLambda3D(*lx, lx_len, *ly, ly_len, *lz, lz_len, *d, d_len);

  // update interval number by newly calculated expansion
#ifdef OMC_UPDATE_INTERVAL_BY_EXPANSION
  // calculate the interval values by expansion
  auto ilx = o.To_Interval(lx_len, *lx), ily = o.To_Interval(ly_len, *ly),
       ilz = o.To_Interval(lz_len, *lz), id = o.To_Interval(d_len, *d);
  // update interval number
  #ifdef OMC_CACHE_DF
  m_lx = IT(ilx.first, ilx.second), m_ly = IT(ily.first, ily.second),
  m_lz = IT(ilz.first, ilz.second), m_d = IT(id.first, id.second);
  #else
  if (gcv_enabled && cv)
  {
    cv->dfilter_lx     = IT(ilx.first, ilx.second);
    cv->dfilter_ly     = IT(ily.first, ily.second);
    cv->dfilter_lz     = IT(ilz.first, ilz.second);
    cv->dfilter_d      = IT(id.first, id.second);
    cv->dfilter_cached = true;
  }
  #endif
#endif

  // then, cache the lambda values
  if (gcv_enabled && !cv->expansion_cached)
  {
    cv->expansion_lx = *lx, cv->expansion_ly = *ly, cv->expansion_lz = *lz,
    cv->expansion_d = *d, cv->expansion_lx_len = lx_len,
    cv->expansion_ly_len = ly_len, cv->expansion_lz_len = lz_len,
    cv->expansion_d_len = d_len, cv->expansion_cached = true;
  }
}

} // namespace OMC