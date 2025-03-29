#pragma once

#include "FaceRefine.h"

namespace OMC {

template <typename T, typename D>
FaceRefine<T, D>::FaceRefine(const Domain &_domain, const Criteria &_criteria,
                             TetMesh &_tet_mesh)
  : domain(_domain)
  , criteria(_criteria)
  , tet_mesh(_tet_mesh)
{
}

template <typename T, typename D>
void FaceRefine<T, D>::scanElements()
{
  size_t num_faces = tet_mesh.sizeFaces();

  for (index_t face_idoff = 0; face_idoff < num_faces; face_idoff++)
  {
    checkNewFace(face_idoff);
  }
}

/**
 * @brief Check a new face to determine if it is restricted to a surface patch
 * and evaluate its quality. If the face is found to be restricted, it is added
 * to the refinement queue for further processing.
 *
 * @param face_idoff The idoff of the face in the tetrahedral mesh.
 *
 * @note While checking a new face, no modifications should be made to its
 * associated conflict zone to ensure consistency and correctness.
 */
template <typename T, typename D>
void FaceRefine<T, D>::checkNewFace(index_t face_idoff)
{
  index_t mirror_idoff = tet_mesh.mirrorFace(face_idoff);

  if (!tet_mesh.isFiniteTet(face_idoff) && !tet_mesh.isFiniteTet(mirror_idoff))
  {
    // face and its mirror face are both infinite.
    return;
  }

  index_t min_idoff = std::min(face_idoff, mirror_idoff);
  index_t max_idoff = std::max(face_idoff, mirror_idoff);

  if (!(tet_mesh.mark(min_idoff, FACE_MARK::VISITED) &&
        tet_mesh.mark(max_idoff, FACE_MARK::VISITED)))
  { // face or its mirror face have been visited.
    // this scenario can occur during parallel processing when multiple threads
    // attempt to process the same face or its mirror face simultaneously.
    // so, we always try to mark the smaller idoff first.
    return;
  }

  SurfacePatchIndex surface_patch;
  EPoint3           intersection;
  if (isFaceRestricted(face_idoff, surface_patch, intersection))
  {
    // face is restricted to a surface patch
    tet_mesh.mark(face_idoff, FACE_MARK::RESTRICTED);
    tet_mesh.mark(mirror_idoff, FACE_MARK::RESTRICTED);
    // evaluate the quality
    FaceQuality face_quality =
      criteria.faceQuality(tet_mesh, face_idoff, intersection);

    if (face_quality)
    { // face should be refined.
      // we put the min_idoff to the queue to ensure identifier unique.
      face_queue.push(min_idoff, face_quality);
    }
  }
  else
  { // face is not restricted
    tet_mesh.unmark(face_idoff, FACE_MARK::RESTRICTED);
    tet_mesh.unmark(mirror_idoff, FACE_MARK::RESTRICTED);
  }
}

/**
 * @brief Checks if a face of the tetrahedral mesh is restricted to a
 * surface patch specified by the domain.
 *
 * A face is considered `restricted` if the dual of the face in the dual
 * Voronoi diagram (usually a segment or a ray) intersects with the surface
 * patch.
 *
 * @param face_idoff The idoff of the face in the tetrahedral mesh.
 * @param surface_patch The index of the surface patch.
 * @param intersection The intersection point between the dual of the face
 * and the surface patch.
 * @return true if the face is restricted to a surface patch, otherwise
 * false.
 */
template <typename T, typename D>
bool FaceRefine<T, D>::isFaceRestricted(index_t            face_idoff,
                                        SurfacePatchIndex &surface_patch,
                                        EPoint3           &intersection) const
{
  // Check if the face is adjacent to two finite tetrahedra
  index_t mirror_idoff = tet_mesh.mirrorFace(face_idoff);

  OMC_EXPENSIVE_ASSERT(tet_mesh.isFiniteTet(face_idoff) ||
                         tet_mesh.isFiniteTet(mirror_idoff),
                       "Invalid face idoff.");

  if (tet_mesh.isFiniteTet(face_idoff) && tet_mesh.isFiniteTet(mirror_idoff))
  {
    // Get the dual segment of the face
    Segment3 dual_seg = tet_mesh.faceDualSegment(face_idoff);

    if (dual_seg.start() == dual_seg.end())
      return false; // degenerate segment

    // Adjust the endpoints of the dual segment to get always the same
    // intersection
    if (canonicalCompare(dual_seg.start(), dual_seg.end()) == Sign::POSITIVE)
      dual_seg = Segment3(dual_seg.end(), dual_seg.start());

    // Check if the dual segment intersects with the surface patch
    if (domain.doIntersectSurface(dual_seg, surface_patch))
    {
      OMC_UNUSED int dimension;
      domain.surfaceIntersection(dual_seg, surface_patch, intersection,
                                 dimension);
      return true;
    }
  }
  else
  {
    // Get the dual ray of the face
    index_t finite_idoff =
      tet_mesh.isFiniteTet(face_idoff) ? face_idoff : mirror_idoff;
    Ray3 dual_ray = tet_mesh.faceDualRay(finite_idoff);

    if (dual_ray.start() == dual_ray.start() + dual_ray.direction())
      return false; // degenerate ray

    if (domain.doIntersectSurface(dual_ray, surface_patch))
    {
      OMC_UNUSED int dimension;
      domain.surfaceIntersection(dual_ray, surface_patch, intersection,
                                 dimension);
      return true;
    }
  }

  return false;
}

template <typename T, typename D>
Sign FaceRefine<T, D>::canonicalCompare(const EPoint3 &p1, const EPoint3 &p2)
{
  return p1.x() < p2.x()   ? Sign::NEGATIVE
         : p1.x() > p2.x() ? Sign::POSITIVE
         : p1.y() < p2.y() ? Sign::NEGATIVE
         : p1.y() > p2.y() ? Sign::POSITIVE
         : p1.z() < p2.z() ? Sign::NEGATIVE
         : p1.z() > p2.z() ? Sign::POSITIVE
                           : Sign::ZERO;
}

} // namespace OMC