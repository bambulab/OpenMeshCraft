#pragma once

#include <vector>

namespace OMC {

template <typename Traits>
class SAABB_TraversalTraits
{
public: /* Types ************************************************************/
	using PrimT = typename Traits::PrimT;
	using BboxT = typename Traits::BboxT;

	SAABB_TraversalTraits() = default;

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
class SAABB_ProjectionTraversal : public SAABB_TraversalTraits<Traits>
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
	 * @brief Constructs an SAABB_ProjectionTraversal object.
	 *
	 * @param query The query point used for the traversal.
	 * @param hint A hint point to optimize the traversal.
	 * @param hint_prim A pointer to the primitive associated with the hint point.
	 */
	SAABB_ProjectionTraversal(const PointT &query, const PointT &hint,
	                         PrimCPtr hint_prim)
	  : m_query_sphere(query, (query - hint).sqrnorm())
	  , m_closest_point(hint)
	  , m_closest_prim(hint_prim)
	{
	}

public: /* Inherited Interfaces *********************************************/
	/**
	 * @brief Check if the distance to the given primitive is less than the
	 * current closest distance, and update the closest distance if necessary.
	 * @return always true to make the traversal continue.
	 */
	bool intersection(const PrimT &prim) override
	{
		PointT new_closest_point = m_project_point(prim, m_query_sphere.center());
		double new_square_distance =
		  (new_closest_point - m_query_sphere.center()).sqrnorm();

		if (new_square_distance < m_query_sphere.squared_radius())
		{
			m_query_sphere.squared_radius() = new_square_distance;
			m_closest_point                 = new_closest_point;
			m_closest_prim                  = &prim;
		}
		return true;
	}

	/**
	 * @brief Check if the box contains a possible closer point,
	 * which is equivalent to check if the query sphere intersects the box.
	 * @return true if the box contains a possible closer point.
	 */
	bool do_inter(const BboxT &bbox) const override
	{
		return m_box_sphere_do_intersect(bbox, m_query_sphere);
	}

public: /* Interfaces *******************************************************/
	/// @brief Get the closest point
	const PointT &closest_point() const { return m_closest_point; }

	/// @brief Get the closest primitive
	PrimCPtr closest_primitive() const { return m_closest_prim; }

	/// @brief Get the closest squared distance.
	NT squared_distance() const { return m_query_sphere.squared_radius(); }

private: /* Data & Predicates ***********************************************/
	/* Data */
	SphereT      m_query_sphere;
	PointT       m_closest_point;
	PrimCPtr     m_closest_prim;
	/* Predicates */
	DoIntersect  m_box_sphere_do_intersect;
	ProjectPoint m_project_point;
};

/// @todo Add an option to find first or all intersections.
template <typename Traits>
class SAABB_BoxInterTraversal : public SAABB_TraversalTraits<Traits>
{
public: /* Types ************************************************************/
	using PrimT  = typename Traits::PrimT;
	using QPrimT = typename Traits::QPrimT;
	using BboxT  = typename Traits::BboxT;

	using CalcBbox    = typename Traits::CalcBbox;
	using DoIntersect = typename Traits::DoIntersect;

	using PrimCPtr  = const PrimT *;
	using PrimCPtrs = std::vector<PrimCPtr>;

public: /* Constructor ******************************************************/
	/**
	 * @brief Construct an SAABB_BoxInterTraversal object.
	 * @param query The query primitive.
	 */
	SAABB_BoxInterTraversal(const QPrimT &query)
	  : m_query(query)
	{
		m_box_of_query = m_calc_bbox(m_query);
	}

public: /* Inherited Interfaces *********************************************/
	/**
	 * @brief Save the given primitive into results, due to its bounding box
	 * intersects the query box.
	 * @return always true to make the traversal continue.
	 */
	bool intersection(const PrimT &prim) override
	{
		m_intersected_prims.push_back(&prim);
		return true;
	}

	/**
	 * @brief Check if the bounding box of the given primitive intersects with the
	 * query box.
	 * @return true if they intersect.
	 */
	bool do_inter(const BboxT &bbox) const override
	{
		return m_do_intersect(bbox, m_box_of_query);
	}

public: /* Interfaces ********************************************************/
	/// @brief Get all (bbox-)intersected primitives
	const PrimCPtrs &result() const { return m_intersected_prims; }

private: /* Data & Predicates ************************************************/
	/* Data */
	const QPrimT &m_query;
	BboxT         m_box_of_query;
	PrimCPtrs     m_intersected_prims;
	/* Predicates */
	CalcBbox      m_calc_bbox;
	DoIntersect   m_do_intersect;
};

/// @todo Add an option to find first or all intersections.
template <typename Traits>
class SAABB_PrimInterTraversal
{
public: /* Types ************************************************************/
	using PrimT  = typename Traits::PrimT;
	using QPrimT = typename Traits::QPrimT;
	using BboxT  = typename Traits::BboxT;

	using CalcBbox    = typename Traits::CalcBbox;
	using DoIntersect = typename Traits::DoIntersect;

	using PrimCPtr  = const PrimT *;
	using PrimCPtrs = std::vector<PrimCPtr>;

public: /* Constructor ******************************************************/
	/**
	 * @brief Construct an SAABB_PrimInterTraversal object.
	 * @param query The query primitive.
	 */
	SAABB_PrimInterTraversal(const QPrimT &query)
	  : m_query(query)
	{
		m_box_of_query = m_calc_bbox(m_query);
	}

public: /* Inherited Interfaces *********************************************/
	/**
	 * @brief Check if the given primitive intersects with the query primitive.
	 * Save the primitive into results if they intersect.
	 * @return always true to make the traversal continue.
	 */
	bool intersection(const PrimT &prim) override
	{
		if (m_do_intersect(m_box_of_query, prim))
		{
			if (m_do_intersect(m_query, prim))
				m_intersected_prims.push_back(&prim);
		}
		return true;
	}

	/**
	 * @brief Check if the bounding box of the given primitive intersects with the
	 * query box.
	 * @return true if they intersect.
	 */
	bool do_inter(const BboxT &bbox) const override
	{
		return m_do_intersect(bbox, m_box_of_query);
	}

public: /* Interfaces *******************************************************/
	/// @brief Get all intersected primitives
	PrimCPtrs result() const { return m_intersected_prims; }

private: /* Data & Predicates ***********************************************/
	/* Data */
	const QPrimT &m_query;
	BboxT         m_box_of_query;
	PrimCPtrs     m_intersected_prims;
	/* Predicates */
	CalcBbox      m_calc_bbox;
	DoIntersect   m_do_intersect;
};

} // namespace OMC