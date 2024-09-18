#pragma once

#include "TetMesh.h"

namespace OMC {

/**
 * @brief Apply a Delaunay tetrahedralization to a point set.
 * @details
 * - Theory reference: [Gmsh] Marot, C., Pellerin, J. and Remacle, J. F. One
 * machine, one minute, three billion tetrahedra. International Journal for
 * Numerical Methods in Engineering (2018).
 * - Implementation reference: [RobustCDT] Diazzi, L., Panozzo, D., Vaxman, A.
 * and Attene, M. Constrained Delaunay Tetrahedrization: A Robust and Practical
 * Approach. ACM Transactions on Graphics, 42, 6 (2023), 1-15.
 */
template <typename Traits>
class DelaunayTet
{
public: /* Traits **********************************************************/
	using Self = DelaunayTet<Traits>;

	using NT     = typename Traits::NT;
	using EPoint = typename Traits::EPoint;
	using GPoint = typename Traits::GPoint;

	using AsGP = typename Traits::AsGP;
	using AsEP = typename Traits::AsEP;
	using ToEP = typename Traits::ToEP;

	using Orient3D          = typename Traits::Orient3D;
	using CollinearPoints3D = typename Traits::CollinearPoints3D;
	using InSphere          = typename Traits::InSphere;

	const static index_t INFINITE_VERTEX = InvalidIndex;

	enum class TET_MARK : uint32_t
	{
		NO_MARKS  = 0,
		VISITED   = 1,
		TO_DELETE = 2,
	};

public: /* Constructor & Destructor ****************************************/
	DelaunayTet() = delete;
	DelaunayTet(const std::vector<GPoint *> &_in_verts,
	            std::vector<index_t>        &_out_tets);

public: /* Algorithm *******************************************************/
	/* Pipeline of the algorithm */
	void tetrahedralize();

	void initialize(index_t &k, index_t &l);

	void insertVertex(const index_t vid, index_t &tet);

	void markInfiniteTetsDeleted();

	void removeDeletedTets();

	/* Connectivity operations on tetrahedra mesh */

	GPoint       &gpnt(index_t vid) { return *verts[vid]; }
	const GPoint &gpnt(index_t vid) const { return *verts[vid]; }
	const EPoint &epnt(index_t vid) const { return AsEP()(*verts[vid]); }

	/// Get the index to the node
	index_t       &tetNode(index_t idoff) { return tet_node[idoff]; }
	const index_t &tetNode(index_t idoff) const { return tet_node[idoff]; }

	/// Get the idoff to the neighbor
	index_t       &tetNeigh(index_t idoff) { return tet_neigh[idoff]; }
	const index_t &tetNeigh(index_t idoff) const { return tet_neigh[idoff]; }

	static index_t clipId(index_t idoff) { return idoff & (~3); }
	static index_t getId(index_t idoff) { return idoff >> 2; }

	static index_t clipOff(index_t idoff) { return idoff & 3; }

	// tetNi is a sum modulo 3 - used to traverse the nodes of a tet
	static index_t tetN1(index_t idoff) { return (idoff + 1) & 3; }
	static index_t tetN2(index_t idoff) { return (idoff + 2) & 3; }
	static index_t tetN3(index_t idoff) { return (idoff + 3) & 3; }

	// tetONi - as above, but results in a coherent orientation
	// -------------------
	// off | 0 | 1 | 2 | 3
	// ----|---|---|---|--
	// ON1 | 1 | 2 | 3 | 0
	// ON2 | 3 | 3 | 1 | 1
	// ON3 | 2 | 0 | 0 | 2
	// -------------------
	static index_t tetON1(index_t idoff) { return (idoff + 1) & 3; }
	static index_t tetON2(index_t idoff) { return (idoff & 2) ^ 3; }
	static index_t tetON3(index_t idoff) { return (idoff + 3) & 2; }

	// clang-format off
	void mark(index_t idoff, TET_MARK bit) { tet_mark[getId(idoff)] |= (uint32_t)bit; }
	void unmark(index_t idoff, TET_MARK bit) { tet_mark[getId(idoff)] &= ~((uint32_t)bit); }
	void clearMark(index_t idoff) { tet_mark[getId(idoff)] = (uint32_t)TET_MARK::NO_MARKS; }

	bool isNoMarks(index_t idoff) { return tet_mark[getId(idoff)] == (uint32_t)TET_MARK::NO_MARKS; }
	bool isMarked(index_t idoff, TET_MARK bit) { return tet_mark[getId(idoff)] & ((uint32_t)bit); }
	// clang-format on

	void pushMarkDeletedTet(index_t idoff);

	void resizeTets(size_t new_size);
	void reserveTets(size_t new_capacity);
	void incSizeTets(size_t inc_size);

	size_t sizeVerts() const { return verts.size(); }
	size_t sizeTets() const { return tet_node.size() >> 2; }

	void clear();

	/* Geometric operations on tetrahedra mesh */

	bool vertexInTetSphere(index_t tet_idoff, index_t vid) const;

	bool vertexInTetSphere(const index_t *node, index_t vid) const;

	Sign symbolicPerturbation(index_t *indices) const;

public: /* Data ************************************************************/
	/// Input vertices (pointers to points in arena)
	///
	/// We assume that:
	/// 1. all vertices are explicit points.
	/// 2. no coincident vertices exist.
	const std::vector<GPoint *> &verts;

	/// Output tetrahedra
	///
	/// 1. There are `n` tetrahedra, and each tetrahedron has 4 vertices/nodes,
	/// resulting in a total of `4n` vertex/node indices stored in tet_node.
	/// 2. The orientation of the tetrahedron vertices/nodes (a, b, c, d) is
	/// determined by the convention that the cross product of (b - a) and (c - a)
	/// points toward d (i.e., the tetrahedron has a positive volume when
	/// calculating orient3d(a, b, c, d)).
	std::vector<index_t> &tet_node;

	/* Auxiliary data */

	/// Mark for each tetrahedron (See details for each bit above).
	std::vector<uint32_t> tet_mark;

	/// Collect all deleted tetrahedra. They may be reused to generate new
	/// tetrahedra.
	std::vector<index_t> tet_deleted;

	/// Four neighbors for each tetrahedron
	///
	/// 1. tet_neigh stores 4 neighbors for `n` tetrahedra, resulting in a total
	/// of `4n` neighbors stored in tet_neigh.
	/// 2. The value at `idoff = tet_id * 4 + offset` in tet_neigh corresponds to
	/// the neighbor of the corresponding node in tet_node.
	/// 3. The neighbor stored at the `idoff` position of tet_neigh is the
	/// opposite node in the adjacent tetrahedron of the corresponding node.
	/// 4. The stored value for the neighbor is also its `idoff` in tet_node, not
	/// its node index.
	///
	/// An illustration in 2D:
	///  idoff of the opposite node in the opposite neighbor...
	///        /\ 
	///      /___\ 
	///      \   /
	///       \/
	/// ...is stored in tet_neigh.
	std::vector<index_t> tet_neigh;

	/// vertex-(one_of_the)incident-tetrahedron relation
	std::vector<index_t> inc_tet;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "DelaunayTet.inl"
#endif