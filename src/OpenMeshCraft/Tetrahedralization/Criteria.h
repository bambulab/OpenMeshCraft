#pragma once

#include "TetMesh.h"

namespace OMC {

template <typename _Traits>
class TetMeshCriteria
{
public: /* Traits **********************************************************/
  using Traits = _Traits;

  using Self = TetMeshCriteria<Traits>;

  using NT      = typename Traits::NT;
  using Vec3    = typename Traits::Vec3;
  using EPoint3 = typename Traits::EPoint3;

  using BoundingBox3 = typename Traits::BoundingBox3;

  using Ray3     = typename Traits::Ray3;
  using Segment3 = typename Traits::Segment3;

  using TetMesh   = TetrahedralMesh<Traits>;
  using VTX_MARK  = typename TetMesh::VTX_MARK;
  using TET_MARK  = typename TetMesh::TET_MARK;
  using FACE_MARK = typename TetMesh::FACE_MARK;

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

    explicit operator bool() const { return quality > 0; }

    bool operator<(const FaceQuality &rhs) const { return quality < rhs.quality; }
    bool operator==(const FaceQuality &rhs) const { return quality == rhs.quality; }
    bool operator>(const FaceQuality &rhs) const { return quality > rhs.quality; }
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
  Self& setDomain(const BoundingBox3 &bbox);

  // A restricted face has a corresponding intersection point between its
  // Voronoi dual (a segment or a ray) and input surface patch.
  // The distance between the face's circumcenter and the intersection point
  // should be less than this threshold.
  NT restricted_face_distance_threshold;

  /**
   * @brief Set the restricted face distance threshold.
   * @param threshold The threshold should be given in the percentage of the
   * domain diagonal length. For example, `threshold = 1.0` means the 1% of the
   * domain diagonal length.
   */
  Self& setRestrictedFaceDistanceThreshold(NT threshold);

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
                          const EPoint3 &intersection) const;

  /**
   * @brief Evaluate the quality of a tetrahedron.
   *
   * @param tet_mesh The tetrahedral mesh.
   * @param tet_idoff The idoff of the tetrahedron in the tetrahedral mesh.
   *
   * @return The quality of the tetrahedron.
   */
  FaceQuality tetQuality(const TetMesh &tet_mesh, index_t tet_idoff) const;
};

} // namespace OMC