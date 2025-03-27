#pragma once

#include <cstddef>

#include <iterator>

namespace OMC {

/**
 * @class KdPointContainer
 * @brief A container class for managing a collection of points in a k-d tree
 * structure. It supports operations such as splitting the points into two
 * containers based on a specified axis and value.
 * @tparam KdTraits Traits class that defines the types used in the k-d tree.
 */
template <typename KdTraits>
class KdPointContainer
{
public: /* Types *************************************************************/
  using NT = typename KdTraits::NT;

  using KdPointPtr      = typename KdTraits::KdPointPtr;
  using KdPointPtrsIter = typename KdTraits::KdPointPtrsIter;
  using KdBox           = typename KdTraits::KdBox;

public: /* Constructor *******************************************************/
  KdPointContainer() = default;

  KdPointContainer(KdPointPtrsIter begin, KdPointPtrsIter end);

public: /* Interfaces ********************************************************/
  inline size_t          size() const { return std::distance(m_begin, m_end); }
  inline KdPointPtrsIter begin() const { return m_begin; }
  inline KdPointPtrsIter end() const { return m_end; }
  inline const KdBox    &bbox() const { return m_bbox; }
  inline const KdBox    &tbox() const { return m_tbox; }

  /**
   * @brief Split points in `this` to two containers `this` and `c_low`.
   * Points are split by given separate axis and separate value.
   * @param c_low The other point container storing points.
   * @param sep_axis separate axis.
   * @param sep_val separate value.
   * @param sliding whether sliding points.
   */
  void split(KdPointContainer &c_low, size_t &sep_axis, NT &sep_val,
             bool sliding = false);

private: /* Data *************************************************************/
  KdPointPtrsIter m_begin, m_end;
  KdBox           m_bbox, m_tbox;
  size_t          m_build_axis;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "KdPointContainer.inl"
#endif