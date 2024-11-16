#pragma once

#include "OpenMeshCraft/Geometry/Primitives/ExplicitPoint2T.h"
#include "OpenMeshCraft/Geometry/Primitives/ExplicitPoint3T.h"
#include "OpenMeshCraft/Geometry/Primitives/GenericPoint2T.h"
#include "OpenMeshCraft/Geometry/Primitives/GenericPoint3T.h"

#include <type_traits>

namespace OMC {

/**
 * @brief Calculate lower/upper bound for various types of point
 * and output the result to an explicit point type.
 * @tparam GPointT Generic point type (e.g., implicit point type)
 * @tparam EPointT Explicit point type (storing coordinates explicitly)
 */
template <typename GPointT, typename EPointT>
class PointBound
{
public:
	template <typename GPT,
	          typename = std::enable_if_t<std::is_same_v<GPT, GPointT> &&
	                                      std::is_same_v<GPT, EPointT>>>
	const EPointT &lower_bound(const GPointT &gp)
	{
		return gp;
	}

	template <typename GPT,
	          typename = std::enable_if_t<std::is_same_v<GPT, GPointT> &&
	                                      std::is_same_v<GPT, EPointT>>>
	const EPointT &upper_bound(const GPointT &gp)
	{
		return gp;
	}

	template <typename GPT,
	          typename = std::enable_if_t<std::is_same_v<GPT, GPointT> &&
	                                      std::is_same_v<GPT, EPointT>>>
	std::pair<EPointT, EPointT> both_bounds(const GPointT &gp)
	{
		return std::make_pair(gp, gp);
	}
};

template <typename IT, typename ET>
class PointBound<GenericPoint2T<IT, ET>, ExplicitPoint2T<IT, ET>>
{
public:
	using EP = ExplicitPoint2T<IT, ET>;
	using GP = GenericPoint2T<IT, ET>;

	/**
	 * @brief Calculate the lower bound of a generic point.
	 * @param apap as precise as possible
	 */
	EP lower_bound(const GP &gp, bool apap = false)
	{
		IT ix, iy, id;
		ET ex, ey, ed;
		if (gp.is_explicit())
		{
			return gp.to_explicit();
		}
		else if (!apap && gp.getIntervalLambda(ix, iy, id))
		{
			IT x = ix / id, y = iy / id;
			return EP(x.inf(), y.inf());
		}
		else
		{
			gp.getExactLambda(ex, ey, ed);
			ET x = ex / ed, y = ey / ed;
			return EP(to_interval(x).first, to_interval(y).first);
		}
	}

	/**
	 * @brief Calculate the upper bound of a generic point.
	 * @param apap as precise as possible
	 */
	EP upper_bound(const GP &gp, bool apap = false)
	{
		IT ix, iy, id;
		ET ex, ey, ed;
		if (gp.is_explicit())
		{
			return gp.to_explicit();
		}
		else if (!apap && gp.getIntervalLambda(ix, iy, id))
		{
			IT x = ix / id, y = iy / id;
			return EP(x.sup(), y.sup());
		}
		else
		{
			gp.getExactLambda(ex, ey, ed);
			ET x = ex / ed, y = ey / ed;
			return EP(to_interval(x).second, to_interval(y).second);
		}
	}

	/**
	 * @brief Calculate the both lower and upper bounds of a generic point.
	 * @param apap as precise as possible
	 * @return A pair of (first) lower and (second) upper bounds.
	 */
	std::pair<EP, EP> both_bounds(const GP &gp, bool apap = false)
	{
		IT ix, iy, id;
		ET ex, ey, ed;
		if (gp.is_explicit())
		{
			return std::make_pair(gp.to_explicit(), gp.to_explicit());
		}
		else if (!apap && gp.getIntervalLambda(ix, iy, id))
		{
			IT x = ix / id, y = iy / id;
			return std::make_pair(EP(x.inf(), y.inf()), EP(x.sup(), y.sup()));
		}
		else
		{
			gp.getExactLambda(ex, ey, ed);
			ET x = ex / ed, y = ey / ed;

			std::pair<double, double> xi = to_interval(x), yi = to_interval(y);
			return std::make_pair(EP(xi.first, yi.first), EP(xi.second, yi.second));
		}
	}
};

template <typename IT, typename ET>
class PointBound<GenericPoint3T<IT, ET>, ExplicitPoint3T<IT, ET>>
{
public:
	using EP = ExplicitPoint3T<IT, ET>;
	using GP = GenericPoint3T<IT, ET>;

	/**
	 * @brief Calculate the lower bound of a generic point.
	 * @param apap as precise as possible
	 */
	EP lower_bound(const GP &gp, bool apap = false)
	{
		IT ix, iy, iz, id;
		ET ex, ey, ez, ed;
		if (gp.is_explicit())
		{
			return gp.to_explicit();
		}
		else if (!apap && gp.getIntervalLambda(ix, iy, iz, id))
		{
			IT x = ix / id, y = iy / id, z = iz / id;
			return EP(x.inf(), y.inf(), z.inf());
		}
		else
		{
			gp.getExactLambda(ex, ey, ez, ed);
			ET x = ex / ed, y = ey / ed, z = ez / ed;
			return EP(to_interval(x).first, to_interval(y).first,
			          to_interval(z).first);
		}
	}

	/**
	 * @brief Calculate the upper bound of a generic point.
	 * @param apap as precise as possible
	 */
	EP upper_bound(const GP &gp, bool apap = false)
	{
		IT ix, iy, iz, id;
		ET ex, ey, ez, ed;
		if (gp.is_explicit())
		{
			return gp.to_explicit();
		}
		else if (!apap && gp.getIntervalLambda(ix, iy, iz, id))
		{
			IT x = ix / id, y = iy / id, z = iz / id;
			return EP(x.sup(), y.sup(), z.sup());
		}
		else
		{
			gp.getExactLambda(ex, ey, ez, ed);
			ET x = ex / ed, y = ey / ed, z = ez / ed;
			return EP(to_interval(x).second, to_interval(y).second,
			          to_interval(z).second);
		}
	}

	/**
	 * @brief Calculate the both lower and upper bounds of a generic point.
	 * @param apap as precise as possible
	 * @return A pair of (first) lower and (second) upper bounds.
	 */
	std::pair<EP, EP> both_bounds(const GP &gp, bool apap = false)
	{
		IT ix, iy, iz, id;
		ET ex, ey, ez, ed;
		if (gp.is_explicit())
		{
			return std::make_pair(gp.to_explicit(), gp.to_explicit());
		}
		else if (!apap && gp.getIntervalLambda(ix, iy, iz, id))
		{
			IT x = ix / id, y = iy / id, z = iz / id;
			return std::make_pair(EP(x.inf(), y.inf(), z.inf()),
			                      EP(x.sup(), y.sup(), z.sup()));
		}
		else
		{
			gp.getExactLambda(ex, ey, ez, ed);
			ET x = ex / ed, y = ey / ed, z = ez / ed;

			std::pair<double, double> xi = to_interval(x), yi = to_interval(y),
			                          zi = to_interval(z);
			return std::make_pair(EP(xi.first, yi.first, zi.first),
			                      EP(xi.second, yi.second, zi.second));
		}
	}
};

} // namespace OMC