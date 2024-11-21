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
#include "OpenMeshCraft/Utils/Logger.h"
#include "OpenMeshCraft/Utils/Macros.h"

#include "OpenMeshCraft/Arrangements/Utils.h"

#include <bitset>
#include <fstream>
#include <memory>
#include <vector>

namespace OMC {

// Enable shuffling missing segments in each loop of segment recovery.
// #define OMC_CDT_SHUFFLE_MISSING_SEGMENTS

// Enable exact inSphere predicate in finding encroaching point.
#define OMC_CDT_EXACT_ENCROACH_TEST

// Choose one segmen recovery strategy
// #define OMC_CDT_SEG_SIHANG
#define OMC_CDT_SEG_GREEDY

// Enable protecting sphere strategy
#define OMC_CDT_PROTECT_SPHERE

struct ConstrDelTet_Config
{
	/// output more log information
	bool verbose                = false;
	/// If set to true, the explicit result (points and tetrahedra) will be saved
	/// in output mesh set by setTriMeshAsOutput.
	bool output_explicit_result = false;

	/// The threshold of the number of Steiner points inserted in segment
	/// recovery. The threshold is a multiple of the number of vertices.
	/// Set to 0 to disable the threshold.
	size_t Steiner_point_thres = 0;
};

struct ConstrDelTet_Stats
{
	/* Preprocessing *************************************************/

	double pp_elapsed = 0.; // timings of preprocessing

	/* Delaunay tetrahedralization ***********************************/

	double dt_elapsed = 0.; // timings of Delaunay tetrahedralization

	/* Constraints Recovery ******************************************/

	double seg_elapsed  = 0.; // timings of segment recovery
	double face_elapsed = 0.; // timings of face recovery

	size_t seg_steiner = 0; // number of Steiner points
};

// TODO Rename to InlinedVector2, and extract both Arrangements and CDT's
// AuxVector to a common place.
template <typename T>
using AuxVector2 = boost::container::small_vector<index_t, 2>;

using AuxVecIter      = typename AuxVector2<index_t>::iterator;
using AuxVecConstIter = typename AuxVector2<index_t>::const_iterator;

template <typename Traits>
struct CDTPointArena
{
public:
	using EPoint     = typename Traits::EPoint;
	using GPoint     = typename Traits::GPoint;
	using IPoint_SSI = typename Traits::IPoint_SSI;
	using IPoint_LNC = typename Traits::IPoint_LNC;
	using IPoint_LPI = typename Traits::IPoint_LPI;
	using IPoint_TPI = typename Traits::IPoint_TPI;

public:
	std::deque<IPoint_SSI> ssi; // SSI points
	std::deque<IPoint_LNC> lnc; // LNC points
	std::deque<IPoint_LPI> lpi; // LPI points
	std::deque<IPoint_TPI> tpi; // TPI points

public:
	void recycle(IPoint_SSI *ssi_ptr) { recycled_ssi.push(ssi_ptr); }
	void recycle(IPoint_LNC *lnc_ptr) { recycled_lnc.push(lnc_ptr); }
	void recycle(IPoint_LPI *lpi_ptr) { recycled_lpi.push(lpi_ptr); }
	void recycle(IPoint_TPI *tpi_ptr) { recycled_tpi.push(tpi_ptr); }

	IPoint_SSI *emplace(IPoint_SSI &&p)
	{
		IPoint_SSI *ssi_ptr = nullptr;
		if (recycled_ssi.empty())
		{
			ssi.emplace_back(std::move(p));
			ssi_ptr = &ssi.back();
		}
		else
		{
			ssi_ptr = recycled_ssi.front();
			recycled_ssi.pop();
			*ssi_ptr = std::move(p);
		}
		return ssi_ptr;
	}

	IPoint_LNC *emplace(IPoint_LNC &&p)
	{
		IPoint_LNC *lnc_ptr = nullptr;
		if (recycled_lnc.empty())
		{
			lnc.emplace_back(std::move(p));
			lnc_ptr = &lnc.back();
		}
		else
		{
			lnc_ptr = recycled_lnc.front();
			recycled_lnc.pop();
			*lnc_ptr = std::move(p);
		}
		return lnc_ptr;
	}

	IPoint_LPI *emplace(IPoint_LPI &&p)
	{
		IPoint_LPI *lpi_ptr = nullptr;
		if (recycled_lpi.empty())
		{
			lpi.emplace_back(std::move(p));
			lpi_ptr = &lpi.back();
		}
		else
		{
			lpi_ptr = recycled_lpi.front();
			recycled_lpi.pop();
			*lpi_ptr = std::move(p);
		}
		return lpi_ptr;
	}

	IPoint_TPI *emplace(IPoint_TPI &&p)
	{
		IPoint_TPI *tpi_ptr = nullptr;
		if (recycled_tpi.empty())
		{
			tpi.emplace_back(std::move(p));
			tpi_ptr = &tpi.back();
		}
		else
		{
			tpi_ptr = recycled_tpi.front();
			recycled_tpi.pop();
			*tpi_ptr = std::move(p);
		}
		return tpi_ptr;
	}

	void reserve_ssi(size_t new_n)
	{
		for (size_t i = 0; i < new_n; i++)
			recycle(&ssi.emplace_back());
	}

	void reserve_lpi(size_t new_n)
	{
		for (size_t i = 0; i < new_n; i++)
			recycle(&lpi.emplace_back());
	}

	void reserve_tpi(size_t new_n)
	{
		for (size_t i = 0; i < new_n; i++)
			recycle(&tpi.emplace_back());
	}

private:
	std::queue<IPoint_SSI *> recycled_ssi;
	std::queue<IPoint_LNC *> recycled_lnc;
	std::queue<IPoint_LPI *> recycled_lpi;
	std::queue<IPoint_TPI *> recycled_tpi;
};

#define OMC_CDT_START_ELAPSE(name) auto name = OMC::Logger::elapse_reset();

#define OMC_CDT_SAVE_ELAPSED(name, dst_name, dscrpt)                    \
	if (stats != nullptr)                                                 \
		stats->dst_name = OMC::Logger::elapsed(name).count();               \
	if (config.verbose)                                                   \
	{                                                                     \
		OMC::Logger::info(std::format("[OpenMeshCraft CDT] " dscrpt         \
		                              " time : {} s",                       \
		                              OMC::Logger::elapsed(name).count())); \
	}

} // namespace OMC