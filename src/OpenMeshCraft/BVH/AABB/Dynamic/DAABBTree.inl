#pragma once

#include "DAABBTree.h"

#include "OpenMeshCraft/Utils/Exception.h"

#include <numeric>

namespace OMC {

template <typename Traits>
template <typename PrimsIterT, typename IndicesIter>
void DAABBTree<Traits>::insert(PrimsIterT pfirst, PrimsIterT pbeyond,
                               IndicesIter ifirst, IndicesIter ibeyond)
{
	OMC_ASSERT(std::distance(pfirst, pbeyond) == std::distance(ifirst, ibeyond),
	           "The number of primitives and indices must be equal.");

	m_primitives.reserve(m_primitives.size() + std::distance(pfirst, pbeyond));
	m_ex_map2_in.reserve(m_ex_map2_in.size() + std::distance(pfirst, pbeyond));
	m_in_map2_ex.resize(m_in_map2_ex.size() + std::distance(pfirst, pbeyond));

	for (; pfirst != pbeyond; pfirst++, ifirst++)
	{
		connect(*ifirst, m_primitives.size());
		m_primitives.push_back(*pfirst);
	}

	m_primitive_map2_node.resize(m_primitives.size());
	m_primitive_deleted.resize(m_primitives.size(), false);
}

template <typename Traits>
void DAABBTree<Traits>::build()
{
	if (m_primitives.empty())
		return;
	m_nodes.clear();
	m_node_deleted.clear();
	m_primitive_map2_node.clear();
	m_nodes.reserve(m_primitives.size() * 2);
	m_node_deleted.reserve(m_primitives.size() * 2);
	m_primitive_map2_node.resize(m_primitives.size(), InvalidIndex);

	std::vector<index_t> ids(m_primitives.size());
	std::iota(ids.begin(), ids.end(), 0);
	expand(ids.begin(), ids.end(), /*parent_idx*/ InvalidIndex);
}

template <typename Traits>
void DAABBTree<Traits>::clear()
{
	m_primitives.clear();
	m_nodes.clear();

	m_ex_map2_in.clear();
	m_in_map2_ex.clear();

	m_primitive_map2_node.clear();

	m_primitive_deleted.clear();
	m_node_deleted.clear();
}

template <typename Traits>
void DAABBTree<Traits>::insert(const PrimT &prim, index_t ex_prim_idx)
{
	index_t in_prim_idx = insert_a_primitive(prim);
	connect(ex_prim_idx, in_prim_idx);

	BboxT bbox = CalcBbox()(prim);

	switch (m_primitives.size())
	{
	case 1: // only one just added primitive, no node exists.
	{
		using iterator                 = std::array<index_t, 1>::iterator;
		std::array<index_t, 1> indices = {in_prim_idx};
		expand(indices.begin(), indices.end(), /*parent_idx*/ InvalidIndex);
	}
	break;
	default:
	{
		insert_to_node(in_prim_idx, bbox, /*node_idx*/ 0);
	}
	break;
	}
}

template <typename Traits>
void DAABBTree<Traits>::remove(index_t ex_prim_idx)
{
	OMC_EXPENSIVE_ASSERT(prim_exists(ex_prim_idx), "Non-existant primitive.");
	index_t in_prim_idx = ex2in(ex_prim_idx);

	// mark the primitive as deleted, it will be removed when collecting garbage.
	pdeleted(in_prim_idx) = true;
	// now remove it from tree (leaf node).
	remove_from_leaf_node(in_prim_idx);
	// reset mapping between internal and external indices
	in2ex(in_prim_idx) = InvalidIndex;
	m_ex_map2_in.erase(ex_prim_idx);
}

template <typename Traits>
void DAABBTree<Traits>::update(index_t ex_prim_idx, const PrimT &new_prim)
{
	OMC_EXPENSIVE_ASSERT(prim_exists(ex_prim_idx), "Non-existant primitive.");
	index_t in_prim_idx = ex2in(ex_prim_idx);

	PrimT &p = primitive(in_prim_idx);
	NodeT &n = node(in2nd(in_prim_idx));
	OMC_EXPENSIVE_ASSERT(n.m_left_child == in_prim_idx, "in2nd error.");
	p        = new_prim;
	n.m_bbox = CalcBbox()(p);
	update_node_box(n.m_parent);
}

template <typename Traits>
void DAABBTree<Traits>::split(index_t ex_prim_idx, index_t ex_subp0_idx,
                              const PrimT &subprim0, index_t ex_subp1_idx,
                              const PrimT &subprim1)
{
	OMC_EXPENSIVE_ASSERT(prim_exists(ex_prim_idx), "Non-existant primitive.");
	index_t in_prim_idx = ex2in(ex_prim_idx);

	index_t in_subp0_idx = insert_a_primitive(subprim0);
	index_t in_subp1_idx = insert_a_primitive(subprim1);
	connect(ex_subp0_idx, in_subp0_idx);
	connect(ex_subp1_idx, in_subp1_idx);

	split_node(in2nd(in_prim_idx), in_subp0_idx, in_subp1_idx);
	pdeleted(in_prim_idx) = true;
}

template <typename Traits>
void DAABBTree<Traits>::collect_garbage()
{
	{ // remove deleted primitives
		// `front` and `back` are internal primitive indices
		index_t front = 0;
		index_t back  = m_primitive_deleted.size() - 1;

		while (true)
		{
			// find the first deleted and last undeleted primitive
			while (!pdeleted(front) && front < back)
				++front;
			while (pdeleted(back) && front < back)
				--back;
			if (front >= back)
				break;

			// swap deleted status of front and back
			std::swap(pdeleted(front), pdeleted(back));

			// overwrite the deleted primitive with the undeleted primitive
			primitive(front) = primitive(back);

			// update the mapping between ex and in
			connect(in2ex(back), front);

			// It is unnecessary to update the mapping between in and node
			// because we rebuild the tree finally.
			// in2nd(front) = in2nd(back);
			// node(in2nd(front)).m_left_child = front;
		}
		m_primitives.resize(pdeleted(front) ? (front) : (front + 1));
		m_in_map2_ex.resize(m_primitives.size());
		m_primitive_map2_node.resize(m_primitives.size());
		m_primitive_deleted.resize(m_primitives.size());
	}

	build();
}

template <typename Traits>
template <typename TraversalTrait>
void DAABBTree<Traits>::traverse(TraversalTrait &trait) const
{
	if (m_primitives.empty())
		return;
	else if (m_primitives.size() == 1)
		trait.intersection(primitive(0), in2ex(0));
	else                       // m_primitives.size() > 1
		traverse_node(trait, 0); // root node's index is always 0.
}

template <typename Traits>
template <typename TraversalTrait>
bool DAABBTree<Traits>::traverse_node(TraversalTrait &trait,
                                      index_t         node_idx) const
{
	// trait.intersection will check intersection with primitive.
	// trait.do_inter will check intersection with box.
	bool         go_next = true;
	const NodeT &n       = node(node_idx);
	switch (n.m_nb_primitives)
	{
	case 1:
		return trait.intersection(primitive(n.m_left_child), in2ex(n.m_left_child));
	default:
		if (trait.do_inter(node(n.m_left_child).m_bbox))
		{
			go_next = traverse_node(trait, n.m_left_child);
			if (go_next && trait.do_inter(node(n.m_right_child).m_bbox))
				go_next = traverse_node(trait, n.m_right_child);
			return go_next;
		}
		else if (trait.do_inter(node(n.m_right_child).m_bbox))
		{
			return traverse_node(trait, n.m_right_child);
		}
		return true;
	}
}

template <typename Traits>
void DAABBTree<Traits>::connect(index_t ex_prim_idx, index_t in_prim_idx)
{
	ex2in(ex_prim_idx) = in_prim_idx;
	in2ex(in_prim_idx) = ex_prim_idx;
}

template <typename Traits>
template <typename IndicesIter>
auto DAABBTree<Traits>::calc_bbox(IndicesIter first, IndicesIter beyond)
  -> BboxT
{
	BboxT bbox = CalcBbox()(primitive(*first));
	for (++first; first != beyond; ++first)
		bbox += CalcBbox()(primitive(*first));
	return bbox;
}

template <typename Traits>
template <typename IndicesIter>
int DAABBTree<Traits>::split_primitives(IndicesIter first, IndicesIter beyond,
                                        IndicesIter &middle, const BboxT &box)
{
	size_t split_axis = SplitPrims()(this, first, beyond, middle, box);
	return static_cast<int>(split_axis);
}

template <typename Traits>
template <typename IndicesIter>
index_t DAABBTree<Traits>::expand(IndicesIter first, IndicesIter beyond,
                                  index_t parent_idx)
{
	index_t     node_idx = create_a_node();
	NodeT      &n        = node(node_idx);
	IndicesIter middle;

	n.m_parent        = parent_idx;
	n.m_nb_primitives = std::distance(first, beyond);
	n.m_bbox          = calc_bbox(first, beyond);
	n.m_split_axis    = split_primitives(first, beyond, middle, n.m_bbox);

	switch (n.m_nb_primitives)
	{
	case 0:
		OMC_ASSERT(false, "Expand a DAABB node without child.");
		break;
	case 1:
		n.m_left_child  = *first;
		n.m_right_child = InvalidIndex;
		in2nd(*first)   = node_idx;
		break;
	default:
		node(node_idx).m_left_child  = expand(first, middle, node_idx);
		node(node_idx).m_right_child = expand(middle, beyond, node_idx);
		break;
	}
	return node_idx;
}

template <typename Traits>
index_t DAABBTree<Traits>::insert_a_primitive(const PrimT &prim)
{
	m_primitives.push_back(prim);
	m_in_map2_ex.push_back(InvalidIndex);
	m_primitive_map2_node.push_back(InvalidIndex);
	m_primitive_deleted.push_back(false);
	return m_primitives.size() - 1;
}

template <typename Traits>
index_t DAABBTree<Traits>::create_a_node()
{
	m_nodes.emplace_back();
	m_node_deleted.push_back(false);
	return m_nodes.size() - 1;
}

template <typename Traits>
void DAABBTree<Traits>::insert_to_node(index_t in_prim_idx, BboxT &prim_box,
                                       index_t node_idx)
{
	NodeT &n = node(node_idx);
	n.m_nb_primitives += 1;
	// n.m_parent unchanged.
	switch (n.m_nb_primitives)
	{
	case 2:
	{
		using iterator                 = std::array<index_t, 2>::iterator;
		std::array<index_t, 2> indices = {n.m_left_child, in_prim_idx};
		iterator first = indices.begin(), beyond = indices.end(), middle;

		n.m_bbox += prim_box;
		n.m_split_axis = split_primitives(first, beyond, middle, n.m_bbox);

		node(node_idx).m_left_child  = expand(first, middle, node_idx);
		node(node_idx).m_right_child = expand(middle, beyond, node_idx);
	}
	break;
	default:
	{
		NodeT &lnode = node(n.m_left_child);
		NodeT &rnode = node(n.m_right_child);

		n.m_bbox += prim_box;
		size_t sd         = n.m_split_axis;
		auto   left_max   = lnode.m_bbox.max_coord(sd);
		auto   right_min  = rnode.m_bbox.min_coord(sd);
		auto   insert_min = prim_box.min_coord(sd);
		auto   insert_max = prim_box.max_coord(sd);

		if (insert_max <= right_min)
			insert_to_node(in_prim_idx, prim_box, n.m_left_child);
		else if (insert_min >= left_max)
			insert_to_node(in_prim_idx, prim_box, n.m_right_child);
		else
		{
			// choose a branch that makes tree more balance.
			if (lnode.m_nb_primitives > rnode.m_nb_primitives)
				insert_to_node(in_prim_idx, prim_box, n.m_right_child);
			else
				insert_to_node(in_prim_idx, prim_box, n.m_left_child);
		}
	}
	break;
	}
}

template <typename Traits>
void DAABBTree<Traits>::remove_from_leaf_node(index_t in_prim_idx)
{
	index_t node_idx = in2nd(in_prim_idx);
	NodeT  &n        = node(node_idx);

	OMC_EXPENSIVE_ASSERT(n.is_leaf() && n.m_left_child == in_prim_idx,
	                     "remove a primitive from non-leaf node or mismatch.");

	// remove primitive from the leaf node
	n.m_left_child    = InvalidIndex;
	n.m_nb_primitives = 0;

	// decrease nb_primitive in ancestors
	index_t parent_idx = n.m_parent;
	while (is_valid_idx(parent_idx))
	{
		node(parent_idx).m_nb_primitives -= 1;
		parent_idx = node(parent_idx).m_parent;
	}

	// remove node due to nb_primitives == 0
	remove_node(node_idx);
	in2nd(in_prim_idx) = InvalidIndex;
}

template <typename Traits>
void DAABBTree<Traits>::remove_node(index_t node_idx)
{
	OMC_EXPENSIVE_ASSERT(node(node_idx).m_nb_primitives == 0,
	                     "remove a non-empty node.");
	m_node_deleted[node_idx] = true;
	// remove node from its parent. move its sibling up.
	NodeT  &n                = node(node_idx);
	index_t parent_idx       = n.m_parent;
	n.clear();
	if (is_valid_idx(parent_idx))
	{
		NodeT &parent_node = node(parent_idx);
		if (parent_node.m_left_child == node_idx)
		{
			parent_node.m_left_child = InvalidIndex;
			moveup_node(parent_node.m_right_child);
		}
		else
		{
			parent_node.m_right_child = InvalidIndex;
			moveup_node(parent_node.m_left_child);
		}
	}
}

template <typename Traits>
void DAABBTree<Traits>::moveup_node(index_t node_idx)
{
	OMC_EXPENSIVE_ASSERT(is_valid_idx(node(node_idx).m_parent),
	                     "Can't move up root.");

	NodeT  &n            = node(node_idx);
	index_t parent_idx   = n.m_parent;
	NodeT  &parent_node  = node(parent_idx);
	index_t grandpa_idx  = parent_node.m_parent;
	// overwrite the parent node with current node.
	parent_node          = n;
	parent_node.m_parent = grandpa_idx;
	// clear current node and remove it.
	n.clear();
	m_node_deleted[node_idx] = true;

	// reconnect nodes and primitives
	if (parent_node.m_nb_primitives >= 2)
	{ // has child nodes, update parent in child nodes.
		node(parent_node.m_left_child).m_parent  = parent_idx;
		node(parent_node.m_right_child).m_parent = parent_idx;
	}
	else if (parent_node.m_nb_primitives == 1)
	{ // has primitive, map the primitive to the node.
		in2nd(parent_node.m_left_child) = parent_idx;
	}
	// update bounding box of nodes
	update_node_box(grandpa_idx);
}

template <typename Traits>
void DAABBTree<Traits>::update_node_box(index_t node_idx)
{
	OMC_EXPENSIVE_ASSERT(is_valid_idx(node_idx) && node_idx < m_nodes.size() &&
	                       !ndeleted(node_idx),
	                     "update a non-existant or deleted node.");

	NodeT &cur_node = node(node_idx);
	BboxT  new_box =
	  node(cur_node.m_left_child).m_bbox + node(cur_node.m_right_child).m_bbox;
	if (!(cur_node.m_bbox == new_box))
	{
		cur_node.m_bbox = new_box;
		if (is_valid_idx(cur_node.m_parent))
			update_node_box(cur_node.m_parent);
	}
}

template <typename Traits>
void DAABBTree<Traits>::split_node(index_t node_idx, index_t subprim0_idx,
                                   index_t subprim1_idx)
{
	NodeT &n = node(node_idx);

	OMC_EXPENSIVE_ASSERT(n.is_leaf(), "split a non-leaf node.");

	n.m_nb_primitives = 2;
	// n.m_parent unchanged.

	using iterator                 = std::array<index_t, 2>::iterator;
	std::array<index_t, 2> indices = {subprim0_idx, subprim1_idx};
	iterator first = indices.begin(), beyond = indices.end(), middle;

	n.m_bbox       = calc_bbox(first, beyond);
	n.m_split_axis = split_primitives(first, beyond, middle, n.m_bbox);

	node(node_idx).m_left_child  = expand(first, middle, node_idx);
	node(node_idx).m_right_child = expand(middle, beyond, node_idx);
	update_node_box(node(node_idx).m_parent);
}

} // namespace OMC