#pragma once

#include "PLC.h"

namespace OMC {

/**
 * @brief Initializes a PLC edge with the given endpoints (`e0` and `e1`).
 *
 * This constructor is used to initialize a PLC edge at the beginning.
 */
template <typename Traits>
PiecewiseLinearComplex<Traits>::PLCEdge::PLCEdge(index_t e0, index_t e1)
  : type(PLCEdgeType::UNDETERMINED)
  , ep(unique_pair(e0, e1))
  , ancestor_id(InvalidIndex)
  , child_id(InvalidIndex)
  , acute_vid(InvalidIndex)
{
}

/**
 * @brief Initializes a PLC edge with the edge type (`_type`), the given
 * endpoints (`e0` and `e1`), the ancestor edge index, and the child edge index.
 *
 * This constructor is used to construct a PLC sub-edge after splitting.
 */
template <typename Traits>
PiecewiseLinearComplex<Traits>::PLCEdge::PLCEdge(PLCEdgeType _type, index_t e0,
                                                 index_t e1,
                                                 index_t _ancestor_id,
                                                 index_t _child_id,
                                                 index_t _acute_vid)
  : type(_type)
  , ep{e0, e1}
  , ancestor_id(_ancestor_id)
  , child_id(_child_id)
  , acute_vid(_acute_vid)
{
}

/**
 * @brief Initializes a PLC with the given vertices, edges and triangles.
 */
template <typename Traits>
PiecewiseLinearComplex<Traits>::PiecewiseLinearComplex(
  const std::vector<GPoint *> &_vertices, const std::vector<index_t> &_edges,
  const std::vector<index_t> &_triangles)
  : vertices(_vertices)
  , edges(_edges)
  , triangles(_triangles)
  , input_nv(_vertices.size())
  , input_ne(_edges.size() / 2)
  , input_nt(_triangles.size() / 3)
{
}

/**
 * @brief This function classifies the edges and vertices in the PLC, and build
 * PLC edges for later segment recovery.
 *
 * Vertices are classified into acute and non-acute vertices.
 * Based on the vertex types, edges are classified into different types (see
 * PLCEdgeType) for further recovery and splitting.
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - Section 3.3 Segment recovery, in [Robust CDT].
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::initPLCEdges()
{
	// (1) build initial PLC edges
	buildInitialPLCEdges();

	// (2) classify vertices and edges
	classifyVertEdge();

	// (3) initialize vertex incident edges
	initVertIncEdge();
}

/**
 * @brief Builds the initial Piecewise Linear Complex (PLC) edges.
 *
 * This function initializes the PLC edges from the input edges and triangles.
 * It ensures that the input PLC is valid (without intersections) and
 * initializes the input edges and triangles as PLC edges.
 *
 * @pre The input PLC is valid and does not contain intersections.
 * @post
 * - Input edges and triangles are initialized as PLC edges.
 * - Duplicate edges are merged.
 * - Incident triangles for each edge are recorded.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::buildInitialPLCEdges()
{
	// =========================================================================
	// # Build PLC edges
	// ## pre-condition: the input PLC is valid (without intersections).
	// ## post-condition: input edges and triangles are initialized as PLC edges.

	// ## Put all input edges into the PLC edges.
	//    Duplicate edges may exist, so they will be merged later.
	plc_edges.resize(input_nt * 3 + input_ne);
	edge_inc_tri.resize(input_nt * 3 + input_ne);

	for (index_t ti = 0; ti < input_nt; ti++)
	{
		index_t ti_v = ti * 3;
		for (index_t j = 0; j < 3; j++)
		{
			PLCEdge &e = plc_edges[ti_v + j];
			// Set type and endpoints
			e.type     = PLCEdgeType::UNDETERMINED;
			e.ep = unique_pair(triangles[ti_v + j], triangles[ti_v + (j + 1) % 3]);
			// Set the ancestor to remember where the incident triangles are stored.
			// The ancestor will be clear after initialization.
			e.ancestor_id = ti_v + j;
			e.child_id    = InvalidIndex;
			// Set the incident triangle
			edge_inc_tri[ti_v + j].push_back(ti);
		}
	}
	for (index_t eid = 0; eid < input_ne; eid++)
	{
		index_t ei_v                  = eid * 2;
		plc_edges[input_nt * 3 + eid] = PLCEdge(edges[ei_v], edges[ei_v + 1]);
	}

	// ## Merge the duplicate PLC edges

	// ### Sort edges by their unique endpoint pairs.
	std::sort(plc_edges.begin(), plc_edges.end(), std::less<PLCEdge>());

	// ### Merge the incident triangles of the same edge.
	for (index_t eid = 0; eid < plc_edges.size(); /*eid is updated in the loop */)
	{
		// record the first unique edge
		PLCEdge             &first_e       = plc_edges[eid];
		AuxVector4<index_t> &first_inc_tri = edge_inc_tri[first_e.ancestor_id];
		// find the subsequent duplicate edges
		while ((++eid) < plc_edges.size() && (first_e == plc_edges[eid]))
		{
			PLCEdge             &curr_e       = plc_edges[eid];
			AuxVector4<index_t> &curr_inc_tri = edge_inc_tri[curr_e.ancestor_id];
			// merge the incident triangle to the first edge
			if (curr_inc_tri.size() == 1)
				first_inc_tri.push_back(curr_inc_tri[0]);
			// clear the incident triangle, this edge will be removed later
			curr_inc_tri.clear();
			curr_e.type = PLCEdgeType::TO_DELETE;
		}
	}

	// ### Remove duplicate edges.
	plc_edges.erase(std::remove_if(plc_edges.begin(), plc_edges.end(),
	                               [](const PLCEdge &e)
	                               { return e.type == PLCEdgeType::TO_DELETE; }),
	                plc_edges.end());
	init_npe = plc_edges.size();
	// ### Restore incident triangles
	std::vector<AuxVector4<index_t>> tmp_edge_inc_tri(plc_edges.size());
	for (index_t eid = 0; eid < plc_edges.size(); eid++)
	{
		index_t &ancestor_id  = plc_edges[eid].ancestor_id;
		tmp_edge_inc_tri[eid] = std::move(edge_inc_tri[ancestor_id]);
		ancestor_id           = InvalidIndex;
	}
	edge_inc_tri = std::move(tmp_edge_inc_tri);
}

/**
 * @brief Classifies the vertices and edges of a Piecewise Linear Complex (PLC).
 *
 * This function performs the classification of vertices and edges in a PLC.
 * It first classifies edges as flat or undetermined, then classifies vertices
 * as acute or not, and finally classifies non-flat edges based on the number
 * of acute vertices they connect.
 *
 * @pre PLC edges are built.
 * @post PLC vertices are classified as acute or not, and PLC edges are
 * classified into different types.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::classifyVertEdge()
{
	// =========================================================================
	// # Classify edge and vertices
	// ## pre-condition: PLC edges are built.
	// ## post-condition: PLC vertices are classified to acute or not, and PLC
	//    edges are classified to different types.

	// vertex-vertex relation of the PLC
	std::vector<AuxVector16<index_t>> vv(input_nv);
	// vertex is acute or not
	std::vector<uint8_t>              is_acute_vertex(input_nv, false);

	auto isFlatEdge = [this](index_t eid) -> bool
	{
		const PLCEdge &e = edge(eid);
		return numEdgeIncTri(eid) == 2 &&
		       Orient3D()(pnt(e.ep0()), pnt(e.ep1()),
		                  pnt(oppV2E(e, edgeIncTri(eid, 0))),
		                  pnt(oppV2E(e, edgeIncTri(eid, 1)))) == Sign::ZERO;
	};

	auto isAcuteVert = [this, &vv](index_t vi) -> bool
	{
		const GPoint &vip = pnt(vi);
		for (index_t i = 0; i < vv[vi].size(); i++)
			for (index_t j = 0; j < i; j++)
				if (DotProduct3D()(pnt(vv[vi][i]), vip, pnt(vv[vi][j])) ==
				    Sign::POSITIVE)
					return true;

		return false;
	};

	// ## Traverse all edges to check if they are flat edges,
	//    and build the vertex-vertex relation at the same time.
	for (index_t eid = 0; eid < numEdges(); eid++)
	{
		PLCEdge &e = edge(eid);
		if (isFlatEdge(eid))
		{
			e.type = PLCEdgeType::FLAT_EDGE;
		}
		else
		{
			e.type = PLCEdgeType::UNDETERMINED;
			vv[e.ep0()].push_back(e.ep1());
			vv[e.ep1()].push_back(e.ep0());
			// Check close and manifold by checking the number of incident triangles.
			if (numEdgeIncTri(eid) != 2)
				is_close_and_manifold = false;
		}
	}

	// ## Traverse all vertices to check if they are acute vertices.
	for (index_t vi = 0; vi < input_nv; vi++)
		is_acute_vertex[vi] = isAcuteVert(vi);

	// ## Classify non-flat edges.
	for (index_t eid = 0; eid < numEdges(); eid++)
	{
		PLCEdge &e = edge(eid);
		// skip flat edges
		if (e.type == PLCEdgeType::FLAT_EDGE)
			continue;
		// count the number of acute vertices
		size_t acute_vertex_count =
		  (size_t)is_acute_vertex[e.ep0()] + (size_t)is_acute_vertex[e.ep1()];
		// classify the edge type based on the number of acute vertices
		if (acute_vertex_count == 0)
		{
			e.type      = PLCEdgeType::NO_ACUTE_VERTEX;
			e.acute_vid = InvalidIndex;
		}
		else if (acute_vertex_count == 2)
		{
			e.type      = PLCEdgeType::BOTH_ACUTE_VERTEX;
			e.acute_vid = InvalidIndex;
		}
		else
		{
			e.type = PLCEdgeType::ONE_ACUTE_VERTEX;
			if (is_acute_vertex[e.ep1()])
			{ // swap two endpoints to make the acute vertex at the first position
				e.swapEp();
			}
			e.acute_vid = e.ep0();
		}
	}
}

template <typename Traits>
void PiecewiseLinearComplex<Traits>::initVertIncEdge()
{
	vertex_inc_edge.resize(input_nv);
	for (index_t eid = 0; eid < numEdges(); eid++)
	{
		PLCEdge &e = edge(eid);
		if (e.type != PLCEdgeType::FLAT_EDGE)
		{
			vertex_inc_edge[e.ep0()].push_back(eid);
			vertex_inc_edge[e.ep1()].push_back(eid);
		}
	}
}

/**
 * @brief Initializes PLC faces with ordered sub-edges.
 *
 * This function initializes PLC faces with ordered sub-edges surrounding the
 * PLC face. Triangles across the flat edges are merged into one PLC face.
 * The sub-edges are sorted by their endpoints in a connected manner.
 *
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - Section 3.4 Face Recovery, in [Robust CDT].
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::initPLCFaces()
{
	// (1) Initialize the sub-edges for each original edge
	initSubEdges();

	// (2) Sort the sub-edges by their endpoints
	sortSubEdges();

	// (3) Assemble the sub-edges to faces
	assembleEdges2Faces();

	// (4) merge the faces across flat edges
	mergeFacesArossFlatEdges();

	// (5) remove duplicate bounding edges
	removeDuplicateBoundingEdges();

	// (6) extract bounding vertices
	extractBoundingVertices();
}

/**
 * @brief Initializes the sub-edges for each original edge in the Piecewise
 * Linear Complex (PLC).
 *
 * This function builds a map from each original edge to its sub-edges after
 * splitting. It uses a depth-first search to find all sub-edges for each
 * original edge and stores them in a sequential vector.
 *
 * @pre Segment recovery is done.
 * @post Sub-edges belonging to the same original edge are stored in a
 * sequential vector.
 *
 * Assertions:
 * - Ensures that the current edge is an original edge.
 * - Ensures that the size of the sub-edge range matches the expected size.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::initSubEdges()
{
	// =========================================================================
	// # We build a map from each original edge to its sub-edges after splitting.
	// ## pre-condition: segment recovery is done.
	// ## post-condition: sub-edges belong to the same original edge are put in a
	//   	sequential vector.

	auto findSubEdges = [this](index_t eid)
	{
		// deep first search to find all sub-edges for edge `ei`
		AuxVector64<index_t> sub_edge_stack;
		sub_edge_stack.push_back(eid);

		while (!sub_edge_stack.empty())
		{
			index_t curr_eid = sub_edge_stack.back();
			sub_edge_stack.pop_back();
			PLCEdge &curr_e = edge(curr_eid);

			if (is_valid_idx(curr_e.child_id))
			{
				// if the edge has child, push the child edges into the stack
				sub_edge_stack.push_back(curr_e.child_id);
				sub_edge_stack.push_back(curr_e.child_id + 1);
			}
			else
			{
				// if the edge does not have child, it is a sub-edge
				sub_edges.push_back(curr_eid);
			}
		}
	};

	sub_edge_range.reserve(numEdges());
	sub_edges.reserve(numEdges());

	// find all sub-edges for each original edge
	for (index_t eid = 0; eid < init_npe; eid++)
	{
		// skip the sub-edge (non-original edge)
		OMC_EXPENSIVE_ASSERT(!is_valid_idx(edge(eid).ancestor_id),
		                     "Not an ancestor PLC edge.");
		// the start position of sub-edges
		index_t sub_edge_start = sub_edges.size();
		// find all sub-edges and put them in `sub_edges`
		findSubEdges(eid);
		// record the range of sub-edges
		size_t sub_edge_size = sub_edges.size() - sub_edge_start;
		sub_edge_range.emplace_back(eid, sub_edge_start, sub_edge_size);

		OMC_EXPENSIVE_ASSERT(sub_edge_range.size() == eid + 1, "size mismatch.");
	}
}

/**
 * @brief Sorts sub-edges by their endpoints in a connected manner.
 *
 * This function sorts the sub-edges stored in `sub_edges` such that they are
 * ordered by their endpoints in a connected manner. It ensures that the
 * sub-edges form a continuous chain.
 *
 * @pre The sub-edges are properly stored in `sub_edges`.
 * @post The sub-edges are sorted in `sub_edges` by their endpoints in a
 * connected manner.
 *
 * Assertions:
 * - This function uses expensive assertions to verify the correctness of
 * the sorting.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::sortSubEdges()
{
	// =========================================================================
	// # Sort sub-edges by their endpoints in a connected manner
	// ## pre-condition: sub-edges are properly stored in `sub_edges`
	// ## post-condition: sub-edges are sorted in `sub_edges` by their endpoints
	//    in a connected manner

	for (const SubEdgeRange &range : sub_edge_range)
	{
		PLCEdge &e = edge(range.orig_eid);

		// Adjust endpoints of original edges to a unique pair
		e.makeUniqEp();
		if (range.size == 1)
		{ // This original edge is not split
			OMC_EXPENSIVE_ASSERT(sub_edges[range.start] == range.orig_eid,
			                     "Not the same original edge.");
			continue;
		}

		// Get the range of sub-edges
		index_t sub_edge_start = range.start;
		index_t sub_edge_end   = sub_edge_start + range.size;

		// Map from the endpoint to the sub-edge indices.
		// Note that each vertex has at most two adjacent sub-edges.
		phmap::flat_hash_map<index_t, IPair> ep_map2_sube;
		for (index_t i = sub_edge_start; i < sub_edge_end; i++)
		{
			index_t        sub_eid = sub_edges[i];
			const PLCEdge &sub_e   = edge(sub_eid);
			// map ep0 to sub_e
			if (ep_map2_sube.find(sub_e.ep0()) == ep_map2_sube.end())
				ep_map2_sube[sub_e.ep0()] = IPair(sub_eid, InvalidIndex);
			else
				ep_map2_sube[sub_e.ep0()].second = sub_eid;
			// map ep1 to sub_e
			if (ep_map2_sube.find(sub_e.ep1()) == ep_map2_sube.end())
				ep_map2_sube[sub_e.ep1()] = IPair(sub_eid, InvalidIndex);
			else
				ep_map2_sube[sub_e.ep1()].second = sub_eid;
		}

		// Sort sub-edges by their endpoints

		// Find and set the first sub-edge
		OMC_EXPENSIVE_ASSERT(!is_valid_idx(ep_map2_sube.at(e.ep0()).second) &&
		                       !is_valid_idx(ep_map2_sube.at(e.ep1()).second),
		                     "The original start and end points should have only "
		                     "one connected sub-edge.");

		index_t curr_vid = e.ep0(), last_eid = InvalidIndex;
		for (index_t i = sub_edge_start; i < sub_edge_end; i++)
		{
			IPair two_sub_eid = ep_map2_sube.at(curr_vid);
			// get the current edge different from the last edge
			sub_edges[i] =
			  two_sub_eid.second == last_eid ? two_sub_eid.first : two_sub_eid.second;
			PLCEdge &sube = edge(sub_edges[i]);
			// Adjust the order of the endpoints
			if (sube.ep1() == curr_vid)
				sube.swapEp();
			// update the vertex and edge in the iteration
			curr_vid = sube.ep1();
			last_eid = sub_edges[i];
		}

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		// check if the sub-edges are well connected
		for (index_t i = 0; i < range.size - 1; i++)
		{
			index_t        curr_i = sub_edge_start + i;
			index_t        next_i = sub_edge_start + i + 1;
			const PLCEdge &curr_e = edge(sub_edges[curr_i]);
			const PLCEdge &next_e = edge(sub_edges[next_i]);
			OMC_ASSERT(curr_e.ep1() == next_e.ep0(), "Not connected sub-edges.");
		}
#endif
	}
}

/**
 * @brief Assembles ordered sub-edges into each PLC (Piecewise Linear Complex)
 * face to form an ordered edge chain surrounding the PLC face.
 *
 * This function processes the sub-edges and associates them with their
 * corresponding PLC faces. It ensures that the sub-edges are ordered correctly
 * to form a continuous edge chain around each face.
 *
 * @pre Sub-edges are sorted in `sub_edges` by their endpoints.
 * @post PLC faces are built with ordered sub-edges.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::assembleEdges2Faces()
{
	// =========================================================================
	// # Assemble ordered sub-edges into each PLC face to form an ordered edge
	// chain surrounding the PLC face.
	// ## pre-condition: sub-edges are sorted in `sub_edges` by their endpoints
	// ## post-condition: PLC faces are built with ordered sub-edges

	plc_faces.resize(input_nt);
	for (index_t tid = 0; tid < input_nt; tid++)
	{
		plc_faces[tid].triangles.push_back(tid);
		plc_faces[tid].bounding_edges.resize(3);
		for (index_t j = 0; j < 3; j++)
			plc_faces[tid].bounding_edges[j].tid = InvalidIndex;
	}

	auto assembleEdges2Faces =
	  [this](const SubEdgeRange &range, PLCFace &f, index_t t_id)
	{
		OMC_EXPENSIVE_ASSERT(f.triangles.size() == 1 && f.triangles[0] == t_id,
		                     "Not the same triangle face.");

		index_t tv[3] = {triangles[f.triangles[0] * 3],
		                 triangles[f.triangles[0] * 3 + 1],
		                 triangles[f.triangles[0] * 3 + 2]};

		const PLCEdge &e     = edge(range.orig_eid);
		index_t        ev[2] = {e.ep0(), e.ep1()};

		for (int i = 0; i < 3; ++i)
		{
			if ((ev[0] == tv[i] && ev[1] == tv[(i + 1) % 3]) ||
			    (ev[0] == tv[(i + 1) % 3] && ev[1] == tv[i]))
			{
				OMC_EXPENSIVE_ASSERT(!is_valid_idx(f.bounding_edges[i].tid),
				                     "Already set.");
				f.bounding_edges[i].range    = range;
				f.bounding_edges[i].tid      = t_id;
				f.bounding_edges[i].reversed = !(ev[0] == tv[i]);
				return;
			}
		}
		OMC_ASSERT(false, "Impossible case. Cannot find the match edge.");
	};

	// Assemble edges to their incident faces
	for (index_t eid = 0; eid < init_npe; eid++)
	{
		OMC_EXPENSIVE_ASSERT(!is_valid_idx(edge(eid).ancestor_id),
		                     "Not an ancestor PLC edge.");
		for (index_t tid : edge_inc_tri[eid])
		{
			assembleEdges2Faces(sub_edge_range[eid], plc_faces[tid], tid);
		}
	}

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	for (index_t fid = 0; fid < input_nt; fid++)
	{
		const PLCFace &f = plc_faces[fid];
		for (const BoundingEdge &be : f.bounding_edges)
		{
			OMC_ASSERT(is_valid_idx(be.tid), "Bounding edge not set.");
		}
	}
#endif
}

/**
 * @brief Merges faces across flat edges in a Piecewise Linear Complex (PLC).
 *
 * This function merges faces in a PLC that are connected by flat edges. It
 * ensures that the resulting faces are properly connected and updates the
 * internal data structures accordingly.
 *
 * @pre Bounding edges must be built for each PLC face.
 * @post PLC faces are merged across flat PLC edges.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::mergeFacesArossFlatEdges()
{
	// =========================================================================
	// # Merge faces across flat PLC edges.
	// ## pre-condition: bounding edges are built for each PLC face.
	// ## post-condition: PLC faces are merged across flat PLC edges.

	// Map each PLC face to the merged face
	// (similar to union-find data structure)
	std::vector<index_t> remap(input_nt);
	std::iota(remap.begin(), remap.end(), 0);
	// find the merged face in the map
	auto findMergedFace = [&remap](index_t i)
	{
		while (remap[i] != i)
			i = remap[i];
		return i;
	};

	// merge `src_f` to `dst_f` across the flat edge `eid`
	auto mergePLCFace = [this](PLCFace &dst_f, PLCFace &src_f, index_t eid)
	{
		// both dst_edges and src_edges are connected rings.
		auto &dst_edges = dst_f.bounding_edges;
		auto &src_edges = src_f.bounding_edges;

		// find position to cut the both rings.
		// OPT consider very large PLC face (it may be common seen in CAD models).
		auto dst_pos = std::find(dst_edges.begin(), dst_edges.end(), eid);
		auto src_pos = std::find(src_edges.begin(), src_edges.end(), eid);
		OMC_ASSERT(dst_pos != dst_edges.end(), "Cannot find the flat edge.");
		OMC_ASSERT(src_pos != src_edges.end(), "Cannot find the flat edge.");

		// Check if the orientation of the edges is consistent
		if (dst_pos->reversed == src_pos->reversed)
		{ // Not consistent, reverse all edges in `src_f`
			for (BoundingEdge &be : src_edges)
				be.reversed = !be.reversed;
			std::reverse(src_edges.begin(), src_edges.end());
			src_pos = (src_edges.end() - 1) - (src_pos - src_edges.begin());
		}

		// `dst_edges` is cut to: begin |<-- 1 -->| dst_pos |<-- 4 -->| end
		// `src_edges` is cut to: begin |<-- 3 -->| src_pos |<-- 2 -->| end
		// Then they are connected as:
		// |<-- 1 -->| |<-- 2 -->| |<-- 3 -->| |<-- 4 -->|

		// Connect the cut rings by merging the edges
		AuxVector4<BoundingEdge> new_edges;
		new_edges.reserve(src_edges.size() + dst_edges.size());
		// Sequentially put cut rings (1,2,3,4) to the new ring `new_edges`
		if (dst_pos != dst_edges.begin())
			new_edges.insert(new_edges.end(), dst_edges.begin(), dst_pos);
		if (src_pos != src_edges.end())
			new_edges.insert(new_edges.end(), src_pos + 1, src_edges.end());
		if (src_pos != src_edges.begin())
			new_edges.insert(new_edges.end(), src_edges.begin(), src_pos);
		if (dst_pos != dst_edges.end())
			new_edges.insert(new_edges.end(), dst_pos + 1, dst_edges.end());

		dst_edges = std::move(new_edges);
		src_edges.clear();
		// Merge triangles
		dst_f.triangles.insert(dst_f.triangles.end(), src_f.triangles.begin(),
		                       src_f.triangles.end());
		src_f.triangles.clear();

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		// check dst_edges are well connected
		for (index_t i = 0; i < dst_edges.size(); i++)
		{
			index_t             next_i  = (i + 1) % dst_edges.size();
			const BoundingEdge &curr_be = dst_edges[i];
			const BoundingEdge &next_be = dst_edges[next_i];

			const PLCEdge &curr_e = edge(curr_be.range.orig_eid);
			const PLCEdge &next_e = edge(next_be.range.orig_eid);
			index_t curr_end_vid  = curr_be.reversed ? curr_e.ep0() : curr_e.ep1();
			index_t next_bgn_vid  = next_be.reversed ? next_e.ep1() : next_e.ep0();
			OMC_ASSERT(curr_end_vid == next_bgn_vid, "Not connected bounding edges.");
		}
#endif
	};

	for (index_t eid = 0; eid < init_npe; eid++)
	{
		const PLCEdge &e = edge(eid);
		// skip non-flat edge
		if (e.type != PLCEdgeType::FLAT_EDGE)
			continue;
		index_t t0 = findMergedFace(edgeIncTri(eid, 0));
		index_t t1 = findMergedFace(edgeIncTri(eid, 1));
		if (t0 == t1) // Do not merge these two faces
			continue;   // to avoid non-simply connected face.
		if (t0 > t1)
			std::swap(t0, t1); // Always merge to the lower face.

		mergePLCFace(face(t0), face(t1), eid); // merge the two faces
		remap[t1] = t0;                        // and adjust the map
	}

	// remove merged and empty faces
	plc_faces.erase(std::remove_if(plc_faces.begin(), plc_faces.end(),
	                               [](const PLCFace &f)
	                               { return f.triangles.empty(); }),
	                plc_faces.end());
}

template <typename Traits>
void PiecewiseLinearComplex<Traits>::removeDuplicateBoundingEdges()
{
	// Pre-condition: all faces are merged across flat edges.
	//   However, duplicate bounding edges may exist within a single face and may
	//   be sequential or non-sequential. Removing non-sequential duplicate edges
	//   may cause disjoint boundaries.
	// Post-condition: all faces have no duplicate bounding edges.

	// Remove duplicate bounding edges for each face
	// OPT consider very large PLC face (it may be common seen in CAD models).
	for (index_t fid = 0; fid < numFaces(); fid++)
	{
		PLCFace &f         = face(fid);
		auto    &bnd_edges = f.bounding_edges;

		if (bnd_edges.size() <= 4)
			continue; // A triangle or a quad face, no need to remove duplicate edges.

		// We first remove sequential duplicate bounding edges
		for (index_t i = 0; i < bnd_edges.size() - 1; /*i is updated in the loop*/)
		{
			BoundingEdge &curr_e = bnd_edges[i];
			BoundingEdge &next_e = bnd_edges[i + 1];
			if (curr_e == next_e)
			{
				OMC_EXPENSIVE_ASSERT(curr_e.reversed != next_e.reversed,
				                     "inconsistent orientation.");
				bnd_edges.erase(bnd_edges.begin() + i, bnd_edges.begin() + i + 2);
				i -= (i != 0);
			}
			else
				i += 1;
		}
		OMC_EXPENSIVE_ASSERT(bnd_edges.size() >= 3, "too few bounding edges.");
		// Note that bounding edges form a ring, we detect and remove
		// duplicate edges at beginning and ending.
		while (!bnd_edges.empty() && bnd_edges.front() == bnd_edges.back())
		{
			OMC_EXPENSIVE_ASSERT(bnd_edges.front().reversed !=
			                       bnd_edges.back().reversed,
			                     "inconsistent orientation.");
			std::rotate(bnd_edges.begin(), bnd_edges.begin() + 1, bnd_edges.end());
			bnd_edges.pop_back();
			bnd_edges.pop_back();
		}
		OMC_EXPENSIVE_ASSERT(bnd_edges.size() >= 3, "too few bounding edges.");

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		// check if all bounding edges are correctly connected
		for (index_t i = 0; i < bnd_edges.size(); i++)
		{
			index_t             next_i  = (i + 1) % bnd_edges.size();
			const BoundingEdge &curr_be = bnd_edges[i];
			const BoundingEdge &next_be = bnd_edges[next_i];

			const PLCEdge &curr_e = edge(curr_be.range.orig_eid);
			const PLCEdge &next_e = edge(next_be.range.orig_eid);
			index_t curr_end_vid  = curr_be.reversed ? curr_e.ep0() : curr_e.ep1();
			index_t next_bgn_vid  = next_be.reversed ? next_e.ep1() : next_e.ep0();
			OMC_ASSERT(curr_end_vid == next_bgn_vid, "Not connected bounding edges.");
		}
#endif

		// Then remove non-sequential duplicate bounding edges.
		// Note this removal will cut one boundary to multiple disjointed ones.
		// OPT sequential duplicate edges may still appear in this step, remove them
		// more efficiently?
		AuxVector4<BoundingEdge> tmp_bnd_edges = bnd_edges;
		std::sort(tmp_bnd_edges.begin(), tmp_bnd_edges.end());
		for (size_t i = 0; i < tmp_bnd_edges.size() - 1; i++)
		{
			if (tmp_bnd_edges[i] != tmp_bnd_edges[i + 1])
				continue;
			index_t eid        = tmp_bnd_edges[i].range.orig_eid;
			auto    first_pos  = std::find(bnd_edges.begin(), bnd_edges.end(), eid);
			auto    second_pos = std::find(first_pos + 1, bnd_edges.end(), eid);

			// `bnd_edges` is cut as:
			// begin |<-1->| first_pos |<-2->| second_pos |<-3->| end
			// Then they are connected as:
			// |<-1->||<-3->||<-2->|
			// Actually, |<-2->| is separated from the original ring to be a new ring.

			// temporary store |<-2->| in `new_edges`
			AuxVector4<BoundingEdge> new_edges(first_pos + 1, second_pos);
			// remove [ first_pos |<-2->| second_pos ] from the original ring
			bnd_edges.erase(first_pos, second_pos + 1);
			// append the |<-2->| to the `bnd_edges`
			bnd_edges.insert(bnd_edges.end(), new_edges.begin(), new_edges.end());
		}

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		// check if all bounding edges are correctly connected.
		// consider multiple disjointed boundaries.
		index_t curr_ring_start = 0;
		for (index_t i = 0; i < bnd_edges.size(); i++)
		{
			index_t             next_i  = (i + 1) % bnd_edges.size();
			const BoundingEdge &curr_be = bnd_edges[i];
			const BoundingEdge &next_be = bnd_edges[next_i];

			const PLCEdge &curr_e = edge(curr_be.range.orig_eid);
			const PLCEdge &next_e = edge(next_be.range.orig_eid);
			index_t curr_end_vid  = curr_be.reversed ? curr_e.ep0() : curr_e.ep1();
			index_t next_bgn_vid  = next_be.reversed ? next_e.ep1() : next_e.ep0();
			if (curr_end_vid == next_bgn_vid)
				continue; // current ring is still connected, continue to next edge
			// current ring is disconnected, check if it is a valid ring by returning
			// to the start point.
			const BoundingEdge &start_be = bnd_edges[curr_ring_start];
			const PLCEdge      &start_e  = edge(start_be.range.orig_eid);
			index_t start_vid = start_be.reversed ? start_e.ep1() : start_e.ep0();
			OMC_ASSERT(curr_end_vid == start_vid, "Not connected bounding edges.");
			// update the start position of the next ring
			curr_ring_start = next_i;
		}
#endif
	}
}

/**
 * @brief Extracts the bounding vertices for each face in the Piecewise Linear
 * Complex (PLC).
 *
 * This function processes each face in the PLC to extract its bounding vertices
 * and store them in the `bounding_vertices` and `flat_vertices` containers. It
 * ensures that all vertices of each PLC face are properly extracted and stored
 * without duplicates.
 *
 * @pre All PLC faces are properly merged, and no duplicate edges exist in any
 * PLC face.
 * @post All vertices of each PLC face are extracted and stored into
 * `bounding_vertices` and `flat_vertices`.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::extractBoundingVertices()
{
	// =========================================================================
	// # Extract vertices for each PLC face
	// ## pre-condition: all PLC faces are properly merged, and no duplicate edges
	// exist in PLC face.
	// ## post-condition: All vertices of each PLC face are extracted, and stored
	// into `bounding_vertices` and `flat_vertices`.

	for (index_t fid = 0; fid < numFaces(); fid++)
	{
		PLCFace &f = face(fid);
		// traverse bounding edges of this face and extract bounding vertices
		for (index_t eid = 0; eid < f.bounding_edges.size(); eid++)
		{
			const BoundingEdge &be    = f.bounding_edges[eid];
			const SubEdgeRange &range = be.range;
			// add each sub-edge's endpoint to the `vertices`
			for (index_t i = range.start; i < range.start + range.size; i++)
			{
				const PLCEdge &sub_e = edge(sub_edges[i]);
				// add which one of the endpoints is determined by the orientation
				f.bounding_vertices.push_back(be.reversed ? sub_e.ep1() : sub_e.ep0());
			}
		}
		// sort bounding vertices and remove duplicate vertices
		std::sort(f.bounding_vertices.begin(), f.bounding_vertices.end());
		f.bounding_vertices.erase(
		  std::unique(f.bounding_vertices.begin(), f.bounding_vertices.end()),
		  f.bounding_vertices.end());

		// traverse triangles of this face and extract all vertices
		AuxVector4<index_t> temp_flat_vertices;
		for (index_t tid : f.triangles)
		{
			temp_flat_vertices.push_back(triangles[tid * 3]);
			temp_flat_vertices.push_back(triangles[tid * 3 + 1]);
			temp_flat_vertices.push_back(triangles[tid * 3 + 2]);
		}
		// sort and remove duplicate vertices
		std::sort(temp_flat_vertices.begin(), temp_flat_vertices.end());
		temp_flat_vertices.erase(
		  std::unique(temp_flat_vertices.begin(), temp_flat_vertices.end()),
		  temp_flat_vertices.end());
		// subtract `bounding_vertices` from current `flat_vertices` to get
		// right `flat_vertices`
		std::set_difference(temp_flat_vertices.begin(), temp_flat_vertices.end(),
		                    f.bounding_vertices.begin(), f.bounding_vertices.end(),
		                    std::back_inserter(f.flat_vertices));
	}
}

/**
 * @brief Opposite vertex to the `edge` in the given triangle `tid`.
 */
template <typename Traits>
index_t PiecewiseLinearComplex<Traits>::oppV2E(const PLCEdge &edge,
                                               index_t        tid) const
{
	index_t vid;
	// clang-format off
	vid = triangles[tid * 3];
	if (vid != edge.ep0() && vid != edge.ep1()) return vid;
	vid = triangles[tid * 3 + 1];
	if (vid != edge.ep0() && vid != edge.ep1()) return vid;
	vid = triangles[tid * 3 + 2];
	if (vid != edge.ep0() && vid != edge.ep1()) return vid;
	// clang-format on
	return InvalidIndex;
}

template <typename Traits>
void PiecewiseLinearComplex<Traits>::splitPLCEdge(index_t eid, index_t vid)
{
	PLCEdge &e   = edge(eid);
	index_t  ep0 = e.ep0();
	index_t  ep1 = e.ep1();

	index_t ancestor_id = is_valid_idx(e.ancestor_id) ? e.ancestor_id : eid;
	// create two new edge
	if (e.type == PLCEdgeType::BOTH_ACUTE_VERTEX)
	{
		OMC_EXPENSIVE_ASSERT(!is_valid_idx(e.ancestor_id), "Not an ancestor edge.");
		// create two new edges with the type `ONE_ACUTE_VERTEX`
		// `ep0` and `ep1` are the closer vertex to the original acute vertices.
		// `vid` is the farther(opposite) vertex to the original acute vertices.
		plc_edges.emplace_back(PLCEdgeType::ONE_ACUTE_VERTEX, ep0, vid, ancestor_id,
		                       /*child_id*/ InvalidIndex, /*avute_vid*/ ep0);
		plc_edges.emplace_back(PLCEdgeType::ONE_ACUTE_VERTEX, ep1, vid, ancestor_id,
		                       /*child_id*/ InvalidIndex, /*acute_vid*/ ep1);
	}
	else // ONE_ACUTE_VERTEX or NO_ACUTE_VERTEX
	{
		PLCEdgeType new_type  = e.type;
		index_t     acute_vid = e.acute_vid;
		// create two new edges inherit the same edge type.
		// `ep0` is the vertex closer to the original acute vertex in <ep0, vid>,
		// so as `vid` in <vid, ep1>. This is to distinguish the closer vertex in
		// lineSphereIntersection_oneAc function in segment recovery.
		plc_edges.emplace_back(new_type, ep0, vid, ancestor_id,
		                       /*child_id*/ InvalidIndex, acute_vid);
		plc_edges.emplace_back(new_type, vid, ep1, ancestor_id,
		                       /*child_id*/ InvalidIndex, acute_vid);
	}
	index_t child_id   = plc_edges.size() - 2;
	edge(eid).child_id = child_id;

	// remove original edge from two endpoints' incident edges
	*std::find(vertex_inc_edge[ep0].begin(), vertex_inc_edge[ep0].end(), eid) =
	  vertex_inc_edge[ep0].back();
	*std::find(vertex_inc_edge[ep1].begin(), vertex_inc_edge[ep1].end(), eid) =
	  vertex_inc_edge[ep1].back();
	vertex_inc_edge[ep0].pop_back();
	vertex_inc_edge[ep1].pop_back();
	// add two new edges to three endpoints' incident edges
	OMC_EXPENSIVE_ASSERT(vertex_inc_edge.size() == vid, "size mismatch.");
	vertex_inc_edge.emplace_back();
	vertex_inc_edge[ep0].push_back(child_id);
	vertex_inc_edge[vid].push_back(child_id);
	vertex_inc_edge[vid].push_back(child_id + 1);
	vertex_inc_edge[ep1].push_back(child_id + 1);
}

/**
 * @brief Checks if an edge exists between two vertices in the Piecewise Linear
 * Complex (PLC).
 *
 * @param e0 The index of the first vertex.
 * @param e1 The index of the second vertex.
 * @return The index of the edge connecting `e0` and `e1` if it exists,
 * otherwise returns `InvalidIndex`.
 */
template <typename Traits>
index_t PiecewiseLinearComplex<Traits>::edgeExists(index_t e0, index_t e1) const
{
	// This function iterates through all edges incident to the vertex `e0` and
	// checks if any of these edges connect to the vertex `e1`.
	// If such an edge is found, its index is returned.
	for (index_t eid : vertex_inc_edge[e0])
	{
		const PLCEdge &e = edge(eid);
		if (e.ep1() == e1 || e.ep0() == e1)
			return eid;
	}
	return InvalidIndex;
}

/**
 * @brief Get the `eid`-th bounding edge of a PLC face `fid`.
 * @param [in] f the PLC face.
 * @param [in] eid index to the bounding edge in the PLC face.
 * @param [out] tid the incident input triangle index to the bounding edge.
 * @param [out] reversed the orientation of the bounding edge.
 * @return the bounding edge (PLCEdge).
 */
template <typename Traits>
auto PiecewiseLinearComplex<Traits>::boundingEdge(const PLCFace &f, index_t eid,
                                                  index_t *tid,
                                                  bool    *reversed) const
  -> const PLCEdge &
{
	OMC_EXPENSIVE_ASSERT(!f.bounding_edges.empty(), "empty bounding edges.");

	index_t first = 0;
	for (const BoundingEdge &be : f.bounding_edges)
	{
		if (first + be.range.size > eid)
		{
			if (tid)
				*tid = be.tid;
			if (reversed)
				*reversed = be.reversed;
			return edge(sub_edges[be.range.start + eid - first]);
		}
		first += be.range.size;
	}

	OMC_ASSERT(false, "Invalid index to the bounding edge.");
}

/**
 * @brief Builds a set of adjacent vertex pairs for a given face.
 *
 * This function iterates over the bounding edges of the provided face and
 * inserts unique pairs of vertices into the provided set of adjacent vertices.
 *
 * @tparam IndexPairSet The type of the set used to store adjacent vertex pairs.
 *
 * @param f The face for which to build the set of adjacent vertex pairs.
 * @param adj_vtx The set to store the adjacent vertex pairs.
 */
template <typename Traits>
template <typename IndexPairSet>
void PiecewiseLinearComplex<Traits>::buildBoundingVtxAdjSet(
  const PLCFace &f, IndexPairSet &adj_vtx) const
{
	for (const BoundingEdge &be : f.bounding_edges)
	{
		const SubEdgeRange &range = be.range;
		for (index_t i = range.start; i < range.start + range.size; i++)
		{
			const PLCEdge &sub_e = edge(sub_edges[i]);
			adj_vtx.insert(unique_pair(sub_e.ep0(), sub_e.ep1()));
		}
	}
}

} // namespace OMC