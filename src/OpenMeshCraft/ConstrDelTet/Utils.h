#pragma once

// clang-format off
#include "OpenMeshCraft/Utils/DisableWarnings.h"
#include "boost/container/flat_set.hpp"
#include "boost/container/small_vector.hpp"
#include "parallel_hashmap/phmap.h"
#include "parallel_hashmap/btree.h"
#include "tbb/tbb.h"
#include "OpenMeshCraft/Utils/EnableWarnings.h"
// clang-format on

#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#include "OpenMeshCraft/Geometry/Intersection/IntersectionUtils.h"
#include "OpenMeshCraft/Geometry/Utils.h"

#include "OpenMeshCraft/Utils/ContainerOp.h"
#include "OpenMeshCraft/Utils/Exception.h"
#include "OpenMeshCraft/Utils/Hashers.h"
#include "OpenMeshCraft/Utils/IndexDef.h"
#include "OpenMeshCraft/Utils/Label.h"
#include "OpenMeshCraft/Utils/Macros.h"

#include <bitset>
#include <memory>
#include <vector>

namespace OMC {

struct ConstrDelTet_Config
{
	/// output more log information
	bool verbose                = false;
	/// If set to true, the explicit result (points and tetrahedra) will be saved
	/// in output mesh set by setTriMeshAsOutput.
	bool output_explicit_result = false;
};

struct ConstrDelTet_Stats
{
	/* Preprocessing *************************************************/

	double pp_elapsed = 0.; // timings of preprocessing

	/* Delaunay tetrahedralization ***********************************/

	double dt_elapsed = 0.; // timings of Delaunay tetrahedralization
};

} // namespace OMC