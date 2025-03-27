#pragma once

#include "QuadTree.h"

#include <algorithm>

namespace OMC {

template <typename Traits>
auto QuadTree<Traits>::adj_vertex(index_t vidx, index_t axis, bool dir)
  -> index_t
{
  return m_adj_vertices[vidx][(axis << 1) + dir];
}

template <typename Traits>
auto QuadTree<Traits>::calc_vertex_position(index_t nd_idx, index_t nv_idx)
  -> OrPoint
{
  NodeCRef nd = this->node(nd_idx);
  OrPoint  c  = this->node_center(nd);
  OrPoint  h  = this->node_side_length(nd) * NT(0.5);
  switch (nv_idx)
  {
  case 0:
    return OrPoint(c.x() - h.x(), c.y() - h.y());
  case 1:
    return OrPoint(c.x() + h.x(), c.y() - h.y());
  case 2:
    return OrPoint(c.x() - h.x(), c.y() + h.y());
  case 3:
    return OrPoint(c.x() + h.x(), c.y() + h.y());
  default:
#ifdef OMC_ENABLE_ASSERT
    OMC_ASSERT(false, "vertex index {} out of range.", nv_idx);
#else
    return OrPoint(NT(0.), NT(0.), NT(0.));
#endif
  }
}

template <typename Traits>
void QuadTree<Traits>::set_adj_vertices_pair(index_t vl, index_t vh,
                                             index_t axis)
{
  m_adj_vertices[vl][(axis << 1) + true]  = vh;
  m_adj_vertices[vh][(axis << 1) + false] = vl;
}

template <typename Traits>
void QuadTree<Traits>::build_vertices()
{
  this->m_vertices.clear();
  m_adj_vertices.clear();
  // During building vertices, the VertexPtr stored in Node is temporarily
  // interpreted as the index of vertex. This interpretation is used to random
  // access different containers.

  // each node has 4 vertices located on its 4 faces,
  // we store this relation in face_vertices.
  std::vector<std::array<index_t, 2 * Dimension>> face_vertices;
  // each vertex has 4 vertices located on its 4 adjacent edges,
  // we store this relation in edge_vertices.
  std::vector<std::array<index_t, 2 * Dimension>> edge_vertices;

  // initialize edge_vertices
  std::array<index_t, 2 * Dimension> invalid_indices;
  std::fill(invalid_indices.begin(), invalid_indices.end(), InvalidIndex);

  // An edge of a node is given by (lower index, higher index),
  // try to find the middle vertex on this edge if it exists.
  auto find_edge_vertex = [this, &edge_vertices, &invalid_indices](
                            NodeRef nd, index_t li, index_t hi) -> index_t
  {
    // use xor to get the axis
    index_t axis = ((li ^ hi) >> 1) << 1;
    index_t vl   = nd.vertex(li);
    index_t vh   = nd.vertex(hi);
    // find at higher direction of lower vertex.
    if (is_valid_idx(edge_vertices[vl][axis + true]))
      return edge_vertices[vl][axis + true];
    // find at lower direction of higher vertex. (is this neccessary?)
    if (is_valid_idx(edge_vertices[vh][axis + false]))
      return edge_vertices[vh][axis + false];

    index_t new_vidx = this->new_vertex();
    // set edge vertices
    edge_vertices.push_back(invalid_indices);
    edge_vertices[vl][axis + true]  = new_vidx;
    edge_vertices[vh][axis + false] = new_vidx;
    // set adjacent relationship
    m_adj_vertices.push_back(invalid_indices);
    m_adj_vertices[vl][axis + true]        = new_vidx;
    m_adj_vertices[vh][axis + false]       = new_vidx;
    m_adj_vertices[new_vidx][axis + false] = vl;
    m_adj_vertices[new_vidx][axis + true]  = vh;
    return new_vidx;
  };

  // build 4 corner vertices for root node.
  for (index_t i = 0; i < Degree; i++)
  {
    this->root_node().vertex(i) = this->new_vertex();
  }
  m_adj_vertices.resize(Degree, invalid_indices);
  edge_vertices.resize(Degree, invalid_indices);

  // traversal nodes to build vertices for them.
  std::queue<index_t> nodes_to_traverse;
  index_t             curr_depth;

  nodes_to_traverse.push(this->root_node_idx());
  curr_depth = 0;

  // Iterate nodes
  while (!nodes_to_traverse.empty())
  {
    index_t nd_idx = nodes_to_traverse.front();
    NodeRef nd     = this->node(nd_idx);
    nodes_to_traverse.pop();

    if (curr_depth != nd.depth())
    {
      OMC_ASSERT(curr_depth == nd.depth() - 1,
                 "depth delta is larger than 1 during traverse.");
      curr_depth = nd.depth();
      // reset all edge_vertices
      std::fill(edge_vertices.begin(), edge_vertices.end(), invalid_indices);
    }

    // When traverse to this node, its corner vertices have been built.
    // If it is leaf node, do nothing.
    if (nd.is_leaf())
      continue;
    // else we build face vertices and edge vertices for this node.

    const auto &nd_vs = nd.vertices();
    index_t     v0    = nd_vs[0];
    index_t     v1    = nd_vs[1];
    index_t     v2    = nd_vs[2];
    index_t     v3    = nd_vs[3];

    // try to find edge vertices,
    // if not found, we build new vertices and store in edge_vertices.
    index_t ev01 = find_edge_vertex(nd, 0, 1);
    index_t ev02 = find_edge_vertex(nd, 0, 2);
    index_t ev13 = find_edge_vertex(nd, 1, 3);
    index_t ev23 = find_edge_vertex(nd, 2, 3);

    // build center vertices
    index_t cv = this->new_vertex();
    edge_vertices.push_back(invalid_indices);
    m_adj_vertices.push_back(invalid_indices);

    // children nodes inherit vertices.
    this->node(nd.child(0)).vertices() = {v0, ev01, ev02, cv};
    this->node(nd.child(1)).vertices() = {ev01, v1, cv, ev13};
    this->node(nd.child(2)).vertices() = {ev02, cv, v2, ev23};
    this->node(nd.child(3)).vertices() = {cv, ev13, ev23, v3};

    // set adjancen relationship between
    // (1) between center vertex and all edge vertices
    set_adj_vertices_pair(ev02, cv, 0);
    set_adj_vertices_pair(cv, ev13, 0);
    set_adj_vertices_pair(ev01, cv, 1);
    set_adj_vertices_pair(cv, ev23, 1);

    for (index_t i = 0; i < Degree; i++)
      nodes_to_traverse.push(nd.child(i));
  }

  // calculate positions for all vertices
  std::vector<uint8_t> position_calculated(this->m_vertices.size(), false);
  nodes_to_traverse.push(this->root_node_idx());

  while (!nodes_to_traverse.empty())
  {
    index_t nd_idx = nodes_to_traverse.front();
    NodeRef nd     = this->node(nd_idx);
    nodes_to_traverse.pop();

    if (nd.is_leaf())
    {
      for (index_t i = 0; i < Degree; i++)
      {
        index_t vi = nd.vertex(i);
        if (!position_calculated[vi])
        {
          this->vertex(vi).position() = calc_vertex_position(nd_idx, i);
          position_calculated[vi]     = true;
        }
      }
    }
    else
    {
      for (index_t i = 0; i < Degree; i++)
        nodes_to_traverse.push(nd.child(i));
    }
  }
}

template <typename Traits>
void QuadTree<Traits>::calc_box_for_children(NodeRef nd, OrPointCRef c)
{
  OrPointCRef minb = nd.box().min_bound();
  OrPointCRef maxb = nd.box().max_bound();

  // clang-format off
  // child 0(000, -x-y)
  this->node(nd.child(0)).box() = Bbox(minb, c);
  // child 1(001, +x-y)
  this->node(nd.child(1)).box() = Bbox(OrPoint(c.x(), minb.y()), OrPoint(maxb.x(), c.y()));
  // child 2(010, -x+y)
  this->node(nd.child(2)).box() = Bbox(OrPoint(minb.x(), c.y()), OrPoint(c.x(), maxb.y()));
  // child 3(011, +x+y)
  this->node(nd.child(3)).box() = Bbox(c, maxb);
  // clang-format on
}

} // namespace OMC