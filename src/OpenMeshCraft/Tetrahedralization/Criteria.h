#pragma once

#include "TetMesh.h"

namespace OMC {

template <typename _Traits>
class TetMeshCriteria
{
public: /* Traits **********************************************************/
  using Traits = _Traits;

  using Self = TetMeshCriteria<Traits>;

  using NT           = typename Traits::NT;
  using Vec3         = typename Traits::Vec3;
  using BoundingBox3 = typename Traits::BoundingBox3;

  using ConstructCircumcenter3 =
    typename Traits::template ConstructCircumcenter3</*Filtered*/ true,
                                                     /*ForceExact*/ false>;

  using TetMesh = TetrahedralMesh<Traits>;
  using Point3  = typename TetMesh::Point3;
  using Weight  = typename TetMesh::Weight;

public: /* Quality definitions *********************************************/
  /* Face quality ===========================================================
   *
   * - quality: higher value means worse quality, 0 is the best (satisfy all
   * criterias).
   * - operator bool: whether the face violates any quality criteria.
   * - overloaded comprators: compare the quality.
   *
   */
  struct FaceQuality
  {
    NT quality;

    // clang-format off
    FaceQuality() : quality(0) {}
    FaceQuality(NT _quality) : quality(_quality) {}

    explicit operator bool() const { return quality > 0; }

    bool operator<(const FaceQuality &rhs) const { return quality < rhs.quality; }
    bool operator==(const FaceQuality &rhs) const { return quality == rhs.quality; }
    bool operator>(const FaceQuality &rhs) const { return quality > rhs.quality; }
    // clang-format on
  };

  /* Cell quality ===========================================================
   *
   * - quality: higher value means worse quality, 0 is the best (satisfy all
   * criterias).
   * - operator bool: whether the face violates any quality criteria.
   * - overloaded comprators: compare the quality.
   *
   */
  struct CellQuality
  {
    NT quality;

    // clang-format off
    CellQuality() : quality(0) {}
    CellQuality(NT _quality) : quality(_quality) {}

    explicit operator bool() const { return quality > 0; }

    bool operator<(const CellQuality &rhs) const { return quality < rhs.quality; }
    bool operator==(const CellQuality &rhs) const { return quality == rhs.quality; }
    bool operator>(const CellQuality &rhs) const { return quality > rhs.quality; }
    // clang-format on
  };

public: /* Quality settings ************************************************/
  // The domain bounding box.
  BoundingBox3 domain_bbox;
  // The diagonal length of the domain bounding box.
  NT           domain_diag_length;

  /**
   * @brief Set the domain bounding box and initialize related data.
   * @param bbox Bounding box of the domain.
   */
  Self &setDomain(const BoundingBox3 &bbox);

  // A restricted face has a corresponding intersection point between its
  // Voronoi dual (a segment or a ray) and input surface patch.
  // The distance between the face's circumcenter and the intersection point
  // should be less than this threshold.
  NT restricted_face_distance_threshold = 0;

  /**
   * @brief Set the restricted face distance threshold.
   * @param threshold The threshold should be given in the percentage of the
   * domain diagonal length. For example, `threshold = 1.0` means the 1% of the
   * domain diagonal length.
   */
  Self &setRestrictedFaceDistanceThreshold(NT threshold);

  // The minimal/maximal uniform size thresholds for cells.
  // All cells' circumradius should be greater/less than the thresholds.
  NT cell_min_uniform_size_threshold = 0;
  NT cell_max_uniform_size_threshold = 0;

  /**
   * @brief Set the min/max uniform size thresholds.
   * @param threshold The threshold should be given in the percentage of the
   * domain diagonal length. For example, `threshold = 1.0` means the 1% of the
   * domain diagonal length.
   */
  Self &setMinUniformSizeThreshold (NT threshold);
  Self &setMaxUniformSizeThreshold (NT threshold);

  // The ratio between the circumradius and the edge length of a tetrahedron.
  // Range [0, 1], optimal 1, recommanded target range [0.6, 1].
  NT cell_radius_edge_ratio_threshold = 0;

  /**
   * @brief Set the cell radius edge ratio threshold
   * @param threshold See `cell_radius_edge_ratio_threshold`.
   */
  Self &setCellRadiusEdgeRatioThreshold(NT threshold);

public: /* Quality queries *************************************************/
  /**
   * @brief Evaluate the quality of a face.
   *
   * @param tet_mesh The tetrahedral mesh.
   * @param face_idoff The idoff of the face in the tetrahedral mesh.
   * @param intersection The intersection point of the face with the surface
   * patch.
   *
   * @return The quality of the face.
   */
  FaceQuality faceQuality(const TetMesh &tet_mesh, index_t face_idoff,
                          const Point3 &intersection) const;

  /**
   * @brief Evaluate the quality of a tetrahedron.
   *
   * @param tet_mesh The tetrahedral mesh.
   * @param tet_idoff The idoff of the tetrahedron in the tetrahedral mesh.
   *
   * @return The quality of the tetrahedron.
   */
  CellQuality cellQuality(const TetMesh &tet_mesh, index_t tet_idoff) const;

public:
  static NT length(const Point3 &p, const Point3 &q);

  static NT sq_length(const Point3 &p, const Point3 &q);

  static NT area(const Point3 &p, const Point3 &q, const Point3 &r);

  static NT volume(const Point3 &p, const Point3 &q, const Point3 &r,
                   const Point3 &s);

  static NT minDiahedralAngle(const Point3 &p, const Point3 &q, const Point3 &r,
                              const Point3 &s);
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Criteria.inl"
#endif