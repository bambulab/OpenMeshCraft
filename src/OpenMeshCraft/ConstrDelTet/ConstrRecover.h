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

	using Orient3D           = typename Traits::Orient3D;
	using OrientOn2D         = typename Traits::OrientOn2D;
	using CollinearPoints3D  = typename Traits::CollinearPoints3D;
	using InSphere           = typename Traits::InSphere;
	using MaxCompInTriNormal = typename Traits::MaxCompInTriNormal;

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
	                                   index_t &ref_tid) const;

	GPoint *splitAtMiddle(index_t eid) const;

	GPoint *splitSegment_NoAcuteVertex(index_t eid, index_t ref_vid) const;

	GPoint *splitSegment_OneAcuteVertex(index_t eid, index_t ref_vid) const;

	/* Recover constrained faces */

	void faceRecovery();

	/* sub-algorithms for face recovery */

	bool tetIntersectsFace(index_t                      tet_idoff,
	                       const typename PLC::PLCFace &face) const;

	void getTetsIntersectingFace(index_t fid, std::vector<index_t> &tets);

	/* Geometric & Topologic Operations on both TetMesh & PLC */

	GPoint       &gpnt(index_t vid) { return *verts[vid]; }
	const GPoint &gpnt(index_t vid) const { return *verts[vid]; }

	index_t newVtx(GPoint *new_pnt);

	Sign orient3dCached(index_t v0, index_t v1, index_t v2, index_t v3);
	void clearCachedOrient3d();

	bool segCrossesFace(index_t s0, index_t s1,
	                    const typename PLC::PLCFace &face) const;

public: /* Data ************************************************************/
	/// vertices (stored by both `tet_mesh` and `plc`)
	std::vector<GPoint *> &verts;
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
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ConstrRecover.inl"
#endif