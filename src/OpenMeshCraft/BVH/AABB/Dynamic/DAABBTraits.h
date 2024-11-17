#pragma once

#include "OpenMeshCraft/Utils/Exception.h"
#include "OpenMeshCraft/Utils/ExtendedTypeTraits.h"
#include "OpenMeshCraft/Utils/IndexDef.h"
#include "OpenMeshCraft/Utils/SFINAE.h"

#include <algorithm>
#include <type_traits>
#include <vector>

namespace OMC {

/**
 * @class DAABBPrimSplitPred
 * @brief Compare two primitives at specified axis.
 * @tparam PrimT primitive type.
 * @tparam PrimReferencePoint primitive reference point strategy.
 */
template <typename PrimT, typename PrimReferencePoint>
class DAABBPrimSplitPred
{
public: /* Constructor ****************************************************/
	DAABBPrimSplitPred()
	  : m_split_axis(0)
	{
	}
	DAABBPrimSplitPred(size_t split_axis)
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
 * @class DAABBSplitPrimitives
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
class DAABBSplitPrimitives
{
public: /* Operator *******************************************************/
	/// @brief Split the indices of primitives.
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

class DAABBDenseIndexMap
{
public:
	std::vector<index_t> map;

public:
	index_t size() const { return map.size(); }
	bool    empty() const { return map.empty(); }

	void reserve(size_t size) { map.reserve(size); }
	void resize(size_t size) { map.resize(size); }
	void clear() { map.clear(); }

	index_t &operator[](size_t idx)
	{
		if (idx >= map.size())
			map.resize(idx + 1, InvalidIndex);
		return map[idx];
	}

	index_t &at(size_t idx)
	{
		OMC_EXPENSIVE_ASSERT(idx < map.size(), "Index out of range.");
		return map[idx];
	}
	index_t at(size_t idx) const
	{
		OMC_EXPENSIVE_ASSERT(idx < map.size(), "Index out of range.");
		return map[idx];
	}

	size_t erase(index_t idx)
	{
		OMC_EXPENSIVE_ASSERT(idx < map.size(), "Index out of range.");
		index_t old = map[idx];
		map[idx] = InvalidIndex;
		return is_valid_idx(old);
	}
};

template <typename Traits>
class DAABBAutoDeduceTraits : public Traits
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
	static_assert(std::is_same_v<BboxT, DeducedBboxT>,
	              "Inconsistent BboxT type.");

	// Primitive split predicate ----------------------------------------------
	using DefaultSplitPred = DAABBPrimSplitPred<PrimT, PrimReferencePoint>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, PrimSplitPred, DefaultSplitPred,
	                           PrimSplitPred);

	// Primitive split method -------------------------------------------------
	using DefaultSplitPrims = DAABBSplitPrimitives<BboxT, PrimSplitPred>;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, SplitPrims, DefaultSplitPrims, SplitPrims);

	// Store indexed primitive -------------------------------------------------
	using DefaultIndexMap = DAABBDenseIndexMap;
	GET_TYPE_OTHERWISE_DEFAULT(Traits, IndexMap, DefaultIndexMap, IndexMap);
};

} // namespace OMC