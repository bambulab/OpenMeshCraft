#pragma once

#include "OpenMeshCraft/Utils/Macros.h"

namespace OMC {

template <typename IT>
bool lambda2d_SSI_interval(IT ea1x, IT ea1y, IT ea2x, IT ea2y, IT eb1x, IT eb1y,
                           IT eb2x, IT eb2y, IT &lambda_x, IT &lambda_y,
                           IT &lambda_det);

template <typename ET>
void lambda2d_SSI_exact(ET ea1x, ET ea1y, ET ea2x, ET ea2y, ET eb1x, ET eb1y,
                        ET eb2x, ET eb2y, ET &lambda_x, ET &lambda_y,
                        ET &lambda_det);

inline void lambda2d_SSI_expansion(double ea1x, double ea1y, double ea2x,
                                   double ea2y, double eb1x, double eb1y,
                                   double eb2x, double eb2y, double **lambda_x,
                                   int &lambda_x_len, double **lambda_y,
                                   int &lambda_y_len, double **lambda_det,
                                   int &lambda_det_len);

template <typename IT>
bool lambda3d_SSI_interval(IT xa, IT ya, IT za, IT xb, IT yb, IT zb, IT xp,
                           IT yp, IT xq, IT yq, IT &lambda_x, IT &lambda_y,
                           IT &lambda_z, IT &lambda_d);

template <typename ET>
void lambda3d_SSI_exact(ET xa, ET ya, ET za, ET xb, ET yb, ET zb, ET xp, ET yp,
                        ET xq, ET yq, ET &lambda_x, ET &lambda_y, ET &lambda_z,
                        ET &lambda_d);

inline void lambda3d_SSI_expansion(double xa, double ya, double za, double xb,
                                   double yb, double zb, double xp, double yp,
                                   double xq, double yq, double **lambda_x,
                                   int &lambda_x_len, double **lambda_y,
                                   int &lambda_y_len, double **lambda_z,
                                   int &lambda_z_len, double **lambda_d,
                                   int &lambda_d_len);

template <typename IT>
bool lambda3d_LPI_interval(IT px, IT py, IT pz, IT qx, IT qy, IT qz, IT rx,
                           IT ry, IT rz, IT sx, IT sy, IT sz, IT tx, IT ty,
                           IT tz, IT &lambda_d, IT &lambda_x, IT &lambda_y,
                           IT &lambda_z);

template <typename ET>
void lambda3d_LPI_exact(ET px, ET py, ET pz, ET qx, ET qy, ET qz, ET rx, ET ry,
                        ET rz, ET sx, ET sy, ET sz, ET tx, ET ty, ET tz,
                        ET &lambda_d, ET &lambda_x, ET &lambda_y, ET &lambda_z);

inline void lambda3d_LPI_expansion(double px, double py, double pz, double qx,
                                   double qy, double qz, double rx, double ry,
                                   double rz, double sx, double sy, double sz,
                                   double tx, double ty, double tz,
                                   double **lambda_d, int &lambda_d_len,
                                   double **lambda_x, int &lambda_x_len,
                                   double **lambda_y, int &lambda_y_len,
                                   double **lambda_z, int &lambda_z_len);

template <typename IT>
bool lambda3d_TPI_interval(IT ov1x, IT ov1y, IT ov1z, IT ov2x, IT ov2y, IT ov2z,
                           IT ov3x, IT ov3y, IT ov3z, IT ow1x, IT ow1y, IT ow1z,
                           IT ow2x, IT ow2y, IT ow2z, IT ow3x, IT ow3y, IT ow3z,
                           IT ou1x, IT ou1y, IT ou1z, IT ou2x, IT ou2y, IT ou2z,
                           IT ou3x, IT ou3y, IT ou3z, IT &lambda_x,
                           IT &lambda_y, IT &lambda_z, IT &lambda_d);

template <typename ET>
void lambda3d_TPI_exact(ET ov1x, ET ov1y, ET ov1z, ET ov2x, ET ov2y, ET ov2z,
                        ET ov3x, ET ov3y, ET ov3z, ET ow1x, ET ow1y, ET ow1z,
                        ET ow2x, ET ow2y, ET ow2z, ET ow3x, ET ow3y, ET ow3z,
                        ET ou1x, ET ou1y, ET ou1z, ET ou2x, ET ou2y, ET ou2z,
                        ET ou3x, ET ou3y, ET ou3z, ET &lambda_x, ET &lambda_y,
                        ET &lambda_z, ET &lambda_d);

inline void lambda3d_TPI_expansion(
  double ov1x, double ov1y, double ov1z, double ov2x, double ov2y, double ov2z,
  double ov3x, double ov3y, double ov3z, double ow1x, double ow1y, double ow1z,
  double ow2x, double ow2y, double ow2z, double ow3x, double ow3y, double ow3z,
  double ou1x, double ou1y, double ou1z, double ou2x, double ou2y, double ou2z,
  double ou3x, double ou3y, double ou3z, double **lambda_x, int &lambda_x_len,
  double **lambda_y, int &lambda_y_len, double **lambda_z, int &lambda_z_len,
  double **lambda_d, int &lambda_d_len);

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "ImplicitPointPredicates.inl"
#endif