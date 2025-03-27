#pragma once

#include "PointBound.h"

#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"

namespace OMC {

/**
 * @brief Calculate bounding box for given primitives.
 * @tparam Kernel
 */
template <typename Kernel>
class CalcBoundingBox3K
{
public:
  using K = Kernel;

  using IT = IntervalNumber<std::true_type>;

  using EPoint3 = typename K::EPoint3;
  using GPoint3 = typename K::GPoint3;

  using Sphere3      = typename K::Sphere3;
  using Segment3     = typename K::Segment3;
  using Triangle3    = typename K::Triangle3;
  using BoundingBox3 = typename K::BoundingBox3;

public:
  /* Below functions calculate box for given primitives and update reference
   * box. */

  /// @brief Special version for implicit/generic points.
  template <typename GPT,
            typename = std::enable_if_t<std::is_same_v<GPT, GPoint3> &&
                                        !std::is_same_v<GPT, EPoint3>>>
  void operator()(BoundingBox3 &box, const GPT &gp);

  void operator()(BoundingBox3 &box, const EPoint3 &point);
  void operator()(BoundingBox3 &box, const Segment3 &segment);
  void operator()(BoundingBox3 &box, const Triangle3 &triangle);
  void operator()(BoundingBox3 &box, const Sphere3 &sphere);

  /**
   * @brief Calculate a bounding box for a given primitive.
   * @tparam PrimitiveT Any geometry primitive.
   * @param primitive The given primitive.
   * @return The resulting bounding box.
   */
  template <typename PrimitiveT>
  BoundingBox3 operator()(const PrimitiveT &primitive)
  {
    BoundingBox3 box;
    (*this)(box, primitive);
    return box;
  }
};

template <typename Kernel>
template <typename GPT, typename /*SFINAE*/>
void CalcBoundingBox3K<Kernel>::operator()(BoundingBox3 &box, const GPT &gp)
{
  auto [minb, maxb] = PointBound<GPoint3, EPoint3>().both_bounds(gp);
  box.min_bound()   = minb;
  box.max_bound()   = maxb;
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BoundingBox3  &box,
                                           const EPoint3 &point)
{
  box.min_bound() = point;
  box.max_bound() = point;
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BoundingBox3   &box,
                                           const Segment3 &segment)
{
  box.min_bound() = segment.start();
  box.min_bound().minimize(segment.end());
  box.max_bound() = segment.start();
  box.max_bound().maximize(segment.end());
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BoundingBox3    &box,
                                           const Triangle3 &triangle)
{
  box.min_bound() = triangle.v0();
  box.max_bound() = triangle.v0();
  box.min_bound().minimize(triangle.v1());
  box.min_bound().minimize(triangle.v2());
  box.max_bound().maximize(triangle.v1());
  box.max_bound().maximize(triangle.v2());
}

template <typename Kernel>
void CalcBoundingBox3K<Kernel>::operator()(BoundingBox3  &box,
                                           const Sphere3 &sphere)
{
  IT::Protector it_protecter;

  IT cx(sphere.center().x());
  IT cy(sphere.center().y());
  IT cz(sphere.center().z());
  IT sr(sphere.squared_radius());

  IT r    = sr.sqrt();
  IT minx = cx - r, miny = cy - r, minz = cz - r;
  IT maxx = cx + r, maxy = cy + r, maxz = cz + r;

  box.min_bound() = EPoint3(minx.inf(), miny.inf(), minz.inf());
  box.max_bound() = EPoint3(maxx.sup(), maxy.sup(), maxz.sup());
}

} // namespace OMC