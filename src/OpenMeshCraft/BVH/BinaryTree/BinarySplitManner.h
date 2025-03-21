#pragma once

#include "OpenMeshCraft/Utils/Exception.h"
#include "OpenMeshCraft/Utils/IndexDef.h"

#define OMC_BSM_SAMPLE
#define OMC_BSM_SAMPLE_COUNT 1024

namespace OMC {

class BinarySplitManner
{
public:
	enum class Manner
	{
		GeomCenter,
		ElemCenter
	};

	BinarySplitManner()
	  : m_manner(Manner::ElemCenter)
	  , m_cross_thres(0.1)
	  , m_balence_thres(0.1)
	{
	}

	BinarySplitManner(Manner _manner)
	  : m_manner(_manner)
	  , m_cross_thres(0.1)
	  , m_balence_thres(0.1)
	{
	}

public:
	inline void set_thres(double _cross_thres, double _balence_thres)
	{
		m_cross_thres   = _cross_thres;
		m_balence_thres = _balence_thres;
	}

public:
	inline bool need_tight_box();

	/**
	 * @brief Decide where to split a node.
	 * @param [in] tree
	 * @param [in] node
	 * @param [out] split_axis
	 * @param [out] split_coord
	 * @param [out] lower_tbox tight box for lower node
	 * @param [out] higher_tbox tight box for higher node
	 * @return true if split is ok.
	 */
	template <typename Tree, typename Node>
	bool operator()(const Tree &tree, const Node &node, index_t &split_axis,
	                typename Tree::NT &split_coord);

	template <typename Tree, typename Node>
	bool geom_center(const Tree &tree, const Node &node, index_t &split_axis,
	                 typename Tree::NT &split_coord);

	template <typename Tree, typename Node>
	bool elem_center(const Tree &tree, const Node &node, index_t &split_axis,
	                 typename Tree::NT &split_coord);

protected:
	Manner m_manner;

	double m_cross_thres;
	double m_balence_thres;
};

inline bool BinarySplitManner::need_tight_box()
{
	switch (m_manner)
	{
	case Manner::GeomCenter:
		return true;
	case Manner::ElemCenter:
		return false;
	default:
		OMC_ASSERT(false, "Unknown split manner.");
		return false;
	}
}

template <typename Tree, typename Node>
bool BinarySplitManner::operator()(const Tree &tree, const Node &node,
                                   index_t           &split_axis,
                                   typename Tree::NT &split_coord)
{
	switch (m_manner)
	{
	case Manner::GeomCenter:
	{
		return geom_center(tree, node, split_axis, split_coord);
	}
	break;
	case Manner::ElemCenter:
	{
		return elem_center(tree, node, split_axis, split_coord);
	}
	break;
	default:
		OMC_ASSERT(false, "Unknown split manner.");
		return false;
	}
}

template <typename Tree, typename Node>
bool BinarySplitManner::geom_center(const Tree &tree, const Node &node,
                                    index_t           &split_axis,
                                    typename Tree::NT &split_coord)
{
	size_t  total = node.boxes().size();
	index_t begin = *node.boxes().begin();
	index_t end   = *node.boxes().end();
	// find the axis where box_side_length is longest at
	split_axis    = node.tbox().longest_axis();
	// now we simply split node at the center of the longest axis.
	split_coord   = 0.5 * (node.tbox().max_coord(split_axis) +
                       node.tbox().min_coord(split_axis));
	// check if boxes are partitionable and balence.
	size_t lower = 0, cross = 0, higher = 0;

	auto assign_box = [&](index_t box_idx)
	{
		typename Tree::TreeBboxCRef b = tree.box(box_idx);

		bool in_lower  = b.min_coord(split_axis) < split_coord;
		bool in_higher = b.max_coord(split_axis) >= split_coord;

		if (in_lower && in_higher)
			cross += 1;
		else if (in_lower)
			lower += 1;
		else if (in_higher)
			higher += 1;
	};

#ifdef OMC_BSM_SAMPLE // [B]inary [S]plit [M]anner

	size_t step = 1;
	if (total > OMC_BSM_SAMPLE_COUNT * 2)
	{
		step  = total / OMC_BSM_SAMPLE_COUNT;
		total = total / step;
	}

	for (index_t box_id = begin; box_id < end; box_id += step)
		assign_box(box_id);

#else

	std::for_each(node.boxes().begin(), node.boxes().end(), assign_box);

#endif

	bool partitionable = (double)cross / total < m_cross_thres;

	bool balence = (double)lower / total > m_balence_thres &&
	               (double)higher / total > m_balence_thres;

	return partitionable && balence;
}

template <typename Tree, typename Node>
bool BinarySplitManner::elem_center(const Tree &tree, const Node &node,
                                    index_t           &split_axis,
                                    typename Tree::NT &split_coord)
{
	size_t  total = node.boxes().size();
	index_t begin = *node.boxes().begin();
	index_t end   = *node.boxes().end();

	// assign boxes and check if partitionable
	typename Tree::TreePoint center(0.);

	std::array<size_t, Tree::Dimension> lower, cross, higher;
	std::fill(lower.begin(), lower.end(), 0);
	std::fill(cross.begin(), cross.end(), 0);
	std::fill(higher.begin(), higher.end(), 0);

	auto assign_box = [&](index_t box_idx)
	{
		typename Tree::TreeBboxCRef b = tree.box(box_idx);

		for (index_t split_axis = 0; split_axis < Tree::Dimension; split_axis++)
		{
			typename Tree::NT split_coord = center[split_axis];

			bool in_lower  = b.min_coord(split_axis) < split_coord;
			bool in_higher = b.max_coord(split_axis) >= split_coord;

			if (in_lower && in_higher)
				cross[split_axis] += 1;
			else if (in_lower)
				lower[split_axis] += 1;
			else if (in_higher)
				higher[split_axis] += 1;
		}
	};

#ifdef OMC_BSM_SAMPLE // [B]inary [S]plit [M]anner

	size_t step = 1;
	if (total > OMC_BSM_SAMPLE_COUNT * 2)
	{
		step  = total / OMC_BSM_SAMPLE_COUNT;
		total = total / step;
	}

	for (index_t box_id = begin; box_id < end; box_id += step)
		center += tree.box(box_id).min_bound() + tree.box(box_id).max_bound();
	center /= (typename Tree::NT)(total * 2);

	OMC_EXPENSIVE_ASSERT(center >= node.box().min_bound() &&
	                       center <= node.box().max_bound(),
	                     "calculated box center does not inside box.");

	for (index_t box_id = begin; box_id < end; box_id += step)
		assign_box(box_id);

#else

	// calculate the center of elements on all dimensions
	typename Tree::TreePoint center(0.);
	for (index_t box_id : node.boxes())
		center += tree.box(box_id).min_bound() + tree.box(box_id).max_bound();
	center /= (typename Tree::NT)(total * 2);

	OMC_EXPENSIVE_ASSERT(center >= node.box().min_bound() &&
	                       center <= node.box().max_bound(),
	                     "calculated box center does not inside box.");

	std::for_each(node.boxes().begin(), node.boxes().end(), assign_box);

#endif

	// find an axis that partitions boxes best.
	index_t best_axis  = OMC::InvalidIndex;
	double  best_score = std::numeric_limits<double>::max();
	for (index_t axis = 0; axis < Tree::Dimension; axis++)
	{
		if (lower[axis] == 0 || higher[axis] == 0)
			continue;

		double score = ((double)cross[axis] / total) /
		               ((double)lower[axis] / total) /
		               ((double)higher[axis] / total);
		if (score < best_score)
		{
			best_score = score;
			best_axis  = axis;
		}
	}

	if (OMC::is_valid_idx(best_axis) &&
	    /*partitionable*/ (double)cross[best_axis] / total < m_cross_thres &&
	    /*balence*/ (double)lower[best_axis] / total > m_balence_thres &&
	    /*balence*/ (double)higher[best_axis] / total > m_balence_thres)
	{
		// update box_assign_res
		split_axis  = best_axis;
		split_coord = center[best_axis];
		return true;
	}
	else
		return geom_center(tree, node, split_axis, split_coord);
}

} // namespace OMC