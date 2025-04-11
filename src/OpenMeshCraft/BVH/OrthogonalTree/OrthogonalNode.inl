#pragma once

#include "OrthogonalNode.h"

#include "OpenMeshCraft/Utils/Exception.h"

namespace OMC {

template <typename Traits>
OrthogonalNode_Base<Traits>::OrthogonalNode_Base()
{
  m_parent   = InvalidIndex;
  m_children = InvalidIndex;
  m_depth    = 0;
  m_size     = 0;
  std::fill(m_global_coordinates.begin(), m_global_coordinates.end(), 0);
}

/// @brief Access one child by local index.
template <typename Traits>
auto OrthogonalNode_Base<Traits>::child(index_t index) const -> index_t
{
  OMC_EXPENSIVE_ASSERT(is_valid_idx(m_children), "leaf node has no child.");
  OMC_EXPENSIVE_ASSERT(index < Degree, "index {} out of range.", index);
  return m_children + index;
}

template <typename Traits>
bool OrthogonalNode_Base<Traits>::local_coordinates(size_t axis) const
{
  OMC_EXPENSIVE_ASSERT(axis < Dimension, "invalid axis {}", axis);
  return m_global_coordinates[axis] & gc_t(1);
}

template <typename Traits>
void OrthogonalNode_Base<Traits>::local_coordinates(LocalCoordinates &lc) const
{
  // OPT: cost is expensive.
  if constexpr (Dimension >= 1)
    lc[0] = m_global_coordinates[0] & gc_t(1);
  if constexpr (Dimension >= 2)
    lc[1] = m_global_coordinates[1] & gc_t(1);
  if constexpr (Dimension >= 3)
    lc[2] = m_global_coordinates[2] & gc_t(1);
  if constexpr (Dimension > 3)
    for (size_t i = 3; i < Dimension; i++)
      lc[i] = m_global_coordinates[i] & gc_t(1);
}

template <typename Traits>
auto OrthogonalNode_Base<Traits>::local_coordinates() const -> LocalCoordinates
{
  LocalCoordinates result;
  local_coordinates(result);
  return result;
}

/// @brief Access vertices.
/// There are Degree vertices in Degree subspaces.
/// They can be accessed by local coordinates.
template <typename Traits, typename NodeAttrT>
auto OrthogonalNode_Vtx<Traits, NodeAttrT, /*HasVertex*/ true>::vertex(
  index_t index) -> index_t &
{
  OMC_EXPENSIVE_ASSERT(m_vertices, "Null vertices.");
  OMC_EXPENSIVE_ASSERT(index < Base::Degree, "index {} out of range.", index);
  return m_vertices[index];
}

/// @brief Access vertices.
/// There are Degree vertices in Degree subspaces.
/// They can be accessed by local coordinates.
template <typename Traits, typename NodeAttrT>
auto OrthogonalNode_Vtx<Traits, NodeAttrT, /*HasVertex*/ true>::vertex(
  index_t index) const -> index_t
{
  OMC_EXPENSIVE_ASSERT(m_vertices, "Null vertices.");
  OMC_EXPENSIVE_ASSERT(index < Base::Degree, "index {} out of range.", index);
  return m_vertices[index];
}

} // namespace OMC