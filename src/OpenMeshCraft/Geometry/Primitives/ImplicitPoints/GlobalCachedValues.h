#pragma once

#include "OpenMeshCraft/Geometry/Utils.h"

#include "parallel_hashmap/phmap.h"

#include <atomic>
#include <deque>

namespace OMC {

template <typename IT, typename ET>
class OnePointCachedValues2
{
public:
  using FT = double;

public:
  // dynamic filter (interval number)
  IT dfilter_lx, dfilter_ly, dfilter_d;

  // exact number
  ET *exact_lx = nullptr, *exact_ly = nullptr, *exact_d = nullptr;

  // expansion number
  FT *expansion_lx = nullptr, *expansion_ly = nullptr, *expansion_d = nullptr;
  int expansion_lx_len = 0, expansion_ly_len = 0, expansion_d_len = 0;

  bool dfilter_cached   = false;
  bool exact_cached     = false;
  bool expansion_cached = false;

  OnePointCachedValues2() noexcept
  {
    exact_lx = nullptr;
    exact_ly = nullptr;
    exact_d  = nullptr;

    expansion_lx     = nullptr;
    expansion_ly     = nullptr;
    expansion_d      = nullptr;
    expansion_lx_len = 0;
    expansion_ly_len = 0;
    expansion_d_len  = 0;

    dfilter_cached = false;
    exact_cached     = false;
    expansion_cached = false;
  }

  OnePointCachedValues2(const OnePointCachedValues2 &rhs) = delete;
  OnePointCachedValues2(OnePointCachedValues2 &&rhs)      = delete;

  void operator=(const OnePointCachedValues2 &rhs) = delete;
  void operator=(OnePointCachedValues2 &&rhs)      = delete;

  ~OnePointCachedValues2()
  {
    if (expansion_cached)
    {
      free(expansion_lx);
      free(expansion_ly);
      free(expansion_d);
    }
    if (exact_cached || exact_lx)
    {
      delete[] exact_lx;
    }
  }

  void alloc_exact()
  {
    ET *new_et = new ET[3];
    exact_lx   = new_et + 0;
    exact_ly   = new_et + 1;
    exact_d    = new_et + 3;
  }
};

template <typename IT, typename ET>
class OnePointCachedValues3
{
public:
  using FT = double;

public:
#ifndef OMC_CACHE_DF
  // dynamic filter (interval number)
  IT dfilter_lx, dfilter_ly, dfilter_lz, dfilter_d;
#endif

  // exact number
  ET *exact_lx = nullptr, *exact_ly = nullptr, *exact_lz = nullptr,
     *exact_d = nullptr;

  // expansion number
  FT *expansion_lx = nullptr, *expansion_ly = nullptr, *expansion_lz = nullptr,
     *expansion_d      = nullptr;
  int expansion_lx_len = 0, expansion_ly_len = 0, expansion_lz_len = 0,
      expansion_d_len = 0;

#ifndef OMC_CACHE_DF
  bool dfilter_cached = false;
#endif
  bool exact_cached     = false;
  bool expansion_cached = false;

  OnePointCachedValues3() noexcept
  {
    exact_lx = nullptr;
    exact_ly = nullptr;
    exact_lz = nullptr;
    exact_d  = nullptr;

    expansion_lx     = nullptr;
    expansion_ly     = nullptr;
    expansion_lz     = nullptr;
    expansion_d      = nullptr;
    expansion_lx_len = 0;
    expansion_ly_len = 0;
    expansion_lz_len = 0;
    expansion_d_len  = 0;

#ifndef OMC_CACHE_DF
    dfilter_cached = false;
#endif
    exact_cached     = false;
    expansion_cached = false;
  }

  OnePointCachedValues3(const OnePointCachedValues3 &rhs) = delete;
  OnePointCachedValues3(OnePointCachedValues3 &&rhs)      = delete;

  void operator=(const OnePointCachedValues3 &rhs) = delete;
  void operator=(OnePointCachedValues3 &&rhs)      = delete;

  ~OnePointCachedValues3() noexcept
  {
    if (expansion_cached)
    {
      free(expansion_lx);
      free(expansion_ly);
      free(expansion_lz);
      free(expansion_d);
    }
    if (exact_cached || exact_lx)
    {
      delete[] exact_lx;
    }
  }

  void alloc_exact()
  {
    ET *new_et = new ET[4];
    exact_lx   = new_et + 0;
    exact_ly   = new_et + 1;
    exact_lz   = new_et + 2;
    exact_d    = new_et + 3;
  }
};

template <typename OnePointCachedValues_>
class GlobalCachedValues
{
public:
  using OnePointCachedValues = OnePointCachedValues_;
  using PointsCachedValuesMap =
    phmap::flat_hash_map<void *, OnePointCachedValues *>;
  using PointsCachedValuesArena = std::deque<OnePointCachedValues>;

public:
  static OnePointCachedValues &get(void *point_ptr)
  {
    auto iter = m_map.find(point_ptr);
    if (iter != m_map.end())
    {
      return *iter->second;
    }
    else
    {
      m_arena.emplace_back();
      OnePointCachedValues *cv = &m_arena.back();
      m_map.insert(std::pair<void *, OnePointCachedValues *>(point_ptr, cv));
      return *cv;
    }
  }

  static void remove(void *point_ptr) { m_map.erase(point_ptr); }

  static void clear_cached_values()
  {
    m_map.clear();
    m_arena.clear();
  }

  static void enable()
  {
    // spin lock
    while (spin_lock.test_and_set(std::memory_order_acquire))
      ;
    m_enabled = true;
    spin_lock.clear(std::memory_order_release);
  }

  static void disable()
  {
    // spin lock
    while (spin_lock.test_and_set(std::memory_order_acquire))
      ;
    m_enabled = false;
    m_map.clear();
    spin_lock.clear(std::memory_order_release);
  }

  bool is_enabled() const { return m_enabled; }

protected:
  /// one map per thread, map generic point's pointer to cached value
  /// (use tbb::enumerable_thread_sepcific when multiple instances are required)
  thread_local static PointsCachedValuesMap   m_map;
  thread_local static PointsCachedValuesArena m_arena;

  static bool m_enabled;

  /// mutex for multi-thread safety
  static std::atomic_flag spin_lock;
};

// Define thread_local static members
template <typename OnePointCachedValues_>
thread_local
  typename GlobalCachedValues<OnePointCachedValues_>::PointsCachedValuesMap
    GlobalCachedValues<OnePointCachedValues_>::m_map;

template <typename OnePointCachedValues_>
thread_local
  typename GlobalCachedValues<OnePointCachedValues_>::PointsCachedValuesArena
    GlobalCachedValues<OnePointCachedValues_>::m_arena;

template <typename OnePointCachedValues_>
bool GlobalCachedValues<OnePointCachedValues_>::m_enabled = false;

template <typename OnePointCachedValues_>
std::atomic_flag GlobalCachedValues<OnePointCachedValues_>::spin_lock =
  ATOMIC_FLAG_INIT;

} // namespace OMC