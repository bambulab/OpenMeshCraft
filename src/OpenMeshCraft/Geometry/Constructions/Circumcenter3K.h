#pragma once

namespace OMC {

/**
 * @brief Construct circumcenter in 3D.
 * Support geometric primitives: Tetrahedron3, Triangle3, Segment3.
 * @tparam Kernel
 * @todo Support more geometric primitives.
 */
template <typename Kernel, bool _Filtered = false, bool _ForceExact = false>
class ConstructCircumcenter3K
{
public:
  using K = Kernel;

  static constexpr bool Filtered   = _Filtered;
  static constexpr bool ForceExact = _ForceExact;

  using NT = typename K::NT;
  using ET = typename K::ET;

  using ToET = typename K::ToET;
  using ToNT = typename K::ToNT;

  using Vec3    = typename K::Vec3;
  using EPoint3 = typename K::EPoint3;
  using GPoint3 = typename K::GPoint3;

  using Segment3     = typename K::Segment3;
  using Triangle3    = typename K::Triangle3;
  using Tetrahedron3 = typename K::Tetrahedron3;

  using Orient3D = typename K::Orient3D;
  using InSphere = typename K::InSphere;

public:
  /**
   * @brief Construct circumcenter for a segment defined by two points.
   * @return The circumcenter of the segment.
   */
  EPoint3 operator()(const EPoint3 &v0, const EPoint3 &v1) const;
  /**
   * @brief Construct circumcenter for a segment.
   * @return The circumcenter of the segment.
   */
  EPoint3 operator()(const Segment3 &seg) const;
  /**
   * @brief Construct circumcenter of two weighted points.
   * @return The circumcenter of two weighted points.
   */
  EPoint3 operator()(const EPoint3 &v0, const EPoint3 &v1, NT w0, NT w1) const;

  /**
   * @brief Construct circumcenter for a triangle defined by three points.
   * @return The circumcenter of the triangle.
   */
  EPoint3 operator()(const EPoint3 &v0, const EPoint3 &v1,
                     const EPoint3 &v2) const;
  /**
   * @brief Construct circumcenter for a triangle.
   * @return The circumcenter of the triangle.
   */
  EPoint3 operator()(const Triangle3 &tri) const;
  /**
   * @brief Construct circumcenter of three weighted points.
   * @return The circumcenter of three weighted points.
   */
  EPoint3 operator()(const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2,
                     NT w0, NT w1, NT w2) const;

  /**
   * @brief Construct circumcenter for a tetrahedron defined by four points.
   * @return The circumcenter of the tetrahedron.
   */
  EPoint3 operator()(const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2,
                     const EPoint3 &v3) const;
  /**
   * @brief Construct circumcenter for a tetrahedron.
   * @return The circumcenter of the tetrahedron.
   */
  EPoint3 operator()(const Tetrahedron3 &tet) const;
  /**
   * @brief Construct circumcenter of four weighted points.
   * @return The circumcenter of four weighted points.
   */
  EPoint3 operator()(const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2,
                     const EPoint3 &v3, NT w0, NT w1, NT w2, NT w3) const;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "Circumcenter3K.inl"
#endif