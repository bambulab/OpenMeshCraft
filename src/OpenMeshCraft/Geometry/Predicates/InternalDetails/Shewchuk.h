#pragma once

#ifndef OMC_NO_SHEWCHUK
extern "C"
{
	// The shewchuk's sign is same with ours.
	double orient2d(const double *pa, const double *pb, const double *pc);

	// This orient3d from shewchuk calculates the determinant:
	// 		det(a', b', c', d'),
	// where a' = (a, 1), so as b', c', d'.
	//
	// However, all orient3d from OpenMeshCraft calculates the determinant:
	//   -det(a', b', c', d').
	// So, the result of this function should be negated.
	double orient3d(const double *pa, const double *pb, const double *pc,
	                const double *pd);

	// This orient3d sees `b`, `c` and `d` as a triangle, and `a` as a point.
	// It calculates and caches the sub-determinant related to the triangle.
	void orient3d_get_minors(const double *pb, const double *pc, const double *pd,
	                         double *minor, double *perm);

	// This orient3d uses cached minors to calculate the whole determinant.
	double orient3d_with_cached_minors(const double *pa, const double *pb,
	                                   const double *pc, const double *pd,
	                                   double *minor, double *perm);

	// `a`, `b` and `c` form a circle, and `d` is a query point.
	// POSITIVE->inside, ZERO->on, NEGATIVE->outside.
	double incircle(const double *pa, const double *pb, const double *pc,
	                const double *pd);

	// `a`, `b`, `c` and `d` form a sphere, and `e` is a query point.
	// POSITIVE->inside, ZERO->on, NEGATIVE->outside.
	double insphere(const double *pa, const double *pb, const double *pc,
	                const double *pd, const double *pe);
}
#endif