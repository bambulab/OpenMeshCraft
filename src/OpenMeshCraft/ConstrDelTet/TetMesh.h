#pragma once

#include "Utils.h"

#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#include "OpenMeshCraft/Utils/Exception.h"
#include "OpenMeshCraft/Utils/IndexDef.h"
#include "OpenMeshCraft/Utils/Macros.h"

namespace OMC {

template <typename Traits>
class TetrahedralMesh
{
public:
	using Self = TetrahedralMesh<Traits>;

	using NT     = typename Traits::NT;     ///< number type
	using EPoint = typename Traits::EPoint; ///< explicit point
	using GPoint = typename Traits::GPoint; ///< generic point

	using AsGP = typename Traits::AsGP; ///< use as generic point
	using AsEP = typename Traits::AsEP; ///< use as explicit point
	using ToEP = typename Traits::ToEP; ///< convert to explicit point

	using Orient3D          = typename Traits::Orient3D;
	using CollinearPoints3D = typename Traits::CollinearPoints3D;
	using InSphere          = typename Traits::InSphere;

	/// Infinite vertex index
	const static index_t INFINITE_VERTEX = InvalidIndex;

	enum class VTX_MARK : uint32_t
	{
		NO_MARK    = 0,
		VISITED    = 1,
		TO_DELETE  = 2,
		ENCROACHED = 4,
		TOUCHED    = 8,
	};

	/// Mark for each tetrahedron
	enum class TET_MARK : uint32_t
	{
		NO_MARK   = 0,
		VISITED   = 1,
		TO_DELETE = 2,
	};

public:
	/* Constructors and Destructors */
	TetrahedralMesh() = delete;
	TetrahedralMesh(const std::vector<GPoint *> &points);

public:
	/* Connectivity operations on tetrahedra mesh */

	/// Get the point of the vertex
	GPoint       &gpnt(index_t vid) { return *verts[vid]; }
	const GPoint &gpnt(index_t vid) const { return *verts[vid]; }
	const EPoint &epnt(index_t vid) const { return AsEP()(*verts[vid]); }

	/// Get the index (NOT the idoff) to the incident tetrahedron of a vertex
	index_t       &incTet(index_t vid) { return inc_tet[vid]; }
	const index_t &incTet(index_t vid) const { return inc_tet[vid]; }

	/// Get the index to the node/vertex
	/// @param idoff idoff = tet_id * 4 + offset
	index_t       &tetNode(index_t idoff) { return tet_node[idoff]; }
	const index_t &tetNode(index_t idoff) const { return tet_node[idoff]; }

	/// Get the idoff to the neighbor
	/// @param idoff idoff = tet_id * 4 + offset
	index_t       &tetNeigh(index_t idoff) { return tet_neigh[idoff]; }
	const index_t &tetNeigh(index_t idoff) const { return tet_neigh[idoff]; }

	/// Clip the id of an idoff
	/// @param idoff idoff = tet_id * 4 + offset
	/// @return tet_id * 4
	static index_t clipId(index_t idoff) { return idoff & (~3); }

	/// Get the id of an idoff
	/// @param idoff idoff = tet_id * 4 + offset
	/// @return tet_id
	static index_t getId(index_t idoff) { return idoff >> 2; }

	/// Get the idoff from an id
	/// @param id index to a tetrahedron
	/// @return idoff = id * 4
	static index_t toIdOff(index_t id) { return id << 2; }

	/// Clip the offset of an idoff
	/// @param idoff idoff = tet_id * 4 + offset
	/// @return offset
	static index_t clipOff(index_t idoff) { return idoff & 3; }

	/// Get the next `i` node index of the given node index in a tetrahedron.
	/// tetNi is a sum modulo 3, used to traverse the nodes of a tet.
	/// @param idoff idoff = tet_id * 4 + offset
	static index_t tetNi(index_t idoff, index_t i) { return (idoff + i) & 3; }

	/// tetONi - as above, but results in a coherent orientation
	/// @details
	/// -------------------
	/// off | 0 | 1 | 2 | 3
	/// ----|---|---|---|--
	/// ON1 | 1 | 2 | 3 | 0
	/// ON2 | 3 | 3 | 1 | 1
	/// ON3 | 2 | 0 | 0 | 2
	/// -------------------
	static index_t tetON1(index_t idoff) { return (idoff + 1) & 3; }
	static index_t tetON2(index_t idoff) { return (idoff & 2) ^ 3; }
	static index_t tetON3(index_t idoff) { return (idoff + 3) & 2; }

	index_t tetCorner(index_t tet_idoff, index_t vid) const;

	bool tetHasVertex(index_t tet_idoff, index_t vid) const;

	bool isFiniteTet(index_t idoff) const;

	bool edgeExists(index_t vid0, index_t vid1) const;

	void oppoTetEdge(index_t tet_idoff, index_t vid0, index_t vid1, index_t &vid2,
	                 index_t &vid3) const;

	template <typename ContainerT>
	void VT(index_t vid, ContainerT &tets) const;

	template <typename ContainerT>
	void VV(index_t vid, ContainerT &verts) const;

	template <typename ContainerT>
	void ET(index_t vid0, index_t vid1, ContainerT &tets) const;

	/* Operations about marks */

	// clang-format off

	/// mark the tetrahedron with the given bit
	void mark(index_t idoff, TET_MARK bit) const { tet_mark[getId(idoff)] |= (uint32_t)bit; }
	/// unmark the tetrahedron with the given bit
	void unmark(index_t idoff, TET_MARK bit) const { tet_mark[getId(idoff)] &= ~((uint32_t)bit); }
	/// clear all marks of the tetrahedron
	void clearTetMark(index_t idoff) const { tet_mark[getId(idoff)] = (uint32_t)TET_MARK::NO_MARK; }
	/// check if the tetrahedron has no mark
	bool isTetUnmarked(index_t idoff) const { return tet_mark[getId(idoff)] == (uint32_t)TET_MARK::NO_MARK; }
	/// check if the tetrahedron is marked with the given bit
	bool isTetMarked(index_t idoff, TET_MARK bit) const { return tet_mark[getId(idoff)] & ((uint32_t)bit); }

	/// mark the vertex with the given bit
	void mark(index_t vid, VTX_MARK bit) const { vtx_mark[vid] |= (uint32_t)bit; }
	/// unmark the vertex with the given bit
	void unmark(index_t vid, VTX_MARK bit) const { vtx_mark[vid] &= ~((uint32_t)bit); }
	/// clear all marks of the vertex
	void clearVtxMark(index_t vid) const { vtx_mark[vid] = (uint32_t)VTX_MARK::NO_MARK; }
	/// check if the vertex has no mark
	bool isVtxUnmarked(index_t vid) const { return vtx_mark[vid] == (uint32_t)VTX_MARK::NO_MARK; }
	/// check if the vertex is marked with the given bit
	bool isVtxMarked(index_t vid, VTX_MARK bit) const { return vtx_mark[vid] & ((uint32_t)bit); }

	// clang-format on

	/* Operations about creation */

	void newVtx(index_t new_vid);

	index_t newTet();
	void    newTets(size_t inc_size, AuxVector64<index_t> &new_tets);

	/* Operations about deletion */

	void markTetAsDeleted(index_t idoff);
	void removeDeletedTets();

	void clear();
	void clearVerts();
	void clearTets();

	/* Operations about resizing */

	void resizeTets(size_t new_size);
	void reserveTets(size_t new_capacity);
	void reserveNewTets(size_t inc_size);

	/* Operations about query */

	size_t sizeVerts() const { return verts.size(); }
	size_t sizeTets() const { return tet_node.size() >> 2; }

	/* Common geometric predicates */

	bool vertexInTetSphere(index_t tet_idoff, index_t vid) const;

	bool vertexInTetSphere(const index_t *node, index_t vid) const;

	Sign symbolicPerturbation(index_t *indices) const;

public: /* Data ************************************************************/
	/// Vertices (pointers to points in arena)
	///
	/// We assume that:
	/// 1. all vertices are explicit points.
	/// 2. no coincident vertices exist.
	const std::vector<GPoint *> &verts;

	/// Vertex-(one_of_the)incident-tetrahedron relation.
	/// Each index is the id of the incident tetrahedron.
	std::vector<index_t> inc_tet;

	/// Tetrahedra (indices to vertices)
	///
	/// 1. There are `n` tetrahedra, and each tetrahedron has 4 vertices/nodes,
	/// resulting in a total of `4n` vertex/node indices stored in tet_node.
	/// 2. The orientation of the tetrahedron vertices/nodes (a, b, c, d) is
	/// determined by the convention that the cross product of (b - a) and (c - a)
	/// points toward d (i.e., the tetrahedron has a positive volume when
	/// calculating orient3d(a, b, c, d)).
	std::vector<index_t> tet_node;

	/* Auxiliary data */

	mutable std::vector<uint32_t> vtx_mark;

	/// Mark for each tetrahedron (See details for each bit above).
	mutable std::vector<uint32_t> tet_mark;

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
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "TetMesh.inl"
#endif