#pragma once

#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"
#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
#define CHECK_FOR_XYZERFLOWS

namespace OMC {

/*********************************************************************/
/* Forward Declarations (hand)****************************************/
/*********************************************************************/

inline int maxComponentInTriangleNormal(double ov1x, double ov1y, double ov1z,
                                        double ov2x, double ov2y, double ov2z,
                                        double ov3x, double ov3y, double ov3z);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline int maxComponentInTriangleNormal_filtered(double ov1x, double ov1y,
                                                 double ov1z, double ov2x,
                                                 double ov2y, double ov2z,
                                                 double ov3x, double ov3y,
                                                 double ov3z)
{
  double v3x  = ov3x - ov2x;
  double v3y  = ov3y - ov2y;
  double v3z  = ov3z - ov2z;
  double v2x  = ov2x - ov1x;
  double v2y  = ov2y - ov1y;
  double v2z  = ov2z - ov1z;
  double nvx1 = v2y * v3z;
  double nvx2 = v2z * v3y;
  double nvx  = nvx1 - nvx2;
  double nvy1 = v3x * v2z;
  double nvy2 = v3z * v2x;
  double nvy  = nvy1 - nvy2;
  double nvz1 = v2x * v3y;
  double nvz2 = v2y * v3x;
  double nvz  = nvz1 - nvz2;

  double nvxc = fabs(nvx);
  double nvyc = fabs(nvy);
  double nvzc = fabs(nvz);
  double nv   = nvxc;
  int    dim  = 0;
  if (nvyc > nv)
  {
    nv  = nvyc;
    dim = 1;
  }
  if (nvzc > nv)
  {
    nv  = nvzc;
    dim = 2;
  }

  double eps = 8.88720573725927976811e-16, max1, max2;
  if (dim == 0)
  {
    max1 = fabs(v2y) >= fabs(v2z) ? fabs(v2y) : fabs(v2z);
    max2 = fabs(v3y) >= fabs(v3z) ? fabs(v3y) : fabs(v3z);
  }
  else if (dim == 1)
  {
    max1 = fabs(v2x) >= fabs(v2z) ? fabs(v2x) : fabs(v2z);
    max2 = fabs(v3x) >= fabs(v3z) ? fabs(v3x) : fabs(v3z);
  }
  else // dim==2
  {
    max1 = fabs(v2x) >= fabs(v2y) ? fabs(v2x) : fabs(v2y);
    max2 = fabs(v3x) >= fabs(v3y) ? fabs(v3x) : fabs(v3y);
  }
  if (nv > eps * max1 * max2)
    return dim;

  return -1;
}

inline int maxComponentInTriangleNormal_interval(
  IntervalNumber<std::false_type> ov1x, IntervalNumber<std::false_type> ov1y,
  IntervalNumber<std::false_type> ov1z, IntervalNumber<std::false_type> ov2x,
  IntervalNumber<std::false_type> ov2y, IntervalNumber<std::false_type> ov2z,
  IntervalNumber<std::false_type> ov3x, IntervalNumber<std::false_type> ov3y,
  IntervalNumber<std::false_type> ov3z)
{
  using IT = IntervalNumber<std::false_type>;
  IT::Protector P;

  IT v3x  = ov3x - ov2x;
  IT v3y  = ov3y - ov2y;
  IT v3z  = ov3z - ov2z;
  IT v2x  = ov2x - ov1x;
  IT v2y  = ov2y - ov1y;
  IT v2z  = ov2z - ov1z;
  IT nvx1 = v2y * v3z;
  IT nvx2 = v2z * v3y;
  IT nvx  = nvx1 - nvx2;
  IT nvy1 = v3x * v2z;
  IT nvy2 = v3z * v2x;
  IT nvy  = nvy1 - nvy2;
  IT nvz1 = v2x * v3y;
  IT nvz2 = v2y * v3x;
  IT nvz  = nvz1 - nvz2;

  int    dim = -1;
  double nv  = 0.;
  if (nvx.is_sign_reliable())
  {
    nv  = fabs(nvx.inf() + nvx.sup());
    dim = 0;
  }
  if (nvy.is_sign_reliable())
  {
    nv  = std::max(nv, fabs(nvy.inf() + nvy.sup()));
    dim = 1;
  }
  if (nvz.is_sign_reliable())
  {
    nv  = std::max(nv, fabs(nvz.inf() + nvz.sup()));
    dim = 2;
  }

  return dim;
}

inline int maxComponentInTriangleNormal_expansion(double ov1x, double ov1y,
                                                  double ov1z, double ov2x,
                                                  double ov2y, double ov2z,
                                                  double ov3x, double ov3y,
                                                  double ov3z)
{
  expansionObject o;
  double          v3x[2];
  o.Two_Diff(ov3x, ov2x, v3x);
  double v3y[2];
  o.Two_Diff(ov3y, ov2y, v3y);
  double v3z[2];
  o.Two_Diff(ov3z, ov2z, v3z);
  double v2x[2];
  o.Two_Diff(ov2x, ov1x, v2x);
  double v2y[2];
  o.Two_Diff(ov2y, ov1y, v2y);
  double v2z[2];
  o.Two_Diff(ov2z, ov1z, v2z);
  double nvx1[8];
  o.Two_Two_Prod(v2y, v3z, nvx1);
  double nvx2[8];
  o.Two_Two_Prod(v2z, v3y, nvx2);
  double nvx[16];
  int    nvx_len = o.Gen_Diff(8, nvx1, 8, nvx2, nvx);
  double nvy1[8];
  o.Two_Two_Prod(v3x, v2z, nvy1);
  double nvy2[8];
  o.Two_Two_Prod(v3z, v2x, nvy2);
  double nvy[16];
  int    nvy_len = o.Gen_Diff(8, nvy1, 8, nvy2, nvy);
  double nvz1[8];
  o.Two_Two_Prod(v2x, v3y, nvz1);
  double nvz2[8];
  o.Two_Two_Prod(v2y, v3x, nvz2);
  double nvz[16];
  int    nvz_len = o.Gen_Diff(8, nvz1, 8, nvz2, nvz);

  double nvxc = fabs(nvx[nvx_len - 1]);
  double nvyc = fabs(nvy[nvy_len - 1]);
  double nvzc = fabs(nvz[nvz_len - 1]);
  double nv   = nvxc;
  if (nvyc > nv)
    nv = nvyc;
  if (nvzc > nv)
    return 2;
  if (nv == nvxc)
    return 0;
  return 1;
}

inline int maxComponentInTriangleNormal(double ov1x, double ov1y, double ov1z,
                                        double ov2x, double ov2y, double ov2z,
                                        double ov3x, double ov3y, double ov3z)
{
  int ret;
  ret = maxComponentInTriangleNormal_filtered(ov1x, ov1y, ov1z, ov2x, ov2y,
                                              ov2z, ov3x, ov3y, ov3z);
  if (ret >= 0)
    return ret;
  ret = maxComponentInTriangleNormal_interval(ov1x, ov1y, ov1z, ov2x, ov2y,
                                              ov2z, ov3x, ov3y, ov3z);
  if (ret >= 0)
    return ret;
  return maxComponentInTriangleNormal_expansion(ov1x, ov1y, ov1z, ov2x, ov2y,
                                                ov2z, ov3x, ov3y, ov3z);
}

} // namespace OMC