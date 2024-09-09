// Tetrahedra soup
#include "OpenMeshCraft/Mesh/TetSoup.h"
// Geometry kernel
#include "OpenMeshCraft/Geometry/ExactIndirectPredicatesApproxConstructions.h"

#include "CDT.h"

namespace OMC {

template class ConstrDelTet<EIAC, TetSoupTraits>;

}