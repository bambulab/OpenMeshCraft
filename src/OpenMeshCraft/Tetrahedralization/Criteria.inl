#pragma once

#include "Criteria.h"

#include "OpenMeshCraft/Geometry/Determinant.h"

#include <numbers>

namespace OMC {

template <typename T, typename D>
auto TetMeshCriteria<T, D>::setDomain(const Domain &_domain) -> Self &
{
  domain             = &_domain;
  domain_bbox        = domain->bbox();
  domain_diag_length = domain_bbox.diagonal_length();
  return *this;
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::setRestrictedFaceDistanceThreshold(NT threshold)
  -> Self &
{
  restricted_face_distance_threshold = (threshold * 0.01) * domain_diag_length;
  return *this;
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::setMinUniformSizeThreshold(NT threshold) -> Self &
{
  cell_min_uniform_size_threshold = (threshold * 0.01) * domain_diag_length;
  return *this;
}
template <typename T, typename D>
auto TetMeshCriteria<T, D>::setMaxUniformSizeThreshold(NT threshold) -> Self &
{
  cell_max_uniform_size_threshold = (threshold * 0.01) * domain_diag_length;
  return *this;
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::setCellRadiusEdgeRatioThreshold(NT threshold)
  -> Self &
{
  cell_radius_edge_ratio_threshold = threshold;
  return *this;
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::faceQuality(const TetMesh &tet_mesh,
                                        index_t        face_idoff,
                                        const Point3  &intersection) const
  -> FaceQuality
{
  NT quality = 0.0;

  index_t v0 =
    tet_mesh.tetNode(TetMesh::clipId(face_idoff) + TetMesh::tetON1(face_idoff));

  // restricted face distance ===============================================

  // get the circumcenter of the face
  Point3 circumcenter = tet_mesh.faceDualPoint(face_idoff);
  NT     circumradius = (circumcenter - tet_mesh.point(v0)).length();

  // compute the distance between the circumcenter and the intersection point
  NT distance = (circumcenter - intersection).norm();

  // check if the distance is less than the threshold
  if (distance > restricted_face_distance_threshold)
    quality += distance;

  // restricted face size ===================================================

  // uniform size -----------------------------------------------------------
  if (cell_min_uniform_size_threshold > 0.0 &&
      circumradius < cell_min_uniform_size_threshold)
  { // filter out small faces
    return FaceQuality(0);
  }

  if (cell_max_uniform_size_threshold > 0.0 &&
      circumradius > cell_max_uniform_size_threshold)
  { // refine too large faces
    return FaceQuality(circumradius / cell_max_uniform_size_threshold);
  }

  // sizing field -----------------------------------------------------------
  if (domain && domain->hasSizingField())
  {
    // get the size
    NT size = domain->pointSize(circumcenter);
    if (size > 0.0 && circumradius > size)
    { // refine too large faces
      return FaceQuality(circumradius / size);
    }
  }

  // add more quality metrics below =========================================

  return FaceQuality(quality);
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::cellQuality(const TetMesh &tet_mesh,
                                        index_t tet_idoff) const -> CellQuality
{
  // ensure valid and unique idoff
  tet_idoff = TetMesh::clipId(tet_idoff);

  const index_t *tet_nodes = &tet_mesh.tetNode(tet_idoff);

  const Point3 &p = tet_mesh.point(tet_nodes[0]);
  const Point3 &q = tet_mesh.point(tet_nodes[1]);
  const Point3 &r = tet_mesh.point(tet_nodes[2]);
  const Point3 &s = tet_mesh.point(tet_nodes[3]);

  // Compute maximal squared edge lengths
  NT max_sq_length = sq_length(p, q);
  max_sq_length    = std::max(max_sq_length, sq_length(p, r));
  max_sq_length    = std::max(max_sq_length, sq_length(p, s));
  max_sq_length    = std::max(max_sq_length, sq_length(q, r));
  max_sq_length    = std::max(max_sq_length, sq_length(q, s));
  max_sq_length    = std::max(max_sq_length, sq_length(r, s));
  NT max_length    = std::sqrt(max_sq_length);

  // Compute unweighted CircumCenter and CircumRadius
  Point3 unweighted_cc = ConstructCircumcenter3()(p, q, r, s);
  NT     unweighted_cr = length(p, unweighted_cc);

  // cell size ==============================================================

  // uniform size -----------------------------------------------------------
  if (cell_min_uniform_size_threshold > 0.0 &&
      unweighted_cr < cell_min_uniform_size_threshold)
  { // filter out small cells
    return CellQuality(0);
  }

  if (cell_max_uniform_size_threshold > 0.0 &&
      unweighted_cr > cell_max_uniform_size_threshold)
  { // refine too large cells
    return CellQuality(unweighted_cr / cell_max_uniform_size_threshold);
  }

  // sizing field -----------------------------------------------------------
  if (domain && domain->hasSizingField())
  {
    // get the size
    NT size = domain->pointSize(unweighted_cc);
    if (size > 0.0 && unweighted_cr > size)
    { // refine too large cells
      return CellQuality(unweighted_cr / size);
    }
  }

  // cell shape =============================================================

  // Compute inradius
  NT area_pqr = area(p, q, r), area_pqs = area(p, q, s),
     area_prs = area(p, r, s), area_qrs = area(q, r, s);
  NT tet_area = area_pqr + area_pqs + area_prs + area_qrs;
  NT tet_vol  = volume(p, q, r, s);
  NT inradius = 3.0 * tet_vol / tet_area;

  // Compute radius-edge ratio ----------------------------------------------
  constexpr NT _2_SQRT_6         = 4.898979485566356; // 2 * sqrt(6)
  NT           radius_edge_ratio = _2_SQRT_6 * inradius / max_length;

  if (radius_edge_ratio < cell_radius_edge_ratio_threshold)
    return CellQuality(1.0 - radius_edge_ratio);

#if 0
  // Compute volume-edge ratio ----------------------------------------------
  constexpr NT _6_SQRT_2 = 8.485281374238570; // 6 * sqrt(2)
  NT volume_edge_ratio   = _6_SQRT_2 * tet_vol / (max_length * max_sq_length);

  // Compute aspect ratio ---------------------------------------------------
  constexpr NT _3_SQRT_3_2 = 3.674234614174767; // 3 * sqrt(3/2)

  NT max_area =
    std::max(std::max(area_pqr, area_pqs), std::max(area_prs, area_qrs));
  NT min_height   = tet_vol / max_area; // (* 3) is done in _3_SQRT_3_2
  NT aspect_ratio = _3_SQRT_3_2 * min_height / max_length;

  // Compute minimal dihedral angle -----------------------------------------
  NT min_dihedral_angle = minDihedralAngle(p, q, r, s);
#endif

  return CellQuality(0);
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::length(const Point3 &p, const Point3 &q) -> NT
{
  return (q - p).norm();
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::sq_length(const Point3 &p, const Point3 &q) -> NT
{
  return (q - p).sqrnorm();
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::area(const Point3 &p, const Point3 &q,
                                 const Point3 &r) -> NT
{
  return std::abs((q - p).cross(r - p).norm() / 2.0);
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::volume(const Point3 &p, const Point3 &q,
                                   const Point3 &r, const Point3 &s) -> NT
{
  return std::abs(((q - p).cross(r - p)).dot(s - p) / 6.0);
}

template <typename T, typename D>
auto TetMeshCriteria<T, D>::minDiahedralAngle(const Point3 &p, const Point3 &q,
                                              const Point3 &r, const Point3 &s)
  -> NT
{
  Vec3 v01 = (p - q);
  Vec3 v02 = (p - r);
  Vec3 v03 = (p - s);
  Vec3 v12 = (q - r);
  Vec3 v13 = (q - s);
  Vec3 v23 = (r - s);

  Vec3 v_01_02 = v01.cross(v02);
  NT   a_012   = v_01_02.dot(v_01_02);

  Vec3 v_01_03 = v01.cross(v03);
  NT   a_013   = v_01_03.dot(v_01_03);

  Vec3 v_12_13 = v12.cross(v13);
  NT   a_123   = v_12_13.dot(v_12_13);

  Vec3 v_02_03 = v02.cross(v03);
  NT   a_023   = v_02_03.dot(v_02_03);

  NT min_quotient = v01.dot(v01) / (a_012 * a_013);
  min_quotient    = (std::min)(min_quotient, v02.dot(v02) / (a_012 * a_023));
  min_quotient    = (std::min)(min_quotient, v03.dot(v03) / (a_013 * a_023));
  min_quotient    = (std::min)(min_quotient, v12.dot(v12) / (a_012 * a_123));
  min_quotient    = (std::min)(min_quotient, v13.dot(v13) / (a_013 * a_123));
  min_quotient    = (std::min)(min_quotient, v23.dot(v23) / (a_023 * a_123));
  min_quotient    = sqrt(min_quotient);

  return std::abs(
    std::asin(determinant(v01.x(), v01.y(), v01.z(), v02.x(), v02.y(), v02.z(),
                          v03.x(), v03.y(), v03.z()) *
              min_quotient) *
    NT(180) / NT(std::numbers::pi));
}

} // namespace OMC