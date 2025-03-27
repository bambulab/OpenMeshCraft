#pragma once

#include "OpenMeshCraft/Utils/ExtendedTypeTraits.h"

namespace OMC {

/******************************************************/
/* 1. Define the reference point of the generic point */
/******************************************************/

/**
 * @class AABB_GPoint_ReferencePoint
 * @brief A class template to compute a reference point for a generic point
 *
 * @tparam GPointPtr The pointer of the generic point.
 * @tparam ToEP Convert the generic point to explicit point.
 */
template <typename GPointPtr, typename ToEP>
class AABB_GPoint_ReferencePoint
{
public:
  using GPointT = remove_cvref_t<decltype(*std::declval<GPointPtr>())>;
  using EPointT =
    remove_cvref_t<decltype(std::declval<ToEP>()(*std::declval<GPointPtr>()))>;

public:
  EPointT operator()(GPointPtr gp) { return ToEP()(*gp); }
};

} // namespace OMC