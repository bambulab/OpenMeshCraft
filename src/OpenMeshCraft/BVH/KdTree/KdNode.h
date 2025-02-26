#pragma once

namespace OMC {

/**
 * @brief Base node type for internal node and leaf node in the k-d tree.
 */
template <typename KdTraits>
class KdNode
{
public:
	KdNode() = delete;

	KdNode(bool leaf)
	  : m_is_leaf(leaf)
	{
	}

public:
	bool m_is_leaf;
};

/**
 * @class KdInternalNode
 * @brief Represents an internal node in a k-d tree.
 * @tparam KdTraits Traits class that numeric types used in the k-d tree.
 */
template <typename KdTraits>
class KdInternalNode : public KdNode<KdTraits>
{
public:
	using NT      = typename KdTraits::NT;
	using Node    = KdNode<KdTraits>;
	using NodePtr = Node *;

public:
	KdInternalNode()
	  : Node(false)
	{
	}

	inline void set_separator(size_t cut_axis, NT cut_val)
	{
		m_cut_axis = cut_axis;
		m_cut_val  = cut_val;
	}

public:
	/// The axis along which the node splits the data.
	size_t  m_cut_axis;
	/// The value at which the node splits the data along the cut axis.
	NT      m_cut_val;
	/// Additional values for managing the range of data in child nodes.
	NT      m_lower_low_val, m_lower_high_val, m_upper_low_val, m_upper_high_val;
	/// Pointers to the lower and upper child nodes.
	NodePtr m_lower_ch, m_upper_ch;
};

/**
 * @class KdLeafNode
 * @brief A class representing a leaf node in a k-d tree.
 * @tparam KdTraits Traits class that numeric types used in the k-d tree.
 */
template <typename KdTraits>
class KdLeafNode : public KdNode<KdTraits>
{
public:
	using NT           = typename KdTraits::NT;
	using Node         = KdNode<KdTraits>;
	using KdPointsIter = typename KdTraits::KdPointsIter;

public:
	KdLeafNode()
	  : Node(true)
	{
	}

	KdLeafNode(size_t n)
	  : Node(true)
	  , n(n)
	{
	}

public:
	/// The number of points in the leaf node.
	size_t       n;
	/// An iterator to the data points in the leaf node.
	KdPointsIter data;
};

} // namespace OMC