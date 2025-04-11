#pragma once

#include "AdapOrthTraits.h"

#include "OpenMeshCraft/Utils/Exception.h"

#include <array>
#include <vector>

namespace OMC {

/**
 * @brief Node in adaptive orthogonal tree.
 * Node maintains a local topology of the tree (parent and children).
 * Node also contains geometry information, but never modify it.
 * @tparam Traits
 */
template <typename Traits>
class AdapOrthNode_Base
{
public:
  /// The maximal depth of orthogonal tree.
  /// Root node is at depth 0.
  /// For example, when MaxDepth is 1, the tree is allowed to have a root node
  /// (at depth 0) and root node's children (at depth 1). Deeper nodes are not
  /// allowd to exist in the tree.
  static constexpr size_t MaxDepth = Traits::MaxDepth;

  /// Dimension, typically 2 or 3, or higher n
  static constexpr size_t Dimension = Traits::Dimension;

  /// size of children, typically 4 or 8, or higher 2^n.
  static constexpr size_t Degree = (1u << Dimension);

  static_assert(MaxDepth <= 64);

  /// Geometry information
  using Bbox     = typename Traits::BboxT;
  using TreeBbox = typename Traits::TreeBboxT;
  AdapOrthTreeAbbreviate(TreeBbox);

  /// Abbreviation of AdapOrthNode.
  using Node = AdapOrthNode_Base<Traits>;
  AdapOrthTreeAbbreviate(Node);

  /** @brief Array storing a bundle of children.
   * @details The orthtree subdivides the space in 2 on each axis
   * available, so a child node can be accessed by selecting a Boolean
   * value for each axis. The `index` parameter is thus
   * interpreted as a bitmap, where each bit matches an axis
   * (starting by the least significant bit for coordinate X).
   *
   * For example, in the case of an octree (dimension 3):
   *
   * - index 0 (000 in binary) is the children on the "minimum corner" (xmin,
   * ymin, zmin)
   * - index 1 (001 in binary) is on (xmax, ymin, zmin)
   * - index 2 (010 in binary) is on (xmin, ymax, zmin)
   * - index 6 (101 in binary) is on (xmax, ymin, zmax)
   * @note When splitting a node, allocate children in bundle, not one by one.
   * @note We only use a pointer to represent children, we guarantee that
   * children are sequantial in memory. It is almost equivalent to
   *      using Children = std::array<NodePtr, Degree>;
   */
  using Children = index_t;

public: /* Constructors (Copy, Move, Assign) and Destructor */
  AdapOrthNode_Base()
  {
    m_parent        = InvalidIndex;
    m_children      = InvalidIndex;
    m_children_size = 0;
    m_depth         = 0;
    m_size          = 0;

    std::fill(m_child_map.begin(), m_child_map.end(), InvalidIndex);
  }

  void shallow_copy(NodeCRef rhs)
  {
    m_parent        = rhs.m_parent;
    m_children      = rhs.m_children;
    m_children_size = rhs.m_children_size;
    m_depth         = rhs.m_depth;
    m_box           = rhs.m_box;
    m_tbox          = rhs.m_tbox;
    m_size          = 0;
    m_child_map     = rhs.m_child_map;
  }

  void clear_boxes() { m_boxes = std::vector<index_t>(); }

public: /* Queries */
  bool is_root() const { return m_depth == 0; }

  bool is_internal() const { return is_valid_idx(m_children); }

  bool is_leaf() const { return !is_valid_idx(m_children); }

public: /* Data access */
  /// @brief Access parent.
  index_t       &parent() { return m_parent; }
  /// @brief Access parent.
  const index_t &parent() const { return m_parent; }

  /// @brief Access one child by local index (0 ~ Degree-1).
  index_t child(index_t index) const
  {
    OMC_EXPENSIVE_ASSERT(is_valid_idx(m_children), "leaf node has no child.");
    OMC_EXPENSIVE_ASSERT(index < children_size(), "index {} out of range.",
                         index);
    return m_children + index;
  }

  /// @brief Access children (start index of children)
  index_t       &children() { return m_children; }
  /// @brief Access children (start index of children)
  const index_t &children() const { return m_children; }

  /// @brief Access children size
  size_t       &children_size() { return m_children_size; }
  /// @brief Access children size
  const size_t &children_size() const { return m_children_size; }

  index_t       &depth() { return m_depth; }
  const index_t &depth() const { return m_depth; }

  /// Access loose bounding box of this node
  Bbox       &box() { return m_box; }
  const Bbox &box() const { return m_box; }

  /// Access tight bounding box of this node
  Bbox       &tbox() { return m_tbox; }
  const Bbox &tbox() const { return m_tbox; }

  /// Access geometry information
  std::vector<index_t>       &boxes() { return m_boxes; }
  const std::vector<index_t> &boxes() const { return m_boxes; }

  /// Access size
  size_t       &size() { return m_size; }
  const size_t &size() const { return m_size; }

  /// children map
  const std::array<index_t, Degree> &child_map() const { return m_child_map; }
  std::array<index_t, Degree>       &child_map() { return m_child_map; }

protected:
  /// index of parent, InvalidIndex if parent doesn't exist.
  index_t                     m_parent;
  /// children of this node.
  Children                    m_children;
  size_t                      m_children_size;
  /// start from 0 (Root), end with MaxDepth.
  index_t                     m_depth;
  /// loose box of this node
  Bbox                        m_box;
  /// tight box of this node
  Bbox                        m_tbox;
  /// boxes interseted with this node.
  std::vector<index_t>        m_boxes;
  /// size of all boxes stored in this node (including children).
  size_t                      m_size;
  /// Map children to all corners
  std::array<index_t, Degree> m_child_map;
};

template <typename Traits, typename NodeAttrT>
class AdapOrthNode : public AdapOrthNode_Base<Traits>
{
public:
  /// Access node attribute
  NodeAttrT       &attribute() { return m_attribute; }
  const NodeAttrT &attribute() const { return m_attribute; }

protected:
  /// attribute
  NodeAttrT m_attribute;
};

template <typename Traits>
class AdapOrthNode<Traits, void> : public AdapOrthNode_Base<Traits>
{
  // empty attribute
};

} // namespace OMC