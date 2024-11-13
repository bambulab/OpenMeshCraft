#pragma once

#include "AABBTraversalTraits.h"

namespace OMC {

template <typename Traits>
AABB_ProjectionTraversal<Traits>::AABB_ProjectionTraversal(const PointT &query,
                                                           const PointT &hint,
                                                           PrimCPtr hint_prim)
  : m_query_sphere(query, (query - hint).sqrnorm())
  , m_closest_point(hint)
  , m_closest_prim(hint_prim)
{
}

template <typename Traits>
bool AABB_ProjectionTraversal<Traits>::intersection(const PrimT &prim)
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

template <typename Traits>
bool AABB_ProjectionTraversal<Traits>::do_inter(const BboxT &bbox) const
{
	return m_box_sphere_do_intersect(bbox, m_query_sphere);
}

template <typename Traits>
AABB_BoxInterTraversal<Traits>::AABB_BoxInterTraversal(const QPrimT &query)
  : m_query(query)
{
	m_box_of_query = m_calc_bbox(m_query);
}

template <typename Traits>
bool AABB_BoxInterTraversal<Traits>::intersection(const PrimT &prim)
{
	// TODO after implement exact box-tri intersect check, add it back
	//  if (m_do_intersect(m_box_of_query, prim))
	//  {
	//  	m_intersected_prims.push_back(&prim);
	//  }
	m_intersected_prims.push_back(&prim);
	return true;
}

template <typename Traits>
bool AABB_BoxInterTraversal<Traits>::do_inter(const BboxT &bbox) const
{
	return m_do_intersect(bbox, m_box_of_query);
}

template <typename Traits>
AABB_PrimInterTraversal<Traits>::AABB_PrimInterTraversal(const QPrimT &query)
  : m_query(query)
{
	m_box_of_query = m_calc_bbox(m_query);
}

template <typename Traits>
bool AABB_PrimInterTraversal<Traits>::intersection(const PrimT &prim)
{
	if (m_do_intersect(m_box_of_query, prim))
	{
		if (m_do_intersect(m_query, prim))
			m_intersected_prims.push_back(&prim);
	}
	return true;
}

template <typename Traits>
bool AABB_PrimInterTraversal<Traits>::do_inter(const BboxT &bbox) const
{
	return m_do_intersect(bbox, m_box_of_query);
}

} // namespace OMC