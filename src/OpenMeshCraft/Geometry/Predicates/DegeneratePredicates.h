#pragma once

#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#include <tuple>

namespace OMC {

template <typename Kernel>
class CollinearPoints2K
{
public:
  using K = Kernel;

  using NT      = typename K::NT;
  using GPoint2 = typename K::GPoint2;

  using Orient2D = typename K::Orient2D;

public:
  bool operator()(const GPoint2 &p, const GPoint2 &q, const GPoint2 &r)
  {
    return Orient2D()(p, q, r) == Sign::ZERO;
  }
};

template <typename Kernel>
class CollinearPoints3K
{
public:
  using K = Kernel;

  using NT      = typename K::NT;
  using GPoint3 = typename K::GPoint3;

  using OrientOn2D = typename K::OrientOn2D;

public:
  /// @brief Check if three points are collinear. See details in the opposite
  /// function `misaligned`.
  bool operator()(const GPoint3 &p, const GPoint3 &q, const GPoint3 &r)
  {
    return !misaligned(p, q, r);
  }

  /// @brief Check if three points are collinear. See details in the opposite
  /// function `misaligned`.
  bool operator()(const NT *p, const NT *q, const NT *r)
  {
    return !misaligned(p, q, r);
  }

  /**
   * @brief Check if three points (`A`, `B` and `C`) are misaligned (NOT
   * collinear).
   * @param A_B_C Given in generic points.
   * @return true if the points are misaligned (NOT collinear).
   */
  bool misaligned(const GPoint3 &A, const GPoint3 &B, const GPoint3 &C)
  {
    return (is_sign_posneg(OrientOn2D().on_xy(A, B, C)) ||
            is_sign_posneg(OrientOn2D().on_yz(A, B, C)) ||
            is_sign_posneg(OrientOn2D().on_zx(A, B, C)));
  }

  /**
   * @brief Check if three points (`A`, `B` and `C`) are misaligned (NOT
   * collinear).
   * @param A_B_C Given in number pointers.
   * @return true if the points are misaligned (NOT collinear).
   */
  bool misaligned(const NT *A, const NT *B, const NT *C)
  {
    return (is_sign_posneg(OrientOn2D().on_xy(A, B, C)) ||
            is_sign_posneg(OrientOn2D().on_yz(A, B, C)) ||
            is_sign_posneg(OrientOn2D().on_zx(A, B, C)));
  }

  /**
   * @brief Check if three points (`A`, `B` and `C`) are misaligned (NOT
   * collinear).
   *
   * Faster. It assumes that points are coplanar and the dominant normal
   * component is n_max (see MaxComponentInTriangleNormal).
   *
   * @param A_B_C Given in generic points.
   * @return true if the points are misaligned (NOT collinear).
   */
  bool misaligned(const GPoint3 &A, const GPoint3 &B, const GPoint3 &C,
                  int n_max)
  {
    return ((n_max == 2 && is_sign_posneg(OrientOn2D().on_xy(A, B, C))) ||
            (n_max == 0 && is_sign_posneg(OrientOn2D().on_yz(A, B, C))) ||
            (n_max == 1 && is_sign_posneg(OrientOn2D().on_zx(A, B, C))));
  }
};

template <typename Kernel>
class CollinearSort3K
{
public:
  using K = Kernel;

  using NT      = typename K::NT;
  using GPoint3 = typename K::GPoint3;

  using OrientOn2D = typename K::OrientOn2D;
  using LessThan3D = typename K::LessThan3D;

public:
  /**
   * @brief Sort three collinear points along the line.
   * @return A tuple contains three references that are ordered.
   */
  std::tuple<const GPoint3 &, const GPoint3 &, const GPoint3 &>
  operator()(const GPoint3 &p, const GPoint3 &q, const GPoint3 &r)
  {
    using CR = const GPoint3 &;
    using CP = const GPoint3 *;

#define SORT_ON_AXIS(axis)                              \
  if (LessThan3D().on_##axis(*a, *b) == Sign::POSITIVE) \
    std::swap(a, b);                                    \
  if (LessThan3D().on_##axis(*b, *c) == Sign::POSITIVE) \
    std::swap(b, c);                                    \
  if (LessThan3D().on_##axis(*a, *c) == Sign::POSITIVE) \
    std::swap(a, c);

    CP a = &p, b = &q, c = &r;
    if (LessThan3D().on_x(p, q) != Sign::ZERO ||
        LessThan3D().on_x(p, r) != Sign::ZERO ||
        LessThan3D().on_x(q, r) != Sign::ZERO)
    {
      SORT_ON_AXIS(x);
    }
    else if (LessThan3D().on_y(p, q) != Sign::ZERO ||
             LessThan3D().on_y(p, r) != Sign::ZERO ||
             LessThan3D().on_y(q, r) != Sign::ZERO)
    {
      SORT_ON_AXIS(y);
    }
    else if (LessThan3D().on_z(p, q) != Sign::ZERO ||
             LessThan3D().on_z(p, r) != Sign::ZERO ||
             LessThan3D().on_z(q, r) != Sign::ZERO)
    {
      SORT_ON_AXIS(z);
    }
#undef SORT_ON_AXIS

    return std::make_tuple<CR, CR, CR>(*a, *b, *c);
  }
};

/**
 * @brief Check if four points in 3D are coplanar.
 */
template <typename Kernel>
class CoplanarPoints3K
{
public:
  using K = Kernel;

  using NT      = typename K::NT;
  using GPoint3 = typename K::GPoint3;

  using Orient3D = typename K::Orient3D;

public:
  /**
   * @brief Check if `p` , `q` , `r` and `s` are coplanar.
   * @return true if they are coplanar, otherwise false.
   */
  bool operator()(const GPoint3 &p, const GPoint3 &q, const GPoint3 &r,
                  const GPoint3 &s)
  {
    return Orient3D()(p, q, r, s) == Sign::ZERO;
  }
};

#if 0 // When needed, figure out a better way to implement this.
/**
 * @brief CheckDegenerate3K implements several algorithms that check if a
 * primitive in 3D is degenerate.
 * @tparam Kernel
 */
template <typename Kernel>
class CheckDegenerate3K
{
public:
  using K = Kernel;

  using NT        = typename K::NT;
  using GPoint3   = typename K::GPoint3;
  using Segment3  = typename K::Segment3;
  using Triangle3 = typename K::Triangle3;

  using LessThan3D       = typename K::LessThan3D;
  using CollinearPoints3 = typename K::CollinearPoints3;
  using CollinearSort3   = typename K::CollinearSort3;

  struct NoDgn
  {
  };
  using DgnType = std::variant<NoDgn, GPoint3, Segment3>;

public:
  /**
   * @brief Check if a segment is degenerate. If it is degenerate, return the
   * degeneration type and geometry.
   * @return std::variant Void if no degeneration, otherwise it contains
   * primitives whose types are defined in this class \ref CheckDegenerate3K.
   * @retval PointT If the segment degenerate to point, return the point.
   */
  DgnType operator()(const Segment3 &segment)
  {
    if (LessThan3D().coincident(segment.start(), segment.end()))
      return DgnType{segment.start()}; // degenerate to point
    else
      return DgnType(); // contains NoDgn.
  }

  /**
   * @brief Check if a triangle is degenerate. If it is degenerate, return the
   * degeneration type and geometry.
   * @return std::variant Void if no degeneration, otherwise it contains
   * primitives whose types are defined in this class \ref CheckDegenerate3K.
   * @retval PointT If the triangle degenerates to point.
   * @retval Segment3 If the trianngle degenerates to segment.
   */
  DgnType operator()(const Triangle3 &triangle)
  {
    auto &t = triangle;

    if (LessThan3D().coincident(t.v0(), t.v1()) &&
        LessThan3D().coincident(t.v1(), t.v2()))
    {
      return DgnType{t.v0()}; // degenerate to point
    }
    else if (CollinearPoints3()(t.v0(), t.v1(), t.v2()))
    {
      auto [a, b, c] = CollinearSort3()(t.v0(), t.v1(), t.v2());
      return DgnType{Segment3(a, c)}; // degenerate to segment
    }
    else
      return DgnType(); // NoDgn
  }
};
#else
template <typename Kernel>
class CheckDegenerate3K
{
};
#endif

} // namespace OMC