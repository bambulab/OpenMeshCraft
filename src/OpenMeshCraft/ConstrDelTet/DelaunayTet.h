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

	using TetMesh = TetrahedralMesh<Traits>;

public: /* Constructor & Destructor ****************************************/
	DelaunayTet() = delete;
	DelaunayTet(TetMesh &_mesh)
	  : mesh(_mesh)
	{
	}

public: /* Algorithm *******************************************************/
	/* Pipeline of the algorithm */
	void tetrahedralize(bool remove_infinite_tets = false);

	void initialize(index_t &k, index_t &l);

	void insertVertex(const index_t vid, index_t &tet);

	void markInfiniteTetsDeleted();

public: /* Data ************************************************************/
	TetMesh &mesh;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "DelaunayTet.inl"
#endif