#pragma once

#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"

namespace OMC {

template <typename IT>
bool lambda2d_SSI_interval(IT ea1x, IT ea1y, IT ea2x, IT ea2y, IT eb1x, IT eb1y,
                           IT eb2x, IT eb2y, IT &lambda_x, IT &lambda_y,
                           IT &lambda_det)
{
  typename IT::Protector P;

  IT t1a(ea1x * ea2y);
  IT t1b(ea2x * ea1y);
  IT t1(t1a - t1b);
  IT tx2(eb1x - eb2x);
  IT t3a(eb1x * eb2y);
  IT t3b(eb2x * eb1y);
  IT t3(t3a - t3b);
  IT tx4(ea1x - ea2x);
  IT ty2(eb1y - eb2y);
  IT ty4(ea1y - ea2y);
  IT lxa(t1 * tx2);
  IT lxb(t3 * tx4);
  lambda_x = lxa - lxb;
  IT lya(t1 * ty2);
  IT lyb(t3 * ty4);
  lambda_y = lya - lyb;
  IT deta(tx4 * ty2);
  IT detb(tx2 * ty4);
  lambda_det = deta - detb;

  return (lambda_det.is_sign_reliable());
}

template <typename ET>
void lambda2d_SSI_exact(ET ea1x, ET ea1y, ET ea2x, ET ea2y, ET eb1x, ET eb1y,
                        ET eb2x, ET eb2y, ET &lambda_x, ET &lambda_y,
                        ET &lambda_det)
{
  ET t1a = ea1x * ea2y;
  ET t1b = ea2x * ea1y;
  ET t1  = t1a - t1b;
  ET tx2 = eb1x - eb2x;
  ET t3a = eb1x * eb2y;
  ET t3b = eb2x * eb1y;
  ET t3  = t3a - t3b;
  ET tx4 = ea1x - ea2x;
  ET ty2 = eb1y - eb2y;
  ET ty4 = ea1y - ea2y;
  ET lxa = t1 * tx2;
  ET lxb = t3 * tx4;

  lambda_x   = lxa - lxb;
  ET lya     = t1 * ty2;
  ET lyb     = t3 * ty4;
  lambda_y   = lya - lyb;
  ET deta    = tx4 * ty2;
  ET detb    = tx2 * ty4;
  lambda_det = deta - detb;
}

template <typename IT>
bool lambda3d_SSI_interval(IT xa, IT ya, IT za, IT xb, IT yb, IT zb, IT xp,
                           IT yp, IT xq, IT yq, IT &lambda_x, IT &lambda_y,
                           IT &lambda_z, IT &lambda_d)
{
  typename IT::Protector P;

  IT xba   = xb - xa;
  IT yba   = yb - ya;
  IT zba   = zb - za;
  IT xap   = xa - xp;
  IT yap   = ya - yp;
  IT yqp   = yq - yp;
  IT xqp   = xq - xp;
  IT c1    = xap * yqp;
  IT c2    = xqp * yap;
  IT c3    = xba * yqp;
  IT c4    = xqp * yba;
  IT c12   = c1 - c2;
  lambda_d = c4 - c3;
  IT xf    = xba * c12;
  IT xs    = xa * lambda_d;
  lambda_x = xf + xs;
  IT yf    = yba * c12;
  IT ys    = ya * lambda_d;
  lambda_y = yf + ys;
  IT zf    = zba * c12;
  IT zs    = za * lambda_d;
  lambda_z = zf + zs;
  return lambda_d.is_sign_reliable();
}

template <typename ET>
void lambda3d_SSI_exact(ET xa, ET ya, ET za, ET xb, ET yb, ET zb, ET xp, ET yp,
                        ET xq, ET yq, ET &lambda_x, ET &lambda_y, ET &lambda_z,
                        ET &lambda_d)
{
  ET xba   = xb - xa;
  ET yba   = yb - ya;
  ET zba   = zb - za;
  ET xap   = xa - xp;
  ET yap   = ya - yp;
  ET yqp   = yq - yp;
  ET xqp   = xq - xp;
  ET c1    = xap * yqp;
  ET c2    = xqp * yap;
  ET c3    = xba * yqp;
  ET c4    = xqp * yba;
  ET c12   = c1 - c2;
  lambda_d = c4 - c3;
  ET xf    = xba * c12;
  ET xs    = xa * lambda_d;
  lambda_x = xf + xs;
  ET yf    = yba * c12;
  ET ys    = ya * lambda_d;
  lambda_y = yf + ys;
  ET zf    = zba * c12;
  ET zs    = za * lambda_d;
  lambda_z = zf + zs;
}

template <typename IT>
bool lambda3d_LNC_interval(IT px, IT py, IT pz, IT qx, IT qy, IT qz, IT t,
                           IT &lambda_x, IT &lambda_y, IT &lambda_z,
                           IT &lambda_d)
{
  typename IT::Protector P;

  IT vx    = px - qx;
  IT vy    = py - qy;
  IT vz    = pz - qz;
  IT vxt   = vx * t;
  IT vyt   = vy * t;
  IT vzt   = vz * t;
  lambda_x = px - vxt;
  lambda_y = py - vyt;
  lambda_z = pz - vzt;
  lambda_d = 1;
  return true;
}

template <typename ET>
void lambda3d_LNC_exact(ET px, ET py, ET pz, ET qx, ET qy, ET qz, ET t,
                        ET &lambda_x, ET &lambda_y, ET &lambda_z, ET &lambda_d)
{
  ET vx    = px - qx;
  ET vy    = py - qy;
  ET vz    = pz - qz;
  ET vxt   = vx * t;
  ET vyt   = vy * t;
  ET vzt   = vz * t;
  lambda_x = px - vxt;
  lambda_y = py - vyt;
  lambda_z = pz - vzt;
  lambda_d = 1;
}

inline void lambda3d_LNC_expansion(double px, double py, double pz, double qx,
                                   double qy, double qz, double t,
                                   double **lambda_x, int &lambda_x_len,
                                   double **lambda_y, int &lambda_y_len,
                                   double **lambda_z, int &lambda_z_len,
                                   double **lambda_d, int &lambda_d_len)
{
  expansionObject o;
  double          vx[2];
  o.Two_Diff(px, qx, vx);
  double vy[2];
  o.Two_Diff(py, qy, vy);
  double vz[2];
  o.Two_Diff(pz, qz, vz);
  double vxt[4];
  o.Two_One_Prod(vx, t, vxt);
  double vyt[4];
  o.Two_One_Prod(vy, t, vyt);
  double vzt[4];
  o.Two_One_Prod(vz, t, vzt);
  lambda_x_len =
    o.Gen_Diff_With_PreAlloc(1, &px, 4, vxt, lambda_x, lambda_x_len);
  lambda_y_len =
    o.Gen_Diff_With_PreAlloc(1, &py, 4, vyt, lambda_y, lambda_y_len);
  lambda_z_len =
    o.Gen_Diff_With_PreAlloc(1, &pz, 4, vzt, lambda_z, lambda_z_len);
  if (lambda_d_len == 0)
    *lambda_d = AllocDoubles(1);
  (*lambda_d)[0] = 1;
  lambda_d_len   = 1;
}

template <typename IT>
bool lambda3d_LPI_interval(IT px, IT py, IT pz, IT qx, IT qy, IT qz, IT rx,
                           IT ry, IT rz, IT sx, IT sy, IT sz, IT tx, IT ty,
                           IT tz, IT &lambda_d, IT &lambda_x, IT &lambda_y,
                           IT &lambda_z)
{
  typename IT::Protector P;

  IT a11(px - qx);
  IT a12(py - qy);
  IT a13(pz - qz);
  IT a21(sx - rx);
  IT a22(sy - ry);
  IT a23(sz - rz);
  IT a31(tx - rx);
  IT a32(ty - ry);
  IT a33(tz - rz);
  IT tv1(a22 * a33);
  IT tv2(a23 * a32);
  IT a2233(tv1 - tv2);
  IT tv3(a21 * a33);
  IT tv4(a23 * a31);
  IT a2133(tv3 - tv4);
  IT tv5(a21 * a32);
  IT tv6(a22 * a31);
  IT a2132(tv5 - tv6);
  IT tv7(a11 * a2233);
  IT tv8(a12 * a2133);
  IT tv9(a13 * a2132);
  IT tt1(tv7 - tv8);
  lambda_d = tt1 + tv9;
  IT px_rx(px - rx);
  IT py_ry(py - ry);
  IT pz_rz(pz - rz);
  IT tt2(py_ry * a2133);
  IT tt3(px_rx * a2233);
  IT tt4(pz_rz * a2132);
  IT tt5(tt3 + tt4);
  IT n(tt5 - tt2);
  IT ax(a11 * n);
  IT ay(a12 * n);
  IT az(a13 * n);
  IT dpx(lambda_d * px);
  IT dpy(lambda_d * py);
  IT dpz(lambda_d * pz);
  lambda_x = dpx - ax;
  lambda_y = dpy - ay;
  lambda_z = dpz - az;

  return (lambda_d.is_sign_reliable());
}

template <typename ET>
void lambda3d_LPI_exact(ET px, ET py, ET pz, ET qx, ET qy, ET qz, ET rx, ET ry,
                        ET rz, ET sx, ET sy, ET sz, ET tx, ET ty, ET tz,
                        ET &lambda_d, ET &lambda_x, ET &lambda_y, ET &lambda_z)
{
  ET a11   = px - qx;
  ET a12   = py - qy;
  ET a13   = pz - qz;
  ET a21   = sx - rx;
  ET a22   = sy - ry;
  ET a23   = sz - rz;
  ET a31   = tx - rx;
  ET a32   = ty - ry;
  ET a33   = tz - rz;
  ET tv1   = a22 * a33;
  ET tv2   = a23 * a32;
  ET a2233 = tv1 - tv2;
  ET tv3   = a21 * a33;
  ET tv4   = a23 * a31;
  ET a2133 = tv3 - tv4;
  ET tv5   = a21 * a32;
  ET tv6   = a22 * a31;
  ET a2132 = tv5 - tv6;
  ET tv7   = a11 * a2233;
  ET tv8   = a12 * a2133;
  ET tv9   = a13 * a2132;
  ET tt1   = tv7 - tv8;
  lambda_d = tt1 + tv9;
  ET px_rx = px - rx;
  ET py_ry = py - ry;
  ET pz_rz = pz - rz;
  ET tt2   = py_ry * a2133;
  ET tt3   = px_rx * a2233;
  ET tt4   = pz_rz * a2132;
  ET tt5   = tt3 + tt4;
  ET n     = tt5 - tt2;
  ET ax    = a11 * n;
  ET ay    = a12 * n;
  ET az    = a13 * n;
  ET dpx   = lambda_d * px;
  ET dpy   = lambda_d * py;
  ET dpz   = lambda_d * pz;
  lambda_x = dpx - ax;
  lambda_y = dpy - ay;
  lambda_z = dpz - az;
}

template <typename IT>
bool lambda3d_TPI_interval(IT ov1x, IT ov1y, IT ov1z, IT ov2x, IT ov2y, IT ov2z,
                           IT ov3x, IT ov3y, IT ov3z, IT ow1x, IT ow1y, IT ow1z,
                           IT ow2x, IT ow2y, IT ow2z, IT ow3x, IT ow3y, IT ow3z,
                           IT ou1x, IT ou1y, IT ou1z, IT ou2x, IT ou2y, IT ou2z,
                           IT ou3x, IT ou3y, IT ou3z, IT &lambda_x,
                           IT &lambda_y, IT &lambda_z, IT &lambda_d)
{
  typename IT::Protector P;

  IT v3x(ov3x - ov2x);
  IT v3y(ov3y - ov2y);
  IT v3z(ov3z - ov2z);
  IT v2x(ov2x - ov1x);
  IT v2y(ov2y - ov1y);
  IT v2z(ov2z - ov1z);
  IT w3x(ow3x - ow2x);
  IT w3y(ow3y - ow2y);
  IT w3z(ow3z - ow2z);
  IT w2x(ow2x - ow1x);
  IT w2y(ow2y - ow1y);
  IT w2z(ow2z - ow1z);
  IT u3x(ou3x - ou2x);
  IT u3y(ou3y - ou2y);
  IT u3z(ou3z - ou2z);
  IT u2x(ou2x - ou1x);
  IT u2y(ou2y - ou1y);
  IT u2z(ou2z - ou1z);
  IT nvx1(v2y * v3z);
  IT nvx2(v2z * v3y);
  IT nvx(nvx1 - nvx2);
  IT nvy1(v3x * v2z);
  IT nvy2(v3z * v2x);
  IT nvy(nvy1 - nvy2);
  IT nvz1(v2x * v3y);
  IT nvz2(v2y * v3x);
  IT nvz(nvz1 - nvz2);
  IT nwx1(w2y * w3z);
  IT nwx2(w2z * w3y);
  IT nwx(nwx1 - nwx2);
  IT nwy1(w3x * w2z);
  IT nwy2(w3z * w2x);
  IT nwy(nwy1 - nwy2);
  IT nwz1(w2x * w3y);
  IT nwz2(w2y * w3x);
  IT nwz(nwz1 - nwz2);
  IT nux1(u2y * u3z);
  IT nux2(u2z * u3y);
  IT nux(nux1 - nux2);
  IT nuy1(u3x * u2z);
  IT nuy2(u3z * u2x);
  IT nuy(nuy1 - nuy2);
  IT nuz1(u2x * u3y);
  IT nuz2(u2y * u3x);
  IT nuz(nuz1 - nuz2);
  IT nwyuz1(nwy * nuz);
  IT nwyuz2(nwz * nuy);
  IT nwyuz(nwyuz1 - nwyuz2);
  IT nwxuz1(nwx * nuz);
  IT nwxuz2(nwz * nux);
  IT nwxuz(nwxuz1 - nwxuz2);
  IT nwxuy1(nwx * nuy);
  IT nwxuy2(nwy * nux);
  IT nwxuy(nwxuy1 - nwxuy2);
  IT nvyuz1(nvy * nuz);
  IT nvyuz2(nvz * nuy);
  IT nvyuz(nvyuz1 - nvyuz2);
  IT nvxuz1(nvx * nuz);
  IT nvxuz2(nvz * nux);
  IT nvxuz(nvxuz1 - nvxuz2);
  IT nvxuy1(nvx * nuy);
  IT nvxuy2(nvy * nux);
  IT nvxuy(nvxuy1 - nvxuy2);
  IT nvywz1(nvy * nwz);
  IT nvywz2(nvz * nwy);
  IT nvywz(nvywz1 - nvywz2);
  IT nvxwz1(nvx * nwz);
  IT nvxwz2(nvz * nwx);
  IT nvxwz(nvxwz1 - nvxwz2);
  IT nvxwy1(nvx * nwy);
  IT nvxwy2(nvy * nwx);
  IT nvxwy(nvxwy1 - nvxwy2);
  IT p1a(nvx * ov1x);
  IT p1b(nvy * ov1y);
  IT p1c(nvz * ov1z);
  IT p1ab(p1a + p1b);
  IT p1(p1ab + p1c);
  IT p2a(nwx * ow1x);
  IT p2b(nwy * ow1y);
  IT p2c(nwz * ow1z);
  IT p2ab(p2a + p2b);
  IT p2(p2ab + p2c);
  IT p3a(nux * ou1x);
  IT p3b(nuy * ou1y);
  IT p3c(nuz * ou1z);
  IT p3ab(p3a + p3b);
  IT p3(p3ab + p3c);
  IT lxa(p1 * nwyuz);
  IT lxb(p3 * nvywz);
  IT lxc(p2 * nvyuz);
  IT lxab(lxa + lxb);
  lambda_x = lxab - lxc;
  IT lya(p2 * nvxuz);
  IT lyb(p3 * nvxwz);
  IT lyc(p1 * nwxuz);
  IT lybc(lyc + lyb);
  lambda_y = lya - lybc;
  IT lza(p3 * nvxwy);
  IT lzb(p1 * nwxuy);
  IT lzc(p2 * nvxuy);
  IT lzab(lza + lzb);
  lambda_z = lzab - lzc;
  IT da(nvx * nwyuz);
  IT db(nvz * nwxuy);
  IT dc(nvy * nwxuz);
  IT dab(da + db);
  lambda_d = dab - dc;

  return (lambda_d.is_sign_reliable());
}

template <typename ET>
void lambda3d_TPI_exact(ET ov1x, ET ov1y, ET ov1z, ET ov2x, ET ov2y, ET ov2z,
                        ET ov3x, ET ov3y, ET ov3z, ET ow1x, ET ow1y, ET ow1z,
                        ET ow2x, ET ow2y, ET ow2z, ET ow3x, ET ow3y, ET ow3z,
                        ET ou1x, ET ou1y, ET ou1z, ET ou2x, ET ou2y, ET ou2z,
                        ET ou3x, ET ou3y, ET ou3z, ET &lambda_x, ET &lambda_y,
                        ET &lambda_z, ET &lambda_d)
{
  ET v3x    = ov3x - ov2x;
  ET v3y    = ov3y - ov2y;
  ET v3z    = ov3z - ov2z;
  ET v2x    = ov2x - ov1x;
  ET v2y    = ov2y - ov1y;
  ET v2z    = ov2z - ov1z;
  ET w3x    = ow3x - ow2x;
  ET w3y    = ow3y - ow2y;
  ET w3z    = ow3z - ow2z;
  ET w2x    = ow2x - ow1x;
  ET w2y    = ow2y - ow1y;
  ET w2z    = ow2z - ow1z;
  ET u3x    = ou3x - ou2x;
  ET u3y    = ou3y - ou2y;
  ET u3z    = ou3z - ou2z;
  ET u2x    = ou2x - ou1x;
  ET u2y    = ou2y - ou1y;
  ET u2z    = ou2z - ou1z;
  ET nvx1   = v2y * v3z;
  ET nvx2   = v2z * v3y;
  ET nvx    = nvx1 - nvx2;
  ET nvy1   = v3x * v2z;
  ET nvy2   = v3z * v2x;
  ET nvy    = nvy1 - nvy2;
  ET nvz1   = v2x * v3y;
  ET nvz2   = v2y * v3x;
  ET nvz    = nvz1 - nvz2;
  ET nwx1   = w2y * w3z;
  ET nwx2   = w2z * w3y;
  ET nwx    = nwx1 - nwx2;
  ET nwy1   = w3x * w2z;
  ET nwy2   = w3z * w2x;
  ET nwy    = nwy1 - nwy2;
  ET nwz1   = w2x * w3y;
  ET nwz2   = w2y * w3x;
  ET nwz    = nwz1 - nwz2;
  ET nux1   = u2y * u3z;
  ET nux2   = u2z * u3y;
  ET nux    = nux1 - nux2;
  ET nuy1   = u3x * u2z;
  ET nuy2   = u3z * u2x;
  ET nuy    = nuy1 - nuy2;
  ET nuz1   = u2x * u3y;
  ET nuz2   = u2y * u3x;
  ET nuz    = nuz1 - nuz2;
  ET nwyuz1 = nwy * nuz;
  ET nwyuz2 = nwz * nuy;
  ET nwyuz  = nwyuz1 - nwyuz2;
  ET nwxuz1 = nwx * nuz;
  ET nwxuz2 = nwz * nux;
  ET nwxuz  = nwxuz1 - nwxuz2;
  ET nwxuy1 = nwx * nuy;
  ET nwxuy2 = nwy * nux;
  ET nwxuy  = nwxuy1 - nwxuy2;
  ET nvyuz1 = nvy * nuz;
  ET nvyuz2 = nvz * nuy;
  ET nvyuz  = nvyuz1 - nvyuz2;
  ET nvxuz1 = nvx * nuz;
  ET nvxuz2 = nvz * nux;
  ET nvxuz  = nvxuz1 - nvxuz2;
  ET nvxuy1 = nvx * nuy;
  ET nvxuy2 = nvy * nux;
  ET nvxuy  = nvxuy1 - nvxuy2;
  ET nvywz1 = nvy * nwz;
  ET nvywz2 = nvz * nwy;
  ET nvywz  = nvywz1 - nvywz2;
  ET nvxwz1 = nvx * nwz;
  ET nvxwz2 = nvz * nwx;
  ET nvxwz  = nvxwz1 - nvxwz2;
  ET nvxwy1 = nvx * nwy;
  ET nvxwy2 = nvy * nwx;
  ET nvxwy  = nvxwy1 - nvxwy2;
  ET p1a    = nvx * ov1x;
  ET p1b    = nvy * ov1y;
  ET p1c    = nvz * ov1z;
  ET p1ab   = p1a + p1b;
  ET p1     = p1ab + p1c;
  ET p2a    = nwx * ow1x;
  ET p2b    = nwy * ow1y;
  ET p2c    = nwz * ow1z;
  ET p2ab   = p2a + p2b;
  ET p2     = p2ab + p2c;
  ET p3a    = nux * ou1x;
  ET p3b    = nuy * ou1y;
  ET p3c    = nuz * ou1z;
  ET p3ab   = p3a + p3b;
  ET p3     = p3ab + p3c;
  ET lxa    = p1 * nwyuz;
  ET lxb    = p3 * nvywz;
  ET lxc    = p2 * nvyuz;
  ET lxab   = lxa + lxb;
  lambda_x  = lxab - lxc;
  ET lya    = p2 * nvxuz;
  ET lyb    = p3 * nvxwz;
  ET lyc    = p1 * nwxuz;
  ET lybc   = lyc + lyb;
  lambda_y  = lya - lybc;
  ET lza    = p3 * nvxwy;
  ET lzb    = p1 * nwxuy;
  ET lzc    = p2 * nvxuy;
  ET lzab   = lza + lzb;
  lambda_z  = lzab - lzc;
  ET da     = nvx * nwyuz;
  ET db     = nvz * nwxuy;
  ET dc     = nvy * nwxuz;
  ET dab    = da + db;
  lambda_d  = dab - dc;
}

inline void lambda2d_SSI_expansion(double ea1x, double ea1y, double ea2x,
                                   double ea2y, double eb1x, double eb1y,
                                   double eb2x, double eb2y, double **lambda_x,
                                   int &lambda_x_len, double **lambda_y,
                                   int &lambda_y_len, double **lambda_det,
                                   int &lambda_det_len)
{
  expansionObject o;
  double          t1a[2];
  o.Two_Prod(ea1x, ea2y, t1a);
  double t1b[2];
  o.Two_Prod(ea2x, ea1y, t1b);
  double t1[4];
  o.Two_Two_Diff(t1a, t1b, t1);
  double tx2[2];
  o.Two_Diff(eb1x, eb2x, tx2);
  double t3a[2];
  o.Two_Prod(eb1x, eb2y, t3a);
  double t3b[2];
  o.Two_Prod(eb2x, eb1y, t3b);
  double t3[4];
  o.Two_Two_Diff(t3a, t3b, t3);
  double tx4[2];
  o.Two_Diff(ea1x, ea2x, tx4);
  double ty2[2];
  o.Two_Diff(eb1y, eb2y, ty2);
  double ty4[2];
  o.Two_Diff(ea1y, ea2y, ty4);
  double lxa[16];
  int    lxa_len = o.Gen_Product(4, t1, 2, tx2, lxa);
  double lxb[16];
  int    lxb_len = o.Gen_Product(4, t3, 2, tx4, lxb);
  lambda_x_len = o.Gen_Diff_With_PreAlloc(lxa_len, lxa, lxb_len, lxb, lambda_x,
                                          lambda_x_len);
  double lya[16];
  int    lya_len = o.Gen_Product(4, t1, 2, ty2, lya);
  double lyb[16];
  int    lyb_len = o.Gen_Product(4, t3, 2, ty4, lyb);
  lambda_y_len = o.Gen_Diff_With_PreAlloc(lya_len, lya, lyb_len, lyb, lambda_y,
                                          lambda_y_len);
  double deta[8];
  int    deta_len = o.Gen_Product(2, tx4, 2, ty2, deta);
  double detb[8];
  int    detb_len = o.Gen_Product(2, tx2, 2, ty4, detb);
  lambda_det_len  = o.Gen_Diff_With_PreAlloc(deta_len, deta, detb_len, detb,
                                             lambda_det, lambda_det_len);
}

inline void lambda3d_SSI_expansion(double xa, double ya, double za, double xb,
                                   double yb, double zb, double xp, double yp,
                                   double xq, double yq, double **lambda_x,
                                   int &lambda_x_len, double **lambda_y,
                                   int &lambda_y_len, double **lambda_z,
                                   int &lambda_z_len, double **lambda_d,
                                   int &lambda_d_len)
{
  expansionObject o;
  double          xba[2];
  o.Two_Diff(xb, xa, xba);
  double yba[2];
  o.Two_Diff(yb, ya, yba);
  double zba[2];
  o.Two_Diff(zb, za, zba);
  double xap[2];
  o.Two_Diff(xa, xp, xap);
  double yap[2];
  o.Two_Diff(ya, yp, yap);
  double yqp[2];
  o.Two_Diff(yq, yp, yqp);
  double xqp[2];
  o.Two_Diff(xq, xp, xqp);
  double c1[8];
  int    c1_len = o.Gen_Product(2, xap, 2, yqp, c1);
  double c2[8];
  int    c2_len = o.Gen_Product(2, xqp, 2, yap, c2);
  double c3[8];
  int    c3_len = o.Gen_Product(2, xba, 2, yqp, c3);
  double c4[8];
  int    c4_len = o.Gen_Product(2, xqp, 2, yba, c4);
  double c12[16];
  int    c12_len = o.Gen_Diff(c1_len, c1, c2_len, c2, c12);
  lambda_d_len =
    o.Gen_Diff_With_PreAlloc(c4_len, c4, c3_len, c3, lambda_d, lambda_d_len);
  double xf[64];
  int    xf_len = o.Gen_Product(2, xba, c12_len, c12, xf);
  double xs[32];
  int    xs_len = o.Gen_Scale(lambda_d_len, *lambda_d, xa, xs);
  lambda_x_len =
    o.Gen_Sum_With_PreAlloc(xf_len, xf, xs_len, xs, lambda_x, lambda_x_len);
  double yf[64];
  int    yf_len = o.Gen_Product(2, yba, c12_len, c12, yf);
  double ys[32];
  int    ys_len = o.Gen_Scale(lambda_d_len, *lambda_d, ya, ys);
  lambda_y_len =
    o.Gen_Sum_With_PreAlloc(yf_len, yf, ys_len, ys, lambda_y, lambda_y_len);
  double zf[64];
  int    zf_len = o.Gen_Product(2, zba, c12_len, c12, zf);
  double zs[32];
  int    zs_len = o.Gen_Scale(lambda_d_len, *lambda_d, za, zs);
  lambda_z_len =
    o.Gen_Sum_With_PreAlloc(zf_len, zf, zs_len, zs, lambda_z, lambda_z_len);
}

inline void lambda3d_LPI_expansion(double px, double py, double pz, double qx,
                                   double qy, double qz, double rx, double ry,
                                   double rz, double sx, double sy, double sz,
                                   double tx, double ty, double tz,
                                   double **lambda_d, int &lambda_d_len,
                                   double **lambda_x, int &lambda_x_len,
                                   double **lambda_y, int &lambda_y_len,
                                   double **lambda_z, int &lambda_z_len)
{
  expansionObject o;
  double          a11[2];
  o.Two_Diff(px, qx, a11);
  double a12[2];
  o.Two_Diff(py, qy, a12);
  double a13[2];
  o.Two_Diff(pz, qz, a13);
  double a21[2];
  o.Two_Diff(sx, rx, a21);
  double a22[2];
  o.Two_Diff(sy, ry, a22);
  double a23[2];
  o.Two_Diff(sz, rz, a23);
  double a31[2];
  o.Two_Diff(tx, rx, a31);
  double a32[2];
  o.Two_Diff(ty, ry, a32);
  double a33[2];
  o.Two_Diff(tz, rz, a33);
  double tv1[8];
  int    tv1_len = o.Gen_Product(2, a22, 2, a33, tv1);
  double tv2[8];
  int    tv2_len = o.Gen_Product(2, a23, 2, a32, tv2);
  double a2233[16];
  int    a2233_len = o.Gen_Diff(tv1_len, tv1, tv2_len, tv2, a2233);
  double tv3[8];
  int    tv3_len = o.Gen_Product(2, a21, 2, a33, tv3);
  double tv4[8];
  int    tv4_len = o.Gen_Product(2, a23, 2, a31, tv4);
  double a2133[16];
  int    a2133_len = o.Gen_Diff(tv3_len, tv3, tv4_len, tv4, a2133);
  double tv5[8];
  int    tv5_len = o.Gen_Product(2, a21, 2, a32, tv5);
  double tv6[8];
  int    tv6_len = o.Gen_Product(2, a22, 2, a31, tv6);
  double a2132[16];
  int    a2132_len = o.Gen_Diff(tv5_len, tv5, tv6_len, tv6, a2132);
  double tv7[64];
  int    tv7_len = o.Gen_Product(2, a11, a2233_len, a2233, tv7);
  double tv8[64];
  int    tv8_len = o.Gen_Product(2, a12, a2133_len, a2133, tv8);
  double tv9[64];
  int    tv9_len = o.Gen_Product(2, a13, a2132_len, a2132, tv9);
  double tt1[128];
  int    tt1_len = o.Gen_Diff(tv7_len, tv7, tv8_len, tv8, tt1);
  lambda_d_len =
    o.Gen_Sum_With_PreAlloc(tt1_len, tt1, tv9_len, tv9, lambda_d, lambda_d_len);
  double px_rx[2];
  o.Two_Diff(px, rx, px_rx);
  double py_ry[2];
  o.Two_Diff(py, ry, py_ry);
  double pz_rz[2];
  o.Two_Diff(pz, rz, pz_rz);
  double tt2[64];
  int    tt2_len = o.Gen_Product(2, py_ry, a2133_len, a2133, tt2);
  double tt3[64];
  int    tt3_len = o.Gen_Product(2, px_rx, a2233_len, a2233, tt3);
  double tt4[64];
  int    tt4_len = o.Gen_Product(2, pz_rz, a2132_len, a2132, tt4);
  double tt5[128];
  int    tt5_len = o.Gen_Sum(tt3_len, tt3, tt4_len, tt4, tt5);
  double n_p[128], *n = n_p;
  int    n_len = o.Gen_Diff_With_PreAlloc(tt5_len, tt5, tt2_len, tt2, &n, 128);
  double ax_p[128], *ax = ax_p;
  int    ax_len = o.Gen_Product_With_PreAlloc(2, a11, n_len, n, &ax, 128);
  double ay_p[128], *ay = ay_p;
  int    ay_len = o.Gen_Product_With_PreAlloc(2, a12, n_len, n, &ay, 128);
  double az_p[128], *az = az_p;
  int    az_len = o.Gen_Product_With_PreAlloc(2, a13, n_len, n, &az, 128);
  double dpx_p[128], *dpx = dpx_p;
  int    dpx_len =
    o.Gen_Scale_With_PreAlloc(lambda_d_len, *lambda_d, px, &dpx, 128);
  double dpy_p[128], *dpy = dpy_p;
  int    dpy_len =
    o.Gen_Scale_With_PreAlloc(lambda_d_len, *lambda_d, py, &dpy, 128);
  double dpz_p[128], *dpz = dpz_p;
  int    dpz_len =
    o.Gen_Scale_With_PreAlloc(lambda_d_len, *lambda_d, pz, &dpz, 128);
  lambda_x_len =
    o.Gen_Diff_With_PreAlloc(dpx_len, dpx, ax_len, ax, lambda_x, lambda_x_len);
  lambda_y_len =
    o.Gen_Diff_With_PreAlloc(dpy_len, dpy, ay_len, ay, lambda_y, lambda_y_len);
  lambda_z_len =
    o.Gen_Diff_With_PreAlloc(dpz_len, dpz, az_len, az, lambda_z, lambda_z_len);

  if (dpz_p != dpz)
    FreeDoubles(dpz);
  if (dpy_p != dpy)
    FreeDoubles(dpy);
  if (dpx_p != dpx)
    FreeDoubles(dpx);
  if (az_p != az)
    FreeDoubles(az);
  if (ay_p != ay)
    FreeDoubles(ay);
  if (ax_p != ax)
    FreeDoubles(ax);
  if (n_p != n)
    FreeDoubles(n);
}

inline void lambda3d_TPI_expansion(
  double ov1x, double ov1y, double ov1z, double ov2x, double ov2y, double ov2z,
  double ov3x, double ov3y, double ov3z, double ow1x, double ow1y, double ow1z,
  double ow2x, double ow2y, double ow2z, double ow3x, double ow3y, double ow3z,
  double ou1x, double ou1y, double ou1z, double ou2x, double ou2y, double ou2z,
  double ou3x, double ou3y, double ou3z, double **lambda_x, int &lambda_x_len,
  double **lambda_y, int &lambda_y_len, double **lambda_z, int &lambda_z_len,
  double **lambda_d, int &lambda_d_len)
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
  double w3x[2];
  o.Two_Diff(ow3x, ow2x, w3x);
  double w3y[2];
  o.Two_Diff(ow3y, ow2y, w3y);
  double w3z[2];
  o.Two_Diff(ow3z, ow2z, w3z);
  double w2x[2];
  o.Two_Diff(ow2x, ow1x, w2x);
  double w2y[2];
  o.Two_Diff(ow2y, ow1y, w2y);
  double w2z[2];
  o.Two_Diff(ow2z, ow1z, w2z);
  double u3x[2];
  o.Two_Diff(ou3x, ou2x, u3x);
  double u3y[2];
  o.Two_Diff(ou3y, ou2y, u3y);
  double u3z[2];
  o.Two_Diff(ou3z, ou2z, u3z);
  double u2x[2];
  o.Two_Diff(ou2x, ou1x, u2x);
  double u2y[2];
  o.Two_Diff(ou2y, ou1y, u2y);
  double u2z[2];
  o.Two_Diff(ou2z, ou1z, u2z);
  double nvx1[8];
  int    nvx1_len = o.Gen_Product(2, v2y, 2, v3z, nvx1);
  double nvx2[8];
  int    nvx2_len = o.Gen_Product(2, v2z, 2, v3y, nvx2);
  double nvx[16];
  int    nvx_len = o.Gen_Diff(nvx1_len, nvx1, nvx2_len, nvx2, nvx);
  double nvy1[8];
  int    nvy1_len = o.Gen_Product(2, v3x, 2, v2z, nvy1);
  double nvy2[8];
  int    nvy2_len = o.Gen_Product(2, v3z, 2, v2x, nvy2);
  double nvy[16];
  int    nvy_len = o.Gen_Diff(nvy1_len, nvy1, nvy2_len, nvy2, nvy);
  double nvz1[8];
  int    nvz1_len = o.Gen_Product(2, v2x, 2, v3y, nvz1);
  double nvz2[8];
  int    nvz2_len = o.Gen_Product(2, v2y, 2, v3x, nvz2);
  double nvz[16];
  int    nvz_len = o.Gen_Diff(nvz1_len, nvz1, nvz2_len, nvz2, nvz);
  double nwx1[8];
  int    nwx1_len = o.Gen_Product(2, w2y, 2, w3z, nwx1);
  double nwx2[8];
  int    nwx2_len = o.Gen_Product(2, w2z, 2, w3y, nwx2);
  double nwx[16];
  int    nwx_len = o.Gen_Diff(nwx1_len, nwx1, nwx2_len, nwx2, nwx);
  double nwy1[8];
  int    nwy1_len = o.Gen_Product(2, w3x, 2, w2z, nwy1);
  double nwy2[8];
  int    nwy2_len = o.Gen_Product(2, w3z, 2, w2x, nwy2);
  double nwy[16];
  int    nwy_len = o.Gen_Diff(nwy1_len, nwy1, nwy2_len, nwy2, nwy);
  double nwz1[8];
  int    nwz1_len = o.Gen_Product(2, w2x, 2, w3y, nwz1);
  double nwz2[8];
  int    nwz2_len = o.Gen_Product(2, w2y, 2, w3x, nwz2);
  double nwz[16];
  int    nwz_len = o.Gen_Diff(nwz1_len, nwz1, nwz2_len, nwz2, nwz);
  double nux1[8];
  int    nux1_len = o.Gen_Product(2, u2y, 2, u3z, nux1);
  double nux2[8];
  int    nux2_len = o.Gen_Product(2, u2z, 2, u3y, nux2);
  double nux[16];
  int    nux_len = o.Gen_Diff(nux1_len, nux1, nux2_len, nux2, nux);
  double nuy1[8];
  int    nuy1_len = o.Gen_Product(2, u3x, 2, u2z, nuy1);
  double nuy2[8];
  int    nuy2_len = o.Gen_Product(2, u3z, 2, u2x, nuy2);
  double nuy[16];
  int    nuy_len = o.Gen_Diff(nuy1_len, nuy1, nuy2_len, nuy2, nuy);
  double nuz1[8];
  int    nuz1_len = o.Gen_Product(2, u2x, 2, u3y, nuz1);
  double nuz2[8];
  int    nuz2_len = o.Gen_Product(2, u2y, 2, u3x, nuz2);
  double nuz[16];
  int    nuz_len = o.Gen_Diff(nuz1_len, nuz1, nuz2_len, nuz2, nuz);
  double nwyuz1_p[16], *nwyuz1 = nwyuz1_p;
  int    nwyuz1_len =
    o.Gen_Product_With_PreAlloc(nwy_len, nwy, nuz_len, nuz, &nwyuz1, 16);
  double nwyuz2_p[16], *nwyuz2 = nwyuz2_p;
  int    nwyuz2_len =
    o.Gen_Product_With_PreAlloc(nwz_len, nwz, nuy_len, nuy, &nwyuz2, 16);
  double nwyuz_p[16], *nwyuz = nwyuz_p;
  int    nwyuz_len = o.Gen_Diff_With_PreAlloc(nwyuz1_len, nwyuz1, nwyuz2_len,
                                              nwyuz2, &nwyuz, 16);
  double nwxuz1_p[16], *nwxuz1 = nwxuz1_p;
  int    nwxuz1_len =
    o.Gen_Product_With_PreAlloc(nwx_len, nwx, nuz_len, nuz, &nwxuz1, 16);
  double nwxuz2_p[16], *nwxuz2 = nwxuz2_p;
  int    nwxuz2_len =
    o.Gen_Product_With_PreAlloc(nwz_len, nwz, nux_len, nux, &nwxuz2, 16);
  double nwxuz_p[16], *nwxuz = nwxuz_p;
  int    nwxuz_len = o.Gen_Diff_With_PreAlloc(nwxuz1_len, nwxuz1, nwxuz2_len,
                                              nwxuz2, &nwxuz, 16);
  double nwxuy1_p[16], *nwxuy1 = nwxuy1_p;
  int    nwxuy1_len =
    o.Gen_Product_With_PreAlloc(nwx_len, nwx, nuy_len, nuy, &nwxuy1, 16);
  double nwxuy2_p[16], *nwxuy2 = nwxuy2_p;
  int    nwxuy2_len =
    o.Gen_Product_With_PreAlloc(nwy_len, nwy, nux_len, nux, &nwxuy2, 16);
  double nwxuy_p[16], *nwxuy = nwxuy_p;
  int    nwxuy_len = o.Gen_Diff_With_PreAlloc(nwxuy1_len, nwxuy1, nwxuy2_len,
                                              nwxuy2, &nwxuy, 16);
  double nvyuz1_p[16], *nvyuz1 = nvyuz1_p;
  int    nvyuz1_len =
    o.Gen_Product_With_PreAlloc(nvy_len, nvy, nuz_len, nuz, &nvyuz1, 16);
  double nvyuz2_p[16], *nvyuz2 = nvyuz2_p;
  int    nvyuz2_len =
    o.Gen_Product_With_PreAlloc(nvz_len, nvz, nuy_len, nuy, &nvyuz2, 16);
  double nvyuz_p[16], *nvyuz = nvyuz_p;
  int    nvyuz_len = o.Gen_Diff_With_PreAlloc(nvyuz1_len, nvyuz1, nvyuz2_len,
                                              nvyuz2, &nvyuz, 16);
  double nvxuz1_p[16], *nvxuz1 = nvxuz1_p;
  int    nvxuz1_len =
    o.Gen_Product_With_PreAlloc(nvx_len, nvx, nuz_len, nuz, &nvxuz1, 16);
  double nvxuz2_p[16], *nvxuz2 = nvxuz2_p;
  int    nvxuz2_len =
    o.Gen_Product_With_PreAlloc(nvz_len, nvz, nux_len, nux, &nvxuz2, 16);
  double nvxuz_p[16], *nvxuz = nvxuz_p;
  int    nvxuz_len = o.Gen_Diff_With_PreAlloc(nvxuz1_len, nvxuz1, nvxuz2_len,
                                              nvxuz2, &nvxuz, 16);
  double nvxuy1_p[16], *nvxuy1 = nvxuy1_p;
  int    nvxuy1_len =
    o.Gen_Product_With_PreAlloc(nvx_len, nvx, nuy_len, nuy, &nvxuy1, 16);
  double nvxuy2_p[16], *nvxuy2 = nvxuy2_p;
  int    nvxuy2_len =
    o.Gen_Product_With_PreAlloc(nvy_len, nvy, nux_len, nux, &nvxuy2, 16);
  double nvxuy_p[16], *nvxuy = nvxuy_p;
  int    nvxuy_len = o.Gen_Diff_With_PreAlloc(nvxuy1_len, nvxuy1, nvxuy2_len,
                                              nvxuy2, &nvxuy, 16);
  double nvywz1_p[16], *nvywz1 = nvywz1_p;
  int    nvywz1_len =
    o.Gen_Product_With_PreAlloc(nvy_len, nvy, nwz_len, nwz, &nvywz1, 16);
  double nvywz2_p[16], *nvywz2 = nvywz2_p;
  int    nvywz2_len =
    o.Gen_Product_With_PreAlloc(nvz_len, nvz, nwy_len, nwy, &nvywz2, 16);
  double nvywz_p[16], *nvywz = nvywz_p;
  int    nvywz_len = o.Gen_Diff_With_PreAlloc(nvywz1_len, nvywz1, nvywz2_len,
                                              nvywz2, &nvywz, 16);
  double nvxwz1_p[16], *nvxwz1 = nvxwz1_p;
  int    nvxwz1_len =
    o.Gen_Product_With_PreAlloc(nvx_len, nvx, nwz_len, nwz, &nvxwz1, 16);
  double nvxwz2_p[16], *nvxwz2 = nvxwz2_p;
  int    nvxwz2_len =
    o.Gen_Product_With_PreAlloc(nvz_len, nvz, nwx_len, nwx, &nvxwz2, 16);
  double nvxwz_p[16], *nvxwz = nvxwz_p;
  int    nvxwz_len = o.Gen_Diff_With_PreAlloc(nvxwz1_len, nvxwz1, nvxwz2_len,
                                              nvxwz2, &nvxwz, 16);
  double nvxwy1_p[16], *nvxwy1 = nvxwy1_p;
  int    nvxwy1_len =
    o.Gen_Product_With_PreAlloc(nvx_len, nvx, nwy_len, nwy, &nvxwy1, 16);
  double nvxwy2_p[16], *nvxwy2 = nvxwy2_p;
  int    nvxwy2_len =
    o.Gen_Product_With_PreAlloc(nvy_len, nvy, nwx_len, nwx, &nvxwy2, 16);
  double nvxwy_p[16], *nvxwy = nvxwy_p;
  int    nvxwy_len = o.Gen_Diff_With_PreAlloc(nvxwy1_len, nvxwy1, nvxwy2_len,
                                              nvxwy2, &nvxwy, 16);
  double p1a_p[16], *p1a = p1a_p;
  int    p1a_len = o.Gen_Scale_With_PreAlloc(nvx_len, nvx, ov1x, &p1a, 16);
  double p1b_p[16], *p1b = p1b_p;
  int    p1b_len = o.Gen_Scale_With_PreAlloc(nvy_len, nvy, ov1y, &p1b, 16);
  double p1c_p[16], *p1c = p1c_p;
  int    p1c_len = o.Gen_Scale_With_PreAlloc(nvz_len, nvz, ov1z, &p1c, 16);
  double p1ab_p[16], *p1ab = p1ab_p;
  int p1ab_len = o.Gen_Sum_With_PreAlloc(p1a_len, p1a, p1b_len, p1b, &p1ab, 16);
  double p1_p[16], *p1 = p1_p;
  int p1_len = o.Gen_Sum_With_PreAlloc(p1ab_len, p1ab, p1c_len, p1c, &p1, 16);
  double p2a_p[16], *p2a = p2a_p;
  int    p2a_len = o.Gen_Scale_With_PreAlloc(nwx_len, nwx, ow1x, &p2a, 16);
  double p2b_p[16], *p2b = p2b_p;
  int    p2b_len = o.Gen_Scale_With_PreAlloc(nwy_len, nwy, ow1y, &p2b, 16);
  double p2c_p[16], *p2c = p2c_p;
  int    p2c_len = o.Gen_Scale_With_PreAlloc(nwz_len, nwz, ow1z, &p2c, 16);
  double p2ab_p[16], *p2ab = p2ab_p;
  int p2ab_len = o.Gen_Sum_With_PreAlloc(p2a_len, p2a, p2b_len, p2b, &p2ab, 16);
  double p2_p[16], *p2 = p2_p;
  int p2_len = o.Gen_Sum_With_PreAlloc(p2ab_len, p2ab, p2c_len, p2c, &p2, 16);
  double p3a_p[16], *p3a = p3a_p;
  int    p3a_len = o.Gen_Scale_With_PreAlloc(nux_len, nux, ou1x, &p3a, 16);
  double p3b_p[16], *p3b = p3b_p;
  int    p3b_len = o.Gen_Scale_With_PreAlloc(nuy_len, nuy, ou1y, &p3b, 16);
  double p3c_p[16], *p3c = p3c_p;
  int    p3c_len = o.Gen_Scale_With_PreAlloc(nuz_len, nuz, ou1z, &p3c, 16);
  double p3ab_p[16], *p3ab = p3ab_p;
  int p3ab_len = o.Gen_Sum_With_PreAlloc(p3a_len, p3a, p3b_len, p3b, &p3ab, 16);
  double p3_p[16], *p3 = p3_p;
  int p3_len = o.Gen_Sum_With_PreAlloc(p3ab_len, p3ab, p3c_len, p3c, &p3, 16);
  double lxa_p[16], *lxa = lxa_p;
  int    lxa_len =
    o.Gen_Product_With_PreAlloc(p1_len, p1, nwyuz_len, nwyuz, &lxa, 16);
  double lxb_p[16], *lxb = lxb_p;
  int    lxb_len =
    o.Gen_Product_With_PreAlloc(p3_len, p3, nvywz_len, nvywz, &lxb, 16);
  double lxc_p[16], *lxc = lxc_p;
  int    lxc_len =
    o.Gen_Product_With_PreAlloc(p2_len, p2, nvyuz_len, nvyuz, &lxc, 16);
  double lxab_p[16], *lxab = lxab_p;
  int lxab_len = o.Gen_Sum_With_PreAlloc(lxa_len, lxa, lxb_len, lxb, &lxab, 16);
  lambda_x_len = o.Gen_Diff_With_PreAlloc(lxab_len, lxab, lxc_len, lxc,
                                          lambda_x, lambda_x_len);
  double lya_p[16], *lya = lya_p;
  int    lya_len =
    o.Gen_Product_With_PreAlloc(p2_len, p2, nvxuz_len, nvxuz, &lya, 16);
  double lyb_p[16], *lyb = lyb_p;
  int    lyb_len =
    o.Gen_Product_With_PreAlloc(p3_len, p3, nvxwz_len, nvxwz, &lyb, 16);
  double lyc_p[16], *lyc = lyc_p;
  int    lyc_len =
    o.Gen_Product_With_PreAlloc(p1_len, p1, nwxuz_len, nwxuz, &lyc, 16);
  double lybc_p[16], *lybc = lybc_p;
  int lybc_len = o.Gen_Sum_With_PreAlloc(lyc_len, lyc, lyb_len, lyb, &lybc, 16);
  lambda_y_len = o.Gen_Diff_With_PreAlloc(lya_len, lya, lybc_len, lybc,
                                          lambda_y, lambda_y_len);
  double lza_p[16], *lza = lza_p;
  int    lza_len =
    o.Gen_Product_With_PreAlloc(p3_len, p3, nvxwy_len, nvxwy, &lza, 16);
  double lzb_p[16], *lzb = lzb_p;
  int    lzb_len =
    o.Gen_Product_With_PreAlloc(p1_len, p1, nwxuy_len, nwxuy, &lzb, 16);
  double lzc_p[16], *lzc = lzc_p;
  int    lzc_len =
    o.Gen_Product_With_PreAlloc(p2_len, p2, nvxuy_len, nvxuy, &lzc, 16);
  double lzab_p[16], *lzab = lzab_p;
  int lzab_len = o.Gen_Sum_With_PreAlloc(lza_len, lza, lzb_len, lzb, &lzab, 16);
  lambda_z_len = o.Gen_Diff_With_PreAlloc(lzab_len, lzab, lzc_len, lzc,
                                          lambda_z, lambda_z_len);
  double da_p[16], *da = da_p;
  int    da_len =
    o.Gen_Product_With_PreAlloc(nvx_len, nvx, nwyuz_len, nwyuz, &da, 16);
  double db_p[16], *db = db_p;
  int    db_len =
    o.Gen_Product_With_PreAlloc(nvz_len, nvz, nwxuy_len, nwxuy, &db, 16);
  double dc_p[16], *dc = dc_p;
  int    dc_len =
    o.Gen_Product_With_PreAlloc(nvy_len, nvy, nwxuz_len, nwxuz, &dc, 16);
  double dab_p[16], *dab = dab_p;
  int    dab_len = o.Gen_Sum_With_PreAlloc(da_len, da, db_len, db, &dab, 16);
  lambda_d_len =
    o.Gen_Diff_With_PreAlloc(dab_len, dab, dc_len, dc, lambda_d, lambda_d_len);

  if (dab_p != dab)
    FreeDoubles(dab);
  if (dc_p != dc)
    FreeDoubles(dc);
  if (db_p != db)
    FreeDoubles(db);
  if (da_p != da)
    FreeDoubles(da);
  if (lzab_p != lzab)
    FreeDoubles(lzab);
  if (lzc_p != lzc)
    FreeDoubles(lzc);
  if (lzb_p != lzb)
    FreeDoubles(lzb);
  if (lza_p != lza)
    FreeDoubles(lza);
  if (lybc_p != lybc)
    FreeDoubles(lybc);
  if (lyc_p != lyc)
    FreeDoubles(lyc);
  if (lyb_p != lyb)
    FreeDoubles(lyb);
  if (lya_p != lya)
    FreeDoubles(lya);
  if (lxab_p != lxab)
    FreeDoubles(lxab);
  if (lxc_p != lxc)
    FreeDoubles(lxc);
  if (lxb_p != lxb)
    FreeDoubles(lxb);
  if (lxa_p != lxa)
    FreeDoubles(lxa);
  if (p3_p != p3)
    FreeDoubles(p3);
  if (p3ab_p != p3ab)
    FreeDoubles(p3ab);
  if (p3c_p != p3c)
    FreeDoubles(p3c);
  if (p3b_p != p3b)
    FreeDoubles(p3b);
  if (p3a_p != p3a)
    FreeDoubles(p3a);
  if (p2_p != p2)
    FreeDoubles(p2);
  if (p2ab_p != p2ab)
    FreeDoubles(p2ab);
  if (p2c_p != p2c)
    FreeDoubles(p2c);
  if (p2b_p != p2b)
    FreeDoubles(p2b);
  if (p2a_p != p2a)
    FreeDoubles(p2a);
  if (p1_p != p1)
    FreeDoubles(p1);
  if (p1ab_p != p1ab)
    FreeDoubles(p1ab);
  if (p1c_p != p1c)
    FreeDoubles(p1c);
  if (p1b_p != p1b)
    FreeDoubles(p1b);
  if (p1a_p != p1a)
    FreeDoubles(p1a);
  if (nvxwy_p != nvxwy)
    FreeDoubles(nvxwy);
  if (nvxwy2_p != nvxwy2)
    FreeDoubles(nvxwy2);
  if (nvxwy1_p != nvxwy1)
    FreeDoubles(nvxwy1);
  if (nvxwz_p != nvxwz)
    FreeDoubles(nvxwz);
  if (nvxwz2_p != nvxwz2)
    FreeDoubles(nvxwz2);
  if (nvxwz1_p != nvxwz1)
    FreeDoubles(nvxwz1);
  if (nvywz_p != nvywz)
    FreeDoubles(nvywz);
  if (nvywz2_p != nvywz2)
    FreeDoubles(nvywz2);
  if (nvywz1_p != nvywz1)
    FreeDoubles(nvywz1);
  if (nvxuy_p != nvxuy)
    FreeDoubles(nvxuy);
  if (nvxuy2_p != nvxuy2)
    FreeDoubles(nvxuy2);
  if (nvxuy1_p != nvxuy1)
    FreeDoubles(nvxuy1);
  if (nvxuz_p != nvxuz)
    FreeDoubles(nvxuz);
  if (nvxuz2_p != nvxuz2)
    FreeDoubles(nvxuz2);
  if (nvxuz1_p != nvxuz1)
    FreeDoubles(nvxuz1);
  if (nvyuz_p != nvyuz)
    FreeDoubles(nvyuz);
  if (nvyuz2_p != nvyuz2)
    FreeDoubles(nvyuz2);
  if (nvyuz1_p != nvyuz1)
    FreeDoubles(nvyuz1);
  if (nwxuy_p != nwxuy)
    FreeDoubles(nwxuy);
  if (nwxuy2_p != nwxuy2)
    FreeDoubles(nwxuy2);
  if (nwxuy1_p != nwxuy1)
    FreeDoubles(nwxuy1);
  if (nwxuz_p != nwxuz)
    FreeDoubles(nwxuz);
  if (nwxuz2_p != nwxuz2)
    FreeDoubles(nwxuz2);
  if (nwxuz1_p != nwxuz1)
    FreeDoubles(nwxuz1);
  if (nwyuz_p != nwyuz)
    FreeDoubles(nwyuz);
  if (nwyuz2_p != nwyuz2)
    FreeDoubles(nwyuz2);
  if (nwyuz1_p != nwyuz1)
    FreeDoubles(nwyuz1);
}

} // namespace OMC