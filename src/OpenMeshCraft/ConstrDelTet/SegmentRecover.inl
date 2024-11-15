#pragma once

#include "SegmentRecover.h"

namespace OMC {

// Enable shuffling missing segments in each loop of segment recovery.
// #define OMC_CDT_SHUFFLE_MISSING_SEGMENTS

// Enable exact inSphere predicate in finding encroaching point.
#define OMC_CDT_EXACT_ENCROACH_TEST

// Choose one segmen recovery strategy
// #define OMC_CDT_SEG_SIHANG
#define OMC_CDT_SEG_GREEDY

/**
 * @brief Initialize with the Delaunay tetrahedral mesh and the input
 * constrained triangles. Prepare for the constraits recovery.
 * @param _tet_mesh the Delaunay tetrahedral mesh
 * @param _plc the input constrained piecewise linear complex
 */
template <typename Traits>
SegmentRecover<Traits>::SegmentRecover(std::vector<GPoint *> &_verts,
                                       std::vector<PntArena> &_pnt_arenas,
                                       TetMesh &_tet_mesh, PLC &_plc,
                                       ConstrDelTet_Config _config,
                                       ConstrDelTet_Stats *_stats)
  : verts(_verts)
  , pnt_arenas(_pnt_arenas)
  , tet_mesh(_tet_mesh)
  , plc(_plc)
  , config(_config)
  , stats(_stats)
{
}

template <typename Traits>
void SegmentRecover<Traits>::segmentRecovery()
{
#if defined(OMC_CDT_SEG_SIHANG)
	segmentRecovery_SiHang();
#elif defined(OMC_CDT_SEG_GREEDY)
	segmentRecovery_Greedy();
#endif
}

/**
 * @brief Create a new vertex and update `tet_mesh` and `plc` at the same time.
 * @param new_pnt geometric implementation of the new vertex
 * @return the index to the new vertex.
 */
template <typename Traits>
template <typename PointType>
index_t SegmentRecover<Traits>::newVtx(PointType new_pnt)
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

template <typename Traits>
void SegmentRecover<Traits>::segmentRecovery_SiHang()
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

	size_t orig_vn     = verts.size();
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
			tet_mesh.mark(ep0, VTX_MARK::TO_CHECK);
			tet_mesh.mark(ep1, VTX_MARK::TO_CHECK);
			tet_mesh.mark(new_vid, VTX_MARK::TO_CHECK);
			AuxVector64<index_t> local_vv;
			tet_mesh.VV(new_vid, local_vv);
			for (index_t vid : local_vv)
				tet_mesh.mark(vid, VTX_MARK::TO_CHECK);

			// log and output
			split_count++;
			if (config.verbose && split_count % 100 == 0)
			{
				std::cout << std::format("\r[OpenMeshCraft CDT] {} segments are split. "
				                         "{} segments are missing.",
				                         split_count, missing_segments.size());
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
		OMC_ASSERT(config.Steiner_point_thres == 0 ||
		             split_count < orig_vn * config.Steiner_point_thres,
		           "Too many Steiner points are inserted.");
#ifdef OMC_CDT_SHUFFLE_MISSING_SEGMENTS
		std::shuffle(missing_segments.begin(), missing_segments.end(),
		             std::default_random_engine(std::random_device()()));
#endif
		// clear the `TO_CHECK` mark for all vertices
		for (index_t vid = 0; vid < tet_mesh.sizeVerts(); vid++)
			tet_mesh.unmark(vid, VTX_MARK::TO_CHECK);
	}
	if (config.verbose) // output a new line
		std::cout << std::endl;

	tet_mesh.removeDeletedTets();

	if (stats)
	{ // record statistics about segment recovery
		stats->seg_steiner = split_count;
	}

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
index_t SegmentRecover<Traits>::splitMissingSegment(index_t eid)
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

#ifdef OMC_CDT_EXACT_ENCROACH_TEST
		OMC_EXPENSIVE_ASSERT(is_valid_idx(ref_vid),
		                     "Could not find a valid reference encroaching point.");
#else
		if (!is_valid_idx(ref_vid))
		{ //  can't find the reference encroaching point due to inexact predicate.
			// just (use BothAcute strategy to) split the segment at its middle point.
			curr_tet = TetMesh::toIdOff(tet_mesh.incTet(edge.ep0()));
			new_vid  = splitSegment_BothAcuteVertex(eid);
		}
		else
#endif
		{
			if (edge.type == PLCEdgeType::NO_ACUTE_VERTEX)
				new_vid = splitSegment_NoAcuteVertex(eid, ref_vid);
			else // ONE_ACUTE_VERTEX
				new_vid = splitSegment_OneAcuteVertex(eid, ref_vid);
		}
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
void SegmentRecover<Traits>::findReferenceEncroachingPoint(
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
	tet_mesh.mark(edge.ep0(), VTX_MARK::ENCROACHED);
	tet_mesh.mark(edge.ep1(), VTX_MARK::ENCROACHED);

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
	tet_mesh.unmark(edge.ep0(), VTX_MARK::ENCROACHED);
	tet_mesh.unmark(edge.ep1(), VTX_MARK::ENCROACHED);
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
index_t SegmentRecover<Traits>::splitSegment_BothAcuteVertex(index_t eid)
{
	const PLCEdge &edge    = plc.edge(eid);
	// Get the new point
	IPoint_LNC     new_pnt = middlePoint(edge);
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
index_t SegmentRecover<Traits>::splitSegment_NoAcuteVertex(index_t eid,
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
		new_pnt = middlePoint(edge);
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
index_t SegmentRecover<Traits>::splitSegment_OneAcuteVertex(index_t eid,
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
		new_pnt = middlePoint(edge);
	}

	// Add the new point
	index_t new_vid = newVtx(new_pnt);
	// Split edge by the new point
	plc.splitPLCEdge(eid, new_vid);

	return new_vid;
}

/**
 * @brief Two points `a` and `b` form a smallest (diametral) sphere, check if
 * the query point `c` lies inside or touches the sphere.
 * @return True if the point lies inside or touches the sphere, false otherwise.
 */
template <typename Traits>
bool SegmentRecover<Traits>::inSphere(const GPoint &a, const GPoint &b,
                                      const GPoint &c)
{
	// In [Robust CDT 2023], this predicate is implemented in floating-point
	// numbers, I reimplemnted it in exact predicates.

#ifdef OMC_CDT_EXACT_ENCROACH_TEST
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
bool SegmentRecover<Traits>::largerSphere(const GPoint &a, const GPoint &b,
                                          const GPoint &c, const GPoint &d)
{
	// It is complex to generate a complete point arrangement to calculate an
	// exact predicate. This predicate tolerate floating-point errors, so I
	// directly use the inexact predicate.

#if 0
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
bool SegmentRecover<Traits>::isLessThanDistance(const GPoint &a,
                                                const GPoint &b,
                                                const GPoint &c)
{
	// This predicate tolerate floating-point errors, so I directly use the
	// inexact predicate.

#if 0
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
bool SegmentRecover<Traits>::isLessThanHalfDistance(const GPoint &a,
                                                    const GPoint &b,
                                                    const GPoint &c)
{
	// This predicate tolerate floating-point errors, so I directly use the
	// inexact predicate.

#if 0
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
SegmentRecover<Traits>::getInterpolateT(index_t oep0, index_t oep1, index_t ep0,
                                        index_t ep1) const
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
auto SegmentRecover<Traits>::middlePoint(const PLCEdge &e) const -> IPoint_LNC
{
	OMC_EXPENSIVE_ASSERT(!is_valid_idx(e.child_id), "The edge is already split.");

	index_t ep0 = e.ep0(), ep1 = e.ep1();

	if (is_valid_idx(e.ancestor_id)) // The edge is a sub-edge of a split edge.
	{
		const PLCEdge &oe   = plc.edge(e.ancestor_id);
		index_t        oep0 = oe.ep0(), oep1 = oe.ep1();

		auto [t0, t1] = getInterpolateT(oep0, oep1, ep0, ep1);
		OMC_EXPENSIVE_ASSERT((t0 + t1) * 0.5 != t0 && (t0 + t1) * 0.5 != t1,
		                     "The edge can not be split at midpoint.");
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
auto SegmentRecover<Traits>::lineSphereIntersection_noAc(index_t eid,
                                                         bool    reverse,
                                                         index_t ref_vid) const
  -> IPoint_LNC
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
	OMC_EXPENSIVE_ASSERT(t0 < t1, "Invalid interpolate parameters.");
	// Parameterize the sphere radius to the original segment
	double radius =
	  std::sqrt((ref_v - end_v).sqrnorm() / (oe1_v - oe0_v).sqrnorm());
	// Get the parameter of the intersection point
	double t = reverse ? t1 - radius : t0 + radius;
	// Check if the intersection point is inside the edge
	if (t <= t0 || t >= t1)
	{ // if no (maybe caused by numerical error), return the middle point
		t = (t0 + t1) * 0.5;
	}
	OMC_EXPENSIVE_ASSERT((t0 < t && t < t1), "The point is outside the edge.");
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
auto SegmentRecover<Traits>::lineSphereIntersection_oneAc(index_t eid,
                                                          index_t ref_vid) const
  -> IPoint_LNC
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
	OMC_EXPENSIVE_ASSERT(t0 < t1, "Invalid interpolation parameters.");
	// Parameterize the sphere radius to the original segment
	double t   = std::sqrt((ref_v - oe0_v).sqrnorm() / (oe1_v - oe0_v).sqrnorm());
	// Ensure that the intersection point is inside the edge,
	// and make the sub segments as long as possible.
	double eps = (t1 - t0) * 0.2;
	if (t <= (t0 + eps) || t >= (t1 - eps))
	{ // Otherwise return the middle point
		t = (t0 + t1) * 0.5;
	}
	OMC_EXPENSIVE_ASSERT((t0 < t && t < t1), "The point is outside the edge.");
	return CreateLNC()(gpnt(oep0), gpnt(oep1), t);
}

template <typename Traits>
void SegmentRecover<Traits>::segmentRecovery_Greedy()
{
	// initialize the PLC edges
	plc.initPLCEdges();

	// initialize the segments' diametral sphere tree.
	{
		std::vector<GenericSegment3T> segments;
		segments.reserve(plc.numEdges());
		for (index_t eid = 0; eid < plc.numEdges(); eid++)
		{
			const PLCEdge &e = plc.edge(eid);
			if (e.type != PLCEdgeType::FLAT_EDGE)
			{
				index_t ev0 = e.ep0(), ev1 = e.ep1();
				segments.emplace_back(&gpnt(ev0), &gpnt(ev1));
			}
		}
		tree.insert(std::move(segments));
		tree.build();
	}
}

} // namespace OMC