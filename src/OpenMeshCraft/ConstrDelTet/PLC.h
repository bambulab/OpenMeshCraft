#pragma once

#include "Utils.h"

namespace OMC {

/**
 * @brief Piecewise linear complex (PLC) for constraints recovery.
 */
template <typename Traits>
class PiecewiseLinearComplex
{
public: /* Traits **********************************************************/
	using Self = PiecewiseLinearComplex<Traits>;

	using NT     = typename Traits::NT;
	using EPoint = typename Traits::EPoint;
	using GPoint = typename Traits::GPoint;

	using AsGP = typename Traits::AsGP;
	using AsEP = typename Traits::AsEP;
	using ToEP = typename Traits::ToEP;

	using Orient3D          = typename Traits::Orient3D;
	using CollinearPoints3D = typename Traits::CollinearPoints3D;
	using DotProduct3D      = typename Traits::DotProduct3D;
	using InSphere          = typename Traits::InSphere;

public: /* Auxiliary data structures ****************************************/
	/// The type of the edge in the PLC, determining the recovery strategy on
	/// edges.
	enum class PLCEdgeType
	{
		// The type of the edge is undetermined.
		UNDETERMINED,
		// The "flat" edges will be ignored by segment recovery algorithm and will
		// not be further classyfied.
		FLAT_EDGE,
		// The "both acute vertex" edges will be immediatelly split by inserting the
		// middle point (each sub-edge becomes "one acute vertex")
		BOTH_ACUTE_VERTEX,
		// sub-edges of "one acute vertex" inherit the same edge type
		ONE_ACUTE_VERTEX,
		// sub-edges of "no acute vertex" inherit the same edge type
		NO_ACUTE_VERTEX,
		// The edge is marked to be deleted.
		TO_DELETE
	};

	class PLCEdge
	{
	public: /* Data *********************************************************/
		/// The type of the edge.
		PLCEdgeType type;
		/// The indices of the endpoints of the edge.
		/// (In `ONC_ACUTE_VERTEX` case, acute vertex is at the first position.
		///  In other cases, the order is arbitrary.)
		IPair       ep;
		/// the ancestor (not the parent) edge is the original edge before splitting
		/// (set to InvalidIndex if this edge is not a sub-edge)
		index_t     ancestor_id;
		/// the child edge is the edge after splitting
		/// (set to InvalidIndex if this edge is not splitted)
		/// (every edge is splitted to two subsequent child edges)
		index_t     child_id;

	public: /* Constructors *************************************************/
		PLCEdge() = default;
		PLCEdge(index_t e0, index_t e1);
		PLCEdge(PLCEdgeType _type, index_t e0, index_t e1, index_t _ancestor_id,
		        index_t _child_id);

	public: /* Interfaces ***************************************************/
		index_t       &ep0() { return ep.first; }
		const index_t &ep0() const { return ep.first; }
		index_t       &ep1() { return ep.second; }
		const index_t &ep1() const { return ep.second; }

		void swapEp() { std::swap(ep.first, ep.second); }

		bool operator<(const PLCEdge &rhs) const { return ep < rhs.ep; }
		bool operator==(const PLCEdge &rhs) const { return ep == rhs.ep; }
	};

	class PLCFace
	{
	public: /* Data *********************************************************/
	};

public: /* Constructor & Destructor ****************************************/
	PiecewiseLinearComplex() = delete;
	PiecewiseLinearComplex(const std::vector<GPoint *> &_vertices,
	                       const std::vector<index_t>  &_edges,
	                       const std::vector<index_t>  &_triangles);

public: /* Interfaces ******************************************************/
	/* Initialize PLC edges and faces */
	void initPLCEdges();
	void initPLCFaces();

	/* Connectivity operations on PLC */

	GPoint       &pnt(index_t vid) { return *vertices[vid]; }
	const GPoint &pnt(index_t vid) const { return *vertices[vid]; }

	PLCEdge       &edge(index_t eid) { return plc_edges[eid]; }
	const PLCEdge &edge(index_t eid) const { return plc_edges[eid]; }

	PLCFace       &face(index_t fid) { return plc_faces[fid]; }
	const PLCFace &face(index_t fid) const { return plc_faces[fid]; }

	size_t numVertices() const { return vertices.size(); }
	size_t numEdges() const { return plc_edges.size(); }
	size_t numFaces() const { return plc_faces.size(); }

	index_t oppV2E(const PLCEdge &edge, index_t tid) const;

	void splitPLCEdge(index_t eid, index_t vid);

	/* Query auxiliary data */

	// clang-format off
	/// Number of incident triangles to the edge.
	size_t numEdgeIncTri(index_t eid) const { return edge_inc_tri[eid].size(); }
	/// Get the `j`-th incident triangle to the edge.
	index_t edgeIncTri(index_t eid, index_t j) { return edge_inc_tri[eid][j]; }
	// clang-format on

public: /* Data ************************************************************/
	/// The input vertices.
	const std::vector<GPoint *> &vertices;
	/// The input isolated edges (storing indices to vertices).
	const std::vector<index_t>  &edges;
	/// The input triangles (storing indices to vertices).
	const std::vector<index_t>  &triangles;

	const size_t input_nv; ///< number of input vertices
	const size_t input_ne; ///< number of input edges
	const size_t input_nt; ///< number of input triangles

	bool is_close_and_manifold; ///< whether the input is close and manifold

	/* Auxiliary data structures for PLC */

	std::vector<PLCEdge> plc_edges;

	/// Triangles incident to each edge.
	/// We only store incident triangles for original input edges, not for
	/// split edges.
	std::vector<AuxVector4<index_t>> edge_inc_tri;

	std::vector<PLCFace> plc_faces;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "PLC.inl"
#endif