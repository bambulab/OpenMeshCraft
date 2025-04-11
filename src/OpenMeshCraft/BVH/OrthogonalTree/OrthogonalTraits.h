#pragma once

#include "OpenMeshCraft/Utils/SFINAE.h"

namespace OMC {

template <typename OrthTraits>
class OrthAutoDeduceTraits
{
public:
  /************* Below values and types must be provided ******************/

  static constexpr size_t Dimension = OrthTraits::Dimension;

  // bounding box type
  using BboxT       = typename OrthTraits::BboxT;
  // split predicate
  using SplitPred   = typename OrthTraits::SplitPred;
  // do intersect
  using DoIntersect = typename OrthTraits::DoIntersect;
  // calculate bounding box
  using CalcBbox    = typename OrthTraits::CalcBbox;

  /*************** Try to deduce below values *****************************/

  // clang-format off
  GET_VALUE_OTHERWISE_DEFAULT(OrthTraits, size_t, MaxDepth, 16, MaxDepth);
  GET_VALUE_OTHERWISE_DEFAULT(OrthTraits, bool, EnableGrade, false, EnableGrade)
  GET_VALUE_OTHERWISE_DEFAULT(OrthTraits, bool, EnableVertices, false, EnableVertices);
  GET_VALUE_OTHERWISE_DEFAULT(OrthTraits, bool, StoreBoxesInInternalNodes, false, StoreBoxesInInternalNodes);
  // clang-format on

  /****************** Try to deduce below types ***************************/

  // number type
  GET_TYPE_OTHERWISE_DEFAULT(OrthTraits, NT, double, NT);
  static_assert(!std::is_void_v<NT>,
                "NT is not provided and can't be deduced.");

  // primitive's attribute
  GET_TYPE_OTHERWISE_DEFAULT(OrthTraits, PrimAttrT, void, PrimAttrT);

  // node attribute
  GET_TYPE_OTHERWISE_DEFAULT(OrthTraits, NodeAttrT, void, NodeAttrT);

  // vertex attribute
  GET_TYPE_OTHERWISE_DEFAULT(OrthTraits, VertexAttrT, void, VertexAttrT);

  /*************************************************************************/
  /*                Below types are automatically deduced.                 */
  /*************************************************************************/

  // OrBboxT ===============================================================

  class OrBboxT_NoAttr : public BboxT
  {
  public:
    const BboxT &bbox() const { return *static_cast<const BboxT *>(this); }
    BboxT       &bbox() { return *static_cast<BboxT *>(this); }
  };

  class OrBboxT_Attr : public BboxT
  {
  public:
    const BboxT &bbox() const { return *static_cast<const BboxT *>(this); }
    BboxT       &bbox() { return *static_cast<BboxT *>(this); }

    PrimAttrT  attr() const { return m_attr; }
    PrimAttrT &attr() { return m_attr; }

  protected:
    PrimAttrT m_attr;
  };

  using OrBboxT =
    std::conditional_t<std::is_void_v<PrimAttrT>, OrBboxT_NoAttr, OrBboxT_Attr>;
};

#define OrthTreeAbbreviate(Type)   \
  using Type##Ptr  = Type *;       \
  using Type##CPtr = const Type *; \
  using Type##Ref  = Type &;       \
  using Type##CRef = const Type &

} // namespace OMC