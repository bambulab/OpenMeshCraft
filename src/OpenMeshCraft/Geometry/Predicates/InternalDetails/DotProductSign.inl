#pragma once

#include "OpenMeshCraft/Geometry/Predicates/IndirectDefinitions.h"

#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"
#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"
#include "OpenMeshCraft/NumberTypes/LazyNumber.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
#define CHECK_FOR_XYZERFLOWS

namespace OMC {

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

inline Sign dotProductSign2D_filtered(double px, double py, double rx,
                                      double ry, double qx, double qy);

template <typename IT>
Sign dotProductSign2D_interval(IT px, IT py, IT rx, IT ry, IT qx, IT qy);

template <typename ET>
Sign dotProductSign2D_exact(ET px, ET py, ET rx, ET ry, ET qx, ET qy);

inline Sign dotProductSign2D_expansion(double px, double py, double rx,
                                       double ry, double qx, double qy);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign2D(double px, double py, double rx, double ry, double qx,
                      double qy);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign2D(const GenericPoint2T<IT, ET> &p,
                      const GenericPoint2T<IT, ET> &r,
                      const GenericPoint2T<IT, ET> &q);

/*===================================================================*/

inline Sign dotProductSign2D4P_filtered(double px, double py, double rx,
                                        double ry, double qx, double qy,
                                        double sx, double sy);

template <typename IT>
Sign dotProductSign2D4P_interval(IT px, IT py, IT rx, IT ry, IT qx, IT qy,
                                 IT sx, IT sy);

template <typename ET>
Sign dotProductSign2D4P_exact(ET px, ET py, ET rx, ET ry, ET qx, ET qy, ET sx,
                              ET sy);

inline Sign dotProductSign2D4P_expansion(double px, double py, double rx,
                                         double ry, double qx, double qy,
                                         double sx, double sy);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign2D4P(double px, double py, double rx, double ry, double qx,
                        double qy, double sx, double sy);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign2D4P(const GenericPoint2T<IT, ET> &p,
                        const GenericPoint2T<IT, ET> &r,
                        const GenericPoint2T<IT, ET> &q,
                        const GenericPoint2T<IT, ET> &s);

/*===================================================================*/

inline Sign dotProductSign3D_filtered(double px, double py, double pz,
                                      double rx, double ry, double rz,
                                      double qx, double qy, double qz);

template <typename IT>
Sign dotProductSign3D_interval(IT px, IT py, IT pz, IT rx, IT ry, IT rz, IT qx,
                               IT qy, IT qz);

template <typename ET>
Sign dotProductSign3D_exact(ET px, ET py, ET pz, ET rx, ET ry, ET rz, ET qx,
                            ET qy, ET qz);

inline Sign dotProductSign3D_expansion(double px, double py, double pz,
                                       double rx, double ry, double rz,
                                       double qx, double qy, double qz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign3D(double px, double py, double pz, double rx, double ry,
                      double rz, double qx, double qy, double qz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign3D(const GenericPoint3T<IT, ET> &p,
                      const GenericPoint3T<IT, ET> &r,
                      const GenericPoint3T<IT, ET> &q);

/*===================================================================*/

inline Sign dotProductSign3D4P_filtered(double px, double py, double pz,
                                        double rx, double ry, double rz,
                                        double qx, double qy, double qz,
                                        double sx, double sy, double sz);

template <typename IT>
Sign dotProductSign3D4P_interval(IT px, IT py, IT pz, IT rx, IT ry, IT rz,
                                 IT qx, IT qy, IT qz, IT sx, IT sy, IT sz);

template <typename ET>
Sign dotProductSign3D4P_exact(ET px, ET py, ET pz, ET rx, ET ry, ET rz, ET qx,
                              ET qy, ET qz, ET sx, ET sy, ET sz);

inline Sign dotProductSign3D4P_expansion(double px, double py, double pz,
                                         double rx, double ry, double rz,
                                         double qx, double qy, double qz,
                                         double sx, double sy, double sz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign3D4P(double px, double py, double pz, double rx, double ry,
                        double rz, double qx, double qy, double qz, double sx,
                        double sy, double sz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSign3D4P(const GenericPoint3T<IT, ET> &p,
                        const GenericPoint3T<IT, ET> &r,
                        const GenericPoint3T<IT, ET> &q,
                        const GenericPoint3T<IT, ET> &s);

/*===================================================================*/

inline Sign dotProductSignOn2Dxy4P_filtered(double px, double py, double rx,
                                            double ry, double qx, double qy,
                                            double sx, double sy);

template <typename IT>
Sign dotProductSignOn2Dxy4P_interval(IT px, IT py, IT rx, IT ry, IT qx, IT qy,
                                     IT sx, IT sy);

template <typename ET>
Sign dotProductSignOn2Dxy4P_exact(ET px, ET py, ET rx, ET ry, ET qx, ET qy,
                                  ET sx, ET sy);

inline Sign dotProductSignOn2Dxy4P_expansion(double px, double py, double rx,
                                             double ry, double qx, double qy,
                                             double sx, double sy);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSignOn2Dxy4P(double px, double py, double rx, double ry,
                            double qx, double qy, double sx, double sy);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSignOn2Dxy4P(const GenericPoint3T<IT, ET> &p,
                            const GenericPoint3T<IT, ET> &r,
                            const GenericPoint3T<IT, ET> &q,
                            const GenericPoint3T<IT, ET> &s);

/*===================================================================*/

inline Sign dotProductSignOn2Dyz4P_filtered(double py, double pz, double ry,
                                            double rz, double qy, double qz,
                                            double sy, double sz);

template <typename IT>
Sign dotProductSignOn2Dyz4P_interval(IT py, IT pz, IT ry, IT rz, IT qy, IT qz,
                                     IT sy, IT sz);

template <typename ET>
Sign dotProductSignOn2Dyz4P_exact(ET py, ET pz, ET ry, ET rz, ET qy, ET qz,
                                  ET sy, ET sz);

inline Sign dotProductSignOn2Dyz4P_expansion(double py, double pz, double ry,
                                             double rz, double qy, double qz,
                                             double sy, double sz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSignOn2Dyz4P(double py, double pz, double ry, double rz,
                            double qy, double qz, double sy, double sz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSignOn2Dyz4P(const GenericPoint3T<IT, ET> &p,
                            const GenericPoint3T<IT, ET> &r,
                            const GenericPoint3T<IT, ET> &q,
                            const GenericPoint3T<IT, ET> &s);

/*===================================================================*/

inline Sign dotProductSignOn2Dzx4P_filtered(double px, double pz, double rx,
                                            double rz, double qx, double qz,
                                            double sx, double sz);

template <typename IT>
Sign dotProductSignOn2Dzx4P_interval(IT px, IT pz, IT rx, IT rz, IT qx, IT qz,
                                     IT sx, IT sz);

template <typename ET>
Sign dotProductSignOn2Dzx4P_exact(ET px, ET pz, ET rx, ET rz, ET qx, ET qz,
                                  ET sx, ET sz);

inline Sign dotProductSignOn2Dzx4P_expansion(double px, double pz, double rx,
                                             double rz, double qx, double qz,
                                             double sx, double sz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSignOn2Dzx4P(double px, double pz, double rx, double rz,
                            double qx, double qz, double sx, double sz);

template <typename IT, typename ET, bool WithSSFilter>
Sign dotProductSignOn2Dzx4P(const GenericPoint3T<IT, ET> &p,
                            const GenericPoint3T<IT, ET> &r,
                            const GenericPoint3T<IT, ET> &q,
                            const GenericPoint3T<IT, ET> &s);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign2D_EEI_interval(const GenericPoint2T<IT, ET> &q, IT px,
                                   IT py, IT rx, IT ry);

template <typename IT, typename ET>
Sign dotProductSign2D_EEI_exact(const GenericPoint2T<IT, ET> &q, ET px, ET py,
                                ET rx, ET ry);

template <typename IT, typename ET>
Sign dotProductSign2D_EEI_expansion(const GenericPoint2T<IT, ET> &q, double px,
                                    double py, double rx, double ry);

template <typename IT, typename ET>
Sign dotProductSign2D_EEI(const GenericPoint2T<IT, ET> &q, double px, double py,
                          double rx, double ry);

template <typename IT, typename ET>
Sign dotProductSign2D_EEI(const GenericPoint2T<IT, ET> &q,
                          const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign2D_IEE_interval(const GenericPoint2T<IT, ET> &p, IT rx,
                                   IT ry, IT qx, IT qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IEE_exact(const GenericPoint2T<IT, ET> &p, ET rx, ET ry,
                                ET qx, ET qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IEE_expansion(const GenericPoint2T<IT, ET> &p, double rx,
                                    double ry, double qx, double qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IEE(const GenericPoint2T<IT, ET> &p, double rx, double ry,
                          double qx, double qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IEE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r,
                          const GenericPoint2T<IT, ET> &q);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign2D_IEI_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &q, IT rx,
                                   IT ry);

template <typename IT, typename ET>
Sign dotProductSign2D_IEI_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &q, ET rx, ET ry);

template <typename IT, typename ET>
Sign dotProductSign2D_IEI_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &q, double rx,
                                    double ry);

template <typename IT, typename ET>
Sign dotProductSign2D_IEI(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q, double rx,
                          double ry);

template <typename IT, typename ET>
Sign dotProductSign2D_IEI(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q,
                          const GenericPoint2T<IT, ET> &r);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign2D_IIE_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &r, IT qx,
                                   IT qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IIE_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &r, ET qx, ET qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IIE_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &r, double qx,
                                    double qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IIE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r, double qx,
                          double qy);

template <typename IT, typename ET>
Sign dotProductSign2D_IIE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r,
                          const GenericPoint2T<IT, ET> &q);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign2D_III_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &r,
                                   const GenericPoint2T<IT, ET> &q);

template <typename IT, typename ET>
Sign dotProductSign2D_III_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &r,
                                const GenericPoint2T<IT, ET> &q);

template <typename IT, typename ET>
Sign dotProductSign2D_III_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &r,
                                    const GenericPoint2T<IT, ET> &q);

template <typename IT, typename ET>
Sign dotProductSign2D_III(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r,
                          const GenericPoint2T<IT, ET> &q);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign3D_EEI_interval(const GenericPoint3T<IT, ET> &q, IT px,
                                   IT py, IT pz, IT rx, IT ry, IT rz);

template <typename IT, typename ET>
Sign dotProductSign3D_EEI_exact(const GenericPoint3T<IT, ET> &q, ET px, ET py,
                                ET pz, ET rx, ET ry, ET rz);

template <typename IT, typename ET>
Sign dotProductSign3D_EEI_expansion(const GenericPoint3T<IT, ET> &q, double px,
                                    double py, double pz, double rx, double ry,
                                    double rz);

template <typename IT, typename ET>
Sign dotProductSign3D_EEI(const GenericPoint3T<IT, ET> &q, double px, double py,
                          double pz, double rx, double ry, double rz);

template <typename IT, typename ET>
Sign dotProductSign3D_EEI(const GenericPoint3T<IT, ET> &q,
                          const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign3D_IEE_interval(const GenericPoint3T<IT, ET> &p, IT rx,
                                   IT ry, IT rz, IT qx, IT qy, IT qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEE_exact(const GenericPoint3T<IT, ET> &p, ET rx, ET ry,
                                ET rz, ET qx, ET qy, ET qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEE_expansion(const GenericPoint3T<IT, ET> &p, double rx,
                                    double ry, double rz, double qx, double qy,
                                    double qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEE(const GenericPoint3T<IT, ET> &p, double rx, double ry,
                          double rz, double qx, double qy, double qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r,
                          const GenericPoint3T<IT, ET> &q);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign3D_IEI_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &q, IT rx,
                                   IT ry, IT rz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEI_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &q, ET rx, ET ry,
                                ET rz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEI_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &q, double rx,
                                    double ry, double rz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEI(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q, double rx, double ry,
                          double rz);

template <typename IT, typename ET>
Sign dotProductSign3D_IEI(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q,
                          const GenericPoint3T<IT, ET> &r);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign3D_IIE_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &r, IT qx,
                                   IT qy, IT qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IIE_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &r, ET qx, ET qy,
                                ET qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IIE_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &r, double qx,
                                    double qy, double qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IIE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r, double qx, double qy,
                          double qz);

template <typename IT, typename ET>
Sign dotProductSign3D_IIE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r,
                          const GenericPoint3T<IT, ET> &q);

/*===================================================================*/

template <typename IT, typename ET>
Sign dotProductSign3D_III_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &r,
                                   const GenericPoint3T<IT, ET> &q);

template <typename IT, typename ET>
Sign dotProductSign3D_III_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &r,
                                const GenericPoint3T<IT, ET> &q);

template <typename IT, typename ET>
Sign dotProductSign3D_III_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &r,
                                    const GenericPoint3T<IT, ET> &q);

template <typename IT, typename ET>
Sign dotProductSign3D_III(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r,
                          const GenericPoint3T<IT, ET> &q);

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

inline Sign dotProductSign2D_filtered(double px, double py, double rx,
                                      double ry, double qx, double qy)
{
	double lx = px - qx;
	double ly = py - qy;
	double gx = rx - qx;
	double gy = ry - qy;
	double dx = lx * gx;
	double dy = ly * gy;
	double d  = dx + dy;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gy)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 8.881784197001252e-16;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSign2D_interval(IT px, IT py, IT rx, IT ry, IT qx, IT qy)
{
	typename IT::Protector P;

	IT lx = px - qx;
	IT ly = py - qy;
	IT gx = rx - qx;
	IT gy = ry - qy;
	IT dx = lx * gx;
	IT dy = ly * gy;
	IT d  = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSign2D_exact(ET px, ET py, ET rx, ET ry, ET qx, ET qy)
{
	ET lx = px - qx;
	ET ly = py - qy;
	ET gx = rx - qx;
	ET gy = ry - qy;
	ET dx = lx * gx;
	ET dy = ly * gy;
	ET d  = dx + dy;
	return OMC::sign(d);
}

Sign dotProductSign2D_expansion(double px, double py, double rx, double ry,
                                double qx, double qy)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double gx[2];
	o.Two_Diff(rx, qx, gx);
	double gy[2];
	o.Two_Diff(ry, qy, gy);
	double dx[8];
	int    dx_len = o.Gen_Product(2, lx, 2, gx, dx);
	double dy[8];
	int    dy_len = o.Gen_Product(2, ly, 2, gy, dy);
	double d[16];
	int    d_len = o.Gen_Sum(dx_len, dx, dy_len, dy, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D(double px, double py, double rx, double ry, double qx,
                      double qy)
{
	Sign ret;
	ret = dotProductSign2D_filtered(px, py, rx, ry, qx, qy);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSign2D_interval<IT>(px, py, rx, ry, qx, qy);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D_expansion(px, py, rx, ry, qx, qy);
}

template <typename IT, typename ET>
Sign dotProductSign2D(const GenericPoint2T<IT, ET> &p,
                      const GenericPoint2T<IT, ET> &r,
                      const GenericPoint2T<IT, ET> &q)
{
	return dotProductSign2D<IT, ET>(p.x(), p.y(), r.x(), r.y(), q.x(), q.y());
}

inline Sign dotProductSign2D4P_filtered(double px, double py, double rx,
                                        double ry, double qx, double qy,
                                        double sx, double sy)
{
	double lx = px - qx;
	double ly = py - qy;
	double gx = rx - sx;
	double gy = ry - sy;
	double dx = lx * gx;
	double dy = ly * gy;
	double d  = dx + dy;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gy)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 8.881784197001252e-16;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSign2D4P_interval(IT px, IT py, IT rx, IT ry, IT qx, IT qy,
                                 IT sx, IT sy)
{
	typename IT::Protector P;

	IT lx = px - qx;
	IT ly = py - qy;
	IT gx = rx - sx;
	IT gy = ry - sy;
	IT dx = lx * gx;
	IT dy = ly * gy;
	IT d  = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSign2D4P_exact(ET px, ET py, ET rx, ET ry, ET qx, ET qy, ET sx,
                              ET sy)
{
	ET lx = px - qx;
	ET ly = py - qy;
	ET gx = rx - sx;
	ET gy = ry - sy;
	ET dx = lx * gx;
	ET dy = ly * gy;
	ET d  = dx + dy;
	return OMC::sign(d);
}

Sign dotProductSign2D4P_expansion(double px, double py, double rx, double ry,
                                  double qx, double qy, double sx, double sy)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double gx[2];
	o.Two_Diff(rx, sx, gx);
	double gy[2];
	o.Two_Diff(ry, sy, gy);
	double dx[8];
	int    dx_len = o.Gen_Product(2, lx, 2, gx, dx);
	double dy[8];
	int    dy_len = o.Gen_Product(2, ly, 2, gy, dy);
	double d[16];
	int    d_len = o.Gen_Sum(dx_len, dx, dy_len, dy, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D4P(double px, double py, double rx, double ry, double qx,
                        double qy, double sx, double sy)
{
	Sign ret;
	ret = dotProductSign2D4P_filtered(px, py, rx, ry, qx, qy, sx, sy);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSign2D4P_interval<IT>(px, py, rx, ry, qx, qy, sx, sy);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D4P_expansion(px, py, rx, ry, qx, qy, sx, sy);
}

template <typename IT, typename ET>
Sign dotProductSign2D4P(const GenericPoint2T<IT, ET> &p,
                        const GenericPoint2T<IT, ET> &r,
                        const GenericPoint2T<IT, ET> &q,
                        const GenericPoint2T<IT, ET> &s)
{
	return dotProductSign2D4P<IT, ET>(p.x(), p.y(), r.x(), r.y(), q.x(), q.y(),
	                                  s.x(), s.y());
}

inline Sign dotProductSign3D_filtered(double px, double py, double pz,
                                      double rx, double ry, double rz,
                                      double qx, double qy, double qz)
{
	double lx = px - qx;
	double ly = py - qy;
	double lz = pz - qz;
	double gx = rx - qx;
	double gy = ry - qy;
	double gz = rz - qz;
	double dx = lx * gx;
	double dy = ly * gy;
	double dz = lz * gz;
	double d1 = dx + dy;
	double d  = d1 + dz;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lz)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gy)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gz)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 1.4432899320127035e-15;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSign3D_interval(IT px, IT py, IT pz, IT rx, IT ry, IT rz, IT qx,
                               IT qy, IT qz)
{
	typename IT::Protector P;

	IT lx = px - qx;
	IT ly = py - qy;
	IT lz = pz - qz;
	IT gx = rx - qx;
	IT gy = ry - qy;
	IT gz = rz - qz;
	IT dx = lx * gx;
	IT dy = ly * gy;
	IT dz = lz * gz;
	IT d1 = dx + dy;
	IT d  = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSign3D_exact(ET px, ET py, ET pz, ET rx, ET ry, ET rz, ET qx,
                            ET qy, ET qz)
{
	ET lx = px - qx;
	ET ly = py - qy;
	ET lz = pz - qz;
	ET gx = rx - qx;
	ET gy = ry - qy;
	ET gz = rz - qz;
	ET dx = lx * gx;
	ET dy = ly * gy;
	ET dz = lz * gz;
	ET d1 = dx + dy;
	ET d  = d1 + dz;
	return OMC::sign(d);
}

Sign dotProductSign3D_expansion(double px, double py, double pz, double rx,
                                double ry, double rz, double qx, double qy,
                                double qz)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double lz[2];
	o.Two_Diff(pz, qz, lz);
	double gx[2];
	o.Two_Diff(rx, qx, gx);
	double gy[2];
	o.Two_Diff(ry, qy, gy);
	double gz[2];
	o.Two_Diff(rz, qz, gz);
	double dx[8];
	int    dx_len = o.Gen_Product(2, lx, 2, gx, dx);
	double dy[8];
	int    dy_len = o.Gen_Product(2, ly, 2, gy, dy);
	double dz[8];
	int    dz_len = o.Gen_Product(2, lz, 2, gz, dz);
	double d1[16];
	int    d1_len = o.Gen_Sum(dx_len, dx, dy_len, dy, d1);
	double d[24];
	int    d_len = o.Gen_Sum(d1_len, d1, dz_len, dz, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D(double px, double py, double pz, double rx, double ry,
                      double rz, double qx, double qy, double qz)
{
	Sign ret;
	ret = dotProductSign3D_filtered(px, py, pz, rx, ry, rz, qx, qy, qz);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSign3D_interval<IT>(px, py, pz, rx, ry, rz, qx, qy, qz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D_expansion(px, py, pz, rx, ry, rz, qx, qy, qz);
}

template <typename IT, typename ET>
Sign dotProductSign3D(const GenericPoint3T<IT, ET> &p,
                      const GenericPoint3T<IT, ET> &r,
                      const GenericPoint3T<IT, ET> &q)
{
	return dotProductSign3D<IT, ET>(p.x(), p.y(), p.z(), r.x(), r.y(), r.z(),
	                                q.x(), q.y(), q.z());
}

inline Sign dotProductSign3D4P_filtered(double px, double py, double pz,
                                        double rx, double ry, double rz,
                                        double qx, double qy, double qz,
                                        double sx, double sy, double sz)
{
	double lx = px - qx;
	double ly = py - qy;
	double lz = pz - qz;
	double gx = rx - sx;
	double gy = ry - sy;
	double gz = rz - sz;
	double dx = lx * gx;
	double dy = ly * gy;
	double dz = lz * gz;
	double d1 = dx + dy;
	double d  = d1 + dz;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lz)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gy)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gz)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 1.4432899320127035e-15;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSign3D4P_interval(IT px, IT py, IT pz, IT rx, IT ry, IT rz,
                                 IT qx, IT qy, IT qz, IT sx, IT sy, IT sz)
{
	typename IT::Protector P;

	IT lx = px - qx;
	IT ly = py - qy;
	IT lz = pz - qz;
	IT gx = rx - sx;
	IT gy = ry - sy;
	IT gz = rz - sz;
	IT dx = lx * gx;
	IT dy = ly * gy;
	IT dz = lz * gz;
	IT d1 = dx + dy;
	IT d  = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSign3D4P_exact(ET px, ET py, ET pz, ET rx, ET ry, ET rz, ET qx,
                              ET qy, ET qz, ET sx, ET sy, ET sz)
{
	ET lx = px - qx;
	ET ly = py - qy;
	ET lz = pz - qz;
	ET gx = rx - sx;
	ET gy = ry - sy;
	ET gz = rz - sz;
	ET dx = lx * gx;
	ET dy = ly * gy;
	ET dz = lz * gz;
	ET d1 = dx + dy;
	ET d  = d1 + dz;
	return OMC::sign(d);
}

Sign dotProductSign3D4P_expansion(double px, double py, double pz, double rx,
                                  double ry, double rz, double qx, double qy,
                                  double qz, double sx, double sy, double sz)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double lz[2];
	o.Two_Diff(pz, qz, lz);
	double gx[2];
	o.Two_Diff(rx, sx, gx);
	double gy[2];
	o.Two_Diff(ry, sy, gy);
	double gz[2];
	o.Two_Diff(rz, sz, gz);
	double dx[8];
	int    dx_len = o.Gen_Product(2, lx, 2, gx, dx);
	double dy[8];
	int    dy_len = o.Gen_Product(2, ly, 2, gy, dy);
	double dz[8];
	int    dz_len = o.Gen_Product(2, lz, 2, gz, dz);
	double d1[16];
	int    d1_len = o.Gen_Sum(dx_len, dx, dy_len, dy, d1);
	double d[24];
	int    d_len = o.Gen_Sum(d1_len, d1, dz_len, dz, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D4P(double px, double py, double pz, double rx, double ry,
                        double rz, double qx, double qy, double qz, double sx,
                        double sy, double sz)
{
	Sign ret;
	ret =
	  dotProductSign3D4P_filtered(px, py, pz, rx, ry, rz, qx, qy, qz, sx, sy, sz);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSign3D4P_interval<IT>(px, py, pz, rx, ry, rz, qx, qy, qz, sx,
	                                      sy, sz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D4P_expansion(px, py, pz, rx, ry, rz, qx, qy, qz, sx,
	                                    sy, sz);
}

template <typename IT, typename ET>
Sign dotProductSign3D4P(const GenericPoint3T<IT, ET> &p,
                        const GenericPoint3T<IT, ET> &r,
                        const GenericPoint3T<IT, ET> &q,
                        const GenericPoint3T<IT, ET> &s)
{
	return dotProductSign3D4P<IT, ET>(p.x(), p.y(), p.z(), r.x(), r.y(), r.z(),
	                                  q.x(), q.y(), q.z(), s.x(), s.y(), s.z());
}

inline Sign dotProductSignOn2Dxy4P_filtered(double px, double py, double rx,
                                            double ry, double qx, double qy,
                                            double sx, double sy)
{
	double lx = px - qx;
	double ly = py - qy;
	double gx = rx - sx;
	double gy = ry - sy;
	double dx = lx * gx;
	double dy = ly * gy;
	double d  = dx + dy;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gy)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 8.881784197001252e-16;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSignOn2Dxy4P_interval(IT px, IT py, IT rx, IT ry, IT qx, IT qy,
                                     IT sx, IT sy)
{
	typename IT::Protector P;

	IT lx = px - qx;
	IT ly = py - qy;
	IT gx = rx - sx;
	IT gy = ry - sy;
	IT dx = lx * gx;
	IT dy = ly * gy;
	IT d  = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSignOn2Dxy4P_exact(ET px, ET py, ET rx, ET ry, ET qx, ET qy,
                                  ET sx, ET sy)
{
	ET lx = px - qx;
	ET ly = py - qy;
	ET gx = rx - sx;
	ET gy = ry - sy;
	ET dx = lx * gx;
	ET dy = ly * gy;
	ET d  = dx + dy;
	return OMC::sign(d);
}

Sign dotProductSignOn2Dxy4P_expansion(double px, double py, double rx,
                                      double ry, double qx, double qy,
                                      double sx, double sy)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double ly[2];
	o.Two_Diff(py, qy, ly);
	double gx[2];
	o.Two_Diff(rx, sx, gx);
	double gy[2];
	o.Two_Diff(ry, sy, gy);
	double dx[8];
	int    dx_len = o.Gen_Product(2, lx, 2, gx, dx);
	double dy[8];
	int    dy_len = o.Gen_Product(2, ly, 2, gy, dy);
	double d[16];
	int    d_len = o.Gen_Sum(dx_len, dx, dy_len, dy, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSignOn2Dxy4P(double px, double py, double rx, double ry,
                            double qx, double qy, double sx, double sy)
{
	Sign ret;
	ret = dotProductSignOn2Dxy4P_filtered(px, py, rx, ry, qx, qy, sx, sy);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSignOn2Dxy4P_interval<IT>(px, py, rx, ry, qx, qy, sx, sy);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSignOn2Dxy4P_expansion(px, py, rx, ry, qx, qy, sx, sy);
}

template <typename IT, typename ET>
Sign dotProductSignOn2Dxy4P(const GenericPoint3T<IT, ET> &p,
                            const GenericPoint3T<IT, ET> &r,
                            const GenericPoint3T<IT, ET> &q,
                            const GenericPoint3T<IT, ET> &s)
{
	return dotProductSignOn2Dxy4P<IT, ET>(p.x(), p.y(), r.x(), r.y(), q.x(),
	                                      q.y(), s.x(), s.y());
}

inline Sign dotProductSignOn2Dyz4P_filtered(double py, double pz, double ry,
                                            double rz, double qy, double qz,
                                            double sy, double sz)
{
	double ly = py - qy;
	double lz = pz - qz;
	double gy = ry - sy;
	double gz = rz - sz;
	double dy = ly * gy;
	double dz = lz * gz;
	double d  = dy + dz;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(ly)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lz)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gy)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gz)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 8.881784197001252e-16;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSignOn2Dyz4P_interval(IT py, IT pz, IT ry, IT rz, IT qy, IT qz,
                                     IT sy, IT sz)
{
	typename IT::Protector P;

	IT ly = py - qy;
	IT lz = pz - qz;
	IT gy = ry - sy;
	IT gz = rz - sz;
	IT dy = ly * gy;
	IT dz = lz * gz;
	IT d  = dy + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSignOn2Dyz4P_exact(ET py, ET pz, ET ry, ET rz, ET qy, ET qz,
                                  ET sy, ET sz)
{
	ET ly = py - qy;
	ET lz = pz - qz;
	ET gy = ry - sy;
	ET gz = rz - sz;
	ET dy = ly * gy;
	ET dz = lz * gz;
	ET d  = dy + dz;
	return OMC::sign(d);
}

Sign dotProductSignOn2Dyz4P_expansion(double py, double pz, double ry,
                                      double rz, double qy, double qz,
                                      double sy, double sz)
{
	expansionObject o;
	double          ly[2];
	o.Two_Diff(py, qy, ly);
	double lz[2];
	o.Two_Diff(pz, qz, lz);
	double gy[2];
	o.Two_Diff(ry, sy, gy);
	double gz[2];
	o.Two_Diff(rz, sz, gz);
	double dy[8];
	int    dy_len = o.Gen_Product(2, ly, 2, gy, dy);
	double dz[8];
	int    dz_len = o.Gen_Product(2, lz, 2, gz, dz);
	double d[16];
	int    d_len = o.Gen_Sum(dy_len, dy, dz_len, dz, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSignOn2Dyz4P(double py, double pz, double ry, double rz,
                            double qy, double qz, double sy, double sz)
{
	Sign ret;
	ret = dotProductSignOn2Dyz4P_filtered(py, pz, ry, rz, qy, qz, sy, sz);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSignOn2Dyz4P_interval<IT>(py, pz, ry, rz, qy, qz, sy, sz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSignOn2Dyz4P_expansion(py, pz, ry, rz, qy, qz, sy, sz);
}

template <typename IT, typename ET>
Sign dotProductSignOn2Dyz4P(const GenericPoint3T<IT, ET> &p,
                            const GenericPoint3T<IT, ET> &r,
                            const GenericPoint3T<IT, ET> &q,
                            const GenericPoint3T<IT, ET> &s)
{
	return dotProductSignOn2Dyz4P<IT, ET>(p.y(), p.z(), r.y(), r.z(), q.y(),
	                                      q.z(), s.y(), s.z());
}

inline Sign dotProductSignOn2Dzx4P_filtered(double px, double pz, double rx,
                                            double rz, double qx, double qz,
                                            double sx, double sz)
{
	double lx = px - qx;
	double lz = pz - qz;
	double gx = rx - sx;
	double gz = rz - sz;
	double dx = lx * gx;
	double dz = lz * gz;
	double d  = dx + dz;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(lx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(lz)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gx)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(gz)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= 8.881784197001252e-16;

	return filter_sign(d, epsilon);
}

template <typename IT>
Sign dotProductSignOn2Dzx4P_interval(IT px, IT pz, IT rx, IT rz, IT qx, IT qz,
                                     IT sx, IT sz)
{
	typename IT::Protector P;

	IT lx = px - qx;
	IT lz = pz - qz;
	IT gx = rx - sx;
	IT gz = rz - sz;
	IT dx = lx * gx;
	IT dz = lz * gz;
	IT d  = dx + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign dotProductSignOn2Dzx4P_exact(ET px, ET pz, ET rx, ET rz, ET qx, ET qz,
                                  ET sx, ET sz)
{
	ET lx = px - qx;
	ET lz = pz - qz;
	ET gx = rx - sx;
	ET gz = rz - sz;
	ET dx = lx * gx;
	ET dz = lz * gz;
	ET d  = dx + dz;
	return OMC::sign(d);
}

Sign dotProductSignOn2Dzx4P_expansion(double px, double pz, double rx,
                                      double rz, double qx, double qz,
                                      double sx, double sz)
{
	expansionObject o;
	double          lx[2];
	o.Two_Diff(px, qx, lx);
	double lz[2];
	o.Two_Diff(pz, qz, lz);
	double gx[2];
	o.Two_Diff(rx, sx, gx);
	double gz[2];
	o.Two_Diff(rz, sz, gz);
	double dx[8];
	int    dx_len = o.Gen_Product(2, lx, 2, gx, dx);
	double dz[8];
	int    dz_len = o.Gen_Product(2, lz, 2, gz, dz);
	double d[16];
	int    d_len = o.Gen_Sum(dx_len, dx, dz_len, dz, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSignOn2Dzx4P(double px, double pz, double rx, double rz,
                            double qx, double qz, double sx, double sz)
{
	Sign ret;
	ret = dotProductSignOn2Dzx4P_filtered(px, pz, rx, rz, qx, qz, sx, sz);
	if (is_sign_reliable(ret))
		return ret;
	ret = dotProductSignOn2Dzx4P_interval<IT>(px, pz, rx, rz, qx, qz, sx, sz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSignOn2Dzx4P_expansion(px, pz, rx, rz, qx, qz, sx, sz);
}

template <typename IT, typename ET>
Sign dotProductSignOn2Dzx4P(const GenericPoint3T<IT, ET> &p,
                            const GenericPoint3T<IT, ET> &r,
                            const GenericPoint3T<IT, ET> &q,
                            const GenericPoint3T<IT, ET> &s)
{
	return dotProductSignOn2Dzx4P<IT, ET>(p.x(), p.z(), r.x(), r.z(), q.x(),
	                                      q.z(), s.x(), s.z());
}

template <typename IT, typename ET>
Sign dotProductSign2D_EEI_interval(const GenericPoint2T<IT, ET> &q, IT px,
                                   IT py, IT rx, IT ry)
{
	IT lqx, lqy, dq;
	if (!q.getIntervalLambda(lqx, lqy, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pxq = px * dq;
	IT pyq = py * dq;
	IT rxq = rx * dq;
	IT ryq = ry * dq;
	IT lx  = pxq - lqx;
	IT ly  = pyq - lqy;
	IT gx  = rxq - lqx;
	IT gy  = ryq - lqy;
	IT dx  = lx * gx;
	IT dy  = ly * gy;
	IT d   = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_EEI_exact(const GenericPoint2T<IT, ET> &q, ET px, ET py,
                                ET rx, ET ry)
{
	ET lqx, lqy, dq;
	q.getExactLambda(lqx, lqy, dq);
	ET pxq = px * dq;
	ET pyq = py * dq;
	ET rxq = rx * dq;
	ET ryq = ry * dq;
	ET lx  = pxq - lqx;
	ET ly  = pyq - lqy;
	ET gx  = rxq - lqx;
	ET gy  = ryq - lqy;
	ET dx  = lx * gx;
	ET dy  = ly * gy;
	ET d   = dx + dy;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_EEI_expansion(const GenericPoint2T<IT, ET> &q, double px,
                                    double py, double rx, double ry)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lqx_p[128], *lqx = lqx_p, lqy_p[128], *lqy = lqy_p, dq_p[128],
	                   *dq = dq_p;
	int lqx_len = 128, lqy_len = 128, dq_len = 128;
	q.getExpansionLambda(&lqx, lqx_len, &lqy, lqy_len, &dq, dq_len);
	if ((dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          pxq_p[128], *pxq = pxq_p;
		int    pxq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, px, &pxq, 128);
		double pyq_p[128], *pyq = pyq_p;
		int    pyq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, py, &pyq, 128);
		double rxq_p[128], *rxq = rxq_p;
		int    rxq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, rx, &rxq, 128);
		double ryq_p[128], *ryq = ryq_p;
		int    ryq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, ry, &ryq, 128);
		double lx_p[128], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(pxq_len, pxq, lqx_len, lqx, &lx, 128);
		double ly_p[128], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(pyq_len, pyq, lqy_len, lqy, &ly, 128);
		double gx_p[128], *gx = gx_p;
		int gx_len = o.Gen_Diff_With_PreAlloc(rxq_len, rxq, lqx_len, lqx, &gx, 128);
		double gy_p[128], *gy = gy_p;
		int gy_len = o.Gen_Diff_With_PreAlloc(ryq_len, ryq, lqy_len, lqy, &gy, 128);
		double dx_p[128], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 128);
		double dy_p[128], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 128);
		double d_p[128], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d, 128);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (ryq_p != ryq)
			FreeDoubles(ryq);
		if (rxq_p != rxq)
			FreeDoubles(rxq);
		if (pyq_p != pyq)
			FreeDoubles(pyq);
		if (pxq_p != pxq)
			FreeDoubles(pxq);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lqx_p != lqx)
			FreeDoubles(lqx);
		if (lqy_p != lqy)
			FreeDoubles(lqy);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign2D_EEI_exact<IT, ET>(q, px, py, rx, ry);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D_EEI(const GenericPoint2T<IT, ET> &q, double px, double py,
                          double rx, double ry)
{
	Sign ret;
	ret = dotProductSign2D_EEI_interval<IT, ET>(q, px, py, rx, ry);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D_EEI_expansion<IT, ET>(q, px, py, rx, ry);
}

template <typename IT, typename ET>
Sign dotProductSign2D_EEI(const GenericPoint2T<IT, ET> &q,
                          const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r)
{
	return dotProductSign2D_EEI<IT, ET>(q, p.x(), p.y(), r.x(), r.y());
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEE_interval(const GenericPoint2T<IT, ET> &p, IT rx,
                                   IT ry, IT qx, IT qy)
{
	IT lpx, lpy, dp;
	if (!p.getIntervalLambda(lpx, lpy, dp))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT qxd = qx * dp;
	IT qyd = qy * dp;
	IT lx  = lpx - qxd;
	IT ly  = lpy - qyd;
	IT gx  = rx - qx;
	IT gy  = ry - qy;
	IT dx  = lx * gx;
	IT dy  = ly * gy;
	IT d   = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEE_exact(const GenericPoint2T<IT, ET> &p, ET rx, ET ry,
                                ET qx, ET qy)
{
	ET lpx, lpy, dp;
	p.getExactLambda(lpx, lpy, dp);
	ET qxd = qx * dp;
	ET qyd = qy * dp;
	ET lx  = lpx - qxd;
	ET ly  = lpy - qyd;
	ET gx  = rx - qx;
	ET gy  = ry - qy;
	ET dx  = lx * gx;
	ET dy  = ly * gy;
	ET d   = dx + dy;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEE_expansion(const GenericPoint2T<IT, ET> &p, double rx,
                                    double ry, double qx, double qy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[128], *lpx = lpx_p, lpy_p[128], *lpy = lpy_p, dp_p[128],
	                   *dp = dp_p;
	int lpx_len = 128, lpy_len = 128, dp_len = 128;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &dp, dp_len);
	if ((dp[dp_len - 1] != 0))
	{
		expansionObject o;
		double          qxd_p[128], *qxd = qxd_p;
		int    qxd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qx, &qxd, 128);
		double qyd_p[128], *qyd = qyd_p;
		int    qyd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qy, &qyd, 128);
		double lx_p[128], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(lpx_len, lpx, qxd_len, qxd, &lx, 128);
		double ly_p[128], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(lpy_len, lpy, qyd_len, qyd, &ly, 128);
		double gx[2];
		o.Two_Diff(rx, qx, gx);
		double gy[2];
		o.Two_Diff(ry, qy, gy);
		double dx_p[128], *dx = dx_p;
		int    dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, 2, gx, &dx, 128);
		double dy_p[128], *dy = dy_p;
		int    dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, 2, gy, &dy, 128);
		double d_p[128], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d, 128);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (qyd_p != qyd)
			FreeDoubles(qyd);
		if (qxd_p != qxd)
			FreeDoubles(qxd);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign2D_IEE_exact<IT, ET>(p, rx, ry, qx, qy);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEE(const GenericPoint2T<IT, ET> &p, double rx, double ry,
                          double qx, double qy)
{
	Sign ret;
	ret = dotProductSign2D_IEE_interval<IT, ET>(p, rx, ry, qx, qy);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D_IEE_expansion<IT, ET>(p, rx, ry, qx, qy);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r,
                          const GenericPoint2T<IT, ET> &q)
{
	return dotProductSign2D_IEE<IT, ET>(p, r.x(), r.y(), q.x(), q.y());
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEI_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &q, IT rx,
                                   IT ry)
{
	IT lpx, lpy, dp, lqx, lqy, dq;
	if (!p.getIntervalLambda(lpx, lpy, dp) || !q.getIntervalLambda(lqx, lqy, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dqp  = dq * dp;
	IT pxq  = lpx * dqp;
	IT pyq  = lpy * dqp;
	IT rxq  = rx * dq;
	IT ryq  = ry * dq;
	IT lqxd = lqx * dp;
	IT lqyd = lqy * dp;
	IT lx   = pxq - lqxd;
	IT ly   = pyq - lqyd;
	IT gx   = rxq - lqx;
	IT gy   = ryq - lqy;
	IT dx   = lx * gx;
	IT dy   = ly * gy;
	IT d    = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEI_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &q, ET rx, ET ry)
{
	ET lpx, lpy, dp, lqx, lqy, dq;
	p.getExactLambda(lpx, lpy, dp);
	q.getExactLambda(lqx, lqy, dq);
	ET dqp  = dq * dp;
	ET pxq  = lpx * dqp;
	ET pyq  = lpy * dqp;
	ET rxq  = rx * dq;
	ET ryq  = ry * dq;
	ET lqxd = lqx * dp;
	ET lqyd = lqy * dp;
	ET lx   = pxq - lqxd;
	ET ly   = pyq - lqyd;
	ET gx   = rxq - lqx;
	ET gy   = ryq - lqy;
	ET dx   = lx * gx;
	ET dy   = ly * gy;
	ET d    = dx + dy;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEI_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &q, double rx,
                                    double ry)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[64], *lpx = lpx_p, lpy_p[64], *lpy = lpy_p, dp_p[64], *dp = dp_p,
	                  lqx_p[64], *lqx = lqx_p, lqy_p[64], *lqy = lqy_p, dq_p[64],
	                  *dq = dq_p;
	int lpx_len = 64, lpy_len = 64, dp_len = 64, lqx_len = 64, lqy_len = 64,
	    dq_len = 64;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &dp, dp_len);
	q.getExpansionLambda(&lqx, lqx_len, &lqy, lqy_len, &dq, dq_len);
	if ((dp[dp_len - 1] != 0) && (dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          dqp_p[64], *dqp = dqp_p;
		int dqp_len = o.Gen_Product_With_PreAlloc(dq_len, dq, dp_len, dp, &dqp, 64);
		double pxq_p[64], *pxq = pxq_p;
		int    pxq_len =
		  o.Gen_Product_With_PreAlloc(lpx_len, lpx, dqp_len, dqp, &pxq, 64);
		double pyq_p[64], *pyq = pyq_p;
		int    pyq_len =
		  o.Gen_Product_With_PreAlloc(lpy_len, lpy, dqp_len, dqp, &pyq, 64);
		double rxq_p[64], *rxq = rxq_p;
		int    rxq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, rx, &rxq, 64);
		double ryq_p[64], *ryq = ryq_p;
		int    ryq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, ry, &ryq, 64);
		double lqxd_p[64], *lqxd = lqxd_p;
		int    lqxd_len =
		  o.Gen_Product_With_PreAlloc(lqx_len, lqx, dp_len, dp, &lqxd, 64);
		double lqyd_p[64], *lqyd = lqyd_p;
		int    lqyd_len =
		  o.Gen_Product_With_PreAlloc(lqy_len, lqy, dp_len, dp, &lqyd, 64);
		double lx_p[64], *lx = lx_p;
		int    lx_len =
		  o.Gen_Diff_With_PreAlloc(pxq_len, pxq, lqxd_len, lqxd, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int    ly_len =
		  o.Gen_Diff_With_PreAlloc(pyq_len, pyq, lqyd_len, lqyd, &ly, 64);
		double gx_p[64], *gx = gx_p;
		int gx_len = o.Gen_Diff_With_PreAlloc(rxq_len, rxq, lqx_len, lqx, &gx, 64);
		double gy_p[64], *gy = gy_p;
		int gy_len = o.Gen_Diff_With_PreAlloc(ryq_len, ryq, lqy_len, lqy, &gy, 64);
		double dx_p[64], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 64);
		double dy_p[64], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 64);
		double d_p[64], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d, 64);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (lqyd_p != lqyd)
			FreeDoubles(lqyd);
		if (lqxd_p != lqxd)
			FreeDoubles(lqxd);
		if (ryq_p != ryq)
			FreeDoubles(ryq);
		if (rxq_p != rxq)
			FreeDoubles(rxq);
		if (pyq_p != pyq)
			FreeDoubles(pyq);
		if (pxq_p != pxq)
			FreeDoubles(pxq);
		if (dqp_p != dqp)
			FreeDoubles(dqp);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lqx_p != lqx)
			FreeDoubles(lqx);
		if (lqy_p != lqy)
			FreeDoubles(lqy);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign2D_IEI_exact<IT, ET>(p, q, rx, ry);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEI(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q, double rx, double ry)
{
	Sign ret;
	ret = dotProductSign2D_IEI_interval<IT, ET>(p, q, rx, ry);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D_IEI_expansion<IT, ET>(p, q, rx, ry);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IEI(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &q,
                          const GenericPoint2T<IT, ET> &r)
{
	return dotProductSign2D_IEI<IT, ET>(p, q, r.x(), r.y());
}

template <typename IT, typename ET>
Sign dotProductSign2D_IIE_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &r, IT qx,
                                   IT qy)
{
	IT lpx, lpy, dp, lrx, lry, dr;
	if (!p.getIntervalLambda(lpx, lpy, dp) || !r.getIntervalLambda(lrx, lry, dr))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT qxd = qx * dp;
	IT qyd = qy * dp;
	IT lx  = lpx - qxd;
	IT ly  = lpy - qyd;
	IT qxr = qx * dr;
	IT qyr = qy * dr;
	IT gx  = lrx - qxr;
	IT gy  = lry - qyr;
	IT dx  = lx * gx;
	IT dy  = ly * gy;
	IT d   = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IIE_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &r, ET qx, ET qy)
{
	ET lpx, lpy, dp, lrx, lry, dr;
	p.getExactLambda(lpx, lpy, dp);
	r.getExactLambda(lrx, lry, dr);
	ET qxd = qx * dp;
	ET qyd = qy * dp;
	ET lx  = lpx - qxd;
	ET ly  = lpy - qyd;
	ET qxr = qx * dr;
	ET qyr = qy * dr;
	ET gx  = lrx - qxr;
	ET gy  = lry - qyr;
	ET dx  = lx * gx;
	ET dy  = ly * gy;
	ET d   = dx + dy;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IIE_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &r, double qx,
                                    double qy)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[64], *lpx = lpx_p, lpy_p[64], *lpy = lpy_p, dp_p[64], *dp = dp_p,
	                  lrx_p[64], *lrx = lrx_p, lry_p[64], *lry = lry_p, dr_p[64],
	                  *dr = dr_p;
	int lpx_len = 64, lpy_len = 64, dp_len = 64, lrx_len = 64, lry_len = 64,
	    dr_len = 64;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &dp, dp_len);
	r.getExpansionLambda(&lrx, lrx_len, &lry, lry_len, &dr, dr_len);
	if ((dp[dp_len - 1] != 0) && (dr[dr_len - 1] != 0))
	{
		expansionObject o;
		double          qxd_p[64], *qxd = qxd_p;
		int    qxd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qx, &qxd, 64);
		double qyd_p[64], *qyd = qyd_p;
		int    qyd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qy, &qyd, 64);
		double lx_p[64], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(lpx_len, lpx, qxd_len, qxd, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(lpy_len, lpy, qyd_len, qyd, &ly, 64);
		double qxr_p[64], *qxr = qxr_p;
		int    qxr_len = o.Gen_Scale_With_PreAlloc(dr_len, dr, qx, &qxr, 64);
		double qyr_p[64], *qyr = qyr_p;
		int    qyr_len = o.Gen_Scale_With_PreAlloc(dr_len, dr, qy, &qyr, 64);
		double gx_p[64], *gx = gx_p;
		int gx_len = o.Gen_Diff_With_PreAlloc(lrx_len, lrx, qxr_len, qxr, &gx, 64);
		double gy_p[64], *gy = gy_p;
		int gy_len = o.Gen_Diff_With_PreAlloc(lry_len, lry, qyr_len, qyr, &gy, 64);
		double dx_p[64], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 64);
		double dy_p[64], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 64);
		double d_p[64], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d, 64);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (qyr_p != qyr)
			FreeDoubles(qyr);
		if (qxr_p != qxr)
			FreeDoubles(qxr);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (qyd_p != qyd)
			FreeDoubles(qyd);
		if (qxd_p != qxd)
			FreeDoubles(qxd);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lrx_p != lrx)
			FreeDoubles(lrx);
		if (lry_p != lry)
			FreeDoubles(lry);
		if (dr_p != dr)
			FreeDoubles(dr);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign2D_IIE_exact<IT, ET>(p, r, qx, qy);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D_IIE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r, double qx, double qy)
{
	Sign ret;
	ret = dotProductSign2D_IIE_interval<IT, ET>(p, r, qx, qy);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D_IIE_expansion<IT, ET>(p, r, qx, qy);
}

template <typename IT, typename ET>
Sign dotProductSign2D_IIE(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r,
                          const GenericPoint2T<IT, ET> &q)
{
	return dotProductSign2D_IIE<IT, ET>(p, r, q.x(), q.y());
}

template <typename IT, typename ET>
Sign dotProductSign2D_III_interval(const GenericPoint2T<IT, ET> &p,
                                   const GenericPoint2T<IT, ET> &r,
                                   const GenericPoint2T<IT, ET> &q)
{
	IT lpx, lpy, dp, lrx, lry, dr, lqx, lqy, dq;
	if (!p.getIntervalLambda(lpx, lpy, dp) ||
	    !r.getIntervalLambda(lrx, lry, dr) || !q.getIntervalLambda(lqx, lqy, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT qxd  = lqx * dp;
	IT qyd  = lqy * dp;
	IT lpxq = lpx * dq;
	IT lpyq = lpy * dq;
	IT lx   = lpxq - qxd;
	IT ly   = lpyq - qyd;
	IT qxr  = lqx * dr;
	IT qyr  = lqy * dr;
	IT lrxq = lrx * dq;
	IT lryq = lry * dq;
	IT gx   = lrxq - qxr;
	IT gy   = lryq - qyr;
	IT dx   = lx * gx;
	IT dy   = ly * gy;
	IT d    = dx + dy;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_III_exact(const GenericPoint2T<IT, ET> &p,
                                const GenericPoint2T<IT, ET> &r,
                                const GenericPoint2T<IT, ET> &q)
{
	ET lpx, lpy, dp, lrx, lry, dr, lqx, lqy, dq;
	p.getExactLambda(lpx, lpy, dp);
	r.getExactLambda(lrx, lry, dr);
	q.getExactLambda(lqx, lqy, dq);
	ET qxd  = lqx * dp;
	ET qyd  = lqy * dp;
	ET lpxq = lpx * dq;
	ET lpyq = lpy * dq;
	ET lx   = lpxq - qxd;
	ET ly   = lpyq - qyd;
	ET qxr  = lqx * dr;
	ET qyr  = lqy * dr;
	ET lrxq = lrx * dq;
	ET lryq = lry * dq;
	ET gx   = lrxq - qxr;
	ET gy   = lryq - qyr;
	ET dx   = lx * gx;
	ET dy   = ly * gy;
	ET d    = dx + dy;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign2D_III_expansion(const GenericPoint2T<IT, ET> &p,
                                    const GenericPoint2T<IT, ET> &r,
                                    const GenericPoint2T<IT, ET> &q)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[64], *lpx = lpx_p, lpy_p[64], *lpy = lpy_p, dp_p[64], *dp = dp_p,
	                  lrx_p[64], *lrx = lrx_p, lry_p[64], *lry = lry_p, dr_p[64],
	                  *dr = dr_p, lqx_p[64], *lqx = lqx_p, lqy_p[64],
	                  *lqy = lqy_p, dq_p[64], *dq = dq_p;
	int lpx_len = 64, lpy_len = 64, dp_len = 64, lrx_len = 64, lry_len = 64,
	    dr_len = 64, lqx_len = 64, lqy_len = 64, dq_len = 64;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &dp, dp_len);
	r.getExpansionLambda(&lrx, lrx_len, &lry, lry_len, &dr, dr_len);
	q.getExpansionLambda(&lqx, lqx_len, &lqy, lqy_len, &dq, dq_len);
	if ((dp[dp_len - 1] != 0) && (dr[dr_len - 1] != 0) && (dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          qxd_p[64], *qxd = qxd_p;
		int             qxd_len =
		  o.Gen_Product_With_PreAlloc(lqx_len, lqx, dp_len, dp, &qxd, 64);
		double qyd_p[64], *qyd = qyd_p;
		int    qyd_len =
		  o.Gen_Product_With_PreAlloc(lqy_len, lqy, dp_len, dp, &qyd, 64);
		double lpxq_p[64], *lpxq = lpxq_p;
		int    lpxq_len =
		  o.Gen_Product_With_PreAlloc(lpx_len, lpx, dq_len, dq, &lpxq, 64);
		double lpyq_p[64], *lpyq = lpyq_p;
		int    lpyq_len =
		  o.Gen_Product_With_PreAlloc(lpy_len, lpy, dq_len, dq, &lpyq, 64);
		double lx_p[64], *lx = lx_p;
		int    lx_len =
		  o.Gen_Diff_With_PreAlloc(lpxq_len, lpxq, qxd_len, qxd, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int    ly_len =
		  o.Gen_Diff_With_PreAlloc(lpyq_len, lpyq, qyd_len, qyd, &ly, 64);
		double qxr_p[64], *qxr = qxr_p;
		int    qxr_len =
		  o.Gen_Product_With_PreAlloc(lqx_len, lqx, dr_len, dr, &qxr, 64);
		double qyr_p[64], *qyr = qyr_p;
		int    qyr_len =
		  o.Gen_Product_With_PreAlloc(lqy_len, lqy, dr_len, dr, &qyr, 64);
		double lrxq_p[64], *lrxq = lrxq_p;
		int    lrxq_len =
		  o.Gen_Product_With_PreAlloc(lrx_len, lrx, dq_len, dq, &lrxq, 64);
		double lryq_p[64], *lryq = lryq_p;
		int    lryq_len =
		  o.Gen_Product_With_PreAlloc(lry_len, lry, dq_len, dq, &lryq, 64);
		double gx_p[64], *gx = gx_p;
		int    gx_len =
		  o.Gen_Diff_With_PreAlloc(lrxq_len, lrxq, qxr_len, qxr, &gx, 64);
		double gy_p[64], *gy = gy_p;
		int    gy_len =
		  o.Gen_Diff_With_PreAlloc(lryq_len, lryq, qyr_len, qyr, &gy, 64);
		double dx_p[64], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 64);
		double dy_p[64], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 64);
		double d_p[64], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d, 64);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (lryq_p != lryq)
			FreeDoubles(lryq);
		if (lrxq_p != lrxq)
			FreeDoubles(lrxq);
		if (qyr_p != qyr)
			FreeDoubles(qyr);
		if (qxr_p != qxr)
			FreeDoubles(qxr);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (lpyq_p != lpyq)
			FreeDoubles(lpyq);
		if (lpxq_p != lpxq)
			FreeDoubles(lpxq);
		if (qyd_p != qyd)
			FreeDoubles(qyd);
		if (qxd_p != qxd)
			FreeDoubles(qxd);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lrx_p != lrx)
			FreeDoubles(lrx);
		if (lry_p != lry)
			FreeDoubles(lry);
		if (dr_p != dr)
			FreeDoubles(dr);
	}

	if (!GenericPoint2T<IT, ET>::global_cached_values_enabled())
	{
		if (lqx_p != lqx)
			FreeDoubles(lqx);
		if (lqy_p != lqy)
			FreeDoubles(lqy);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign2D_III_exact<IT, ET>(p, r, q);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign2D_III(const GenericPoint2T<IT, ET> &p,
                          const GenericPoint2T<IT, ET> &r,
                          const GenericPoint2T<IT, ET> &q)
{
	Sign ret;
	ret = dotProductSign2D_III_interval<IT, ET>(p, r, q);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign2D_III_expansion<IT, ET>(p, r, q);
}

template <typename IT, typename ET>
Sign dotProductSign3D_EEI_interval(const GenericPoint3T<IT, ET> &q, IT px,
                                   IT py, IT pz, IT rx, IT ry, IT rz)
{
	IT lqx, lqy, lqz, dq;
	if (!q.getIntervalLambda(lqx, lqy, lqz, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pxq = px * dq;
	IT pyq = py * dq;
	IT pzq = pz * dq;
	IT rxq = rx * dq;
	IT ryq = ry * dq;
	IT rzq = rz * dq;
	IT lx  = pxq - lqx;
	IT ly  = pyq - lqy;
	IT lz  = pzq - lqz;
	IT gx  = rxq - lqx;
	IT gy  = ryq - lqy;
	IT gz  = rzq - lqz;
	IT dx  = lx * gx;
	IT dy  = ly * gy;
	IT dz  = lz * gz;
	IT d1  = dx + dy;
	IT d   = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_EEI_exact(const GenericPoint3T<IT, ET> &q, ET px, ET py,
                                ET pz, ET rx, ET ry, ET rz)
{
	ET lqx, lqy, lqz, dq;
	q.getExactLambda(lqx, lqy, lqz, dq);
	ET pxq = px * dq;
	ET pyq = py * dq;
	ET pzq = pz * dq;
	ET rxq = rx * dq;
	ET ryq = ry * dq;
	ET rzq = rz * dq;
	ET lx  = pxq - lqx;
	ET ly  = pyq - lqy;
	ET lz  = pzq - lqz;
	ET gx  = rxq - lqx;
	ET gy  = ryq - lqy;
	ET gz  = rzq - lqz;
	ET dx  = lx * gx;
	ET dy  = ly * gy;
	ET dz  = lz * gz;
	ET d1  = dx + dy;
	ET d   = d1 + dz;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_EEI_expansion(const GenericPoint3T<IT, ET> &q, double px,
                                    double py, double pz, double rx, double ry,
                                    double rz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lqx_p[64], *lqx = lqx_p, lqy_p[64], *lqy = lqy_p, lqz_p[64],
	                  *lqz = lqz_p, dq_p[64], *dq = dq_p;
	int lqx_len = 64, lqy_len = 64, lqz_len = 64, dq_len = 64;
	q.getExpansionLambda(&lqx, lqx_len, &lqy, lqy_len, &lqz, lqz_len, &dq,
	                     dq_len);
	if ((dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          pxq_p[64], *pxq = pxq_p;
		int    pxq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, px, &pxq, 64);
		double pyq_p[64], *pyq = pyq_p;
		int    pyq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, py, &pyq, 64);
		double pzq_p[64], *pzq = pzq_p;
		int    pzq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, pz, &pzq, 64);
		double rxq_p[64], *rxq = rxq_p;
		int    rxq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, rx, &rxq, 64);
		double ryq_p[64], *ryq = ryq_p;
		int    ryq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, ry, &ryq, 64);
		double rzq_p[64], *rzq = rzq_p;
		int    rzq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, rz, &rzq, 64);
		double lx_p[64], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(pxq_len, pxq, lqx_len, lqx, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(pyq_len, pyq, lqy_len, lqy, &ly, 64);
		double lz_p[64], *lz = lz_p;
		int lz_len = o.Gen_Diff_With_PreAlloc(pzq_len, pzq, lqz_len, lqz, &lz, 64);
		double gx_p[64], *gx = gx_p;
		int gx_len = o.Gen_Diff_With_PreAlloc(rxq_len, rxq, lqx_len, lqx, &gx, 64);
		double gy_p[64], *gy = gy_p;
		int gy_len = o.Gen_Diff_With_PreAlloc(ryq_len, ryq, lqy_len, lqy, &gy, 64);
		double gz_p[64], *gz = gz_p;
		int gz_len = o.Gen_Diff_With_PreAlloc(rzq_len, rzq, lqz_len, lqz, &gz, 64);
		double dx_p[64], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 64);
		double dy_p[64], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 64);
		double dz_p[64], *dz = dz_p;
		int dz_len = o.Gen_Product_With_PreAlloc(lz_len, lz, gz_len, gz, &dz, 64);
		double d1_p[64], *d1 = d1_p;
		int    d1_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d1, 64);
		double d_p[64], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(d1_len, d1, dz_len, dz, &d, 64);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (dz_p != dz)
			FreeDoubles(dz);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gz_p != gz)
			FreeDoubles(gz);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (rzq_p != rzq)
			FreeDoubles(rzq);
		if (ryq_p != ryq)
			FreeDoubles(ryq);
		if (rxq_p != rxq)
			FreeDoubles(rxq);
		if (pzq_p != pzq)
			FreeDoubles(pzq);
		if (pyq_p != pyq)
			FreeDoubles(pyq);
		if (pxq_p != pxq)
			FreeDoubles(pxq);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lqx_p != lqx)
			FreeDoubles(lqx);
		if (lqy_p != lqy)
			FreeDoubles(lqy);
		if (lqz_p != lqz)
			FreeDoubles(lqz);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign3D_EEI_exact<IT, ET>(q, px, py, pz, rx, ry, rz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D_EEI(const GenericPoint3T<IT, ET> &q, double px, double py,
                          double pz, double rx, double ry, double rz)
{
	Sign ret;
	ret = dotProductSign3D_EEI_interval<IT, ET>(q, px, py, pz, rx, ry, rz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D_EEI_expansion<IT, ET>(q, px, py, pz, rx, ry, rz);
}

template <typename IT, typename ET>
Sign dotProductSign3D_EEI(const GenericPoint3T<IT, ET> &q,
                          const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r)
{
	return dotProductSign3D_EEI<IT, ET>(q, p.x(), p.y(), p.z(), r.x(), r.y(),
	                                    r.z());
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEE_interval(const GenericPoint3T<IT, ET> &p, IT rx,
                                   IT ry, IT rz, IT qx, IT qy, IT qz)
{
	IT lpx, lpy, lpz, dp;
	if (!p.getIntervalLambda(lpx, lpy, lpz, dp))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT qxd = qx * dp;
	IT qyd = qy * dp;
	IT qzd = qz * dp;
	IT lx  = lpx - qxd;
	IT ly  = lpy - qyd;
	IT lz  = lpz - qzd;
	IT gx  = rx - qx;
	IT gy  = ry - qy;
	IT gz  = rz - qz;
	IT dx  = lx * gx;
	IT dy  = ly * gy;
	IT dz  = lz * gz;
	IT d1  = dx + dy;
	IT d   = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEE_exact(const GenericPoint3T<IT, ET> &p, ET rx, ET ry,
                                ET rz, ET qx, ET qy, ET qz)
{
	ET lpx, lpy, lpz, dp;
	p.getExactLambda(lpx, lpy, lpz, dp);
	ET qxd = qx * dp;
	ET qyd = qy * dp;
	ET qzd = qz * dp;
	ET lx  = lpx - qxd;
	ET ly  = lpy - qyd;
	ET lz  = lpz - qzd;
	ET gx  = rx - qx;
	ET gy  = ry - qy;
	ET gz  = rz - qz;
	ET dx  = lx * gx;
	ET dy  = ly * gy;
	ET dz  = lz * gz;
	ET d1  = dx + dy;
	ET d   = d1 + dz;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEE_expansion(const GenericPoint3T<IT, ET> &p, double rx,
                                    double ry, double rz, double qx, double qy,
                                    double qz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[128], *lpx = lpx_p, lpy_p[128], *lpy = lpy_p, lpz_p[128],
	                   *lpz = lpz_p, dp_p[128], *dp = dp_p;
	int lpx_len = 128, lpy_len = 128, lpz_len = 128, dp_len = 128;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &lpz, lpz_len, &dp,
	                     dp_len);
	if ((dp[dp_len - 1] != 0))
	{
		expansionObject o;
		double          qxd_p[128], *qxd = qxd_p;
		int    qxd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qx, &qxd, 128);
		double qyd_p[128], *qyd = qyd_p;
		int    qyd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qy, &qyd, 128);
		double qzd_p[128], *qzd = qzd_p;
		int    qzd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qz, &qzd, 128);
		double lx_p[128], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(lpx_len, lpx, qxd_len, qxd, &lx, 128);
		double ly_p[128], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(lpy_len, lpy, qyd_len, qyd, &ly, 128);
		double lz_p[128], *lz = lz_p;
		int lz_len = o.Gen_Diff_With_PreAlloc(lpz_len, lpz, qzd_len, qzd, &lz, 128);
		double gx[2];
		o.Two_Diff(rx, qx, gx);
		double gy[2];
		o.Two_Diff(ry, qy, gy);
		double gz[2];
		o.Two_Diff(rz, qz, gz);
		double dx_p[128], *dx = dx_p;
		int    dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, 2, gx, &dx, 128);
		double dy_p[128], *dy = dy_p;
		int    dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, 2, gy, &dy, 128);
		double dz_p[128], *dz = dz_p;
		int    dz_len = o.Gen_Product_With_PreAlloc(lz_len, lz, 2, gz, &dz, 128);
		double d1_p[128], *d1 = d1_p;
		int    d1_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d1, 128);
		double d_p[128], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(d1_len, d1, dz_len, dz, &d, 128);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (dz_p != dz)
			FreeDoubles(dz);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (qzd_p != qzd)
			FreeDoubles(qzd);
		if (qyd_p != qyd)
			FreeDoubles(qyd);
		if (qxd_p != qxd)
			FreeDoubles(qxd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (lpz_p != lpz)
			FreeDoubles(lpz);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign3D_IEE_exact<IT, ET>(p, rx, ry, rz, qx, qy, qz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEE(const GenericPoint3T<IT, ET> &p, double rx, double ry,
                          double rz, double qx, double qy, double qz)
{
	Sign ret;
	ret = dotProductSign3D_IEE_interval<IT, ET>(p, rx, ry, rz, qx, qy, qz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D_IEE_expansion<IT, ET>(p, rx, ry, rz, qx, qy, qz);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r,
                          const GenericPoint3T<IT, ET> &q)
{
	return dotProductSign3D_IEE<IT, ET>(p, r.x(), r.y(), r.z(), q.x(), q.y(),
	                                    q.z());
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEI_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &q, IT rx,
                                   IT ry, IT rz)
{
	IT lpx, lpy, lpz, dp, lqx, lqy, lqz, dq;
	if (!p.getIntervalLambda(lpx, lpy, lpz, dp) ||
	    !q.getIntervalLambda(lqx, lqy, lqz, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dqp  = dq * dp;
	IT pxq  = lpx * dqp;
	IT pyq  = lpy * dqp;
	IT pzq  = lpz * dqp;
	IT rxq  = rx * dq;
	IT ryq  = ry * dq;
	IT rzq  = rz * dq;
	IT lqxd = lqx * dp;
	IT lqyd = lqy * dp;
	IT lqzd = lqz * dp;
	IT lx   = pxq - lqxd;
	IT ly   = pyq - lqyd;
	IT lz   = pzq - lqzd;
	IT gx   = rxq - lqx;
	IT gy   = ryq - lqy;
	IT gz   = rzq - lqz;
	IT dx   = lx * gx;
	IT dy   = ly * gy;
	IT dz   = lz * gz;
	IT d1   = dx + dy;
	IT d    = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEI_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &q, ET rx, ET ry,
                                ET rz)
{
	ET lpx, lpy, lpz, dp, lqx, lqy, lqz, dq;
	p.getExactLambda(lpx, lpy, lpz, dp);
	q.getExactLambda(lqx, lqy, lqz, dq);
	ET dqp  = dq * dp;
	ET pxq  = lpx * dqp;
	ET pyq  = lpy * dqp;
	ET pzq  = lpz * dqp;
	ET rxq  = rx * dq;
	ET ryq  = ry * dq;
	ET rzq  = rz * dq;
	ET lqxd = lqx * dp;
	ET lqyd = lqy * dp;
	ET lqzd = lqz * dp;
	ET lx   = pxq - lqxd;
	ET ly   = pyq - lqyd;
	ET lz   = pzq - lqzd;
	ET gx   = rxq - lqx;
	ET gy   = ryq - lqy;
	ET gz   = rzq - lqz;
	ET dx   = lx * gx;
	ET dy   = ly * gy;
	ET dz   = lz * gz;
	ET d1   = dx + dy;
	ET d    = d1 + dz;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEI_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &q, double rx,
                                    double ry, double rz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[64], *lpx = lpx_p, lpy_p[64], *lpy = lpy_p, lpz_p[64],
	                  *lpz = lpz_p, dp_p[64], *dp = dp_p, lqx_p[64], *lqx = lqx_p,
	                  lqy_p[64], *lqy = lqy_p, lqz_p[64], *lqz = lqz_p, dq_p[64],
	                  *dq = dq_p;
	int lpx_len = 64, lpy_len = 64, lpz_len = 64, dp_len = 64, lqx_len = 64,
	    lqy_len = 64, lqz_len = 64, dq_len = 64;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &lpz, lpz_len, &dp,
	                     dp_len);
	q.getExpansionLambda(&lqx, lqx_len, &lqy, lqy_len, &lqz, lqz_len, &dq,
	                     dq_len);
	if ((dp[dp_len - 1] != 0) && (dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          dqp_p[64], *dqp = dqp_p;
		int dqp_len = o.Gen_Product_With_PreAlloc(dq_len, dq, dp_len, dp, &dqp, 64);
		double pxq_p[64], *pxq = pxq_p;
		int    pxq_len =
		  o.Gen_Product_With_PreAlloc(lpx_len, lpx, dqp_len, dqp, &pxq, 64);
		double pyq_p[64], *pyq = pyq_p;
		int    pyq_len =
		  o.Gen_Product_With_PreAlloc(lpy_len, lpy, dqp_len, dqp, &pyq, 64);
		double pzq_p[64], *pzq = pzq_p;
		int    pzq_len =
		  o.Gen_Product_With_PreAlloc(lpz_len, lpz, dqp_len, dqp, &pzq, 64);
		double rxq_p[64], *rxq = rxq_p;
		int    rxq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, rx, &rxq, 64);
		double ryq_p[64], *ryq = ryq_p;
		int    ryq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, ry, &ryq, 64);
		double rzq_p[64], *rzq = rzq_p;
		int    rzq_len = o.Gen_Scale_With_PreAlloc(dq_len, dq, rz, &rzq, 64);
		double lqxd_p[64], *lqxd = lqxd_p;
		int    lqxd_len =
		  o.Gen_Product_With_PreAlloc(lqx_len, lqx, dp_len, dp, &lqxd, 64);
		double lqyd_p[64], *lqyd = lqyd_p;
		int    lqyd_len =
		  o.Gen_Product_With_PreAlloc(lqy_len, lqy, dp_len, dp, &lqyd, 64);
		double lqzd_p[64], *lqzd = lqzd_p;
		int    lqzd_len =
		  o.Gen_Product_With_PreAlloc(lqz_len, lqz, dp_len, dp, &lqzd, 64);
		double lx_p[64], *lx = lx_p;
		int    lx_len =
		  o.Gen_Diff_With_PreAlloc(pxq_len, pxq, lqxd_len, lqxd, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int    ly_len =
		  o.Gen_Diff_With_PreAlloc(pyq_len, pyq, lqyd_len, lqyd, &ly, 64);
		double lz_p[64], *lz = lz_p;
		int    lz_len =
		  o.Gen_Diff_With_PreAlloc(pzq_len, pzq, lqzd_len, lqzd, &lz, 64);
		double gx_p[64], *gx = gx_p;
		int gx_len = o.Gen_Diff_With_PreAlloc(rxq_len, rxq, lqx_len, lqx, &gx, 64);
		double gy_p[64], *gy = gy_p;
		int gy_len = o.Gen_Diff_With_PreAlloc(ryq_len, ryq, lqy_len, lqy, &gy, 64);
		double gz_p[64], *gz = gz_p;
		int gz_len = o.Gen_Diff_With_PreAlloc(rzq_len, rzq, lqz_len, lqz, &gz, 64);
		double dx_p[64], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 64);
		double dy_p[64], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 64);
		double dz_p[64], *dz = dz_p;
		int dz_len = o.Gen_Product_With_PreAlloc(lz_len, lz, gz_len, gz, &dz, 64);
		double d1_p[64], *d1 = d1_p;
		int    d1_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d1, 64);
		double d_p[64], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(d1_len, d1, dz_len, dz, &d, 64);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (dz_p != dz)
			FreeDoubles(dz);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gz_p != gz)
			FreeDoubles(gz);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (lqzd_p != lqzd)
			FreeDoubles(lqzd);
		if (lqyd_p != lqyd)
			FreeDoubles(lqyd);
		if (lqxd_p != lqxd)
			FreeDoubles(lqxd);
		if (rzq_p != rzq)
			FreeDoubles(rzq);
		if (ryq_p != ryq)
			FreeDoubles(ryq);
		if (rxq_p != rxq)
			FreeDoubles(rxq);
		if (pzq_p != pzq)
			FreeDoubles(pzq);
		if (pyq_p != pyq)
			FreeDoubles(pyq);
		if (pxq_p != pxq)
			FreeDoubles(pxq);
		if (dqp_p != dqp)
			FreeDoubles(dqp);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (lpz_p != lpz)
			FreeDoubles(lpz);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lqx_p != lqx)
			FreeDoubles(lqx);
		if (lqy_p != lqy)
			FreeDoubles(lqy);
		if (lqz_p != lqz)
			FreeDoubles(lqz);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign3D_IEI_exact<IT, ET>(p, q, rx, ry, rz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEI(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q, double rx, double ry,
                          double rz)
{
	Sign ret;
	ret = dotProductSign3D_IEI_interval<IT, ET>(p, q, rx, ry, rz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D_IEI_expansion<IT, ET>(p, q, rx, ry, rz);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IEI(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &q,
                          const GenericPoint3T<IT, ET> &r)
{
	return dotProductSign3D_IEI<IT, ET>(p, q, r.x(), r.y(), r.z());
}

template <typename IT, typename ET>
Sign dotProductSign3D_IIE_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &r, IT qx,
                                   IT qy, IT qz)
{
	IT lpx, lpy, lpz, dp, lrx, lry, lrz, dr;
	if (!p.getIntervalLambda(lpx, lpy, lpz, dp) ||
	    !r.getIntervalLambda(lrx, lry, lrz, dr))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT qxd = qx * dp;
	IT qyd = qy * dp;
	IT qzd = qz * dp;
	IT lx  = lpx - qxd;
	IT ly  = lpy - qyd;
	IT lz  = lpz - qzd;
	IT qxr = qx * dr;
	IT qyr = qy * dr;
	IT qzr = qz * dr;
	IT gx  = lrx - qxr;
	IT gy  = lry - qyr;
	IT gz  = lrz - qzr;
	IT dx  = lx * gx;
	IT dy  = ly * gy;
	IT dz  = lz * gz;
	IT d1  = dx + dy;
	IT d   = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IIE_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &r, ET qx, ET qy,
                                ET qz)
{
	ET lpx, lpy, lpz, dp, lrx, lry, lrz, dr;
	p.getExactLambda(lpx, lpy, lpz, dp);
	r.getExactLambda(lrx, lry, lrz, dr);
	ET qxd = qx * dp;
	ET qyd = qy * dp;
	ET qzd = qz * dp;
	ET lx  = lpx - qxd;
	ET ly  = lpy - qyd;
	ET lz  = lpz - qzd;
	ET qxr = qx * dr;
	ET qyr = qy * dr;
	ET qzr = qz * dr;
	ET gx  = lrx - qxr;
	ET gy  = lry - qyr;
	ET gz  = lrz - qzr;
	ET dx  = lx * gx;
	ET dy  = ly * gy;
	ET dz  = lz * gz;
	ET d1  = dx + dy;
	ET d   = d1 + dz;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IIE_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &r, double qx,
                                    double qy, double qz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[64], *lpx = lpx_p, lpy_p[64], *lpy = lpy_p, lpz_p[64],
	                  *lpz = lpz_p, dp_p[64], *dp = dp_p, lrx_p[64], *lrx = lrx_p,
	                  lry_p[64], *lry = lry_p, lrz_p[64], *lrz = lrz_p, dr_p[64],
	                  *dr = dr_p;
	int lpx_len = 64, lpy_len = 64, lpz_len = 64, dp_len = 64, lrx_len = 64,
	    lry_len = 64, lrz_len = 64, dr_len = 64;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &lpz, lpz_len, &dp,
	                     dp_len);
	r.getExpansionLambda(&lrx, lrx_len, &lry, lry_len, &lrz, lrz_len, &dr,
	                     dr_len);
	if ((dp[dp_len - 1] != 0) && (dr[dr_len - 1] != 0))
	{
		expansionObject o;
		double          qxd_p[64], *qxd = qxd_p;
		int    qxd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qx, &qxd, 64);
		double qyd_p[64], *qyd = qyd_p;
		int    qyd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qy, &qyd, 64);
		double qzd_p[64], *qzd = qzd_p;
		int    qzd_len = o.Gen_Scale_With_PreAlloc(dp_len, dp, qz, &qzd, 64);
		double lx_p[64], *lx = lx_p;
		int lx_len = o.Gen_Diff_With_PreAlloc(lpx_len, lpx, qxd_len, qxd, &lx, 64);
		double ly_p[64], *ly = ly_p;
		int ly_len = o.Gen_Diff_With_PreAlloc(lpy_len, lpy, qyd_len, qyd, &ly, 64);
		double lz_p[64], *lz = lz_p;
		int lz_len = o.Gen_Diff_With_PreAlloc(lpz_len, lpz, qzd_len, qzd, &lz, 64);
		double qxr_p[64], *qxr = qxr_p;
		int    qxr_len = o.Gen_Scale_With_PreAlloc(dr_len, dr, qx, &qxr, 64);
		double qyr_p[64], *qyr = qyr_p;
		int    qyr_len = o.Gen_Scale_With_PreAlloc(dr_len, dr, qy, &qyr, 64);
		double qzr_p[64], *qzr = qzr_p;
		int    qzr_len = o.Gen_Scale_With_PreAlloc(dr_len, dr, qz, &qzr, 64);
		double gx_p[64], *gx = gx_p;
		int gx_len = o.Gen_Diff_With_PreAlloc(lrx_len, lrx, qxr_len, qxr, &gx, 64);
		double gy_p[64], *gy = gy_p;
		int gy_len = o.Gen_Diff_With_PreAlloc(lry_len, lry, qyr_len, qyr, &gy, 64);
		double gz_p[64], *gz = gz_p;
		int gz_len = o.Gen_Diff_With_PreAlloc(lrz_len, lrz, qzr_len, qzr, &gz, 64);
		double dx_p[64], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 64);
		double dy_p[64], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 64);
		double dz_p[64], *dz = dz_p;
		int dz_len = o.Gen_Product_With_PreAlloc(lz_len, lz, gz_len, gz, &dz, 64);
		double d1_p[64], *d1 = d1_p;
		int    d1_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d1, 64);
		double d_p[64], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(d1_len, d1, dz_len, dz, &d, 64);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (dz_p != dz)
			FreeDoubles(dz);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gz_p != gz)
			FreeDoubles(gz);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (qzr_p != qzr)
			FreeDoubles(qzr);
		if (qyr_p != qyr)
			FreeDoubles(qyr);
		if (qxr_p != qxr)
			FreeDoubles(qxr);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (qzd_p != qzd)
			FreeDoubles(qzd);
		if (qyd_p != qyd)
			FreeDoubles(qyd);
		if (qxd_p != qxd)
			FreeDoubles(qxd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (lpz_p != lpz)
			FreeDoubles(lpz);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lrx_p != lrx)
			FreeDoubles(lrx);
		if (lry_p != lry)
			FreeDoubles(lry);
		if (lrz_p != lrz)
			FreeDoubles(lrz);
		if (dr_p != dr)
			FreeDoubles(dr);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign3D_IIE_exact<IT, ET>(p, r, qx, qy, qz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D_IIE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r, double qx, double qy,
                          double qz)
{
	Sign ret;
	ret = dotProductSign3D_IIE_interval<IT, ET>(p, r, qx, qy, qz);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D_IIE_expansion<IT, ET>(p, r, qx, qy, qz);
}

template <typename IT, typename ET>
Sign dotProductSign3D_IIE(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r,
                          const GenericPoint3T<IT, ET> &q)
{
	return dotProductSign3D_IIE<IT, ET>(p, r, q.x(), q.y(), q.z());
}

template <typename IT, typename ET>
Sign dotProductSign3D_III_interval(const GenericPoint3T<IT, ET> &p,
                                   const GenericPoint3T<IT, ET> &r,
                                   const GenericPoint3T<IT, ET> &q)
{
	IT lpx, lpy, lpz, dp, lrx, lry, lrz, dr, lqx, lqy, lqz, dq;
	if (!p.getIntervalLambda(lpx, lpy, lpz, dp) ||
	    !r.getIntervalLambda(lrx, lry, lrz, dr) ||
	    !q.getIntervalLambda(lqx, lqy, lqz, dq))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT qxd  = lqx * dp;
	IT qyd  = lqy * dp;
	IT qzd  = lqz * dp;
	IT lpxq = lpx * dq;
	IT lpyq = lpy * dq;
	IT lpzq = lpz * dq;
	IT lx   = lpxq - qxd;
	IT ly   = lpyq - qyd;
	IT lz   = lpzq - qzd;
	IT qxr  = lqx * dr;
	IT qyr  = lqy * dr;
	IT qzr  = lqz * dr;
	IT lrxq = lrx * dq;
	IT lryq = lry * dq;
	IT lrzq = lrz * dq;
	IT gx   = lrxq - qxr;
	IT gy   = lryq - qyr;
	IT gz   = lrzq - qzr;
	IT dx   = lx * gx;
	IT dy   = ly * gy;
	IT dz   = lz * gz;
	IT d1   = dx + dy;
	IT d    = d1 + dz;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_III_exact(const GenericPoint3T<IT, ET> &p,
                                const GenericPoint3T<IT, ET> &r,
                                const GenericPoint3T<IT, ET> &q)
{
	ET lpx, lpy, lpz, dp, lrx, lry, lrz, dr, lqx, lqy, lqz, dq;
	p.getExactLambda(lpx, lpy, lpz, dp);
	r.getExactLambda(lrx, lry, lrz, dr);
	q.getExactLambda(lqx, lqy, lqz, dq);
	ET qxd  = lqx * dp;
	ET qyd  = lqy * dp;
	ET qzd  = lqz * dp;
	ET lpxq = lpx * dq;
	ET lpyq = lpy * dq;
	ET lpzq = lpz * dq;
	ET lx   = lpxq - qxd;
	ET ly   = lpyq - qyd;
	ET lz   = lpzq - qzd;
	ET qxr  = lqx * dr;
	ET qyr  = lqy * dr;
	ET qzr  = lqz * dr;
	ET lrxq = lrx * dq;
	ET lryq = lry * dq;
	ET lrzq = lrz * dq;
	ET gx   = lrxq - qxr;
	ET gy   = lryq - qyr;
	ET gz   = lrzq - qzr;
	ET dx   = lx * gx;
	ET dy   = ly * gy;
	ET dz   = lz * gz;
	ET d1   = dx + dy;
	ET d    = d1 + dz;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign dotProductSign3D_III_expansion(const GenericPoint3T<IT, ET> &p,
                                    const GenericPoint3T<IT, ET> &r,
                                    const GenericPoint3T<IT, ET> &q)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lpx_p[32], *lpx = lpx_p, lpy_p[32], *lpy = lpy_p, lpz_p[32],
	                  *lpz = lpz_p, dp_p[32], *dp = dp_p, lrx_p[32], *lrx = lrx_p,
	                  lry_p[32], *lry = lry_p, lrz_p[32], *lrz = lrz_p, dr_p[32],
	                  *dr = dr_p, lqx_p[32], *lqx = lqx_p, lqy_p[32],
	                  *lqy = lqy_p, lqz_p[32], *lqz = lqz_p, dq_p[32], *dq = dq_p;
	int lpx_len = 32, lpy_len = 32, lpz_len = 32, dp_len = 32, lrx_len = 32,
	    lry_len = 32, lrz_len = 32, dr_len = 32, lqx_len = 32, lqy_len = 32,
	    lqz_len = 32, dq_len = 32;
	p.getExpansionLambda(&lpx, lpx_len, &lpy, lpy_len, &lpz, lpz_len, &dp,
	                     dp_len);
	r.getExpansionLambda(&lrx, lrx_len, &lry, lry_len, &lrz, lrz_len, &dr,
	                     dr_len);
	q.getExpansionLambda(&lqx, lqx_len, &lqy, lqy_len, &lqz, lqz_len, &dq,
	                     dq_len);
	if ((dp[dp_len - 1] != 0) && (dr[dr_len - 1] != 0) && (dq[dq_len - 1] != 0))
	{
		expansionObject o;
		double          qxd_p[32], *qxd = qxd_p;
		int             qxd_len =
		  o.Gen_Product_With_PreAlloc(lqx_len, lqx, dp_len, dp, &qxd, 32);
		double qyd_p[32], *qyd = qyd_p;
		int    qyd_len =
		  o.Gen_Product_With_PreAlloc(lqy_len, lqy, dp_len, dp, &qyd, 32);
		double qzd_p[32], *qzd = qzd_p;
		int    qzd_len =
		  o.Gen_Product_With_PreAlloc(lqz_len, lqz, dp_len, dp, &qzd, 32);
		double lpxq_p[32], *lpxq = lpxq_p;
		int    lpxq_len =
		  o.Gen_Product_With_PreAlloc(lpx_len, lpx, dq_len, dq, &lpxq, 32);
		double lpyq_p[32], *lpyq = lpyq_p;
		int    lpyq_len =
		  o.Gen_Product_With_PreAlloc(lpy_len, lpy, dq_len, dq, &lpyq, 32);
		double lpzq_p[32], *lpzq = lpzq_p;
		int    lpzq_len =
		  o.Gen_Product_With_PreAlloc(lpz_len, lpz, dq_len, dq, &lpzq, 32);
		double lx_p[32], *lx = lx_p;
		int    lx_len =
		  o.Gen_Diff_With_PreAlloc(lpxq_len, lpxq, qxd_len, qxd, &lx, 32);
		double ly_p[32], *ly = ly_p;
		int    ly_len =
		  o.Gen_Diff_With_PreAlloc(lpyq_len, lpyq, qyd_len, qyd, &ly, 32);
		double lz_p[32], *lz = lz_p;
		int    lz_len =
		  o.Gen_Diff_With_PreAlloc(lpzq_len, lpzq, qzd_len, qzd, &lz, 32);
		double qxr_p[32], *qxr = qxr_p;
		int    qxr_len =
		  o.Gen_Product_With_PreAlloc(lqx_len, lqx, dr_len, dr, &qxr, 32);
		double qyr_p[32], *qyr = qyr_p;
		int    qyr_len =
		  o.Gen_Product_With_PreAlloc(lqy_len, lqy, dr_len, dr, &qyr, 32);
		double qzr_p[32], *qzr = qzr_p;
		int    qzr_len =
		  o.Gen_Product_With_PreAlloc(lqz_len, lqz, dr_len, dr, &qzr, 32);
		double lrxq_p[32], *lrxq = lrxq_p;
		int    lrxq_len =
		  o.Gen_Product_With_PreAlloc(lrx_len, lrx, dq_len, dq, &lrxq, 32);
		double lryq_p[32], *lryq = lryq_p;
		int    lryq_len =
		  o.Gen_Product_With_PreAlloc(lry_len, lry, dq_len, dq, &lryq, 32);
		double lrzq_p[32], *lrzq = lrzq_p;
		int    lrzq_len =
		  o.Gen_Product_With_PreAlloc(lrz_len, lrz, dq_len, dq, &lrzq, 32);
		double gx_p[32], *gx = gx_p;
		int    gx_len =
		  o.Gen_Diff_With_PreAlloc(lrxq_len, lrxq, qxr_len, qxr, &gx, 32);
		double gy_p[32], *gy = gy_p;
		int    gy_len =
		  o.Gen_Diff_With_PreAlloc(lryq_len, lryq, qyr_len, qyr, &gy, 32);
		double gz_p[32], *gz = gz_p;
		int    gz_len =
		  o.Gen_Diff_With_PreAlloc(lrzq_len, lrzq, qzr_len, qzr, &gz, 32);
		double dx_p[32], *dx = dx_p;
		int dx_len = o.Gen_Product_With_PreAlloc(lx_len, lx, gx_len, gx, &dx, 32);
		double dy_p[32], *dy = dy_p;
		int dy_len = o.Gen_Product_With_PreAlloc(ly_len, ly, gy_len, gy, &dy, 32);
		double dz_p[32], *dz = dz_p;
		int dz_len = o.Gen_Product_With_PreAlloc(lz_len, lz, gz_len, gz, &dz, 32);
		double d1_p[32], *d1 = d1_p;
		int    d1_len = o.Gen_Sum_With_PreAlloc(dx_len, dx, dy_len, dy, &d1, 32);
		double d_p[32], *d = d_p;
		int    d_len = o.Gen_Sum_With_PreAlloc(d1_len, d1, dz_len, dz, &d, 32);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (dz_p != dz)
			FreeDoubles(dz);
		if (dy_p != dy)
			FreeDoubles(dy);
		if (dx_p != dx)
			FreeDoubles(dx);
		if (gz_p != gz)
			FreeDoubles(gz);
		if (gy_p != gy)
			FreeDoubles(gy);
		if (gx_p != gx)
			FreeDoubles(gx);
		if (lrzq_p != lrzq)
			FreeDoubles(lrzq);
		if (lryq_p != lryq)
			FreeDoubles(lryq);
		if (lrxq_p != lrxq)
			FreeDoubles(lrxq);
		if (qzr_p != qzr)
			FreeDoubles(qzr);
		if (qyr_p != qyr)
			FreeDoubles(qyr);
		if (qxr_p != qxr)
			FreeDoubles(qxr);
		if (lz_p != lz)
			FreeDoubles(lz);
		if (ly_p != ly)
			FreeDoubles(ly);
		if (lx_p != lx)
			FreeDoubles(lx);
		if (lpzq_p != lpzq)
			FreeDoubles(lpzq);
		if (lpyq_p != lpyq)
			FreeDoubles(lpyq);
		if (lpxq_p != lpxq)
			FreeDoubles(lpxq);
		if (qzd_p != qzd)
			FreeDoubles(qzd);
		if (qyd_p != qyd)
			FreeDoubles(qyd);
		if (qxd_p != qxd)
			FreeDoubles(qxd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lpx_p != lpx)
			FreeDoubles(lpx);
		if (lpy_p != lpy)
			FreeDoubles(lpy);
		if (lpz_p != lpz)
			FreeDoubles(lpz);
		if (dp_p != dp)
			FreeDoubles(dp);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lrx_p != lrx)
			FreeDoubles(lrx);
		if (lry_p != lry)
			FreeDoubles(lry);
		if (lrz_p != lrz)
			FreeDoubles(lrz);
		if (dr_p != dr)
			FreeDoubles(dr);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lqx_p != lqx)
			FreeDoubles(lqx);
		if (lqy_p != lqy)
			FreeDoubles(lqy);
		if (lqz_p != lqz)
			FreeDoubles(lqz);
		if (dq_p != dq)
			FreeDoubles(dq);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return dotProductSign3D_III_exact<IT, ET>(p, r, q);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign dotProductSign3D_III(const GenericPoint3T<IT, ET> &p,
                          const GenericPoint3T<IT, ET> &r,
                          const GenericPoint3T<IT, ET> &q)
{
	Sign ret;
	ret = dotProductSign3D_III_interval<IT, ET>(p, r, q);
	if (is_sign_reliable(ret))
		return ret;
	return dotProductSign3D_III_expansion<IT, ET>(p, r, q);
}
} // namespace OMC