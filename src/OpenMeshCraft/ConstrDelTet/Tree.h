#pragma once

#include "Utils.h"

#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTree.h"
#include "OpenMeshCraft/BVH/AABB/Static/SAABBTree.h"

#include "OpenMeshCraft/BVH/AABB/Instance/AABBTree_SegSphere_Intersection.h"
#include "OpenMeshCraft/BVH/AABB/Instance/AABBTree_Segment_Intersection.h"

#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"

#include <vector>

namespace OMC {

/*******************************************************************************
 * Dynamic AABB tree.
 * Detect intersection between Steiner point and constrained segment.
 *******************************************************************************/

template <typename Traits>
class GenericSegment3T
{
public: /* Traits *************************************************************/
	using EPoint = typename Traits::EPoint;
	using GPoint = typename Traits::GPoint;

	using AsGP = typename Traits::AsGP;
	using AsEP = typename Traits::AsEP;
	using ToEP = typename Traits::ToEP;

public: /* Constructors *******************************************************/
	/**
	 * @brief Construct Segment3T by default.
	 */
	GenericSegment3T()
	  : m_start_gp(nullptr)
	  , m_end_gp(nullptr)
	{
	}

	/**
	 * @brief Construct Segment3T from given \p start and \p end.
	 * @param start start point of segment
	 * @param end end point of segment
	 */
	GenericSegment3T(const GPoint *start, const GPoint *end)
	  : m_start_gp(start)
	  , m_end_gp(end)
	  , m_start_ep(ToEP()(*start))
	  , m_end_ep(ToEP()(*end))
	{
	}

	/// Acess the explicit endpoints for approximate calculation.
	const EPoint &start() const { return m_start_ep; }
	const EPoint &end() const { return m_end_ep; }

	/// Acess the generic endpoints for exact calculation.
	const GPoint &start_gp() const { return *m_start_gp; }
	const GPoint &end_gp() const { return *m_end_gp; }

public: /* Data members *******************************************************/
	const GPoint *m_start_gp;
	const GPoint *m_end_gp;

	EPoint m_start_ep;
	EPoint m_end_ep;
};

template <typename Traits>
class CalcBbox_CDT
{
public: /* Traits *************************************************************/
	using IT = IntervalNumber<std::true_type>;

	using EPoint = typename Traits::EPoint;
	using GPoint = typename Traits::GPoint;

	using BoundingBox = typename Traits::BoundingBox;
	using CalcBbox    = typename Traits::CalcBbox;

	using GSegment = GenericSegment3T<Traits>;

public: /* Operators **********************************************************/
	/**
	 * @brief Calculate the bounding box of the segment.
	 * @param seg The segment to calculate.
	 * @return The bounding box of the segment.
	 */
	BoundingBox operator()(const GSegment &seg) const
	{
		const GPoint &start = seg.start_gp(), &end = seg.end_gp();

		// calculate the bounding box of endpoints
		BoundingBox start_bound = CalcBbox()(start);
		BoundingBox end_bound   = CalcBbox()(end);

		// calculate the bounding box of the diametral sphere of the segment.
		BoundingBox bbox;
		{
			IT::Protector it_protecter;

			// start point
			IT sx(-start_bound.min_bound().x(), start_bound.max_bound().x());
			IT sy(-start_bound.min_bound().y(), start_bound.max_bound().y());
			IT sz(-start_bound.min_bound().z(), start_bound.max_bound().z());
			// end point
			IT ex(-end_bound.min_bound().x(), end_bound.max_bound().x());
			IT ey(-end_bound.min_bound().y(), end_bound.max_bound().y());
			IT ez(-end_bound.min_bound().z(), end_bound.max_bound().z());
			// middle point
			IT mx = (sx + ex) * 0.5;
			IT my = (sy + ey) * 0.5;
			IT mz = (sz + ez) * 0.5;
			// radius
			IT dx = (sx - ex), dy = (sy - ey), dz = (sz - ez);
			IT squared_diameter = dx * dx + dy * dy + dz * dz;
			IT radius           = squared_diameter.sqrt() * 0.5;
			// bounding
			IT minx = mx - radius, maxx = mx + radius;
			IT miny = my - radius, maxy = my + radius;
			IT minz = mz - radius, maxz = mz + radius;

			// bounding box
			bbox.min_bound() = EPoint(minx.inf(), miny.inf(), minz.inf());
			bbox.max_bound() = EPoint(maxx.sup(), maxy.sup(), maxz.sup());
		}
		return bbox;
	}

	BoundingBox operator()(const GPoint &gpnt) const { return CalcBbox()(gpnt); }
};

template <typename Traits>
using CDT_SegSphereTree = DAABBTree_SegSphere_Intersection<
  GenericSegment3T<Traits>, CalcBbox_CDT<Traits>, typename Traits::DoIntersect>;

template <typename Traits>
using CDT_SegmentTree =
  SAABBTree_Segment_Intersection<typename Traits::Segment,
                                 typename Traits::CalcBbox,
                                 typename Traits::DoIntersect>;

} // namespace OMC