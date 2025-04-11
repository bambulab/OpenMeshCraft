#pragma once

namespace OMC {

template <typename BboxT, typename BoxIter>
BboxT calc_box_from_boxes(BoxIter begin, BoxIter end)
{
  BboxT box;
  if (begin == end)
    return box;

  box = *begin;
  for (++begin; begin != end; ++begin)
    box += *begin;

  return box;
}

template <typename BboxT, typename BoxPtrIter>
BboxT calc_box_from_box_pointers(BoxPtrIter begin, BoxPtrIter end)
{
  BboxT box;
  if (begin == end)
    return box;

  box = (*begin)->box();
  for (++begin; begin != end; ++begin)
    box += (*begin)->box();

  return box;
}

template <typename BboxT, typename Tree, typename BoxIdxIter>
BboxT calc_box_from_box_indices(const Tree &tree, BoxIdxIter begin,
                                BoxIdxIter end)
{
  BboxT box;
  if (begin == end)
    return box;

  box = tree.box(*begin);
  for (++begin; begin != end; ++begin)
    box += tree.box(*begin);

  return box;
}

} // namespace OMC