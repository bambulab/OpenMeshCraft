#pragma once

#include "OpenMeshCraft/NumberTypes/NumberUtils.h"
#include "ProjectPoint3K.h"

namespace OMC {

template <typename Kernel>
auto ProjectPoint3K<Kernel>::operator()(const Segment3 &segment,
                                        const GPoint3  &point) const -> EPoint3
{
#if 0 // when needed, figure out a better way to handle this
	typename CheckDegenerate3::DgnType degeneration = CheckDegenerate3()(segment);

	if (std::holds_alternative<typename CheckDegenerate3::NoDgn>(degeneration))
	{
		return proj_to_segment(segment, point);
	}
	else if (std::holds_alternative<GPoint3>(degeneration))
	{
		// segment is degenerate to point, point is projected to point.
		return ToEP()(std::get<GPoint3>(std::move(degeneration)));
	}
#endif

	return proj_to_segment(segment, point);
}

template <typename Kernel>
auto ProjectPoint3K<Kernel>::operator()(const Triangle3 &triangle,
                                        const GPoint3   &point) const -> EPoint3
{
#if 0 // when needed, figure out a better way to handle this
	typename CheckDegenerate3::DgnType degeneration =
	  CheckDegenerate3()(triangle);

	if (std::holds_alternative<typename CheckDegenerate3::NoDgn>(degeneration))
	{
		return proj_to_triangle(triangle, point);
	}
	else if (std::holds_alternative<Segment3>(degeneration))
	{
		// segment is degenerate to point, point is projected to point.
		return proj_to_segment(std::get<Segment3>(degeneration), point);
	}
	else if (std::holds_alternative<GPoint3>(degeneration))
	{
		// segment is degenerate to point, point is projected to point.
		return ToEP()(std::get<GPoint3>(std::move(degeneration)));
	}
#endif

	return proj_to_triangle(triangle, point);
}

template <typename Kernel>
auto ProjectPoint3K<Kernel>::operator()(const BoundingBox3 &bbox,
                                        const GPoint3 &point) const -> EPoint3
{
	EPoint3 result = ToEP()(point);
#define COMPARE_AXIS(axis)                                                \
	if (LessThan3D().on_##axis(point, bbox.min_bound()) <= Sign::ZERO)      \
		result.axis() = bbox.min_bound().axis();                              \
	else if (LessThan3D().on_##axis(point, bbox.max_bound()) >= Sign::ZERO) \
		result.axis() = bbox.max_bound().axis();

	COMPARE_AXIS(x);
	COMPARE_AXIS(y);
	COMPARE_AXIS(z);
#undef COMPARE_AXIS
	return result;
}

template <typename Kernel>
auto ProjectPoint3K<Kernel>::proj_to_segment(const Segment3 &segment,
                                             const GPoint3  &point) const
  -> EPoint3
{
	// No degeneration, project point to the segment.
	Vec3 segment_vec = segment.end() - segment.start();
	NT   numerator   = segment_vec.dot(point - segment.start());

	if (numerator /*segment_to_vector.dot(query - *segment.first)*/ <= NT(0.0))
	{
		return segment.start();
	}
	else if (segment_vec.dot(point - segment.end()) >= NT(0.0))
	{
		return segment.end();
	}
	else
	{
		NT dominator = segment_vec.sqrnorm();
		return segment.start() + (numerator / dominator) * segment_vec;
	}
}

template <typename Kernel>
auto ProjectPoint3K<Kernel>::proj_to_triangle(const Triangle3 &triangle,
                                              const GPoint3   &point) const
  -> EPoint3
{
	const EPoint3 &a = triangle.v0(), &b = triangle.v1(), &c = triangle.v2();
	EPoint3        ep = ToEP()(point);

	// 1. Project point to the support plane of the triangle.
	Vec3    normal      = ConstructNormal3()(triangle);
	NT      numerator   = (ep - a).dot(normal);
	NT      denominator = normal.sqrnorm();
	EPoint3 proj_point  = ep - (numerator / denominator) * normal;
	// proj_point is the project point on the support plane.

	// 2. Check if the projected point is inside the triangle.
	// * If it is inside the triangle, then return it as result.
	// * If it is outside the triangle, further project proj_point to one segment
	// depending on its position.

	// If the proj_point is outside the triangle, we project it to triangle edge
	// lines and check if it is on the triangle edge segments. We need to try no
	// more than three edges.

	bool    outside = false;
	EPoint3 result;

	auto check_seg = [&ep, &normal, &proj_point, &outside,
	                  &result](const EPoint3 &start,
	                           const EPoint3 &end) -> bool // found result
	{
		// Offset points of triangle by the normal of triangle to construct a plane
		// which is orthogonal to the triangle.
		EPoint3 offset_start = start + normal;

		// The orientation of point with respect to orthogonal plane defined on ij,
		// where ij means vertex vi and vj.
		// These orientations are used to determine whether the proj_point is
		// inside/outside the triangle.
		Sign ori_point = Orient3D()(start, end, offset_start, ep);
		if (ori_point != Sign::NEGATIVE)
		{
			outside = true;

			// 3. The proj_point is outside the triangle.
			// Project proj_point to Line, check if it is on the Segment.
			Vec3 seg_vec        = end - start;
			Vec3 start_to_point = proj_point - start;
			Vec3 end_to_point   = proj_point - end;

			NT ori_start_to_end = start_to_point.dot(seg_vec);
			NT ori_end_to_start = end_to_point.dot(seg_vec);
			if (ori_start_to_end >= NT(0.0) && ori_end_to_start <= NT(0.0))
			{
				// 4. The proj_proj_point is on the Segment
				NT seg_sqrnorm = seg_vec.sqrnorm();
				result         = start + (ori_start_to_end / seg_sqrnorm) * seg_vec;
				return true;
			}
			// 5. The proj_proj_point is not on the Segment.
			// It is possibly on another segment or vertices.
		}
		return false;
	};

	if (check_seg(a, b) || check_seg(b, c) || check_seg(c, a))
		return result;

	if (outside)
	{
		NT dis_to_a = (ep - a).sqrnorm();
		NT dis_to_b = (ep - b).sqrnorm();
		NT dis_to_c = (ep - c).sqrnorm();
		if (dis_to_a <= dis_to_b)
		{
			if (dis_to_a <= dis_to_c)
				return a;
			else
				return c;
		}
		else
		{
			if (dis_to_b <= dis_to_c)
				return b;
			else
				return c;
		}
	}
	else // proj_point is inside the triangle, return it.
		return proj_point;
}

} // namespace OMC