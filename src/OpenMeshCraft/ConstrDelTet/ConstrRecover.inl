#pragma once

#include "ConstrRecover.h"

namespace OMC {

/**
 * @brief Initialize with the Delaunay tetrahedral mesh and the input
 * constrained triangles. Prepare for the constraits recovery.
 * @param _tet_mesh the Delaunay tetrahedral mesh
 * @param _input_tv the input constrained triangles
 */
template <typename Traits>
ConstraintsRecover<Traits>::ConstraintsRecover(
  TetMesh &_tet_mesh, PLC& _plc)
  : tet_mesh(_tet_mesh)
  , plc(_plc)
{

}

} // namespace OMC