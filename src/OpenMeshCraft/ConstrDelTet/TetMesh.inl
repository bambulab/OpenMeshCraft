#pragma once

#include "TetMesh.h"

namespace OMC {

template <typename Traits>
void TetrahedralMesh<Traits>::initialize(const std::vector<GPoint *> &points)
{
	verts = points;
	inc_tet.resize(verts.size(), InvalidIndex);
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
		clearMark(new_tet_idoff);
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
			clearMark(*iter);
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

		OMC_EXPENSIVE_ASSERT(!CollinearPoints3D()(epnt(tet_nodes[0]),
		                                          epnt(tet_nodes[1]),
		                                          epnt(tet_nodes[2])),
		                     "The boundary face is degenerate.");

		// We first check the position of the vertex relative to the supporting
		// plane of the boundary face.
		Sign ori = Orient3D()(epnt(tet_nodes[0]), epnt(tet_nodes[1]),
		                      epnt(tet_nodes[2]), epnt(vid));
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
		  Orient3D()(epnt(nn[0]), epnt(nn[1]), epnt(nn[2]), epnt(nn[3])) ==
		    Sign::NEGATIVE,
		  "The neighboring tetrahedron is either degenerate or flipped.");

		return !vertexInTetSphere(nn, vid);
		// reverse the sign, since the order of the first three vertices is not
		// adjusted.
	}
	else
	{
		// For a finite tetrahedron, check the inSphere predicate.

		OMC_EXPENSIVE_ASSERT(Orient3D()(epnt(tet_nodes[0]), epnt(tet_nodes[1]),
		                                epnt(tet_nodes[2]),
		                                epnt(tet_nodes[3])) == Sign::POSITIVE,
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
	Sign ori = InSphere()(epnt(node[0]), epnt(node[1]), epnt(node[2]),
	                      epnt(node[3]), epnt(vid));
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
	Sign ori = Orient3D()(epnt(indices[1]), epnt(indices[2]), epnt(indices[3]),
	                      epnt(indices[4]));
	if (ori != Sign::ZERO)
		return (swaps % 2) ? reverse_sign(ori) : ori;

	// Orientation test on the vertices except the second vertex
	ori = Orient3D()(epnt(indices[0]), epnt(indices[2]), epnt(indices[3]),
	                 epnt(indices[4]));
	return (swaps % 2) ? ori : reverse_sign(ori);
}

} // namespace OMC