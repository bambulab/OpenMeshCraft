#pragma once

#include "OpenMeshCraft/Utils/IndexDef.h"
#include "OpenMeshCraft/Utils/SFINAE.h"

namespace OMC {

template <typename AdapOrthTraits>
class AdapOrthAutoDeduceTraits
{
public:
  /************* Below values and types must be provided ******************/

  static constexpr size_t Dimension = AdapOrthTraits::Dimension;

  // bounding box type
  using BboxT           = typename AdapOrthTraits::BboxT;
  // split predicate: when to split and when to stop.
  using SplitPred       = typename AdapOrthTraits::SplitPred;
  // shape refine predicate: when to refine and when to stop.
  using ShapeRefinePred = typename AdapOrthTraits::ShapeRefinePred;
  // do intersect
  using DoIntersect     = typename AdapOrthTraits::DoIntersect;
  // calculate bounding box
  using CalcBbox        = typename AdapOrthTraits::CalcBbox;

  /*************** Try to deduce below values *****************************/

  // clang-format off
  GET_VALUE_OTHERWISE_DEFAULT(AdapOrthTraits, size_t, MaxDepth, 32, MaxDepth);
  GET_VALUE_OTHERWISE_DEFAULT(AdapOrthTraits, bool, StoreBoxesInInternalNodes, false, StoreBoxesInInternalNodes);
  // clang-format on

  /****************** Try to deduce below types ***************************/

  // number type
  GET_TYPE_OTHERWISE_DEFAULT(AdapOrthTraits, NT, double, NT);
  static_assert(!std::is_void_v<NT>,
                "NT is not provided and can't be deduced.");

  // primitive's attribute
  GET_TYPE_OTHERWISE_DEFAULT(AdapOrthTraits, PrimAttrT, void, PrimAttrT);

  // node attribute
  GET_TYPE_OTHERWISE_DEFAULT(AdapOrthTraits, NodeAttrT, double, NodeAttrT);

  /*************************************************************************/
  /*                Below types are automatically deduced.                 */
  /*************************************************************************/

  // TreeBboxT ===============================================================

  class TreeBboxT_NoAttr : public BboxT
  {
  public:
    const BboxT &bbox() const { return *static_cast<const BboxT *>(this); }
    BboxT       &bbox() { return *static_cast<BboxT *>(this); }
  };

  class TreeBboxT_Attr : public BboxT
  {
  public:
    const BboxT &bbox() const { return *static_cast<const BboxT *>(this); }
    BboxT       &bbox() { return *static_cast<BboxT *>(this); }

    PrimAttrT  attr() const { return m_attr; }
    PrimAttrT &attr() { return m_attr; }

  protected:
    PrimAttrT m_attr;
  };

  using TreeBboxT = std::conditional_t<std::is_void_v<PrimAttrT>,
                                       TreeBboxT_NoAttr, TreeBboxT_Attr>;
};

#define AdapOrthTreeAbbreviate(Type) \
  using Type##Ptr  = Type *;         \
  using Type##CPtr = const Type *;   \
  using Type##Ref  = Type &;         \
  using Type##CRef = const Type &

} // namespace OMC