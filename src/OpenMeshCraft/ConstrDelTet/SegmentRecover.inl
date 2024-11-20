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

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// check if all segments are recovered
	for (index_t eid = 0; eid < plc.numEdges(); eid++)
	{
		const PLCEdge &e = plc.edge(eid);
		if (!e.is_split() && e.type != PLCEdgeType::FLAT_EDGE)
		{
			OMC_ASSERT(tet_mesh.edgeExists(e.ep0(), e.ep1()), "Missing segment {}.",
			           eid);
		}
	}
#endif

	tet_mesh.removeDeletedTets();
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
			if (!e.is_split() && e.type != PLCEdgeType::FLAT_EDGE &&
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
	if (stats)
	{ // record statistics about segment recovery
		stats->seg_steiner = split_count;
	}

	tet_mesh.removeDeletedTets();
}

template <typename Traits>
index_t SegmentRecover<Traits>::splitMissingSegment(index_t eid)
{
	IPoint_LNC new_pnt;
	index_t    curr_tet = InvalidIndex;

	PLCEdge &edge = plc.edge(eid);

	if (edge.type == PLCEdgeType::BOTH_ACUTE_VERTEX)
	{
		// This split strategy is used to split segment with two acute vertices, and
		// generating two sub-edges with type `ONE_ACUTE_VERTEX`.
		curr_tet = TetMesh::toIdOff(tet_mesh.incTet(edge.ep0()));
		new_pnt  = middlePoint(edge);
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
			new_pnt  = middlePoint(edge);
		}
		else
#endif
		{
			if (edge.type == PLCEdgeType::NO_ACUTE_VERTEX)
				new_pnt = splitSegment_NoAcuteVertex(eid, ref_vid);
			else // ONE_ACUTE_VERTEX
				new_pnt = splitSegment_OneAcuteVertex(eid, ref_vid);
		}
	}

	// Add the new point
	index_t new_vid = newVtx(new_pnt);
	// Split edge by the new point
	plc.splitPLCEdge(eid, new_vid);
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
 * @param ref_tidoff index_off to the tetrahedron containing the reference
 * encroaching point
 * @param enc_verts indices to the encroaching points
 * @see Section 3.3 Segment recovery, in [Robust CDT].
 * @note
 * Rely on mark `TOUCHED` to avoid visiting the same tetrahedron and the
 * same vertex multiple times.
 * Relay on mark `ENCROACHED` to mark the encroaching vertices.
 * Not thread safe.
 */
template <typename Traits>
void SegmentRecover<Traits>::findReferenceEncroachingPoint(
  index_t eid, index_t &ref_vid, index_t &ref_tidoff,
  AuxVector64<index_t> *enc_verts) const
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
	ref_tidoff          = InvalidIndex;

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
				if (enc_verts) // store the encroaching vertices if required
					enc_verts->push_back(vid);
				// check if it is the reference encroaching point
				if (ref_vid == InvalidIndex || largerSphere(p0, p1, curr_p, *ref_p))
				{
					ref_vid    = vid;
					ref_tidoff = tet_idoff;
					ref_p      = &curr_p;
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
 * @brief Find the splitting point to split the constrained edge `eid` that has
 * no acute vertices, but do not really split the edge.
 * @param eid The constrained edge to split.
 * @param ref_vid The reference encroaching point.
 * @return the splitting point.
 * @see The strategy is described in Section 3.3 of [Robust CDT].
 */
template <typename Traits>
auto SegmentRecover<Traits>::splitSegment_NoAcuteVertex(index_t eid,
                                                        index_t ref_vid)
  -> IPoint_LNC
{
	const PLCEdge &edge = plc.edge(eid);

	const GPoint &ep0_pnt = gpnt(edge.ep0());
	const GPoint &ep1_pnt = gpnt(edge.ep1());
	const GPoint &ref_pnt = gpnt(ref_vid);

	if (isLessThanHalfDistance(ep0_pnt, ref_pnt, ep1_pnt))
	{ // The `ref_pnt` is closer to the endpoint `ep0`, and the distance between
		// `ref_pnt` and `ep0` is less than half the distance between `ep0` and
		// `ep1`.
		return lineSphereIntersection_noAc(eid, false, ref_vid);
	}
	else if (isLessThanHalfDistance(ep1_pnt, ref_pnt, ep0_pnt))
	{ // The `ref_pnt` is closer to the endpoint `ep1`, and the distance between
		// `ref_pnt` and `ep1` is less than half the distance between `ep0` and
		// `ep1`.
		return lineSphereIntersection_noAc(eid, true, ref_vid);
	}
	else
	{ // The distances between both <`ref_pnt`, `ep0`> and <`ref_pnt`, `ep1`>
		// are larger than half the distance between `ep0` and `ep1`.
		// Split the segment at the middle point.
		return middlePoint(edge);
	}
}

/**
 * @brief Find the splitting point to split the constrained edge `eid` that has
 * only one acute vertex, but do not really split the segment.
 * @param eid The constrained edge to split.
 * @param ref_vid the reference encroaching point.
 * @return the new splitting point.
 * @see The strategy is described in Section 3.3 of [Robust CDT].
 */
template <typename Traits>
auto SegmentRecover<Traits>::splitSegment_OneAcuteVertex(index_t eid,
                                                         index_t ref_vid)
  -> IPoint_LNC
{
	const PLCEdge &edge = plc.edge(eid);

	IPoint_LNC new_pnt = lineSphereIntersection_oneAc(eid, ref_vid);

	if (isLessThanDistance(new_pnt, gpnt(edge.ep1()), gpnt(ref_vid)))
	{ // The new point is closer to the non-acute endpoint `ep1` than the
		// reference encroaching point, we should switch to another split strategy
		// (described in Section 3.3 in [Robust CDT]), but it is not really
		// necessary. Just using midpoint provides better performances
		new_pnt = middlePoint(edge);
	}

	return new_pnt;
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
	OMC_EXPENSIVE_ASSERT(!e.is_split(), "The edge is already split.");

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
	// initialize the PLC edges.
	plc.initPLCEdges();

	// initialize the static segment tree and the dynamic segments' diametral
	// sphere tree.
	size_t non_flat_count = initializeTrees();

	// build the protecting sphere for the PLC edges on PLC vertices.
	buildProtectingSphere();

	// ===========================================================================
	// Then a greedy strategy to split remaining missing segments.

	seg_steiner_point.resize(plc.numEdges());
	seg_queue.reserve(plc.numEdges());

	size_t missing_count = 0;
	// Initialize the segments to be split.
	for (index_t eid = 0; eid < plc.numEdges(); eid++)
	{
		const PLCEdge &e = plc.edge(eid);

		if (!e.is_split() && e.type != PLCEdgeType::FLAT_EDGE &&
		    !tet_mesh.edgeExists(e.ep0(), e.ep1()))
		{
			pushSegmentToQueue</*AllowUpdate*/ false>(eid);
			missing_count++;
			if (config.verbose && missing_count % 100 == 0)
			{
				std::cout << std::format("\rmissing segments count: {}", missing_count);
			}
		}
	}
	if (config.verbose) // output a new line
		std::cout << std::endl;

	size_t split_count = 0;
	// Loop to split segments with the highest priority
	while (!seg_queue.empty())
	{
		index_t eid      = seg_queue.top().first;
		double  priority = seg_queue.top().second;
		seg_queue.pop();

		OMC_EXPENSIVE_ASSERT(plc.edge(eid).type != PLCEdgeType::FLAT_EDGE,
		                     "Try to split flat edge.");
		OMC_EXPENSIVE_ASSERT(!plc.edge(eid).is_split(),
		                     "The edge is already split.");
		// Skip the recovered segment
		if (tet_mesh.edgeExists(plc.edge(eid).ep0(), plc.edge(eid).ep1()))
			continue;

		// Get the Steiner point
		IPoint_LNC new_pnt = seg_steiner_point[eid];

		// Before split, find encroached segments
		AuxVector64<index_t> possible_enc_segs, enc_segs;
		sph_tree.all_intersections(new_pnt, possible_enc_segs);
		for (index_t possible_enc_eid : possible_enc_segs)
		{
			if (possible_enc_eid == eid)
				continue; // skip the split segment

			const PLCEdge &possible_enc_e = plc.edge(possible_enc_eid);
			if (!inSphere(gpnt(possible_enc_e.ep0()), gpnt(possible_enc_e.ep1()),
			              new_pnt))
				continue; // skip the segments that are not encroached

			enc_segs.push_back(possible_enc_eid);
		}

		// Split the segment by the new point
		index_t new_vid = newVtx(new_pnt);
		plc.splitPLCEdge(eid, new_vid);

		// Insert the splitting point into the Delaunay tetrahedral mesh
		DelTet  DT(tet_mesh);
		index_t tet = TetMesh::toIdOff(tet_mesh.incTet(plc.edge(eid).ep0()));
		// -- Walk and find the cavity
		AuxVector64<index_t> cavity_tets;
		AuxVector64<index_t> cavity_corners;
		DT.walk(new_vid, tet);
		DT.cavity(new_vid, tet, cavity_tets, cavity_corners);
		// -- Find missing segments in the cavity (inner edges of the cavity)
		//    (they may not be encroached by the Steiner point)
		AuxVector64<index_t> cavity_missing_segs;
		missingSegmentsInCavity(cavity_tets, cavity_corners, cavity_missing_segs);
		// -- Fill the cavity
		DT.filling(new_vid, cavity_corners);
		// -- Check the validity
		OMC_EXPENSIVE_ASSERT(DT.localVerify(new_vid),
		                     "Invalid Delaunay tetrahedralization.");

		// Update related data structures
		seg_steiner_point.emplace_back();
		seg_steiner_point.emplace_back();

		// Update the segments' diametral sphere tree
		const PLCEdge &e     = plc.edge(eid);
		const PLCEdge &ch_e0 = plc.edge(e.child_id);
		const PLCEdge &ch_e1 = plc.edge(e.child_id + 1);
		GenericSegment ch0(&gpnt(ch_e0.ep0()), &gpnt(ch_e0.ep1()));
		GenericSegment ch1(&gpnt(ch_e1.ep0()), &gpnt(ch_e1.ep1()));
		sph_tree.split(eid, e.child_id, ch0, e.child_id + 1, ch1);

		// Add two sub-segments to the queue
		missing_count--; // due to the split
		if (!tet_mesh.edgeExists(ch_e0.ep0(), ch_e0.ep1()))
		{
			pushSegmentToQueue</*AllowUpdate*/ false>(e.child_id);
			missing_count++;
		}
		if (!tet_mesh.edgeExists(ch_e1.ep0(), ch_e1.ep1()))
		{
			pushSegmentToQueue</*AllowUpdate*/ false>(e.child_id + 1);
			missing_count++;
		}
		missing_count += cavity_missing_segs.size();

		// -------------------------------------------------------------------------
		// The segments that are not encroached by the Steiner point
		// may change their status:
		// - missing -> missing and recovered -> recovered.
		// - recovered -> missing, when all incident tetrahedra are removed.
		// -------------------------------------------------------------------------
		// The segments that are encroached by the Steiner point
		// may change their status:
		// - recovered -> missing, when all incident tetrahedra are removed.
		// - recovered -> recovered, when at least one incident tetrahedra is kept.
		// - missing -> missing, a missing segment will never be recovered
		//   by adding a Steiner point to another segment.
		// -------------------------------------------------------------------------

		// Update the priority of the segments that are encroached by the split
		AuxVector64<index_t> segs_to_update;
		segs_to_update.insert(segs_to_update.end(), enc_segs.begin(),
		                      enc_segs.end());
		segs_to_update.insert(segs_to_update.end(), cavity_missing_segs.begin(),
		                      cavity_missing_segs.end());
		segs_to_update.erase(
		  std::unique(segs_to_update.begin(), segs_to_update.end()),
		  segs_to_update.end());

		for (index_t eid_to_update : segs_to_update)
		{
			const PLCEdge &enc_e = plc.edge(eid_to_update);
			if (tet_mesh.edgeExists(enc_e.ep0(), enc_e.ep1()))
				continue; // skip the recovered segments
			// Update the priority of the segment
			pushSegmentToQueue</*AllowUpdate*/ true>(eid_to_update);
		}

		split_count++;
		if (split_count % 5000 == 0)
		{ // rebuild the tree for better efficiency
			sph_tree.collect_garbage();
			OMC_ASSERT(sph_tree.size() == non_flat_count + split_count,
			           "The tree size is not correct after collecting garbage.");
		}
		if (config.verbose)
		{ // report the progress
			std::cout << std::format(
			  "\rSplit count: {}. Missing count: {}. Priority: {}", split_count,
			  missing_count, int(priority));
		}
	}
	if (config.verbose) // just output a new line
		std::cout << std::endl;
	if (stats)
	{ // record statistics about segment recovery
		stats->seg_steiner = split_count;
	}
	OMC_ASSERT(missing_count == 0, "Some segments are not recovered.");
}

/**
 * @brief Initializes the segment and segment diametral sphere trees.
 * @return The number of non-flat edges processed.
 */
template <typename Traits>
size_t SegmentRecover<Traits>::initializeTrees()
{
	size_t non_flat_count = 0;

	// segment tree
	std::vector<IndexedSegment> indexed_segments;
	indexed_segments.reserve(plc.numEdges());
	// segment diametral sphere tree
	std::vector<GenericSegment> segments;
	std::vector<index_t>        indices;
	segments.reserve(plc.numEdges());
	indices.reserve(plc.numEdges());
	// collect primitives
	for (index_t eid = 0; eid < plc.numEdges(); eid++)
	{
		const PLCEdge &e = plc.edge(eid);
		if (e.type != PLCEdgeType::FLAT_EDGE)
		{
			non_flat_count++;
			// endpoints
			index_t       ev0 = e.ep0(), ev1 = e.ep1();
			const GPoint &gp0 = gpnt(ev0), &gp1 = gpnt(ev1);
			// segment tree
			indexed_segments.emplace_back(Segment(AsEP()(gp0), AsEP()(gp1)), eid);
			// segment diametral sphere tree
			segments.emplace_back(&gp0, &gp1);
			indices.push_back(eid);
		}
	}
	// segment tree
	seg_tree.insert(indexed_segments.begin(), indexed_segments.end());
	seg_tree.build();
	// segment diametral sphere tree
	sph_tree.insert(segments.begin(), segments.end(), indices.begin(),
	                indices.end());
	sph_tree.build();

	return non_flat_count;
}

/**
 * @brief Constructs protecting spheres for vertices in the PLC.
 *
 * If a vertex needs protection, it constructs an initial protecting sphere
 * based on the shortest edge lengths connected to the vertex.
 * It then checks for intersections with other segments and shrinks the sphere
 * if necessary to ensure the vertex is well-protected.
 * @see Shewchuk, J. R. Constrained Delaunay Tetrahedralizations and Provably
 * Good Boundary Recovery. In Proceedings of the International Meshing
 * Roundtable Conference (2002).
 */
template <typename Traits>
void SegmentRecover<Traits>::buildProtectingSphere()
{
	protecting_sphere_squared_radius.resize(plc.numVertices(), -1.0);

	auto approxEdgeLength = [this](const PLCEdge &e)
	{ return (gpnt(e.ep0()) - gpnt(e.ep1())).sqrnorm(); };

	for (index_t vid = 0; vid < plc.numVertices(); vid++)
	{
		std::cout << std::format("\rProcessing vertex {}      ", vid);
		// check if the vertex need to be protected,
		// get the shortest edge length at the same time.
		bool   need_protect            = false;
		double shortest_acute_edge     = DBL_MAX; // l_i in reference paper
		double shortest_non_acute_edge = DBL_MAX; // d_i in reference paper

		boost::container::flat_set<index_t> inc_edges;
		auto [inc_edges_begin, inc_edges_end] = plc.vertIncEdges(vid);
		for (AuxVecConstIter iter = inc_edges_begin; iter != inc_edges_end; iter++)
		{
			index_t        eid = *iter;
			const PLCEdge &e   = plc.edge(eid);
			inc_edges.insert(eid);

			if (e.type == PLCEdgeType::NO_ACUTE_VERTEX)
				continue;
			else if (e.type == PLCEdgeType::ONE_ACUTE_VERTEX)
			{
				need_protect = true;
				if (e.acute_vid == vid)
				{
					shortest_acute_edge =
					  std::min(shortest_acute_edge, approxEdgeLength(e));
				}
				else
				{
					shortest_non_acute_edge =
					  std::min(shortest_non_acute_edge, approxEdgeLength(e));
				}
			}
			else // e.type == PLCEdgeType::BOTH_ACUTE_VERTEX
			{
				need_protect = true;
				shortest_acute_edge =
				  std::min(shortest_acute_edge, approxEdgeLength(e));
			}
		}

		if (!need_protect)
			continue;

		// construct a initial protecting sphere based on the above lengths.
		const EPoint &center = AsEP()(gpnt(vid));
		double        squared_radius =
		  std::min(shortest_acute_edge * 0.0625, shortest_non_acute_edge * 0.25);
		Sphere sphere(center, squared_radius);

		// find segments that intersect the currect sphere
		AuxVector64<index_t> intersected_edges;
		{
			// find intersected segments by AABB tree
			AuxVector64<index_t> _intersected_edges;
			seg_tree.all_intersections(sphere, _intersected_edges);
			// remove incident edges in found intersected edges.
			boost::container::flat_set<index_t> _tmp_set(_intersected_edges.begin(),
			                                             _intersected_edges.end());
			std::set_difference(_tmp_set.begin(), _tmp_set.end(), inc_edges.begin(),
			                    inc_edges.end(),
			                    std::back_inserter(intersected_edges));
		}

		// if no intersected segments, the vertex is well-protected.
		if (intersected_edges.empty())
		{
			protecting_sphere_squared_radius[vid] = squared_radius;
			continue;
		}

		// otherwise, we need to shrink the sphere.
		AuxVector64<Segment> intersected_segs;
		for (index_t eid : intersected_edges)
		{
			const PLCEdge &e = plc.edge(eid);
			intersected_segs.emplace_back(AsEP()(gpnt(e.ep0())),
			                              AsEP()(gpnt(e.ep1())));
		}

		// the shortest projection distance from the vertex to the intersected
		// segments is also called `local feature size` (lfs).
		// we need to shrink the sphere to be less than the local feature size.
		double min_proj_dis = DBL_MAX;
		for (const Segment &seg : intersected_segs)
		{
			EPoint proj_pnt = ProjectPoint()(seg, center);
			double proj_dis = (proj_pnt - center).sqrnorm();
			min_proj_dis    = std::min(min_proj_dis, proj_dis);
		}

		// reduce the projection distance to avoid numerical error
		sphere.squared_radius() = min_proj_dis * 0.5;
		// check if the sphere is still intersected by segments
		while (!intersected_segs.empty())
		{
			if (DoIntersect()(sphere, intersected_segs.back()))
				sphere.squared_radius() *= 0.5;
			else
				intersected_segs.pop_back();
		}

		protecting_sphere_squared_radius[vid] = sphere.squared_radius();
	}
}

/**
 * @brief Pushes a segment `eid` into the priority queue.
 *
 * This function calculates the Steiner point for the segment, evaluates the
 * segment's priority, and then pushes the segment into the priority queue.
 */
template <typename Traits>
template <bool AllowUpdate>
void SegmentRecover<Traits>::pushSegmentToQueue(index_t eid)
{
	AuxVector64<index_t> enc_verts;
	// Get the Steiner point to split the segment
	seg_steiner_point[eid] = getSteinerPoint(eid, enc_verts);
	// Evaluate the priority and push the segment into the queue
	double priority = getSegPriority(eid, seg_steiner_point[eid], enc_verts);
	seg_queue.push<AllowUpdate>(eid, priority);
}

/**
 * @brief Computes the Steiner point for segment recovery in constrained
 * Delaunay tetrahedralization.
 * This function identifies encroaching points on a given edge and determines a
 * Steiner point to split the segment.
 *
 * @param eid The index of the edge to be split.
 * @param enc_verts A vector to store indices of encroaching vertices.
 * @return The computed Steiner point.
 *
 * @note This function requires exact encroachment test.
 * @pre The edge type must be either PLCEdgeType::NO_ACUTE_VERTEX or
 * PLCEdgeType::ONE_ACUTE_VERTEX.
 */
template <typename Traits>
auto SegmentRecover<Traits>::getSteinerPoint(index_t               eid,
                                             AuxVector64<index_t> &enc_verts)
  -> IPoint_LNC
{
	// Find encroaching points
	index_t ref_vid, curr_tet;
	findReferenceEncroachingPoint(eid, ref_vid, curr_tet, &enc_verts);

	// Check the validity of encroaching points
	OMC_EXPENSIVE_ASSERT(!enc_verts.empty(), "Empty encroaching points.");

#if 0   // SiHang's strategy
	// Get the Steiner point to split the segment
	if (plc.edge(eid).type == PLCEdgeType::BOTH_ACUTE_VERTEX)
		return middlePoint(plc.edge(eid));
	else if (plc.edge(eid).type == PLCEdgeType::NO_ACUTE_VERTEX)
		return splitSegment_NoAcuteVertex(eid, ref_vid);
	else // ONE_ACUTE_VERTEX
		return splitSegment_OneAcuteVertex(eid, ref_vid);
#elif 0 // simple middle point strategy
	return middlePoint(plc.edge(eid));
#elif 1
	return reduceMostEncroachingPoints(eid, enc_verts);
#endif
}

/**
 * @brief Calculates the priority of a segment based on the number of reduced
 * encroaching points and encroaching segments.
 *
 * @param eid The index of the edge for which the priority is being calculated.
 * @param steiner_pnt The Steiner point used in the calculation.
 * @param enc_verts A vector of indices representing the encroaching vertices.
 * @return The calculated priority of the segment.
 */
template <typename Traits>
double SegmentRecover<Traits>::getSegPriority(
  index_t eid, const IPoint_LNC &steiner_pnt,
  const AuxVector64<index_t> &enc_verts) const
{
	const PLCEdge &e   = plc.edge(eid);
	// Get the endpoints of the edge.
	const GPoint  &ep0 = gpnt(e.ep0()), &ep1 = gpnt(e.ep1());
	const GPoint  &steiner_gpnt = static_cast<const GPoint &>(steiner_pnt);

	// 1. Calculate the number of reduced encroaching points
	size_t original_enc_verts = enc_verts.size();

	// Two diametral spheres defined by (ep0, steiner_pnt) and (ep1, steiner_pnt)
	size_t enc_s0 = 0, enc_s1 = 0;
	for (index_t vid : enc_verts)
	{
		const GPoint &pnt = gpnt(vid);
		if (inSphere(ep0, steiner_gpnt, pnt))
			enc_s0++;
		else if (inSphere(ep1, steiner_gpnt, pnt))
			enc_s1++;
	}
	size_t reduced_enc_verts = original_enc_verts - (enc_s0 + enc_s1);

	// 2. Calculate the number of encroaching segments by the Steiner point
	AuxVector64<index_t> possible_enc_segs;
	sph_tree.all_intersections(steiner_gpnt, possible_enc_segs);

	size_t num_enc_segs = 0;
	for (index_t possible_enc_eid : possible_enc_segs)
	{
		const PLCEdge &possible_enc_e = plc.edge(possible_enc_eid);
		if (inSphere(gpnt(possible_enc_e.ep0()), gpnt(possible_enc_e.ep1()),
		             steiner_gpnt))
			num_enc_segs++;
	}

	double priority = 1.0 * reduced_enc_verts - 0.1 * num_enc_segs;
	return priority;
}

template <typename Traits>
void SegmentRecover<Traits>::missingSegmentsInCavity(
  const AuxVector64<index_t> &cavity_tets,
  const AuxVector64<index_t> &cavity_corners,
  AuxVector64<index_t>       &missing_segs)
{
	// collect edges of cavity
	boost::container::flat_set<UIPair> cavity_edges;
	for (index_t tet_idoff : cavity_tets)
	{
		for (index_t i = 0; i < 3; i++)
		{
			index_t vi = tet_mesh.tetNode(tet_idoff + i);
			for (index_t j = i + 1; j < 4; j++)
			{
				index_t vj = tet_mesh.tetNode(tet_idoff + j);
				cavity_edges.insert(unique_pair(vi, vj));
			}
		}
	}
	// collect boundary edges of cavity
	boost::container::flat_set<UIPair> cavity_boundary_edges;
	for (index_t idoff : cavity_corners)
	{
		index_t id = TetMesh::clipId(idoff);
		index_t v1 = tet_mesh.tetNode(id + TetMesh::tetNi(idoff, 1)),
		        v2 = tet_mesh.tetNode(id + TetMesh::tetNi(idoff, 2)),
		        v3 = tet_mesh.tetNode(id + TetMesh::tetNi(idoff, 3));
		cavity_boundary_edges.insert(unique_pair(v1, v2));
		cavity_boundary_edges.insert(unique_pair(v2, v3));
		cavity_boundary_edges.insert(unique_pair(v3, v1));
	}
	// get inner edges of the cavity
	AuxVector64<UIPair> cavity_inner_edges;
	std::set_difference(
	  cavity_edges.begin(), cavity_edges.end(), cavity_boundary_edges.begin(),
	  cavity_boundary_edges.end(),
	  std::inserter(cavity_inner_edges, cavity_inner_edges.end()));
	// find missing segments in the cavity
	for (const UIPair &edge : cavity_inner_edges)
	{
		index_t vi = edge.first, vj = edge.second;
		index_t inner_eid = plc.edgeExists(vi, vj);
		if (is_valid_idx(inner_eid))
			missing_segs.push_back(inner_eid);
	}
}

template <typename Traits>
auto SegmentRecover<Traits>::reduceMostEncroachingPoints(
  index_t eid, const AuxVector64<index_t> &enc_verts) const -> IPoint_LNC
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
	// Get the interpolation parameters
	auto [t0, t1] = getInterpolateT(oep0, oep1, ep0, ep1);
	if (t1 < t0)
		std::swap(t0, t1);

	// Get the vectors of related points.
	Vec3 oe0_v = AsEP()(gpnt(oep0)).as_vec();
	Vec3 oe1_v = AsEP()(gpnt(oep1)).as_vec();
	Vec3 e0_v  = ToEP()(gpnt(ep0)).as_vec();
	Vec3 e1_v  = ToEP()(gpnt(ep1)).as_vec();

	using Interval = std::pair<double, double>;
	// find all intervals that reduce at least an encroaching point
	AuxVector64<Interval> intervals;
	for (index_t enc_vid : enc_verts)
	{
		Vec3   enc_v    = ToEP()(gpnt(enc_vid)).as_vec();
		// Calculate the valid interval
		double valid_t0 = linePlaneIntersection(oe0_v, oe1_v, enc_v, e0_v - enc_v);
		double valid_t1 = linePlaneIntersection(oe0_v, oe1_v, enc_v, e1_v - enc_v);
		// Ensure that the interval is inside the edge.
		if (valid_t1 < valid_t0)
			std::swap(valid_t0, valid_t1);
		valid_t0 = std::max(valid_t0, t0);
		valid_t1 = std::min(valid_t1, t1);

		intervals.emplace_back(valid_t0, valid_t1);
	}

	// find the interval that reduce the most encroaching points

	// -- cut the axis to smaller intervals by the endpoints of the intervals
	AuxVector64<double> cut_points;
	for (const Interval &interval : intervals)
	{
		cut_points.push_back(interval.first);
		cut_points.push_back(interval.second);
	}
	cut_points.erase(std::unique(cut_points.begin(), cut_points.end()),
	                 cut_points.end());

	phmap::flat_hash_map<double, index_t> cut_point_map;
	for (index_t i = 0; i < cut_points.size(); i++)
		cut_point_map[cut_points[i]] = i;

	// -- count all intervals that contain each interval
	AuxVector64<uint32_t> interval_count(cut_points.size() - 1, 0);
	for (const Interval &interval : intervals)
	{
		index_t start = cut_point_map[interval.first];
		index_t end   = cut_point_map[interval.second];
		for (index_t i = start; i < end; i++)
			interval_count[i]++;
	}

	// -- find the interval that has the maximum count
	auto max_count =
	  *std::max_element(interval_count.begin(), interval_count.end());

	// -- get the Steiner point to maximize sub-segments' length
	double t = -1.0, mid_t = (t0 + t1) * 0.5;
	for (index_t i = 0; i < cut_points.size() - 1; i++)
	{
		if (interval_count[i] != max_count)
			continue;

		double _t = -1.0;
		if (cut_points[i + 1] < mid_t)
			_t = cut_points[i + 1];
		else if (cut_points[i] > mid_t)
			_t = cut_points[i];
		else
			_t = mid_t;

		if (std::abs(_t - mid_t) < std::abs(t - mid_t))
			t = _t;
	}

	if (t <= t0 || t >= t1)
	{ // if invalid (maybe caused by numerical error), return the middle point
		t = (t0 + t1) * 0.5;
	}

	return CreateLNC()(gpnt(oep0), gpnt(oep1), t);
}

template <typename Traits>
double
SegmentRecover<Traits>::linePlaneIntersection(const Vec3 &e0, const Vec3 &e1,
                                              const Vec3 &p, const Vec3 &n)
{
	// The line is defined by two points e0 and e1.
	// The plane is defined by a point p and a normal vector n.

	// Let the intersection point be x = e0 + t * (e1 - e0).
	// x statisfy the plane equation: n dot (x - p) = 0.

	// So we can solve the equation: t = (n dot (p - e0)) / (n dot (e1 - e0)).
	return n.dot(p - e0) / n.dot(e1 - e0);
}

} // namespace OMC