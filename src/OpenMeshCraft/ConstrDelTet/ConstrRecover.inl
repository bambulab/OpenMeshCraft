#pragma once

#include "ConstrRecover.h"

namespace OMC {

// In [Robust CDT 2023], some predicates are implemented in floating-point
// numbers, I reimplemnted them in exact predicates. Define the below macro to
// use the exact predicates.
// TODO Exact predicates with implicit points are not implemented yet.
// #define OMC_SEGMENT_RECOVERY_EXACT_PRED

/**
 * @brief Initialize with the Delaunay tetrahedral mesh and the input
 * constrained triangles. Prepare for the constraits recovery.
 * @param _tet_mesh the Delaunay tetrahedral mesh
 * @param _plc the input constrained piecewise linear complex
 */
template <typename Traits>
ConstraintsRecover<Traits>::ConstraintsRecover(
  std::vector<GPoint *> &_verts, std::vector<PntArena> &_pnt_arenas,
  TetMesh &_tet_mesh, PLC &_plc, bool _verbose)
  : verts(_verts)
  , pnt_arenas(_pnt_arenas)
  , tet_mesh(_tet_mesh)
  , plc(_plc)
  , verbose(_verbose)
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
		const PLCEdge &e = plc.edge(eid);
		if (e.type != PLCEdgeType::FLAT_EDGE &&
		    !tet_mesh.edgeExists(e.ep0(), e.ep1()))
		{
			missing_segments.push_back(eid);
		}
	}

	// Once a segment is split, new missing segments may appear near it.
	// So, mark adjacent vertices as `TO_CHECK`, and check them after a loop.

	// clear the `TO_CHECK` mark for all vertices
	for (index_t vid = 0; vid < tet_mesh.sizeVerts(); vid++)
		tet_mesh.unmark(vid, VTX_MARK::TO_CHECK);

	size_t split_count = 0;

	// Main loop: split missing segments to recover them.
	while (!missing_segments.empty())
	{
		// Split the existing constrained segment
		while (!missing_segments.empty())
		{
			// Get the constrained segment to split
			index_t eid = missing_segments.back();
			missing_segments.pop_back();
			const PLCEdge &e   = plc.edge(eid);
			index_t        ep0 = e.ep0(), ep1 = e.ep1();

			// Check if the segment is still missing
			if (tet_mesh.edgeExists(ep0, ep1))
				continue;

			// Split the segment
			index_t new_vid = splitMissingSegment(eid);

			// Touch the neighbor vertices
			// New missing edges will appear near touched vertices
			AuxVector64<index_t> local_vv;
			local_vv.push_back(ep0);
			local_vv.push_back(ep1);
			tet_mesh.VV(new_vid, local_vv);
			for (index_t vid : local_vv)
				tet_mesh.mark(vid, VTX_MARK::TO_CHECK);

			// log and output
			split_count++;
			if (verbose && split_count % 100 == 0)
			{
				std::cout << std::format(
				  "\r{} segments are split. {} segments are missing.", split_count,
				  missing_segments.size());
			}
		}
		// Find new missing edges around touched vertices
		for (index_t eid = 0; eid < plc.numEdges(); eid++)
		{
			const PLCEdge &e = plc.edge(eid);
			if (!is_valid_idx(e.child_id) && e.type != PLCEdgeType::FLAT_EDGE &&
			    (tet_mesh.isMarked(e.ep0(), VTX_MARK::TO_CHECK) ||
			     tet_mesh.isMarked(e.ep1(), VTX_MARK::TO_CHECK)) &&
			    !tet_mesh.edgeExists(e.ep0(), e.ep1()))
			{
				missing_segments.push_back(eid);
			}
		}
		// clear the `TO_CHECK` mark for all vertices
		for (index_t vid = 0; vid < tet_mesh.sizeVerts(); vid++)
			tet_mesh.unmark(vid, VTX_MARK::TO_CHECK);
	}
	if (verbose) // output a new line
		std::cout << std::endl;

	tet_mesh.removeDeletedTets();

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// check if all segments are recovered
	for (index_t eid = 0; eid < plc.numEdges(); eid++)
	{
		const PLCEdge &e = plc.edge(eid);
		if (!is_valid_idx(e.child_id) && e.type != PLCEdgeType::FLAT_EDGE)
		{
			OMC_ASSERT(tet_mesh.edgeExists(e.ep0(), e.ep1()), "Missing segment.");
		}
	}
#endif
}

template <typename Traits>
index_t ConstraintsRecover<Traits>::splitMissingSegment(index_t eid)
{
	index_t new_vid  = InvalidIndex;
	index_t curr_tet = InvalidIndex;

	PLCEdge &edge = plc.edge(eid);

	if (edge.type == PLCEdgeType::BOTH_ACUTE_VERTEX)
	{
		curr_tet = TetMesh::toIdOff(tet_mesh.incTet(edge.ep0()));
		new_vid  = splitSegment_BothAcuteVertex(eid);
	}
	else // ONE_ACUTE_VERTEX or NO_ACUTE_VERTEX
	{
		index_t ref_vid;
		findReferenceEncroachingPoint(eid, ref_vid, curr_tet);

		OMC_EXPENSIVE_ASSERT(is_valid_idx(ref_vid),
		                     "Could not find a valid reference encroaching point.");

		if (edge.type == PLCEdgeType::NO_ACUTE_VERTEX)
			new_vid = splitSegment_NoAcuteVertex(eid, ref_vid);
		else // ONE_ACUTE_VERTEX
			new_vid = splitSegment_OneAcuteVertex(eid, ref_vid);
	}

	// insert the splitting point into the Delaunay tetrahedral mesh
	DelTet DT(tet_mesh);
	DT.insertVertex(new_vid, curr_tet);

	OMC_EXPENSIVE_ASSERT(DT.localVerify(new_vid),
	                     "Invalid Delaunay tetrahedralization.");
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
 * @note
 * Rely on mark `TOUCHED` to avoid visiting the same tetrahedron and the
 * same vertex multiple times.
 * Relay on mark `ENCROACHED` to mark the encroaching vertices.
 * Not thread safe.
 */
template <typename Traits>
void ConstraintsRecover<Traits>::findReferenceEncroachingPoint(
  index_t eid, index_t &ref_vid, index_t &ref_tid) const
{
	AuxVector64<index_t> encroach_tets;
	const PLCEdge       &edge = plc.edge(eid);

	// find tetrahedra adjacent to the first endpoint `ep0`
	tet_mesh.VT(edge.ep0(), encroach_tets);
	// and mark the tetrahedra as touched
	for (index_t tet_idoff : encroach_tets)
		tet_mesh.mark(tet_idoff, TET_MARK::TOUCHED);

	tet_mesh.mark(edge.ep0(), VTX_MARK::TOUCHED);
	tet_mesh.mark(edge.ep1(), VTX_MARK::TOUCHED);

	const GPoint &p0    = gpnt(edge.ep0());
	const GPoint &p1    = gpnt(edge.ep1());
	const GPoint *ref_p = nullptr;
	ref_vid             = InvalidIndex;
	ref_tid             = InvalidIndex;

	for (index_t i = 0; i < encroach_tets.size(); i++)
	{
		index_t tet_idoff = encroach_tets[i];

		// check if the tetrahedron has an encroaching point
		for (index_t j = 0; j < 4; j++)
		{
			index_t vid = tet_mesh.tetNode(tet_idoff + j);
			if (tet_mesh.isMarked(vid, VTX_MARK::TOUCHED) ||
			    tet_mesh.isMarked(vid, VTX_MARK::ENCROACHED))
				continue;
			tet_mesh.mark(vid, VTX_MARK::TOUCHED);
			const GPoint &curr_p = gpnt(vid);

			// check if the vertex is encroaching
			if (inSphere(p0, p1, curr_p))
			{
				tet_mesh.mark(vid, VTX_MARK::ENCROACHED);
				// check if it is the reference encroaching point
				if (ref_vid == InvalidIndex || largerSphere(p0, p1, curr_p, *ref_p))
				{
					ref_vid = vid;
					ref_tid = tet_idoff;
					ref_p   = &curr_p;
				}
			}
		}

		// clang-format off
		const int is_encroached[] = {
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff), VTX_MARK::ENCROACHED),
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff + 1), VTX_MARK::ENCROACHED),
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff + 2), VTX_MARK::ENCROACHED),
			tet_mesh.isMarked(tet_mesh.tetNode(tet_idoff + 3), VTX_MARK::ENCROACHED),
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

			if (tet_mesh.isMarked(neigh_idoff, TET_MARK::TOUCHED) ||
			    !tet_mesh.isFiniteTet(neigh_idoff))
				continue;

			if (total_encroached - is_encroached[j] > 0)
			{
				encroach_tets.push_back(TetMesh::clipId(neigh_idoff));
				tet_mesh.mark(neigh_idoff, TET_MARK::TOUCHED);
			}
		}
	}

	// clear all marks
	tet_mesh.unmark(edge.ep0(), VTX_MARK::TOUCHED);
	tet_mesh.unmark(edge.ep1(), VTX_MARK::TOUCHED);
	for (index_t idoff : encroach_tets)
	{
		tet_mesh.unmark(idoff, TET_MARK::TOUCHED);
		for (index_t j = 0; j < 4; j++)
		{
			index_t vid = tet_mesh.tetNode(idoff + j);
			tet_mesh.unmark(vid, VTX_MARK::TOUCHED);
			tet_mesh.unmark(vid, VTX_MARK::ENCROACHED);
		}
	}
}

/**
 * @brief Split the constrained edge `eid` at the middle point.
 *
 * This split strategy is used to split segment with two acute vertices, and
 * generating two sub-edges with type `ONE_ACUTE_VERTEX`.
 *
 * @return The index to the splitting point.
 */
template <typename Traits>
index_t ConstraintsRecover<Traits>::splitSegment_BothAcuteVertex(index_t eid)
{
	const PLCEdge &edge    = plc.edge(eid);
	// Get the new point
	IPoint_LNC     new_pnt = middlePoint_bothAc(edge);
	// Add the new point
	index_t        new_vid = newVtx(new_pnt);
	// Split edge by the new point
	plc.splitPLCEdge(eid, new_vid);

	return new_vid;
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
index_t ConstraintsRecover<Traits>::splitSegment_NoAcuteVertex(index_t eid,
                                                               index_t ref_vid)
{
	const PLCEdge &edge = plc.edge(eid);

	const GPoint &ep0_pnt = gpnt(edge.ep0());
	const GPoint &ep1_pnt = gpnt(edge.ep1());
	const GPoint &ref_pnt = gpnt(ref_vid);

	IPoint_LNC new_pnt;

	if (isLessThanHalfDistance(ep0_pnt, ref_pnt, ep1_pnt))
	{ // The `ref_pnt` is closer to the endpoint `ep0`, and the distance between
		// `ref_pnt` and `ep0` is less than half the distance between `ep0` and
		// `ep1`.
		new_pnt = lineSphereIntersection_noAc(eid, false, ref_vid);
	}
	else if (isLessThanHalfDistance(ep1_pnt, ref_pnt, ep0_pnt))
	{ // The `ref_pnt` is closer to the endpoint `ep1`, and the distance between
		// `ref_pnt` and `ep1` is less than half the distance between `ep0` and
		// `ep1`.
		new_pnt = lineSphereIntersection_noAc(eid, true, ref_vid);
	}
	else
	{ // The distances between both <`ref_pnt`, `ep0`> and <`ref_pnt`, `ep1`>
		// are larger than half the distance between `ep0` and `ep1`.
		// Split the segment at the middle point.
		new_pnt = middlePoint_bothAc(edge);
	}

	// Add the new point
	index_t new_vid = newVtx(new_pnt);
	// Split edge by the new point
	plc.splitPLCEdge(eid, new_vid);

	return new_vid;
}

/**
 * @brief Split the constrained edge `eid` that has only one acute vertex.
 * @param eid The constrained edge to split.
 * @param ref_vid the reference encroaching point.
 * @return the new splitting point.
 * @see The strategy is described in Section 3.3 of [Robust CDT].
 */
template <typename Traits>
index_t ConstraintsRecover<Traits>::splitSegment_OneAcuteVertex(index_t eid,
                                                                index_t ref_vid)
{
	const PLCEdge &edge = plc.edge(eid);

	IPoint_LNC new_pnt;

	new_pnt = lineSphereIntersection_oneAc(eid, ref_vid);

	if (isLessThanDistance(new_pnt, gpnt(edge.ep1()), gpnt(ref_vid)))
	{ // The new point is closer to the non-acute endpoint `ep1` than the
		// reference encroaching point, we should switch to another split strategy
		// (described in Section 3.3 in [Robust CDT]), but it is not really
		// necessary. Just using midpoint provides better performances
		new_pnt = middlePoint_bothAc(edge);
	}

	// Add the new point
	index_t new_vid = newVtx(new_pnt);
	// Split edge by the new point
	plc.splitPLCEdge(eid, new_vid);

	return new_vid;
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
		v_reindex.clear();

		v_orient.resize(verts.size(), Sign::UNCERTAIN);
		v_count.resize(verts.size(), 0);
		v_reindex.resize(verts.size(), InvalidIndex);

		for (index_t tid = 0; tid < tet_mesh.sizeTets(); tid++)
			tet_mesh.unmark(TetMesh::toIdOff(tid), TET_MARK::TOUCHED);
	}

	// traverse all faces in the PLC to recover the missing faces
	bool   need_recursion  = false;
	size_t recover_succeed = 0, recover_fail = 0;

	do
	{
		need_recursion = false;

		for (index_t i = 0; i < plc.numFaces(); i++)
		{
			std::vector<index_t> tets;
			getTetsIntersectingFace(i, tets);

			if (tets.empty())
				continue; // this face is already recovered.

			bool succeed = false, expanded = false;
			recoverFace_cavityExpanding(i, tets, succeed, expanded);

			// log and output
			if (succeed)
				recover_succeed++;
			else
				recover_fail++;
			if (verbose)
				std::cout << std::format(
				  "\r{} faces are recovered. {} faces are missing.", recover_succeed,
				  recover_fail);

			// A recovered face may be destroyed by the recovery of another face
			// when expansion is needed.
			// OPT: Record relation between tet face and PLC face to detect destroyed
			// faces more efficiently.
			if (expanded)
				need_recursion = true;
		}
	} while (need_recursion && recover_fail == 0);
	if (verbose) // output a new line
	{
		std::cout << std::endl;
		if (recover_fail > 0)
			std::cout << "Fail to recover " << recover_fail << " faces." << std::endl;
	}
}

/**
 * @brief Two points `a` and `b` form a smallest (diametral) sphere, check if
 * the query point `c` lies inside or touches the sphere.
 * @return True if the point lies inside or touches the sphere, false otherwise.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::inSphere(const GPoint &a, const GPoint &b,
                                          const GPoint &c)
{
#ifdef OMC_SEGMENT_RECOVERY_EXACT_PRED
	return InSphere()(a, b, c) >= Sign::ZERO;
#else
	EPoint a_ep = ToEP()(a), b_ep = ToEP()(b), c_ep = ToEP()(c);
	return (c_ep - a_ep).sqrnorm() + (c_ep - b_ep).sqrnorm() <=
	       (a_ep - b_ep).sqrnorm();
#endif
}

/**
 * @brief Points `a`, `b` and `c` form a smallest sphere S(abc), and points
 * `a`, `b` and `d` form another smallest sphere S(abd). We want to know if
 * S(abc) is larger than S(abd).
 * @return true if S(abc) is larger than S(abd), false otherwise.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::largerSphere(const GPoint &a, const GPoint &b,
                                              const GPoint &c, const GPoint &d)
{
#ifdef OMC_SEGMENT_RECOVERY_EXACT_PRED
	return InSphere().largerSphere(a, b, c, d) == Sign::POSITIVE;
#else
	// calculate vectors between points
	EPoint a_ep = ToEP()(a), b_ep = ToEP()(b), c_ep = ToEP()(c), d_ep = ToEP()(d);
	Vec3   ac = (c_ep - a_ep), bc = (c_ep - b_ep);
	Vec3   ad = (d_ep - a_ep), bd = (d_ep - b_ep);

	// let the angle between ac and bc be <abc>, and the angle between ad and bd
	// be <abd>.
	// cos(<abc>) = (ac dot bc) / (|ac| * |bc|), so as cos(<abd>).
	// S(abc) is larger than S(abd) if and only if cos(<abc>) < cos(<abd>).

	NT len_c = ac.sqrnorm() * bc.sqrnorm();
	NT len_d = ad.sqrnorm() * bd.sqrnorm();
	NT dot_c = ac.dot(bc);
	NT dot_d = ad.dot(bd);

	// cos(<abc>) < cos(<abd>) is equivalent to the below inequality.
	return (dot_d * dot_d) * len_c < (dot_c * dot_c) * len_d;
#endif
}

/**
 * @brief Check if the distance between `a` and `b` is less than the distance
 * between `a` and `c`.
 * @return true if less, false otherwise.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::isLessThanDistance(const GPoint &a,
                                                    const GPoint &b,
                                                    const GPoint &c)
{
#ifdef OMC_SEGMENT_RECOVERY_EXACT_PRED
	return SquaredDistance3D()(a, b, c) == Sign::NEGATIVE;
#else
	EPoint a_ep = ToEP()(a), b_ep = ToEP()(b), c_ep = ToEP()(c);
	return (b_ep - a_ep).sqrnorm() < (c_ep - a_ep).sqrnorm();
#endif
}

/**
 * @brief Check if the distance between `a` and `b` is less than half the
 * distance between `a` and `c`.
 * @return true if less, false otherwise.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::isLessThanHalfDistance(const GPoint &a,
                                                        const GPoint &b,
                                                        const GPoint &c)
{
#ifdef OMC_SEGMENT_RECOVERY_EXACT_PRED
	// scale the squared distance between a and b by 4 to avoid square root.
	return SquaredDistance3D()(a, b, c, /*ab_scale*/ 4) == Sign::NEGATIVE;
#else
	EPoint a_ep = ToEP()(a), b_ep = ToEP()(b), c_ep = ToEP()(c);
	return (b_ep - a_ep).sqrnorm() * 4 < (c_ep - a_ep).sqrnorm();
#endif
}

/**
 * @brief Given original PLC edge (oep0, oep1) and a sub-edge (ep0, ep1) of the
 * original one, find the interpolation parameter t0 and t1 such that the
 * sub-edge is the interpolation of the original edge:
 * ep0 = oep0 + t0 * (oep1 - oep0),
 * ep1 = oep0 + t1 * (oep1 - oep0).
 *
 * @param oep0 one endpoint of the original PLC edge
 * @param oep1 the other endpoint of the original PLC edge
 * @param ep0	one endpoint of the sub-edge
 * @param ep1 the other endpoint of the sub-edge
 * @return A pair of interpolation parameters t0 and t1.
 */
template <typename Traits>
std::pair<double, double>
ConstraintsRecover<Traits>::getInterpolateT(index_t oep0, index_t oep1,
                                            index_t ep0, index_t ep1) const
{
	double t0 = -1.0, t1 = -1.0;

	// calculate the interpolation parameter for `ep0`
	if (ep0 == oep0)
		t0 = 0.0;
	else if (ep0 == oep1)
		t0 = 1.0;
	else if (&(gpnt(ep0).LNC().P()) == &gpnt(oep0))
		t0 = gpnt(ep0).LNC().T();
	else if (&(gpnt(ep0).LNC().P()) == &gpnt(oep1))
		t0 = 1.0 - gpnt(ep0).LNC().T();
	else
	{
		OMC_ASSERT(false, "The sub-edge is not a part of the original edge.");
	}

	// calculate the interpolation parameter for `ep1`
	if (ep1 == oep0)
		t1 = 0.0;
	else if (ep1 == oep1)
		t1 = 1.0;
	else if (&(gpnt(ep1).LNC().P()) == &gpnt(oep0))
		t1 = gpnt(ep1).LNC().T();
	else if (&(gpnt(ep1).LNC().P()) == &gpnt(oep1))
		t1 = 1.0 - gpnt(ep1).LNC().T();
	else
	{
		OMC_ASSERT(false, "The sub-edge is not a part of the original edge.");
	}

	OMC_EXPENSIVE_ASSERT(t0 >= 0.0 && t0 <= 1.0 && t1 >= 0.0 && t1 <= 1.0,
	                     "Invalid interpolation parameters.");
	return std::pair<double, double>(t0, t1);
}

/**
 * @brief Get the middle point of a PLC edge represented by LNC implicit point.
 * This function is used to split a PLC edge with two acute vertices.
 * @param e The given PLC edge.
 * @note bothAc means both acute vertices.
 * @return IPoint_LNC The middle point of the edge.
 */
template <typename Traits>
auto ConstraintsRecover<Traits>::middlePoint_bothAc(const PLCEdge &e) const
  -> IPoint_LNC
{
	OMC_EXPENSIVE_ASSERT(!is_valid_idx(e.child_id), "The edge is already split.");

	index_t ep0 = e.ep0(), ep1 = e.ep1();

	if (is_valid_idx(e.ancestor_id)) // The edge is a sub-edge of a split edge.
	{
		const PLCEdge &oe   = plc.edge(e.ancestor_id);
		index_t        oep0 = oe.ep0(), oep1 = oe.ep1();

		auto [t0, t1] = getInterpolateT(oep0, oep1, ep0, ep1);
		return CreateLNC()(gpnt(oep0), gpnt(oep1), (t0 + t1) * 0.5);
	}
	else // The edge is not split yet.
	{
		return CreateLNC()(gpnt(ep0), gpnt(ep1), /*interpolation T*/ 0.5);
	}
}

/**
 * @brief Get the intersection point between the line and the sphere,
 * represented as an LNC implicit point.
 *
 * - The line is defined by the constrained edge `eid`.
 *
 * - The sphere is centered at one endpoint (determined by `reverse`) of the
 * edge, with the radius being the distance between the endpoint and the
 * reference encroaching point `ref_vid`.
 *
 * @param [in] eid The index of the constrained edge.
 * @param [in] reverse TRUE if the reference encroaching point is closer to the
 * endpoint `ep1`, FALSE if it is closer to the endpoint `ep0`. The sphere
 * centers at the endpoint that is closer to the reference encroaching point.
 * @param [in] ref_vid The index of the reference encroaching point.
 * @note `noAc` means no acute vertex.
 * @return IPoint_LNC The intersection point represented in LNC.
 */
template <typename Traits>
auto ConstraintsRecover<Traits>::lineSphereIntersection_noAc(
  index_t eid, bool reverse, index_t ref_vid) const -> IPoint_LNC
{
	const PLCEdge &e   = plc.edge(eid);
	// Get the endpoints of the edge and its original edge.
	index_t        ep0 = e.ep0(), ep1 = e.ep1();
	index_t        oep0 = InvalidIndex, oep1 = InvalidIndex;
	if (is_valid_idx(e.ancestor_id))
	{
		const PLCEdge &oe = plc.edge(e.ancestor_id);
		oep0 = oe.ep0(), oep1 = oe.ep1();
	}
	else
	{
		oep0 = ep0, oep1 = ep1;
	}
	OMC_EXPENSIVE_ASSERT(gpnt(oep0).is_explicit() && gpnt(oep1).is_explicit(),
	                     "Input points contain implicit points.");
	// Get the vectors of related points.
	Vec3 oe0_v    = AsEP()(gpnt(oep0)).as_vec();
	Vec3 oe1_v    = AsEP()(gpnt(oep1)).as_vec();
	Vec3 ref_v    = ToEP()(gpnt(ref_vid)).as_vec();
	Vec3 end_v    = ToEP()(gpnt(reverse ? ep1 : ep0)).as_vec();
	// Get the interpolation parameters
	auto [t0, t1] = getInterpolateT(oep0, oep1, ep0, ep1);
	// Parameterize the sphere radius to the original segment
	double radius_t =
	  std::sqrt((ref_v - end_v).sqrnorm() / (oe1_v - oe0_v).sqrnorm());
	// Get the parameter of the intersection point
	double t = reverse ? t1 - radius_t : t0 + radius_t;
	// Check if the intersection point is inside the edge
	if (t <= t0 || t >= t1)
	{ // if no (maybe caused by numerical error), return the middle point
		t = (t0 + t1) * 0.5;
	}

	return CreateLNC()(gpnt(oep0), gpnt(oep1), t);
}

/**
 * @brief  Get the intersection point between the line and the sphere,
 * represented as an LNC implicit point.
 *
 * - The line is defined by the constrained edge `eid`.
 *
 * - The sphere is centered at the acute endpoint of the edge, with the radius
 * being the distance between the acute endpoint and the reference encroaching
 * point `ref_vid`.
 *
 * - Acute endpoint is always put in the first position.
 *
 * @param [in] eid The index of the constrained edge.
 * @param [in] ref_vid The index of the reference encroaching point.
 * @note `oneAc` means one acute vertex.
 * @return IPoint_LNC The intersection point represented in LNC.
 */
template <typename Traits>
auto ConstraintsRecover<Traits>::lineSphereIntersection_oneAc(
  index_t eid, index_t ref_vid) const -> IPoint_LNC
{
	const PLCEdge &e   = plc.edge(eid);
	// Get the endpoints of the edge and its original edge.
	index_t        ep0 = e.ep0(), ep1 = e.ep1();
	index_t        acute_vid = e.acute_vid;
	index_t        oep0, oep1;
	if (is_valid_idx(e.ancestor_id))
	{
		const PLCEdge &oe = plc.edge(e.ancestor_id);
		oep0 = oe.ep0(), oep1 = oe.ep1();
	}
	else
	{
		oep0 = ep0, oep1 = ep1;
	}
	OMC_EXPENSIVE_ASSERT(
	  acute_vid == oep0 || acute_vid == oep1,
	  "The acute vertex is not an endpoint of the original edge.");
	OMC_EXPENSIVE_ASSERT(gpnt(oep0).is_explicit() && gpnt(oep1).is_explicit(),
	                     "Input points contain implicit points.");
	if (acute_vid == oep1) // swap the acute vertex to oep0
		std::swap(oep0, oep1);
	// Get the vectors of related points.
	Vec3 oe0_v    = AsEP()(gpnt(oep0)).as_vec();
	Vec3 oe1_v    = AsEP()(gpnt(oep1)).as_vec();
	Vec3 ref_v    = ToEP()(gpnt(ref_vid)).as_vec();
	// Get the interpolation parameters
	auto [t0, t1] = getInterpolateT(oep0, oep1, ep0, ep1);
	// Parameterize the sphere radius to the original segment
	double radius_t =
	  std::sqrt((ref_v - oe0_v).sqrnorm() / (oe1_v - oe0_v).sqrnorm());
	// Ensure that the intersection point is inside the edge
	double eps = (t1 - t0) * 0.2;
	if (radius_t <= (t0 + eps) || radius_t >= (t1 - eps))
	{ // Otherwise return the middle point
		radius_t = (t0 + t1) * 0.5;
	}

	return CreateLNC()(gpnt(oep0), gpnt(oep1), radius_t);
}

/**
 * @brief Finds the tetrahedra intersecting a given PLC face.
 *
 * This function identifies the tetrahedra that intersect with a specified PLC
 * face. It assumes that all PLC segments have already been recovered.
 *
 * @param fid The index of the PLC face to check for intersections.
 * @param tets A vector to store the indices of the intersecting tetrahedra.
 *
 * @pre All PLC segments are recovered.
 * @post The vector `tets` contains the indices of the tetrahedra intersecting
 * the PLC face.
 *
 * @details
 * The function performs the following main steps:
 * 1. Finds part of tetrahedra intersecting the face around flat vertices or
 * around a bounding edge.
 * 2. Expands the search to find all intersected tetrahedra by traversing
 * neighbors.
 * 3. Checks if found tetrahedra penetrate the face and outputs the results.
 */
template <typename Traits>
void ConstraintsRecover<Traits>::getTetsIntersectingFace(
  index_t fid, std::vector<index_t> &tets)
{
	// =========================================================================
	// # Find the tetrahedra intersecting the PLC face (not all)
	// ## pre-condition: all PLC segments are recovered.
	// ## post-condition: find the tetrahedra intersecting the PLC face (not all).

	// ## Get and initialize data.

	// Get the PLC face
	const PLCFace &face = plc.face(fid);

	// Get the first bounding edge `e0` of the face
	// - `tri0` is the incident input triangle of `e0`.
	// - `rev0` is the orientation of `e0`.
	// - `orig_e0` is the original edge of `e0` and an edge of `tri0`
	index_t        tri0 = InvalidIndex;
	const PLCEdge &e0   = plc.boundingEdge(face, 0, &tri0);
	const PLCEdge &orig_e0 =
	  is_valid_idx(e0.ancestor_id) ? plc.edge(e0.ancestor_id) : e0;

	// Get the endpoints of `e0` and `orig_e0`
	index_t e0p0 = e0.ep0(), e0p1 = e0.ep1();
	index_t oe0p0 = orig_e0.ep0(), oe0p1 = orig_e0.ep1();
	// Get the three vertices of `tri0`
	index_t tri_v[3] = {plc.triVtx(tri0, 0), plc.triVtx(tri0, 1),
	                    plc.triVtx(tri0, 2)};
	int     n_max    = -1; // the maximal component of triangle normal.
	Sign    tri_ori  = Sign::UNCERTAIN; // triangle vertex orientation.
	OMC_EXPENSIVE_ASSERT(
	  (oe0p0 == tri_v[0] || oe0p0 == tri_v[1] || oe0p0 == tri_v[2]) &&
	    (oe0p1 == tri_v[0] || oe0p1 == tri_v[1] || oe0p1 == tri_v[2]),
	  "The original edge is not an edge of the input triangle.");

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// check if all bounding edges are recovered.
	for (const BoundingEdge &be : face.bounding_edges)
	{
		for (index_t i = be.range.start; i < be.range.start + be.range.size; i++)
		{
			const PLCEdge &edge = plc.subEdge(i);
			OMC_ASSERT(tet_mesh.edgeExists(edge.ep0(), edge.ep1()),
			           "The edge is not recovered.");
		}
	}
#endif

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

	auto isVtxBounding = [this](index_t vid) { return v_count[vid] > 0; };

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
		tet_mesh.oppoEdge(tet_idoff, tet_v[0], tet_v[1], tet_v[2], tet_v[3]);

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

			if (!isVtxBounding(copl_vid)) // this point is not a bounding vertex,
				continue;                   // so it is outside, skip it.

			const GPoint &tri_p0 = gpnt(tri_v[0]), &tri_p1 = gpnt(tri_v[1]),
			             &tri_p2 = gpnt(tri_v[2]), &copl_p = gpnt(copl_vid);

			if (n_max == -1)
			{
				n_max = MaxCompInTriNormal()(
				  AsEP()(tri_p0).data(), AsEP()(tri_p1).data(), AsEP()(tri_p2).data());
				tri_ori = OrientOn2D()(tri_p0, tri_p1, tri_p2, n_max);
			}

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
		tet_mesh.mark(tet_idoff, TET_MARK::TOUCHED);

	OMC_EXPENSIVE_ASSERT(!B.empty(), "No intersected tetrahedra found.");

	// =========================================================================
	// # Find all the intersected tetrahedra by expanding
	//   from the found tetrahedra.
	// ## pre-condition: part intersected tetrahedra are found
	// ## post-condition: all intersected tetrahedra are found

	auto collectTet = [this, &B](index_t tet_idoff)
	{
		B.push_back(tet_idoff);
		tet_mesh.mark(tet_idoff, TET_MARK::TOUCHED);
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
			index_t nb_idoff = TetMesh::clipId(tet_mesh.tetNeigh(tet_idoff + j));
			// If the neighbor is not finite or touched, skip
			if (!tet_mesh.isFiniteTet(nb_idoff) ||
			    tet_mesh.isMarked(nb_idoff, TET_MARK::TOUCHED))
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
		tet_mesh.unmark(tet_idoff, TET_MARK::TOUCHED);
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

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// check if all bounding and flat vertices are traversed.
	for (index_t tet_idoff : B)
	{
		index_t v[4] = {
		  tet_mesh.tetNode(tet_idoff + 0), tet_mesh.tetNode(tet_idoff + 1),
		  tet_mesh.tetNode(tet_idoff + 2), tet_mesh.tetNode(tet_idoff + 3)};
		v_count[v[0]] = v_count[v[1]] = v_count[v[2]] = v_count[v[3]] = 1;
	}
	for (index_t vid : face.bounding_vertices)
	{
		OMC_ASSERT(v_count[vid], "missing bounding vertex in cavity");
	}
	for (index_t vid : face.flat_vertices)
	{
		OMC_ASSERT(v_count[vid], "missing flat vertex in cavity");
	}
	for (index_t tet_idoff : B)
	{
		index_t v[4] = {
		  tet_mesh.tetNode(tet_idoff + 0), tet_mesh.tetNode(tet_idoff + 1),
		  tet_mesh.tetNode(tet_idoff + 2), tet_mesh.tetNode(tet_idoff + 3)};
		v_count[v[0]] = v_count[v[1]] = v_count[v[2]] = v_count[v[3]] = 0;
	}
#endif
}

template <typename Traits>
void ConstraintsRecover<Traits>::recoverFace_cavityExpanding(
  index_t fid, const std::vector<index_t> &tets, bool &succeed, bool &expanded)
{
	// Get the PLC face
	const PLCFace &face = plc.face(fid);

	{ // Initialize vertex orientation and count
		index_t tid = face.triangles[0];
		index_t tv0 = plc.triVtx(tid, 0), tv1 = plc.triVtx(tid, 1),
		        tv2 = plc.triVtx(tid, 2);

		for (index_t vid : face.bounding_vertices)
		{
			v_orient[vid] = Sign::ZERO;
			v_count[vid]  = 0;
		}
		for (index_t vid : face.flat_vertices)
		{
			v_orient[vid] = Sign::ZERO;
			v_count[vid]  = 0;
		}

		for (index_t tet_idoff : tets)
		{
			for (index_t j = 0; j < 4; j++)
			{
				index_t vid  = tet_mesh.tetNode(tet_idoff + j);
				v_count[vid] = 0;
				orient3dCached(tv0, tv1, tv2, vid);
			}
		}
	}

	// =========================================================================
	// # Divide cavity into top and bottom half cavity
	// ## pre-condition: all tetrahedra intersecting the PLC face are found.
	// ## post-condition: cavity vertices and boundary faces are divided.

	// touch all tetrahedra in `tets` for dividing cavity
	for (index_t tet_idoff : tets)
		tet_mesh.mark(tet_idoff, TET_MARK::TOUCHED);

	// divide cavity into top and bottom half cavity.

	// indices of the vertices of the two half cavities.
	// - vertices on the PLC face belong to both sides.
	AuxVector64<index_t> top_vertices, bottom_vertices;

	// boundary faces of the two half cavities.
	// - each boundary face has a corresponding corner in an adjacent untouched
	// tet.
	//   (see explanation of `corner` in TetMesh::tet_node.(3))
	// - store the indices of corners in below vectors.
	// - faces on the PLC face are ignored.
	AuxVector64<index_t> top_faces, bottom_faces;

	for (index_t tet_idoff : tets)
	{
		// divide vertices into top and bottom cavity.
		for (index_t j = 0; j < 4; j++)
		{
			index_t vid = tet_mesh.tetNode(tet_idoff + j);
			if (v_count[vid]) // skip traversed vertices
				continue;

			v_count[vid] = 1;
			Sign ov      = v_orient[vid];
			OMC_EXPENSIVE_ASSERT(is_sign_reliable(ov), "uninitialized orientation.");
			if (ov >= Sign::ZERO)
				top_vertices.push_back(vid);
			if (ov <= Sign::ZERO)
				bottom_vertices.push_back(vid);
		}
		// divide boundary faces into top and bottom cavity.
		for (index_t j = 0; j < 4; j++)
		{
			// the neighboring corner
			index_t neigh_idoff = tet_mesh.tetNeigh(tet_idoff + j);
			if (tet_mesh.isMarked(neigh_idoff, TET_MARK::TOUCHED))
				continue;
			// Get the vertices of the common face, which is also the boundary face of
			// the cavity.
			index_t v0, v1, v2;
			tet_mesh.faceVertices(neigh_idoff, v0, v1, v2);

			bool top = v_orient[v0] >= Sign::ZERO && v_orient[v1] >= Sign::ZERO &&
			           v_orient[v2] >= Sign::ZERO;
			bool bottom = v_orient[v0] <= Sign::ZERO && v_orient[v1] <= Sign::ZERO &&
			              v_orient[v2] <= Sign::ZERO;
			OMC_EXPENSIVE_ASSERT(
			  (top || bottom) && (!top || !bottom),
			  "(1) Face belongs to neither top nor bottom half cavity."
			  "(2) Face belongs to both top and bottom half cavity.");
			// check if the face belongs to the top or bottom half cavity.
			if (top)
				top_faces.push_back(neigh_idoff);
			else if (bottom)
				bottom_faces.push_back(neigh_idoff);
		}
	}

	// Sort vertices and faces so that
	// we can build a sequential map from global mesh to local meshed cavity.
	std::sort(top_vertices.begin(), top_vertices.end());
	std::sort(bottom_vertices.begin(), bottom_vertices.end());
	std::sort(top_faces.begin(), top_faces.end());
	std::sort(bottom_faces.begin(), bottom_faces.end());

	// clear vertex count
	for (index_t vid : top_vertices)
		v_count[vid] = 0;
	for (index_t vid : bottom_vertices)
		v_count[vid] = 0;
	// clear touched marks
	for (index_t tet_idoff : tets)
		tet_mesh.unmark(tet_idoff, TET_MARK::TOUCHED);
	// v_orient is kept for further use.

	// =========================================================================
	// # Delaunay tetrahedralize the top and bottom half cavity.
	//   The cavity may be expanded to recover missing cavity boundary faces.
	// ## pre-condition: cavity is properly divided.
	// ## post-condition: two half cavities are properly tetrahedralized.

	std::unique_ptr<TetMesh> top_mesh, bottom_mesh; // Delaunay tet mesh
	std::vector<GPoint *>    top_vps, bottom_vps;   // vertex pointers
	std::vector<index_t>     tets_to_remove;        // new tets after expanding

	index_t missing_face = InvalidIndex;
	index_t new_tet = InvalidIndex, new_vertex = InvalidIndex;

	// cavity is ok when it does not cross the PLC plane.
	bool cavity_ok = true;

	// convert vertex indices to vertex pointers
	top_vps.reserve(2 * top_vertices.size());
	bottom_vps.reserve(2 * bottom_vertices.size());
	for (index_t vid : top_vertices)
		top_vps.push_back(&gpnt(vid));
	for (index_t vid : bottom_vertices)
		bottom_vps.push_back(&gpnt(vid));

	// tetrahedralize the half cavity.
	// if any cavity face is missing, expand the cavity to recover the missing
	// face, until no missing face.
	while (cavity_ok)
	{ // fill the cavity by Delaunay tetrahedralization
		top_mesh = std::make_unique<TetMesh>(top_vps);
		DelTet top_dt(*top_mesh);
		top_dt.tetrahedralize();
		// check if any cavity face is missing
		if (cavityHasMissingFace(*top_mesh, top_vertices, top_faces, missing_face))
		{
			// expand the cavity to recover the missing boundary face.
			expandCavity(face, top_vertices, top_faces, missing_face, new_tet,
			             new_vertex);
			// mark the tetrahedron to remove
			tets_to_remove.push_back(new_tet);
			// add the vertex if it is not in the cavity
			if (is_valid_idx(new_vertex) && v_orient[new_vertex] >= Sign::ZERO)
				top_vps.push_back(&gpnt(new_vertex));
			else if (is_valid_idx(new_vertex) && v_orient[new_vertex] < Sign::ZERO)
				cavity_ok = false;
			// mark the cavity is expanded
			expanded = true;
		}
		else // no missing face found, tethraheralization is done.
			break;
	}

	while (cavity_ok)
	{ // fill the cavity by Delaunay tetrahedralization
		bottom_mesh = std::make_unique<TetMesh>(bottom_vps);
		DelTet bottom_dt(*bottom_mesh);
		bottom_dt.tetrahedralize();
		// check if any cavity face is missing
		if (cavityHasMissingFace(*bottom_mesh, bottom_vertices, bottom_faces,
		                         missing_face))
		{
			// expand the cavity to recover the missing boundary face.
			expandCavity(face, bottom_vertices, bottom_faces, missing_face, new_tet,
			             new_vertex);
			// mark the tetrahedron to remove
			tets_to_remove.push_back(new_tet);
			// add the vertex if it is not in the cavity
			if (is_valid_idx(new_vertex) && v_orient[new_vertex] <= Sign::ZERO)
				bottom_vps.push_back(&gpnt(new_vertex));
			else if (is_valid_idx(new_vertex) && v_orient[new_vertex] > Sign::ZERO)
				cavity_ok = false;
			// mark the cavity is expanded
			expanded = true;
		}
		else // no missing face found, tethraheralization is done.
			break;
	}

	if (cavity_ok)
	{ // Really modify the global mesh.
		size_t n_top_faces = top_faces.size(), n_bottom_faces = bottom_faces.size();
		// first, embed the tetrahedralization of the cavity to the global mesh
		embedMeshedCavity(*top_mesh, top_vertices, top_faces, bottom_faces);
		embedMeshedCavity(*bottom_mesh, bottom_vertices, bottom_faces, top_faces);

		OMC_ASSERT(n_top_faces == top_faces.size(),
		           "The number of top faces is not consistent.");
		OMC_ASSERT(n_bottom_faces < bottom_faces.size(),
		           "The number of bottom faces is not consistent.");

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		{ // check validity of the embedded part
			size_t  new_finite_tets = top_mesh->sizeTets() + bottom_mesh->sizeTets();
			DelTet  DT(tet_mesh);
			index_t tet_idoff_start = (tet_mesh.sizeTets() - new_finite_tets) * 4;
			index_t tet_idoff_end   = tet_mesh.sizeTets() * 4;
			for (index_t tet_idoff = tet_idoff_start; tet_idoff < tet_idoff_end;
			     tet_idoff += 4)
			{
				OMC_ASSERT(DT.verifyVolume(tet_idoff), "Negative volume.");
				OMC_ASSERT(DT.verifyNeighbor(tet_idoff), "Connectivity error.");
			}
		}
#endif

		// then, remove the tetrahedra of cavity
		for (index_t idoff : tets) // original part of the cavity
			tet_mesh.markTetAsDeleted(idoff);
		for (index_t idoff : tets_to_remove) // expanded part of the cavity
			tet_mesh.markTetAsDeleted(idoff);
		tet_mesh.removeDeletedTets();
	}
	succeed = cavity_ok;

	{ // Clear cached vertex orientation
		for (index_t vid : v_cached_orient)
			v_orient[vid] = Sign::UNCERTAIN;
		v_cached_orient.clear();
		for (index_t vid : face.bounding_vertices)
			v_orient[vid] = Sign::UNCERTAIN;
		for (index_t vid : face.flat_vertices)
			v_orient[vid] = Sign::UNCERTAIN;
	}
}

/**
 * @brief Checks if the cavity has any missing faces.
 *
 * This function determines if any face in the given list of faces is missing
 * in the local mesh. It maps the global indices of vertices to local indices,
 * traverses all faces to check for their existence in the local mesh, and
 * identifies any missing face.
 *
 * @param local_mesh The local tetrahedral mesh to check against.
 * @param vertices A vector of vertex indices in the global mesh.
 * @param faces A vector of face indices in the global mesh.
 * @param missing_face Output parameter that will hold the index of the missing
 * face if any.
 * @return True if there is a missing face, false otherwise.
 * @note `v_reindex` is used, not thread safe.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::cavityHasMissingFace(
  const TetMesh &local_mesh, const AuxVector64<index_t> &vertices,
  const AuxVector64<index_t> &faces, index_t &missing_face)
{
	missing_face = InvalidIndex;
	// map global index in `tet_mesh` to local index in `local_mesh`
	for (index_t i = 0; i < vertices.size(); i++)
		v_reindex[vertices[i]] = i;

	// traverse all faces to check if any one is missing
	for (index_t idoff : faces)
	{
		// map global face to local face
		index_t lv0, lv1, lv2;
		tet_mesh.faceVertices(idoff, lv0, lv1, lv2);
		lv0 = v_reindex[lv0], lv1 = v_reindex[lv1], lv2 = v_reindex[lv2];
		// check if local face exists
		if (!local_mesh.faceExists(lv0, lv1, lv2))
		{
			missing_face = idoff;
			break;
		}
	}

	// reset the map in `v_reindex`
	for (index_t i = 0; i < vertices.size(); i++)
		v_reindex[vertices[i]] = InvalidIndex;
	return is_valid_idx(missing_face);
}

/**
 * @brief Expand the cavity to recover the missing boundary face.
 *
 * The missing face is adjacent to two tetrahedra.
 * One tetrahedron belongs to the cavity while the other does not.
 * We expand the cavity by adding the new tetrahedron into the cavity.
 *
 * @param [in] plc_face The PLC face to recover.
 * @param [in] vertices Vertices of the half cavity.
 * @param [in] faces Boundary faces of the half cavity.
 * @param [in] missing_face The missing boundary face when meshing the cavity.
 * @param [out] new_tet The new tetrahedron of the cavity after expanding.
 * @param [out] new_vertex The new vertex of the cavity after expanding.
 */
template <typename Traits>
void ConstraintsRecover<Traits>::expandCavity(const PLCFace        &plc_face,
                                              AuxVector64<index_t> &vertices,
                                              AuxVector64<index_t> &faces,
                                              index_t  missing_face,
                                              index_t &new_tet,
                                              index_t &new_vertex)
{
	OMC_EXPENSIVE_ASSERT(tet_mesh.isFiniteTet(missing_face),
	                     "The missing face belongs to an infinite tet.");

	// (1) Get the `new_tet`
	// The new tetrahedron containing `missing_face` will be added to the cavity.
	// `missing_face` corresponds to a corner in `new_tet`
	new_tet = TetMesh::clipId(missing_face);

	// (2) Remove `missing_face` from `faces`
	auto faces_iter = std::lower_bound(faces.begin(), faces.end(), missing_face);
	OMC_EXPENSIVE_ASSERT(faces_iter != faces.end() && *faces_iter == missing_face,
	                     "The missing face is not in the boundary faces.");
	faces.erase(faces_iter);

	// (3) Add the `new_tet`.
	// For each corner in `new_tet` except the one corresponding to (corr. to)
	// `missing_face`, check if the face corr. to the corner needs to be
	// expanded.
	size_t added_corner_count = 0;
	for (index_t i = 0; i < 4; i++)
	{
		index_t corner = new_tet + i;
		if (corner == missing_face) // Skip the corner corr. to the missing face
			continue;
		// Check if the face corr. to this corner is already in the boundary faces
		faces_iter = std::lower_bound(faces.begin(), faces.end(), corner);
		if (faces_iter == faces.end() || *faces_iter == corner)
		{ // If the corner is in the boundary faces, remove it due to expanding.
			faces.erase(faces_iter);
		}
		else
		{ // Otherwise, add the face corr. to this corner of the cavity.
			// (we actually add the opposite corner.)
			faces.insert(faces_iter, tet_mesh.tetNeigh(corner));
			added_corner_count++;
		}
	}

	// (4) A new vertex is possibly added to the cavity.
	// If three corners are added, add their common vertex to the cavity. The
	// common vertex is the opposite vertex to the missing face in the `new_tet`.
	if (added_corner_count == 3)
	{
		new_vertex = tet_mesh.tetNode(missing_face);
		auto vit   = std::lower_bound(vertices.begin(), vertices.end(), new_vertex);
		if (vit == vertices.end() || *vit != new_vertex)
		{
			vertices.insert(vit, new_vertex);
			// calculate the orientation of the new vertex
			index_t tid = plc_face.triangles[0];
			index_t tv0 = plc.triVtx(tid, 0), tv1 = plc.triVtx(tid, 1),
			        tv2 = plc.triVtx(tid, 2);

			v_orient[new_vertex] = orient3dCached(tv0, tv1, tv2, new_vertex);
		}
		else
			new_vertex = InvalidIndex;
	}
	else
		new_vertex = InvalidIndex;
}

/**
 * @brief Embeds a meshed cavity into the global tetrahedral mesh.
 *
 * This function takes a local tetrahedral mesh representing a cavity and embeds
 * it into a global tetrahedral mesh. It performs the following steps:
 *
 * 1. Maps global corners to local ones and identifies boundary corners.
 *
 * 2. Classifies local tetrahedra as inside or outside based on boundary
 * corners.
 *
 * 3. Removes outside tetrahedra from the local mesh.
 *
 * 4. Embeds the local mesh into the global mesh.
 *
 * 5. Collects base faces (corners) that are boundary faces of the cavity.
 *
 * @tparam Traits The traits class providing necessary types and constants.
 * @param local_mesh The local tetrahedral mesh representing the cavity.
 * @param vertices A vector of vertex indices in the global mesh.
 * @param faces A vector of face indices in the global mesh.
 * @param base A vector to store the base faces (corners) of the cavity.
 */
template <typename Traits>
void ConstraintsRecover<Traits>::embedMeshedCavity(
  TetMesh &local_mesh, const AuxVector64<index_t> &vertices,
  const AuxVector64<index_t> &faces, AuxVector64<index_t> &base)
{
	std::vector<uint8_t> corner_is_boundary(local_mesh.sizeTets() * 4, false);

	typedef struct BoundaryCornerPair
	{
		index_t c0;  // one corner in the local mesh.
		index_t c1;  // the other corner in the local mesh.
		index_t bnd; // boundary corner in the global mesh.
	} BCP;
	AuxVector64<BCP> bcpairs;

	// (1) Map the global corners (with corresponding boundary face) to local ones

	// Build a map from global vertices to local vertices
	for (index_t i = 0; i < vertices.size(); i++)
		v_reindex[vertices[i]] = i;

	// Find the boundary corners in the local mesh
	for (index_t idoff : faces)
	{
		// map global face to local face
		index_t lv0, lv1, lv2;
		tet_mesh.faceVertices(idoff, lv0, lv1, lv2);
		lv0 = v_reindex[lv0], lv1 = v_reindex[lv1], lv2 = v_reindex[lv2];
		// Get the two corners corresponding to the local face
		index_t c0, c1;
		local_mesh.faceCorners(lv0, lv1, lv2, c0, c1);
		// Mark them as boundary corners and record the pair
		corner_is_boundary[c0] = true;
		corner_is_boundary[c1] = true;
		bcpairs.push_back({c0, c1, idoff});
	}

	// Reset the map
	for (index_t i = 0; i < vertices.size(); i++)
		v_reindex[vertices[i]] = InvalidIndex;

	// (2) Classify the local tetrahedra to inside/outside based on the boundary
	// corners. We will embed inner tetrahedra into the global mesh. Note that
	// not all tetrahedra or vertices will be embedded.

	// Find an infinite tet in the local mesh that has at least a vertex not on
	// the PLC face. Start from this tet to classify the tetrahedra.
	index_t start_tet = InvalidIndex;
	for (index_t tid = 0; tid < local_mesh.sizeTets(); tid++)
	{
		index_t tet_idoff = TetMesh::toIdOff(tid);
		if (!local_mesh.isFiniteTet(tet_idoff) &&
		    (v_orient[vertices[local_mesh.tetNode(tet_idoff)]] != Sign::ZERO ||
		     v_orient[vertices[local_mesh.tetNode(tet_idoff + 1)]] != Sign::ZERO ||
		     v_orient[vertices[local_mesh.tetNode(tet_idoff + 2)]] != Sign::ZERO))
		{
			start_tet = tet_idoff;
			break;
		}
	}
	OMC_ASSERT(is_valid_idx(start_tet), "No start tet found.");

	local_mesh.classifyInOut(corner_is_boundary, start_tet);

	// (3) Remove the outside tetrahedra, since we only embed the inside
	// tetrahedra to the global mesh.
	std::vector<index_t> tet_reindex(local_mesh.sizeTets());
	std::iota(tet_reindex.begin(), tet_reindex.end(), 0);

	std::vector<uint8_t> remain_vtx(vertices.size(), false);

	// Depart the outside tetrahedra from the local mesh
	for (index_t tid = 0; tid < local_mesh.sizeTets(); tid++)
	{
		index_t idoff = TetMesh::toIdOff(tid);
		if (local_mesh.isMarked(idoff, TET_MARK::OUTSIDE))
		{
			// depart the outside tetrahedron from its inside neighbors.
			for (index_t j = 0; j < 4; j++)
			{
				index_t neigh_idoff = local_mesh.tetNeigh(idoff + j);
				if (local_mesh.isMarked(neigh_idoff, TET_MARK::INSIDE))
					local_mesh.tetNeigh(neigh_idoff) = InvalidIndex;
			}
		}
		else
		{
			OMC_EXPENSIVE_ASSERT(local_mesh.isMarked(idoff, TET_MARK::INSIDE),
			                     "Wrong mark.");
			// remaining vertices only relate to the inside tetrahedra.
			for (index_t j = 0; j < 4; j++)
			{
				index_t vid            = local_mesh.tetNode(idoff + j);
				local_mesh.incTet(vid) = tid;
				remain_vtx[vid]        = true;
			}
		}
	}

	// To remove the outside tetrahedra, we move the inside tetrahedra from the
	// end to replace the outside tetrahedra at the beginning.
	index_t last_tid = local_mesh.sizeTets() - 1;
	for (index_t tid = 0; tid < last_tid; tid++)
	{
		index_t idoff = TetMesh::toIdOff(tid);
		if (!local_mesh.isMarked(idoff, TET_MARK::OUTSIDE))
			continue;

		// move to the last inside tetrahedron
		while (local_mesh.isMarked(TetMesh::toIdOff(last_tid), TET_MARK::OUTSIDE))
			last_tid--; // there is at least one inside tet.
		if (tid >= last_tid)
			break; // all outside tets are removed, break the loop.

		index_t last_idoff = TetMesh::toIdOff(last_tid);
		// Move the last inside tetrahedron to the current position.
		for (index_t j = 0; j < 4; j++)
		{
			TetMesh &LM   = local_mesh;
			// Update the node information.
			index_t &node = LM.tetNode(idoff + j);
			node          = LM.tetNode(last_idoff + j);

			// Update the neighbor information.
			index_t neigh          = LM.tetNeigh(last_idoff + j);
			LM.tetNeigh(idoff + j) = neigh;
			if (is_valid_idx(neigh))
				LM.tetNeigh(neigh) = idoff + j;

			// Update the incident tetrahedron information.
			LM.incTet(node) = tid;
		}
		// Update the mark.
		local_mesh.tetMark(tid) = local_mesh.tetMark(last_tid);
		// Update the reindex map.
		tet_reindex[last_tid]   = tid;
		tet_reindex[tid]        = last_tid;
		// move the last tetrahedron.
		last_tid--;
	}
	while (local_mesh.isMarked(TetMesh::toIdOff(last_tid), TET_MARK::OUTSIDE))
		last_tid--;
	// Finally, all outside tetrahedra are removed by the above loop.
	local_mesh.resizeTets(last_tid + 1);

	// (4) Embed the local mesh to the global

	// record size before embedding
	size_t n_local_tets  = local_mesh.sizeTets();
	size_t n_local_verts = local_mesh.sizeVerts();
	size_t n_global_tets = tet_mesh.sizeTets();

	// update the node in the local mesh to the corresponding global node
	for (index_t tid = 0; tid < n_local_tets; tid++)
	{
		for (index_t idoff = TetMesh::toIdOff(tid), j = 0; j < 4; j++)
		{
			OMC_EXPENSIVE_ASSERT(local_mesh.tetNode(idoff + j) !=
			                       TetMesh::INFINITE_VERTEX,
			                     "Infinite vertex.");
			local_mesh.tetNode(idoff + j) = vertices[local_mesh.tetNode(idoff + j)];
		}
	}
	// attach the local nodes to the global mesh
	tet_mesh.tet_node.insert(tet_mesh.tet_node.end(), local_mesh.tet_node.begin(),
	                         local_mesh.tet_node.end());
	// update the vertex-tetrahedron incident relation in the global mesh
	for (index_t vid = 0; vid < n_local_verts; vid++)
	{
		if (remain_vtx[vid])
		{
			OMC_EXPENSIVE_ASSERT(local_mesh.incTet(vid) < n_local_tets,
			                     "Wrong incTet.");
			tet_mesh.incTet(vertices[vid]) = local_mesh.incTet(vid) + n_global_tets;
		}
	}
	// update the neighbor in the local mesh
	size_t _4n_global_tets = n_global_tets * 4;
	for (index_t tid = 0; tid < n_local_tets; tid++)
	{
		for (index_t idoff = TetMesh::toIdOff(tid), j = 0; j < 4; j++)
		{
			index_t &neigh = local_mesh.tetNeigh(idoff + j);
			if (is_valid_idx(neigh))
				neigh += _4n_global_tets;
		}
	}
	// attach the local neightbor to the global mesh
	tet_mesh.tet_neigh.insert(tet_mesh.tet_neigh.end(),
	                          local_mesh.tet_neigh.begin(),
	                          local_mesh.tet_neigh.end());
	OMC_EXPENSIVE_ASSERT(tet_mesh.tet_neigh.size() == 4 * tet_mesh.sizeTets(),
	                     "Wrong tet_neigh size.");
	// connect the neighbors adjacent to the cavity boundary
	for (const BCP &bcp : bcpairs)
	{
		index_t t0 = tet_reindex[TetMesh::getId(bcp.c0)];
		index_t t1 = tet_reindex[TetMesh::getId(bcp.c1)];
		OMC_EXPENSIVE_ASSERT((t0 < n_local_tets || t1 < n_local_tets) &&
		                       (t0 >= n_local_tets || t1 >= n_local_tets),
		                     "One inside tet and one outside tet.");
		index_t inner_corner             = t0 < n_local_tets
		                                     ? TetMesh::toIdOff(t0) + TetMesh::clipOff(bcp.c0)
		                                     : TetMesh::toIdOff(t1) + TetMesh::clipOff(bcp.c1);
		index_t bnd                      = bcp.bnd;
		index_t global_corner            = _4n_global_tets + inner_corner;
		tet_mesh.tetNeigh(global_corner) = bnd;
		tet_mesh.tetNeigh(bnd)           = global_corner;
	}
	// update the tet marks in the global mesh
	tet_mesh.tet_mark.resize(tet_mesh.sizeTets());

	// (5) Collect the base faces (corners). They are the boundary faces of the
	// cavity, located on the PLC face.
	for (index_t tid = n_global_tets; tid < tet_mesh.sizeTets(); tid++)
	{
		index_t idoff = TetMesh::toIdOff(tid);
		for (index_t j = 0; j < 4; j++)
		{
			if (is_valid_idx(tet_mesh.tetNeigh(idoff + j)))
				continue;
#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
			index_t v0, v1, v2;
			tet_mesh.faceVertices(idoff + j, v0, v1, v2);
			OMC_ASSERT(v_orient[v0] == Sign::ZERO && v_orient[v1] == Sign::ZERO &&
			             v_orient[v2] == Sign::ZERO,
			           "Wrong base face.");
#endif
			base.push_back(idoff + j);
		}
	}
}

/**
 * @brief Check if a tetrahedron `tet_idoff` intersects a PLC face `face`.
 */
template <typename Traits>
bool ConstraintsRecover<Traits>::tetIntersectsFace(index_t        tet_idoff,
                                                   const PLCFace &face)
{
	auto isVtxBounding = [this](index_t vid) { return v_count[vid] > 0; };

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
bool ConstraintsRecover<Traits>::segCrossesFace(index_t s0, index_t s1,
                                                const PLCFace &face) const
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
template <typename PointType>
index_t ConstraintsRecover<Traits>::newVtx(PointType new_pnt)
{
	// create the new vertex
	index_t new_vid     = verts.size();
	// Put the new vertex into the point arena
	auto   *new_pnt_ptr = pnt_arenas[0].emplace(std::move(new_pnt));
	// Put the new vertex into the vertex list
	verts.push_back(static_cast<GPoint *>(new_pnt_ptr));

	// create auxiliary data in TetMesh & PLC
	tet_mesh.newVtx(new_vid);

	return new_vid;
}

} // namespace OMC