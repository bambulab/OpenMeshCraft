#pragma once

#include "OrthogonalTree.h"

#include <algorithm>

namespace OMC {

/**
 * @brief Quadtree, i.e., orthogonal tree in 2D.
 * @details Two directions along each axis in Cartesian space, relative to a
 * node.
 *
 * Directions are mapped to numbers as 2-bit integers,
 *
 * The first bit indicate the axis (0 = x, 1 = y),
 * the second bit indicates the direction along that axis (0 = -, 1 = +).
 *
 * It has the following fomula:
 *
 * 	index = axis << 1 + direction.
 *
 * The following diagram may be a useful reference:
 *
 *            3 *
 *              |
 *              |                    y+
 *              |                    * 
 *     0 *------+------* 1           |
 *              |                    |
 *              |                    +-----* x+
 *              |
 *              * 2
 *
 * The four children and corner vertices have following indices:
 * 2(10) __________________ 3(11)
 *      |                 |   +y
 *      |                 |
 *      |                 |
 *      |                 |
 *      |                 |
 *      |_________________|  -y
 * -x  0(00)            1(01)  +x
 *
 */
template <typename _Traits>
class QuadTree : public OrthogonalTree<_Traits>
{
public:
	using Traits = _Traits;

	static constexpr size_t MaxDepth       = Traits::MaxDepth;
	static constexpr size_t Dimension      = Traits::Dimension;
	static constexpr size_t Degree         = (1u << Dimension);
	static constexpr bool   EnableVertices = Traits::EnableVertices;

	using NT = typename Traits::NT;

	using Bbox = typename Traits::BboxT;

	using OrBbox = typename Traits::OrBboxT;
	OrthTreeAbbreviate(OrBbox);

	using OrPoint = remove_cvref_t<decltype(std::declval<OrBbox>().min_bound())>;
	OrthTreeAbbreviate(OrPoint);

	using Node = OrthogonalNode<Traits>;
	OrthTreeAbbreviate(Node);

	using Vertex = OrthogonalVertex<Traits>;
	OrthTreeAbbreviate(Vertex);

public:
	index_t adj_vertex(index_t vidx, index_t axis, bool dir);

protected:
	/**
	 * @brief Get the position of a vertex. the vertex is located by node + local
	 * vertex index.
	 * @param nd_idx node index
	 * @param nv_idx local index of vertex in given node
	 * @return PointT the position of the vertex
	 */
	OrPoint calc_vertex_position(index_t nd_idx, index_t nv_idx);

	void set_adj_vertices_pair(index_t vl, index_t vh, index_t axis);

	/**
	 * @brief Build vertices for the OcTree.
	 * Each node has eight corner vertices. A vertex is unique to all adjacent
	 * nodes.
	 */
	virtual void build_vertices() final;

	virtual void calc_box_for_children(NodeRef nd, OrPointCRef center) final;

protected:
	/// Six adjcent vertices of each vertex.
	std::vector<std::array<index_t, 2 * Dimension>> m_adj_vertices;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "QuadTree.inl"
#endif