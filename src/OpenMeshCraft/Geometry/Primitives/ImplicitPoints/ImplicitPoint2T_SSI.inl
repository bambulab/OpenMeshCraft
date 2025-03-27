#pragma once

#include "OpenMeshCraft/Geometry/Predicates/InternalDetails/ImplicitPointPredicates.inl"
#include "OpenMeshCraft/Geometry/Primitives/ImplicitPoint2T.h"

namespace OMC {

template <typename IT, typename ET>
ImplicitPoint2T_SSI<IT, ET>::ImplicitPoint2T_SSI() noexcept
  : GP(PointType::SSI)
  , ia(nullptr)
  , ib(nullptr)
  , ip(nullptr)
  , iq(nullptr)
{
}

template <typename IT, typename ET>
ImplicitPoint2T_SSI<IT, ET>::ImplicitPoint2T_SSI(const EP &a, const EP &b,
                                                 const EP &p,
                                                 const EP &q) noexcept
  : GP(PointType::SSI)
  , ia(&a)
  , ib(&b)
  , ip(&p)
  , iq(&q)
{
}

template <typename IT, typename ET>
ImplicitPoint2T_SSI<IT, ET>::ImplicitPoint2T_SSI(const IP &rhs) noexcept
  : GP(static_cast<const GP &>(rhs))
  , ia(rhs.ia)
  , ib(rhs.ib)
  , ip(rhs.ip)
  , iq(rhs.iq)
{
}

template <typename IT, typename ET>
ImplicitPoint2T_SSI<IT, ET>::ImplicitPoint2T_SSI(IP &&rhs) noexcept
  : GP(static_cast<GP &&>(rhs))
  , ia(rhs.ia)
  , ib(rhs.ib)
  , iq(rhs.iq)
  , ip(rhs.ip)
{
}

template <typename IT, typename ET>
auto ImplicitPoint2T_SSI<IT, ET>::operator=(const IP &rhs) -> IP &
{
  *static_cast<GP *>(this) = (static_cast<const GP &>(rhs));

  ia = rhs.ia;
  ib = rhs.ib;
  iq = rhs.iq;
  ip = rhs.ip;
  return *this;
}

template <typename IT, typename ET>
auto ImplicitPoint2T_SSI<IT, ET>::operator=(IP &&rhs) -> IP &
{
  *static_cast<GP *>(this) = (static_cast<GP &&>(rhs));

  ia = rhs.ia;
  ib = rhs.ib;
  iq = rhs.iq;
  ip = rhs.ip;
  return *this;
}

template <typename IT, typename ET>
bool ImplicitPoint2T_SSI<IT, ET>::getIntervalLambda(IT &lx, IT &ly, IT &d) const
{
  bool gcv_enabled = this->gcv().is_enabled();

  typename GP::GCV::OnePointCachedValues *cv =
    gcv_enabled ? &(this->gcv().get((void *)this)) : nullptr;

  // if lambda values are cached, return them
  if (gcv_enabled && cv->dfilter_cached)
  {
    lx = cv->dfilter_lx, ly = cv->dfilter_ly, d = cv->dfilter_d;
    return (cv->dfilter_d.is_sign_reliable());
  }

  // otherwise, calculate the lambda values
  lambda2d_SSI_interval<IT>(A().x(), A().y(), B().x(), B().y(), P().x(),
                            P().y(), Q().x(), Q().y(), lx, ly, d);
  if (d.is_negative())
    lx.invert(), ly.invert(), d.invert();

  // then, cache the lambda values
  if (gcv_enabled && !cv->dfilter_cached)
  {
    cv->dfilter_lx = lx, cv->dfilter_ly = ly, cv->dfilter_d = d;
    cv->dfilter_cached = true;
  }

  return d.is_sign_reliable();
}

template <typename IT, typename ET>
void ImplicitPoint2T_SSI<IT, ET>::getExactLambda(ET &lx, ET &ly, ET &d) const
{
  bool gcv_enabled = this->gcv().is_enabled();

  typename GP::GCV::OnePointCachedValues *cv =
    gcv_enabled ? &(this->gcv().get((void *)this)) : nullptr;

  // if lambda values are cached, return them
  if (gcv_enabled && cv->exact_cached)
  {
    lx = *cv->exact_lx, ly = *cv->exact_ly, d = *cv->exact_d;
    return;
  }

  // otherwise, calculate the lambda values
  lambda2d_SSI_exact<ET>(A().x(), A().y(), B().x(), B().y(), P().x(), P().y(),
                         Q().x(), Q().y(), lx, ly, d);
  if (OMC::sign(d) == Sign::NEGATIVE)
    lx = -lx, ly = -ly, d = -d;

  // then, cache the lambda values
  if (gcv_enabled && !cv->exact_cached)
  {
    cv->alloc_exact();
    *cv->exact_lx = lx, *cv->exact_ly = ly, *cv->exact_d = d;
    cv->exact_cached = true;
  }
}

template <typename IT, typename ET>
void ImplicitPoint2T_SSI<IT, ET>::getExpansionLambda(NT **lx, int &lx_len,
                                                     NT **ly, int &ly_len,
                                                     NT **d, int &d_len) const
{
  bool gcv_enabled = this->gcv().is_enabled();

  typename GP::GCV::OnePointCachedValues *cv =
    gcv_enabled ? &(this->gcv().get((void *)this)) : nullptr;

  // if lambda values are cached, return them
  if (gcv_enabled && cv->expansion_cached)
  {
    *lx = cv->expansion_lx, *ly = cv->expansion_ly, *d = cv->expansion_d,
    lx_len = cv->expansion_lx_len, ly_len = cv->expansion_ly_len,
    d_len = cv->expansion_d_len;
    return;
  }

  // if cache is enabled, allocate new memory for lambda values
  if (gcv_enabled)
    lx_len = 0, ly_len = 0, d_len = 0;

  // otherwise, calculate the lambda values
  lambda2d_SSI_expansion(A().x(), A().y(), B().x(), B().y(), P().x(), P().y(),
                         Q().x(), Q().y(), lx, lx_len, ly, ly_len, d, d_len);
  if ((*d)[d_len - 1] < 0)
  {
    expansionObject o;
    o.Gen_Invert(lx_len, *lx);
    o.Gen_Invert(ly_len, *ly);
    o.Gen_Invert(d_len, *d);
  }

  // then, cache the lambda values
  if (gcv_enabled && !cv->expansion_cached)
  {
    cv->expansion_lx = *lx, cv->expansion_ly = *ly, cv->expansion_d = *d,
    cv->expansion_lx_len = lx_len, cv->expansion_ly_len = ly_len,
    cv->expansion_d_len = d_len, cv->expansion_cached = true;
  }
}

} // namespace OMC