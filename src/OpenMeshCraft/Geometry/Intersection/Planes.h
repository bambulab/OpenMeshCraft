#pragma once

#include "OpenMeshCraft/Geometry/Determinant.h"

namespace OMC {

/**
 * @brief Intersection of planes in 3D.
 * @tparam Kernel.
 */
template <typename Kernel>
class Planes_Intersection3K
{
public:
  using K = Kernel;

  using NT      = typename K::NT;
  using Vec3    = typename K::Vec3;
  using EPoint3 = typename K::EPoint3;

  using ImplicitPlane3 = typename K::ImplicitPlane3;

public:
  EPoint3 operator()(const ImplicitPlane3 &f, const ImplicitPlane3 &g,
                     const ImplicitPlane3 &h) const
  {
    // clang-format off
    NT x = determinant<NT>(-f.d(), f.b(), f.c(),
                           -g.d(), g.b(), g.c(),
                           -h.d(), h.b(), h.c());
    NT y = determinant<NT>(f.a(), -f.d(), f.c(),
                           g.a(), -g.d(), g.c(),
                           h.a(), -h.d(), h.c());
    NT z = determinant<NT>(f.a(), f.b(), -f.d(),
                           g.a(), g.b(), -g.d(),
                           h.a(), h.b(), -h.d());
    NT w = determinant<NT>(f.a(), f.b(), f.c(),
                           g.a(), g.b(), g.c(),
                           h.a(), h.b(), h.c());
    // clang-format on
    return EPoint3(x / w, y / w, z / w);
  }
};

} // namespace OMC