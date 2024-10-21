#pragma once

#include "ImplicitPoints/GlobalCachedValues.h"

#include "ExplicitPoint2T.h"
#include "GenericPoint2T.h"

#include "OpenMeshCraft/Geometry/Utils.h"

namespace OMC {

/**
 * @brief Implicit exact 2D point defined by the intersection of two lines.
 * Two lines (segments) are defined by two endpoints respectively.
 *
 * The point has a homogeneous representation (lx, ly, d), which defines the
 * coordinates of the point as (x, y) = (lx, ly) / d.
 *
 * The homogeneous representation avoids the division operation, which enables
 * efficient exact arithmetic operations.
 */
template <typename IT_, typename ET_>
class ImplicitPoint2T_SSI : public GenericPoint2T<IT_, ET_>
{
public: /* types *************************************************************/
	using FT = double; ///< floating point type
	using IT = IT_;    ///< interval type
	using ET = ET_;    ///< exact type

	using EP = ExplicitPoint2T<IT, ET>;
	using IP = ImplicitPoint2T_SSI<IT, ET>;
	using GP = GenericPoint2T<IT, ET>;

	/// An enum class to indicate the type of the point.
	using PointType = typename GP::PointType;

	/// A class to store cached values for one point.
	using GCV = GlobalCachedValues<OnePointCachedValues2<IT, ET>>;

public: /* Constructors ******************************************************/
	/// @brief default constructor
	ImplicitPoint2T_SSI() noexcept;

	/// @brief init SSI point with segment(a, b) and segment(c, d)
	ImplicitPoint2T_SSI(const EP &a, const EP &b, const EP &c,
	                    const EP &d) noexcept;

	~ImplicitPoint2T_SSI() noexcept {}

	ImplicitPoint2T_SSI(const IP &rhs) noexcept;
	ImplicitPoint2T_SSI(IP &&rhs) noexcept;

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
	bool getIntervalLambda(IT &lx, IT &ly, IT &d) const;

	/**
	 * @brief Get the Lambda values represented by exact numbers.
	 */
	void getExactLambda(ET &lx, ET &ly, ET &d) const;

	/**
	 * @brief Get the Lambda values represented by expansion numbers.
	 */
	void getExpansionLambda(FT **lx, int &lx_len, FT **ly, int &ly_len, FT **d,
	                        int &d_len) const;

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
	const EP *ia, *ib; ///< the first segment(a, b)
	const EP *ip, *iq; ///< the second segment(p, q)

	/// global cached lambda values
	static GCV global_cached_values;
};

/// static member variables
template <typename IT_, typename ET_>
typename ImplicitPoint2T_SSI<IT_, ET_>::GCV
  ImplicitPoint2T_SSI<IT_, ET_>::global_cached_values =
    ImplicitPoint2T_SSI<IT_, ET_>::GCV();

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ImplicitPoints/ImplicitPoint2T_SSI.inl"
#endif