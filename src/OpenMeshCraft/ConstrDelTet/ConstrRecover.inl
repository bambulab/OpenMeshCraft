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
			    tet_mesh.isMarked(e.ep0(), TetMesh::VTX_MARK::TOUCHED) &&
			    tet_mesh.isMarked(e.ep1(), TetMesh::VTX_MARK::TOUCHED) &&
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
 * @note Rely on mark `TOUCHED` to avoid visiting the same tetrahedron and the
 * same vertex multiple times.
 * @note ==NOT THREAD SAFE==
 */
template <typename Traits>
void ConstraintsRecover<Traits>::findReferenceEncroachingPoint(
  index_t eid, index_t &ref_vid, index_t &ref_tid) const
{
	AuxVector64<index_t>         encroach_tets;
	const typename PLC::PLCEdge &edge = plc.edge(eid);

	// find tetrahedra adjacent to the first endpoint `ep0`
	tet_mesh.VT(edge.ep0(), encroach_tets);
	// and mark the tetrahedra as touched
	for (index_t tet_idoff : encroach_tets)
		tet_mesh.mark(tet_idoff, TetMesh::TET_MARK::TOUCHED);

	tet_mesh.mark(edge.ep0(), TetMesh::VTX_MARK::TOUCHED);
	tet_mesh.mark(edge.ep1(), TetMesh::VTX_MARK::TOUCHED);

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
			if (tet_mesh.isMarked(vid, TetMesh::VTX_MARK::TOUCHED) ||
			    tet_mesh.isMarked(vid, TetMesh::VTX_MARK::ENCROACHED))
				continue;
			tet_mesh.mark(vid, TetMesh::VTX_MARK::TOUCHED);
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
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff), TetMesh::VTX_MARK::ENCROACHED),
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff + 1), TetMesh::VTX_MARK::ENCROACHED),
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff + 2), TetMesh::VTX_MARK::ENCROACHED),
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff + 3), TetMesh::VTX_MARK::ENCROACHED),
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

			if (tet_mesh.isMarked(neigh_idoff, TetMesh::TET_MARK::TOUCHED) ||
			    tet_mesh.tetNode(neigh_idoff) == TetMesh::INFINITE_VERTEX)
				continue;

			if (total_encroached - is_encroached[j] > 0)
			{
				encroach_tets.push_back(tet_mesh.clipId(neigh_idoff));
				tet_mesh.mark(neigh_idoff, TetMesh::TET_MARK::TOUCHED);
			}
		}
	}

	// clear all marks
	tet_mesh.unmark(edge.ep0(), TetMesh::VTX_MARK::TOUCHED);
	tet_mesh.unmark(edge.ep1(), TetMesh::VTX_MARK::TOUCHED);
	for (index_t idoff : encroach_tets)
	{
		tet_mesh.unmark(idoff, TetMesh::TET_MARK::TOUCHED);
		for (index_t j = 0; j < 4; j++)
		{
			index_t vid = tet_mesh.tetNode(idoff + j);
			tet_mesh.unmark(vid, TetMesh::VTX_MARK::TOUCHED);
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
	// initialize PLC faces
	plc.initPLCFaces();

	// initialize auxiliary data for face recovery.
	{
		v_orient.clear();
		v_cached_orient.clear();
		v_count.clear();
		v_orient.resize(verts.size(), Sign::UNCERTAIN);
		v_count.resize(verts.size(), 0);
		for (index_t tid = 0; tid < tet_mesh.sizeTets(); tid++)
			tet_mesh.unmark(tid << 2, TetMesh::TET_MARK::TOUCHED);
	}

	// traverse all faces in the PLC to recover the missing faces
	bool need_recursion = false;

	do
	{
		need_recursion = false;

		for (index_t i = 0; i < plc.numFaces(); i++)
		{
			std::vector<index_t> tets;
			getTetsIntersectingFace(i, tets);

			if (tets.empty())
				continue; // this face is already recovered.
		}
	} while (need_recursion);
}

/**
 * @brief Check if a tetrahedron `tet_idoff` intersects a PLC face `face`.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::tetIntersectsFace(
  index_t tet_idoff, const typename PLC::PLCFace &face)
{
	if (!tet_mesh.isFiniteTet(tet_idoff))
		return false;

	index_t tid = face.triangles[0];
	index_t t0 = plc.triVtx(tid, 0), t1 = plc.triVtx(tid, 1),
	        t2 = plc.triVtx(tid, 2);

	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 4; j++)
		{
			index_t ei = tet_mesh.tetNode(tet_idoff + i);
			index_t ej = tet_mesh.tetNode(tet_idoff + j);
			if (isVtxBounding(ei) || isVtxBounding(ej))
				continue; // the edge is coplanar

			Sign oei = orient3dCached(t0, t1, t2, ei);
			Sign oej = orient3dCached(t0, t1, t2, ej);
			if (oei >= Sign::ZERO && oej >= Sign::ZERO ||
			    oei <= Sign::ZERO && oej <= Sign::ZERO)
				continue; // the inner edge does not crosses the face

			if (segCrossesFace(ei, ej, face))
				return true; // the inner edge crosses one of the triangles
		}

	return false;
}

template <typename Traits>
void ConstraintsRecover<Traits>::getTetsIntersectingFace(
  index_t fid, std::vector<index_t> &tets)
{
	// =========================================================================
	// # Find the tetrahedra intersecting the PLC face (not all)
	// ## pre-condition: all PLC segments are recovered.
	// ## post-condition: find the tetrahedra intersecting the PLC face (not all).

	// TODO how to check the face is already recovered?

	// ## Get and initialize data.

	// Get the PLC face
	const typename PLC::PLCFace &face = plc.face(fid);

	// Get the first bounding edge `e0` of the face
	// - `tri0` is the incident input triangle of `e0`.
	// - `rev0` is the orientation of `e0`.
	// - `orig_e0` is the original edge of `e0` and an edge of `tri0`
	index_t                      tri0    = InvalidIndex;
	const typename PLC::PLCEdge &e0      = plc.boundingEdge(face, 0, &tri0);
	const typename PLC::PLCEdge &orig_e0 = plc.edge(e0.ancestor_id);

	// Get the endpoints of `e0` and `orig_e0`
	index_t e0p0 = e0.ep0(), e0p1 = e0.ep1();
	index_t oe0p0 = orig_e0.ep0(), oe0p1 = orig_e0.ep1();
	// Get the three vertices of `tri0`
	index_t tri_v[3] = {plc.triVtx(tri0, 0), plc.triVtx(tri0, 1),
	                    plc.triVtx(tri0, 2)};
	OMC_EXPENSIVE_ASSERT(
	  (oe0p0 == tri_v[0] || oe0p0 == tri_v[1] || oe0p0 == tri_v[2]) &&
	    (oe0p1 == tri_v[0] || oe0p1 == tri_v[1] || oe0p1 == tri_v[2]),
	  "The original edge is not an edge of the input triangle.");

	// Adjust the order of the vertices of `tri0` to make sure that `oe0p0` and
	// `oe0p1` are the first two vertices of `tri0`.
	tri_v[2] += tri_v[0] + tri_v[1];
	tri_v[0] = oe0p0, tri_v[1] = oe0p1, tri_v[2] = tri_v[2] - oe0p0 - oe0p1;

	// Initialize four vertices of adajcent tetrahedron.
	// First essemble the two endpoints of the first bounding edge.
	index_t              tet_v[4] = {e0p0, e0p1, InvalidIndex, InvalidIndex};
	// Get the incident tets of the first bounding edge
	AuxVector64<index_t> edge_incident_tets;
	tet_mesh.ET(tet_v[0], tet_v[1], edge_incident_tets);

	// ## If the face just has one triangle and is not splitted,
	//    check if the face is already recovered.
	if (face.triangles.size() == 1 && face.bounding_vertices.size() == 3 &&
	    face.flat_vertices.empty())
	{
		// The opposite vertex to the edge `e0`
		index_t opp_v = (tri_v[0] != tet_v[0] && tri_v[0] != tet_v[1])   ? tri_v[0]
		                : (tri_v[1] != tet_v[0] && tri_v[1] != tet_v[1]) ? tri_v[1]
		                                                                 : tri_v[2];
		// Check if the opposite vertex is in the incident tets
		for (index_t tet_idoff : edge_incident_tets)
		{
			if (tet_mesh.tetHasVertex(tet_idoff, opp_v))
			{         // The tetrahedron contains the opposite vertex
				return; // The face is already recovered, exit.
			}
		}
	}

	// ## initialize data for further check

	// initialize vertex orientation and increase count
	// v_orient is initialized to UNCERTAIN and v_count is initialized to zero.
	// so, remember to reset them before and after calling this function.
	for (index_t vid : face.bounding_vertices)
	{
		v_orient[vid] = Sign::ZERO;
		v_count[vid]++;
	}
	for (index_t vid : face.flat_vertices)
	{
		v_orient[vid] = Sign::ZERO;
	}

	// The vector to store intersected tetrahedra
	AuxVector64<index_t> B;

	// ## Find the intersected tetrahedra around flat vertices
	if (!face.flat_vertices.empty())
	{
		// find in VT
		for (index_t vid : face.flat_vertices)
		{
			AuxVector64<index_t> tmp_B;
			tet_mesh.VT(vid, tmp_B);
			B.insert(B.end(), tmp_B.begin(), tmp_B.end());
		}
		// unique
		B.erase(std::unique(B.begin(), B.end()), B.end());
	}

	// ## Find a tet `t0` in ET(e) intersecting the face interior.
	if (!B.empty())               // if `B` is not empty.
		edge_incident_tets.clear(); // skip finding.
	for (index_t tet_idoff : edge_incident_tets)
	{
		// Get the edge opposite to `e0`
		// (`e0` is stored in tet_v[0,1], the oppo edge is stored in tet_v[3,4])
		tet_mesh.oppoTetEdge(tet_idoff, tet_v[0], tet_v[1], tet_v[2], tet_v[3]);

		// Calculate the orientation of two endpoints of the opposite edge with
		// respect to the plane defined by the PLC face.
		//                        ========== plane ===========  query point
		Sign ot2 = orient3dCached(tri_v[0], tri_v[1], tri_v[2], tet_v[2]);
		Sign ot3 = orient3dCached(tri_v[0], tri_v[1], tri_v[2], tet_v[3]);

		OMC_EXPENSIVE_ASSERT(ot2 != Sign::ZERO || ot3 != Sign::ZERO,
		                     "Degenerate tetrahedron.");

		// check if the opposite edge is totally above or below the plane
		if (ot2 != Sign::ZERO && ot2 == ot3)
			continue; // ==> no intersection, skip

		if (ot2 == Sign::ZERO || ot3 == Sign::ZERO) // one endpoint is on the plane
		{
			index_t copl_vid = ot2 == Sign::ZERO ? tet_v[2] : tet_v[3];

			if (isVtxBounding(copl_vid)) // this point is not a bounding vertex,
				continue;                  // so it is outside, skip it.

			const GPoint &tri_p0 = gpnt(tri_v[0]), &tri_p1 = gpnt(tri_v[1]),
			             &tri_p2 = gpnt(tri_v[2]), &copl_p = gpnt(copl_vid);

			int n_max = MaxCompInTriNormal()(
			  AsEP()(tri_p0).data(), AsEP()(tri_p1).data(), AsEP()(tri_p2).data());
			Sign tri_ori  = OrientOn2D()(tri_p0, tri_p1, tri_p2, n_max);
			Sign copl_ori = OrientOn2D()(tri_p0, tri_p1, copl_p, n_max);
			OMC_EXPENSIVE_ASSERT(tri_ori != Sign::ZERO && copl_ori != Sign::ZERO,
			                     "Degenerate triangle.");

			if (tri_ori == copl_ori) // coplanar point is inside the face
			{
				B.push_back(tet_idoff); // find an intersected tetrahedron
				break;                  // exit loop
			}
		}
		if (ot2 != ot3 && segCrossesFace(tet_v[2], tet_v[3], face))
		{                         // the opposite edge crosses the face
			B.push_back(tet_idoff); // find an intersected tetrahedron
			break;                  // exit loop
		}
	}

	// mark found tetrahedra as touched
	for (index_t tet_idoff : B)
		tet_mesh.mark(tet_idoff, TetMesh::TET_MARK::TOUCHED);

	OMC_EXPENSIVE_ASSERT(!B.empty(), "No intersected tetrahedra found.");

	// =========================================================================
	// # Find all the intersected tetrahedra by expanding
	//   from the found tetrahedra.
	// ## pre-condition: part intersected tetrahedra are found
	// ## post-condition: all intersected tetrahedra are found

	auto collectTet = [this, &B](index_t tet_idoff)
	{
		B.push_back(tet_idoff);
		tet_mesh.mark(tet_idoff, TetMesh::TET_MARK::TOUCHED);
	};

	phmap::flat_hash_set<IPair, hash<IPair>> vtx_adj_set;
	plc.buildBoundingVtxAdjSet(face, vtx_adj_set);

	auto areVertsAdj = [&vtx_adj_set](index_t v0, index_t v1) -> bool
	{ return vtx_adj_set.find(unique_pair(v0, v1)) != vtx_adj_set.end(); };

	for (index_t k = 0; k < B.size(); k++)
	{
		index_t tet_idoff = B[k];

		// Traverse the four neighbors of the tetrahedron
		for (index_t j = 0; j < 4; j++)
		{
			index_t nb_idoff = tet_mesh.clipId(tet_mesh.tetNeigh(tet_idoff + j));
			// If the neighbor is not finite or touched, skip
			if (!tet_mesh.isFiniteTet(nb_idoff) ||
			    tet_mesh.isMarked(nb_idoff, TetMesh::TET_MARK::TOUCHED))
				continue;
			// The vertices of the common triangle between two tets.
			index_t cv[3]  = {tet_mesh.tetNode(tet_idoff + ((j + 1) & 3)),
			                  tet_mesh.tetNode(tet_idoff + ((j + 2) & 3)),
			                  tet_mesh.tetNode(tet_idoff + ((j + 3) & 3))};
			// Is the common vertex a bounding vertex?
			bool    bv[3]  = {isVtxBounding(cv[0]), isVtxBounding(cv[1]),
			                  isVtxBounding(cv[2])};
			// POSITIVE = 1, ZERO = 0, NEGATIVE = -1
			int     o3d[3] = {
        static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], cv[0])),
        static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], cv[1])),
        static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], cv[2]))};

			if (bv[0] && bv[1] && bv[2])
			{ // All bounding vertices, this common face is on the PLC face.
				// Thus, the opposite tetrahedron is intersected.
				collectTet(nb_idoff);
			}
			else if (bv[0] && bv[1])
			{ // Only two bounding vertices.
				// The edge connecting the two bounding vertices is inside the PLC face
				// if the two bounding vertices are NOT adjacent, otherwise the edge is
				// a bounding edge.
				// The opposite tetrahedron is intersected in the former case.
				if (!areVertsAdj(cv[0], cv[1]))
					collectTet(nb_idoff);
			}
			else if (bv[1] && bv[2])
			{ // Same as the above case
				if (!areVertsAdj(cv[1], cv[2]))
					collectTet(nb_idoff);
			}
			else if (bv[2] && bv[0])
			{ // Same as the above case
				if (!areVertsAdj(cv[2], cv[0]))
					collectTet(nb_idoff);
			}
			else if (bv[0])
			{ // Only one bounding vertex.
				// Condition: The edge opposite to the bounding vertex in the common
				// triangle crosses the PLC face
				// ==> The common triangle intersects the PLC face
				// ==> The opposite tetrahedron is intersected.
				if (o3d[1] * o3d[2] < 0)
					collectTet(nb_idoff);
			}
			else if (bv[1])
			{ // Same as the above case
				if (o3d[2] * o3d[0] < 0)
					collectTet(nb_idoff);
			}
			else if (bv[2])
			{ // Same as the above case
				if (o3d[0] * o3d[1] < 0)
					collectTet(nb_idoff);
			}
			else
			{ // No bounding vertex.
				// Condition: Any edge of the common triangle crosses the PLC face
				// ==> The common triangle intersects the PLC face
				// ==> The opposite tetrahedron is intersected.
				if (o3d[1] * o3d[2] < 0 || o3d[2] * o3d[0] < 0 || o3d[0] * o3d[1] < 0)
					collectTet(nb_idoff);
			}
		}
	}

	// Check if found tetrahedra penetrate the face and output
	for (index_t tet_idoff : B)
	{
		tet_mesh.unmark(tet_idoff, TetMesh::TET_MARK::TOUCHED);
		index_t v[4] = {
		  tet_mesh.tetNode(tet_idoff + 0), tet_mesh.tetNode(tet_idoff + 1),
		  tet_mesh.tetNode(tet_idoff + 2), tet_mesh.tetNode(tet_idoff + 3)};
		// POSITIVE = 1, ZERO = 0, NEGATIVE = -1
		int ov[4] = {
		  static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], v[0])),
		  static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], v[1])),
		  static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], v[2])),
		  static_cast<int>(orient3dCached(tri_v[0], tri_v[1], tri_v[2], v[3]))};

		if (!((ov[0] >= 0 && ov[1] >= 0 && ov[2] >= 0 && ov[3] >= 0) ||
		      (ov[0] <= 0 && ov[1] <= 0 && ov[2] <= 0 && ov[3] <= 0)))
		{ // the tet penetrate the face, output
			OMC_EXPENSIVE_ASSERT(tetIntersectsFace(tet_idoff, face), "Wrong tet.");
			tets.push_back(tet_idoff);
		}
		// otherwise, the tet is just touching the face, and the face is partially
		// recovered.
	}

	// Clear auxiliary orientation and count
	for (index_t vid : v_cached_orient)
		v_orient[vid] = Sign::UNCERTAIN;
	v_cached_orient.clear();
	for (index_t vid : face.bounding_vertices)
	{
		v_count[vid]  = 0;
		v_orient[vid] = Sign::UNCERTAIN;
	}
	for (index_t vid : face.flat_vertices)
		v_orient[vid] = Sign::UNCERTAIN;
}

/**
 * @brief Compute orient3d for four vertices and cache the result.
 * Use a cached value if available to avoid redundant calculations.
 * @param v_0_1_2 the first three vertices define a plane
 * @param v3 the fourth query vertex
 * @return The orientation of v3 with respect to the plane defined by v_0_1_2.
 */
template <typename Traits>
Sign ConstraintsRecover<Traits>::orient3dCached(index_t v0, index_t v1,
                                                index_t v2, index_t v3)
{
	if (v_orient[v3] != Sign::UNCERTAIN)
		return v_orient[v3];
	v_orient[v3] = Orient3D()(gpnt(v0), gpnt(v1), gpnt(v2), gpnt(v3));
	v_cached_orient.push_back(v3);
	return v_orient[v3];
}

/**
 * @brief Checks if a segment crosses any triangle within a given PLC face.
 * @param s0 The index of the first point of the segment.
 * @param s1 The index of the second point of the segment.
 * @param face The face containing the triangles to check for intersection.
 * @return True if the segment crosses any triangle in the face.
 * @note Assume that segment crosses the support plane of the PLC face.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::segCrossesFace(
  index_t s0, index_t s1, const typename PLC::PLCFace &face) const
{
	const GPoint &p0 = gpnt(s0), &p1 = gpnt(s1);

	for (index_t tid : face.triangles)
	{
		const GPoint &v0 = gpnt(plc.triVtx(tid, 0)), &v1 = gpnt(plc.triVtx(tid, 1)),
		             &v2 = gpnt(plc.triVtx(tid, 2));
		// We have known that the segment crosses the support plane,
		// so, we skip checking orientation of p0, p1 w.r.t the plane.

		// We check whether the segment crosses the triangle.
		// s crosses t (borders included), if the signs of the three tetrahedra
		// obtained combining s with the three edges of t are all equal.
		Sign o1 = Orient3D()(p0, p1, v0, v1);
		Sign o2 = Orient3D()(p0, p1, v1, v2);
		if ((o1 > Sign::ZERO && o2 < Sign::ZERO) ||
		    (o1 < Sign::ZERO && o2 > Sign::ZERO))
			continue;
		Sign o3 = Orient3D()(p0, p1, v2, v0);
		if ((o1 > Sign::ZERO && o3 < Sign::ZERO) ||
		    (o1 < Sign::ZERO && o3 > Sign::ZERO))
			continue;
		if ((o2 > Sign::ZERO && o3 < Sign::ZERO) ||
		    (o2 < Sign::ZERO && o3 > Sign::ZERO))
			continue;
		// OPT orientation can be cached locally

		return true;
	}
	return false;
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