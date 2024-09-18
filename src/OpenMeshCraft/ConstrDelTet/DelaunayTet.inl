#pragma once

#include "DelaunayTet.h"
#include "Utils.h"

namespace OMC {

template <typename Traits>
DelaunayTet<Traits>::DelaunayTet(const std::vector<GPoint *> &_in_verts,
                                 std::vector<index_t>        &_out_tets)
  : verts(_in_verts)
  , tet_node(_out_tets)
{
}

template <typename Traits>
void DelaunayTet<Traits>::tetrahedralize()
{
	// TODO sort vertices to tetrahedralize it faster.

	index_t init_k, init_l;
	initialize(init_k, init_l);

	index_t      curr_tet = 0;
	const size_t n_verts  = sizeVerts();
	for (index_t i = 2; i < n_verts; i++)
		if (i != init_k && i != init_l)
			insertVertex(i, curr_tet);

	markInfiniteTetsDeleted();

	removeDeletedTets();
}

/**
 * @brief Initialize an initial tetrahedron with positive volume.
 * @param k The third vertex in the initial tetrahedron.
 * @param l The fourth vertex in the initial tetrahedron.
 */
template <typename Traits>
void DelaunayTet<Traits>::initialize(index_t &k, index_t &l)
{
	// clear all auxiliary data
	clear();

	// Size of the input vertices
	const size_t n = sizeVerts();

	// Goal: find four non-coplanar vertices to form the initial tetrahedron.
	// Pre-condition: no coincident vertices exist.
	// The pre-condition is satisfied by running cleanMesh before Delaunay
	// tetrahedralization.

	// Indices of the four vertices
	index_t i = 0, j = 1;
	k = InvalidIndex, l = InvalidIndex;
	// Four vertices
	const EPoint &vi = epnt(i), &vj = epnt(j);
	// Orientation of the four vertices (i.e., the sign of the tetrahedron volume
	// formed by the four vertices)
	Sign          ori = Sign::ZERO;

	// Traversal all vertices
	for (k = 2; ori == Sign::ZERO && k < n - 1; k++)
	{
		const EPoint &vk = epnt(k);
		// Find the third vertex to form a valid triangle
		if (CollinearPoints3D()(vi, vj, vk))
			continue;
		// Find the fourth vertex to form a valid tetrahedron
		for (l = k + 1; ori == Sign::ZERO && l < n; l++)
		{
			const EPoint &vl = epnt(l);
			// Since the input GPoints are always an EPoint, we will convert them.
			ori              = Orient3D()(vi, vj, vk, vl);
		}
	}
	// Decrease the indices by 1 to offset the increment from the for loop
	k -= 1;
	l -= 1;

	OMC_ASSERT(ori == Sign::POSITIVE || ori == Sign::NEGATIVE,
	           "[OpenMeshCraft DelaunayTet] Input vertices do not define a "
	           "tetrahedron with non-zero volume.");

	if (ori == Sign::NEGATIVE)
		std::swap(i, j);

	// All boundary triangular face is connected to an infinite vertex,
	// forming a tetrahedron with infinite volume.
	// These tetrahedra containing infinite vertex are outer tetrahedra.
	const index_t base_tet[]   = {l, k, j, i,
	                              l, j, k, INFINITE_VERTEX,
	                              l, k, i, INFINITE_VERTEX,
	                              l, i, j, INFINITE_VERTEX,
	                              k, j, i, INFINITE_VERTEX};
	// 1. The neighbor of an infinite vertex in any outer tetrahedron is the
	// opposite node in the adjacent inner tetrahedron.
	// 2. The neighbor of a finite vertex in an outer tetrahedron is the opposite
	// node on the opposite face of the boundary.
	const index_t base_neigh[] = {19, 15, 11, 7, /*INFINITE_VERTEX*/
	                              18, 10, 13, 3, /*i*/
	                              17, 14, 5,  2, /*j*/
	                              16, 6,  9,  1, /*k*/
	                              12, 8,  4,  0 /*l*/};

	reserveTets(n);
	resizeTets(5);
	std::memcpy(&tetNode(0), base_tet, 5 * 4 * sizeof(index_t));
	std::memcpy(&tetNeigh(0), base_neigh, 5 * 4 * sizeof(index_t));

	// set the vertex-(one_of_the)incident-tetrahedron relation
	inc_tet.resize(n);
	inc_tet[i] = 0;
	inc_tet[j] = 0;
	inc_tet[k] = 0;
	inc_tet[l] = 0;
}

/**
 * @brief Incrementally inserts vertices into the Delaunay tetrahedralization.
 * @details When inserting a vertex, it first collects all tetrahedra
 * whose circumsphere contains the vertex and replaces them with a star of new
 * tetrahedra originating from the vertex.
 * @param vid The vertex to be inserted, represented in vertex index.
 * @param tet One newly constructed tetrahedron created during the insertion of
 * the last vertex, represented in `idoff`.
 */
template <typename Traits>
void DelaunayTet<Traits>::insertVertex(const index_t vid, index_t &tet)
{
	// ==========================================================================
	// Step 1: Walking
	// Traverse the tetrahedral mesh from `tet` to the tetrahedron containing
	// `vid`.

	if (tetNode(tet + 3) == INFINITE_VERTEX) // Check if we are in an infinite tet
		tet = clipId(tetNeigh(tet + 3));       // then move to the finite neighbor.

	// Walk step by step to the target tetrahedron where `vid` is located.
	// The walking direction is determined by the orientation of `vid` with
	// respect to the current tetrahedron.

	// Entering face at each step (it actually stores the opposite node's
	// offset of the entering face.)
	index_t entering_face = 4;
	while (true)
	{
		const index_t *curr_nodes = &tetNode(tet);
		index_t        off        = 0;
		for (; off < 4; off++)
		{
			if (off == entering_face) // skip the entering face
				continue;
			OMC_EXPENSIVE_ASSERT(!CollinearPoints3D()(epnt(curr_nodes[tetON1(off)]),
			                                          epnt(curr_nodes[tetON2(off)]),
			                                          epnt(curr_nodes[tetON3(off)])),
			                     "Current face is degenerate.");

			// check the orientation of `vid` with respect to the current face
			if (Orient3D()(
			      epnt(curr_nodes[tetON1(off)]), epnt(curr_nodes[tetON2(off)]),
			      epnt(curr_nodes[tetON3(off)]), epnt(vid)) == Sign::NEGATIVE)
			{
				index_t neighbor_idoff = tetNeigh(tet + off);

				tet           = clipId(neighbor_idoff);
				entering_face = clipOff(neighbor_idoff);
				break;
			}
		}
		// `vid` is inside the current tet, we have stepped into the target.
		if (off == 4)
		{
			OMC_EXPENSIVE_ASSERT(
			  InSphere()(epnt(tetNode(tet)), epnt(tetNode(tet + 1)),
			             epnt(tetNode(tet + 2)), epnt(tetNode(tet + 3)),
			             epnt(vid)) == Sign::POSITIVE,
			  "`vid` is not inside the current tetrahedron's circumsphere.");
			break;
		}
		// if we have stepped into an infinite tetrahedron, it is the target too.
		if (tetNode(tet + 3) == INFINITE_VERTEX)
			break;
	}

	// ==========================================================================
	// Step 2: Cavity
	// Gather all tetrahedra whose circumsphere contains `v_id` and remove them
	// to create a cavity.

	AuxVector64<index_t> cavity_corners;

	const size_t first = tet_deleted.size();
	pushMarkDeletedTet(tet);

	// Traverse all deleted tetrahedra one by one
	for (index_t i = first; i < tet_deleted.size(); i++)
	{
		// Traverse a deleted tetrahedron's neighbors
		for (index_t j = 0; j < 4; j++)
		{
			index_t neigh_idoff = tetNeigh(tet_deleted[i] + j); // get the neighbor
			if (isNoMarks(neigh_idoff))
			{
				// if the neighbor has not been visited.
				if (vertexInTetSphere(neigh_idoff, vid))
				{
					// if the vertex is inside the circumsphere of the neighbor.
					pushMarkDeletedTet(neigh_idoff);
				}
				else
				{
					mark(neigh_idoff, TET_MARK::VISITED);
					cavity_corners.push_back(neigh_idoff);
				}
			}
			else if (isMarked(neigh_idoff, TET_MARK::VISITED))
			{
				// the neighbor has been visited but is not deleted (i.e. its
				// circumsphere does not contain the vertex), thus the shared face is
				// the boundary of the cavity, so we record the node opposite to the
				// shared face (neigh_idoff) as a cavity corner.
				cavity_corners.push_back(neigh_idoff);
			}
#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
			else if (isMarked(neigh_idoff, TET_MARK::TO_DELETE))
			{
				OMC_ASSERT(std::find(tet_deleted.begin(), tet_deleted.end(),
				                     clipId(neigh_idoff)) != tet_deleted.end(),
				           "A deleted tetrahedron is not recorded in tet_deleted.");
			}
			else
			{
				OMC_ASSERT(false, "Impossible case.");
			}
#endif
		}
	}

	// ==========================================================================
	// Step 3: Filling
	// Fill the cavity by connecting `v_id` to the cavity's boundary and establish
	// correct neighbor and incident relationships.

	static const index_t fi[4][3] = {{2, 1, 3}, {0, 2, 3}, {1, 0, 3}, {0, 1, 2}};

	// Resize the mesh to host the new tets
	index_t newpos = tet_node.size();
	if (cavity_corners.size() > tet_deleted.size())
		incSizeTets(cavity_corners.size() - tet_deleted.size());

	// Create new tets
	index_t new_tet_idoff = InvalidIndex;
	for (index_t corner : cavity_corners)
	{
		clearMark(corner);
		// Find position to put new tet
		if (tet_deleted.empty())
		{
			new_tet_idoff = newpos;
			newpos += 4;
		}
		else
		{
			new_tet_idoff = tet_deleted.back();
			tet_deleted.pop_back();

			OMC_EXPENSIVE_ASSERT(isMarked(new_tet_idoff, TET_MARK::TO_DELETE),
			                     "The tet is not marked to be deleted.");
		}

		// create the new tet
		index_t corner_id          = clipId(corner);
		index_t corner_off         = clipOff(corner);
		// -- put the `vid` at the first position
		tetNode(new_tet_idoff)     = vid;
		// -- put the opposite face at the last three positions and correct the
		// orientation by the map `fi`
		tetNode(new_tet_idoff + 1) = tetNode(corner_id + fi[corner_off][0]);
		tetNode(new_tet_idoff + 2) = tetNode(corner_id + fi[corner_off][1]);
		tetNode(new_tet_idoff + 3) = tetNode(corner_id + fi[corner_off][2]);

		OMC_EXPENSIVE_ASSERT(
		  tetNode(new_tet_idoff + 3) == INFINITE_VERTEX ||
		    Orient3D()(epnt(tetNode(new_tet_idoff)),
		               epnt(tetNode(new_tet_idoff + 1)),
		               epnt(tetNode(new_tet_idoff + 2)),
		               epnt(tetNode(new_tet_idoff + 3))) == Sign::POSITIVE,
		  "The newly generated tetrahedron is either degenerate or flipped.");

		// build the neighbor relationship (`vid` and `corner` is a pair of
		// neighbors).
		tetNeigh(new_tet_idoff)     = corner;
		tetNeigh(corner)            = new_tet_idoff;
		// remaining neighbors will be generated later
		tetNeigh(new_tet_idoff + 1) = InvalidIndex;
		tetNeigh(new_tet_idoff + 2) = InvalidIndex;
		tetNeigh(new_tet_idoff + 3) = InvalidIndex;

		if (tetNode(new_tet_idoff + 3) != INFINITE_VERTEX)
		{
			index_t tet_id                      = getId(new_tet_idoff);
			inc_tet[vid]                        = tet_id;
			inc_tet[tetNode(new_tet_idoff + 1)] = tet_id;
			inc_tet[tetNode(new_tet_idoff + 2)] = tet_id;
			inc_tet[tetNode(new_tet_idoff + 3)] = tet_id;
		}
		clearMark(new_tet_idoff);
	}

	// Restore the connectivity within the cavity

	// Begin at tetrahedron containing `c` and traverse around the given edge as
	// long as the adjacencies are well-defined. If an invalid adjacency is
	// encountered, we arrive at the tetrahedron adjacent to the tetraheron
	// containing `o`, thus we can fix the invalid adajcency.
	auto seekAndSetMutualAdjacency = [this](index_t o0, index_t o1, index_t o2,
	                                        index_t /*corner*/ c,
	                                        index_t /*tet*/    o)
	{
		const index_t v0 = tetNode(o + o0), v1 = tetNode(o + o1),
		              v2 = tetNode(o + o2);
		o += o0;

		// find `v0` in the neighboring tetrahedron and save its idoff in `c`.
		c = clipId(c);
		while (tetNode(c) != v0)
			c++;

		// Traverse around the edge v1-v2 as long as the adjacencies are
		// well-defined; we will encounter the newly generated tetrahedron that is
		// adjacent to tetrahedron `o` at the edge v1-v2 when the loop is end.
		while (tetNeigh(c) != InvalidIndex)
		{
			// Step into next adjacent tetrahedron and arrive at `w`.
			c               = tetNeigh(c);
			const index_t w = tetNode(c);
			// Find node that is not equal to `v1`, `v2` or `w`.
			c               = clipId(c);
			while (tetNode(c) == v1 || tetNode(c) == v2 || tetNode(c) == w)
				c++;
		}
		// encounter the ill-defined adjacency, fix it and exit.
		tetNeigh(c) = o;
		tetNeigh(o) = c;
	};

	for (index_t c : cavity_corners) // for each corner `c`
	{
		const index_t  o = tetNeigh(c);  // tet `o` originating from `vid`
		const index_t *n = &tetNeigh(o); // neighbors `n` of this tet

		OMC_EXPENSIVE_ASSERT(
		  tetNode(o) == vid,
		  "The neighboring tetrahedron does not originate from `vid`");
		OMC_EXPENSIVE_ASSERT(n[0] == c, "The neighbor relationship is incorrect.");

		// fix neighbors
		if (n[1] == InvalidIndex)
			seekAndSetMutualAdjacency(1, 2, 3, c, o);
		if (n[2] == InvalidIndex)
			seekAndSetMutualAdjacency(2, 1, 3, c, o);
		if (n[3] == InvalidIndex)
			seekAndSetMutualAdjacency(3, 1, 2, c, o);
	}

	tet = tetNeigh(cavity_corners.back());
}

/**
 * @brief Marks tetrahedrons containing infinite vertices as deleted.
 */
template <typename Traits>
void DelaunayTet<Traits>::markInfiniteTetsDeleted()
{
	const size_t n = sizeTets();
	for (index_t id = 0; id < n; id++)
	{
		index_t  idoff = id << 2;
		index_t *node  = &tetNode(idoff);
		if (node[0] == INFINITE_VERTEX || node[1] == INFINITE_VERTEX ||
		    node[2] == INFINITE_VERTEX || node[3] == INFINITE_VERTEX)
		{
			pushMarkDeletedTet(idoff);
		}
	}
}

template <typename Traits>
void DelaunayTet<Traits>::removeDeletedTets()
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
				tet_neigh[n]     = t + i;
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
 * @brief Push the deleted tetrahedron into tet_deleted, and mark it as deleted.
 * @param idoff tetrahedron's idoff = tet_id * 4 + node_offset
 */
template <typename Traits>
void DelaunayTet<Traits>::pushMarkDeletedTet(index_t idoff)
{
	tet_deleted.push_back(clipId(idoff));
	mark(idoff, TET_MARK::TO_DELETE);
}

template <typename Traits>
void DelaunayTet<Traits>::resizeTets(size_t new_size)
{
	tet_mark.resize(new_size);
	new_size <<= 2;
	tet_node.resize(new_size);
	tet_neigh.resize(new_size);
}

template <typename Traits>
void DelaunayTet<Traits>::reserveTets(size_t new_capacity)
{
	tet_mark.reserve(new_capacity);
	new_capacity <<= 2;
	tet_node.reserve(new_capacity);
	tet_neigh.reserve(new_capacity);
}

template <typename Traits>
void DelaunayTet<Traits>::incSizeTets(size_t inc_size)
{
	resizeTets(sizeTets() + inc_size);
}

template <typename Traits>
void DelaunayTet<Traits>::clear()
{
	tet_node  = std::vector<index_t>();
	tet_mark  = std::vector<uint32_t>();
	tet_neigh = std::vector<index_t>();
	inc_tet   = std::vector<index_t>();
}

template <typename Traits>
bool DelaunayTet<Traits>::vertexInTetSphere(index_t tet_idoff,
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
 */
template <typename Traits>
bool DelaunayTet<Traits>::vertexInTetSphere(const index_t *node,
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
Sign DelaunayTet<Traits>::symbolicPerturbation(index_t *indices) const
{
	int swaps = 0;
	int n     = 5;
	int count;
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

	Sign ori = Orient3D()(epnt(indices[1]), epnt(indices[2]), epnt(indices[3]),
	                      epnt(indices[4]));
	if (ori != Sign::ZERO)
		return (swaps % 2) ? reverse_sign(ori) : ori;

	ori = Orient3D()(epnt(indices[0]), epnt(indices[2]), epnt(indices[3]),
	                 epnt(indices[4]));
	return (swaps % 2) ? ori : reverse_sign(ori);
}

} // namespace OMC