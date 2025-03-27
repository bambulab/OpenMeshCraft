#pragma once

#include "FastTriMesh.h"
#include "Tree.h"
#include "TriangleSoup.h"

// clang-format off
#include "OpenMeshCraft/Utils/DisableWarnings.h"
#include "boost/container/flat_set.hpp"
#include "parallel_hashmap/phmap.h"
#include "OpenMeshCraft/Utils/EnableWarnings.h"
// clang-format on

namespace OMC {

template <typename Traits>
class Triangulation
{
private:
  using NT           = typename Traits::NT;
  using EPoint3      = typename Traits::EPoint3;
  using GPoint3      = typename Traits::GPoint3;
  using IPoint3T_SSI = typename Traits::IPoint3T_SSI;
  using IPoint3T_LPI = typename Traits::IPoint3T_LPI;
  using IPoint3T_TPI = typename Traits::IPoint3T_TPI;
  using AsGP         = typename Traits::AsGP;
  using AsEP         = typename Traits::AsEP;
  using ToEP         = typename Traits::ToEP;
  using CreateSSI3   = typename Traits::CreateSSI3;
  using CreateLPI    = typename Traits::CreateLPI;
  using CreateTPI    = typename Traits::CreateTPI;

  using Orient3D   = typename Traits::Orient3D;
  using OrientOn2D = typename Traits::OrientOn2D;
  using LessThan3D = typename Traits::LessThan3D;

  using Segment3_Point3_DoIntersect =
    typename Traits::Segment3_Point3_DoIntersect;
  using Segment3_Segment3_DoIntersect =
    typename Traits::Segment3_Segment3_DoIntersect;
  using Triangle3_Point3_DoIntersect =
    typename Traits::Triangle3_Point3_DoIntersect;

  using FTriMesh = FastTriMesh<Traits>;
  using PntArena = ArrPointArena<Traits>;
  using TriSoup  = TriangleSoup<Traits>;

  // Segment, containing seg_id and seg's endpoints
  using Segment      = UIPair;
  // Collect segments on a triangle
  using SegmentsList = phmap::flat_hash_set<Segment, hash<Segment>>;
  // Segment will be split to sub-segments by TPI points,
  // map sub-segments to its original segment id.
  using RefSegs      = boost::container::flat_set<index_t, std::less<index_t>,
                                                  InlinedVector4<index_t>>;
  using SubSegMap    = phmap::flat_hash_map<Segment, RefSegs, hash<Segment>>;
  // Store segments adajcent to TPI points in a triangle.
  using TPI2Segs     = phmap::flat_hash_map<index_t, InlinedVector4<index_t>>;
  // Pockets
  using Pocket       = InlinedVector16<index_t>;
  using Polygon      = boost::container::flat_set<index_t, std::less<index_t>,
                                                  InlinedVector16<index_t>>;

public:
  Triangulation(TriSoup &_ts, std::vector<index_t> &new_tris,
                std::vector<Label>            &new_labels,
                const MeshArrangements_Config &_config,
                MeshArrangements_Stats        &_stats);

private:
  void triangulateSingleTriangle(index_t t_id, FTriMesh &subm,
                                 std::vector<index_t> &new_tris,
                                 std::vector<Label>   &new_labels);

  /* Split triangle and edges by constraint points ****************************/

  void
  sortedVertexListAlongSegment(const typename TriSoup::Edge2PntsSet &point_list,
                               index_t v0_id, index_t v1_id,
                               std::vector<index_t> &out_point_list);

  void splitSingleTriangleWithTree(FTriMesh                   &subm,
                                   const std::vector<index_t> &points);

  void splitSingleEdge(FTriMesh &subm, index_t v0_id, index_t v1_id,
                       std::vector<index_t> &points);

#ifndef OMC_ARR_3D_PREDS
  std::pair<index_t, bool> locatePointInTree(const FTriMesh &subm, index_t p_id,
                                             const SplitTree &tree);

  std::pair<index_t, bool> locatePointInTreeRecur(const FTriMesh  &subm,
                                                  const GPoint3   &p,
                                                  const SplitTree &tree,
                                                  index_t node_id, UIPair ev);
#else
  index_t locatePointInTree(const FTriMesh &subm, index_t p_id,
                            const SplitTree &tree);

  index_t locatePointInTreeRecur(const FTriMesh &subm, const GPoint3 &p,
                                 const SplitTree &tree, index_t node_id);
#endif

  /* Split triangle by contraint segments *************************************/

  void addConstraintSegmentsInSingleTriangle(FTriMesh             &subm,
                                             std::vector<index_t> &seg_ids,
                                             std::vector<Segment> &segments);

  void addConstraintSegment(FTriMesh &subm, const Segment &seg,
                            std::vector<Segment> &segment_list,
                            SubSegMap &sub_segs_map, TPI2Segs &tpi2segs);

  void findIntersectingElements(FTriMesh &subm, index_t &v_start,
                                index_t                  &v_stop,
                                InlinedVector64<index_t> &intersected_edges,
                                InlinedVector64<index_t> &intersected_tris,
                                std::vector<Segment>     &segment_list,
                                SubSegMap &sub_segs_map, TPI2Segs &tpi2segs);

  void splitSegmentInSubSegments(index_t v_start, index_t v_stop,
                                 index_t mid_point, SubSegMap &sub_segs_map);

  index_t createTPI(FTriMesh &subm, index_t seg0_id, index_t seg1_id);

  std::pair<bool, index_t> addAndFixTPI(index_t seg0_id, index_t seg1_id,
                                        IPoint3T_TPI *vtx);

  index_t fixTPI(index_t seg0_id, index_t seg1_id, IPoint3T_TPI *vtx);

  template <typename tri_iterator, typename edge_iterator>
  void boundaryWalker(const FTriMesh &subm, index_t v_start, index_t v_stop,
                      tri_iterator curr_p, edge_iterator curr_e,
                      InlinedVector64<index_t> &h);

  void earcutLinear(const FTriMesh &subm, const InlinedVector64<index_t> &poly,
                    InlinedVector64<index_t> &tris);

  /* Solve pockets ************************************************************/

  void solvePocketsInCoplanarTriangle(const FTriMesh       &subm,
                                      std::vector<index_t> &new_tris,
                                      std::vector<Label>   &new_labels,
                                      const Label          &label);

  void findPocketsInTriangle(const FTriMesh       &subm,
                             std::vector<Pocket>  &tri_pockets,
                             std::vector<Polygon> &tri_polygons);

  /* Postfix indices **********************************************************/

  void postFixIndices(std::vector<index_t> &new_tris,
                      std::vector<Label> &new_labels, index_t tpi_begin);

private:
#ifndef OMC_ARR_3D_PREDS
  static bool pointInsideSegmentCollinear(const FTriMesh &subm, index_t ev0_id,
                                          index_t ev1_id, index_t p_id);
#else
  static bool fastPointOnLine(const FTriMesh &subm, index_t e_id, index_t p_id);

  static bool pointInsideSegment(const FTriMesh &subm, index_t e0_id,
                                 index_t e1_id, index_t p_id);

  static bool segmentsIntersectInside(const FTriMesh &subm, index_t e00_id,
                                      index_t e01_id, index_t e10_id,
                                      index_t e11_id);
#endif

private:
  TriSoup &ts;

  std::vector<PntArena> &pnt_arenas;

  /* Configuration */
  const MeshArrangements_Config &config;
  /* Statistics */
  MeshArrangements_Stats        &stats;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Triangulation.inl"
#endif