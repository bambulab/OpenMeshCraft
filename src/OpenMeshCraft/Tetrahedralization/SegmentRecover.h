#pragma once

#include "DelaunayTet.h"
#include "PLC.h"
#include "TetMesh.h"
#include "Tree.h"
#include "Utils.h"

namespace OMC {

/**
 * @brief Recover the segment constraints in CDT algorithm.
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - [Si and Gärtner 2005] Hang Si and Klaus Gärtner. 2005. Meshing Piecewise
 *   Linear Complexes by Constrained Delaunay Tetrahedralizations. Proceedings
 *   of the 14th International Meshing Roundtable, 147–163.
 */
template <typename Traits>
class SegmentRecover
{
public: /* Traits **********************************************************/
  using Self = SegmentRecover<Traits>;

  using NT           = typename Traits::NT;
  using Vec2         = typename Traits::Vec2;
  using Vec3         = typename Traits::Vec3;
  using EPoint3      = typename Traits::EPoint3;
  using GPoint3      = typename Traits::GPoint3;
  using IPoint3T_LNC = typename Traits::IPoint3T_LNC;

  using AsGP = typename Traits::AsGP;
  using AsEP = typename Traits::AsEP;
  using ToEP = typename Traits::ToEP;

  using CreateLNC = typename Traits::CreateLNC;

  using Sphere3  = typename Traits::Sphere3;
  using Segment3 = typename Traits::Segment3;

  // predicates
  using InSphere          = typename Traits::InSphere;
  using SquaredDistance3D = typename Traits::SquaredDistance3D;
  using DoIntersect       = typename Traits::DoIntersect;
  // constructions
  using CalcBoundingBox3  = typename Traits::CalcBoundingBox3;
  using ProjectPoint3     = typename Traits::ProjectPoint3;

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

  using IndexedSegment = PrimitiveWithAttribute<Segment3, index_t>;
  using SegmentTree    = CDT_SegmentTree<Traits>;

  using PntArena = CDTPointArena<Traits>;

public: /* Constructor & Destructor ******************************************/
  SegmentRecover() = delete;
  SegmentRecover(std::vector<GPoint3 *> &_verts, std::vector<PntArena> &_ars,
                 TetMesh &_tet_mesh, PLC &_plc, ConstrDelTet_Config _config,
                 ConstrDelTet_Stats *_stats = nullptr);

public: /* Interface *********************************************************/
  /* Recover constrained segments */

  void segmentRecovery();

public: /* Common operations used by recovery algorithms *********************/
  /* Geometric & Topologic Operations on both TetMesh & PLC */

  GPoint3       &gpnt(index_t vid) { return *verts[vid]; }
  const GPoint3 &gpnt(index_t vid) const { return *verts[vid]; }

  template <typename PointType>
  index_t newVtx(PointType new_pnt);

public: /* SiHang's Recovery Algorithm ***************************************/
  void segmentRecovery_SiHang(size_t num_loop = 0);

  /* sub-algorithms for segment recovery */

  index_t splitMissingSegment(index_t eid);

  template <typename Container = InlinedVector64<index_t>>
  void findReferenceEncroachingPoint(index_t eid, index_t &ref_vid,
                                     index_t   &ref_tid,
                                     Container *enc_verts = nullptr);

  IPoint3T_LNC splitSegment_NoAcuteVertex(index_t eid, index_t ref_vid) const;

  IPoint3T_LNC splitSegment_OneAcuteVertex(index_t eid, index_t ref_vid) const;

  /* Low level details for edge recovery (predicates, utils, marks...) */

  static bool inSphere(const GPoint3 &a, const GPoint3 &b, const GPoint3 &c);

  static bool largerSphere(const GPoint3 &a, const GPoint3 &b, const GPoint3 &c,
                           const GPoint3 &d);

  static bool isLessThanDistance(const GPoint3 &a, const GPoint3 &b,
                                 const GPoint3 &c);

  static bool isLessThanHalfDistance(const GPoint3 &a, const GPoint3 &b,
                                     const GPoint3 &c);

  std::pair<double, double> getInterpolateT(index_t oep0, index_t oep1,
                                            index_t ep0, index_t ep1) const;

  IPoint3T_LNC middlePoint(const PLCEdge &e) const;

  IPoint3T_LNC lineSphereIntersection_noAc(index_t eid, bool reverse,
                                           index_t ref_vid) const;

  IPoint3T_LNC lineSphereIntersection_oneAc(index_t eid, index_t acute_vid,
                                            index_t ref_vid) const;

public: /* Protecting sphere *************************************************/
  void buildProtectingSphere();

  void protectVertex(index_t eid, IPoint3T_LNC &steiner_point) const;

  IPoint3T_LNC splitSegment_ProtectingSphere(index_t eid,
                                             index_t center_vid) const;

public: /* Data **************************************************************/
  /// vertices (stored by both `tet_mesh` and `plc`)
  std::vector<GPoint3 *> &verts;
  /// All generated points in algorithm are stored in pnt_arena
  std::vector<PntArena>  &pnt_arenas;
  /// Tetrahedral mesh
  TetMesh                &tet_mesh;
  /// Constrained piecewise linear complex
  PLC                    &plc;

  /* Data used by explicit protecting sphere */

  bool protecting_sphere_initialized;

  /// The segment tree
  /// - The tree is build on the initial (input) constrained segments.
  /// - The segments in tree have the same indices as the PLC edges.
  /// - The tree is used to quickly find intersecting segments with a
  ///   (protecting) sphere.
  /// - The tree is static and does not change during the recovery process.
  SegmentTree seg_tree;

  /// The protecting sphere
  /// - The protecting sphere is built on original input vertices whose incident
  /// edges form acute angles.
  /// - We save the squared radius of the protecting sphere for these vertex.
  /// - The squared radius is set to negative value if the vertex need not
  /// protection.
  std::vector<double> protecting_sphere_squared_radius;

public: /* Flags and configurations ******************************************/
  ConstrDelTet_Config config;

  ConstrDelTet_Stats *stats;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "SegmentRecover.inl"
#endif