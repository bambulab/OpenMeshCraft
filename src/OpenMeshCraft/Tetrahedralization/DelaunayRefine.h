#pragma once

#include "Criteria.h"
#include "DelaunayTet.h"
#include "TetMesh.h"

#include "OpenMeshCraft/Utils/IndexHeap.h"

namespace OMC {

#define OMC_DELAUNAY_REFINE_PROFILE

/**
 * @brief The Delaunay refinement process.
 * It incrementally refines the mesh by refining faces and celss that do not
 * satisfy the criteria, while protecting vertex and edge features.
 *
 * Basic concepts is referred to the paper
 * - "Jonathan R. Shewchuk. 1998. Tetrahedral mesh generation by Delaunay
 *    refinement. In Proc. 14th Annu. ACM Sympos. Comput. Geom., pages 86–95."
 * - "Jean-Daniel Boissonnat, and Steve Oudot. 2005. Provably good sampling and
 *   meshing of surfaces. Graphical Models 67, 5."
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
class DelaunayRefine
{
public: /* Traits **********************************************************/
  using Traits = _Traits;
  using Domain = _Domain;

  using Self = DelaunayRefine<Traits, Domain>;

  using NT   = typename Traits::NT;
  using Vec3 = typename Traits::Vec3;

  using Ray3     = typename Traits::Ray3;
  using Segment3 = typename Traits::Segment3;

  using TetMesh   = TetrahedralMesh<Traits>;
  using VTX_MARK  = typename TetMesh::VTX_MARK;
  using TET_MARK  = typename TetMesh::TET_MARK;
  using FACE_MARK = typename TetMesh::FACE_MARK;

  /* Domain =================================================================
   * TODO documentation
   */

  /* Criteria ===============================================================
   * TODO documentation
   */
  using Criteria = TetMeshCriteria<Traits, Domain>;

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

  /* Cell in TetMesh ========================================================
   *
   * A cell is a tetrahedron in tetrahedral mesh, represented by id or idoff
   * (see details in TetMesh).
   *
   */
  // using... id or idoff is of type index_t

  /* Weighted Delaunay tetrahedralization */
  using DelTet = DelaunayTet<Traits>;

  /* Subdomain in Domain ====================================================
   */
  using SubdomainIndex = index_t;

  /* Surface patch in Domain ================================================
   *
   * A surface patch in the domain is the boundary of two subdomains.
   * It is represented by two indices of the subdomains.
   *
   */
  using SurfacePatchIndex = std::pair<SubdomainIndex, SubdomainIndex>;

  /* Feature =================================================================
   *
   * Feature vertices and edges are preserved during the refinement process.
   * Feature vertices are given as points in the domain, and feature edges must
   * connect two feature vertices.
   *
   * Now we require that feature edges are always straight segments.
   * Otherwise there will be a lot of works to do if feature edges are curves.
   *
   * For efficiency, we require feature indices are densely packed.
   * So, we use std::vector to store feature vertices and edges.
   */
  // index to feature vertex
  using FeatureVertexIndex = index_t;
  // index to feature edge
  using FeatureEdgeIndex   = index_t;
  // feature edge, a pair of indices to feature vertices
  using FeatureEdge        = std::pair<FeatureVertexIndex, FeatureVertexIndex>;

  /* Feature Preservation ====================================================
   *
   * Features are safeguarded using protecting balls. These balls are
   * strategically placed on feature vertices and edges to meet the following
   * requirements:
   *
   * - [Dense Sampling 1] The protecting balls must adequately cover all feature
   *   vertices and edges.
   * - [Dense Sampling 2] Adjacent balls on the same edge must intersect
   * significantly, but without one ball containing the center of the other.
   * - [Disjoint Non-Overlapping 1] No three protecting balls should intersect.
   * - [Disjoint Non-Overlapping 2] Protecting balls on different edges must not
   * intersect.
   *
   * These protecting balls are later transformed into weighted vertices within
   * the tetrahedral mesh.
   */
  // Feature protecting ball (center point + squared radius).
  struct ProtectBall
  {
    Point3  center;            // ball center
    NT      radius_sq;         // squared radius
    index_t feature_index;     // index to feature vertex or edge,
                               // depending on is_feature_vertex
    bool    is_feature_vertex; // true if the ball is a feature vertex

    ProtectBall(const Point3 &_center, NT _radius_sq,
                FeatureVertexIndex _feature_vertex_index,
                std::true_type     is_vertex);
    ProtectBall(const Point3 &_center, NT _radius_sq,
                FeatureEdgeIndex _feature_edge_index,
                std::false_type  is_not_vertex);
  };

  /* Status in inserting a protect ball ========================================
   */
  enum class BallConflictStatus
  {
    OK,
    // the refinement point is coincident with an existing vertex
    COINCIDENT_VERTEX,
    // the refinement point is hidden by an existing weighted vertex
    HIDDEN_POINT,
  };

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
    /* append useful information below */
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
  enum class FaceConflictStatus
  {
    OK,
    // the refinement point is coincident with an existing vertex
    COINCIDENT_VERTEX,
    // the refinement point is hidden by an existing weighted vertex
    HIDDEN_POINT,
    // the refinement point is not conflict with the face to refine
    FACE_NOT_CONFLICT
  };

  /* Cell quality from Criteria =============================================
   *
   * The cell quality is used to determine whether a cell should be refined.
   *
   * It should provide:
   * - operator bool: whether the cell should be refined.
   * - overloaded comprators: compare the priority for refinement.
   *   cell with larger value will be refined first.
   *
   */
  using CellQuality = typename Criteria::CellQuality;

  /* Cell queue =============================================================
   *
   * The cell queue is used to store the cells that need to be refined.
   * The priority is cell quality. Worse cell quality has higher priority.
   */
  struct CellToRefine
  {
    CellQuality quality;
    /* append useful information below */
    // clang-format off
    CellToRefine() = default;
    CellToRefine(const CellQuality& _quality)
      : quality(_quality) {}
    bool operator<(const CellToRefine &other) const { return quality < other.quality; }
    bool operator>(const CellToRefine &other) const { return quality > other.quality; }
    // clang-format on
  };

  using CellQueue = IndexSparseHeap<CellToRefine, std::greater<CellToRefine>>;

  /* Status in refining one cell ============================================
   */
  enum class CellConflictStatus
  {
    OK,
    // the refinement point is coincident with an existing vertex
    COINCIDENT_VERTEX,
    // the refinement point is hidden by an existing weighted vertex
    HIDDEN_POINT,
  };

public: /* Constructor and Destructor **************************************/
  DelaunayRefine(const Domain &_domain, const Criteria &_criteria,
                 Points &_points, Weights &_weights, TetMesh &_tet_mesh);

  ~DelaunayRefine() = default;

public: /* Feature preserving *********************************************/
  void preserveFeatures();

public: /* Helper functions for feature preserving ************************/
  /**
   * @brief construct protecting balls on feature vertices
   */
  void constructBallsOnVertices();

  /**
   * @brief Construct protecting balls on feature edges. It will construct more
   * balls to guarantee [Dense Sampling] on feature edges.
   */
  void constructBallsOnEdges();

  /**
   * @brief Shrink the protecting balls on feature vertices and edges.
   * This is to ensure [Disjoint Non-Overlapping] requirements.
   * @return return true if any ball is shrunk.
   */
  bool shrinkBalls(FeatureEdgeIndex feature_edge_idx);

  /**
   * @brief Check if the feature edge is dense sampled.
   */
  bool edgeDenseSampled(FeatureEdgeIndex feature_edge_idx,
                        index_t          first_ball_local_idx,
                        index_t          last_ball_local_idx) const;

  bool verifyDenseSampled(FeatureEdgeIndex feature_edge_idx) const;

  /**
   * @brief Given the feature edge and the local index of the first and last
   * ball, populate protecting balls between the first and last balls, to
   * satisfy [Dense Sampling] requirements. It also ensures [Disjoint
   * Non-Overlapping 1] requirement on the same edge.
   * @param feature_edge_idx
   * @param first_ball_local_idx range includes first
   * @param last_ball_local_idx range includes last
   */
  void populateEdge(FeatureEdgeIndex feature_edge_idx,
                    index_t first_ball_local_idx, index_t last_ball_local_idx);

  /**
   * @brief After a ball is shrunk, find the range of balls on the same edge
   * that do not satisfy [Dense Sampling] requirements.
   * @param feature_edge_idx
   * @return sparse sampling ranges [first, last] need to be re-populated.
   */
  InlinedVector64<std::pair<index_t, index_t>>
  findSparseSampledRange(FeatureEdgeIndex feature_edge_idx) const;

  /**
   * @brief insert all balls into the tetrahedral mesh as weighted vertices.
   *
   */
  void insertAllBalls();

  /**
   * @brief Try to insert a ball as a weighted vertex into weighted DT.
   *
   * @param ball
   * @param tet tet_idoff to start walking from.
   * @return BallConflictStatus
   */
  BallConflictStatus insertBall(const ProtectBall &ball, index_t &tet);

public: /* Restricted Face Refinement *************************************/
  /**
   * @brief [Initialization] Scan the tetrahedral mesh and add faces to the
   * refinement queue.
   * @pre The tetrahedral mesh is already built.
   * @post The refinement queue is filled with faces that need to be refined.
   */
  void scanFaces();

  /**
   * @brief [Stop condition] Check if the face refinement process is done.
   * @return true if the face refinement process is done, false otherwise.
   */
  bool isFaceRefineDone();

  /**
   * @brief [Step in loop] Process one face in the refinement queue.
   * @pre The algorithm is not done.
   * @post The element is processed and removed from the queue. Newly created
   * elements are checked and may be added to the queue.
   */
  FaceConflictStatus processOneFace();

  /**
   * @brief [The whole process] Refine the tetrahedral mesh.
   */
  void refineFaces();

public: /* Helper functions for Restricted Face Refinement ********************/
  void checkNewFace(index_t face_idoff);

  bool isFaceRestricted(index_t face_idoff, SurfacePatchIndex &surface_patch,
                        Point3 &intersection) const;

public: /* Tetrahedra Refinement **********************************************/
  /**
   * @brief [Initialization] Scan the tetrahedral mesh and add cells to the
   * refinement queue.
   * @pre The tetrahedral mesh is already built.
   * @post The refinement queue is filled with cells that need to be refined.
   */
  void scanCells();

  /**
   * @brief [Stop condition] Check if the tet refinement process is done.
   * @return true if the cell refinement process is done, false otherwise.
   */
  bool isCellRefineDone();

  /**
   * @brief [Step in loop] Process one tetrahedron in the refinement queue.
   * @pre The algorithm is not done.
   * @post The element is processed and removed from the queue. Newly created
   * elements are checked and may be added to the queue.
   */
  CellConflictStatus processOneCell();

  /**
   * @brief [The whole process] Refine the tetrahedral mesh.
   */
  void refineCells();

public: /* Helper functions for Tetrahedra Refinement *************************/
  void checkNewCell(index_t tet_idoff);

public: /* Common functions ***************************************************/
  index_t newVertex(const Point3 &point, NT weight);

public: /* Data ***************************************************************/
  /* Input domain and criteria */
  const Domain   &domain;
  const Criteria &criteria;

  /* Tetrahedral mesh */
  Points  &points;
  Weights &weights;
  TetMesh &tet_mesh;

  /* Feature protecting balls */

  // All balls
  std::vector<ProtectBall> protect_balls;

  // balls on feature vertices (Vertex index -> ball index)
  std::vector<index_t>              feature_vertex_balls;
  // balls on feature edges (Edge index -> set of ball indices)
  std::vector<std::vector<index_t>> feature_edge_balls;

  // Deleted balls, waiting to be reused.
  std::vector<index_t> balls_deleted;

  /* Refinement queue */
  FaceQueue face_queue;
  CellQueue cell_queue;

private:
  static Sign canonicalCompare(const Point3 &p1, const Point3 &p2);

  static constexpr NT     dense_sampled_factor  = 0.4;
  static constexpr size_t shrink_max_iterations = 10;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "DelaunayRefine.inl"
#endif