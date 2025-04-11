#pragma once

#include "OrthogonalTree.h"

namespace OMC {

/**
 * @brief Octree, i.e., orthogonal tree in 3D.
 * @details Two directions along each axis in Cartesian space, relative to a
 * node.
 *
 * Directions are mapped to numbers as 3-bit integers,
 * though the numbers 6 and 7 are not used because there are only 6 different
 * directions.
 *
 * The first two bits indicate the axis (00 = x, 01 = y, 10 = z),
 * the third bit indicates the direction along that axis (0 = -, 1 = +).
 *
 * It has the following fomula:
 *
 * 	index = axis << 1 + direction.
 *
 * The following diagram may be a useful reference:
 *
 *            5 *
 *              |  * 3
 *              | /                  z+
 *              |/                   *  y+
 *     0 *------+------* 1           | *
 *             /|                    |/
 *            / |                    +-----* x+
 *         2 *  |
 *              * 4
 *
 * The eight children and corner vertices have following indices:
 *         6(110)              7(111)
 *            -------------------
 *  +z       /|                /|
 *          / |               / |
 *         /  |       5(101) /  |
 * 4(100) -------------------   |        +y
 *        |   |_____________|___|
 *        |  / 2(010)       |  / 3(011)
 *  -z    | /               | /
 *        |/________________|/          -y
 * -x    0(000)            1(001)        +x
 *
 */
template <typename _Traits>
class OcTree : public OrthogonalTree<_Traits>
{
public:
  using Traits = _Traits;

  static constexpr size_t Dimension = Traits::Dimension;
  static constexpr size_t Degree    = (1u << Dimension);

  static constexpr bool EnableVertices = Traits::EnableVertices;

  using Base = OrthogonalTree<Traits>;

  using NT = typename Base::NT;

  using Bbox = typename Base::Bbox;

  using OrBbox = typename Base::OrBbox;
  OrthTreeAbbreviate(OrBbox);

  using OrPoint = typename Base::OrPoint;
  OrthTreeAbbreviate(OrPoint);

  using Node = typename Base::Node;
  OrthTreeAbbreviate(Node);

  using Vertex = typename Base::Vertex;
  OrthTreeAbbreviate(Vertex);

public:
  index_t adj_vertex(index_t vidx, index_t axis, bool dir);

protected:
  /**
   * @brief Build vertices for the OcTree.
   * Each node has eight corner vertices. A vertex is unique to all adjacent
   * nodes.
   */
  virtual void build_vertices() final;

  /**
   * @brief Calculate bounding box for children nodes.
   *
   * @param nd The parent node
   * @param center The parent node's center
   */
  virtual void calc_box_for_children(NodeRef nd, OrPointCRef center) final;

protected:
  /**
   * @brief Implementation of build_vertices().
   * @tparam HasVertex
   */
  void build_vertices_impl();

  /**
   * @brief Get the position of a vertex. the vertex is located by node + local
   * vertex index.
   * @param nd_idx node index
   * @param nv_idx local index of vertex in given node
   * @return PointT the position of the vertex
   */
  OrPoint calc_vertex_position(index_t nd_idx, index_t nv_idx);

  /**
   * @brief Set two vertices are adjacent along the given axis.
   *
   * @param vl lower vertex
   * @param vh higher vertex
   * @param axis
   */
  void set_adj_vertices_pair(index_t vl, index_t vh, index_t axis);

protected:
  /// Six adjcent vertices of each vertex.
  std::vector<std::array<index_t, 2 * Dimension>> m_adj_vertices;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "OcTree.inl"
#endif