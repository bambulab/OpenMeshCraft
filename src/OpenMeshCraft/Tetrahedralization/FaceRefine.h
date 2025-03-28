#pragma once

#include "TetMesh.h"

#include "OpenMeshCraft/Utils/IndexHeap.h"

namespace OMC {

/**
 * @brief Handles face refinement in the Delaunay refinement process.
 * It incrementally refines the mesh by refining faces that do not satisfy the
 * criteria.
 *
 * Basic concepts is referred to the paper "Jean-Daniel Boissonnat, and Steve
 * Oudot. 2005. Provably good sampling and meshing of surfaces. Graphical Models
 * 67, 5."
 *
 * The implementation is referred to CGAL's Mesh_3 package.
 *
 * @tparam Traits Defines the geometric traits.
 * @tparam Domain Specifies the subdomain for each point in space. It handles
 * queries such as: (1) whether a point is within the domain, (2) the subdomain
 * of a point, (3) the intersection between subdomain boundaries and a segment,
 * etc.
 * @tparam Criteria Specifies the criteria for refinement, determining whether a
 * face should be refined.
 */
template <typename _Traits, typename _Domain, typename _Criteria>
class FaceRefine
{
public: /* Traits **********************************************************/
  using Traits   = _Traits;
  using Domain   = _Domain;
  using Criteria = _Criteria;

  using Self = FaceRefine<Traits, Domain, Criteria>;

  using NT      = typename Traits::NT;
  using Vec3    = typename Traits::Vec3;
  using EPoint3 = typename Traits::EPoint3;

  using Ray3     = typename Traits::Ray3;
  using Segment3 = typename Traits::Segment3;

  using TetMesh   = TetrahedralMesh<Traits>;
  using VTX_MARK  = typename TetMesh::VTX_MARK;
  using TET_MARK  = typename TetMesh::TET_MARK;
  using FACE_MARK = typename TetMesh::FACE_MARK;

  /* Face in TetMesh ========================================================
   *
   * A face of a tetrahedron in tetrahedral mesh is represented by idoff (see
   * details in TetMesh).
   * Briefly speaking, it is composed by two parts. The first part is the id
   * of the tetrahedron `tet_id`, and the second part is the `offset` of the
   * opposite vertex of the face in the tetrahedron.
   * So, idoff = tet_id * 4 + offset.
   *
   */

  /* Surface patch in Domain ================================================
   *
   * A surface patch in the domain is the boundary of two subdomains.
   * It is represented by two indices of the subdomains.
   *
   */
  using SurfacePatchIndex = typename Domain::SurfacePatchIndex;

  /* Face quality from Criteria ==============================================
   *
   * The face quality is used to determine whether a face should be refined.
   *
   * It should provide:
   * - operator bool: whether the face should be refined.
   * - overloaded comprators: compare the priority for refinement.
   *   face with larger value will be refined first.
   *
   */
  using FaceQuality = typename Criteria::FaceQuality;

  /* Face queue =============================================================
   *
   * The face queue is used to store the faces that need to be refined.
   * The priority is face quality. Worse face quality has higher priority.
   */
  struct FaceToRefine
  {
    FaceQuality quality;
    // clang-format off
    FaceToRefine(FaceQuality _quality)
      : quality(_quality) {}
    bool operator<(const FaceToRefine &other) const { return quality < other.quality; }
    bool operator>(const FaceToRefine &other) const { return quality > other.quality; }
    // clang-format on
  };

  using FaceQueue = IndexSparseHeap<FaceToRefine, std::greater<FaceToRefine>>;

public: /* Constructor and Destructor **************************************/
  FaceRefine(const Domain &_domain, const Criteria &_criteria,
             TetMesh &_tet_mesh);

  ~FaceRefine() = default;

public: /* Interfaces ******************************************************/
  bool processOneElement();

  void scanElements();

  void getNextElement();

  void tryToRefineElement();

public: /* Helper functions ************************************************/
  void checkNewFace(index_t face_idoff);

  bool isFaceRestricted(index_t face_idoff, SurfacePatchIndex &surface_patch,
                        EPoint3 &intersection) const;

public: /* Data ************************************************************/
  const Domain   &domain;
  const Criteria &criteria;

  TetMesh &tet_mesh;

  FaceQueue face_queue;

private:
  static Sign canonicalCompare(const EPoint3 &p1, const EPoint3 &p2);
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "FaceRefine.inl"
#endif