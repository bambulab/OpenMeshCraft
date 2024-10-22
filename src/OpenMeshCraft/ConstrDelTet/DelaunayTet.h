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
	using InSphere          = typename Traits::InSphere;
	using CollinearPoints3  = typename Traits::CollinearPoints3;

	using TetMesh = TetrahedralMesh<Traits>;

public: /* Constructor & Destructor ****************************************/
	DelaunayTet() = delete;
	DelaunayTet(TetMesh &_mesh)
	  : mesh(_mesh)
	{
	}

public: /* Algorithm *******************************************************/

	/* Pipeline of the algorithm
	 * - Initialize the Delaunay tetrahedralization
	 * - Insert vertices into the Delaunay tetrahedralization
	 * - [Optional] Mark infinite tetrahedra as deleted if required
	 * - Remove deleted tetrahedra
	 */
	void tetrahedralize(bool remove_infinite_tets = false);

	/* Initialize the Delaunay tetrahedralization */
	void initialize(index_t &k, index_t &l);

	/* Insert a vertex into the Delaunay tetrahedralization */
	void insertVertex(const index_t vid, index_t &tet);

	/* [Optional] Mark infinite tetrahedra as deleted */
	void markInfiniteTetsDeleted();

public: /* Checks **********************************************************/

	/* Verify the correctness of the Delaunay tetrahedralization */
	bool verify(bool verbose) const;

public: /* Data ************************************************************/
	TetMesh &mesh;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "DelaunayTet.inl"
#endif