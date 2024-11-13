#pragma once

#include "AABBTree.h"

#include "OpenMeshCraft/Utils/SFINAE.h"

namespace OMC {

template <typename Traits>
class AABB_TraversalTraits
{
public: /* Types ************************************************************/
	using NT    = typename Traits::NT;
	using PrimT = typename Traits::PrimT;
	using BboxT = typename Traits::BboxT;

	AABB_TraversalTraits() = default;

public: /* Interfaces *******************************************************/
	/**
	 * @brief Checks if there is an intersection with the given primitive.
	 *
	 * `intersection` can be reinterpreted as other operations, such as
	 * projection, intersection, etc.
	 *
	 * @param prim The primitive to check for intersection.
	 * @return true if there is an intersection, false otherwise.
	 */
	virtual bool intersection(const PrimT &prim) = 0;

	/**
	 * @brief Determine if an intersection occurs with the given bounding box.
	 *
	 * `intersection` can be reinterpreted as other operations, such as
	 * projection, intersection, etc.
	 *
	 * @param bbox The bounding box to check for intersection.
	 * @return true if an intersection occurs, false otherwise.
	 */
	virtual bool do_inter(const BboxT &bbox) const = 0;
};

template <typename Traits>
class AABB_ProjectionTraversal : public AABB_TraversalTraits<Traits>
{
public: /* Types ************************************************************/
	using NT      = typename Traits::NT;
	using PointT  = typename Traits::PointT;
	using PrimT   = typename Traits::PrimT;
	using BboxT   = typename Traits::BboxT;
	using SphereT = typename Traits::SphereT;

	using DoIntersect  = typename Traits::DoIntersect;
	using ProjectPoint = typename Traits::ProjectPoint;

	using PrimCPtr = const PrimT *;

public: /* Constructor ******************************************************/
	/**
	 * @brief Constructs an AABB_ProjectionTraversal object.
	 *
	 * @param query The query point used for the traversal.
	 * @param hint A hint point to optimize the traversal.
	 * @param hint_prim A pointer to the primitive associated with the hint point.
	 */
	AABB_ProjectionTraversal(const PointT &query, const PointT &hint,
	                         PrimCPtr hint_prim);

public: /* Inherited Interfaces *********************************************/
	bool intersection(const PrimT &prim) override;

	bool do_inter(const BboxT &bbox) const override;

public: /* Interfaces *******************************************************/
	const PointT &closest_point() const { return m_closest_point; }
	PrimCPtr      closest_primitive() const { return m_closest_prim; }
	NT square_distance() const { return m_query_sphere.squared_radius(); }

private: /* Data ************************************************************/
	SphereT      m_query_sphere;
	PointT       m_closest_point;
	PrimCPtr     m_closest_prim;
	DoIntersect  m_box_sphere_do_intersect;
	ProjectPoint m_project_point;
};

/// @todo Add an option to find first or all intersections.
template <typename Traits>
class AABB_BoxInterTraversal : public AABB_TraversalTraits<Traits>
{
public: /* Types ************************************************************/
	using NT     = typename Traits::NT;
	using PointT = typename Traits::PointT;
	using PrimT  = typename Traits::PrimT;
	using QPrimT = typename Traits::QPrimT;
	using BboxT  = typename Traits::BboxT;

	using CalcBbox    = typename Traits::CalcBbox;
	using DoIntersect = typename Traits::DoIntersect;

	using PrimCPtr  = const PrimT *;
	using PrimCPtrs = std::vector<PrimCPtr>;

public: /* Constructor ******************************************************/
	AABB_BoxInterTraversal(const QPrimT &query);

public: /* Inherited Interfaces *********************************************/
	bool intersection(const PrimT &prim) override;

	bool do_inter(const BboxT &bbox) const override;

public: /* Interfaces ******************************************************/
	const PrimCPtrs &result() const { return m_intersected_prims; }

private: /* Data ***********************************************************/
	CalcBbox    m_calc_bbox;
	DoIntersect m_do_intersect;

	QPrimT    m_query;
	BboxT     m_box_of_query;
	PrimCPtrs m_intersected_prims;
};

/// @todo Add an option to find first or all intersections.
template <typename Traits>
class AABB_PrimInterTraversal
{
public: /* Types ************************************************************/
	using NT     = typename Traits::NT;
	using PointT = typename Traits::PointT;
	using PrimT  = typename Traits::PrimT;
	using QPrimT = typename Traits::QPrimT;
	using BboxT  = typename Traits::BboxT;

	using CalcBbox    = typename Traits::CalcBbox;
	using DoIntersect = typename Traits::DoIntersect;

	using PrimCPtr  = const PrimT *;
	using PrimCPtrs = std::vector<PrimCPtr>;

public: /* Constructor ******************************************************/
	AABB_PrimInterTraversal(const QPrimT &query);

public: /* Inherited Interfaces *********************************************/
	bool intersection(const PrimT &prim) override;

	bool do_inter(const BboxT &bbox) const override;

public: /* Interfaces ******************************************************/
	PrimCPtrs result() const { return m_intersected_prims; }

private: /* Data ***********************************************************/
	CalcBbox    m_calc_bbox;
	DoIntersect m_do_intersect;

	QPrimT    m_query;
	BboxT     m_box_of_query;
	PrimCPtrs m_intersected_prims;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "AABBTraversalTraits.inl"
#endif