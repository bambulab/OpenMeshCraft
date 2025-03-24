#pragma once

#include "Circumcenter3K.h"

#include "OpenMeshCraft/Geometry/Determinant.h"
#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

namespace OMC {
template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const EPoint3 &v0, const EPoint3 &v1) const -> EPoint3
{
  return (v0 + v1) * 0.5;
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const Segment3 &seg) const -> EPoint3
{
  return operator()(seg.start(), seg.end());
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(const EPoint3 &v0,
                                                           const EPoint3 &v1,
                                                           NT w0, NT w1) const
  -> EPoint3
{
  Vec3 delta = v1 - v0;
  NT   len   = delta.dot(delta);
  NT   inv   = NT(1) / (NT(2) * len);
  NT   alpha = 1 / NT(2) + (w0 - w1) * inv;

  return v0 + alpha * delta;
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2) const -> EPoint3
{
  NT numx, numy, numz, den;

  determinants_for_circumcenter<NT>(v0.x(), v0.y(), v0.z(), v1.x(), v1.y(),
                                    v1.z(), v2.x(), v2.y(), v2.z(), numx, numy,
                                    numz, den);

  if constexpr (!Filtered)
  { // Return the result without filtering
    NT inv = NT(1) / (NT(2) * den);
    return EPoint3(v0.x() + numx * inv, v0.y() - numy * inv,
                   v0.z() + numz * inv);
  }

  // Filter the result
  if (!(den == NT(0)))
  {
    NT      inv = NT(1) / (NT(2) * den);
    EPoint3 res(v0.x() + numx * inv, v0.y() - numy * inv, v0.z() + numz * inv);

    if (InSphere()(v0, v1, v2, res) == Sign::POSITIVE)
      return res;
  }

  // Calculate using exact numbers
  ToET to_et; // Convert NT to ET
  ToNT to_nt; // Convert ET to NT

  ET numx_rt, numy_rt, numz_rt, den_rt;
  determinants_for_circumcenter<ET>(to_et(v0.x()), to_et(v0.y()), to_et(v0.z()),
                                    to_et(v1.x()), to_et(v1.y()), to_et(v1.z()),
                                    to_et(v2.x()), to_et(v2.y()), to_et(v2.z()),
                                    numx_rt, numy_rt, numz_rt, den_rt);
  ET inv_rt = ET(1) / (ET(2) * den_rt);

  return EPoint3(to_nt(to_et(v0.x()) + numx_rt * inv_rt),
                 to_nt(to_et(v0.y()) - numy_rt * inv_rt),
                 to_nt(to_et(v0.z()) + numz_rt * inv_rt));
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const Triangle3 &tri) const -> EPoint3
{
  return operator()(tri.v0(), tri.v1(), tri.v2());
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(const EPoint3 &v0,
                                                           const EPoint3 &v1,
                                                           const EPoint3 &v2,
                                                           NT w0, NT w1,
                                                           NT w2) const
  -> EPoint3
{
  NT numx, numy, numz, den;

  determinants_for_weighted_circumcenter<NT>(v0.x(), v0.y(), v0.z(), w0, v1.x(),
                                             v1.y(), v1.z(), w1, v2.x(), v2.y(),
                                             v2.z(), w2, numx, numy, numz, den);

  if constexpr (!Filtered)
  { // Return the result without filtering
    NT inv = NT(1) / (NT(2) * den);
    return EPoint3(v0.x() + numx * inv, v0.y() - numy * inv,
                   v0.z() + numz * inv);
  }

  // Filter the result
  if (!(den == NT(0)))
  {
    NT      inv = NT(1) / (NT(2) * den);
    EPoint3 res(v0.x() + numx * inv, v0.y() - numy * inv, v0.z() + numz * inv);

    if (InSphere()(v0, v1, v2, res) == Sign::POSITIVE)
      return res;
  }

  // Calculate using exact numbers
  ToET to_et; // Convert NT to ET
  ToNT to_nt; // Convert ET to NT

  ET numx_rt, numy_rt, numz_rt, den_rt;
  determinants_for_weighted_circumcenter<ET>(
    to_et(v0.x()), to_et(v0.y()), to_et(v0.z()), to_et(w0), to_et(v1.x()),
    to_et(v1.y()), to_et(v1.z()), to_et(w1), to_et(v2.x()), to_et(v2.y()),
    to_et(v2.z()), to_et(w2), numx_rt, numy_rt, numz_rt, den_rt);
  ET inv_rt = ET(1) / (ET(2) * den_rt);

  return EPoint3(to_nt(to_et(v0.x()) + numx_rt * inv_rt),
                 to_nt(to_et(v0.y()) - numy_rt * inv_rt),
                 to_nt(to_et(v0.z()) + numz_rt * inv_rt));
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2,
  const EPoint3 &v3) const -> EPoint3
{
  NT numx, numy, numz, den;

  determinants_for_circumcenter<NT>(v0.x(), v0.y(), v0.z(), v1.x(), v1.y(),
                                    v1.z(), v2.x(), v2.y(), v2.z(), v3.x(),
                                    v3.y(), v3.z(), numx, numy, numz, den);

  if constexpr (!Filtered)
  { // Return the result without filtering
    NT inv = NT(1) / (NT(2) * den);
    return EPoint3(v0.x() + numx * inv, v0.y() - numy * inv,
                   v0.z() + numz * inv);
  }

  // Filter the result
  if (!(den == NT(0)))
  {
    NT      inv = NT(1) / (NT(2) * den);
    EPoint3 res(v0.x() + numx * inv, v0.y() - numy * inv, v0.z() + numz * inv);

    Sign ori       = Orient3D()(v0, v1, v2, v3);
    Sign in_sphere = InSphere()(v0, v1, v2, v3, res);
    if ((ori == Sign::POSITIVE && in_sphere == Sign::POSITIVE) ||
        (ori == Sign::NEGATIVE && in_sphere == Sign::NEGATIVE))
      return res;
  }

  // Calculate using exact numbers
  ToET to_et; // Convert NT to ET
  ToNT to_nt; // Convert ET to NT

  ET numx_rt, numy_rt, numz_rt, den_rt;
  determinants_for_circumcenter<ET>(
    to_et(v0.x()), to_et(v0.y()), to_et(v0.z()), to_et(v1.x()), to_et(v1.y()),
    to_et(v1.z()), to_et(v2.x()), to_et(v2.y()), to_et(v2.z()), to_et(v3.x()),
    to_et(v3.y()), to_et(v3.z()), numx_rt, numy_rt, numz_rt, den_rt);
  ET inv_rt = ET(1) / (ET(2) * den_rt);

  return EPoint3(to_nt(to_et(v0.x()) + numx_rt * inv_rt),
                 to_nt(to_et(v0.y()) - numy_rt * inv_rt),
                 to_nt(to_et(v0.z()) + numz_rt * inv_rt));
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const Tetrahedron3 &tet) const -> EPoint3
{
  return operator()(tet.v0(), tet.v1(), tet.v2(), tet.v3());
}

template <typename Kernel, bool Filtered>
auto ConstructCircumcenter3K<Kernel, Filtered>::operator()(
  const EPoint3 &v0, const EPoint3 &v1, const EPoint3 &v2, const EPoint3 &v3,
  NT w0, NT w1, NT w2, NT w3) const -> EPoint3
{
  NT numx, numy, numz, den;

  determinants_for_weighted_circumcenter<NT>(
    v0.x(), v0.y(), v0.z(), w0, v1.x(), v1.y(), v1.z(), w1, v2.x(), v2.y(),
    v2.z(), w2, v3.x(), v3.y(), v3.z(), w3, numx, numy, numz, den);

  if constexpr (!Filtered)
  { // Return the result without filtering
    NT inv = NT(1) / (NT(2) * den);
    return EPoint3(v0.x() + numx * inv, v0.y() - numy * inv,
                   v0.z() + numz * inv);
  }

  // Filter the result
  if (!(den == NT(0)))
  {
    NT      inv = NT(1) / (NT(2) * den);
    EPoint3 res(v0.x() + numx * inv, v0.y() - numy * inv, v0.z() + numz * inv);

    Sign ori       = Orient3D()(v0, v1, v2, v3);
    Sign in_sphere = InSphere()(v0, v1, v2, v3, res);
    if ((ori == Sign::POSITIVE && in_sphere == Sign::POSITIVE) ||
        (ori == Sign::NEGATIVE && in_sphere == Sign::NEGATIVE))
      return res;
  }

  // Calculate using exact numbers
  ToET to_et; // Convert NT to ET
  ToNT to_nt; // Convert ET to NT

  ET numx_rt, numy_rt, numz_rt, den_rt;
  determinants_for_weighted_circumcenter<ET>(
    to_et(v0.x()), to_et(v0.y()), to_et(v0.z()), to_et(w0), to_et(v1.x()),
    to_et(v1.y()), to_et(v1.z()), to_et(w1), to_et(v2.x()), to_et(v2.y()),
    to_et(v2.z()), to_et(w2), to_et(v3.x()), to_et(v3.y()), to_et(v3.z()),
    to_et(w3), numx_rt, numy_rt, numz_rt, den_rt);
  ET inv_rt = ET(1) / (ET(2) * den_rt);

  return EPoint3(to_nt(to_et(v0.x()) + numx_rt * inv_rt),
                 to_nt(to_et(v0.y()) - numy_rt * inv_rt),
                 to_nt(to_et(v0.z()) + numz_rt * inv_rt));
}

} // namespace OMC