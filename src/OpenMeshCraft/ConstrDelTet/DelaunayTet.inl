#pragma once

#include "DelaunayTet.h"

namespace OMC {

template <typename Traits>
void DelaunayTet<Traits>::tetrahedralize()
{
	// TODO sort vertices to tetrahedralize it faster.

	index_t init_k, init_l;
	initialize(init_k, init_l);

	index_t      curr_tet = 0;
	const size_t n_verts  = mesh.sizeVerts();
	for (index_t i = 2; i < n_verts; i++)
		if (i != init_k && i != init_l)
			insertVertex(i, curr_tet);

	mesh.removeDeletedTets();
}

/**
 * @brief Initialize an initial tetrahedron with positive volume.
 * @param k The third vertex in the initial tetrahedron.
 * @param l The fourth vertex in the initial tetrahedron.
 */
template <typename Traits>
void DelaunayTet<Traits>::initialize(index_t &k, index_t &l)
{
	// clear all tetrahedra in the mesh.
	mesh.clearTets();

	// Size of the input vertices
	const size_t n = mesh.sizeVerts();

	// GOAL: find four non-coplanar vertices to form the initial tetrahedron.
	// Pre-condition: no coincident vertices exist, which is satisfied by running
	// cleanMesh before Delaunay tetrahedralization.

	// Indices of the four vertices
	index_t i = 0, j = 1;
	k = InvalidIndex, l = InvalidIndex;
	// Four vertices
	const GPoint &vi = mesh.gpnt(i), &vj = mesh.gpnt(j);
	// Orientation of the four vertices (i.e., the sign of the tetrahedron volume
	// formed by the four vertices)
	Sign          ori = Sign::ZERO;

	// Traversal all vertices
	for (k = 2; ori == Sign::ZERO && k < n - 1; k++)
	{
		const GPoint &vk = mesh.gpnt(k);
		// Find the third vertex to form a valid triangle
		if (CollinearPoints3()(vi, vj, vk))
			continue;
		// Find the fourth vertex to form a valid tetrahedron
		for (l = k + 1; ori == Sign::ZERO && l < n; l++)
		{
			const GPoint &vl = mesh.gpnt(l);
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
	                              l, j, k, TetMesh::INFINITE_VERTEX,
	                              l, k, i, TetMesh::INFINITE_VERTEX,
	                              l, i, j, TetMesh::INFINITE_VERTEX,
	                              k, j, i, TetMesh::INFINITE_VERTEX};
	// 1. The neighbor of an infinite vertex in any outer tetrahedron is the
	// opposite node in the adjacent inner tetrahedron.
	// 2. The neighbor of a finite vertex in an outer tetrahedron is the opposite
	// node on the opposite face of the boundary.
	const index_t base_neigh[] = {19, 15, 11, 7, /*INFINITE_VERTEX*/
	                              18, 10, 13, 3, /*i*/
	                              17, 14, 5,  2, /*j*/
	                              16, 6,  9,  1, /*k*/
	                              12, 8,  4,  0 /*l*/};

	// create five tetrahedra, one is finite and the other four are infinite.
	// (WARN: rely on internal implementation, not the interface)
	mesh.reserveTets(n);
	mesh.resizeTets(5);
	std::memcpy(&mesh.tetNode(0), base_tet, 5 * 4 * sizeof(index_t));
	std::memcpy(&mesh.tetNeigh(0), base_neigh, 5 * 4 * sizeof(index_t));

	// set the vertex-(one_of_the)incident-tetrahedron relation
	mesh.incTet(i) = 0;
	mesh.incTet(j) = 0;
	mesh.incTet(k) = 0;
	mesh.incTet(l) = 0;
}

/**
 * @brief Incrementally inserts vertices into the Delaunay tetrahedralization.
 * @details When inserting a vertex, it first collects all tetrahedra
 * whose circumsphere contains the vertex and replaces them with a star of new
 * tetrahedra originating from the vertex. Old tetrahedra are marked as deleted.
 * @param vid The vertex to be inserted, represented in vertex index.
 * @param tet One newly constructed tetrahedron created during the insertion of
 * the last vertex, represented in `idoff`.
 * @note Rely on mark `TOUCHED` to avoid redundant operations. Not thread safe.
 */
template <typename Traits>
void DelaunayTet<Traits>::insertVertex(const index_t vid, index_t &tet)
{
	// ==========================================================================
	// Step 1: Walking
	// Traverse the tetrahedral mesh from `tet` to the tetrahedron containing
	// `vid`.

	// Check if we are in an infinite tet
	if (mesh.tetNode(tet + 3) == TetMesh::INFINITE_VERTEX)
		// then move to the finite neighbor.
		tet = TetMesh::clipId(mesh.tetNeigh(tet + 3));

	// Walk step by step to the target tetrahedron where `vid` is located.
	// The walking direction is determined by the orientation of `vid` with
	// respect to the current tetrahedron.

	// Entering face at each step (it actually stores the opposite node's
	// offset of the entering face.)
	index_t entering_face = 4;
	while (true)
	{
		index_t off = 0;
		for (; off < 4; off++)
		{
			if (off == entering_face) // skip the entering face
				continue;
			OMC_EXPENSIVE_ASSERT(
			  !CollinearPoints3()(
			    mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON1(off))),
			    mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON2(off))),
			    mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON3(off)))),
			  "Current face is degenerate.");

			// check the orientation of `vid` with respect to the current face
			if (Orient3D()(mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON1(off))),
			               mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON2(off))),
			               mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON3(off))),
			               mesh.gpnt(vid)) == Sign::NEGATIVE)
			{
				index_t neighbor_idoff = mesh.tetNeigh(tet + off);
				// we are stepping into the neighbor tetrahedron.
				tet                    = TetMesh::clipId(neighbor_idoff);
				entering_face          = TetMesh::clipOff(neighbor_idoff);
				break; // break the for loop
			}
		}
		// `vid` is inside the current tet, we have stepped into the target.
		if (off == 4)
			break; // break the while loop
		// if we have stepped into an infinite tetrahedron, it is the target too.
		if (!mesh.isFiniteTet(tet))
			break; // break the while loop
	}

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// clang-format off
	if (mesh.isFiniteTet(tet))
	{
		OMC_ASSERT(
		  !(LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 0))) ||
		    LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 1))) ||
		    LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 2))) ||
		    LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 3)))),
		  "The inserted vertex coincides with an existing vertex.");
		Sign ori[4];
		for (index_t i = 0; i < 4; i++)
		{
		 ori[i] = Orient3D()(mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON1(i))),
		                     mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON2(i))),
		                     mesh.gpnt(mesh.tetNode(tet + TetMesh::tetON3(i))), mesh.gpnt(vid));
		 OMC_ASSERT(ori[i] >= Sign::ZERO, "The vertex is not inside the target finite tetrahedron.");
		}
	}
	else
	{
		OMC_ASSERT(
		  !(LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 0))) ||
		    LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 1))) ||
		    LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(mesh.tetNode(tet + 2)))),
		  "The inserted vertex coincides with an existing vertex.");
		OMC_ASSERT(Orient3D()(mesh.gpnt(mesh.tetNode(tet)), mesh.gpnt(mesh.tetNode(tet + 1)), mesh.gpnt(mesh.tetNode(tet + 2)), mesh.gpnt(vid)) == Sign::POSITIVE,
		           "The vertex is not inside the target infinite tetrahedron.");
	}
	OMC_ASSERT(mesh.vertexInTetSphere(tet, vid),
	           "The vertex is not inside the target tetrahedron's circumsphere.");
	// clang-format on
#endif

	// ==========================================================================
	// Step 2: Cavity
	// Gather all tetrahedra whose circumsphere contains `v_id` and remove them
	// to create a cavity.

	AuxVector64<index_t> cavity_tets;
	AuxVector64<index_t> cavity_corners;

	mesh.markTetAsDeleted(tet);
	cavity_tets.push_back(TetMesh::clipId(tet));

	// Traverse all newly deleted tetrahedra one by one
	for (index_t i = 0; i < cavity_tets.size(); i++)
	{
		// Traverse a deleted tetrahedron's neighbors
		for (index_t j = 0; j < 4; j++)
		{
			// get the neighbor
			index_t neigh_idoff = mesh.tetNeigh(cavity_tets[i] + j);
			if (mesh.isTetUnmarked(neigh_idoff))
			{
				// if the neighbor has not been touched...
				if (mesh.vertexInTetSphere(neigh_idoff, vid))
				{
					// if the vertex is inside the circumsphere of the neighbor,
					// the neighbor belongs to cavity, so remove it.
					mesh.markTetAsDeleted(neigh_idoff);
					cavity_tets.push_back(TetMesh::clipId(neigh_idoff));
				}
				else
				{
					// if the vertex is outside the circumsphere of the neighbor,
					// the shared face is the boundary of the cavity, so we record it.
					mesh.mark(neigh_idoff, TetMesh::TET_MARK::TOUCHED);
					cavity_corners.push_back(neigh_idoff);
				}
			}
			else if (mesh.isMarked(neigh_idoff, TetMesh::TET_MARK::TOUCHED))
			{
				// the neighbor has been touched but is not deleted (i.e. its
				// circumsphere does not contain the vertex), thus the shared face is
				// the boundary of the cavity, so we record the node opposite to the
				// shared face (neigh_idoff) as a cavity corner.
				cavity_corners.push_back(neigh_idoff);
			}
#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
			else if (mesh.isMarked(neigh_idoff, TetMesh::TET_MARK::TO_DELETE))
			{
				OMC_ASSERT(std::find(cavity_tets.begin(), cavity_tets.end(),
				                     TetMesh::clipId(neigh_idoff)) != cavity_tets.end(),
				           "A deleted tetrahedron is not recorded in cavity.");
			}
			else
			{
				OMC_ASSERT(false, "Impossible case.");
			}
#endif
		}
	}

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
	// Check if the inserted vertex is coincident with the existing vertices.
	boost::container::flat_set<index_t> cavity_verts;
	// Collect vertices of the cavity
	for (index_t tet_idoff : cavity_tets)
	{
		for (index_t j = 0; j < 4; j++)
			if (is_valid_idx(mesh.tetNode(tet_idoff + j)))
				cavity_verts.insert(mesh.tetNode(tet_idoff + j));
	}
	// Check coincident vertices
	for (index_t cavity_vid : cavity_verts)
	{
		OMC_ASSERT(!LessThan3D().coincident(mesh.gpnt(vid), mesh.gpnt(cavity_vid)),
		           "Coincident vertices.");
	}
#endif

	// ==========================================================================
	// Step 3: Filling
	// Fill the cavity by connecting `v_id` to the cavity's boundary and establish
	// correct neighbor and incident relationships.

	static const index_t fi[4][3] = {{2, 1, 3}, {0, 2, 3}, {1, 0, 3}, {0, 1, 2}};

	// Resize the mesh to host the new tets
	AuxVector64<index_t> new_tets(cavity_corners.size());
	mesh.newTets(cavity_corners.size(), new_tets);

	// Create a new tet for each cavity corner.
	for (index_t corner : cavity_corners)
	{
		mesh.unmark(corner, TetMesh::TET_MARK::TOUCHED);

		// get the idoff of the new tet
		index_t new_idoff = new_tets.back();
		new_tets.pop_back();

		// create the new tet
		index_t corner_id           = TetMesh::clipId(corner);
		index_t corner_off          = TetMesh::clipOff(corner);
		// -- put the `vid` at the first position
		mesh.tetNode(new_idoff)     = vid;
		// -- put the opposite face at the last three positions and correct the
		// orientation by the map `fi`
		mesh.tetNode(new_idoff + 1) = mesh.tetNode(corner_id + fi[corner_off][0]);
		mesh.tetNode(new_idoff + 2) = mesh.tetNode(corner_id + fi[corner_off][1]);
		mesh.tetNode(new_idoff + 3) = mesh.tetNode(corner_id + fi[corner_off][2]);

#ifdef OMC_ENABLE_EXPENSIVE_ASSERT
		if (mesh.isFiniteTet(new_idoff))
		{
			Sign tet_volume = Orient3D()(mesh.gpnt(mesh.tetNode(new_idoff)),
			                             mesh.gpnt(mesh.tetNode(new_idoff + 1)),
			                             mesh.gpnt(mesh.tetNode(new_idoff + 2)),
			                             mesh.gpnt(mesh.tetNode(new_idoff + 3)));
			OMC_ASSERT(tet_volume == Sign::POSITIVE,
			           "The newly generated tetrahedron has {} volume.",
			           static_cast<int>(tet_volume));
		}
#endif

		// build the neighbor relationship (`vid` and `corner` is a pair of
		// neighbors).
		mesh.tetNeigh(new_idoff)     = corner;
		mesh.tetNeigh(corner)        = new_idoff;
		// remaining neighbors will be generated later
		mesh.tetNeigh(new_idoff + 1) = InvalidIndex;
		mesh.tetNeigh(new_idoff + 2) = InvalidIndex;
		mesh.tetNeigh(new_idoff + 3) = InvalidIndex;

		if (mesh.tetNode(new_idoff + 3) != TetMesh::INFINITE_VERTEX)
		{
			index_t tet_id                           = TetMesh::getId(new_idoff);
			mesh.incTet(vid)                         = tet_id;
			mesh.incTet(mesh.tetNode(new_idoff + 1)) = tet_id;
			mesh.incTet(mesh.tetNode(new_idoff + 2)) = tet_id;
			mesh.incTet(mesh.tetNode(new_idoff + 3)) = tet_id;
		}
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
		const index_t v0 = mesh.tetNode(o + o0), v1 = mesh.tetNode(o + o1),
		              v2 = mesh.tetNode(o + o2);
		o += o0;

		// find `v0` in the neighboring tetrahedron and save its idoff in `c`.
		c = TetMesh::clipId(c);
		while (mesh.tetNode(c) != v0)
			c++;

		// Traverse around the edge v1-v2 as long as the adjacencies are
		// well-defined; we will encounter the newly generated tetrahedron that is
		// adjacent to tetrahedron `o` at the edge v1-v2 when the loop is end.
		while (mesh.tetNeigh(c) != InvalidIndex)
		{
			// Step into next adjacent tetrahedron and arrive at `w`.
			c               = mesh.tetNeigh(c);
			const index_t w = mesh.tetNode(c);
			// Find node that is not equal to `v1`, `v2` or `w`.
			c               = TetMesh::clipId(c);
			while (mesh.tetNode(c) == v1 || mesh.tetNode(c) == v2 ||
			       mesh.tetNode(c) == w)
				c++;
		}
		// encounter the ill-defined adjacency, fix it and exit.
		mesh.tetNeigh(c) = o;
		mesh.tetNeigh(o) = c;
	};

	for (index_t c : cavity_corners) // for each corner `c`
	{
		const index_t o = mesh.tetNeigh(c); // tet `o` originating from `vid`

		OMC_EXPENSIVE_ASSERT(
		  mesh.tetNode(o) == vid,
		  "The neighboring tetrahedron does not originate from `vid`");
		OMC_EXPENSIVE_ASSERT(mesh.tetNeigh(o) == c,
		                     "The neighbor relationship is incorrect.");

		// fix neighbors
		if (mesh.tetNeigh(o + 1) == InvalidIndex)
			seekAndSetMutualAdjacency(1, 2, 3, c, o);
		if (mesh.tetNeigh(o + 2) == InvalidIndex)
			seekAndSetMutualAdjacency(2, 1, 3, c, o);
		if (mesh.tetNeigh(o + 3) == InvalidIndex)
			seekAndSetMutualAdjacency(3, 1, 2, c, o);
	}

	tet = mesh.tetNeigh(cavity_corners.back());
}

template <typename Traits>
bool DelaunayTet<Traits>::verify() const
{
	for (index_t id = 0; id < mesh.sizeTets() * 4; id += 4)
	{
		// skip the infinite tet and deleted tet
		if (!mesh.isFiniteTet(id) ||
		    mesh.isMarked(id, TetMesh::TET_MARK::TO_DELETE))
			continue;

		if (!verifyVolume(id) || !verifyNeighbor(id))
			return false;
	}

	for (index_t vid = 0; vid < mesh.sizeVerts(); vid++)
	{
		if (!verifyDelaunay(vid))
			return false;
	}

	return true;
}

template <typename Traits>
bool DelaunayTet<Traits>::localVerify(index_t vid) const
{
	AuxVector64<index_t> tets;
	mesh.VT(vid, tets);
	for (index_t tet_idoff : tets)
	{
		if (!verifyVolume(tet_idoff) || !verifyNeighbor(tet_idoff))
			return false;
	}

	if (!verifyDelaunay(vid))
		return false;

	return true;
}

/**
 * @brief Verifies if the tetrahedron specified by the given index has a
 * positive volume.
 * @param tet_idoff The index offset of the tetrahedron to be verified.
 * @return true if the tetrahedron has a positive volume, false otherwise.
 */
template <typename Traits>
bool DelaunayTet<Traits>::verifyVolume(index_t tet_idoff) const
{
	if (Orient3D()(mesh.gpnt(mesh.tetNode(tet_idoff)),
	               mesh.gpnt(mesh.tetNode(tet_idoff + 1)),
	               mesh.gpnt(mesh.tetNode(tet_idoff + 2)),
	               mesh.gpnt(mesh.tetNode(tet_idoff + 3))) != Sign::POSITIVE)
	{
		OMC_ASSERT(false, "The tetrahedron {} has non-positive volume.",
		           tet_idoff / 4);
		return false;
	}
	return true;
}

/**
 * @brief Verifies if the tetrahedron's neighbors are well-connected.
 * @param tet_idoff The index offset of the tetrahedron to be verified.
 * @return true if neighbors are well-connected, false otherwise.
 */
template <typename Traits>
bool DelaunayTet<Traits>::verifyNeighbor(index_t tet_id) const
{
	for (index_t off = 0; off < 4; off++)
	{
		index_t idoff       = tet_id + off;
		index_t neigh_idoff = mesh.tetNeigh(idoff);
		if (neigh_idoff == InvalidIndex)
			continue;
		// the tet's neighbor's neighbor should be the tet itself
		if (mesh.tetNeigh(neigh_idoff) != idoff)
		{
			OMC_ASSERT(
			  false, "The tetrahedron {} and its neighbor {} are not well-connected.",
			  tet_id >> 2, TetMesh::clipId(neigh_idoff) >> 2);
			return false;
		}
		// two neighbors should have a common face with correct orientation
		index_t                neigh_id  = TetMesh::clipId(neigh_idoff);
		index_t                neigh_off = TetMesh::clipOff(neigh_idoff);
		// get the nodes of the two faces
		std::array<index_t, 3> this_face, neigh_face;
		this_face  = {mesh.tetNode(tet_id + TetMesh::tetON1(off)),
		              mesh.tetNode(tet_id + TetMesh::tetON2(off)),
		              mesh.tetNode(tet_id + TetMesh::tetON3(off))};
		neigh_face = {mesh.tetNode(neigh_id + TetMesh::tetON3(neigh_off)),
		              mesh.tetNode(neigh_id + TetMesh::tetON2(neigh_off)),
		              mesh.tetNode(neigh_id + TetMesh::tetON1(neigh_off))};
		// check the orientation of the two faces
		bool common_and_well_oriented = false;
		for (index_t i = 0; i < 3; i++)
		{
			if (this_face[0] == neigh_face[i] &&
			    this_face[1] == neigh_face[(i + 1) % 3] &&
			    this_face[2] == neigh_face[(i + 2) % 3])
			{
				common_and_well_oriented = true;
				break;
			}
		}
		if (!common_and_well_oriented)
		{
			OMC_ASSERT(false,
			           "The common face between tetrahedron {} and its neighbor {} "
			           "are not well-oriented.",
			           tet_id >> 2, neigh_id >> 2);
			return false;
		}
	}
	return true;
}

/**
 * @brief Verifies if the Delaunay condition is satisfied for a given vertex.
 * @param vid The index of the vertex to be checked.
 * @return True if the Delaunay condition is satisfied for the vertex, false
 * otherwise.
 */
template <typename Traits>
bool DelaunayTet<Traits>::verifyDelaunay(index_t vid) const
{
	// 3. Check if the Delaunay condition is satisfied for all vertices
	AuxVector64<index_t> check_tets;
	check_tets.push_back(TetMesh::toIdOff(mesh.incTet(vid)));

	for (index_t first = 0; first < check_tets.size(); first++)
	{
		index_t tid = check_tets[first];
		if (!mesh.isFiniteTet(tid))
			continue;

		// Check the Delaunay condition for this tetrahedron
		if (!mesh.tetHasVertex(tid, vid))
		{
			if (mesh.vertexInTetSphere(tid, vid))
			{
				OMC_ASSERT(
				  false, "The vertex {} is inside the circumsphere of tetrahedron {}.",
				  vid, tid >> 2);
				// clang-format on
				return false;
			}
			else
				continue; // check the next tetrahedron
		}

		// Add the neighbors of the tetrahedron to the check list
		for (index_t off = 0; off < 4; off++)
		{
			index_t idoff       = tid + off;
			index_t neigh_idoff = mesh.tetNeigh(idoff);
			// if the neighbor does not exist or is infinite, skip it
			if (neigh_idoff == InvalidIndex || mesh.isFiniteTet(neigh_idoff))
				continue;
			// if the neighbor has not been checked, add it to the check list
			index_t neigh_id = TetMesh::clipId(neigh_idoff);
			if (std::find(check_tets.begin(), check_tets.end(), neigh_id) ==
			    check_tets.end())
				check_tets.push_back(neigh_id);
		}
	}
	return true;
}

} // namespace OMC