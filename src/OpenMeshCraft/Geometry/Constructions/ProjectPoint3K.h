#pragma once

namespace OMC {

/**
 * @brief ProjectPoint3K implement several project algorithms that project a
 * point to different primitives, such as segment and triangle.
 * @tparam Kernel.
 */
template <typename Kernel>
class ProjectPoint3K
{
public:
  using K = Kernel;

  using NT           = typename K::NT;
  using Vec3         = typename K::Vec3;
  using EPoint3      = typename K::EPoint3;
  using GPoint3      = typename K::GPoint3;
  using BoundingBox3 = typename K::BoundingBox3;
  using Segment3     = typename K::Segment3;
  using Triangle3    = typename K::Triangle3;

  using ToEP = typename K::ToEP;

  using Orient3D   = typename K::Orient3D;
  using LessThan3D = typename K::LessThan3D;

  using CheckDegenerate3 = typename K::CheckDegenerate3;
  using ConstructNormal3 = typename K::ConstructNormal3;

public:
  /**
   * @brief Project a point to segment.
   * @return the projected point.
   */
  EPoint3 operator()(const Segment3 &segment, const GPoint3 &point) const;

  /**
   * @brief Project a point to triangle.
   * @return the projected point.
   */
  EPoint3 operator()(const Triangle3 &triangle, const GPoint3 &point) const;

  /**
   * @brief Project a point to box.
   * @return the projected point.
   */
  EPoint3 operator()(const BoundingBox3 &bbox, const GPoint3 &point) const;

private:
  /**
   * @brief When segment is not degenerate, project point to it.
   * @return GPoint3 the projected point.
   */
  EPoint3 proj_to_segment(const Segment3 &segment, const GPoint3 &point) const;

  /**
   * @brief When triangle is not degenerate, project point to it.
   * @return GPoint3 the projected point.
   */
  EPoint3 proj_to_triangle(const Triangle3 &triangle,
                           const GPoint3   &point) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "ProjectPoint3K.inl"
#endif