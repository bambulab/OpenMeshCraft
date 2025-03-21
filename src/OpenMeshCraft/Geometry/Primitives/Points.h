#pragma once

#include "Point2T.h"
#include "Point3T.h"

namespace OMC {

template <typename NT>
class AsGenericPoint_Ex
{
public:
	using GP2 = Point2T<NT>;
	using EP2 = Point2T<NT>;

	using GP3 = Point3T<NT>;
	using EP3 = Point3T<NT>;

public:
	// clang-format off
	GP2       &operator()(      EP2& src) { return *static_cast<GP2 *>(&src); }
	const GP2 &operator()(const EP2& src) { return *static_cast<const GP2 *>(&src); }

	GP3       &operator()(      EP3& src) { return *static_cast<GP3 *>(&src); }
	const GP3 &operator()(const EP3& src) { return *static_cast<const GP3 *>(&src); }
	// clang-format on
};

template <typename NT>
class AsExplicitPoint_Ex
{
public:
	using GP2 = Point2T<NT>;
	using EP2 = Point2T<NT>;

	using GP3 = Point3T<NT>;
	using EP3 = Point3T<NT>;

public:
	EP2       &operator()(GP2 &src) { return src; }
	EP3       &operator()(GP3 &src) { return src; }
	const EP2 &operator()(const GP2 &src) { return src; }
	const EP3 &operator()(const GP3 &src) { return src; }

	bool is_explicit(OMC_UNUSED const GP2 &src) { return true; }
	bool is_explicit(OMC_UNUSED const GP3 &src) { return true; }
};

template <typename NT>
class ToExplicitPoint_Ex
{
public:
	using GP2 = Point2T<NT>;
	using EP2 = Point2T<NT>;

	using GP3 = Point3T<NT>;
	using EP3 = Point3T<NT>;

public:
	const EP2 &operator()(const GP2 &src) { return src; }
	const EP3 &operator()(const GP3 &src) { return src; }
};

template <typename NT>
class CreateImplicitSSI2_Ex
{
public:
	using GP2     = Point2T<NT>;
	using EP2     = Point2T<NT>;
	using IP2_SSI = Point2T<NT>;

	IP2_SSI operator()(OMC_UNUSED const GP2 &l11, OMC_UNUSED const GP2 &l12,
	                   OMC_UNUSED const GP2 &l21, OMC_UNUSED const GP2 &l22)
	{
		OMC_THROW_NOT_IMPLEMENTED();
		return IP2_SSI();
	}
};

template <typename NT>
class CreateImplicitSSI3_Ex
{
public:
	using GP3     = Point3T<NT>;
	using EP3     = Point3T<NT>;
	using IP3_SSI = Point3T<NT>;

public:
	IP3_SSI operator()(OMC_UNUSED const GP3 &a, OMC_UNUSED const GP3 &b,
	                   OMC_UNUSED const GP3 &p, OMC_UNUSED const GP3 &q,
	                   OMC_UNUSED int plane)
	{
		OMC_THROW_NOT_IMPLEMENTED();
		return IP3_SSI();
	}
};

template <typename NT>
class CreateImplicitLNC_Ex
{
public:
	using GP3     = Point3T<NT>;
	using EP3     = Point3T<NT>;
	using IP3_LNC = Point3T<NT>;

public:
	IP3_LNC operator()(OMC_UNUSED const GP3 &p, OMC_UNUSED const GP3 &q,
	                   OMC_UNUSED const NT t)
	{
		OMC_THROW_NOT_IMPLEMENTED();
		return IP3_LNC();
	}
};

template <typename NT>
class CreateImplicitLPI_Ex
{
public:
	using GP3     = Point3T<NT>;
	using EP3     = Point3T<NT>;
	using IP3_LPI = Point3T<NT>;

public:
	IP3_LPI operator()(OMC_UNUSED const GP3 &p, OMC_UNUSED const GP3 &q,
	                   OMC_UNUSED const GP3 &r, OMC_UNUSED const GP3 &s,
	                   OMC_UNUSED const GP3 &t)
	{
		OMC_THROW_NOT_IMPLEMENTED();
		return IP3_LPI();
	}
};

template <typename NT>
class CreateImplicitTPI_Ex
{
public:
	using GP3     = Point3T<NT>;
	using EP3     = Point3T<NT>;
	using IP3_TPI = Point3T<NT>;

	IP3_TPI operator()(OMC_UNUSED const GP3 &v1, OMC_UNUSED const GP3 &v2,
	                   OMC_UNUSED const GP3 &v3, OMC_UNUSED const GP3 &w1,
	                   OMC_UNUSED const GP3 &w2, OMC_UNUSED const GP3 &w3,
	                   OMC_UNUSED const GP3 &u1, OMC_UNUSED const GP3 &u2,
	                   OMC_UNUSED const GP3 &u3)
	{
		OMC_THROW_NOT_IMPLEMENTED();
		return IP3_TPI();
	}
};

} // namespace OMC