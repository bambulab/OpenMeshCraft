#pragma once

#include "OpenMeshCraft/Utils/ExtendedTypeTraits.h"
#include "OpenMeshCraft/Utils/SFINAE.h"

#include <algorithm>
#include <type_traits>
#include <vector>

namespace OMC {

/**
 * @brief Compare two primitives at specified axis.
 * @tparam PrimT primitive type.
 * @tparam PrimReferencePoint primitive reference point strategy.
 */
template <typename PrimT, typename PrimReferencePoint>
class AABBPrimSplitPred
{
public: /* Constructor ****************************************************/
	AABBPrimSplitPred()
	  : m_split_axis(0)
	{
	}
	AABBPrimSplitPred(size_t split_axis)
	  : m_split_axis(split_axis)
	{
	}

public: /* Operator *******************************************************/
	/// @brief Compare the reference point of two primitives at specified axis.
	bool operator()(const PrimT &lhs, const PrimT &rhs)
	{
		return reference_point(lhs)[m_split_axis] <
		       reference_point(rhs)[m_split_axis];
	}

private:
	size_t             m_split_axis;
	PrimReferencePoint reference_point;
};

/**
 * @class AABBSplitPrimitives
 * @brief A class template for splitting primitives in an axis-aligned bounding
 * box (AABB).
 *
 * This class template provides a mechanism to split a range of primitives based
 * on a specified splitting predicate and the longest axis of the bounding box.
 *
 * @tparam BboxT Type of the bounding box.
 * @tparam PrimsIter Type of the iterator used to traverse the primitives.
 * @tparam PrimSplitPred Type of the predicate used to split the primitives.
 */
template <typename BboxT, typename PrimsIter, typename PrimSplitPred>
class AABBSplitPrimitives
{
public: /* Operator *******************************************************/
	size_t operator()(PrimsIter first, PrimsIter beyond, PrimsIter &middle,
	                  const BboxT &box)
	{
		size_t        split_axis = box.longest_axis();
		PrimSplitPred pred(split_axis);
		middle = first + (beyond - first) / 2;
		std::nth_element(first, middle, beyond, pred);
		return split_axis;
	}
};

template <typename Traits>
class AABBAutoDeduceTraits : public Traits
{
public:
	// Below types must be provided by user

	// Primitive type
	using PrimT              = typename Traits::PrimT;
	// Primitive reference point
	using PrimReferencePoint = typename Traits::PrimReferencePoint;
	// Calculate bounding box
	using CalcBbox           = typename Traits::CalcBbox;

	// Below types can be automatically deduced or explicitly provided by user.
	// We will also check if types are consistent.

	// Primitives
	GET_TYPE_OTHERWISE_DEFAULT(Traits, Prims, std::vector<PrimT>, Prims);
	// Primitives iterator
	GET_TYPE_OTHERWISE_DEFAULT(Traits, PrimsIter, typename Prims::iterator,
	                           PrimsIter);
	// Primitive split predicate
	GET_TYPE_OTHERWISE_DEFAULT(
	  Traits, PrimSplitPred,
	  decltype(AABBPrimSplitPred<PrimT, PrimReferencePoint>()), PrimSplitPred);

	// Point type
	GET_TYPE_OTHERWISE_VOID(PrimT, PointT, DeducedPointT);
	GET_TYPE_OTHERWISE_DEFAULT(Traits, PointT, DeducedPointT, PointT);
	static_assert(!std::is_void_v<PointT>,
	              "PointT is not provided and can't be deduced.");
	static_assert(std::is_void_v<DeducedPointT> ||
	                std::is_same_v<PointT, DeducedPointT>,
	              "Deduced point type from PrimT and provided point type by "
	              "user are different.");
	// Number type
	GET_TYPE_OTHERWISE_VOID(PointT, NT, DeducedNT);
	GET_TYPE_OTHERWISE_DEFAULT(Traits, NT, DeducedNT, NT);
	static_assert(!std::is_void_v<NT>,
	              "Number type is not provided and can't be deduced.");
	static_assert(std::is_void_v<DeducedNT> || std::is_same_v<NT, DeducedNT>,
	              "Deduced number type from PointT and provided number type by "
	              "user are different.");
	// Bounding box type, deduced by CalcBbox or provided by user
	using DeducedBboxT =
	  remove_cvref_t<std::invoke_result_t<decltype(CalcBbox()), const PrimT &>>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, BboxT, DeducedBboxT, BboxT);
	static_assert(std::is_same_v<BboxT, DeducedBboxT>,
	              "Deduced box type from CalcBbox and provided box type by user "
	              "are different.");
	// Primitive split
	using DefaultSplitPrims =
	  AABBSplitPrimitives<BboxT, PrimsIter, PrimSplitPred>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, SplitPrims, DefaultSplitPrims, SplitPrims);
};

} // namespace OMC