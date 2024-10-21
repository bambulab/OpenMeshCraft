#pragma once

#ifndef OMC_NO_SHEWCHUK
extern "C"
{
	double orient2d(const double *pa, const double *pb, const double *pc);

	// In this orient3d from shewchuk, generally, pb, pc and pd come from three
	// vertices of a triangle. However, in all orient3d from OpenMeshCraft, the
	// first three points come from three vertices of a triangle.
	double orient3d(const double *pa, const double *pb, const double *pc,
	                const double *pd);

	void orient3d_get_minors(const double *pb, const double *pc, const double *pd,
	                         double *minor, double *perm);

	double orient3d_with_cached_minors(const double *pa, const double *pb,
	                                   const double *pc, const double *pd,
	                                   double *minor, double *perm);

	double incircle(const double *pa, const double *pb, const double *pc,
	                const double *pd);

	double insphere(const double *pa, const double *pb, const double *pc,
	                const double *pd, const double *pe);
}
#endif