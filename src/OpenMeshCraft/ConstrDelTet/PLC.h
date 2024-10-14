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

		void makeUniqEp() { ep = unique_pair(ep.first, ep.second); }
		void swapEp() { std::swap(ep.first, ep.second); }

		bool operator<(const PLCEdge &rhs) const { return ep < rhs.ep; }
		bool operator==(const PLCEdge &rhs) const { return ep == rhs.ep; }
	};

	/// A range of sub-edges for an original edge after splitting.
	struct SubEdgeRange
	{
		index_t orig_eid; ///< the index of the original edge.
		index_t start; ///< the position in `sub_edges` where the sub-edges start.
		index_t size;  ///< the number of sub-edges stored in `sub_edges`.

		// clang-format off
		SubEdgeRange() = default;
		SubEdgeRange(index_t _eid, index_t _start, index_t _size)
		  : orig_eid(_eid), start(_start), size(_size) {}
		SubEdgeRange(const SubEdgeRange &) = default;
		SubEdgeRange(SubEdgeRange &&)      = default;
		SubEdgeRange &operator=(const SubEdgeRange &rhs)
		{ orig_eid = rhs.orig_eid; start = rhs.start; size = rhs.size; return *this; }
		// clang-format on
	};

	struct BoundingEdge
	{
		SubEdgeRange range;    // sub-edge range
		index_t      tid;      // adjacent triangle (not PLC face) index
		bool         reversed; // whether the edge is reversed

		// clang-format off
		bool operator==(index_t eid) const { return range.orig_eid == eid; }
		bool operator==(const BoundingEdge &rhs) const { return range.orig_eid == rhs.range.orig_eid; }
		bool operator<(index_t eid) const { return range.orig_eid < eid; }
		bool operator<(const BoundingEdge &rhs) const { return range.orig_eid < rhs.range.orig_eid; }
		// clang-format on
	};

	class PLCFace
	{
	public: /* Data *********************************************************/
		/// Original triangles composing the face
		/// (triangle index, mutiple 3 with offset to point to `triangles`)
		AuxVector2<index_t> triangles;

		/// Edges bounding the face (index to `plc_edges`)
		/// - The face may not be simply connected, i.e., there may be holes and
		/// multiple disjoint boundaries.
		/// - Duplicate bounding edges may exist during construction, these
		/// duplicate edges may be subsequent or not. We will remove the duplicate
		/// edges finally.
		AuxVector4<BoundingEdge> bounding_edges;

		/// The unordered bounding vertices of the face (index to `vertices`)
		AuxVector4<index_t> bounding_vertices;
		/// The unordered flat vertices of the face (index to `vertices`)
		AuxVector4<index_t> flat_vertices;
	};

public: /* Constructor & Destructor ****************************************/
	PiecewiseLinearComplex() = delete;
	PiecewiseLinearComplex(const std::vector<GPoint *> &_vertices,
	                       const std::vector<index_t>  &_edges,
	                       const std::vector<index_t>  &_triangles);

public: /* Interfaces ******************************************************/
	/* Initialize PLC edges and faces ****************************************/
	void initPLCEdges();
	void initPLCFaces();

	/* Query on input constraints ********************************************/

	// clang-format off
	GPoint       &pnt(index_t vid) { return *vertices[vid]; }
	const GPoint &pnt(index_t vid) const { return *vertices[vid]; }

	index_t edgeVtx(index_t eid, index_t j) const { return edges[eid * 2 + j]; }

	index_t triVtx(index_t tid, index_t j) const { return triangles[tid * 3 + j]; }
	// clang-format on

	/* Connectivity operations on PLC ****************************************/

	PLCEdge       &edge(index_t eid) { return plc_edges[eid]; }
	const PLCEdge &edge(index_t eid) const { return plc_edges[eid]; }

	PLCFace       &face(index_t fid) { return plc_faces[fid]; }
	const PLCFace &face(index_t fid) const { return plc_faces[fid]; }

	size_t numVertices() const { return vertices.size(); }
	size_t numEdges() const { return plc_edges.size(); }
	size_t numFaces() const { return plc_faces.size(); }

	index_t oppV2E(const PLCEdge &edge, index_t tid) const;

	void splitPLCEdge(index_t eid, index_t vid);

	/* Query auxiliary data **************************************************/

	/* Query auxiliary data of a PLC edge */

	// clang-format off
	/// Number of incident triangles to the edge.
	size_t numEdgeIncTri(index_t eid) const { return edge_inc_tri[eid].size(); }
	/// Get the `j`-th incident triangle to the edge.
	index_t edgeIncTri(index_t eid, index_t j) { return edge_inc_tri[eid][j]; }
	// clang-format on

	/* Query auxiliary data of a PLC face */

	const PLCEdge &boundingEdge(const PLCFace &f, index_t eid,
	                            index_t *tid      = nullptr,
	                            bool    *reversed = nullptr) const;

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

	/// The edges in the PLC.
	std::vector<PLCEdge> plc_edges;

	/// The initial number of PLC edges.
	size_t init_npe;

	/// Triangles incident to each edge.
	/// We only store incident triangles for original input edges, not for
	/// split edges.
	std::vector<AuxVector4<index_t>> edge_inc_tri;

	/// Sub-edges range after splitting the original edges.
	std::vector<SubEdgeRange> sub_edge_range;

	/// All sub-edges are subsequently stored in this vector.
	std::vector<index_t> sub_edges;

	std::vector<PLCFace> plc_faces;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "PLC.inl"
#endif