#pragma once

#include "Criteria.h"

namespace OMC {

template <typename T>
auto TetMeshCriteria<T>::setDomain(const BoundingBox3 &bbox) -> Self &
{
  domain_bbox        = bbox;
  domain_diag_length = (bbox.max_bound() - bbox.min_bound()).norm();
  return *this;
}

template <typename T>
auto TetMeshCriteria<T>::setRestrictedFaceDistanceThreshold(NT threshold)
  -> Self &
{
  restricted_face_distance_threshold = (threshold * 0.01) * domain_diag_length;
  return *this;
}

template <typename T>
auto TetMeshCriteria<T>::faceQuality(const TetMesh &tet_mesh,
                                     index_t        face_idoff,
                                     const EPoint3 &intersection) const
  -> FaceQuality
{
  NT quality = 0.0;

  // restricted face distance ===============================================

  // get the circumcenter of the face
  EPoint3 circumcenter = tet_mesh.faceDualPoint(face_idoff);

  // compute the distance between the circumcenter and the intersection point
  NT distance = (circumcenter - intersection).norm();

  // check if the distance is less than the threshold
  if (distance > restricted_face_distance_threshold)
    quality += distance;

  // add more quality metrics below =========================================

  return FaceQuality(quality);
}

} // namespace OMC