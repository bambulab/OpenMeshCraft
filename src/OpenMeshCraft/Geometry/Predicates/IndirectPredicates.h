#pragma once

#include "OpenMeshCraft/Geometry/Primitives/GenericPoint2T.h"
#include "OpenMeshCraft/Geometry/Primitives/GenericPoint3T.h"

#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#include <tuple>

namespace OMC {

#define TEMPLATE_DECL template <typename FT, typename IT, typename ET>

/******************************************************************************/
/* Dot Product ****************************************************************/
/******************************************************************************/

/**
 * @brief Sign of dot product value of 2D points.
 */
TEMPLATE_DECL
class DotProductSign2D_Indirect
{
public:
	using VecT   = Vec2T<FT>;
	using PointT = GenericPoint2T<IT, ET>;

public:
	/**
	 * @brief Dot product between 2D vectors formed by three points `p`, `r`, `q`.
	 * Two vectors have a common point `q`.
	 * @return sign of (p-q).dot(r-q)
	 */
	Sign operator()(const PointT &p, const PointT &r, const PointT &q);

	/**
	 * @brief Dot product between 2D vectors formed by four points. Each vector is
	 * formed by two points. One starts from `p` and ends at `q`, the other starts
	 * from `r` and ends at `s`.
	 * @return sign of (p-q).dot(r-s)
	 */
	Sign operator()(const PointT &p, const PointT &r, const PointT &q,
	                const PointT &s);
};

/**
 * @brief Sign of dot product value of 3D points.
 */
TEMPLATE_DECL
class DotProductSign3D_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/**
	 * @brief Dot product between 3D vectors formed by three points `p`, `r`, `q`.
	 * Two vectors have a common point `q`.
	 * @return sign of (p-q).dot(r-q)
	 */
	Sign operator()(const PointT &p, const PointT &r, const PointT &q);

	/**
	 * @brief Dot product between 2D vectors formed by four points. Each vector is
	 * formed by two points. One starts from `p` and ends at `q`, the other starts
	 * from `r` and ends at `s`.
	 * @return sign of (p-q).dot(r-s)
	 */
	Sign operator()(const PointT &p, const PointT &r, const PointT &q,
	                const PointT &s);
};

/**
 * @brief Dot product of 3D points on 2D orthogonal planes.
 * Similar to `DotProductSign2D/3D`, see details in the corresponding classes.
 */
TEMPLATE_DECL
class DotProductSignOn2D_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/// @brief Dot product between 3D vectors on xy.
	/// @return sign of (p-q).dot(r-q)
	Sign on_xy(const PointT &p, const PointT &r, const PointT &q);

	/// @brief Dot product between 3D vectors on xy.
	/// @return sign of (p-q).dot(r-s)
	Sign on_xy(const PointT &p, const PointT &r, const PointT &q,
	           const PointT &s);

	/// @brief Dot product between 3D vectors on yz.
	/// @return sign of (p-q).dot(r-q)
	Sign on_yz(const PointT &p, const PointT &r, const PointT &q);

	/// @brief Dot product between 3D vectors on yz.
	/// @return sign of (p-q).dot(r-s)
	Sign on_yz(const PointT &p, const PointT &r, const PointT &q,
	           const PointT &s);

	/// @brief Dot product between 3D vectors on zx.
	/// @return sign of (p-q).dot(r-q)
	Sign on_zx(const PointT &p, const PointT &r, const PointT &q);

	/// @brief Dot product between 3D vectors on zx.
	/// @return sign of (p-q).dot(r-s)
	Sign on_zx(const PointT &p, const PointT &r, const PointT &q,
	           const PointT &s);
};

/******************************************************************************/
/* Distance *******************************************************************/
/******************************************************************************/

/**
 * @brief Compare Square distance of two 2D points with given distances.
 */
TEMPLATE_DECL
class SquareDistance2D_Indirect
{
public:
	using VecT   = Vec2T<FT>;
	using PointT = GenericPoint2T<IT, ET>;

public:
	/**
	 * @brief Calculate the square distance between `p` and `q`, then compare with
	 * `sqr_dis`.
	 * @retval NEGATIVE, calculated square distance is less than `sqr_dis`.
	 * @retval ZERO, calculated square distance is equal to `sqr_dis`.
	 * @retval POSITIVE, calculated square distance is larger than `sqr_dis`.
	 */
	Sign operator()(const PointT &p, const PointT &q, FT sqr_dis);
};

/**
 * @brief Compare Square distance of two 3D points with given distances.
 */
TEMPLATE_DECL
class SquareDistance3D_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/**
	 * @brief Calculate the square distance between `p` and `q`, then compare with
	 * `sqr_dis`.
	 * @retval NEGATIVE, calculated square distance is less than `sqr_dis`.
	 * @retval ZERO, calculated square distance is equal to `sqr_dis`.
	 * @retval POSITIVE, calculated square distance is larger than `sqr_dis`.
	 */
	Sign operator()(const PointT &p, const PointT &q, FT sqr_dis);
};

/******************************************************************************/
/* Orientation ****************************************************************/
/******************************************************************************/

/**
 * @brief Orient2D: Orientation of three 2D points.
 * @details Given three points a, b, c, let ab = b-a, ac = c-a.
 *
 * The orientation is the determinant of the matrix formed by ab and ac.
 * The determinant can also be calculated as:
 *     det = cross(ab, ac).
 *
 * The sign of the determinant indicates the orientation, we describe the
 * orientation as the volume of the triangle formed by three points:
 * - ZERO -> three points are collinear;
 * - POSITIVE -> the triangle formed by three points has positive volume;
 * - NEGATIVE -> the triangle formed by three points has negative volume.
 *
 * In general, a and b usually come from a segment/line, and c is the query
 * point, we expect to know the relative position of c with respect to the
 * segment/line.
 */
TEMPLATE_DECL
class Orient2D_Indirect
{
public:
	using VecT   = Vec2T<FT>;
	using PointT = GenericPoint2T<IT, ET>;

public:
	/**
	 * @brief test orientation of query with respect to 2D line pq.
	 * It calculates the cross product of two vectors (q-p) and (query-p):
	 * (q-p) cross (query - p).
	 * @param p_q_query Given in generic points.
	 * @return POSITIVE->left, ZERO->on, NEGATIVE->right.
	 */
	Sign operator()(const PointT &p, const PointT &q, const PointT &query);

	/**
	 * @brief test orientation of query with respect to 2D line pq.
	 * It calculates the cross product of two vectors (q-p) and (query-p):
	 * (q-p) cross (query - p).
	 * @param p_q_query Given in number pointers.
	 * @return POSITIVE->left, ZERO->on, NEGATIVE->right.
	 */
	Sign operator()(const FT *p, const FT *q, const FT *query);
};

/**
 * @brief Orient3D: orientation of four 3D points.
 * @details Given four points a, b, c, d, let ab = b-a, ac = c-a, ad = d-a.
 *
 * The orientation is the determinant of the matrix formed by ab, ac, ad.
 * The determinant can also be calculated as:
 *     det = dot(cross(ab, ac), ad).
 *
 * The sign of the determinant indicates the orientation, we describe the
 * orientation as the volume of the tetrahedron formed by four points:
 * - ZERO -> four points are coplanar;
 * - POSITIVE -> the tetrahedron formed by four points has positive volume;
 * - NEGATIVE -> the tetrahedron formed by four points has negative volume.
 *
 * In general, a, b and c usually come from a triangle, and d is the query
 * point, we expect to know the relative position of d with respect to the
 * triangle.
 */
TEMPLATE_DECL
class Orient3D_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/**
	 * @brief Given four points a, b, c, d, let ab = b-a, ac = c-a, ad = d-a.
	 * Calculate the determinant: det = dot(cross(ab,ac), ad).
	 * @param points Given in generic points.
	 * @return
	 * ZERO->coplanar, POSITIVE->positive volume, NEGATIVE->negtive volume.
	 */
	Sign operator()(const PointT &a, const PointT &b, const PointT &c,
	                const PointT &d);

	/**
	 * @brief Given four points a, b, c, d, let ab = b-a, ac = c-a, ad = d-a.
	 * Calculate the determinant: det = dot(cross(ab,ac), ad).
	 * @param points Given in number pointers.
	 * @return
	 * ZERO->coplanar, POSITIVE->positive volume, NEGATIVE->negtive volume.
	 */
	Sign operator()(const FT *a, const FT *b, const FT *c, const FT *d);

	/**
	 * @brief Given four points a, b, c, d, let ab = b-a, ac = c-a, ad = d-a.
	 * Calculate the determinant: det = dot(cross(ab,ac), ad).
	 * @param a_b_c Given in number pointers.
	 * @param d Given in generic point.
	 * @return
	 * ZERO->coplanar, POSITIVE->positive volume, NEGATIVE->negtive volume.
	 */
	Sign operator()(const FT *a, const FT *b, const FT *c, const PointT &d);

public: /* Cached version of orient3d ***************************************/
	/**
	 * @brief Calculate cached data for three points pa, pb and pc (which
	 * generally come from three points of a triangle)
	 */
	static void get_minors(const FT *pa, const FT *pb, const FT *pc, FT *minor,
	                       FT *perm);

	/**
	 * @brief Calculate orient3d with cached data. Be careful to put points
	 * in right order!
	 * Cached data are calculated for pa, pb and pc. The query point is pd.
	 */
	static Sign with_cached_minors(const FT *pa, const FT *pb, const FT *pc,
	                               const FT *pd, const FT *minor, const FT *perm);

public: /* Separated stages of adaptive precision strategy ******************/
	/**
	 * @brief Calculates the floating-point filter stage of adaptive precision
	 * strategy.
	 * @return UNCERTAIN->need further exact test,
	 * CERTAIN POSITIVE->positive volume, CERTAIN NEGATIVE->negtive volume.
	 */
	Sign filter(const FT *a, const FT *b, const FT *c, const FT *d);
};

/**
 * @brief Check 3D points' orientation on 2D orthogonal planes.
 * The 2D orthogonal planes include `xy`, `yz` and `zx` planes.
 */
TEMPLATE_DECL
class OrientOn2D_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

	using OrientOn2D = OrientOn2D_Indirect<FT, IT, ET>;

public:
	/**
	 * @brief Calculate the orientation of points on orthogonal plane indicated by
	 * `n_max`.
	 * @param n_max the dominant normal component of the triangle/plane (see
	 * maxComponentInTriangleNormal).
	 * @return Sign Same to Orient2D.
	 */
	Sign operator()(const PointT &a, const PointT &b, const PointT &c, int n_max);

	/*  Orient2D on xy/yz/zx plane. */

	Sign on_xy(const PointT &a, const PointT &b, const PointT &c);
	Sign on_yz(const PointT &a, const PointT &b, const PointT &c);
	Sign on_zx(const PointT &a, const PointT &b, const PointT &c);

	/* Same functions with only different parameter types */

	Sign operator()(const FT *a, const FT *b, const FT *c, int n_max);

	Sign operator()(const FT *a, const FT *b, const PointT &c, int n_max);

	Sign on_xy(const FT *a, const FT *b, const FT *c);
	Sign on_yz(const FT *a, const FT *b, const FT *c);
	Sign on_zx(const FT *a, const FT *b, const FT *c);
};

/******************************************************************************/
/* Less Than ******************************************************************/
/******************************************************************************/

/**
 * @brief Compare coordinate of 2D points.
 * @todo Implement this.
 */
TEMPLATE_DECL
class LessThan2D_Indirect
{
public:
	using VecT   = Vec2T<FT>;
	using PointT = GenericPoint2T<IT, ET>;

public:
	/**
	 * @brief Compare x/y-coordinate of two 2D points `a` and `b`.
	 * @return NEGATIVE -> a<b, ZERO -> a==b, POSITIVE -> a > b.
	 */
	Sign on_x(const PointT &a, const PointT &b);
	Sign on_y(const PointT &a, const PointT &b);

	/**
	 * @brief Lexicographically compare x/y-coordinate of two 2D points `a` and
	 * `b`.
	 * @return NEGATIVE -> a<b, ZERO -> a==b, POSITIVE -> a > b.
	 */
	Sign operator()(const PointT &a, const PointT &b);

	/**
	 * @brief Check if the two points are coincident by lexicographically
	 * comparing their coordinates.
	 */
	bool coincident(const PointT &a, const PointT &b)
	{
		return operator()(a, b) == Sign::ZERO;
	}
};

TEMPLATE_DECL
class LessThan3D_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/**
	 * @brief Compare x/y-coordinate of two 2D points `a` and `b`.
	 * @return NEGATIVE -> a<b, ZERO -> a==b, POSITIVE -> a>b.
	 */
	Sign on_x(const PointT &a, const PointT &b);
	Sign on_y(const PointT &a, const PointT &b);
	Sign on_z(const PointT &a, const PointT &b);

	/**
	 * @brief Compare `axis`-coordinate of two 2D points `a` and `b`.
	 * @param axis 0/1/2 indicates the axis x/y/z.
	 * @return NEGATIVE -> a<b, ZERO -> a==b, POSITIVE -> a>b.
	 */
	Sign on(const PointT &a, const PointT &b, size_t axis);

	/**
	 * @brief Compare coordinate of two 2D points `a` and `b` on all three axes.
	 * @return NEGATIVE -> a<b, ZERO -> a==b, POSITIVE -> a>b.
	 */
	std::array<Sign, 3> on_all(const PointT &a, const PointT &b);

	/**
	 * @brief Lexicographically compare x/y-coordinate of two 2D points `a` and
	 * `b`.
	 * @return NEGATIVE -> a<b, ZERO -> a==b, POSITIVE -> a > b.
	 */
	Sign operator()(const PointT &a, const PointT &b);

	/**
	 * @brief Check if the two points are coincident by lexicographically
	 * comparing their coordinates.
	 */
	bool coincident(const PointT &a, const PointT &b)
	{
		return operator()(a, b) == Sign::ZERO;
	}

	/* Same functions with only different parameter types */

	Sign on_x(const PointT &a, const FT *b);
	Sign on_y(const PointT &a, const FT *b);
	Sign on_z(const PointT &a, const FT *b);

	Sign on(const PointT &a, const FT *b, size_t axis);

	std::array<Sign, 3> on_all(const PointT &a, const FT *b);

	Sign on_x(const PointT &a, const FT b);
	Sign on_y(const PointT &a, const FT b);
	Sign on_z(const PointT &a, const FT b);

	Sign on(const PointT &a, const FT b, size_t axis);
};

/******************************************************************************/
/* Triangle Normal & Segment Axis *********************************************/
/******************************************************************************/

/**
 * @brief Determines the largest component in the normal of a triangle.
 *
 * @details
 * The normal vector of the triangle is computed from the given vertices, and
 * the largest component (in absolute value) of this normal vector is
 * identified.
 *
 * @note This function assumes that the triangle is not exactly degenerate.
 * It may crash otherwise.
 * @note The class provides two operator() overloads:
 * - One that takes the coordinates of the three vertices as separate
 * parameters.
 * - Another that takes the coordinates of the vertices as arrays.
 */
TEMPLATE_DECL
class MaxComponentInTriangleNormal
{
public:
	/**
	 * @brief Given the vertices of a triangle <v1, v2, v3>, this function
	 * computes the normal vector (x, y, z) of the triangle.
	 * It then determines the largest component (in absolute value) of this
	 * normal vector.
	 * @return The function returns:
	 * 0 - if the largest component is |x|
	 * 1 - if the largest component is |y|
	 * 2 - if the largest component is |z|
	 *
	 * @note: This function assumes that the triangle is not degenerate. It may
	 * produce incorrect results or crash otherwise.
	 */
	int operator()(FT v1x, FT v1y, FT v1z, FT v2x, FT v2y, FT v2z, FT v3x, FT v3y,
	               FT v3z);

	/**
	 * @brief Same as the previous function, but takes the coordinates of the
	 * vertices as arrays.
	 */
	int operator()(const FT *v1, const FT *v2, const FT *v3)
	{
		return operator()(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], v3[0], v3[1],
		                  v3[2]);
	}
};

/**
 * @brief Determines the axis along which the segment has the longest projected
 * length.
 *
 * @details
 * The projected length of the segment on each axis (x, y, z) is computed, and
 * the axis with the maximum projected length is identified.
 *
 * @note This function assumes that the segment is not degenerate.
 * It may produce incorrect results or crash otherwise.
 */
TEMPLATE_DECL
class LongestAxis_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/**
	 * @brief Given the endpoints of a segment <a, b>, this function computes the
	 * projected length of the segment on each axis (x, y, z). It then determines
	 * the axis with the longest projected length.
	 * @return The function returns:
	 * 0 - if the longest projected length is along the x-axis
	 * 1 - if the longest projected length is along the y-axis
	 * 2 - if the longest projected length is along the z-axis
	 *
	 * @note: This function assumes that the segment is not degenerate. It may
	 * produce incorrect results or crash otherwise.
	 */
	int operator()(const PointT &a, const PointT &b);
};

/******************************************************************************/
/* Circle & Sphere ************************************************************/
/******************************************************************************/

/**
 * @brief InCircle: Test if a point is inside a circle defined by points.
 */
TEMPLATE_DECL
class InCircle_Indirect
{
public:
	using VecT   = Vec2T<FT>;
	using PointT = GenericPoint2T<IT, ET>;

public:
	/**
	 * @brief In 2D, test a point `d` is inside the circumcircle of three
	 * points `a`, `b`, and `c`. We assume that `a`, `b` and `c` is given in
	 * couter-clock-wise order.
	 * @param points Given in generic points.
	 * @return POSITIVE->inside, ZERO->on, NEGATIVE->outside.
	 */
	Sign operator()(const PointT &a, const PointT &b, const PointT &c,
	                const PointT &d);

	/**
	 * @brief In 2D, test a point `d` is inside the circumcircle of three
	 * points `a`, `b`, and `c`. We assume that `a`, `b` and `c` is given in
	 * couter-clock-wise order.
	 * @param points Given in number pointers.
	 * @return POSITIVE->inside, ZERO->on, NEGATIVE->outside.
	 */
	Sign operator()(const FT *a, const FT *b, const FT *c, const FT *d);
};

/**
 * @brief InSphere: Test if a point is inside a sphere defined by points.
 */
TEMPLATE_DECL
class InSphere_Indirect
{
public:
	using VecT   = Vec3T<FT>;
	using PointT = GenericPoint3T<IT, ET>;

public:
	/**
	 * @brief In 3D, test a point `e` is inside the circumsphere of four
	 * points `a`, `b`, `c`, and `d`.
	 * @param points Given in generic points.
	 * @return POSITIVE->inside, ZERO->on, NEGATIVE->outside.
	 */
	Sign operator()(const PointT &a, const PointT &b, const PointT &c,
	                const PointT &d, const PointT &e);

	/**
	 * @brief In 3D, test a point `e` is inside the circumsphere of four
	 * points `a`, `b`, `c`, and `d`.
	 * @param points Given in number pointers.
	 * @return POSITIVE->inside, ZERO->on, NEGATIVE->outside.
	 */
	Sign operator()(const FT *a, const FT *b, const FT *c, const FT *d,
	                const FT *e);
};

#undef TEMPLATE_DECL

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "IndirectPredicates.inl"
#endif