#pragma once

#include "DelaunayTet.h"
#include "PLC.h"
#include "TetMesh.h"

namespace OMC {

/**
 * @brief Recover the constraints in CDT algorithm.
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - [Si and Gärtner 2005] Hang Si and Klaus Gärtner. 2005. Meshing Piecewise
 * 	 Linear Complexes by Constrained Delaunay Tetrahedralizations. Proceedings
 *   of the 14th International Meshing Roundtable, 147–163.
 */
template <typename Traits>
class ConstraintsRecover
{
public: /* Traits **********************************************************/
	using Self = DelaunayTet<Traits>;

	using NT     = typename Traits::NT;
	using EPoint = typename Traits::EPoint;
	using GPoint = typename Traits::GPoint;

	using AsGP = typename Traits::AsGP;
	using AsEP = typename Traits::AsEP;
	using ToEP = typename Traits::ToEP;

	using Orient3D          = typename Traits::Orient3D;
	using CollinearPoints3D = typename Traits::CollinearPoints3D;
	using InSphere          = typename Traits::InSphere;

	using TetMesh = TetrahedralMesh<Traits>;
	using PLC     = PiecewiseLinearComplex<Traits>;

	using DelTet = DelaunayTet<Traits>;

public: /* Constructor & Destructor ****************************************/
	ConstraintsRecover() = delete;
	ConstraintsRecover(std::vector<GPoint *> &_verts, TetMesh &_tet_mesh,
	                   PLC &_plc);

public: /* Algorithms ******************************************************/
	/* Recover constrained segments */

	void segmentRecovery();

	/* sub-algorithms for segment recovery */

	index_t splitMissingSegment(index_t eid);

	void findReferenceEncroachingPoint(index_t eid, index_t &ref_vid,
	                                   index_t &ref_tid);

	index_t splitAtMiddle(index_t eid);

	index_t splitSegment_NoAcuteVertex(index_t eid, index_t ref_vid);

	index_t splitSegment_OneAcuteVertex(index_t eid, index_t ref_vid);

	/* Geometric & Topologic Operations on both TetMesh & PLC */

	GPoint       &gpnt(index_t vid) { return *verts[vid]; }
	const GPoint &gpnt(index_t vid) const { return *verts[vid]; }

	index_t newVtx(GPoint *new_pnt);

public: /* Data ************************************************************/
	/// vertices (stored by both `tet_mesh` and `plc`)
	std::vector<GPoint *> &verts;
	/// Tetrahedral mesh
	TetMesh               &tet_mesh;
	/// Constrained piecewise linear complex
	PLC                   &plc;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ConstrRecover.inl"
#endif