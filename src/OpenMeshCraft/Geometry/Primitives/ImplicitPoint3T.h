#pragma once

#include "ImplicitPoints/GlobalCachedValues.h"

#include "ExplicitPoint3T.h"
#include "GenericPoint3T.h"

#include "OpenMeshCraft/Geometry/Utils.h"
#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"

#include <memory>

namespace OMC {

/**
 * @brief Implicit exact 3D point defined by the intersection of two lines.
 * Two lines (segments) are defined by two endpoints respectively.
 *
 * The point has a homogeneous representation (lx, ly, lz, d), which defines the
 * coordinates of the point as (x, y, z) = (lx, ly, lz) / d.
 *
 * The homogeneous representation avoids the division operation, which enables
 * efficient exact arithmetic operations.
 */
template <typename IT_, typename ET_>
class ImplicitPoint3T_SSI : public GenericPoint3T<IT_, ET_>
{
public: /* Types *************************************************************/
	using FT = double; ///< floating point type
	using IT = IT_;    ///< interval type
	using ET = ET_;    ///< exact type

	using EP = ExplicitPoint3T<IT, ET>;
	using IP = ImplicitPoint3T_SSI<IT, ET>;
	using GP = GenericPoint3T<IT, ET>;

	/// An enum class to indicate the type of the point.
	using PointType = typename GP::PointType;

	/// A class to store cached values for one point.
	using GCV = GlobalCachedValues<OnePointCachedValues3<IT, ET>>;

public: /* Constructors ******************************************************/
	/// @brief default constructor
	ImplicitPoint3T_SSI() noexcept;

	/**
	 * @brief init SSI point with segment(a, b) and segment(p, q)
	 * @param _plane The 2D plane where the projection of two segments are not
	 * degenerate.
	 */
	ImplicitPoint3T_SSI(const EP &_a, const EP &_b, const EP &_p, const EP &_q,
	                    int _plane) noexcept;

	~ImplicitPoint3T_SSI() noexcept;

	ImplicitPoint3T_SSI(const IP &rhs) noexcept;
	ImplicitPoint3T_SSI(IP &&rhs) noexcept;

	IP &operator=(const IP &rhs);
	IP &operator=(IP &&rhs);

public: /* Members ***********************************************************/
	const EP &A() const { return *ia; }
	const EP &B() const { return *ib; }
	const EP &P() const { return *ip; }
	const EP &Q() const { return *iq; }

public: /* Lambdas ***********************************************************/
	/**
	 * @brief Get the Lambda values represented by interval numbers.
	 * @return true if the sign of d is reliable.
	 */
	bool getIntervalLambda(IT &lx, IT &ly, IT &lz, IT &d) const;

	/**
	 * @brief Get the Lambda values represented by exact numbers.
	 */
	void getExactLambda(ET &lx, ET &ly, ET &lz, ET &d) const;

	/**
	 * @brief Get the Lambda values represented by expansion numbers.
	 */
	void getExpansionLambda(FT **lx, int &lx_len, FT **ly, int &ly_len, FT **lz,
	                        int &lz_len, FT **d, int &d_len) const;

public: /* convert other points **********************************************/
	/**
	 * @brief get the explicit reprensentation of the point.
	 * @param e the explicit point to store the result.
	 * @param aeap abbreviates "as exact as possible". If true, the exact
	 * value is calculated and rounded to the nearest floating point number.
	 */
	void get_explicit(EP &e, bool aeap = false) const;

	/**
	 * @brief get the explicit reprensentation of the point.
	 * @param aeap abbreviates "as exact as possible". If true, the exact
	 * value is calculated and rounded to the nearest floating point number.
	 * @return the explicit point.
	 */
	EP to_explicit(bool aeap = false) const;

public: /* Cache *************************************************************/
	static GCV &gcv() { return global_cached_values; }

private:
	const EP *ia, *ib; ///< The first segment AB
	const EP *ip, *iq; ///< The second segment PQ

	/// The 2D plane where two segments are not degenerate.
	/// Its value means the index of max component of plane's normal.
	/// plane == 0 -> YZ plane;
	/// plane == 1 -> ZX plane;
	/// plane == 2 -> XY plane.
	int plane;

#ifdef OMC_CACHE_DF
	IT m_lx, m_ly, m_lz, m_d;
#endif

	/// global cached lambda values
	static GCV global_cached_values;
};

/**
 * @brief Implicit point defined by the intersection of a line and a plane.
 * The line is defined by a segment with two endpoints, and the plane is defined
 * by a triangle with three points.
 *
 * The point has a homogeneous representation (lx, ly, lz, d), which defines the
 * coordinates of the point as (x, y, z) = (lx, ly, lz) / d.
 *
 * The homogeneous representation avoids the division operation, which enables
 * efficient exact arithmetic operations.
 */
template <typename IT_, typename ET_>
class ImplicitPoint3T_LPI : public GenericPoint3T<IT_, ET_>
{
public: /* Types *************************************************************/
	using FT = double; ///< floating point type
	using IT = IT_;    ///< interval type
	using ET = ET_;    ///< exact type

	using EP = ExplicitPoint3T<IT, ET>;
	using IP = ImplicitPoint3T_LPI<IT, ET>;
	using GP = GenericPoint3T<IT, ET>;

	/// An enum class to indicate the type of the point.
	using PointType = typename GP::PointType;

	/// A class to store cached values for one point.
	using GCV = GlobalCachedValues<OnePointCachedValues3<IT, ET>>;

public: /* Constructors ******************************************************/
	/// @brief default constructor
	ImplicitPoint3T_LPI() noexcept;

	/// @brief init LPI point with line(p,q) and plane(r,s,t)
	ImplicitPoint3T_LPI(const EP &_p, const EP &_q, const EP &_r, const EP &_s,
	                    const EP &_t) noexcept;

	~ImplicitPoint3T_LPI() noexcept;

	ImplicitPoint3T_LPI(const IP &rhs) noexcept;
	ImplicitPoint3T_LPI(IP &&rhs) noexcept;

	IP &operator=(const IP &rhs);
	IP &operator=(IP &&rhs);

public: /* Members ***********************************************************/
	const EP &P() const { return *ip; }
	const EP &Q() const { return *iq; }
	const EP &R() const { return *ir; }
	const EP &S() const { return *is; }
	const EP &T() const { return *it; }

public: /* Lambdas ***********************************************************/
	/**
	 * @brief Get the Lambda values represented by interval numbers.
	 * @return true if the sign of d is reliable.
	 */
	bool getIntervalLambda(IT &lx, IT &ly, IT &lz, IT &d) const;

	/**
	 * @brief Get the Lambda values represented by exact numbers.
	 */
	void getExactLambda(ET &lx, ET &ly, ET &lz, ET &d) const;

	/**
	 * @brief Get the Lambda values represented by expansion numbers.
	 */
	void getExpansionLambda(FT **lx, int &lx_len, FT **ly, int &ly_len, FT **lz,
	                        int &lz_len, FT **d, int &d_len) const;

public: /* convert other points **********************************************/
	/**
	 * @brief get the explicit reprensentation of the point.
	 * @param e the explicit point to store the result.
	 * @param aeap abbreviates "as exact as possible". If true, the exact
	 * value is calculated and rounded to the nearest floating point number.
	 */
	void get_explicit(EP &e, bool aeap = false) const;

	/**
	 * @brief get the explicit reprensentation of the point.
	 * @param aeap abbreviates "as exact as possible". If true, the exact
	 * value is calculated and rounded to the nearest floating point number.
	 * @return the explicit point.
	 */
	EP to_explicit(bool aeap = false) const;

public: /* Cache *************************************************************/
	static GCV &gcv() { return global_cached_values; }

private:
	const EP *ip, *iq;      ///< The line PQ
	const EP *ir, *is, *it; ///< The plane RST

#ifdef OMC_CACHE_DF
	IT m_lx, m_ly, m_lz, m_d;
#endif

	/// global cached lambda values
	static GCV global_cached_values;
};

/**
 * @brief Implicit exact 3D point defined by the intersection of three planes.
 * Three planes (triangles) are defined by three endpoints respectively.
 *
 * The point has a homogeneous representation (lx, ly, lz, d), which defines the
 * coordinates of the point as (x, y, z) = (lx, ly, lz) / d.
 *
 * The homogeneous representation avoids the division operation, which enables
 * efficient exact arithmetic operations.
 */
template <typename IT_, typename ET_>
class ImplicitPoint3T_TPI : public GenericPoint3T<IT_, ET_>
{
public: /* Types *************************************************************/
	using FT = double; ///< floating point type
	using IT = IT_;    ///< interval type
	using ET = ET_;    ///< exact type

	using EP = ExplicitPoint3T<IT, ET>;
	using IP = ImplicitPoint3T_TPI<IT, ET>;
	using GP = GenericPoint3T<IT, ET>;

	/// An enum class to indicate the type of the point.
	using PointType = typename GP::PointType;

	/// A class to store cached values for one point.
	using GCV = GlobalCachedValues<OnePointCachedValues3<IT, ET>>;

public: /* Constructors ******************************************************/
	/// @brief default constructor
	ImplicitPoint3T_TPI() noexcept;

	/// @brief init TPI point with planes (v1,v2,v3), (w1,w2,w3), (u1,u2,u3).
	ImplicitPoint3T_TPI(const EP &_v1, const EP &_v2, const EP &_v3,
	                    const EP &_w1, const EP &_w2, const EP &_w3,
	                    const EP &_u1, const EP &_u2, const EP &_u3) noexcept;

	~ImplicitPoint3T_TPI() noexcept;

	ImplicitPoint3T_TPI(const IP &rhs) noexcept;
	ImplicitPoint3T_TPI(IP &&rhs) noexcept;

	IP &operator=(const IP &rhs);
	IP &operator=(IP &&rhs);

public: /* Members ***********************************************************/
	const EP &V1() const { return *iv1; }
	const EP &V2() const { return *iv2; }
	const EP &V3() const { return *iv3; }
	const EP &W1() const { return *iw1; }
	const EP &W2() const { return *iw2; }
	const EP &W3() const { return *iw3; }
	const EP &U1() const { return *iu1; }
	const EP &U2() const { return *iu2; }
	const EP &U3() const { return *iu3; }

public: /* Lambdas ***********************************************************/
	/**
	 * @brief Get the Lambda values represented by interval numbers.
	 * @return true if the sign of d is reliable.
	 */
	bool getIntervalLambda(IT &lx, IT &ly, IT &lz, IT &d) const;

	/**
	 * @brief Get the Lambda values represented by exact numbers.
	 */
	void getExactLambda(ET &lx, ET &ly, ET &lz, ET &d) const;

	/**
	 * @brief Get the Lambda values represented by expansion numbers.
	 */
	void getExpansionLambda(FT **lx, int &lx_len, FT **ly, int &ly_len, FT **lz,
	                        int &lz_len, FT **d, int &d_len) const;

public: /* functions about types *********************************************/
	/**
	 * @brief get the explicit reprensentation of the point.
	 * @param e the explicit point to store the result.
	 * @param aeap abbreviates "as exact as possible". If true, the exact
	 * value is calculated and rounded to the nearest floating point number.
	 */
	void get_explicit(EP &e, bool aeap = false) const;

	/**
	 * @brief get the explicit reprensentation of the point.
	 * @param aeap abbreviates "as exact as possible". If true, the exact
	 * value is calculated and rounded to the nearest floating point number.
	 * @return the explicit point.
	 */
	EP to_explicit(bool aeap = false) const;

public: /* Cache *************************************************************/
	static GCV &gcv() { return global_cached_values; }

private:
	const EP *iv1, *iv2, *iv3; ///< Plane 1
	const EP *iw1, *iw2, *iw3; ///< Plane 2
	const EP *iu1, *iu2, *iu3; ///< Plane 3

#ifdef OMC_CACHE_DF
	IT m_lx, m_ly, m_lz, m_d;
#endif

	/// global cached lambda values
	static GCV global_cached_values;
};

// static member variables
template <typename IT_, typename ET_>
typename ImplicitPoint3T_SSI<IT_, ET_>::GCV
  ImplicitPoint3T_SSI<IT_, ET_>::global_cached_values =
    ImplicitPoint3T_SSI<IT_, ET_>::GCV();

template <typename IT_, typename ET_>
typename ImplicitPoint3T_LPI<IT_, ET_>::GCV
  ImplicitPoint3T_LPI<IT_, ET_>::global_cached_values =
    ImplicitPoint3T_LPI<IT_, ET_>::GCV();

template <typename IT_, typename ET_>
typename ImplicitPoint3T_TPI<IT_, ET_>::GCV
  ImplicitPoint3T_TPI<IT_, ET_>::global_cached_values =
    ImplicitPoint3T_TPI<IT_, ET_>::GCV();

inline void normalizeLambda3D(double *lx, int &lxl, double *ly, int &lyl,
                              double *lz, int &lzl, double *d, int &dl)
{
	expansionObject o;
	double          maxd, maxsd, ad, aad;
	maxsd = o.To_Double(lxl, lx);
	maxd  = fabs(maxsd);
	if ((aad = fabs((ad = o.To_Double(lyl, ly)))) > maxd)
	{
		maxd  = aad;
		maxsd = ad;
	}
	if ((aad = fabs((ad = o.To_Double(lzl, lz)))) > maxd)
	{
		maxd  = aad;
		maxsd = ad;
	}
	if ((aad = fabs((ad = o.To_Double(dl, d)))) > maxd)
	{
		maxd  = aad;
		maxsd = ad;
	}

	int e;
	frexp(maxsd, &e);
	const double m = ldexp(2, -e);

	o.ExactScale(lxl, lx, m);
	o.ExactScale(lyl, ly, m);
	o.ExactScale(lzl, lz, m);
	o.ExactScale(dl, d, m);
}

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ImplicitPoints/ImplicitPoint3T_SSI.inl"
	#include "ImplicitPoints/ImplicitPoint3T_LPI.inl"
	#include "ImplicitPoints/ImplicitPoint3T_TPI.inl"
#endif