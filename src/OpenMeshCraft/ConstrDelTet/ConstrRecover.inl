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
 * @note Rely on mark `VISITED` to avoid visiting the same tetrahedron and the
 * same vertex multiple times.
 * @note ==NOT THREAD SAFE==
 */
template <typename Traits>
void ConstraintsRecover<Traits>::findReferenceEncroachingPoint(const index_t ei,
                                                               index_t &ref_vid,
                                                               index_t &ref_tid)
{
	AuxVector64<index_t> encroach_tets;
	PLC::PLCEdge        &edge = plc.edge(ei);

	// find tetrahedra adjacent to the first endpoint `ep0`
	tet_mesh.VT(edge.ep0(), encroach_tets);
	// and mark the tetrahedra as visited
	for (index_t tet_idoff : encroach_tets)
		tet_mesh.mark(tet_idoff, TetMesh::TET_MARK::VISITED);

	tet_mesh.mark(edge.ep0(), TetMesh::VTX_MARK::VISITED);
	tet_mesh.mark(edge.ep1(), TetMesh::VTX_MARK::VISITED);

	const GPoint &p0    = tet_mesh.gpnt(edge.ep0());
	const GPoint &p1    = tet_mesh.gpnt(edge.ep1());
	const GPoint *ref_p = nullptr;
	ref_vid             = InvalidIndex;
	ref_tid             = InvalidIndex;

	// TODO An inSphere predicate, receiving 2 points to form the sphere, and 1
	// query point.
	auto inSphere = [](const GPoint &a, const GPoint &b, const GPoint &c) -> bool
	{ return false; };

	// TODO A LargerCircle predicate, receiving 3 points to form the circle, and 1
	// query point to form another circle, and compare the radius.
	auto largerCircle = [](const GPoint &a, const GPoint &b, const GPoint &c,
	                       const GPoint &d) -> bool { return false; };

	for (index_t i = 0; i < encroach_tets.size(); i++)
	{
		index_t tet_idoff = encroach_tets[i];

		// check if the tetrahedron has an encroaching point
		for (index_t j = 0; j < 4; j++)
		{
			index_t vid = tet_mesh.tetNode(tet_idoff + j);
			if (tet_mesh.isVtxMarked(vid, TetMesh::VTX_MARK::VISITED) ||
			    tet_mesh.isVtxMarked(vid, TetMesh::VTX_MARK::ENCROACHED))
				continue;
			tet_mesh.mark(vid, TetMesh::VTX_MARK::VISITED);
			const GPoint &curr_p = tet_mesh.gpnt(vid);

			// check if the vertex is encroaching
			if (inSphere(p0, p1, curr_p))
			{
				tet_mesh.mark(vid, TetMesh::VTX_MARK::ENCROACHED);
				// check if it is the reference encroaching point
				if (ref_vid == InvalidIndex ||
				    largerCircle(p0, p1, *ref_p, tet_mesh.gpnt(vid)))
				{
					ref_vid = vid;
					ref_tid = tet_idoff;
					ref_p   = &tet_mesh.gpnt(ref_vid);
				}
			}
		}

		// clang-format off
		const int is_encroached[] = {
			tet_mesh.isVtxMarked(tet_mesh.tetNode(tet_idoff), TetMesh::VTX_MARK::ENCROACHED),
			tet_mesh.isVtxMarked(tet_mesh.tetNode(tet_idoff + 1), TetMesh::VTX_MARK::ENCROACHED),
			tet_mesh.isVtxMarked(tet_mesh.tetNode(tet_idoff + 2), TetMesh::VTX_MARK::ENCROACHED),
			tet_mesh.isVtxMarked(tet_mesh.tetNode(tet_idoff + 3), TetMesh::VTX_MARK::ENCROACHED),
		};
		const int total_encroached = is_encroached[0] + is_encroached[1] + is_encroached[2] + is_encroached[3];
		// clang-format on

		// Add neighboring tetrahedra to `encroach_tets` for subsequent encroachment
		// checks. The cases are divided based on the number of encroaching vertices
		// in the current tetrahedron:
		//
		// - If the current tetrahedron has no encroaching vertices:
		// 		No neighboring tetrahedron is added.
		// - If the current tetrahedron has only one encroaching vertex:
		//    Neighboring tetrahedra at corners other than the encroaching corner
		//    are added.
		// - If the current tetrahedron has more than one encroaching vertex:
		//    All neighboring tetrahedra are added.

		for (index_t i = 0; i < 4; i++)
		{
			index_t neigh_idoff = tet_mesh.tetNeigh(tet_idoff + i);

			if (tet_mesh.isTetMarked(neigh_idoff, TetMesh::TET_MARK::VISITED) ||
			    tet_mesh.tetNode(neigh_idoff) == TetMesh::INFINITE_VERTEX)
				continue;

			if (total_encroached - is_encroached[i] > 0)
			{
				encroach_tets.push_back(clipId(neigh_idoff));
				tet_mesh.mark(neigh_idoff, TetMesh::TET_MARK::VISITED);
			}
		}
	}

	// clear all marks
	tet_mesh.unmark(edge.ep0(), TetMesh::VTX_MARK::VISITED);
	tet_mesh.unmark(edge.ep1(), TetMesh::VTX_MARK::VISITED);
	for (index_t idoff : encroach_tets)
	{
		tet_mesh.unmark(idoff, TetMesh::TET_MARK::VISITED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff), TetMesh::VTX_MARK::VISITED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff), TetMesh::VTX_MARK::ENCROACHED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff + 1), TetMesh::VTX_MARK::VISITED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff + 1), TetMesh::VTX_MARK::ENCROACHED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff + 2), TetMesh::VTX_MARK::VISITED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff + 2), TetMesh::VTX_MARK::ENCROACHED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff + 3), TetMesh::VTX_MARK::VISITED);
		tet_mesh.unmark(tet_mesh.tetNode(idoff + 3), TetMesh::VTX_MARK::ENCROACHED);
	}
}

} // namespace OMC