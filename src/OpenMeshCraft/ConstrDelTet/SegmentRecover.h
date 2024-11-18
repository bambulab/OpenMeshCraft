#pragma once

#include "DelaunayTet.h"
#include "PLC.h"
#include "TetMesh.h"
#include "Tree.h"

#include "OpenMeshCraft/Utils/IndexHeap.h"

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

	using InSphere          = typename Traits::InSphere;
	using SquaredDistance3D = typename Traits::SquaredDistance3D;

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

	using GenericSegment = GenericSegment3T<Traits>;
	using SegSphereTree  = CDT_SegSphereTree<Traits>;

	using PntArena = CDTPointArena<Traits>;

public: /* Constructor & Destructor ******************************************/
	SegmentRecover() = delete;
	SegmentRecover(std::vector<GPoint *> &_verts, std::vector<PntArena> &_ars,
	               TetMesh &_tet_mesh, PLC &_plc, ConstrDelTet_Config _config,
	               ConstrDelTet_Stats *_stats = nullptr);

public: /* Interface *********************************************************/
	/* Recover constrained segments */

	void segmentRecovery();

public: /* Common operations used by recovery algorithms *********************/
	/* Geometric & Topologic Operations on both TetMesh & PLC */

	GPoint       &gpnt(index_t vid) { return *verts[vid]; }
	const GPoint &gpnt(index_t vid) const { return *verts[vid]; }

	template <typename PointType>
	index_t newVtx(PointType new_pnt);

public: /* SiHang's Recovery Algorithm ***************************************/
	void segmentRecovery_SiHang();

	/* sub-algorithms for segment recovery */

	index_t splitMissingSegment(index_t eid);

	void findReferenceEncroachingPoint(
	  index_t eid, index_t &ref_vid, index_t &ref_tid,
	  AuxVector64<index_t> *enc_verts = nullptr) const;

	IPoint_LNC splitSegment_NoAcuteVertex(index_t eid, index_t ref_vid);

	IPoint_LNC splitSegment_OneAcuteVertex(index_t eid, index_t ref_vid);

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

public: /* Greedy Recovery Algorithm *****************************************/
	void segmentRecovery_Greedy();

	/* Data structures used for greedy strategy */

	/// @brief The priority queue of segments
	using SegPriorityQueue = IndexDenseHeap<double, std::greater<double>>;
	using SegSteinerPoint  = std::vector<IPoint_LNC>;

	template <bool AllowUpdate = true>
	void pushSegmentToQueue(index_t eid);

	IPoint_LNC getSteinerPoint(index_t eid, AuxVector64<index_t> &enc_verts);

	double getSegPriority(index_t eid, const IPoint_LNC &steiner_pnt,
	                      const AuxVector64<index_t> &enc_verts) const;

	/* Help functions used for greedy strategy */

	void missingSegmentsInCavity(const AuxVector64<index_t> &cavity_tets,
	                             const AuxVector64<index_t> &cavity_corners,
	                             AuxVector64<index_t>       &missing_segs);

	IPoint_LNC
	reduceMostEncroachingPoints(index_t                     eid,
	                            const AuxVector64<index_t> &enc_verts) const;

	static double linePlaneIntersection(const Vec3 &e0, const Vec3 &e1,
	                                    const Vec3 &p, const Vec3 &n);

public: /* Data **************************************************************/
	/// vertices (stored by both `tet_mesh` and `plc`)
	std::vector<GPoint *> &verts;
	/// All generated points in algorithm are stored in pnt_arena
	std::vector<PntArena> &pnt_arenas;
	/// Tetrahedral mesh
	TetMesh               &tet_mesh;
	/// Constrained piecewise linear complex
	PLC                   &plc;

	/* Data used by greedy recovery algorithm */

	/// The segments' diametral sphere tree
	/// - The tree is built on the segments' diametral spheres.
	/// - The segments in tree have the same indices as the PLC edges.
	/// - The tree is used to quickly find encroached segments by a Steiner point.
	/// - The tree is updated when a segment is split.
	SegSphereTree tree;

	/// The priority queue of segments to be split.
	SegPriorityQueue seg_queue;
	/// The Steiner point of segments to be split.
	SegSteinerPoint  seg_steiner_point;

public: /* Flags and configurations ******************************************/
	ConstrDelTet_Config config;

	ConstrDelTet_Stats *stats;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "SegmentRecover.inl"
#endif