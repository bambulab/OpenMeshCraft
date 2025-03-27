#pragma once

#include "Bbox_Point.h"

namespace OMC {

/**
 * @brief Check if BoundingBox3 and Ray3 intersect.
 * @tparam Kernel
 */
template <typename Kernel>
class Bbox3_Ray3_DoIntersectK
{
public:
  using K            = Kernel;
  using NT           = typename K::NT;
  using Vec          = typename K::Vec3;
  using GPoint3      = typename K::GPoint3;
  using EPoint3      = typename K::EPoint3;
  using Ray3         = typename K::Ray3;
  using BoundingBox3 = typename K::BoundingBox3;

  using LessThan3D         = typename K::LessThan3D;
  using DotProductSignOn2D = typename K::DotProductSignOn2D;

  using Box_Pnt_DoInter = Bbox_Point_DoIntersectK<Kernel>;

public:
  bool operator()(const BoundingBox3 &box, const Ray3 &ray) const
  {
    const EPoint3 &start = ray.start();
    const Vec     &dir   = ray.direction();

    if (Box_Pnt_DoInter()(box, start))
      return true;

    Sign ret;

    auto less_x = [](const GPoint3 &lhs, const GPoint3 &rhs)
    { return LessThan3D().on_x(lhs, rhs) == Sign::NEGATIVE; };
    auto less_y = [](const GPoint3 &lhs, const GPoint3 &rhs)
    { return LessThan3D().on_y(lhs, rhs) == Sign::NEGATIVE; };
    auto less_z = [](const GPoint3 &lhs, const GPoint3 &rhs)
    { return LessThan3D().on_z(lhs, rhs) == Sign::NEGATIVE; };

    const EPoint3 &bmin = box.min_bound();
    const EPoint3 &bmax = box.max_bound();

    // First, we calculate the interval on the line that is inside between box
    // on each dimension. The interval is represented by two end points on the
    // line. The two end points are further represented by parameters of the
    // line: tmin and tmax.
    // For exactness, tmin and tmax are represented in rational form: tmin =
    // rmin/d, tmax = rmax/d, where d is distance between two end points.
    bool x_degenerate = dir.x() == NT(0);
    bool y_degenerate = dir.y() == NT(0);
    bool z_degenerate = dir.z() == NT(0);
    bool x_reverse, y_reverse, z_reverse;
    NT   rminx, rmaxx, rminy, rmaxy, rminz, rmaxz;

    // -----------------------------------
    // treat x coord
    // -----------------------------------
    if (dir.x() >= NT(0.))
    {
      if (less_x(bmax, start)) // box.max.x < start.x
        return false;
      rmaxx     = NT(bmax.x());
      rminx     = NT(bmin.x());
      // tmax = (rmaxx - start.x) / dir.x
      // tmin = (rminx - start.x) / dir.x
      x_reverse = false;
    }
    else // dir.x < 0
    {
      if (less_x(start, bmin)) // start.x < bmin.x
        return false;
      rmaxx     = NT(bmin.x());
      rminx     = NT(bmax.x());
      // tmax = (rmaxx - start.x) / dir.x
      // tmin = (rminx - start.x) / dir.x
      // To make denominator > 0, adjust to:
      // tmax = (start.x - rmaxx) / (-dir.x)
      // tmin = (start.x - rminx) / (-dir.x)
      x_reverse = true;
    }

    // -----------------------------------
    // treat y coord (totally same as x)
    // -----------------------------------
    if (dir.y() >= NT(0.))
    {
      if (less_y(bmax, start)) // box.max.y < start.y
        return false;
      rmaxy     = NT(bmax.y());
      rminy     = NT(bmin.y());
      // tmax = (rmaxy - start.y) / dir.y
      // tmin = (rminy - start.y) / dir.y
      y_reverse = false;
    }
    else // dir.y < 0
    {
      if (less_y(start, bmin)) // start.y < bmin.y
        return false;
      rmaxy     = NT(bmin.y());
      rminy     = NT(bmax.y());
      // tmax = (rmaxy - start.y) / dir.y
      // tmin = (rminy - start.y) / dir.y
      // To make denominator > 0, adjust to:
      // tmax = (start.y - rmaxy) / (-dir.y)
      // tmin = (start.y - rminy) / (-dir.y)
      y_reverse = true;
    }

    // check if intervals on x, y and z overlap each other.

    if (!x_degenerate || !y_degenerate)
    {
      // between x,y
      // (1) tmaxx < tminy ?
      //  => (rmaxx - start.x) / dir.x < (rminy - start.y) / dir.y ?
      //  => (rmaxx - start.x) * dir.y < (rminy - start.y) * dir.x ?
      //  => (rmaxx - start.x) * dir.y - (rminy - start.y) * dir.x < 0 ?
      //     (Reverse sign if x_reverse and y_reverse are not same)
      //  => DotProductSignOn2D.on_xy
      //     ((rmaxx, rminy, 0.), (dir.y, dir.x, 0.), start, (0.,0.,0.)) < 0 ?
      ret = DotProductSignOn2D().on_xy(EPoint3(rmaxx, rminy, NT(0.)),
                                       EPoint3(dir.y(), -dir.x(), NT(0.)),
                                       start, EPoint3(NT(0.), NT(0.), NT(0.)));
      if ((x_reverse == y_reverse && ret == Sign::NEGATIVE) ||
          (x_reverse != y_reverse && ret == Sign::POSITIVE))
        return false;
      // (2) tmaxy < tminx ?
      //  => (rmaxy - start.y) / dir.y < (rminx - start.x) / dir.x ?
      //  => (rmaxy - start.y) * dir.x < (rminx - start.x) * dir.y ?
      //  => (rminx - start.x) * dir.y - (rmaxy - start.y) * dir.x > 0 ?
      //     (Reverse sign if x_reverse and y_reverse are not same)
      //  => DotProductSignOn2D.on_xy
      //     ((rminx, rmaxy, 0.), (dir.y, dir.x, 0.), start, (0.,0.,0.)) > 0 ?
      ret = DotProductSignOn2D().on_xy(EPoint3(rminx, rmaxy, NT(0.)),
                                       EPoint3(dir.y(), -dir.x(), NT(0.)),
                                       start, EPoint3(NT(0.), NT(0.), NT(0.)));
      if ((x_reverse == y_reverse && ret == Sign::POSITIVE) ||
          (x_reverse != y_reverse && ret == Sign::NEGATIVE))
        return false;
    }

    // -----------------------------------
    // treat z coord (totally same as x and y)
    // -----------------------------------
    if (dir.z() >= NT(0.))
    {
      if (less_z(bmax, start)) // box.max.z < start.z
        return false;
      rmaxz     = NT(bmax.z());
      rminz     = NT(bmin.z());
      // tmax = (rmaxz - start.z) / dir.z
      // tmin = (rminz - start.z) / dir.z
      z_reverse = false;
    }
    else // dir.z < 0
    {
      if (less_z(start, bmin)) // start.z < bmin.z
        return false;
      rmaxz     = NT(bmin.z());
      rminz     = NT(bmax.z());
      // tmax = (rmaxz - start.z) / dir.z
      // tmin = (rminz - start.z) / dir.z
      // To make denominator > 0, adjust to:
      // tmax = (start.z - rmaxz) / (-dir.z)
      // tmin = (start.z - rminz) / (-dir.z)
      z_reverse = true;
    }

    if (!y_degenerate || !z_degenerate)
    {
      ret = DotProductSignOn2D().on_yz(EPoint3(NT(0.), rmaxy, rminz),
                                       EPoint3(NT(0.), dir.z(), -dir.y()),
                                       start, EPoint3(NT(0.), NT(0.), NT(0.)));
      if ((y_reverse == z_reverse && ret == Sign::NEGATIVE) ||
          (y_reverse != z_reverse && ret == Sign::POSITIVE))
        return false;

      ret = DotProductSignOn2D().on_yz(EPoint3(NT(0.), rminy, rmaxz),
                                       EPoint3(NT(0.), dir.z(), -dir.y()),
                                       start, EPoint3(NT(0.), NT(0.), NT(0.)));
      if ((y_reverse == z_reverse && ret == Sign::POSITIVE) ||
          (y_reverse != z_reverse && ret == Sign::NEGATIVE))
        return false;
    }

    if (!z_degenerate || !x_degenerate)
    {
      ret = DotProductSignOn2D().on_zx(EPoint3(rmaxx, NT(0.), rminz),
                                       EPoint3(dir.z(), NT(0.), -dir.x()),
                                       start, EPoint3(NT(0.), NT(0.), NT(0.)));
      if ((z_reverse == x_reverse && ret == Sign::NEGATIVE) ||
          (z_reverse != x_reverse && ret == Sign::POSITIVE))
        return false;

      ret = DotProductSignOn2D().on_zx(EPoint3(rminx, NT(0.), rmaxz),
                                       EPoint3(dir.z(), NT(0.), -dir.x()),
                                       start, EPoint3(NT(0.), NT(0.), NT(0.)));
      if ((z_reverse == x_reverse && ret == Sign::POSITIVE) ||
          (z_reverse != x_reverse && ret == Sign::NEGATIVE))
        return false;
    }

    return true;
  }
};

} // namespace OMC