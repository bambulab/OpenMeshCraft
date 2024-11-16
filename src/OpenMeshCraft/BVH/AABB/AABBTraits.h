#pragma once

#include "OpenMeshCraft/Utils/ExtendedTypeTraits.h"
#include "OpenMeshCraft/Utils/IndexDef.h"
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
 * @tparam PrimSplitPred Type of the predicate used to split the primitives.
 */
template <typename BboxT, typename PrimSplitPred>
class AABBSplitPrimitives
{
public: /* Operator *******************************************************/
	/// @brief An operator for static AABB tree, directly split the primitives.
	template <typename PrimsIter>
	size_t operator()(PrimsIter first, PrimsIter beyond, PrimsIter &middle,
	                  const BboxT &box)
	{
		size_t        split_axis = box.longest_axis();
		PrimSplitPred pred(split_axis);
		middle = first + (beyond - first) / 2;
		std::nth_element(first, middle, beyond, pred);
		return split_axis;
	}

	/// @brief An operator for dynamic AABB tree, split the indices of primitives.
	template <typename TreeT, typename IndicesIter>
	size_t operator()(TreeT *tree, IndicesIter first, IndicesIter beyond,
	                  IndicesIter &middle, const BboxT &box)
	{
		size_t        split_axis = box.longest_axis();
		PrimSplitPred pred(split_axis);
		auto          wrap_pred = [&](index_t lhs, index_t rhs)
		{ return pred(tree->primitive(lhs), tree->primitive(rhs)); };

		middle = first + (beyond - first) / 2;
		std::nth_element(first, middle, beyond, wrap_pred);
		return split_axis;
	}
};

template <typename Traits>
class AABBAutoDeduceTraits : public Traits
{
public:
	// ========================================================================
	// Below types must be provided by user

	// Primitive type
	using PrimT              = typename Traits::PrimT;
	// Calculate bounding box
	using CalcBbox           = typename Traits::CalcBbox;
	// Primitive reference point
	using PrimReferencePoint = typename Traits::PrimReferencePoint;

	// ========================================================================
	// Below types can be automatically deduced or explicitly provided by user.
	// We will also check if types are consistent.

	// Bounding box type -------------------------------------------------------
	using DeducedBboxT =
	  remove_cvref_t<std::invoke_result_t<decltype(CalcBbox()), const PrimT &>>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, BboxT, DeducedBboxT, BboxT);
	static_assert(!std::is_void_v<DeducedBboxT>, "Cannot deduce BboxT type.");
	static_assert(std::is_same_v<BboxT, DeducedBboxT>, "Inconsistent BboxT type.");

	// Primitive split predicate ----------------------------------------------
	using DefaultSplitPred = AABBPrimSplitPred<PrimT, PrimReferencePoint>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, PrimSplitPred, DefaultSplitPred,
	                           PrimSplitPred);

	// Primitive split method -------------------------------------------------
	using DefaultSplitPrims = AABBSplitPrimitives<BboxT, PrimSplitPred>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, SplitPrims, DefaultSplitPrims, SplitPrims);
};

} // namespace OMC