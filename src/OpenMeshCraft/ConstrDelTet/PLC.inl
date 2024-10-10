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
	// # Build PLC edges =========================================================

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
	// ### Restore incident triangles
	std::vector<AuxVector4<index_t>> tmp_edge_inc_tri(plc_edges.size());
	for (index_t eid = 0; eid < plc_edges.size(); eid++)
	{
		index_t &ancestor_id  = plc_edges[eid].ancestor_id;
		tmp_edge_inc_tri[eid] = std::move(edge_inc_tri[ancestor_id]);
		ancestor_id           = InvalidIndex;
	}
	edge_inc_tri = std::move(tmp_edge_inc_tri);

	// # Classify edge and vertices ===========================================

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
	//   	subsequent vector.

	// The sub-edges range for each original edge.
	// The first index point to the position in `sub_edges` where the sub-edges
	// start and are subsequently stored.
	// The second size is the number of sub-edges stored in `sub_edges`.
	std::vector<std::pair<index_t, size_t>> sub_edge_range;

	// All sub-edges are subsequently stored in this vector.
	std::vector<index_t> sub_edges;

	auto findSubEdges = [this, &sub_edges](index_t eid)
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
	for (index_t ei = 0; ei < numEdges(); ei++)
	{
		const PLCEdge &e = edge(ei);
		// skip the sub-edge (non-original edge)
		if (is_valid_idx(e.ancestor_id))
			continue;
		// the start position of sub-edges
		index_t sub_edge_start = sub_edges.size();
		// find all sub-edges and put them in `sub_edges`
		findSubEdges(ei);
		// record the range of sub-edges
		size_t sub_edge_size = sub_edges.size() - sub_edge_start;
		sub_edge_range.emplace_back(sub_edge_start, sub_edge_size);
	}

	// =========================================================================
	// # Sort sub-edges by their endpoints in a connected manner
	// ## pre-condition: sub-edges are properly stored in `sub_edges`
	// ## post-condition: sub-edges are sorted in `sub_edges` by their endpoints
	//    in a connected manner

	for (index_t ei = 0; ei < numEdges(); ei++)
	{
		PLCEdge &e = edge(ei);

		// Adjust endpoints of original edges to a unique pair
		e.ep = unique_pair(e.ep0(), e.ep1());

		// Get the range of sub-edges
		index_t sub_edge_start = sub_edge_range[ei].first;
		index_t sub_edge_end   = sub_edge_start + sub_edge_range[ei].second;

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
		index_t curr_vid = e.ep0();
		index_t i        = sub_edge_start;
		while (curr_vid != e.ep1())
		{
			if (first_ep_map.find(curr_vid) != first_ep_map.end())
			{
				sub_edges[i] = first_ep_map.at(curr_vid);
				curr_vid     = edge(sub_edges[i]).ep1();
			}
			else if (second_ep_map.find(curr_vid) != second_ep_map.end())
			{
				sub_edges[i] = second_ep_map.at(curr_vid);
				edge(sub_edges[i]).swapEp();
				curr_vid = edge(sub_edges[i]).ep1();
			}
			else
			{
				OMC_ASSERT(false, "Impossible case. Cannot find the next sub-edge.");
			}
		}

		// TODO Add a validity check
	}

	// =========================================================================
	// # Assemble ordered sub-edges into each PLC face to form an ordered edge
	// chain surrounding the PLC face.
	// ## pre-condition: sub-edges are sorted in `sub_edges` by their endpoints
	// ## post-condition: PLC faces are built with ordered sub-edges
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
	// create two new edge
	if (e.type == PLCEdgeType::BOTH_ACUTE_VERTEX)
	{
		// create two new edges with the type `ONE_ACUTE_VERTEX`
		plc_edges.emplace_back(PLCEdgeType::ONE_ACUTE_VERTEX, ep0, vid,
		                       e.ancestor_id,
		                       /*child_id*/ InvalidIndex);
		plc_edges.emplace_back(PLCEdgeType::ONE_ACUTE_VERTEX, ep1, vid,
		                       e.ancestor_id,
		                       /*child_id*/ InvalidIndex);
	}
	else // ONE_ACUTE_VERTEX or NO_ACUTE_VERTEX
	{
		// create two new edges inherit the same edge type
		plc_edges.emplace_back(e.type, ep0, vid, e.ancestor_id,
		                       /*child_id*/ InvalidIndex);
		plc_edges.emplace_back(e.type, vid, ep1, e.ancestor_id,
		                       /*child_id*/ InvalidIndex);
	}
	e.child_id = plc_edges.size() - 2;
}

} // namespace OMC