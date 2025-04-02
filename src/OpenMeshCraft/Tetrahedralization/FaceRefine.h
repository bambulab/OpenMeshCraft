#pragma once

#include "Criteria.h"
#include "DelaunayTet.h"
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
 */
template <typename _Traits, typename _Domain>
class FaceRefine
{
public: /* Traits **********************************************************/
  using Traits = _Traits;
  using Domain = _Domain;

  using Self = FaceRefine<Traits, Domain>;

  using NT   = typename Traits::NT;
  using Vec3 = typename Traits::Vec3;

  using Ray3     = typename Traits::Ray3;
  using Segment3 = typename Traits::Segment3;

  using TetMesh   = TetrahedralMesh<Traits>;
  using VTX_MARK  = typename TetMesh::VTX_MARK;
  using TET_MARK  = typename TetMesh::TET_MARK;
  using FACE_MARK = typename TetMesh::FACE_MARK;

  using Criteria = TetMeshCriteria<Traits>;

  /* Points and weights in TetMesh ==========================================
   */
  using Point3  = typename TetMesh::Point3;
  using Weight  = typename TetMesh::Weight;
  using Points  = typename TetMesh::Points;
  using Weights = typename TetMesh::Weights;

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
  // using... face_idoff is of type index_t

  /* Weighted Delaunay tetrahedralization */
  using DelTet = DelaunayTet<Traits>;

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
    Point3      intersection; // intersection between dual and surface patch
    // clang-format off
    FaceToRefine() = default;
    FaceToRefine(const FaceQuality& _quality, const Point3& _intersection)
      : quality(_quality), intersection(_intersection) {}
    bool operator<(const FaceToRefine &other) const { return quality < other.quality; }
    bool operator>(const FaceToRefine &other) const { return quality > other.quality; }
    // clang-format on
  };

  using FaceQueue = IndexSparseHeap<FaceToRefine, std::greater<FaceToRefine>>;

  /* Status in refining one face ============================================
   */
  enum class ConflictStatus
  {
    OK,
    // the refinement point is coincident with an existing vertex
    COINCIDENT_VERTEX,
    // the refinement point is hidden by an existing weighted vertex
    HIDDEN_POINT,
    // the refinement point is not conflict with the face to refine
    FACE_NOT_CONFLICT
  };

public: /* Constructor and Destructor **************************************/
  FaceRefine(const Domain &_domain, const Criteria &_criteria, Points &_points,
             Weights &_weights, TetMesh &_tet_mesh);

  ~FaceRefine() = default;

public: /* Interfaces ******************************************************/
  /**
   * @brief [Initialization] Scan the tetrahedral mesh and add faces to the
   * refinement queue.
   * @pre The tetrahedral mesh is already built.
   * @post The refinement queue is filled with faces that need to be refined.
   */
  void scanElements();

  /**
   * @brief [Stop condition] Check if the refinement process is done.
   * @return true if the refinement process is done, false otherwise.
   */
  bool isDone();

  /**
   * @brief [Step in loop] Process one element in the refinement queue.
   * @pre The algorithm is not done.
   * @post The element is processed and removed from the queue. Newly created
   * elements are checked and may be added to the queue.
   */
  ConflictStatus processOneElement();

  /**
   * @brief [The whole process] Refine the tetrahedral mesh.
   */
  void refine();

public: /* Helper functions ************************************************/
  void checkNewFace(index_t face_idoff);

  bool isFaceRestricted(index_t face_idoff, SurfacePatchIndex &surface_patch,
                        Point3 &intersection) const;

  index_t newVertex(const Point3 &point, NT weight);

public: /* Data ************************************************************/
  const Domain   &domain;
  const Criteria &criteria;

  Points  &points;
  Weights &weights;
  TetMesh &tet_mesh;

  FaceQueue face_queue;

private:
  static Sign canonicalCompare(const Point3 &p1, const Point3 &p2);
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "FaceRefine.inl"
#endif