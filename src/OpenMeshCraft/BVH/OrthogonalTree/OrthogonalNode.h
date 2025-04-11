#pragma once

#include "OrthogonalTraits.h"
#include "OrthogonalVertex.h"

#include "OpenMeshCraft/Utils/IndexDef.h"

#include <bitset>
#include <vector>

namespace OMC {

/**
 * @brief Node in orthogonal tree.
 * Node maintains a local topology of the tree (parent and children),
 * and provides some functions to modify and traverse the tree's topology.
 * Node also contains geometry information, but never modify it.
 *
 * This base class contains necessary data structure. Optional data are stored
 * optionally in derived class.
 * @tparam Traits
 */
template <typename Traits>
class OrthogonalNode_Base
{
public: /* Types *************************************************************/
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

  /// enable vertices (corner vertices and face vertices).
  static constexpr bool EnableVertices = Traits::EnableVertices;

  static_assert(MaxDepth <= 64);

  /// Geometry information
  using Bbox   = typename Traits::BboxT;
  using OrBbox = typename Traits::OrBboxT;
  OrthTreeAbbreviate(OrBbox);

  /// Abbreviation of OrthogonalNode.
  using Node = OrthogonalNode_Base<Traits>;
  OrthTreeAbbreviate(Node);

  /** @brief Array storing a bundle of children.
   * @details The orthtree subdivides the space in 2 on each axis
   * available, so a child node can be accessed by selecting a Boolean
   * value for each axis. The `index` parameter is thus
   * interpreted as a bitmap, where each bit matches a axis
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

  /**
   * @brief Represent this node's relationship to its parent.
   * LocalCoord[i] indicates whether the i-th dimention of this node is
   * lower (bit=0) or higher (bit=1).
   * @note The local coordinates for root node is all zero.
   */
  using LocalCoordinates = std::bitset<Dimension>;

  /// type used in global coordinates, we expect it to be as small as possible.
  using gc_t = std::conditional_t<MaxDepth <= 32, uint32_t, uint64_t>;
  /**
   * @brief Represent this node's relatioship to the root.
   * The global coordinates store all the local coordinates in the path from
   * root to this node.
   * If n is the depth of this node, LocalCoord_d is the local coordinates
   * at depth d, 0 <= d <= n. The we have:
   *       GlobalCoord[i][n-d] = LocalCoord_d[i].
   * GlobalCoord is well defined when d>=1
   */
  using GlobalCoordinates = std::array<gc_t, Dimension>;

public: /* Constructors (Copy, Move, Assign) and Destructor *******************/
  OrthogonalNode_Base();
  OrthogonalNode_Base(const Node &src) = default;
  OrthogonalNode_Base(Node &&src)      = default;
  NodeRef operator=(const Node &src)   = default;
  NodeRef operator=(Node &&src)        = default;
  ~OrthogonalNode_Base()               = default;

public: /* Queries ************************************************************/
  bool is_root() const { return m_depth == 0; }

  bool is_internal() const { return is_valid_idx(m_children); }

  bool is_leaf() const { return !is_valid_idx(m_children); }

public: /* Data access ********************************************************/
  /// @brief Access parent.
  index_t       &parent() { return m_parent; }
  /// @brief Access parent.
  const index_t &parent() const { return m_parent; }

  /// @brief Access children size
  index_t children_size() const { return Degree; }

  /// @brief Access one child by local index (0 ~ Degree-1).
  index_t child(index_t index) const;

  /// @brief Access children (start index of children)
  index_t       &children() { return m_children; }
  /// @brief Access children (start index of children)
  const index_t &children() const { return m_children; }

  /// @brief Access one vertex by local index  (0 ~ Degree-1).
  index_t       &vertex(index_t index);
  /// @brief Access one vertex by local index  (0 ~ Degree-1).
  const index_t &vertex(index_t index) const;

  index_t       &depth() { return m_depth; }
  const index_t &depth() const { return m_depth; }

  /// @brief Query the local coordinate at specific `axis`.
  bool local_coordinates(size_t axis) const;

  /// @brief Get the local coordinate and store in `lc`.
  void local_coordinates(LocalCoordinates &lc) const;

  /// @brief Get the local coordinate.
  LocalCoordinates local_coordinates() const;

  /// @brief Access global coordinates.
  const GlobalCoordinates &global_coordinates() const
  {
    return m_global_coordinates;
  }
  /// @brief Access global coordinates.
  GlobalCoordinates &global_coordinates() { return m_global_coordinates; }

  /// Access bounding box of this node
  Bbox       &box() { return m_box; }
  const Bbox &box() const { return m_box; }

  /// Access geometry information
  std::vector<OrBboxCPtr>       &boxes() { return m_boxes; }
  const std::vector<OrBboxCPtr> &boxes() const { return m_boxes; }

  /// Access size
  size_t       &size() { return m_size; }
  const size_t &size() const { return m_size; }

protected: /* Data ************************************************************/
  /// index of parent, InvalidIndex if parent doesn't exist.
  index_t                 m_parent;
  /// children of this node.
  Children                m_children;
  /// global coordinates of this node.
  GlobalCoordinates       m_global_coordinates;
  /// start from 0 (Root), end with MaxDepth.
  index_t                 m_depth;
  /// box of this node
  Bbox                    m_box;
  /// boxes interseted with this node.
  std::vector<OrBboxCPtr> m_boxes;
  /// size of all boxes stored in this node (including children).
  size_t                  m_size;
};

/**
 * @brief This derived class is used to optionally store node attributes.
 *
 * @tparam Traits
 * @tparam NodeAttr Node attribute type.
 */
template <typename Traits, typename NodeAttr>
class OrthogonalNode_Attr : public OrthogonalNode_Base<Traits>
{
public: /* Types *************************************************************/
  /// Attribute type defined on node.
  using NodeAttrT = typename Traits::NodeAttrT;

public: /* Data access *******************************************************/
  /// Access node attribute
  NodeAttrT       &attribute() { return m_attribute; }
  const NodeAttrT &attribute() const { return m_attribute; }

protected: /* Data ************************************************************/
  /// attribute
  NodeAttrT m_attribute;
};

template <typename Traits>
class OrthogonalNode_Attr<Traits, void> : public OrthogonalNode_Base<Traits>
{
  /* No member or interfaces */
};

/**
 * @brief This derived class is used to optionally store vertices.
 *
 * @tparam Traits
 * @tparam NodeAttr
 * @tparam Vertex
 */
template <typename Traits, typename NodeAttr, bool HasVertex>
class OrthogonalNode_Vtx;

template <typename Traits, typename NodeAttr>
class OrthogonalNode_Vtx<Traits, NodeAttr, /*HasVertex=*/true>
  : public OrthogonalNode_Attr<Traits, NodeAttr>
{
public:
  /// Base class
  using Base = OrthogonalNode_Attr<Traits, NodeAttr>;

  /**
   * @brief Array storing corner vertices of this node.
   * A node has and only has Degree corner vertices.
   * @note A node hold a vertex, but the vertex may not be adjacent to the node.
   * For example in 2D, the big cell holds 4 corner vertices (marked in `c`),
   * but all 4 corner vertices are adjacent to small cells.
   *          c-------f-------c
   *          |       |       |
   *          |       |       |
   *          |       |       |
   *          f-------+-------f
   *          |       |       |
   *          |       |       |
   *          |       |       |
   *          c-------f-------c
   */
  using VertexIds = std::array<index_t, Base::Degree>;

public:
  /// @brief Access vertex.
  index_t         &vertex(index_t index);
  /// @brief Access vertex.
  index_t          vertex(index_t index) const;
  /// @brief Access vertices.
  VertexIds       &vertices() { return m_vertices; }
  /// @brief Access vertices.
  const VertexIds &vertices() const { return m_vertices; }

protected: /* Data ************************************************************/
  /// vertices of this node.
  VertexIds m_vertices;
};

template <typename Traits, typename NodeAttr>
class OrthogonalNode_Vtx<Traits, NodeAttr, /*HasVertex=*/false>
  : public OrthogonalNode_Attr<Traits, NodeAttr>
{
  // no member or interfaces
};

template <typename Traits, typename NodeAttr, bool HasVertex>
using OrthogonalNode = OrthogonalNode_Vtx<Traits, NodeAttr, HasVertex>;

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "OrthogonalNode.inl"
#endif