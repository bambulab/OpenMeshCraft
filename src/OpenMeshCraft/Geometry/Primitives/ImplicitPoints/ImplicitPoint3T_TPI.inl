#pragma once

#include "OpenMeshCraft/Geometry/Predicates/InternalDetails/ImplicitPointPredicates.inl"
#include "OpenMeshCraft/Geometry/Primitives/ImplicitPoint3T.h"

namespace OMC {

template <typename IT, typename ET>
ImplicitPoint3T_TPI<IT, ET>::ImplicitPoint3T_TPI() noexcept
  : GP(PointType::TPI)
{
}

template <typename IT, typename ET>
ImplicitPoint3T_TPI<IT, ET>::ImplicitPoint3T_TPI(const EP &_v1, const EP &_v2,
                                                 const EP &_v3, const EP &_w1,
                                                 const EP &_w2, const EP &_w3,
                                                 const EP &_u1, const EP &_u2,
                                                 const EP &_u3) noexcept
  : GP(PointType::TPI)
  , iv1(&_v1)
  , iv2(&_v2)
  , iv3(&_v3)
  , iw1(&_w1)
  , iw2(&_w2)
  , iw3(&_w3)
  , iu1(&_u1)
  , iu2(&_u2)
  , iu3(&_u3)
{
#ifdef OMC_CACHE_DF
	if (!lambda3d_TPI_interval<IT>(
	      V1().x(), V1().y(), V1().z(), V2().x(), V2().y(), V2().z(), V3().x(),
	      V3().y(), V3().z(), W1().x(), W1().y(), W1().z(), W2().x(), W2().y(),
	      W2().z(), W3().x(), W3().y(), W3().z(), U1().x(), U1().y(), U1().z(),
	      U2().x(), U2().y(), U2().z(), U3().x(), U3().y(), U3().z(), m_lx, m_ly,
	      m_lz, m_d))
		m_d = 0;

	if (m_d.is_negative())
		m_lx = -m_lx, m_ly = -m_ly, m_lz = -m_lz, m_d = -m_d;
#endif
}

template <typename IT, typename ET>
ImplicitPoint3T_TPI<IT, ET>::~ImplicitPoint3T_TPI() noexcept
{
}

template <typename IT, typename ET>
ImplicitPoint3T_TPI<IT, ET>::ImplicitPoint3T_TPI(const IP &rhs) noexcept
  : GP(static_cast<const GP &>(rhs))
  , iv1(rhs.iv1)
  , iv2(rhs.iv2)
  , iv3(rhs.iv3)
  , iw1(rhs.iw1)
  , iw2(rhs.iw2)
  , iw3(rhs.iw3)
  , iu1(rhs.iu1)
  , iu2(rhs.iu2)
  , iu3(rhs.iu3)
{
#ifdef OMC_CACHE_DF
	m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
}

template <typename IT, typename ET>
ImplicitPoint3T_TPI<IT, ET>::ImplicitPoint3T_TPI(IP &&rhs) noexcept
  : GP(static_cast<GP &&>(rhs))
  , iv1(rhs.iv1)
  , iv2(rhs.iv2)
  , iv3(rhs.iv3)
  , iw1(rhs.iw1)
  , iw2(rhs.iw2)
  , iw3(rhs.iw3)
  , iu1(rhs.iu1)
  , iu2(rhs.iu2)
  , iu3(rhs.iu3)
{
#ifdef OMC_CACHE_DF
	m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
}

template <typename IT, typename ET>
auto ImplicitPoint3T_TPI<IT, ET>::operator=(const IP &rhs) -> IP &
{
	*static_cast<GP *>(this) = (static_cast<const GP &>(rhs));
	iv1 = rhs.iv1, iv2 = rhs.iv2, iv3 = rhs.iv3;
	iw1 = rhs.iw1, iw2 = rhs.iw2, iw3 = rhs.iw3;
	iu1 = rhs.iu1, iu2 = rhs.iu2, iu3 = rhs.iu3;
#ifdef OMC_CACHE_DF
	m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
	return *this;
}

template <typename IT, typename ET>
auto ImplicitPoint3T_TPI<IT, ET>::operator=(IP &&rhs) -> IP &
{
	*static_cast<GP *>(this) = (static_cast<GP &&>(rhs));
	iv1 = rhs.iv1, iv2 = rhs.iv2, iv3 = rhs.iv3;
	iw1 = rhs.iw1, iw2 = rhs.iw2, iw3 = rhs.iw3;
	iu1 = rhs.iu1, iu2 = rhs.iu2, iu3 = rhs.iu3;
#ifdef OMC_CACHE_DF
	m_lx = rhs.m_lx, m_ly = rhs.m_ly, m_lz = rhs.m_lz, m_d = rhs.m_d;
#endif
	return *this;
}

template <typename IT, typename ET>
bool ImplicitPoint3T_TPI<IT, ET>::getIntervalLambda(IT &lx, IT &ly, IT &lz,
                                                    IT &d) const
{
#ifdef OMC_CACHE_DF
	lx = m_lx, ly = m_ly, lz = m_lz, d = m_d;
	return (d.is_sign_reliable());
#else
	bool gcv_enabled = gcv().is_enabled();

	typename GCV::OnePointCachedValues *cv =
	  gcv_enabled ? &gcv().get((void *)this) : nullptr;

	// if lambda values are cached, return them
	if (gcv_enabled && cv->dfilter_cached)
	{
		lx = cv->dfilter_lx, ly = cv->dfilter_ly, lz = cv->dfilter_lz,
		d = cv->dfilter_d;
		return d.is_sign_reliable();
	}

	// otherwise, calculate the lambda values
	lambda3d_TPI_interval<IT>(
	  V1().x(), V1().y(), V1().z(), V2().x(), V2().y(), V2().z(), V3().x(),
	  V3().y(), V3().z(), W1().x(), W1().y(), W1().z(), W2().x(), W2().y(),
	  W2().z(), W3().x(), W3().y(), W3().z(), U1().x(), U1().y(), U1().z(),
	  U2().x(), U2().y(), U2().z(), U3().x(), U3().y(), U3().z(), lx, ly, lz, d);
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
void ImplicitPoint3T_TPI<IT, ET>::getExactLambda(ET &lx, ET &ly, ET &lz,
                                                 ET &d) const
{
	bool gcv_enabled = gcv().is_enabled();

	typename GCV::OnePointCachedValues *cv =
	  gcv_enabled ? &gcv().get((void *)this) : nullptr;

	// if lambda values are cached, return them
	if (gcv_enabled && cv->exact_cached)
	{
		lx = *cv->exact_lx, ly = *cv->exact_ly, lz = *cv->exact_lz,
		d = *cv->exact_d;
		return;
	}

	// otherwise, calculate the lambda values
	lambda3d_TPI_exact<ET>(
	  V1().x(), V1().y(), V1().z(), V2().x(), V2().y(), V2().z(), V3().x(),
	  V3().y(), V3().z(), W1().x(), W1().y(), W1().z(), W2().x(), W2().y(),
	  W2().z(), W3().x(), W3().y(), W3().z(), U1().x(), U1().y(), U1().z(),
	  U2().x(), U2().y(), U2().z(), U3().x(), U3().y(), U3().z(), lx, ly, lz, d);
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
void ImplicitPoint3T_TPI<IT, ET>::getExpansionLambda(FT **lx, int &lx_len,
                                                     FT **ly, int &ly_len,
                                                     FT **lz, int &lz_len,
                                                     FT **d, int &d_len) const
{
	bool gcv_enabled = gcv().is_enabled();

	typename GCV::OnePointCachedValues *cv =
	  gcv_enabled ? &gcv().get((void *)this) : nullptr;

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
	lambda3d_TPI_expansion(
	  V1().x(), V1().y(), V1().z(), V2().x(), V2().y(), V2().z(), V3().x(),
	  V3().y(), V3().z(), W1().x(), W1().y(), W1().z(), W2().x(), W2().y(),
	  W2().z(), W3().x(), W3().y(), W3().z(), U1().x(), U1().y(), U1().z(),
	  U2().x(), U2().y(), U2().z(), U3().x(), U3().y(), U3().z(), lx, lx_len, ly,
	  ly_len, lz, lz_len, d, d_len);
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

template <typename IT, typename ET>
void ImplicitPoint3T_TPI<IT, ET>::get_explicit(EP &e, bool aeap) const
{
	FT lx, ly, lz, d;
	// calculate approximate lambda values by interval arithmetic
	IT ilx, ily, ilz, id;
	if (!aeap && getIntervalLambda(ilx, ily, ilz, id))
	{
		lx = ilx.sup() + ilx.inf();
		ly = ily.sup() + ily.inf();
		lz = ilz.sup() + ilz.inf();
		d  = id.sup() + id.inf();
		e  = EP(lx / d, ly / d, lz / d);
		return;
	}
	// calculate more accurate lambda values by exact arithmetic
	ET elx, ely, elz, ed;
	getExactLambda(elx, ely, elz, ed);
	lx = OMC::to_double(elx);
	ly = OMC::to_double(ely);
	lz = OMC::to_double(elz);
	d  = OMC::to_double(ed);
	e  = EP(lx / d, ly / d, lz / d);
}

template <typename IT, typename ET>
auto ImplicitPoint3T_TPI<IT, ET>::to_explicit(bool aeap) const -> EP
{
	EP e;
	get_Explicit(e, aeap);
	return e;
}

} // namespace OMC