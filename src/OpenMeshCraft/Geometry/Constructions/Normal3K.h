#pragma once

#include <type_traits>

namespace OMC {

/**
 * @brief Construct normal in 3D. Support geometric primitives: Triangle3.
 * @tparam Kernel
 * @todo Support more geometric primitives.
 */
template <typename Kernel>
class ConstructNormal3K
{
public:
  using Vec3    = typename Kernel::Vec3;
  using EPoint3 = typename Kernel::EPoint3;
  using GPoint3 = typename Kernel::GPoint3;

  using Triangle3 = typename Kernel::Triangle3;

  using ToEP = typename Kernel::ToEP;

public:
  /**
   * @brief Construct normal for a triangle.
   * This function accepts generic points and converts them to explicit points.
   * @param v0 The first vertex of the triangle.
   * @param v1 The second vertex of the triangle.
   * @param v2 The third vertex of the triangle.
   * @return The normal of the triangle.
   * @todo Support exact construction.
   */
  template <typename GPT,
            typename = std::enable_if_t<std::is_same_v<GPT, GPoint3> &&
                                        !std::is_same_v<GPT, EPoint3>>>
  Vec3 operator()(const GPT &v0, const GPT &v1, const GPT &v2) const
  {
    return (ToEP()(v1) - ToEP()(v0)).cross(ToEP()(v2) - ToEP()(v0));
  }

  /**
   * @brief Construct normal for a triangle. This function accepts only explicit
   * points.
   * @param v0 The first vertex of the triangle.
   * @param v1 The second vertex of the triangle.
   * @param v2 The third vertex of the triangle.
   * @return The normal of the triangle.
   */
  Vec3 operator()(const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2) const
  {
    return (v1 - v0).cross(v2 - v0);
  }

  Vec3 operator()(const Triangle3 &tri) const
  {
    return operator()(tri.v0(), tri.v1(), tri.v2());
  }
};

} // namespace OMC