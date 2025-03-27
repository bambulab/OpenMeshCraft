#pragma once

namespace OMC {

/**
 * @brief Check if two BoundingBox intersect.
 *
 * Bounding boxes intersect if and only if they overlap in all dimensions
 * (including boundary overlap).
 *
 * @tparam Kernel.
 */
template <typename Kernel>
class Bbox_Bbox_DoIntersectK
{
public:
  using K     = Kernel;
  using Bbox2 = typename K::BoundingBox2;
  using Bbox3 = typename K::BoundingBox3;

public:
  /**
   * @brief Check if two BoundingBox intersect.
   * @return True if intersect, otherwise false.
   */
  bool operator()(const Bbox2 &lbox, const Bbox2 &rbox) const
  {
    // Bounding box must contains explicit points, so we directly compare.
    return lbox.min_bound() <= rbox.max_bound() &&
           rbox.min_bound() <= lbox.max_bound();
  }

  /**
   * @brief Check if two BoundingBox intersect.
   * @return True if intersect, otherwise false.
   */
  bool operator()(const Bbox3 &lbox, const Bbox3 &rbox) const
  {
    // Bounding box must contains explicit points, so we directly compare.
    return lbox.min_bound() <= rbox.max_bound() &&
           rbox.min_bound() <= lbox.max_bound();
  }
};

} // namespace OMC