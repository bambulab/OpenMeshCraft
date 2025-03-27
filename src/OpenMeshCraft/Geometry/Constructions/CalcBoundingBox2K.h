#pragma once

#include "PointBound.h"

namespace OMC {

/**
 * @brief Calculate bounding box for given primitives.
 * @tparam Kernel
 */
template <typename Kernel>
class CalcBoundingBox2K
{
public:
  using K  = Kernel;
  using NT = typename K::NT;

  using EPoint2 = typename K::EPoint2;
  using GPoint2 = typename K::GPoint2;

  using Segment2     = typename K::Segment2;
  using Triangle2    = typename K::Triangle2;
  using BoundingBox2 = typename K::BoundingBox2;

public:
  /* Below functions calculate box for given primitives and update reference
   * box. */

  /// @brief Special version for implicit/generic points.
  template <typename GPT,
            typename = std::enable_if_t<std::is_same_v<GPT, GPoint2> &&
                                        !std::is_same_v<GPT, EPoint2>>>
  void operator()(BoundingBox2 &box, const GPT &gp);

  void operator()(BoundingBox2 &box, const EPoint2 &point);
  void operator()(BoundingBox2 &box, const Segment2 &segment);
  void operator()(BoundingBox2 &box, const Triangle2 &triangle);

  /**
   * @brief Calculate a bounding box for a given primitive.
   * @tparam PrimitiveT Any geometry primitive.
   * @param primitive The given primitive.
   * @return The resulting bounding box.
   */
  template <typename PrimitiveT>
  BoundingBox2 operator()(const PrimitiveT &primitive)
  {
    BoundingBox2 box;
    (*this)(box, primitive);
    return box;
  }
};

template <typename Kernel>
template <typename GPT, typename /*SFINAE*/>
void CalcBoundingBox2K<Kernel>::operator()(BoundingBox2 &box, const GPT &gp)
{
  auto [minb, maxb] = PointBound<GPoint2, EPoint2>().both_bounds(gp);
  box.min_bound()   = minb;
  box.max_bound()   = maxb;
}

template <typename Kernel>
void CalcBoundingBox2K<Kernel>::operator()(BoundingBox2  &box,
                                           const EPoint2 &point)
{
  box.min_bound() = point;
  box.max_bound() = point;
}

template <typename Kernel>
void CalcBoundingBox2K<Kernel>::operator()(BoundingBox2   &box,
                                           const Segment2 &segment)
{
  box.min_bound() = segment.start();
  box.min_bound().minimize(segment.end());
  box.max_bound() = segment.start();
  box.max_bound().maximize(segment.end());
}

template <typename Kernel>
void CalcBoundingBox2K<Kernel>::operator()(BoundingBox2    &box,
                                           const Triangle2 &triangle)
{
  box.min_bound() = triangle.v0();
  box.max_bound() = triangle.v0();
  box.min_bound().minimize(triangle.v1());
  box.min_bound().minimize(triangle.v2());
  box.max_bound().maximize(triangle.v1());
  box.max_bound().maximize(triangle.v2());
}

} // namespace OMC