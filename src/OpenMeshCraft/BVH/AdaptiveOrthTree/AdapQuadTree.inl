#pragma once

#include "AdapQuadTree.h"

namespace OMC {

template <typename Traits>
void AdapQuadTree<Traits>::calc_box_for_children(
  NodeRef nd, OrPointCRef c, std::array<Bbox, Degree> &child_boxes)
{
  OrPointCRef minb = nd.box().min_bound();
  OrPointCRef maxb = nd.box().max_bound();

  // clang-format off
  // child 0(00, -x-y)
  child_boxes[0] = Bbox(minb, c);
  // child 1(01, +x-y)
  child_boxes[1] = Bbox(OrPoint(c.x(), minb.y()), OrPoint(maxb.x(), c.y()));
  // child 2(10, -x+y)
  child_boxes[2] = Bbox(OrPoint(minb.x(), c.y()), OrPoint(c.x(), maxb.y()));
  // child 3(11, +x+y)
  child_boxes[3] = Bbox(c, maxb);
  // clang-format on
}

} // namespace OMC