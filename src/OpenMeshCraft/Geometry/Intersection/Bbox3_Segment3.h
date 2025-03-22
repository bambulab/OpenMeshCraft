#pragma once

#include "Bbox3_BoundedLine3.h"

namespace OMC {

/**
 * @brief Check if BoundingBox3 and Segment3 intersect.
 * @tparam Kernel
 */
template <typename Kernel>
class Bbox3_Segment3_DoIntersectK
{
public:
	using K            = Kernel;
	using Segment3     = typename K::Segment3;
	using BoundingBox3 = typename K::BoundingBox3;

	using Bbox3_BdLine3_DoInter = Bbox3_BoundedLine3_DoIntersectK<Kernel>;

public:
	bool operator()(const BoundingBox3 &box, const Segment3 &segment) const
	{
		return Bbox3_BdLine3_DoInter().do_intersect(
		  box, segment.start(), /*bounded start*/ true, segment.end(),
		  /*bounded end*/ true);
	}
};

} // namespace OMC