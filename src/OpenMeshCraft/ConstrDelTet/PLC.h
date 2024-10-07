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
		PLCEdgeType type;

		/// The indices of the endpoints of the edge.
		IPair ep;

		/// The indices of the original(parent) endpoints of the edge.
		IPair oep;

		/// Incident triangles (indices to the input triangles).
		AuxVector4<index_t> inc_tri;

	public: /* Constructors *************************************************/
		PLCEdge() = default;
		PLCEdge(index_t e0, index_t e1);
		PLCEdge(index_t e0, index_t e1, index_t fi);
		PLCEdge(PLCEdgeType _type, index_t e0, index_t e1, index_t oe0, index_t oe1,
		        const AuxVector4<index_t> &_inc_tri);

	public: /* Interfaces ***************************************************/
		index_t       &ep0() { return ep.first; }
		const index_t &ep0() const { return ep.first; }
		index_t       &ep1() { return ep.second; }
		const index_t &ep1() const { return ep.second; }

		index_t       &oep0() { return oep.first; }
		const index_t &oep0() const { return oep.first; }
		index_t       &oep1() { return oep.second; }
		const index_t &oep1() const { return oep.second; }

		static bool less(const PLCEdge &e0, const PLCEdge &e1)
		{
			return e0.ep < e1.ep;
		}
		static bool equal(const PLCEdge &e0, const PLCEdge &e1)
		{
			return e0.ep == e1.ep;
		}
	};

	class PLCFace
	{
	public: /* Data *********************************************************/
	};

public: /* Constructor & Destructor ****************************************/
	PiecewiseLinearComplex() = default;

	void initialize(const std::vector<GPoint *> &_vertices,
	                const std::vector<index_t>  &_edges,
	                const std::vector<index_t>  &_triangles);

public: /* Interfaces ******************************************************/
	/* Connectivity operations on PLC */

	GPoint       &pnt(index_t vid) { return *vertices[vid]; }
	const GPoint &pnt(index_t vid) const { return *vertices[vid]; }

	index_t oppV2E(const PLCEdge &edge, index_t tid) const;

public: /* Data ************************************************************/
	/// The input vertices.
	std::vector<GPoint *> vertices;
	/// The input isolated edges (storing indices to vertices).
	std::vector<index_t>  edges;
	/// The input triangles (storing indices to vertices).
	std::vector<index_t>  triangles;

	size_t input_nv; ///< number of input vertices
	size_t input_ne; ///< number of input edges
	size_t input_nt; ///< number of input triangles

	bool is_close_and_manifold; ///< whether the input is close and manifold

	/* PLC */
	std::vector<PLCEdge> plc_edges;
	std::vector<PLCFace> plc_faces;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "PLC.inl"
#endif