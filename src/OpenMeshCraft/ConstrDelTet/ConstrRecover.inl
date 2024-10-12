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
ConstraintsRecover<Traits>::ConstraintsRecover(std::vector<GPoint *> &_verts,
                                               TetMesh &_tet_mesh, PLC &_plc)
  : verts(_verts)
  , tet_mesh(_tet_mesh)
  , plc(_plc)
{
}

template <typename Traits>
void ConstraintsRecover<Traits>::segmentRecovery()
{
	// initialize the PLC edges
	plc.initPLCEdges();

	// traverse all edges in the PLC to find missing segments
	std::vector<index_t> missing_segments;
	for (index_t eid = 0; eid < plc.numEdges(); eid++)
	{
		const PLC::PLCEdge &e = plc.edge(eid);
		if (e.type != PLC::PLCEdgeType::FLAT_EDGE &&
		    !tet_mesh.edgeExists(e.ep0(), e.ep1()))
		{
			missing_segments.push_back(eid);
		}
	}

	// clear the `TOUCHED` mark for all vertices
	for (index_t vid = 0; vid < tet_mesh.sizeVerts(); vid++)
		tet_mesh.unmark(vid, TetMesh::VTX_MARK::TOUCHED);

	// Main loop: split missing segments to recover them.
	while (!missing_segments.empty())
	{
		// Split the existing constrained segment
		while (!missing_segments.empty())
		{
			// Get the constrained segment to split
			index_t eid = missing_segments.back();
			missing_segments.pop_back();
			const typename PLC::PLCEdge &e = plc.edge(eid);
			// Check if the segment is still missing
			if (tet_mesh.edgeExists(e.ep0(), e.ep1()))
				continue;
			// Split the segment
			index_t              new_vid = splitMissingSegment(eid);
			// Touch the neighbor vertices
			// New missing edges will appear near touched vertices
			AuxVector64<index_t> local_vv;
			local_vv.push_back(e.ep0());
			local_vv.push_back(e.ep1());
			tet_mesh.VV(new_vid, local_vv);
			for (index_t vid : local_vv)
				tet_mesh.mark(vid, TetMesh::VTX_MARK::TOUCHED);
		}
		// Find new missing edges around touched vertices
		for (index_t eid = 0; eid < plc.numEdges(); eid++)
		{
			const PLC::PLCEdge &e = plc.edge(eid);
			if (!is_valid_idx(e.child_id) && e.type != PLC::PLCEdgeType::FLAT_EDGE &&
			    tet_mesh.isVtxMarked(e.ep0(), TetMesh::VTX_MARK::TOUCHED) &&
			    tet_mesh.isVtxMarked(e.ep1(), TetMesh::VTX_MARK::TOUCHED) &&
			    !tet_mesh.edgeExists(e.ep0(), e.ep1()))
			{
				missing_segments.push_back(eid);
			}
		}
		// clear the `TOUCHED` mark for all vertices
		for (index_t vid = 0; vid < tet_mesh.sizeVerts(); vid++)
			tet_mesh.unmark(vid, TetMesh::VTX_MARK::TOUCHED);
	}

	tet_mesh.removeDeletedTets();
}

template <typename Traits>
index_t ConstraintsRecover<Traits>::splitMissingSegment(index_t eid)
{
	GPoint *new_pnt;
	index_t new_vid  = InvalidIndex;
	index_t curr_tet = InvalidIndex;

	typename PLC::PLCEdge &edge = plc.edge(eid);

	if (edge.type == PLC::PLCEdgeType::BOTH_ACUTE_VERTEX)
	{
		curr_tet = tet_mesh.toIdOff(tet_mesh.incTet(edge.ep0()));
		new_pnt  = splitAtMiddle(eid);
	}
	else // ONE_ACUTE_VERTEX or NO_ACUTE_VERTEX
	{
		index_t ref_vid;
		findReferenceEncroachingPoint(eid, ref_vid, curr_tet);

		OMC_EXPENSIVE_ASSERT(is_valid_idx(ref_vid),
		                     "Could not find a valid reference encroaching point.");

		if (edge.type == PLC::PLCEdgeType::NO_ACUTE_VERTEX)
		{
			new_pnt = splitSegment_NoAcuteVertex(eid, ref_vid);
		}
		else // ONE_ACUTE_VERTEX
		{
			new_pnt = splitSegment_OneAcuteVertex(eid, ref_vid);
		}
	}

	// create the new vertex
	new_vid = newVtx(new_pnt);
	// split the PLC edge
	plc.splitPLCEdge(eid, new_vid);
	// insert the splitting point into the Delaunay tetrahedral mesh
	DelTet DT(tet_mesh);
	DT.insertVertex(new_vid, curr_tet);

	return new_vid;
}

/**
 * @brief Find reference encroaching point for segment `eid`.
 *
 * The segment has two endpoints `v1` and `v2`.
 * The segment defines a diametral sphere `D`.
 * Encroaching points are points enclosed (or touched?) by `D`.
 * Reference encroaching point is the point `r` in encroaching points, such
 * that `v1`, `v2` and `r` define a circle with maximum radius.
 * @param eid index to the segment
 * @param ref_vid index to the reference encroaching point
 * @param ref_tid index to the tetrahedron containing the reference encroaching
 * point
 * @see Section 3.3 Segment recovery, in [Robust CDT].
 * @note Rely on mark `VISITED` to avoid visiting the same tetrahedron and the
 * same vertex multiple times.
 * @note ==NOT THREAD SAFE==
 */
template <typename Traits>
void ConstraintsRecover<Traits>::findReferenceEncroachingPoint(index_t  eid,
                                                               index_t &ref_vid,
                                                               index_t &ref_tid)
{
	AuxVector64<index_t>         encroach_tets;
	const typename PLC::PLCEdge &edge = plc.edge(eid);

	// find tetrahedra adjacent to the first endpoint `ep0`
	tet_mesh.VT(edge.ep0(), encroach_tets);
	// and mark the tetrahedra as visited
	for (index_t tet_idoff : encroach_tets)
		tet_mesh.mark(tet_idoff, TetMesh::TET_MARK::VISITED);

	tet_mesh.mark(edge.ep0(), TetMesh::VTX_MARK::VISITED);
	tet_mesh.mark(edge.ep1(), TetMesh::VTX_MARK::VISITED);

	const GPoint &p0    = gpnt(edge.ep0());
	const GPoint &p1    = gpnt(edge.ep1());
	const GPoint *ref_p = nullptr;
	ref_vid             = InvalidIndex;
	ref_tid             = InvalidIndex;

	// TODO An inSphere predicate, receiving 2 points to form the sphere, and 1
	// query point.
	auto inSphere = [](OMC_UNUSED const GPoint &a, OMC_UNUSED const GPoint &b,
	                   OMC_UNUSED const GPoint &c) -> bool { return false; };

	// TODO A LargerCircle predicate, receiving 3 points to form the circle, and 1
	// query point to form another circle, and compare the radius.
	auto largerCircle = [](OMC_UNUSED const GPoint &a, OMC_UNUSED const GPoint &b,
	                       OMC_UNUSED const GPoint &c,
	                       OMC_UNUSED const GPoint &d) -> bool { return false; };

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
			const GPoint &curr_p = gpnt(vid);

			// check if the vertex is encroaching
			if (inSphere(p0, p1, curr_p))
			{
				tet_mesh.mark(vid, TetMesh::VTX_MARK::ENCROACHED);
				// check if it is the reference encroaching point
				if (ref_vid == InvalidIndex || largerCircle(p0, p1, *ref_p, gpnt(vid)))
				{
					ref_vid = vid;
					ref_tid = tet_idoff;
					ref_p   = &gpnt(ref_vid);
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

		for (index_t j = 0; j < 4; j++)
		{
			index_t neigh_idoff = tet_mesh.tetNeigh(tet_idoff + j);

			if (tet_mesh.isTetMarked(neigh_idoff, TetMesh::TET_MARK::VISITED) ||
			    tet_mesh.tetNode(neigh_idoff) == TetMesh::INFINITE_VERTEX)
				continue;

			if (total_encroached - is_encroached[j] > 0)
			{
				encroach_tets.push_back(tet_mesh.clipId(neigh_idoff));
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
		for (index_t j = 0; j < 4; j++)
		{
			index_t vid = tet_mesh.tetNode(idoff + j);
			tet_mesh.unmark(vid, TetMesh::VTX_MARK::VISITED);
			tet_mesh.unmark(vid, TetMesh::VTX_MARK::ENCROACHED);
		}
	}
}

/**
 * @brief Get the splitting point to split the constrained edge `eid` at the
 * middle point, but do not really split the edge.
 *
 * This split strategy is used to split segment with two acute vertices.
 * @return The splitting point.
 */
template <typename Traits>
auto ConstraintsRecover<Traits>::splitAtMiddle(index_t eid) const -> GPoint *
{
	const typename PLC::PLCEdge &edge = plc.edge(eid);

	// TODO get the middle point represented by LNC implicit point
	auto getMidPoint = [](OMC_UNUSED const typename PLC::PLCEdge &e)
	{ return nullptr; };
	GPoint *new_pnt = getMidPoint(edge);

	return new_pnt;
}

/**
 * @brief Find the splitting point to split the constrained edge `eid` that has
 * no acute vertices, but do not really split the edge.
 * @param eid The constrained edge to split.
 * @param ref_vid The reference encroaching point.
 * @return the splitting point.
 * @see The strategy is described in Section 3.3 of [Robust CDT].
 */
template <typename Traits>
auto ConstraintsRecover<Traits>::splitSegment_NoAcuteVertex(
  index_t eid, index_t ref_vid) const -> GPoint *
{
	const typename PLC::PLCEdge &edge = plc.edge(eid);

	const GPoint &ep0_pnt = gpnt(edge.ep0());
	const GPoint &ep1_pnt = gpnt(edge.ep1());
	const GPoint &ref_pnt = gpnt(ref_vid);

	GPoint *new_pnt   = nullptr;
	index_t acute_vid = InvalidIndex;

	// TODO get the middle point represented by LNC implicit point
	auto getMidPoint = [](OMC_UNUSED const typename PLC::PLCEdge &e)
	{ return nullptr; };

	// TODO
	// Check if the distance between `a` and `b` is less than half the distance
	// between `a` and `c`.
	auto isLessThanHalfDistance =
	  [](OMC_UNUSED const GPoint &a, OMC_UNUSED const GPoint &b,
	     OMC_UNUSED const GPoint &c) { return false; };

	// TODO
	// Get the intersection point between the line and the sphere, represented as
	// an LNC implicit point.
	// The line is defined by the constrained edge.
	// The sphere is centered at one endpoint of the edge, with the radius being
	// the distance between the endpoint and the reference encroaching point.
	auto lineSphereIntersection =
	  [](OMC_UNUSED index_t eid, OMC_UNUSED bool reverse_edge,
	     OMC_UNUSED index_t ref_vid, OMC_UNUSED index_t &acute_vid,
	     OMC_UNUSED GPoint *new_pnt) { return nullptr; };

	if (isLessThanHalfDistance(ep0_pnt, ref_pnt, ep1_pnt))
	{
		lineSphereIntersection(eid, /*reverse*/ false, ref_vid, acute_vid, new_pnt);
	}
	else if (isLessThanHalfDistance(ep1_pnt, ref_pnt, ep0_pnt))
	{
		lineSphereIntersection(eid, /*reverse*/ true, ref_vid, acute_vid, new_pnt);
	}
	else
	{
		// The reference encroaching point is the middle point.
		// Split the segment at the middle point.
		new_pnt = getMidPoint(edge);
	}

	return new_pnt;
}

/**
 * @brief Split the constrained edge `eid` that has only one acute vertex.
 * @param eid The constrained edge to split.
 * @param ref_vid the reference encroaching point.
 * @return the new splitting point.
 * @see The strategy is described in Section 3.3 of [Robust CDT].
 */
template <typename Traits>
auto ConstraintsRecover<Traits>::splitSegment_OneAcuteVertex(
  index_t eid, index_t ref_vid) const -> GPoint *
{
	const typename PLC::PLCEdge &edge = plc.edge(eid);

	// TODO get the middle point represented by LNC implicit point
	auto getMidPoint = [](OMC_UNUSED const typename PLC::PLCEdge &e)
	{ return nullptr; };

	// TODO
	// Similar to but not the same as the one in splitSegment_NoAcuteVertex.
	auto lineSphereIntersection =
	  [](OMC_UNUSED index_t eid, OMC_UNUSED index_t ref_vid,
	     OMC_UNUSED index_t &acute_vid, OMC_UNUSED GPoint *new_pnt)
	{ return nullptr; };

	// TODO
	// Check if `a` is closer to `b` than to `c`.
	auto isCloserThan = [](OMC_UNUSED const GPoint &a, OMC_UNUSED const GPoint &b,
	                       OMC_UNUSED const GPoint &c) { return true; };

	index_t acute_vid = InvalidIndex;
	GPoint *new_pnt   = nullptr;

	new_pnt = lineSphereIntersection(eid, ref_vid, acute_vid, new_pnt);

	if (isCloserThan(*new_pnt, gpnt(edge.ep1()), gpnt(ref_vid)))
	{
		// delete new_pnt, create a middle point
		new_pnt = getMidPoint(edge);
	}

	return new_pnt;
}

template <typename Traits>
void ConstraintsRecover<Traits>::faceRecovery()
{
	plc.initPLCFaces();
}

/**
 * @brief Create a new vertex and update `tet_mesh` and `plc` at the same time.
 * @param new_pnt geometric implementation of the new vertex
 * @return the index to the new vertex.
 */
template <typename Traits>
index_t ConstraintsRecover<Traits>::newVtx(GPoint *new_pnt)
{
	// create the new vertex
	index_t new_vid = verts.size();
	// TODO point arena
	verts.push_back(new_pnt);

	// create auxiliary data in TetMesh & PLC
	tet_mesh.newVtx(new_vid);

	return new_vid;
}

} // namespace OMC