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

	using NT         = typename Traits::NT;
	using Vec2       = typename Traits::Vec2;
	using Vec3       = typename Traits::Vec3;
	using EPoint     = typename Traits::EPoint;
	using GPoint     = typename Traits::GPoint;
	using IPoint_SSI = typename Traits::IPoint_SSI;
	using IPoint_LNC = typename Traits::IPoint_LNC;
	using IPoint_LPI = typename Traits::IPoint_LPI;
	using IPoint_TPI = typename Traits::IPoint_TPI;

	using AsGP = typename Traits::AsGP;
	using AsEP = typename Traits::AsEP;
	using ToEP = typename Traits::ToEP;

	using CreateSSI = typename Traits::CreateSSI;
	using CreateLNC = typename Traits::CreateLNC;
	using CreateLPI = typename Traits::CreateLPI;
	using CreateTPI = typename Traits::CreateTPI;

	using Orient3D           = typename Traits::Orient3D;
	using OrientOn2D         = typename Traits::OrientOn2D;
	using LessThan3D         = typename Traits::LessThan3D;
	using InSphere           = typename Traits::InSphere;
	using MaxCompInTriNormal = typename Traits::MaxCompInTriNormal;
	using SquaredDistance3D  = typename Traits::SquaredDistance3D;
	using CollinearPoints3   = typename Traits::CollinearPoints3;

	// clang-format off
	using Segment3_Point3_DoIntersect        = typename Traits::Segment3_Point3_DoIntersect;
	using Segment3_Segment3_DoIntersect      = typename Traits::Segment3_Segment3_DoIntersect;
	using Triangle3_Point3_DoIntersect       = typename Traits::Triangle3_Point3_DoIntersect;
	using Triangle3_Segment3_DoIntersect     = typename Traits::Triangle3_Segment3_DoIntersect;
	using Triangle3_Triangle3_DoIntersect    = typename Traits::Triangle3_Triangle3_DoIntersect;
	using Tetrahedron3_Point3_DoIntersect    = typename Traits::Tetrahedron3_Point3_DoIntersect;
	using Tetrahedron3_Segment3_DoIntersect  = typename Traits::Tetrahedron3_Segment3_DoIntersect;
	using Tetrahedron3_Triangle3_DoIntersect = typename Traits::Tetrahedron3_Triangle3_DoIntersect;
	// clang-format on

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

	using PntArena = CDTPointArena<Traits>;

public: /* Constructor & Destructor ****************************************/
	ConstraintsRecover() = delete;
	ConstraintsRecover(std::vector<GPoint *> &_verts, std::vector<PntArena> &_ars,
	                   TetMesh &_tet_mesh, PLC &_plc, ConstrDelTet_Config _config);

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

	IPoint_LNC middlePoint_bothAc(const PLCEdge &e) const;

	IPoint_LNC lineSphereIntersection_noAc(index_t eid, bool reverse,
	                                       index_t ref_vid) const;

	IPoint_LNC lineSphereIntersection_oneAc(index_t eid, index_t ref_vid) const;

	/* Recover constrained faces */

	void faceRecovery();

	/* sub-algorithms for face recovery */

	void getTetsIntersectingFace(index_t fid, std::vector<index_t> &tets);

	void recoverFace_cavityExpanding(index_t                     fid,
	                                 const std::vector<index_t> &tets,
	                                 bool &succeed, bool &expanded);

	bool cavityHasMissingFace(const TetMesh              &local_mesh,
	                          const AuxVector64<index_t> &vertices,
	                          const AuxVector64<index_t> &faces,
	                          index_t                    &missing_face);

	void expandCavity(AuxVector64<index_t> &vertices, AuxVector64<index_t> &faces,
	                  index_t missing_face, index_t &new_tet,
	                  index_t &new_vertex);

	void embedMeshedCavity(TetMesh                    &local_mesh,
	                       const AuxVector64<index_t> &vertices,
	                       const AuxVector64<index_t> &faces,
	                       AuxVector64<index_t>       &base);

	/* Low level details for face recovery (predicates, utils, marks...) */

	bool tetIntersectsFace(index_t tet_idoff, const PLCFace &face);

	Sign orient3dCached(index_t v0, index_t v1, index_t v2, index_t v3);

	bool segCrossesFace(index_t s0, index_t s1, const PLCFace &face) const;

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

	/* Auxiliary data defined between tetrahedral mesh and PLC */

	/// Vertex orientation with respect to one PLC face.
	std::vector<Sign>    v_orient;
	/// Vertex indices of the cached orientation.
	/// Record them to clear the cache after the recovery of a PLC face.
	std::vector<index_t> v_cached_orient;

	/// Vertex count.
	/// During the recovery of a PLC face, the count of each vertex is incremented
	/// by one each time it appears on the boundary.
	/// - A flat vertex's count is zero.
	/// - A bounding vertex's count is at least one.
	/// - A singular bounding vertex's count is more than one.
	std::vector<uint32_t> v_count;

	/// Vertex re-index, mapping global index to local index.
	/// During the recovery of a PLC face, local cavity is tetrahedralized.
	/// We need to build a mapping from global vertex index to local vertex index,
	/// to check if a cavity face is missing.
	std::vector<index_t> v_reindex;

public: /* Flags and configurations ******************************************/
	ConstrDelTet_Config config;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ConstrRecover.inl"
#endif