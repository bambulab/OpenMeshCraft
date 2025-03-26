#pragma once

#include "DelaunayTet.h"
#include "PLC.h"
#include "TetMesh.h"
#include "Utils.h"

namespace OMC {

/**
 * @brief Recover the face constraints in CDT algorithm.
 * @see
 * - [Robust CDT] Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M.
 *   Constrained Delaunay Tetrahedrization: A Robust and Practical Approach.
 *   ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 * - [Si and Gärtner 2005] Hang Si and Klaus Gärtner. 2005. Meshing Piecewise
 *   Linear Complexes by Constrained Delaunay Tetrahedralizations. Proceedings
 *   of the 14th International Meshing Roundtable, 147–163.
 */
template <typename Traits>
class FaceRecover
{
public: /* Traits **********************************************************/
  using Self = FaceRecover<Traits>;

  using NT      = typename Traits::NT;
  using Vec2    = typename Traits::Vec2;
  using Vec3    = typename Traits::Vec3;
  using EPoint3 = typename Traits::EPoint3;
  using GPoint3 = typename Traits::GPoint3;

  using AsGP = typename Traits::AsGP;
  using AsEP = typename Traits::AsEP;
  using ToEP = typename Traits::ToEP;

  using Orient3D           = typename Traits::Orient3D;
  using OrientOn2D         = typename Traits::OrientOn2D;
  using MaxCompInTriNormal = typename Traits::MaxCompInTriNormal;

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

public: /* Constructor & Destructor ****************************************/
  FaceRecover() = delete;
  FaceRecover(std::vector<GPoint3 *> &_verts, TetMesh &_tet_mesh, PLC &_plc,
              ConstrDelTet_Config _config,
              ConstrDelTet_Stats *_stats = nullptr);

public: /* Algorithms ******************************************************/
  /* Recover constrained faces */

  void faceRecovery();

  /* sub-algorithms for face recovery */

  void getTetsIntersectingFace(index_t fid, std::vector<index_t> &tets);

  void recoverFace_cavityExpanding(index_t                     fid,
                                   const std::vector<index_t> &tets,
                                   bool &succeed, bool &expanded);

  bool cavityHasMissingFace(const TetMesh                  &local_mesh,
                            const InlinedVector64<index_t> &vertices,
                            const InlinedVector64<index_t> &faces,
                            index_t                        &missing_face);

  void expandCavity(InlinedVector64<index_t> &vertices,
                    InlinedVector64<index_t> &faces, index_t missing_face,
                    index_t &new_tet, index_t &new_vertex);

  void embedMeshedCavity(TetMesh                        &local_mesh,
                         const InlinedVector64<index_t> &vertices,
                         const InlinedVector64<index_t> &faces,
                         InlinedVector64<index_t>       &base);

  /* Low level details for face recovery (predicates, utils, marks...) */

  bool tetIntersectsFace(index_t tet_idoff, const PLCFace &face);

  Sign orient3dCached(index_t v0, index_t v1, index_t v2, index_t v3);

  bool segCrossesFace(index_t s0, index_t s1, const PLCFace &face) const;

  /* Geometric & Topologic Operations on both TetMesh & PLC */

  GPoint3       &gpnt(index_t vid) { return *verts[vid]; }
  const GPoint3 &gpnt(index_t vid) const { return *verts[vid]; }

public: /* Data ************************************************************/
  /// vertices (stored by both `tet_mesh` and `plc`)
  const std::vector<GPoint3 *> &verts;

  /// Tetrahedral mesh
  TetMesh &tet_mesh;
  /// Constrained piecewise linear complex
  PLC     &plc;

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

  ConstrDelTet_Stats *stats;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "FaceRecover.inl"
#endif