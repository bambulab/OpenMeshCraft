#pragma once

#include "TetMesh.h"

namespace OMC {

template <typename Traits>
class DelaunayTet
{
public:
	using Self = DelaunayTet<Traits>;

public:
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "DelaunayTet.inl"
#endif