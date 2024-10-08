#pragma once

#include "ConstrRecover.h"

namespace OMC {

/**
 * @brief Initialize with the Delaunay tetrahedral mesh and the input
 * constrained triangles. Prepare for the constraits recovery.
 * @param _tet_mesh the Delaunay tetrahedral mesh
 * @param _plc the input constrained piecewise linear complex
 */
template <typename Traits>
ConstraintsRecover<Traits>::ConstraintsRecover(TetMesh &_tet_mesh, PLC &_plc)
  : tet_mesh(_tet_mesh)
  , plc(_plc)
{
}

template <typename Traits>
void ConstraintsRecover<Traits>::segmentRecovery()
{
	// traverse all edges in the PLC to find missing segments
	std::vector<index_t> missing_segments;
	for (index_t ei = 0; ei < plc.numEdges(); ei++)
	{
		const PLC::PLCEdge &e = plc.edge(ei);
		if (e.type != PLC::PLCEdgeType::FLAT_EDGE &&
		    !tet_mesh.edgeExists(e.ep0(), e.ep1()))
			missing_segments.push_back(ei);
	}
}

template <typename Traits>
void ConstraintsRecover<Traits>::splitMissingSegment(index_t ei)
{
}

/**
 * @brief Find reference encroaching point for segment `ei`.
 *
 * The segment has two endpoints `v1` and `v2`.
 * The segment defines a diametral sphere `D`.
 * Encroaching points are points enclosed (or touched?) by `D`.
 * Reference encroaching point is the point `r` in encroaching points, such
 * that `v1`, `v2` and `r` define a circle with maximum radius.
 * @param ei index to the segment
 * @param ref_vid index to the reference encroaching point
 * @param ref_tid index to the tetrahedron containing the reference encroaching
 * point
 * @see Section 3.3 Segment recovery, in [Robust CDT].
 */
template <typename Traits>
void ConstraintsRecover<Traits>::findReferenceEncroachingPoint(const index_t ei,
                                                               index_t &ref_vid,
                                                               index_t &ref_tid)
{
}

} // namespace OMC