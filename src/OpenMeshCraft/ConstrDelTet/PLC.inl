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
  , oep(unique_pair(e0, e1))
{
}

/**
 * @brief Initializes a PLC edge with the given endpoints (`e0` and `e1`) and
 * the incident triangle (`fi`).
 *
 * This constructor is used to initialize a PLC edge at the beginning.
 */
template <typename Traits>
PiecewiseLinearComplex<Traits>::PLCEdge::PLCEdge(index_t e0, index_t e1,
                                                 index_t fi)
  : type(PLCEdgeType::UNDETERMINED)
  , ep(unique_pair(e0, e1))
  , oep(unique_pair(e0, e1))
{
	inc_tri.push_back(fi);
}

/**
 * @brief Initializes a PLC edge with the edge type (`_type`), the given
 * endpoints (`e0` and `e1`), the given original endpoints (`oe0` and `oe1`) and
 * the incident triangles (`_inc_tri`).
 *
 * This constructor is used to construct a PLC sub-edge after splitting.
 */
template <typename Traits>
PiecewiseLinearComplex<Traits>::PLCEdge::PLCEdge(
  PLCEdgeType _type, index_t e0, index_t e1, index_t oe0, index_t oe1,
  const AuxVector4<index_t> &_inc_tri)
  : type(_type)
  , ep{e0, e1}
  , oep{oe0, oe1}
  , inc_tri(_inc_tri)
{
}

/**
 * @brief Initializes a PLC with the given vertices, edges and triangles.
 * 
 * This constructor classifies the edges and vertices in the PLC.
 * Vertices are classified into acute and non-acute vertices.
 * Based on the vertex types, edges are classified into different types (see
 * PLCEdgeType) for further recovery and splitting.
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - [Si and Gärtner 2005] Hang Si and Klaus Gärtner. 2005. Meshing Piecewise
 * 	 Linear Complexes by Constrained Delaunay Tetrahedralizations. Proceedings
 *   of the 14th International Meshing Roundtable, 147–163.
 */
template <typename Traits>
void PiecewiseLinearComplex<Traits>::initialize(
  const std::vector<GPoint *> &_vertices, const std::vector<index_t> &_edges,
  const std::vector<index_t> &_triangles)
{
	vertices  = _vertices;
	edges     = _edges;
	triangles = _triangles;
	input_nv  = _vertices.size();
	input_ne  = _edges.size() / 2;
	input_nt  = _triangles.size() / 3;
	// # Build PLC edges =========================================================

	// ## Put all triangle edges into the PLC edges.
	//    Duplicate edges may exist, so they will be merged later.
	plc_edges.resize(input_nt * 3 + input_ne);

	for (index_t ti = 0; ti < input_nt; ti++)
	{
		index_t ti_v        = ti * 3;
		plc_edges[ti_v]     = PLCEdge(triangles[ti_v], triangles[ti_v + 1], ti);
		plc_edges[ti_v + 1] = PLCEdge(triangles[ti_v + 1], triangles[ti_v + 2], ti);
		plc_edges[ti_v + 2] = PLCEdge(triangles[ti_v], triangles[ti_v + 2], ti);
	}
	for (index_t ei = 0; ei < input_ne; ei++)
	{
		index_t ei_v                 = ei * 2;
		plc_edges[input_nt * 3 + ei] = PLCEdge(edges[ei_v], edges[ei_v + 1]);
	}

	// ## Merge the duplicate PLC edges

	// ### Sort edges by their unique endpoint pairs.
	std::sort(plc_edges.begin(), plc_edges.end(), PLCEdge::less);

	// ### Merge the incident triangles of the same edge.
	for (index_t ei = 0; ei < plc_edges.size(); /*ei is updated in the loop */)
	{
		// record the first unique edge
		PLCEdge &e = plc_edges[ei];
		// find the subsequent duplicate edges
		while ((++ei) < plc_edges.size() && PLCEdge::equal(e, plc_edges[ei]))
		{
			// merge the incident triangle to the first edge
			if (plc_edges[ei].inc_tri.size() == 1)
				e.inc_tri.push_back(plc_edges[ei].inc_tri[0]);
			// clear the incident triangle, this edge will be removed later
			plc_edges[ei].inc_tri.clear();
			plc_edges[ei].type = PLCEdgeType::TO_DELETE;
		}
	}

	// ### Remove duplicate edges.
	plc_edges.erase(std::remove_if(plc_edges.begin(), plc_edges.end(),
	                               [](const PLCEdge &e)
	                               { return e.type == PLCEdgeType::TO_DELETE; }),
	                plc_edges.end());
	// # Classify edge and vertices =============================================

	// vertex-vertex relation of the PLC
	std::vector<AuxVector16<index_t>> vv(input_nv);
	// vertex is acute or not
	std::vector<uint8_t>              is_acute_vertex(input_nv, false);

	auto isFlatEdge = [this](const PLCEdge &edge) -> bool
	{
		return edge.inc_tri.size() == 2 &&
		       Orient3D()(pnt(edge.ep0()), pnt(edge.ep1()),
		                  pnt(oppV2E(edge, edge.inc_tri[0])),
		                  pnt(oppV2E(edge, edge.inc_tri[1]))) == Sign::ZERO;
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
	for (index_t ei = 0; ei < plc_edges.size(); ei++)
	{
		PLCEdge &e = plc_edges[ei];
		if (isFlatEdge(e))
		{
			e.type = PLCEdgeType::FLAT_EDGE;
		}
		else
		{
			e.type = PLCEdgeType::UNDETERMINED;
			vv[e.ep0()].push_back(e.ep1());
			vv[e.ep1()].push_back(e.ep0());
			// Check close and manifold by checking the number of incident triangles.
			if (e.inc_tri.size() != 2)
				is_close_and_manifold = false;
		}
	}

	// ## Traverse all vertices to check if they are acute vertices.
	for (index_t vi = 0; vi < input_nv; vi++)
		is_acute_vertex[vi] = isAcuteVert(vi);

	// ## Classify non-flat edges.
	for (index_t ei = 0; ei < edges.size(); ei++)
	{
		PLCEdge &e = plc_edges[ei];
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
				std::swap(e.ep0(), e.ep1());
				std::swap(e.oep0(), e.oep1());
			}
		}
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

} // namespace OMC