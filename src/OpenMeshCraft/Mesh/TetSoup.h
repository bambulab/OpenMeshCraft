#pragma once

#include "OpenMeshCraft/Geometry/Primitives/Point3T.h"
#include "OpenMeshCraft/Geometry/Primitives/Vector3T.h"
#include "OpenMeshCraft/Geometry/Primitives/Vector4T.h"

#include "OpenMeshCraft/Utils/IndexDef.h"

#include <vector>

namespace OMC {

class TetSoupTraits
{
public:
  using VecT        = Vec3T<double>;
  using NormalT     = Vec3T<double>;
  using PointT      = Point3T<double>;
  /// The orientation of the triangle vertices (a, b, c) is determined by
  /// the convention that the cross product of (b - a) and (c - a) points to the
  /// triangle's normal.
  using Triangle    = Vec3T<index_t>;
  /// The orientation of the tetrahedron vertices (a, b, c, d) is determined by
  /// the convention that the cross product of (b - a) and (c - a) points
  /// toward d (i.e., the tetrahedron has a positive volume when calculating
  /// orient3d(a, b, c, d)).
  using Tetrahedron = Vec4T<index_t>;
  using Points      = std::vector<PointT>;
  using Normals     = std::vector<NormalT>;
  using Triangles   = std::vector<Triangle>;
  using Tetrahedra  = std::vector<Tetrahedron>;
};

} // namespace OMC