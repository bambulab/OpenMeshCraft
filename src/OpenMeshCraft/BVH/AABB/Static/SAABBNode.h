#pragma once

#include "OpenMeshCraft/Utils/IndexDef.h"

namespace OMC {

/**
 * @brief Define node of static AABB tree.
 * @tparam BboxT The bounding box type used in internal nodes.
 */
template <typename BboxT>
class SAABBNode
{
public:
  using NodeT = SAABBNode<BboxT>;

public:
  SAABBNode()
    : m_bbox()
    , m_left_child(InvalidIndex)
    , m_right_child(InvalidIndex)
  {
  }

  ~SAABBNode() {}

  BboxT       &bbox() { return m_bbox; }
  const BboxT &bbox() const { return m_bbox; }

  index_t &left_child() { return m_left_child; }
  index_t  left_child() const { return m_left_child; }
  index_t &right_child() { return m_right_child; }
  index_t  right_child() const { return m_right_child; }

private:
  BboxT   m_bbox;
  index_t m_left_child, m_right_child;
};

} // namespace OMC
