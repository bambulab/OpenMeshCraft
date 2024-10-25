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
                                                 index_t _child_id)
  : type(_type)
  , ep{e0, e1}
  , ancestor_id(_ancestor_id)
  , child_id(_child_id)
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
			e.ep = unique_pair(triangles[ti_v + j], triangles[(ti_v + j + 1) % 3]);
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
			e.type = PLCEdgeType::NO_ACUTE_VERTEX;
		else if (acute_vertex_count == 2)
			e.type = PLCEdgeType::BOTH_ACUTE_VERTEX;
		else
		{
			e.type = PLCEdgeType::ONE_ACUTE_VERTEX;
			if (is_acute_vertex[e.ep1()])
			{ // swap two endpoints to make the acute vertex at the first position
				e.swapEp();
			}
		}
	}
}

/**
 * @brief
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

		// Get the range of sub-edges
		index_t sub_edge_start = range.start;
		index_t sub_edge_end   = sub_edge_start + range.size;

		// Map from the first/second endpoint to the sub-edge index
		phmap::flat_hash_map<index_t, index_t> first_ep_map;
		phmap::flat_hash_map<index_t, index_t> second_ep_map;
		for (index_t i = sub_edge_start; i < sub_edge_end; i++)
		{
			const PLCEdge &sub_e       = edge(sub_edges[i]);
			first_ep_map[sub_e.ep0()]  = sub_edges[i];
			second_ep_map[sub_e.ep1()] = sub_edges[i];
		}

		// Sort sub-edges by their endpoints
		for (index_t i = sub_edge_start, curr_vid = e.ep0(); curr_vid != e.ep1();)
		{
			if (first_ep_map.find(curr_vid) != first_ep_map.end())
			{
				sub_edges[i] = first_ep_map.at(curr_vid);
			}
			else if (second_ep_map.find(curr_vid) != second_ep_map.end())
			{
				sub_edges[i] = second_ep_map.at(curr_vid);
				edge(sub_edges[i]).swapEp();
			}
			else
			{
				OMC_ASSERT(false, "Impossible case. Cannot find the next sub-edge.");
			}
			// update the current vertex and iterator
			curr_vid = edge(sub_edges[i]).ep1();
			i++;
		}

		// TODO Add a validity check
	}

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
			if (ev[0] == tv[i] && ev[1] == tv[(i + 1) % 3])
			{
				f.bounding_edges[i].range    = range;
				f.bounding_edges[i].tid      = t_id;
				f.bounding_edges[i].reversed = false;
				return;
			}
			else if (ev[0] == tv[(i + 1) % 3] && ev[1] == tv[i])
			{
				f.bounding_edges[i].range    = range;
				f.bounding_edges[i].tid      = t_id;
				f.bounding_edges[i].reversed = true;
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
			PLCFace &f = plc_faces[tid];
			assembleEdges2Faces(sub_edge_range[eid], f, tid);
		}
	}

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

	// At this point, all faces are merged across flat edges.
	// However, duplicate bounding edges may exist within a single face and may be
	// sequential or non-sequential.
	// Removing non-sequential duplicate edges may cause disjoint boundaries.

	// Remove duplicate bounding edges for each face
	// OPT consider very large PLC face (it may be common seen in CAD models).
	for (index_t fid = 0; fid < input_nt; fid++)
	{
		PLCFace &f         = face(fid);
		auto    &bnd_edges = f.bounding_edges;

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
		// TODO add a validity check

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
	}

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// Validity check: check if all faces are properly merged
	for (index_t eid = 0; eid < init_npe; eid++)
	{
		PLCEdge &e = edge(eid);
		if (e.type != PLCEdgeType::FLAT_EDGE)
			continue;
		index_t t0 = findMergedFace(edgeIncTri(eid, 0));
		index_t t1 = findMergedFace(edgeIncTri(eid, 1));
		OMC_ASSERT(t0 == t1 && face(t1).triangles.empty(),
		           "Faces are not properly merged.");
		// TODO more checks
	}
#endif

	// remove merged and empty faces
	plc_faces.erase(std::remove_if(plc_faces.begin(), plc_faces.end(),
	                               [](const PLCFace &f)
	                               { return f.triangles.empty(); }),
	                plc_faces.end());

	// =========================================================================
	// # Extract vertices for each PLC face
	// ## pre-condition: all PLC faces are properly merged, and no duplicate edges
	// exist in PLC face.
	// ## post-condition: All vertices of each PLC face are extracted, and stored
	// into `bounding_vertices` and `flat_vertices`.

	for (index_t fid = 0; fid < input_nt; fid++)
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
		// traverse triangles of this face and extract all vertices
		for (index_t tid : f.triangles)
		{
			f.flat_vertices.push_back(triangles[tid * 3]);
			f.flat_vertices.push_back(triangles[tid * 3 + 1]);
			f.flat_vertices.push_back(triangles[tid * 3 + 2]);
		}
		// sort and remove duplicate vertices
		std::sort(f.flat_vertices.begin(), f.flat_vertices.end());
		f.flat_vertices.erase(
		  std::unique(f.flat_vertices.begin(), f.flat_vertices.end()),
		  f.flat_vertices.end());
		// sort bounding vertices
		std::sort(f.bounding_vertices.begin(), f.bounding_vertices.end());
		// subtract `bounding_vertices` from current `flat_vertices` to get
		// right `flat_vertices`
		AuxVector4<index_t> temp_flat_vertices;
		std::set_difference(f.flat_vertices.begin(), f.flat_vertices.end(),
		                    f.bounding_vertices.begin(), f.bounding_vertices.end(),
		                    std::back_inserter(temp_flat_vertices));
		f.flat_vertices = std::move(temp_flat_vertices);

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		// check if there are duplicate bounding_vertices
		OMC_ASSERT(
		  std::unique(f.bounding_vertices.begin(), f.bounding_vertices.end()) ==
		    f.bounding_vertices.end(),
		  "Duplicate vertices in PLC face.");
#endif
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
		// create two new edges with the type `ONE_ACUTE_VERTEX`
		plc_edges.emplace_back(PLCEdgeType::ONE_ACUTE_VERTEX, ep0, vid, ancestor_id,
		                       /*child_id*/ InvalidIndex);
		plc_edges.emplace_back(PLCEdgeType::ONE_ACUTE_VERTEX, ep1, vid, ancestor_id,
		                       /*child_id*/ InvalidIndex);
	}
	else // ONE_ACUTE_VERTEX or NO_ACUTE_VERTEX
	{
		PLCEdgeType new_type = e.type;
		// create two new edges inherit the same edge type
		plc_edges.emplace_back(new_type, ep0, vid, ancestor_id,
		                       /*child_id*/ InvalidIndex);
		plc_edges.emplace_back(new_type, vid, ep1, ancestor_id,
		                       /*child_id*/ InvalidIndex);
	}
	edge(eid).child_id = plc_edges.size() - 2;
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
auto PiecewiseLinearComplex<Traits>::boundingEdge(
  const PLCFace &f, index_t eid, index_t *tid,
  bool *reversed) const -> const PLCEdge &
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