#pragma once

#include "AABBTree_Triangle.h"

#include "OpenMeshCraft/BVH/AABB/Static/SAABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTree.h"

#include "OpenMeshCraft/Geometry/Primitives/PrimitiveWithAttribute.h"

namespace OMC {

/***********************************************/
/* 2. Define minimum set of AABB traits        */
/***********************************************/

template <typename Kernel>
class SAABBMinimumTraits_Triangle_Intersection
{
public:
	/* Belows are used by AABBTree */

	using K    = Kernel;
	using TriT = typename K::Triangle3;

	// Attribute type
	using PrimAttrT = index_t;
	// Primitive type
	using PrimT     = PrimitiveWithAttribute<TriT, PrimAttrT>;

	// Calculate bounding box
	using CalcBbox = typename K::CalcBoundingBox3;

	// Primitive reference point
	using PrimReferencePoint =
	  AABB_Tri_ReferencePoint<PrimT, AABB_Tri_ReferencePointType::First>;
};

/****************************************************/
/* 3. Automatically deduce the complete AABB traits */
/****************************************************/

template <typename Kernel>
using SAABBTraits_Triangle_Intersection =
  SAABBAutoDeduceTraits<SAABBMinimumTraits_Triangle_Intersection<Kernel>>;

/****************************************************/
/* 4. Define the AABB Tree used for intersection.   */
/****************************************************/

template <typename Kernel>
class SAABBTree_Triangle_Intersection
  : public SAABBTree<SAABBTraits_Triangle_Intersection<Kernel>>
{
public:
	using K = Kernel;

	using BaseT  = SAABBTree<SAABBTraits_Triangle_Intersection<K>>;
	using ThisT  = SAABBTree_Triangle_Intersection<K>;
	using Traits = SAABBTraits_Triangle_Intersection<K>;

	using TriT      = typename Traits::TriT;
	using PrimT     = typename Traits::PrimT;
	using PrimAttrT = typename Traits::PrimAttrT;

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

		using DoIntersect = typename K::DoIntersect;
		using CalcBbox    = typename Traits::CalcBbox;
	};

	template <typename QPrimT>
	using BoxTrav = SAABB_BoxInterTraversal<BoxInterTraits<QPrimT>>;
};

} // namespace OMC
