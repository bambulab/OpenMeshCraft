#pragma once

#include "OpenMeshCraft/Utils/SFINAE.h"

namespace OMC {

template <typename Traits>
class DAABB_TraversalTraits
{
public: /* Types ************************************************************/
	using PrimT = typename Traits::PrimT;
	using BboxT = typename Traits::BboxT;

	DAABB_TraversalTraits() = default;

public: /* Interfaces *******************************************************/
	/**
	 * @brief Checks if there is an intersection with the given primitive.
	 *
	 * `intersection` can be reinterpreted as other operations, such as
	 * projection, intersection, etc.
	 *
	 * @param prim The primitive to check for intersection.
	 * @param ex_prim_idx The external index of the primitive.
	 * @return true if there is an intersection, false otherwise.
	 */
	virtual bool intersection(const PrimT &prim, index_t ex_prim_idx) = 0;

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

/// @todo Add an option to find first or all intersections.
template <typename Traits>
class DAABB_BoxInterTraversal : public DAABB_TraversalTraits<Traits>
{
public: /* Types ************************************************************/
	using PrimT  = typename Traits::PrimT;
	using QPrimT = typename Traits::QPrimT;
	using BboxT  = typename Traits::BboxT;

	using CalcBbox    = typename Traits::CalcBbox;
	using DoIntersect = typename Traits::DoIntersect;

	using Indices = std::vector<index_t>;

public: /* Constructor ******************************************************/
	/**
	 * @brief Construct an DAABB_BoxInterTraversal object.
	 * @param query The query primitive.
	 */
	DAABB_BoxInterTraversal(const QPrimT &query)
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
	bool intersection(OMC_UNUSED const PrimT &prim, index_t ex_prim_idx) override
	{
		m_intersected_prims.push_back(ex_prim_idx);
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
	const Indices &result() const { return m_intersected_prims; }

private: /* Data & Predicates ************************************************/
	/* Data */
	const QPrimT &m_query;
	BboxT         m_box_of_query;
	Indices       m_intersected_prims;
	/* Predicates */
	CalcBbox      m_calc_bbox;
	DoIntersect   m_do_intersect;
};

} // namespace OMC