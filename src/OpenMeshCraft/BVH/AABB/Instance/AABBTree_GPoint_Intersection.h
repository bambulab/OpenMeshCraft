#pragma once

#include "AABBTree_GPoint.h"

#include "OpenMeshCraft/BVH/AABB/Static/SAABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTree.h"

namespace OMC {

/***********************************************/
/* 2. Define minimum set of AABB traits        */
/***********************************************/

template <typename _GPointPtr, typename _ToEP, typename _CalcBbox>
class SAABBMinimumTraits_GPoint_Intersection
{
public:
	/* Belows are used by AABBTree */

	// Primitive type
	using GPointPtr = _GPointPtr;
	using GPointT   = remove_cvref_t<decltype(*std::declval<GPointPtr>())>;

	// Convert the generic point to explicit point
	using ToEP = _ToEP;
	using EPointT =
	  remove_cvref_t<decltype(std::declval<ToEP>()(*std::declval<GPointPtr>()))>;

	// Attribute type
	using PrimAttrT = index_t;
	// Primitive type
	struct PrimT
	{
		GPointPtr      gptr;
		PrimAttrT      attr;
		// accessors
		GPointPtr      primitive() const { return gptr; }
		PrimAttrT      attribute() const { return attr; }
		// behave like a pointer
		// GPointT       &operator*() { return *gptr; }
		const GPointT &operator*() const { return *gptr; }
	};

	// Calculate bounding box
	using CalcBbox = _CalcBbox;

	// Primitive reference point
	using PrimReferencePoint = AABB_GPoint_ReferencePoint<PrimT, ToEP>;
};

/****************************************************/
/* 3. Automatically deduce the complete AABB traits */
/****************************************************/

template <typename _GPointPtr, typename _ToEP, typename _CalcBbox>
using SAABBTraits_GPoint_Intersection = SAABBAutoDeduceTraits<
  SAABBMinimumTraits_GPoint_Intersection<_GPointPtr, _ToEP, _CalcBbox>>;

/****************************************************/
/* 4. Define the AABB Tree used for intersection.   */
/****************************************************/

template <typename _GPointPtr, typename _ToEP, typename _CalcBbox,
          typename _DoIntersect>
class SAABBTree_GPoint_Intersection
  : public SAABBTree<
      SAABBTraits_GPoint_Intersection<_GPointPtr, _ToEP, _CalcBbox>>
{
public:
	using Traits = SAABBTraits_GPoint_Intersection<_GPointPtr, _ToEP, _CalcBbox>;
	using BaseT  = SAABBTree<Traits>;
	using ThisT =
	  SAABBTree_GPoint_Intersection<_GPointPtr, _ToEP, _CalcBbox, _DoIntersect>;

	using GPointPtr = _GPointPtr;
	using ToEP      = _ToEP;

	using GPointT = typename Traits::GPointT;
	using EPointT = typename Traits::EPointT;
	using PrimT   = typename Traits::PrimT;

public:
	template <typename QPrimT, typename Indices>
	void all_intersections(const QPrimT &query, Indices &results) const
	{
		BoxTrav<QPrimT> box_trav(query);
		this->traverse(box_trav);

		auto &prim_ptrs = box_trav.result();
		results.reserve(prim_ptrs.size());
		for (auto pp : prim_ptrs)
			results.push_back(pp->attribute());
	}

protected:
	template <typename _QPrimT>
	class BoxInterTraits
	{
	public:
		using QPrimT = _QPrimT;

		using PrimT = typename Traits::PrimT;
		using BboxT = typename Traits::BboxT;

		using DoIntersect = _DoIntersect;
		using CalcBbox    = _CalcBbox;
	};

	template <typename QPrimT>
	using BoxTrav = SAABB_BoxInterTraversal<BoxInterTraits<QPrimT>>;
};

} // namespace OMC
