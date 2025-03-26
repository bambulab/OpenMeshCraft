#pragma once

#include "IndexDef.h"
#include "Macros.h"

#include <array>
#include <atomic>

/**
 * @class AtomicBitset
 * @brief A thread-safe bitset implementation using atomic operations.
 *
 * This class provides a fixed-size bitset where each bit can be set, reset, and
 * tested in a thread-safe manner using atomic operations. The bitset is divided
 * into chunks of a specified size, and each chunk is managed using an atomic
 * variable.
 *
 * @tparam N The total number of bits in the bitset.
 * @note The default chunk size is 64 bits, which corresponds to the size of a
 * `size_t` on most platforms.
 */
namespace OMC {

template <size_t N>
class AtomicBitset
{
public: /* Definitions and Data *********************************************/
  static constexpr size_t CHUNK_SIZE = 32;
  static constexpr size_t NUM_CHUNKS = (N + CHUNK_SIZE - 1) / CHUNK_SIZE;

  static constexpr bool SINGLE_CHUNK = NUM_CHUNKS == 1;

  using CHUNK_TYPE =
    std::conditional_t<SINGLE_CHUNK, std::atomic<uint32_t>,
                       std::array<std::atomic<uint32_t>, NUM_CHUNKS>>;

  CHUNK_TYPE chunks; // Fixed-size storage

public: /* Interfaces *******************************************************/
  AtomicBitset()
  {
    if constexpr (SINGLE_CHUNK)
    {
      chunks.store(0, std::memory_order_relaxed);
    }
    else
    {
      for (auto &chunk : chunks)
        chunk.store(0, std::memory_order_relaxed);
    }
  }

  // A trick to cooperate with constructions on normal number types
  template <typename NT>
  AtomicBitset(OMC_UNUSED NT nt)
    : AtomicBitset()
  {
  }

  /**
   * @brief Set the bit at the specified index.
   * @param n The index of the bit to set.
   */
  void set(index_t n)
  {
    if constexpr (SINGLE_CHUNK)
    {
      chunks.fetch_or(1ULL << n, std::memory_order_relaxed);
    }
    else
    {
      index_t idx = n / CHUNK_SIZE;
      index_t bit = n % CHUNK_SIZE;
      chunks[idx].fetch_or(1ULL << bit, std::memory_order_relaxed);
    }
  }

  /**
   * @brief Reset the bit at the specified index.
   * @param n The index of the bit to reset.
   */
  void reset(index_t n)
  {
    if constexpr (SINGLE_CHUNK)
    {
      chunks.fetch_and(~(1ULL << n), std::memory_order_relaxed);
    }
    else
    {
      index_t idx = n / CHUNK_SIZE;
      index_t bit = n % CHUNK_SIZE;
      chunks[idx].fetch_and(~(1ULL << bit), std::memory_order_relaxed);
    }
  }

  /**
   * @brief Test the bit at the specified index.
   * @param n The index of the bit to test.
   * @return true if the bit is set, otherwise false.
   */
  bool test(index_t n) const
  {
    if constexpr (SINGLE_CHUNK)
    {
      chunks.load(std::memory_order_relaxed) & (1ULL << n);
    }
    else
    {
      index_t idx = n / CHUNK_SIZE;
      index_t bit = n % CHUNK_SIZE;
      return chunks[idx].load(std::memory_order_relaxed) & (1ULL << bit);
    }
  }

  /**
   * @brief Reset all bits in the bitset.
   */
  void resetAll()
  {
    if constexpr (SINGLE_CHUNK)
    {
      chunks.store(0, std::memory_order_relaxed);
    }
    else
    {
      for (auto &chunk : chunks)
        chunk.store(0, std::memory_order_relaxed);
    }
  }
};

} // namespace OMC