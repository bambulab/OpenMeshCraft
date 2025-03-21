#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"

#include "gtest/gtest.h"

#include "CGAL/Interval_nt.h"

#include <type_traits>

using namespace OMC;

TEST(IntervalNumber, Construct)
{
	IntervalNumber it0(1.);
	IntervalNumber it1(1., 2.);
	// EXPECT_THROW(it1 = IntervalNumber(-1.1, 0.9), std::runtime_error);
}

TEST(IntervalNumber, OperatorsComparedWithCGAL)
{
	auto interval_number_equal = [](const IntervalNumber<std::true_type> &it,
	                                const CGAL::Interval_nt<false>       &_it)
	{
		if (!(it.inf() == _it.inf() && it.sup() == _it.sup()))
		{
			std::cout.precision(20);
			std::cout << "it " << it.inf() << ", " << it.sup() << std::endl;
			std::cout << "_it " << _it.inf() << ", " << _it.sup() << std::endl;
			return false;
		}
		else
			return true;
	};

	using OIT = IntervalNumber<std::true_type>;
	using CIT = CGAL::Interval_nt<false>;

	srand(0);
	OIT::Protector it_protecter;
	for (size_t i = 0; i < 10000000; i++)
	{
		double d1 = rand() * M_PI, d2 = rand() * M_PI;

		OIT it1(d1), it2(d2);
		OIT it3  = it1 + it2;
		OIT it4  = it1 - it2;
		OIT it5  = it1 * it2;
		OIT it6  = it3 * it4;
		OIT it7  = it6 - it5;
		OIT it8  = it7 + it6;
		OIT it9  = it8 * it3;
		OIT it10 = it9 / it3;
		OIT it11 = it10 / it7;

		CIT _it1(d1), _it2(d2);
		CIT _it3  = _it1 + _it2;
		CIT _it4  = _it1 - _it2;
		CIT _it5  = _it1 * _it2;
		CIT _it6  = _it3 * _it4;
		CIT _it7  = _it6 - _it5;
		CIT _it8  = _it7 + _it6;
		CIT _it9  = _it8 * _it3;
		CIT _it10 = _it9 / _it3;
		CIT _it11 = _it10 / _it7;

		ASSERT_TRUE(interval_number_equal(it1, _it1));
		ASSERT_TRUE(interval_number_equal(it2, _it2));
		ASSERT_TRUE(interval_number_equal(it3, _it3));
		ASSERT_TRUE(interval_number_equal(it4, _it4));
		ASSERT_TRUE(interval_number_equal(it5, _it5));
		ASSERT_TRUE(interval_number_equal(it6, _it6));
		ASSERT_TRUE(interval_number_equal(it7, _it7));
		ASSERT_TRUE(interval_number_equal(it8, _it8));
		ASSERT_TRUE(interval_number_equal(it9, _it9));
		ASSERT_TRUE(interval_number_equal(it10, _it10));
		ASSERT_TRUE(interval_number_equal(it11, _it11));

		if (it11.is_negative())
		{
			it11  = -it11;
			_it11 = -_it11;
		}
		if (it11.is_sign_reliable())
		{
			OIT it12  = it11.sqrt();
			CIT _it12 = CGAL::sqrt(_it11);
			ASSERT_TRUE(interval_number_equal(it12, _it12));
		}
	}
}