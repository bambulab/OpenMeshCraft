#pragma once

#include "AdapOcTree.h"

namespace OMC {

template <typename Traits>
void AdapOcTree<Traits>::calc_box_for_children(
  NodeRef nd, TreePointCRef c, std::array<Bbox, Degree> &child_boxes)
{
  TreePointCRef minb = nd.box().min_bound();
  TreePointCRef maxb = nd.box().max_bound();

  // clang-format off
  // child 0(000, -x-y-z)
  child_boxes[0] = Bbox(minb, c);
  // child 1(001, +x-y-z)
  child_boxes[1] = Bbox(TreePoint(c.x(), minb.y(), minb.z()), TreePoint(maxb.x(), c.y(), c.z()));
  // child 2(010, -x+y-z)
  child_boxes[2] = Bbox(TreePoint(minb.x(), c.y(), minb.z()), TreePoint(c.x(), maxb.y(), c.z()));
  // child 3(011, +x+y-z)
  child_boxes[3] = Bbox(TreePoint(c.x(), c.y(), minb.z()), TreePoint(maxb.x(), maxb.y(), c.z()));
  // child 4(100, -x-y+z)
  child_boxes[4] = Bbox(TreePoint(minb.x(), minb.y(), c.z()), TreePoint(c.x(), c.y(), maxb.z()));
  // child 5(101, +x-y+z)
  child_boxes[5] = Bbox(TreePoint(c.x(), minb.y(), c.z()), TreePoint(maxb.x(), c.y(), maxb.z()));
  // child 6(110, -x+y+z)
  child_boxes[6] = Bbox(TreePoint(minb.x(), c.y(), c.z()), TreePoint(c.x(), maxb.y(), maxb.z()));
  // child 7(111, +x+y+z)
  child_boxes[7] = Bbox(c, maxb);
  // clang-format on
}

} // namespace OMC