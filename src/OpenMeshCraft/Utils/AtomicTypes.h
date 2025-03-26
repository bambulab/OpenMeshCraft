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

  ~AtomicBitset() = default;

  AtomicBitset &operator=(const AtomicBitset &rhs)
  {
    if constexpr (SINGLE_CHUNK)
    {
      chunks.store(rhs.chunks.load(std::memory_order_relaxed),
                   std::memory_order_relaxed);
    }
    else
    {
      for (size_t i = 0; i < NUM_CHUNKS; i++)
        chunks[i].store(rhs.chunks[i].load(std::memory_order_relaxed),
                        std::memory_order_relaxed);
    }
    return *this;
  }

  AtomicBitset(const AtomicBitset &rhs) { this->operator=(rhs); }

  /**
   * @brief Set the bit at the specified index.
   * @param n The index of the bit to set.
   * @return true if the bit is successfully set, false if already set.
   */
  bool set(index_t n)
  {
    if constexpr (SINGLE_CHUNK)
    {
      uint32_t mask = uint32_t(1) << n;
      uint32_t prev = chunks.fetch_or(mask, std::memory_order_acq_rel);
      return !(prev & mask);
    }
    else
    {
      index_t  idx  = n / CHUNK_SIZE;
      index_t  bit  = n % CHUNK_SIZE;
      uint32_t mask = uint32_t(1) << bit;
      uint32_t prev = chunks[idx].fetch_or(mask, std::memory_order_acq_rel);
      return !(prev & mask);
    }
  }

  /**
   * @brief Reset the bit at the specified index.
   * @param n The index of the bit to reset.
   * @return true if the bit is successfully unset, false if already unset.
   */
  bool reset(index_t n)
  {
    if constexpr (SINGLE_CHUNK)
    {
      uint32_t mask = uint32_t(1) << n;
      uint32_t prev = chunks.fetch_and(~mask, std::memory_order_acq_rel);
      return (prev & mask);
    }
    else
    {
      index_t  idx  = n / CHUNK_SIZE;
      index_t  bit  = n % CHUNK_SIZE;
      uint32_t mask = uint32_t(1) << bit;
      uint32_t prev = chunks[idx].fetch_and(~mask, std::memory_order_acq_rel);
      return (prev & mask);
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
      return chunks.load(std::memory_order_relaxed) & (uint32_t(1) << n);
    }
    else
    {
      index_t idx = n / CHUNK_SIZE;
      index_t bit = n % CHUNK_SIZE;
      return chunks[idx].load(std::memory_order_relaxed) & (uint32_t(1) << bit);
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