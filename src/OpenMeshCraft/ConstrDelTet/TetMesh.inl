#pragma once

#include "TetMesh.h"

namespace OMC {

template <typename Traits>
TetrahedralMesh<Traits>::TetrahedralMesh(const std::vector<GPoint *> &points)
  : verts(points)
{
	inc_tet.resize(sizeVerts(), InvalidIndex);
	vtx_mark.resize(sizeVerts(), 0);
}

/**
 * @brief Given the tetrahedron (in `idoff`) and its node (in `vertex id`),
 * get the `idoff` to the tetrahedron node.
 */
template <typename Traits>
index_t TetrahedralMesh<Traits>::tetCorner(index_t tet_idoff, index_t vid) const
{
	OMC_EXPENSIVE_ASSERT(clipOff(tet_idoff) == 0,
	                     "Invalid tetrahedron id offset.");
	// clang-format off
	if (tetNode(tet_idoff) == vid)     return tet_idoff;
	if (tetNode(tet_idoff + 1) == vid) return tet_idoff + 1;
	if (tetNode(tet_idoff + 2) == vid) return tet_idoff + 2;
	if (tetNode(tet_idoff + 3) == vid) return tet_idoff + 3;
	// clang-format on
	OMC_ASSERT(false, "The vertex is not in the tetrahedron.");
	return InvalidIndex;
}

/// @brief Check if the tetrahedron has the vertex.
template <typename Traits>
bool TetrahedralMesh<Traits>::tetHasVertex(index_t tet_idoff, index_t vid) const
{
	OMC_EXPENSIVE_ASSERT(clipOff(tet_idoff) == 0,
	                     "Invalid tetrahedron id offset.");
	return tetNode(tet_idoff) == vid || tetNode(tet_idoff + 1) == vid ||
	       tetNode(tet_idoff + 2) == vid || tetNode(tet_idoff + 3) == vid;
}

/// @brief Check if the tetrahedron is finite.
/// Remember that we always put the infinite vertex at the last position.
template <typename Traits>
bool TetrahedralMesh<Traits>::isFiniteTet(index_t idoff) const
{
	// idoff | 3 == clipId(idoff) + 3
	return tetNode(idoff | 3) != INFINITE_VERTEX;
}

/**
 * @brief Finds the two vertices opposite to the given edge in a tetrahedron.
 * @param [in] tet_idoff The offset index of the tetrahedron.
 * @param [in] vid_0_1 The vertices of the query edge.
 * @param [out] vid_2_3 The vertices of the opposite edge.
 * @note The function assumes that the input edge is valid and belongs to the
 * tetrahedron.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::oppoEdge(index_t tet_idoff, index_t vid0,
                                       index_t vid1, index_t &vid2,
                                       index_t &vid3) const
{
	OMC_EXPENSIVE_ASSERT(clipOff(tet_idoff) == 0,
	                     "Invalid tetrahedron id offset.");
	OMC_EXPENSIVE_ASSERT(tetHasVertex(tet_idoff, vid0) &&
	                       tetHasVertex(tet_idoff, vid1),
	                     "The edge is not in the tetrahedron.");

	index_t *res[2] = {&vid2, &vid3}, i, j;
	for (i = 0, j = 0; i < 4; i++)
	{
		index_t w = tetNode(tet_idoff + i);
		if (w != vid0 && w != vid1)
			*(res[j++]) = w;
	}
	OMC_EXPENSIVE_ASSERT(j == 2, "Invalid Input.");
}

/**
 * @brief Finds the opposite corner/node of the face defined by the given
 * vertices `vid0`, `vid1` and `vid2` in the tetrahedron `tet_idoff`.
 *
 * @param [in] tet_idoff The tetrahedron ID offset.
 * @param [in] vid_0_1_2 The face defined by three vertices.
 * @return index_t The opposite vertex index.
 */
template <typename Traits>
index_t TetrahedralMesh<Traits>::oppoVertex(index_t tet_idoff, index_t vid0,
                                            index_t vid1, index_t vid2) const
{
	OMC_EXPENSIVE_ASSERT(clipOff(tet_idoff) == 0,
	                     "Invalid tetrahedron id offset.");
	OMC_EXPENSIVE_ASSERT(tetHasVertex(tet_idoff, vid0) &&
	                       tetHasVertex(tet_idoff, vid1) &&
	                       tetHasVertex(tet_idoff, vid2),
	                     "The face is not in the tetrahedron.");
	// rely on overflow.
	return tetNode(tet_idoff) + tetNode(tet_idoff + 1) + tetNode(tet_idoff + 2) +
	       tetNode(tet_idoff + 3) - vid0 - vid1 - vid2;
}

/**
 * @brief Retrieves the vertex indices of a face of a tetrahedron.
 *
 * This function extracts the vertex indices of a specific face of a tetrahedron
 * identified by the given tetrahedron ID offset.
 *
 * @param [in] tet_idoff The tetrahedron ID offset.
 * @param [out] vid_0_1_2 Reference to store the vertex indices of the face.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::faceVertices(index_t tet_idoff, index_t &vid0,
                                           index_t &vid1, index_t &vid2) const
{
	index_t        off  = clipOff(tet_idoff);
	const index_t *node = &tetNode(clipId(tet_idoff));

	vid0 = node[tetON1(off)];
	vid1 = node[tetON2(off)];
	vid2 = node[tetON3(off)];
}

/**
 * @brief Given two vertices `vid0` and `vid1`, check if the edge defined by the
 * vertices exists in the tetrahedral mesh.
 *
 * Check if the edge exists by traversing the adjacent tetrahedra of the vertex
 * `vid0` to find the vertex `vid1`.
 *
 * @param [in] vid_0_1 two vertices define the edge.
 * @return True if the edge exists, otherwise false.
 *
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron
 * multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
bool TetrahedralMesh<Traits>::edgeExists(index_t vid0, index_t vid1) const
{
	bool    exist     = false;
	// find the first adajcent tetrahedron
	index_t tet_idoff = toIdOff(incTet(vid0));

	AuxVector64<index_t> tets;
	tets.push_back(tet_idoff);
	mark(tet_idoff, TET_MARK::VISITED);

	for (index_t i = 0; i < tets.size(); i++)
	{
		index_t curr_idoff = tets[i];
		// check if the current tetrahedron has the vertex `vid1`
		if (tetHasVertex(curr_idoff, vid1))
		{
			exist = true;
			break; // the edge exists, return true
		}
		// otherwise visit the neighbors at other corners
		for (index_t j = 0; j < 4; j++)
		{
			// skip the corner at `vid0`
			if (tetNode(curr_idoff + j) == vid0)
				continue;
			// visit neighbors at other corners
			index_t neigh_idoff = clipId(tetNeigh(curr_idoff + j));
			// skip infinite tetrahedra and visited tetrahedra
			if (isFiniteTet(neigh_idoff) && !isMarked(neigh_idoff, TET_MARK::VISITED))
			{
				tets.push_back(neigh_idoff);
				mark(neigh_idoff, TET_MARK::VISITED);
			}
		}
	}
	// unmark visited tetrahedra
	for (index_t idoff : tets)
		unmark(idoff, TET_MARK::VISITED);
	return exist;
}

/**
 * @brief Given three vertices `vid0`, `vid1` and `vid2`, check if the face
 * defined by the vertices exists in the tetrahedral mesh.
 *
 * Check if the face exists by traversing the adjacent tetrahedra of the vertex
 * `vid0` to find the vertex `vid1` and `vid2`.
 *
 * @param [in] vid_0_1_2 three vertices define the face.
 * @return True if the face exists, otherwise false.
 *
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron
 * multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
bool TetrahedralMesh<Traits>::faceExists(index_t vid0, index_t vid1,
                                         index_t vid2) const
{
	bool    exist     = false;
	// find the first adajcent tetrahedron
	index_t tet_idoff = toIdOff(incTet(vid0));

	AuxVector64<index_t> tets;
	tets.push_back(tet_idoff);
	mark(tet_idoff, TET_MARK::VISITED);

	for (index_t i = 0; i < tets.size(); i++)
	{
		index_t curr_idoff = tets[i];
		// check if the current tetrahedron has the vertex `vid1` and `vid2`
		if (tetHasVertex(curr_idoff, vid1) && tetHasVertex(curr_idoff, vid2))
		{
			exist = true;
			break; // the face exists, return true
		}
		// otherwise visit the neighbors at other corners
		for (index_t j = 0; j < 4; j++)
		{
			// skip the corner at `vid0`
			if (tetNode(curr_idoff + j) == vid0)
				continue;
			// visit neighbors at other corners
			index_t neigh_idoff = clipId(tetNeigh(curr_idoff + j));
			// skip infinite tetrahedra and visited tetrahedra
			if (isFiniteTet(neigh_idoff) && !isMarked(neigh_idoff, TET_MARK::VISITED))
			{
				tets.push_back(neigh_idoff);
				mark(neigh_idoff, TET_MARK::VISITED);
			}
		}
	}
	// unmark visited tetrahedra
	for (index_t idoff : tets)
		unmark(idoff, TET_MARK::VISITED);
	return exist;
}

/**
 * @brief Collect tetrahedra adjacent to the vertex `vid` and store them in the
 * container `tets`.
 * @param [in] vid Vertex index
 * @param [out] adj_tets Container to store the adjacent tetrahedra (tetrahedron
 * idoff)
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron and
 * the same vertex multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
template <typename ContainerT>
void TetrahedralMesh<Traits>::VT(index_t vid, ContainerT &adj_tets) const
{
	OMC_EXPENSIVE_ASSERT(vid < sizeVerts(), "Invalid vertex index.");
	index_t tet_idoff = toIdOff(incTet(vid));

	adj_tets.push_back(tet_idoff);
	mark(tet_idoff, TET_MARK::VISITED);

	for (index_t i = 0; i < adj_tets.size(); i++)
	{
		index_t curr_idoff = adj_tets[i];
		// visit neighbors
		for (index_t j = 0; j < 4; j++)
		{
			// skip the corner at `vid`
			if (tetNode(curr_idoff + j) == vid)
				continue;
			// visit neighbors at other corners
			index_t neigh_idoff = clipId(tetNeigh(curr_idoff + j));
			// skip infinite tetrahedra and visited tetrahedra
			if (isFiniteTet(neigh_idoff) && !isMarked(neigh_idoff, TET_MARK::VISITED))
			{
				adj_tets.push_back(neigh_idoff);
				mark(neigh_idoff, TET_MARK::VISITED);
			}
		}
	}
	// unmark visited tetrahedra
	for (index_t idoff : adj_tets)
		unmark(idoff, TET_MARK::VISITED);
}

/**
 * @brief Collect vertices adjacent to the vertex `vid` and store them in the
 * container `adj_verts`.
 * @param [in] vid Vertex index
 * @param [out] adj_verts Container to store the adjacent vertices (vertex id)
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron and
 * the same vertex multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
template <typename ContainerT>
void TetrahedralMesh<Traits>::VV(index_t vid, ContainerT &adj_verts) const
{
	OMC_EXPENSIVE_ASSERT(vid < sizeVerts(), "Invalid vertex index.");
	index_t tet_idoff = toIdOff(incTet(vid));

	AuxVector64<index_t> tets;
	tets.push_back(tet_idoff);
	mark(tet_idoff, TET_MARK::VISITED);

	for (index_t i = 0; i < tets.size(); i++)
	{
		index_t curr_idoff = tets[i];
		// visit neighbors
		for (index_t j = 0; j < 4; j++)
		{
			index_t curr_vid = tetNode(curr_idoff + j);
			// skip the corner at `vid`
			if (curr_vid == vid)
				continue;
			// add the corner vertex into `adj_verts`
			if (!isMarked(curr_vid, VTX_MARK::VISITED))
			{
				mark(curr_vid, VTX_MARK::VISITED);
				adj_verts.push_back(curr_vid);
			}
			// visit neighbors at other corners
			index_t neigh_idoff = clipId(tetNeigh(curr_idoff + j));
			// skip infinite tetrahedra and visited tetrahedra
			if (isFiniteTet(neigh_idoff) && !isMarked(neigh_idoff, TET_MARK::VISITED))
			{
				tets.push_back(neigh_idoff);
				mark(neigh_idoff, TET_MARK::VISITED);
			}
		}
	}
	// unmark visited tetrahedra
	for (index_t idoff : tets)
		unmark(idoff, TET_MARK::VISITED);
	// unmark visited vertices
	for (index_t vi : adj_verts)
		unmark(vi, VTX_MARK::VISITED);
}

/**
 * @brief Find tetrahedra adjacent to the edge defined by the vertices `vid0`
 * and `vid1`, and store in `tets`.
 * @param [in] vid0 Vertex index
 * @param [in] vid1 Vertex index
 * @param [out] adj_tets Container to store the adjacent tetrahedra (tetrahedron
 * idoff)
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron and
 * the same vertex multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
template <typename ContainerT>
void TetrahedralMesh<Traits>::ET(index_t vid0, index_t vid1,
                                 ContainerT &adj_tets) const
{
	OMC_EXPENSIVE_ASSERT(vid0 < sizeVerts() && vid1 < sizeVerts(),
	                     "Invalid vertex index.");
	// find tetrahedra adjacent to the vertex `vid0`
	VT(vid0, adj_tets);
	// keep the tetrahedra adjacent to the vertex `vid1`
	for (index_t i = 0; i < adj_tets.size(); /*`i` is updated in the loop*/)
	{
		if (!tetHasVertex(adj_tets[i], vid1))
		{
			std::swap(adj_tets[i], adj_tets.back());
			adj_tets.pop_back();
		}
		else
			i++;
	}
}

/**
 * @brief Find two tetrahedra corresponding to the face defined by the vertices
 * `vid0`, `vid1` and `vid2`.
 *
 * @param [in] vid_0_1_2 three vertices (index) define the face.
 * @param [out] t_1_2 two tetrahedra (tet_idoff) corresponding to the face.
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron and
 * the same vertex multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::faceAdjTets(index_t vid0, index_t vid1,
                                          index_t vid2, index_t &t0,
                                          index_t &t1)
{
	// temporary container to store the adjacent tetrahedra
	index_t adj_tets[2] = {InvalidIndex, InvalidIndex};
	index_t tc          = 0;

	// find the first adajcent tetrahedron
	index_t tet_idoff = toIdOff(incTet(vid0));

	AuxVector64<index_t> tets;
	tets.push_back(tet_idoff);
	mark(tet_idoff, TET_MARK::VISITED);

	for (index_t i = 0; i < tets.size(); i++)
	{
		index_t curr_idoff = tets[i];
		// check if the current tetrahedron has the vertex `vid1` and `vid2`
		if (tetHasVertex(curr_idoff, vid1) && tetHasVertex(curr_idoff, vid2))
		{
			adj_tets[tc++] = curr_idoff;
#ifndef OMC_ENABLE_EXPENSIVE_ASSERT
			if (tc == 2)
				break;
#endif
		}
		// visit the neighbors at other corners
		for (index_t j = 0; j < 4; j++)
		{
			// skip the corner at `vid0`
			if (tetNode(curr_idoff + j) == vid0)
				continue;
			// visit neighbors at other corners
			index_t neigh_idoff = clipId(tetNeigh(curr_idoff + j));
			// skip visited tetrahedra
			if (!isMarked(neigh_idoff, TET_MARK::VISITED))
			{
				tets.push_back(neigh_idoff);
				mark(neigh_idoff, TET_MARK::VISITED);
			}
		}
	}
	// unmark visited tetrahedra
	for (index_t idoff : tets)
		unmark(idoff, TET_MARK::VISITED);

	OMC_EXPENSIVE_ASSERT(tc == 2, "The face is not shared by two tetrahedra.");
	t0 = adj_tets[0], t1 = adj_tets[1];
}

/**
 * @brief Find two corners corresponding to the face defined by the vertices
 * `vid0`, `vid1` and `vid2`.
 *
 * The face has two adjacent tetrahedra, each tetrahedron has a corner
 * corresponding to the face (i.e., the node opposite to the face).
 *
 * @param [in] vid_0_1_2 three vertices (index) define the face.
 * @param [out] c_0_1 two corners (idoff) corresponding to the face.
 * @note It relies on mark `VISITED` to avoid visiting the same tetrahedron and
 * the same vertex multiple times. NOT THREAD SAFE.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::faceCorners(index_t vid0, index_t vid1,
                                          index_t vid2, index_t &c0,
                                          index_t &c1)
{
	// two tetrahedra (tet_idoff) adjacent to the face
	index_t t0, t1;
	faceAdjTets(vid0, vid1, vid2, t0, t1);
	// the idoff of the two corners
	c0 = tetCorner(t0, oppoVertex(t0, vid0, vid1, vid2));
	c1 = tetCorner(t1, oppoVertex(t1, vid0, vid1, vid2));
}

/**
 * @brief Classify tetrahedra to inside and outside.
 * `corner_is_boundary` marks boundary corners.
 * @param [in] corner_is_boundary A vector to mark boundary corners.
 * @param [in] start_tet_idoff The starting tetrahedron to mark.
 * @return The number of tetrahedra classified as inside.
 * @note Rely on a closed and not self-intersected boundary.
 */
template <typename Traits>
size_t
TetrahedralMesh<Traits>::classifyInOut(std::vector<uint8_t> &corner_is_boundary,
                                       index_t               start_tet_idoff)
{
	// All infinite tetrahedra are marked as outside,
	// other tetrahedra are marked as unknown.
	for (index_t i = 0; i < sizeTets(); i++)
		mark(toIdOff(i),
		     isFiniteTet(toIdOff(i)) ? TET_MARK::IO_UNKNOWN : TET_MARK::OUTSIDE);

	// tets saves classified tetrahedra
	std::vector<uint64_t> tets;
	tets.reserve(sizeTets());

	if (is_valid_idx(start_tet_idoff))
	{ // start classification from the given tetrahedron
		OMC_EXPENSIVE_ASSERT(clipOff(start_tet_idoff) == 0 &&
		                       start_tet_idoff < sizeTets() * 4,
		                     "Invalid start tetrahedron id offset.");
		tets.push_back(start_tet_idoff);
	}
	else
	{ // start classification from the all outer tetrahedra
		for (index_t i = 0; i < sizeTets(); i++)
			if (isMarked(toIdOff(i), TET_MARK::OUTSIDE))
				tets.push_back(toIdOff(i));
	}

	// Traverse the unkown tetrahedra to classify them.
	for (index_t i = 0; i < tets.size(); i++)
	{
		index_t tet_idoff = tets[i];
		for (index_t j = 0; j < 4; j++)
		{
			const index_t neigh_idoff = tetNeigh(tet_idoff + j);
			// skip the classified tetrahedra
			if (!isMarked(neigh_idoff, TET_MARK::IO_UNKNOWN))
				continue;

			if (corner_is_boundary[neigh_idoff])
			{ // Encountered a boundary corner/face.
				// Mark the neighbor as the opposite of the current tet.
				mark(neigh_idoff, isMarked(tet_idoff, TET_MARK::INSIDE)
				                    ? TET_MARK::OUTSIDE
				                    : TET_MARK::INSIDE);
			}
			else
			{ // Mark the neighbor as the same as the current tet.
				mark(neigh_idoff, isMarked(tet_idoff, TET_MARK::INSIDE)
				                    ? TET_MARK::INSIDE
				                    : TET_MARK::OUTSIDE);
			}
			// now the neighbor is classified, add it to the list
			unmark(neigh_idoff, TET_MARK::IO_UNKNOWN);
			tets.push_back(clipId(neigh_idoff));
		}
	}

	return std::count_if(tet_mark.begin(), tet_mark.end(), [](uint32_t m)
	                     { return m & (uint32_t)TET_MARK::INSIDE; });
}

/**
 * @brief Create a new vertex.
 *
 * Note that TetMesh does not manage the vertices directly. The new vertex is
 * created externally, and then TetMesh creates the corresponding auxiliary
 * data.
 * @param new_vid The index of the new vertex created externally.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::newVtx(OMC_UNUSED index_t new_vid)
{
	inc_tet.emplace_back(InvalidIndex);
	vtx_mark.emplace_back(0);

	OMC_EXPENSIVE_ASSERT(sizeVerts() == new_vid + 1, "size mismatch.");
	OMC_EXPENSIVE_ASSERT(inc_tet.size() == new_vid + 1, "size mismatch.");
	OMC_EXPENSIVE_ASSERT(vtx_mark.size() == new_vid + 1, "size mismatch.");
}

/**
 * @brief Create a new tetrahedron. The new tetrahedron is either created at the
 * tail of the tetrahedra list or at the position of a deleted tetrahedron.
 * @note
 * - node and neighbor of the new tetrahedron are undefined.
 * - mark of the new tetrahedron is NO_MARK.
 * @return index_t The idoff of the new tetrahedron.
 */
template <typename Traits>
index_t TetrahedralMesh<Traits>::newTet()
{
	index_t new_tet_idoff = InvalidIndex;
	if (tet_deleted.empty())
	{
		new_tet_idoff = sizeTets() * 4;
		tet_mark.emplace_back(TET_MARK::NO_MARK);
		// node and neighbor are undefined
		tet_node.resize(new_tet_idoff + 4);
		tet_neigh.resize(new_tet_idoff + 4);
	}
	else
	{
		OMC_EXPENSIVE_ASSERT(isMarked(tet_deleted.back(), TET_MARK::TO_DELETE),
		                     "The tet is not marked to be deleted.");
		new_tet_idoff = tet_deleted.back();
		tet_deleted.pop_back();
		clearTetMark(new_tet_idoff);
		// node and neighbor are undefined
		// ......
	}
	return new_tet_idoff;
}

/**
 * @brief Allocates new tetrahedra in the mesh.
 *
 * This function resizes the `new_tets` vector to the specified `inc_size` and
 * populates it with indices of newly allocated tetrahedra. It first attempts
 * to reuse deleted tetrahedra if available, and then creates new tetrahedra
 * if necessary.
 * @note
 * - node and neighbor of the new tetrahedron are undefined.
 * - mark of the new tetrahedron is NO_MARK.
 * @param inc_size The number of new tetrahedra to allocate.
 * @param new_tets A vector to store the indices of the newly allocated
 * tetrahedra.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::newTets(size_t                inc_size,
                                      AuxVector64<index_t> &new_tets)
{
	// 1. Resizes the `new_tets` vector to `inc_size`.
	new_tets.resize(inc_size);
	auto first = new_tets.begin();

	// 2. Reuses deleted tetrahedra if available:
	if (!tet_deleted.empty())
	{
		// Copies indices from `tet_deleted` to `new_tets`.
		size_t n = std::min(tet_deleted.size(), inc_size);
		std::copy(tet_deleted.end() - n, tet_deleted.end(), first);
		// Unmarks these tetrahedra as deleted.
		for (auto iter = tet_deleted.end() - n; iter != tet_deleted.end(); iter++)
			clearTetMark(*iter);
		// Updates the size of `tet_deleted`.
		tet_deleted.resize(tet_deleted.size() - n);
		// update the first iterator
		first += n;
		inc_size -= n;
	}

	// 3. Creates new tetrahedra if necessary:
	if (inc_size > 0)
	{
		OMC_EXPENSIVE_ASSERT(tet_deleted.empty(),
		                     "Not all deleted tets are reused.");
		// Resizes the internal tetrahedra storage.
		index_t idoff = sizeTets() * 4;
		resizeTets(sizeTets() + inc_size);
		// Populates `new_tets` with indices of the newly created tetrahedra.
		while (first < new_tets.end())
		{
			*first = idoff;
			first++;
			idoff += 4;
		}
	}
}

/**
 * @brief Marks tetrahedrons containing infinite vertices as deleted.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::markInfiniteTetsDeleted()
{
	const size_t n = sizeTets();
	for (index_t id = 0; id < n; id++)
	{
		index_t idoff = toIdOff(id);
		if (isMarked(idoff, TET_MARK::TO_DELETE))
			continue;
		if (!isFiniteTet(idoff))
		{
			markTetAsDeleted(idoff);
			OMC_EXPENSIVE_ASSERT(tetNeigh(tetNeigh(idoff + 3)) == idoff + 3,
			                     "The neighbor relationship is incorrect.");
			tetNeigh(tetNeigh(idoff + 3)) = InvalidIndex;
		}
	}
}

/**
 * @brief Mark a tetrahedron as deleted.
 * @param idoff tetrahedron's idoff = tet_id * 4 + node_offset
 */
template <typename Traits>
void TetrahedralMesh<Traits>::markTetAsDeleted(index_t idoff)
{
	tet_deleted.push_back(clipId(idoff));
	mark(idoff, TET_MARK::TO_DELETE);
}

/**
 * @brief Really remove the tetrahedra marked as deleted.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::removeDeletedTets()
{
	// If there is no tetrahedra, return.
	if (tet_node.empty())
		return;

	OMC_ASSERT((tet_node.size() % 4 == 0),
	           "Tetrahedra mesh's node size is wrong.");

	// Locate the last tetrahedron that has not been marked for deletion.
	index_t last = tet_node.size() - 4;
	while (isMarked(last, TET_MARK::TO_DELETE) && last > 0)
		last -= 4;

	if (last == 0)
	{ // If all tetrahedra are marked to be deleted...
		resizeTets(0);
		tet_deleted.clear();
		return;
	}

	// Iterate through the list of deleted tetrahedra.
	for (index_t t : tet_deleted)
	{
		// Check if the current tetrahedron is before the last and is marked for
		// deletion.
		if (t < last && isMarked(t, TET_MARK::TO_DELETE))
		{
			// Update the nodes associated with the tetrahedron.
			for (int i = 0; i < 4; i++)
			{
				// Update the node information.
				tet_node[t + i]  = tet_node[last + i];
				// Update the neighbor information.
				const index_t n  = tet_neigh[last + i];
				tet_neigh[t + i] = n;
				if (is_valid_idx(n))
					tet_neigh[n] = t + i;
				// Update the incident tetrahedron information.
				if (tet_node[last + i] != INFINITE_VERTEX &&
				    inc_tet[tet_node[last + i]] == getId(last))
				{
					inc_tet[tet_node[last + i]] = getId(t);
				}
			}
			// Update the mark for the tetrahedron.
			tet_mark[getId(t)] = tet_mark[getId(last)];
			// Move to the next "last un-deleted" tetrahedron.
			last -= 4;
			while (isMarked(last, TET_MARK::TO_DELETE) && last > 0)
				last -= 4;
		}
	}

	resizeTets((last + 4) >> 2);
	tet_deleted.clear();
}

/**
 * @brief Resize the tetrahedra mesh to the new size.
 * @param new_size number of tetrahedra
 */
template <typename Traits>
void TetrahedralMesh<Traits>::resizeTets(size_t new_size)
{
	tet_mark.resize(new_size);
	new_size <<= 2;
	tet_node.resize(new_size);
	tet_neigh.resize(new_size);
}

/**
 * @brief Reserve the memory for the tetrahedra mesh.
 * @param new_capacity number of tetrahedra
 */
template <typename Traits>
void TetrahedralMesh<Traits>::reserveTets(size_t new_capacity)
{
	tet_mark.reserve(new_capacity);
	new_capacity <<= 2;
	tet_node.reserve(new_capacity);
	tet_neigh.reserve(new_capacity);
}

/**
 * @brief Reserve memory for new tetrahedra. It will consider reusing deleted
 * tetrahedra to store new tetrahedra.
 * @param inc_size number of new tetrahedra.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::reserveNewTets(size_t inc_size)
{
	if (inc_size > tet_deleted.size())
		reserveTets(sizeTets() + inc_size - tet_deleted.size());
}

/**
 * @brief Clear all data in the tetrahedra mesh.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::clear()
{
	clearVerts();
	clearTets();
}

/**
 * @brief Clear all vertices and related data in the tetrahedra mesh.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::clearVerts()
{
	verts   = std::vector<GPoint *>();
	inc_tet = std::vector<index_t>();
}

/**
 * @brief Clear all tetrahedra and related data in the tetrahedra mesh.
 */
template <typename Traits>
void TetrahedralMesh<Traits>::clearTets()
{
	// Clear the tetrahedra and related data
	tet_node    = std::vector<index_t>();
	tet_mark    = std::vector<uint32_t>();
	tet_neigh   = std::vector<index_t>();
	tet_deleted = std::vector<index_t>();
}

/**
 * @brief Check if the vertex is inside the circumsphere of the tetrahedron.
 * The checking process is divided into two cases:
 * (1) For a finite tetrahedron, directly apply the inSphere predicate;
 * (2) For an infinite tetrahedron, first check if the vertex is in the outer
 * half-space of the boundary face, and then check if it is inside the
 * circumcircle of the boundary face.
 * @param tet_idoff Tetrahedron's id offset
 * @param vid Vertex id
 * @return True if the vertex is inside the circumsphere, otherwise false
 */
template <typename Traits>
bool TetrahedralMesh<Traits>::vertexInTetSphere(index_t tet_idoff,
                                                index_t vid) const
{
	index_t        tet_id    = clipId(tet_idoff);
	const index_t *tet_nodes = &tetNode(tet_id);

	if (tet_nodes[3] == INFINITE_VERTEX)
	{
		// Infinite tetrahedron, containing a boundary face and the opposite
		// infinite vertex.

		// The circumsphere of an infinite tetrahedron is defined by the union of:
		// (a) the outer half-space defined by the supporting plane of the boundary
		// face (excluding the supporting plane) and (b) the boundary face itself.

		OMC_EXPENSIVE_ASSERT(!CollinearPoints3()(gpnt(tet_nodes[0]),
		                                         gpnt(tet_nodes[1]),
		                                         gpnt(tet_nodes[2])),
		                     "The boundary face is degenerate.");

		// We first check the position of the vertex relative to the supporting
		// plane of the boundary face.
		Sign ori = Orient3D()(gpnt(tet_nodes[0]), gpnt(tet_nodes[1]),
		                      gpnt(tet_nodes[2]), gpnt(vid));
		// If the vertex is not on the plane, it must be located either outside or
		// inside, indicating whether it is inside or outside the circumsphere.
		if (ori != Sign::ZERO)
			return ori == Sign::POSITIVE;

		// If the vertex is on the plane, we then check if it lies within the disk
		// defined by the circumcircle of the boundary triangle. This check is
		// equivalent to determining if it is within the circumsphere of the finite
		// neighboring tetrahedron.
		// OPT: The inSphere result is already calculated and stored in
		// tet_mark[getId(tetNeigh(tet_idoff+3))], right?
		const index_t nn[4] = {tet_nodes[0], tet_nodes[1], tet_nodes[2],
		                       tetNode(tetNeigh(tet_id + 3))};

		OMC_EXPENSIVE_ASSERT(
		  Orient3D()(gpnt(nn[0]), gpnt(nn[1]), gpnt(nn[2]), gpnt(nn[3])) ==
		    Sign::NEGATIVE,
		  "The neighboring tetrahedron is either degenerate or flipped.");

		return !vertexInTetSphere(nn, vid);
		// reverse the sign, since the order of the first three vertices is not
		// adjusted.
	}
	else
	{
		// For a finite tetrahedron, check the inSphere predicate.

		OMC_EXPENSIVE_ASSERT(Orient3D()(gpnt(tet_nodes[0]), gpnt(tet_nodes[1]),
		                                gpnt(tet_nodes[2]),
		                                gpnt(tet_nodes[3])) == Sign::POSITIVE,
		                     "The tetrahedron is either degenerate or flipped.");

		return vertexInTetSphere(tet_nodes, vid);
	}
}

/**
 * @brief Apply an inSphere predicate with symbolic perturbation to avoid
 * non-general configurations (five points co-spherical).
 * NOTE: The nodes must not contain infinite vertex.
 */
template <typename Traits>
bool TetrahedralMesh<Traits>::vertexInTetSphere(const index_t *node,
                                                index_t        vid) const
{
	Sign ori = InSphere()(gpnt(node[0]), gpnt(node[1]), gpnt(node[2]),
	                      gpnt(node[3]), gpnt(vid));
	if (ori != Sign::ZERO)
		return ori == Sign::POSITIVE;

	index_t nn[5] = {node[0], node[1], node[2], node[3], vid};
	ori           = symbolicPerturbation(nn);

	OMC_ASSERT(ori != Sign::ZERO, "symbolic perturbation failed.");
	return ori == Sign::POSITIVE;
}

/**
 * @brief Symbolic perturbation for inSphere predicate, based on the `simulation
 of simplicity` idea.
 * @see
 * - Diazzi, L., Panozzo, D., Vaxman, A. and Attene, M. Constrained Delaunay
 * Tetrahedrization: A Robust and Practical Approach. ACM Transactions on
 * Graphics, 42, 6 (2023), 1-15.
 * - Edelsbrunner, H. and Mücke, E. P. Simulation of simplicity: a technique
 * to cope with degenerate cases in geometric algorithms. ACM Transactions on
 * Graphics, 9, 1 (1990), 66-104.
 */
template <typename Traits>
Sign TetrahedralMesh<Traits>::symbolicPerturbation(index_t *indices) const
{
	int swaps = 0;
	int n     = 5;
	int count;
	// Bubble sort indices and count the number of swaps
	do
	{
		count = 0;
		n--;
		for (int i = 0; i < n; i++)
		{
			if (indices[i] > indices[i + 1])
			{
				std::swap(indices[i], indices[i + 1]);
				count++;
			}
		}
		swaps += count;
	} while (count);

	// Orientation test on the last four vertices (excluding the first vertex)
	Sign ori = Orient3D()(gpnt(indices[1]), gpnt(indices[2]), gpnt(indices[3]),
	                      gpnt(indices[4]));
	if (ori != Sign::ZERO)
		return (swaps % 2) ? reverse_sign(ori) : ori;

	// Orientation test on the vertices except the second vertex
	ori = Orient3D()(gpnt(indices[0]), gpnt(indices[2]), gpnt(indices[3]),
	                 gpnt(indices[4]));
	return (swaps % 2) ? ori : reverse_sign(ori);
}

} // namespace OMC