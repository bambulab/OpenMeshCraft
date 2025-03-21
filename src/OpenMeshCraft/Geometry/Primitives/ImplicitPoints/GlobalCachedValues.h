#pragma once

#include "OpenMeshCraft/Geometry/Utils.h"
#include "OpenMeshCraft/Utils/Exception.h"

#include "parallel_hashmap/phmap.h"
#include "tbb/tbb.h"

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

#ifndef OMC_CACHE_DF
		dfilter_cached = false;
#endif
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
	/// @brief resize to \p thread_num maps, \p thread_num is often the max
	/// thread number.
	void resize(size_t thread_num)
	{
		// spin lock
		while (spin_lock.test_and_set(std::memory_order_acquire))
			;
		m_maps.clear();
		m_maps.resize(thread_num);
		m_arenas.clear();
		m_arenas.resize(thread_num);
		spin_lock.clear(std::memory_order_release);
	}

	OnePointCachedValues &get(void *point_ptr)
	{
		int thread_id = tbb::this_task_arena::current_thread_index();
		OMC_EXPENSIVE_ASSERT((size_t)thread_id < m_maps.size(),
		                     "thread id {} excceed maps size {}", thread_id,
		                     m_maps.size());
		PointsCachedValuesMap &map  = m_maps[thread_id];
		auto                   iter = map.find(point_ptr);
		if (iter != map.end())
		{
			return *iter->second;
		}
		else
		{
			PointsCachedValuesArena &arena = m_arenas[thread_id];
			arena.emplace_back();
			OnePointCachedValues *cv = &arena.back();
			map.insert(std::pair<void *, OnePointCachedValues *>(point_ptr, cv));
			return *cv;
		}
	}

	void remove(void *point_ptr)
	{
		int thread_id = tbb::this_task_arena::current_thread_index();
		OMC_EXPENSIVE_ASSERT((size_t)thread_id < m_maps.size(),
		                     "thread id {} excceed maps size {}", thread_id,
		                     m_maps.size());
		m_maps[thread_id].erase(point_ptr);
	}

	void clear_cached_values()
	{
		int thread_id = tbb::this_task_arena::current_thread_index();
		OMC_EXPENSIVE_ASSERT((size_t)thread_id < m_maps.size(),
		                     "thread id {} excceed maps size {}", thread_id,
		                     m_maps.size());
		m_maps[thread_id].clear();
		m_arenas[thread_id].clear();
	}

	void enable()
	{
		// spin lock
		while (spin_lock.test_and_set(std::memory_order_acquire))
			;
		m_enabled = true;
		spin_lock.clear(std::memory_order_release);
	}

	void disable()
	{
		// spin lock
		while (spin_lock.test_and_set(std::memory_order_acquire))
			;
		m_enabled = false;
		m_maps.clear();
		spin_lock.clear(std::memory_order_release);
	}

	bool is_enabled() const { return m_enabled; }

protected:
	/// one map per thread, map generic point's pointer to cached value
	/// OPT thread_local
	std::deque<PointsCachedValuesMap>   m_maps;
	std::deque<PointsCachedValuesArena> m_arenas;

	bool m_enabled = false;

	/// mutex for multi-thread safety
	std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;
};

} // namespace OMC