#pragma once

#include "PLC.h"
#include "TetMesh.h"
#include "Utils.h"

namespace OMC {

/**
 * @brief Recover the constraints in CDT algorithm.
 */
template <typename Traits>
class ConstraintsRecover
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
	using PLC     = PiecewiseLinearComplex<Traits>;

public: /* Constructor & Destructor ****************************************/
	ConstraintsRecover() = delete;
	ConstraintsRecover(TetMesh &_tet_mesh, PLC &_plc);

public: /* Algorithms ******************************************************/

public: /* Data ************************************************************/
	/// Tetrahedral mesh
	TetMesh &tet_mesh;
  /// Constrained piecewise linear complex
	PLC &plc;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ConstrRecover.inl"
#endif