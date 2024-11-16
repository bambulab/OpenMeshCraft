#pragma once

#include "AABBTree_Triangle.h"

#include "OpenMeshCraft/BVH/AABB/AABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/AABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTree.h"

#include "OpenMeshCraft/BVH/KdTree/KdTraits.h"
#include "OpenMeshCraft/BVH/KdTree/KdTree.h"

#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "OpenMeshCraft/Utils/Exception.h"

#include <memory>

namespace OMC {

#define USE_TRIANGLE_FAST_PROJECTION

/***********************************************/
/* 2. Define minimum set of AABB traits
/***********************************************/

class AABBMinimumTraits_Triangle_NearestSearch
{
public:
	/* Belows are used by AABBTree */

	// Number type
	using NT     = typename APAC::NT;
	// Point type
	using PointT = typename APAC::Point3;
	// Triangle type
#ifdef USE_TRIANGLE_FAST_PROJECTION
	class TriT_ : public APAC::Triangle3,
	              public APAC::FastProjectPoint3::AuxTriangle
	{
	public:
		using PointT       = typename APAC::Point3;
		using BaseTriangle = typename APAC::Triangle3;
		using AuxTriangle  = typename APAC::FastProjectPoint3::AuxTriangle;

	public:
		TriT_(const PointT &v0, const PointT &v1, const PointT &v2)
		  : BaseTriangle(v0, v1, v2)
		  , AuxTriangle(v0, v1, v2)
		{
		}
	};
	using TriT = TriT_;
	// Point projection
	using ProjectPoint3 = typename APAC::FastProjectPoint3;
#else
	using TriT          = typename APAC::Triangle3;
	using ProjectPoint3 = typename APAC::ProjectPoint3;
#endif
	// Attribute type
	using PrimAttrT = index_t;
	// Primitive type
	using PrimT     = PrimitiveWithAttribute<TriT, PrimAttrT>;
	// Primitive reference point
	using PrimReferencePoint =
	  AABB_Tri_ReferencePoint<PrimT, AABB_Tri_ReferencePointType::First>;
	// Calculate bounding box
	using CalcBbox = typename APAC::CalcBoundingBox3;
};

/****************************************************/
/* 3. Automatically deduce the complete AABB traits
/****************************************************/

using AABBTraits_Triangle_NearestSearch =
  AABBAutoDeduceTraits<AABBMinimumTraits_Triangle_NearestSearch>;

/****************************************************/
/* 4. Define the AABB Tree used for nearest search.
/****************************************************/

class SAABBTree_Triangle_NearestSearch
  : public SAABBTree<AABBTraits_Triangle_NearestSearch>
{
public:
	using BaseT  = SAABBTree<AABBTraits_Triangle_NearestSearch>;
	using ThisT  = SAABBTree_Triangle_NearestSearch;
	using Traits = AABBTraits_Triangle_NearestSearch;

	using NT            = typename Traits::NT;
	using PointT        = typename Traits::PointT;
	using TriT          = typename Traits::TriT;
	using PrimAttrT     = typename Traits::PrimAttrT;
	using ProjectPoint3 = typename Traits::ProjectPoint3;
	// Other types will be deduced by AABBTree

public:
	inline void accelerate_nearest_search();

	inline bool best_hint(const PointT               &query,
	                      std::pair<PointT, index_t> &hint) const;

	inline PointT closest_point(const PointT &query) const;

	inline std::pair<PointT, const PrimT *>
	closest_point_and_primitive(const PointT &query) const;

	inline std::pair<PointT, PrimAttrT>
	closest_point_and_primattr(const PointT &query) const;

protected:
	/* Define KdTree used to accelerate closest point search */
	class KdSimpleTraits
	{
	public:
		using NT           = typename Traits::NT;
		using PointT       = typename Traits::PointT;
		using PointAttrT   = index_t;
		using BboxT        = typename Traits::BboxT;
		using ProjectPoint = typename Traits::ProjectPoint3;
	};

	using KdTraits = KdAutoDeduceTraits<KdSimpleTraits>;

	std::unique_ptr<KdTree<KdTraits>> m_kd_tree;

	/* Define traversal traits to find closest point */
	class ProjectionTraits
	{
	public:
		using NT      = typename Traits::NT;
		using PointT  = typename Traits::PointT;
		using PrimT   = typename Traits::PrimT;
		using BboxT   = typename Traits::BboxT;
		using SphereT = typename APAC::Sphere3;

		using DoIntersect = typename APAC::DoIntersect;

#ifdef USE_TRIANGLE_FAST_PROJECTION
		using ProjectPoint = typename APAC::ProjectPoint3;
#else
		using ProjectPoint = typename APAC::ProjectPoint3;
#endif
	};

	using ProjTrav = AABB_ProjectionTraversal<ProjectionTraits>;
};

void SAABBTree_Triangle_NearestSearch::accelerate_nearest_search()
{
	Traits::PrimReferencePoint ref_point;

	std::vector<PointT>  points;
	std::vector<index_t> ids;
	points.reserve(m_primitives.size());
	ids.reserve(m_primitives.size());

	for (index_t i = 0; i < m_primitives.size(); i++)
	{
		points.push_back(ref_point(m_primitives[i]));
		ids.push_back(i);
	}

	m_kd_tree = std::make_unique<KdTree<KdTraits>>();
	m_kd_tree->insert(points, ids);
	m_kd_tree->build();
}

bool SAABBTree_Triangle_NearestSearch::best_hint(
  const PointT &query, std::pair<PointT, index_t> &hint) const
{
	if (m_kd_tree)
	{
		hint = m_kd_tree->search_nearest_point(query);
		return true;
	}
	else if (!m_primitives.empty())
	{
		PrimReferencePoint reference_point;
		hint = std::make_pair<PointT, index_t>(
		  reference_point(*m_primitives.cbegin()), 0);
		return true;
	}
	else
		return false;
}

auto SAABBTree_Triangle_NearestSearch::closest_point(const PointT &query) const
  -> PointT
{
	// Get the best hint
	std::pair<PointT, index_t> hint;
	OMC_THROW_LOGIC_ERROR_IF(
	  !best_hint(query, hint),
	  "Can't find best hint. It may caused by empty primitive.");
	// Traversal the tree
	auto &[hint_point, hint_pid] = hint;
	ProjTrav proj_trav(query, hint_point, m_primitives.data() + hint_pid);
	this->traverse(proj_trav);
	// Return result
	return proj_trav.closest_point();
}

auto SAABBTree_Triangle_NearestSearch::closest_point_and_primitive(
  const PointT &query) const -> std::pair<PointT, const PrimT *>
{
	// Get the best hint
	std::pair<PointT, index_t> hint;
	OMC_THROW_LOGIC_ERROR_IF(
	  !best_hint(query, hint),
	  "Can't find best hint. It may caused by empty primitive.");
	// Traversal the tree
	auto &[hint_point, hint_pid] = hint;
	ProjTrav proj_trav(query, hint_point, m_primitives.data() + hint_pid);
	this->traverse(proj_trav);
	// Return result
	return std::pair<PointT, const PrimT *>(proj_trav.closest_point(),
	                                        proj_trav.closest_primitive());
}

auto SAABBTree_Triangle_NearestSearch::closest_point_and_primattr(
  const PointT &query) const -> std::pair<PointT, PrimAttrT>
{
	// Get the best hint
	std::pair<PointT, index_t> hint;
	OMC_THROW_LOGIC_ERROR_IF(
	  !best_hint(query, hint),
	  "Can't find best hint. It may caused by empty primitive.");
	// Traversal the tree
	auto &[hint_point, hint_pid] = hint;
	ProjTrav proj_trav(query, hint_point, m_primitives.data() + hint_pid);
	this->traverse(proj_trav);
	// Return result
	return std::pair<PointT, PrimAttrT>(
	  proj_trav.closest_point(), proj_trav.closest_primitive()->attribute());
}

#ifdef USE_TRIANGLE_FAST_PROJECTION
	#undef USE_TRIANGLE_FAST_PROJECTION
#endif

} // namespace OMC
