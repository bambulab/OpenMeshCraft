#pragma once

#include "DelaunayRefine.h"

#ifdef OMC_DELAUNAY_REFINE_PROFILE
  #include "OpenMeshCraft/Utils/Logger.h"

  #include <iostream>
#endif

namespace OMC {

template <typename T, typename D>
DelaunayRefine<T, D>::DelaunayRefine(const Domain   &_domain,
                                     const Criteria &_criteria, Points &_points,
                                     Weights &_weights, TetMesh &_tet_mesh)
  : domain(_domain)
  , criteria(_criteria)
  , points(_points)
  , weights(_weights)
  , tet_mesh(_tet_mesh)
{
}

template <typename T, typename D>
void DelaunayRefine<T, D>::scanFaces()
{
  size_t num_faces = tet_mesh.sizeFaces();

  for (index_t face_idoff = 0; face_idoff < num_faces; face_idoff++)
  {
    checkNewFace(face_idoff);
  }
}

template <typename T, typename D>
bool DelaunayRefine<T, D>::isFaceRefineDone()
{
  // TODO: An external force stop control
  // TODO: Other internal stop conditions
  return face_queue.empty();
}

template <typename T, typename D>
auto DelaunayRefine<T, D>::processOneFace() -> FaceConflictStatus
{
  // Get the next face to process from the queue ========================

  auto [face_idoff, face_to_refine] = face_queue.top();
  face_queue.pop();

  OMC_EXPENSIVE_ASSERT(!tet_mesh.isTetDeleted(face_idoff),
                       "The face to process is deleted.");

  index_t mirror_idoff = tet_mesh.mirrorFace(face_idoff);
  index_t finite_idoff =
    tet_mesh.isFiniteTet(face_idoff) ? face_idoff : mirror_idoff;

  // Get the refinement point ===========================================

  Point3 refine_point = face_to_refine.intersection;

  // Locate the refinement point in Delaunay tetrahedralization =========

  DelTet del_tet(tet_mesh);

  index_t tet_id    = TetMesh::clipId(finite_idoff);
  int     dimension = -1;
  del_tet.walk(refine_point, tet_id, &dimension);

  if (dimension == 0)
  {
    // The dual point is coincident with a vertex of the tetrahedral mesh.
    return FaceConflictStatus::COINCIDENT_VERTEX;
  }

  // Find the conflict zone of the refinement point =====================

  InlinedVector64<index_t> conflict_tets;
  InlinedVector64<index_t> conflict_corners;
  del_tet.conflict(refine_point, /*weight*/ 0, tet_id, conflict_tets,
                   conflict_corners);

  if (conflict_tets.empty())
  {
    // The dual point is hidden by an existing weighted vertex.
    return FaceConflictStatus::HIDDEN_POINT;
  }

  // check if the face to refine is conflict with the dual point
  if (std::find(conflict_tets.begin(), conflict_tets.end(),
                TetMesh::clipId(face_idoff)) == conflict_tets.end() ||
      std::find(conflict_tets.begin(), conflict_tets.end(),
                TetMesh::clipId(mirror_idoff)) == conflict_tets.end())
  {
    // clear marks
    for (index_t tet_idoff : conflict_tets)
      tet_mesh.unmark(tet_idoff, TET_MARK::CONFLICT);
    for (index_t corner_idoff : conflict_corners)
      tet_mesh.unmark(corner_idoff, TET_MARK::VISITED);
    return FaceConflictStatus::FACE_NOT_CONFLICT;
  }

  // Remove faces in conflict zone from the queue ========================
  for (index_t cf_tet : conflict_tets)
  {
    for (index_t i = 0; i < 4; i++)
    {
      index_t cf_face        = cf_tet + i;
      index_t mirror_cf_face = tet_mesh.mirrorFace(cf_face);
      if (tet_mesh.isMarked(cf_face, FACE_MARK::RESTRICTED))
      {
        if (face_queue.exist(cf_face))
          face_queue.remove(cf_face);
        if (face_queue.exist(mirror_cf_face))
          face_queue.remove(mirror_cf_face);
      }
    }
  }

  // Insert the refinement point into the mesh ============================
  del_tet.removeConflicts(conflict_tets);
  index_t new_vtx_vid = newVertex(refine_point, /*weight*/ 0);
  del_tet.filling(new_vtx_vid, conflict_corners);

  // Check new faces in the conflict zone =================================

  for (index_t corner : conflict_corners) // for each corner `c`
  {
    tet_mesh.unmark(corner, FACE_MARK::VISITED);

    index_t oppo  = tet_mesh.tetNeigh(corner);
    index_t idoff = TetMesh::clipId(oppo);
    for (index_t i = 0; i < 4; i++)
      checkNewFace(idoff + i);
  }

  return FaceConflictStatus::OK;
}

template <typename T, typename D>
void DelaunayRefine<T, D>::refineFaces()
{
#ifdef OMC_DELAUNAY_REFINE_PROFILE
  size_t num_inserted_point    = 0;
  size_t num_coincident_vertex = 0;
  size_t num_hidden_point      = 0;
  size_t num_face_not_conflict = 0;
#endif

  scanFaces();

  while (!isFaceRefineDone())
  {
    FaceConflictStatus cs = processOneFace();

#ifdef OMC_DELAUNAY_REFINE_PROFILE
    switch (cs)
    {
    case FaceConflictStatus::COINCIDENT_VERTEX:
      num_coincident_vertex += 1;
      break;
    case FaceConflictStatus::HIDDEN_POINT:
      num_hidden_point += 1;
      break;
    case FaceConflictStatus::FACE_NOT_CONFLICT:
      num_face_not_conflict += 1;
      break;
    case FaceConflictStatus::OK:
      num_inserted_point += 1;
      if (num_inserted_point % 100 == 0)
        std::cout << std::format("\rIntersected points {}         ",
                                 num_inserted_point);
      break;
    }
#endif
  }

#ifdef OMC_DELAUNAY_REFINE_PROFILE
  Logger::info("\nDelaunayRefine FaceRefine profile:");
  Logger::info(std::format("  Inserted points: {}", num_inserted_point));
  Logger::info(std::format("  Coincident vertex: {}", num_coincident_vertex));
  Logger::info(std::format("  Hidden point: {}", num_hidden_point));
  Logger::info(std::format("  Face not conflict: {}", num_face_not_conflict));
#endif

  tet_mesh.removeDeletedTets();
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
void DelaunayRefine<T, D>::checkNewFace(index_t face_idoff)
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
  Point3            intersection;
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
      FaceToRefine face_to_refine(face_quality, intersection);
      face_queue.push(min_idoff, face_to_refine);
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
bool DelaunayRefine<T, D>::isFaceRestricted(index_t            face_idoff,
                                            SurfacePatchIndex &surface_patch,
                                            Point3 &intersection) const
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
void DelaunayRefine<T, D>::scanCells()
{
  size_t num_tets = tet_mesh.sizeTets();

  for (index_t tet_id = 0; tet_id < num_tets; tet_id++)
  {
    checkNewCell(TetMesh::toIdOff(tet_id));
  }
}

template <typename T, typename D>
bool DelaunayRefine<T, D>::isCellRefineDone()
{
  // TODO: An external force stop control
  // TODO: Other internal stop conditions
  return cell_queue.empty();
}

template <typename T, typename D>
auto DelaunayRefine<T, D>::processOneCell() -> CellConflictStatus
{
  // Get the next cell to process from the queue ========================

  auto [tet_idoff, cell_to_refine] = cell_queue.top();
  cell_queue.pop();

  OMC_EXPENSIVE_ASSERT(!tet_mesh.isTetDeleted(tet_idoff),
                       "The tetrahedron to process is deleted.");

  // Get the refinement point ===========================================

  Point3 refine_point = tet_mesh.tetDualPoint(tet_idoff);

  // Locate the refinement point in Delaunay tetrahedralization =========

  DelTet del_tet(tet_mesh);

  index_t tet_id    = TetMesh::clipId(tet_idoff);
  int     dimension = -1;
  del_tet.walk(refine_point, tet_id, &dimension);

  if (dimension == 0)
  {
    // The dual point is coincident with a vertex of the tetrahedral mesh.
    return CellConflictStatus::COINCIDENT_VERTEX;
  }

  // Find the conflict zone of the refinement point =====================

  InlinedVector64<index_t> conflict_tets;
  InlinedVector64<index_t> conflict_corners;
  del_tet.conflict(refine_point, /*weight*/ 0, tet_id, conflict_tets,
                   conflict_corners);

  if (conflict_tets.empty())
  {
    // The dual point is hidden by an existing weighted vertex.
    return CellConflictStatus::HIDDEN_POINT;
  }

  // Remove cells in conflict zone from the queue ========================
  for (index_t cf_tet : conflict_tets)
  {
    if (cell_queue.exist(cf_tet))
      cell_queue.remove(cf_tet);
  }

  // Insert the refinement point into the mesh ============================
  del_tet.removeConflicts(conflict_tets);
  index_t new_vtx_vid = newVertex(refine_point, /*weight*/ 0);
  del_tet.filling(new_vtx_vid, conflict_corners);

  // Check new cells in the conflict zone =================================

  for (index_t corner : conflict_corners) // for each corner `c`
  {
    checkNewCell(TetMesh::clipId(tet_mesh.tetNeigh(corner)));
  }

  return CellConflictStatus::OK;
}

template <typename T, typename D>
void DelaunayRefine<T, D>::refineCells()
{
  scanCells();

#ifdef OMC_DELAUNAY_REFINE_PROFILE
  size_t num_inserted_point    = 0;
  size_t num_coincident_vertex = 0;
  size_t num_hidden_point      = 0;
#endif

  while (!isCellRefineDone())
  {
    CellConflictStatus cs = processOneCell();

#ifdef OMC_DELAUNAY_REFINE_PROFILE
    switch (cs)
    {
    case CellConflictStatus::COINCIDENT_VERTEX:
      num_coincident_vertex += 1;
      break;
    case CellConflictStatus::HIDDEN_POINT:
      num_hidden_point += 1;
      break;
    case CellConflictStatus::OK:
      num_inserted_point += 1;
      if (num_inserted_point % 100 == 0)
        std::cout << std::format("\rIntersected points {}         ",
                                 num_inserted_point);
      break;
    }
#endif
  }

#ifdef OMC_DELAUNAY_REFINE_PROFILE
  Logger::info("\nDelaunayRefine CellRefine profile:");
  Logger::info(std::format("  Inserted points: {}", num_inserted_point));
  Logger::info(std::format("  Coincident vertex: {}", num_coincident_vertex));
  Logger::info(std::format("  Hidden point: {}", num_hidden_point));
#endif

  tet_mesh.removeDeletedTets();
}

/**
 * @brief Check a new cell to determine if it need to be refined.
 *
 * @param tet_idoff The idoff of the tetrahedron in the tetrahedral mesh.
 *
 * @note While checking a new cell, no modifications should be made to its
 * associated conflict zone to ensure consistency and correctness.
 */
template <typename T, typename D>
void DelaunayRefine<T, D>::checkNewCell(index_t tet_idoff)
{
  // ensure unique idoff
  tet_idoff = TetMesh::clipId(tet_idoff);

  if (!tet_mesh.isFiniteTet(tet_idoff))
  { // the tetrahedron is infinite.
    return;
  }

  Point3 dual_point = tet_mesh.tetDualPoint(tet_idoff);
  if (!domain.isInDomain(dual_point))
  { // the dual point is outside the domain.
    return;
  }

  CellQuality cell_quality = criteria.cellQuality(tet_mesh, tet_idoff);

  if (cell_quality)
  { // the tetrahedron should be refined.
    cell_queue.push(tet_idoff, cell_quality);
  }
}

template <typename T, typename D>
index_t DelaunayRefine<T, D>::newVertex(const Point3 &point, NT weight)
{
  // TODO lock in multi-threaded env.

  index_t new_vtx_id = points.size();
  points.push_back(point);
  weights.push_back(weight);
  tet_mesh.newVtx(points.size() - 1);
  return new_vtx_id;
}

template <typename T, typename D>
Sign DelaunayRefine<T, D>::canonicalCompare(const Point3 &p1, const Point3 &p2)
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