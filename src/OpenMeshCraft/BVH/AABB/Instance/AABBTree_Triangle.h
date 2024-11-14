#pragma once

#include "OpenMeshCraft/Utils/ExtendedTypeTraits.h"

namespace OMC {

/*************************************************/
/* 1. Define the reference point of the triangle */
/*************************************************/

/**
 * @brief The type of reference point for triangle.
 */
enum class AABB_Tri_ReferencePointType
{
	First,   /// The first point `v0` of the triangle.
	Centroid /// The centroid of the triangle.
};

/**
 * @class AABB_Triangle_ReferencePoint
 * @brief A class template to compute a reference point for a triangle based on
 * the specified reference point type.
 *
 * @tparam TriT The type of the triangle.
 * @tparam RefPntType The type of the reference point.
 */
template <typename TriT, AABB_Tri_ReferencePointType RefPntType>
class AABB_Tri_ReferencePoint
{
public:
	using NT     = typename TriT::NT;
	using PointT = remove_cvref_t<decltype(std::declval<TriT>().v0())>;

public:
	PointT operator()(const TriT &tri)
	{
		if constexpr (RefPntType == AABB_Tri_ReferencePointType::First)
		{
			return tri.v0();
		}
		else if constexpr (RefPntType == AABB_Tri_ReferencePointType::Centroid)
		{
			return (tri.v0() + tri.v1() + tri.v2()) / NT(3.);
		}
	}
};

} // namespace OMC