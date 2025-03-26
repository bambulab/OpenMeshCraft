#pragma once

// clang-format off
#include "OpenMeshCraft/Utils/DisableWarnings.h"
#include "tbb/tbb.h"
#include "OpenMeshCraft/Utils/EnableWarnings.h"
// clang-format on

namespace OMC {

// Enable shuffling missing segments in each loop of segment recovery.
// #define OMC_CDT_SHUFFLE_MISSING_SEGMENTS

// Enable exact inSphere predicate in finding encroaching point.
#define OMC_CDT_EXACT_ENCROACH_TEST

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

template <typename Traits>
struct CDTPointArena
{
public:
  using EPoint3      = typename Traits::EPoint3;
  using GPoint3      = typename Traits::GPoint3;
  using IPoint3T_SSI = typename Traits::IPoint3T_SSI;
  using IPoint3T_LNC = typename Traits::IPoint3T_LNC;
  using IPoint3T_LPI = typename Traits::IPoint3T_LPI;
  using IPoint3T_TPI = typename Traits::IPoint3T_TPI;

public:
  std::deque<IPoint3T_SSI> ssi; // SSI points
  std::deque<IPoint3T_LNC> lnc; // LNC points
  std::deque<IPoint3T_LPI> lpi; // LPI points
  std::deque<IPoint3T_TPI> tpi; // TPI points

public:
  void recycle(IPoint3T_SSI *ssi_ptr) { recycled_ssi.push(ssi_ptr); }
  void recycle(IPoint3T_LNC *lnc_ptr) { recycled_lnc.push(lnc_ptr); }
  void recycle(IPoint3T_LPI *lpi_ptr) { recycled_lpi.push(lpi_ptr); }
  void recycle(IPoint3T_TPI *tpi_ptr) { recycled_tpi.push(tpi_ptr); }

  IPoint3T_SSI *emplace(IPoint3T_SSI &&p)
  {
    IPoint3T_SSI *ssi_ptr = nullptr;
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

  IPoint3T_LNC *emplace(IPoint3T_LNC &&p)
  {
    IPoint3T_LNC *lnc_ptr = nullptr;
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

  IPoint3T_LPI *emplace(IPoint3T_LPI &&p)
  {
    IPoint3T_LPI *lpi_ptr = nullptr;
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

  IPoint3T_TPI *emplace(IPoint3T_TPI &&p)
  {
    IPoint3T_TPI *tpi_ptr = nullptr;
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

  void reserve_lnc(size_t new_n)
  {
    for (size_t i = 0; i < new_n; i++)
      recycle(&lnc.emplace_back());
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
  std::queue<IPoint3T_SSI *> recycled_ssi;
  std::queue<IPoint3T_LNC *> recycled_lnc;
  std::queue<IPoint3T_LPI *> recycled_lpi;
  std::queue<IPoint3T_TPI *> recycled_tpi;
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