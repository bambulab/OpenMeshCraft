#pragma once

#include "AdapOrthTree.h"

namespace OMC {

/**
 * @brief Adaptive quadtree, i.e., orthogonal tree in 2D.
 * @details Details about octree or orthogonal tree are in OrthogonalTree.
 */
template <typename _Traits>
class AdapQuadTree : public AdapOrthTree<_Traits>
{
public:
  using Traits = _Traits;

  static constexpr size_t MaxDepth  = Traits::MaxDepth;
  static constexpr size_t Dimension = Traits::Dimension;
  static constexpr size_t Degree    = (1u << Dimension);

  using Base = AdapOrthTree<Traits>;

  using NT = typename Base::NT;

  using Bbox = typename Base::Bbox;

  using TreeBbox = typename Base::TreeBbox;
  AdapOrthTreeAbbreviate(TreeBbox);

  using TreePoint = typename Base::TreePoint;
  AdapOrthTreeAbbreviate(TreePoint);

  using Node = typename Base::Node;
  AdapOrthTreeAbbreviate(Node);

protected:
  virtual void
  calc_box_for_children(NodeRef nd, TreePointCRef center,
                        std::array<Bbox, Degree> &child_boxes) final;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "AdapQuadTree.inl"
#endif