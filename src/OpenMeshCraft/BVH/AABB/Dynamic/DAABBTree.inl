#pragma once

#include "DAABBTree.h"

#include "OpenMeshCraft/Utils/Exception.h"

#include <numeric>

namespace OMC {

template <typename Traits>
template <typename PrimsIterT>
DAABBTree<Traits>::DAABBTree(PrimsIterT first, PrimsIterT beyond)
{
	insert(first, beyond);
	build();
}

template <typename Traits>
DAABBTree<Traits>::DAABBTree(Prims &&primitives)
{
	insert(primitives);
	build();
}

template <typename Traits>
void DAABBTree<Traits>::insert(Prims &&primitives)
{
	clear();
	m_primitives = std::move(primitives);
	m_primitive_map2_node.resize(m_primitives.size());
	m_primitive_deleted.resize(m_primitives.size(), false);
}

template <typename Traits>
template <typename PrimsIterT>
void DAABBTree<Traits>::insert(PrimsIterT first, PrimsIterT beyond)
{
	clear();
	m_primitives.reserve(std::distance(first, beyond));
	m_primitives.insert(m_primitives.end(), first, beyond);
	m_primitive_map2_node.resize(m_primitives.size());
	m_primitive_deleted.resize(m_primitives.size(), false);
}

template <typename Traits>
void DAABBTree<Traits>::build()
{
	if (m_primitives.empty())
		return;
	m_nodes.reserve(m_primitives.size() * 2);
	m_node_deleted.reserve(m_primitives.size() * 2);

	Indices ids(m_primitives.size());
	std::iota(ids.begin(), ids.end(), 0);
	expand(ids.begin(), ids.end(), /*parent_idx*/ InvalidIndex);
}

template <typename Traits>
void DAABBTree<Traits>::rebuild()
{
	m_nodes.clear();
	m_node_deleted.clear();
	build();
}

template <typename Traits>
void DAABBTree<Traits>::clear()
{
	m_primitives.clear();
	m_nodes.clear();

	m_primitive_map2_node.clear();

	m_primitive_deleted.clear();
	m_node_deleted.clear();
}

template <typename Traits>
void DAABBTree<Traits>::insert(const PrimT &prim)
{
	index_t prim_idx = insert_a_primitive(prim);
	BboxT   bbox     = CalcBbox()(prim);

	switch (m_primitives.size())
	{
	case 1: // only one just added primitive, no node exists.
	{
		index_t node_idx  = create_a_node();
		NodeT  &n         = node(node_idx);
		n.m_bbox          = bbox;
		n.m_nb_primitives = 1;
		n.m_parent        = InvalidIndex;
		n.m_left_child    = prim_idx;
		n.m_right_child   = InvalidIndex;
	}
	break;
	default:
	{
		insert_to_node(prim_idx, bbox, 0);
	}
	break;
	}
}

template <typename Traits>
void DAABBTree<Traits>::remove(index_t prim_idx)
{
	OMC_EXPENSIVE_ASSERT(is_valid_idx(prim_idx) &&
	                       prim_idx < m_primitives.size() &&
	                       !m_primitive_deleted[prim_idx],
	                     "remove a non-existant or deleted primitive.");

	// mark the primitive as deleted, it will be removed when collecting garbage.
	m_primitive_deleted[prim_idx] = true;

	// now remove it from tree (leaf node).
	remove_from_node(prim_idx, mapto(prim_idx));
}

template <typename Traits>
void DAABBTree<Traits>::update(index_t prim_idx, const PrimT &new_prim)
{
	OMC_EXPENSIVE_ASSERT(is_valid_idx(prim_idx) &&
	                       prim_idx < m_primitives.size() &&
	                       !m_primitive_deleted[prim_idx],
	                     "update a non-existant or deleted primitive.");

	PrimT &p = primitive(prim_idx);
	NodeT &n = node(mapto(prim_idx));
	OMC_EXPENSIVE_ASSERT(n.m_left_child == prim_idx, "mapto error.");
	p        = new_prim;
	n.m_bbox = CalcBbox()(p);
	update_node(n.m_parent);
}

template <typename Traits>
void DAABBTree<Traits>::split(index_t prim_idx, const PrimT &subprim0,
                              const PrimT &subprim1)
{
	OMC_EXPENSIVE_ASSERT(is_valid_idx(prim_idx) &&
	                       prim_idx < m_primitives.size() &&
	                       !m_primitive_deleted[prim_idx],
	                     "split a non-existant or non-leaf node.");

	index_t subprim0_idx = insert_a_primitive(subprim0);
	index_t subprim1_idx = insert_a_primitive(subprim1);

	split_node(mapto(prim_idx), subprim0_idx, subprim1_idx);
}

template <typename Traits>
void DAABBTree<Traits>::collect_garbage()
{
	{ // remove deleted primitives
		index_t front = 0;
		index_t back  = m_primitive_deleted.size() - 1;

		while (true)
		{
			// find the first deleted and last undeleted primitive
			while (!m_primitive_deleted[front] && front < back)
				++front;
			while (m_primitive_deleted[back] && front < back)
				--back;
			if (front >= back)
				break;

			// swap front and back
			std::swap(m_primitive_deleted[front], m_primitive_deleted[back]);
			primitive(front) = primitive(back);
			mapto(front)     = mapto(back);
			NodeT &pn        = node(mapto(back));
			pn.m_left_child  = front;
		}
		m_primitives.resize(m_primitive_deleted[front] ? front : front + 1);
		m_primitive_map2_node.resize(m_primitives.size());
		m_primitive_deleted.resize(m_primitives.size());
	}

#if 1
	rebuild();
#else
	{ // remove deleted nodes
		index_t front = 0;
		index_t back  = m_node_deleted.size() - 1;

		while (true)
		{
			// find 1st deleted and last un-deleted
			while (!m_node_deleted[front] && front < back)
				++front;
			while (m_node_deleted[back] && front < back)
				--back;
			if (front >= back)
				break;

			// swap front and back
			std::swap(m_node_deleted[front], m_node_deleted[back]);
			swap_node(front, back);
		}
		m_nodes.resize(m_node_deleted[front] ? front : front + 1);
		m_node_deleted.resize(m_nodes.size());
	}
#endif
}

template <typename Traits>
template <typename TraversalTrait>
void DAABBTree<Traits>::traverse(TraversalTrait &trait) const
{
	if (m_primitives.empty())
		return;
	else if (m_primitives.size() == 1)
		trait.intersection(primitive(0));
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
		return trait.intersection(primitive(n.m_left_child));
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
	index_t node_idx = create_a_node();
	NodeT  &n        = node(node_idx);

	n.m_parent        = parent_idx;
	n.m_nb_primitives = std::distance(first, beyond);

	n.m_bbox = calc_bbox(first, beyond);

	IndicesIter middle;
	n.m_split_axis = split_primitives(first, beyond, middle, n.m_bbox);

	switch (n.m_nb_primitives)
	{
	case 0:
		OMC_ASSERT(false, "Expand a DAABB node without child.");
		break;
	case 1:
		n.m_left_child  = *first;
		n.m_right_child = InvalidIndex;
		mapto(*first)   = node_idx;
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
	m_primitive_deleted.push_back(false);
	m_primitive_map2_node.emplace_back();
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
void DAABBTree<Traits>::insert_to_node(index_t prim_idx, BboxT &prim_box,
                                       index_t node_idx)
{
	NodeT &n = node(node_idx);
	n.m_nb_primitives += 1;
	switch (n.m_nb_primitives)
	{
	case 2:
	{
		using iterator                 = std::array<index_t, 2>::iterator;
		std::array<index_t, 2> indices = {n.m_left_child, prim_idx};

		iterator first = indices.begin(), beyond = indices.end(), middle;
		n.m_bbox       = calc_bbox(first, beyond);
		n.m_split_axis = split_primitives(first, beyond, middle, n.m_bbox);

		node(node_idx).m_left_child  = expand(first, middle, node_idx);
		node(node_idx).m_right_child = expand(middle, beyond, node_idx);
	}
	break;
	default:
	{
		NodeT &lnode = node(n.m_left_child);
		NodeT &rnode = node(n.m_right_child);

		int  sd         = n.m_split_axis;
		auto left_max   = lnode.m_bbox.max_coord(sd);
		auto right_min  = rnode.m_bbox.min_coord(sd);
		auto insert_min = prim_box.min_coord(sd);
		auto insert_max = prim_box.max_coord(sd);
		n.m_bbox += prim_box;

		if (insert_max <= right_min)
			insert_to_node(prim_idx, prim_box, n.m_left_child);
		else if (insert_min >= left_max)
			insert_to_node(prim_idx, prim_box, n.m_right_child);
		else
		{
			// choose a branch that makes tree more balance.
			if (lnode.m_nb_primitives > rnode.m_nb_primitives)
				insert_to_node(prim_idx, prim_box, n.m_right_child);
			else
				insert_to_node(prim_idx, prim_box, n.m_left_child);
		}
	}
	break;
	}
}

template <typename Traits>
void DAABBTree<Traits>::remove_from_node(OMC_UNUSED index_t prim_idx,
                                         index_t            node_idx)
{
	NodeT &n = node(node_idx);

	OMC_EXPENSIVE_ASSERT(n.is_leaf() && n.m_left_child == prim_idx,
	                     "remove a primitive from non-leaf node or mismatch.");

	n.m_left_child    = InvalidIndex;
	n.m_nb_primitives = 0;

	// decrease nb_primitive in ancestors
	index_t parent_idx = n.m_parent;
	while (is_valid_idx(parent_idx))
	{
		node(parent_idx).m_nb_primitives -= 1;
		parent_idx = node(parent_idx).m_parent;
	}

	// due to (nb_primitives == 0)
	remove_node(node_idx);
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

	NodeT  &n           = node(node_idx);
	index_t parent_idx  = n.m_parent;
	NodeT  &parent_node = node(parent_idx);
	index_t grandpa_idx = parent_node.m_parent;

	parent_node          = n;
	parent_node.m_parent = grandpa_idx;
	n.clear();

	if (parent_node.m_nb_primitives >= 2)
	{ // has child nodes, update parent in child nodes.
		node(parent_node.m_left_child).m_parent  = parent_idx;
		node(parent_node.m_right_child).m_parent = parent_idx;
	}
	else if (parent_node.m_nb_primitives == 1)
	{ // has primitive, map the primitive to the node.
		mapto(parent_node.m_left_child) = parent_idx;
	}
	update_node(grandpa_idx);
	remove_node(node_idx);
}

template <typename Traits>
void DAABBTree<Traits>::swap_node(index_t node0, index_t node1)
{
	NodeT &n0 = node(node0);
	NodeT &n1 = node(node1);

	// swap parent's child index
	if (is_valid_idx(n0.m_parent))
	{
		if (node(n0.m_parent).m_left_child == node0)
			node(n0.m_parent).m_left_child = node1;
		else
			node(n0.m_parent).m_right_child = node1;
	}
	if (is_valid_idx(n1.m_parent))
	{
		if (node(n1.m_parent).m_left_child == node1)
			node(n1.m_parent).m_left_child = node0;
		else
			node(n1.m_parent).m_right_child = node0;
	}
	// swap children's parent index
	if (n0.m_nb_primitives >= 2)
	{
		node(n0.m_left_child).m_parent  = node1;
		node(n0.m_right_child).m_parent = node1;
	}
	else if (n0.m_nb_primitives == 1)
	{
		mapto(n0.m_left_child) = node1;
	}

	if (n1.m_nb_primitives >= 2)
	{
		node(n1.m_left_child).m_parent  = node0;
		node(n1.m_right_child).m_parent = node0;
	}
	else if (n1.m_nb_primitives == 1)
	{
		mapto(n1.m_left_child) = node0;
	}
	// swap two nodes
	std::swap(n0, n1);
}

template <typename Traits>
void DAABBTree<Traits>::update_node(index_t node_idx)
{
	if (!is_valid_idx(node_idx))
		return;

	NodeT &cur_node = node(node_idx);
	BboxT  new_box =
	  node(cur_node.m_left_child).m_bbox + node(cur_node.m_right_child).m_bbox;
	if (!(cur_node.m_bbox == new_box))
	{
		cur_node.m_bbox = new_box;
		update_node(cur_node.m_parent);
	}
}

template <typename Traits>
void DAABBTree<Traits>::split_node(index_t node_idx, index_t subprim0_idx,
                                   index_t subprim1_idx)
{
	NodeT &n = node(node_idx);

	OMC_EXPENSIVE_ASSERT(n.is_leaf(), "split a non-leaf node.");

	n.m_nb_primitives = 2;

	using iterator                 = std::array<index_t, 2>::iterator;
	std::array<index_t, 2> indices = {subprim0_idx, subprim1_idx};

	iterator first = indices.begin(), beyond = indices.end(), middle;
	n.m_bbox       = calc_bbox(first, beyond);
	n.m_split_axis = split_primitives(first, beyond, middle, n.m_bbox);

	node(node_idx).m_left_child  = expand(first, middle, node_idx);
	node(node_idx).m_right_child = expand(middle, beyond, node_idx);
	update_node(n.m_parent);
}

} // namespace OMC