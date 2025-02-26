#pragma once

namespace OMC {

/****************************************************************************/
/* Macros that control behavior of predicates *******************************/
/****************************************************************************/

// Cache dynamic filter (interval numbers) in points
#define OMC_CACHE_DF

// Compress expansion before:
// 1. storing coordinates.
// 2. calculate the final determinant in orientOn2D_IIE and orientOn2D_III.
#define OMC_COMPRESS_EXPANSION

// Update interval coordinates after calculating expansion coordinates.
#define OMC_UPDATE_INTERVAL_BY_EXPANSION

// Switch to other exact arithmetic if expansion's length is too long.
#define OMC_LIMIT_EXPANSION_LENGTH
#define OMC_EXPANSION_LENGTH_THRES 100
#define OMC_SUM_LENGTH_THRES 40

/****************************************************************************/
/* Utils about orthogonal plane *********************************************/
/****************************************************************************/

/// @brief An enumeration represents three different orthogonal planes in 3D
/// space: YZ, ZX, and XY. Each plane is assigned a unique integer value.
enum OrPlane
{
	YZ = 0,   // normal is X(0)
	ZX = 1,   // normal is Y(1)
	XY = 2    // normal is Z(2)
};

inline OrPlane int_to_OrPlane(const int &norm)
{
	return static_cast<OrPlane>(norm);
}

inline int OrPlane_to_int(const OrPlane &p) { return static_cast<int>(p); }

} // namespace OMC