#pragma once

#include "OpenMeshCraft/Utils/IndexDef.h"

namespace OMC {

/**
 * @brief Define node of AABB tree.
 * @tparam PrimT The geometry primitive type stored in leaf nodes.
 * @tparam BboxT The bounding box type used in internal nodes.
 */
template <typename PrimT, typename BboxT>
class DAABBNode
{
public: /* Types ***********************************************************/
	using NodeT = DAABBNode<PrimT, BboxT>;

public: /* Constructor and Destructor **************************************/
	DAABBNode()
	  : m_bbox()
	  , m_nb_primitives(0)
	  , m_parent(InvalidIndex)
	  , m_left_child(InvalidIndex)
	  , m_right_child(InvalidIndex)
	  , m_split_axis(InvalidIndex)
	{
	}

	~DAABBNode() {}

	void clear()
	{
		m_nb_primitives = 0;
		m_parent        = InvalidIndex;
		m_left_child    = InvalidIndex;
		m_right_child   = InvalidIndex;
		m_split_axis    = InvalidIndex;
	}

	bool is_leaf() const { return m_nb_primitives == 1; }
	bool is_internal() const { return !is_leaf(); }

public: /* Data ************************************************************/
	/// Bounding box of the node.
	BboxT   m_bbox;
	/// Number of primitives in the node.
	size_t  m_nb_primitives;
	/// Index of the parent node.
	index_t m_parent;
	/// Index of the left child.
	/// If this node is a leaf, it is the index of the primitive.
	index_t m_left_child;
	/// Index of the right child.
	index_t m_right_child;
	/// Split axis of the node.
	size_t  m_split_axis;
};

} // namespace OMC