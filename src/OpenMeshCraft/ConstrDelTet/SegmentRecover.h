#pragma once

#include "DelaunayTet.h"
#include "PLC.h"
#include "TetMesh.h"
#include "Tree.h"

namespace OMC {

/**
 * @brief Recover the segment constraints in CDT algorithm.
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - [Si and Gärtner 2005] Hang Si and Klaus Gärtner. 2005. Meshing Piecewise
 * 	 Linear Complexes by Constrained Delaunay Tetrahedralizations. Proceedings
 *   of the 14th International Meshing Roundtable, 147–163.
 */
template <typename Traits>
class SegmentRecover
{
public: /* Traits **********************************************************/
	using Self = DelaunayTet<Traits>;

	using NT         = typename Traits::NT;
	using Vec2       = typename Traits::Vec2;
	using Vec3       = typename Traits::Vec3;
	using EPoint     = typename Traits::EPoint;
	using GPoint     = typename Traits::GPoint;
	using IPoint_LNC = typename Traits::IPoint_LNC;

	using AsGP = typename Traits::AsGP;
	using AsEP = typename Traits::AsEP;
	using ToEP = typename Traits::ToEP;

	using CreateLNC = typename Traits::CreateLNC;

	using InSphere           = typename Traits::InSphere;
	using SquaredDistance3D  = typename Traits::SquaredDistance3D;

	using TetMesh  = TetrahedralMesh<Traits>;
	using TET_MARK = typename TetMesh::TET_MARK;
	using VTX_MARK = typename TetMesh::VTX_MARK;

	using PLC          = PiecewiseLinearComplex<Traits>;
	using PLCEdge      = typename PLC::PLCEdge;
	using PLCFace      = typename PLC::PLCFace;
	using PLCEdgeType  = typename PLC::PLCEdgeType;
	using SubEdgeRange = typename PLC::SubEdgeRange;
	using BoundingEdge = typename PLC::BoundingEdge;

	using DelTet = DelaunayTet<Traits>;

	using SegSphereTree = CDT_SegSphereTree<Traits>;

	using PntArena = CDTPointArena<Traits>;

public: /* Constructor & Destructor ****************************************/
	SegmentRecover() = delete;
	SegmentRecover(std::vector<GPoint *> &_verts, std::vector<PntArena> &_ars,
	                   TetMesh &_tet_mesh, PLC &_plc, ConstrDelTet_Config _config,
										 ConstrDelTet_Stats* _stats = nullptr);

public: /* Algorithms ******************************************************/
	/* Recover constrained segments */

	void segmentRecovery();

	/* sub-algorithms for segment recovery */

	index_t splitMissingSegment(index_t eid);

	void findReferenceEncroachingPoint(index_t eid, index_t &ref_vid,
	                                   index_t &ref_tid) const;

	index_t splitSegment_BothAcuteVertex(index_t eid);

	index_t splitSegment_NoAcuteVertex(index_t eid, index_t ref_vid);

	index_t splitSegment_OneAcuteVertex(index_t eid, index_t ref_vid);

	/* Low level details for edge recovery (predicates, utils, marks...) */

	static bool inSphere(const GPoint &a, const GPoint &b, const GPoint &c);

	static bool largerSphere(const GPoint &a, const GPoint &b, const GPoint &c,
	                         const GPoint &d);

	static bool isLessThanDistance(const GPoint &a, const GPoint &b,
	                               const GPoint &c);

	static bool isLessThanHalfDistance(const GPoint &a, const GPoint &b,
	                                   const GPoint &c);

	std::pair<double, double> getInterpolateT(index_t oep0, index_t oep1,
	                                          index_t ep0, index_t ep1) const;

	IPoint_LNC middlePoint(const PLCEdge &e) const;

	IPoint_LNC lineSphereIntersection_noAc(index_t eid, bool reverse,
	                                       index_t ref_vid) const;

	IPoint_LNC lineSphereIntersection_oneAc(index_t eid, index_t ref_vid) const;

	/* Geometric & Topologic Operations on both TetMesh & PLC */

	GPoint       &gpnt(index_t vid) { return *verts[vid]; }
	const GPoint &gpnt(index_t vid) const { return *verts[vid]; }

	template <typename PointType>
	index_t newVtx(PointType new_pnt);

public: /* Data ************************************************************/
	/// vertices (stored by both `tet_mesh` and `plc`)
	std::vector<GPoint *> &verts;
	/// All generated points in algorithm are stored in pnt_arena
	std::vector<PntArena> &pnt_arenas;
	/// Tetrahedral mesh
	TetMesh               &tet_mesh;
	/// Constrained piecewise linear complex
	PLC                   &plc;

public: /* Flags and configurations ******************************************/
	ConstrDelTet_Config config;

	ConstrDelTet_Stats* stats;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "SegmentRecover.inl"
#endif