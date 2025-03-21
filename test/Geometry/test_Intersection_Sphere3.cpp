#include "OpenMeshCraft/Geometry/ExactIndirectPredicatesApproxConstructions.h"
#include "OpenMeshCraft/Geometry/Intersection/Sphere3_Point3.h"
#include "OpenMeshCraft/Geometry/Intersection/Sphere3_Segment3.h"
#include "OpenMeshCraft/Geometry/Primitives/Point2T.h"
#include "OpenMeshCraft/Geometry/Primitives/Point3T.h"

// clang-format off
#include "OpenMeshCraft/Utils/DisableWarnings.h"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "OpenMeshCraft/Utils/EnableWarnings.h"
// clang-format on

#include "gtest/gtest.h"

// #define CHECK_EACH
#ifdef CHECK_EACH
#include <execution>
#endif

class test_Intersection_Sphere3 : public testing::Test
{
protected:
	using EIAC = OMC::EIAC;
	using Pnt2 = EIAC::Point2;
	using Pnt3 = EIAC::Point3;

	using Sphere3_Point3_DoIntersect   = OMC::Sphere3_Point3_Do_Intersect<EIAC>;
	using Sphere3_Segment3_DoIntersect = OMC::Sphere3_Segment3_Do_Intersect<EIAC>;

	using FPnt2 = OMC::Point2T<double>;
	using FPnt3 = OMC::Point3T<double>;

	using EKIC = CGAL::Exact_predicates_inexact_constructions_kernel;
};

inline double randomUnitDouble() { return ((double)rand()) / RAND_MAX; }

TEST_F(test_Intersection_Sphere3, spherePoint)
{
	size_t num_all_groups = 100000;
	// reset random seed for this test everytime
	srand(0);

	// Create vector of all sphere and point
	double *atp = new double[num_all_groups * 7];

	// Create vector of random segment and point
	double *random_groups = atp;
	for (size_t i = 0; i < num_all_groups * 7; i++)
		random_groups[i] = randomUnitDouble();

	// Calculate predicates on them
	int  cgal_dummy = 0;
	auto start      = OMC::Logger::elapse_reset();
	for (size_t i = 0; i < num_all_groups; ++i)
	{
		EKIC::Sphere_3 sphere(
		  EKIC::Point_3(atp[7 * i], atp[7 * i + 1], atp[7 * i + 2]),
		  atp[7 * i + 3]);
		EKIC::Point_3 pnt(atp[7 * i + 4], atp[7 * i + 5], atp[7 * i + 6]);
		cgal_dummy +=
		  EKIC::Bounded_side_3()(sphere, pnt) >= CGAL::Bounded_side::ON_BOUNDARY;
		// EKIC::Do_intersect_3()(sphere, pnt);
	}

	std::cout << "CGAL elapsed time: " << OMC::Logger::elapsed(start).count()
	          << "s\n";
	std::cout << "Dummy sum: " << cgal_dummy << "\n";

	int ours_dummy = 0;
	start          = OMC::Logger::elapse_reset();
	for (size_t i = 0; i < num_all_groups; ++i)
	{
		ours_dummy += Sphere3_Point3_DoIntersect()(
		  Pnt3(atp[7 * i], atp[7 * i + 1], atp[7 * i + 2]), atp[7 * i + 3],
		  Pnt3(atp[7 * i + 4], atp[7 * i + 5], atp[7 * i + 6]));
	}

	std::cout << "OpenMeshCraft elapsed time: "
	          << OMC::Logger::elapsed(start).count() << "s\n";
	std::cout << "Dummy sum: " << ours_dummy << "\n";

	EXPECT_EQ(cgal_dummy, ours_dummy);

#ifdef CHECK_EACH
	std::vector indices(num_all_groups, 0);
	std::iota(indices.begin(), indices.end(), 0);
	std::for_each(
	  std::execution::seq, indices.begin(), indices.end(),
	  [&](size_t i)
	  {
		  EKIC::Sphere_3 sphere(
		    EKIC::Point_3(atp[7 * i], atp[7 * i + 1], atp[7 * i + 2]),
		    atp[7 * i + 3]);
		  EKIC::Point_3 pnt(atp[7 * i + 4], atp[7 * i + 5], atp[7 * i + 6]);
		  bool          ref_sign += EKIC::Do_intersect_3()(sphere, pnt);

		  bool our_sign = Sphere3_Point3_DoIntersect()(
		    Pnt3(atp[7 * i], atp[7 * i + 1], atp[7 * i + 2]), atp[7 * i + 3],
		    Pnt3(atp[7 * i + 4], atp[7 * i + 5], atp[7 * i + 6]));

		  EXPECT_EQ(ref_sign, our_sign);
	  });
#endif
	delete[] atp;
}

TEST_F(test_Intersection_Sphere3, sphereSegment)
{
	size_t num_all_groups = 100000;
	// reset random seed for this test everytime
	srand(0);

	// Create vector of all spheres and segments
	double *atp = new double[num_all_groups * 10];

	// Create two random segments
	double *random_groups = atp;
	for (size_t i = 0; i < num_all_groups * 10; i++)
		random_groups[i] = randomUnitDouble();

	// Calculate predicates on them
	int  cgal_dummy = 0;
	auto start      = OMC::Logger::elapse_reset();
	for (size_t i = 0; i < num_all_groups; ++i)
	{
		EKIC::Sphere_3 sphere(
		  EKIC::Point_3(atp[10 * i], atp[10 * i + 1], atp[10 * i + 2]),
		  atp[10 * i + 3]);
		EKIC::Point_3   p0(atp[10 * i + 4], atp[10 * i + 5], atp[10 * i + 6]);
		EKIC::Point_3   p1(atp[10 * i + 7], atp[10 * i + 8], atp[10 * i + 9]);
		EKIC::Segment_3 seg(p0, p1);

		cgal_dummy +=
		  EKIC::Bounded_side_3()(sphere, p0) >= CGAL::Bounded_side::ON_BOUNDARY ||
		  EKIC::Bounded_side_3()(sphere, p1) >= CGAL::Bounded_side::ON_BOUNDARY ||
		  EKIC::Do_intersect_3()(sphere, seg);
	}

	std::cout << "CGAL elapsed time: " << OMC::Logger::elapsed(start).count()
	          << "s\n";
	std::cout << "Dummy sum: " << cgal_dummy << "\n";

	int ours_dummy = 0;
	start          = OMC::Logger::elapse_reset();
	for (size_t i = 0; i < num_all_groups; ++i)
	{
		ours_dummy += Sphere3_Segment3_DoIntersect()(
		  Pnt3(atp[10 * i], atp[10 * i + 1], atp[10 * i + 2]), atp[10 * i + 3],
		  Pnt3(atp[10 * i + 4], atp[10 * i + 5], atp[10 * i + 6]),
		  Pnt3(atp[10 * i + 7], atp[10 * i + 8], atp[10 * i + 9]));
	}

	std::cout << "OpenMeshCraft elapsed time: "
	          << OMC::Logger::elapsed(start).count() << "s\n";
	std::cout << "Dummy sum: " << ours_dummy << "\n";

	EXPECT_EQ(cgal_dummy, ours_dummy);

#ifdef CHECK_EACH
	std::vector indices(num_all_groups, 0);
	std::iota(indices.begin(), indices.end(), 0);
	std::for_each(
	  std::execution::seq, indices.begin(), indices.end(),
	  [&](size_t i)
	  {
		  EKIC::Sphere_3 sphere(
		    EKIC::Point_3(atp[10 * i], atp[10 * i + 1], atp[10 * i + 2]),
		    atp[10 * i + 3]);
		  EKIC::Segment_3 seg(
		    EKIC::Point_3(atp[10 * i + 4], atp[10 * i + 5], atp[10 * i + 6]),
		    EKIC::Point_3(atp[10 * i + 7], atp[10 * i + 8], atp[10 * i + 9]));
		  bool ref_sign = EKIC::Do_intersect_3()(sphere, seg);

		  bool our_sign = Sphere3_Segment3_DoIntersect()(
		    Pnt3(atp[10 * i], atp[10 * i + 1], atp[10 * i + 2]), atp[10 * i + 3],
		    Pnt3(atp[10 * i + 4], atp[10 * i + 5], atp[10 * i + 6]),
		    Pnt3(atp[10 * i + 7], atp[10 * i + 8], atp[10 * i + 9]));

		  EXPECT_EQ(ref_sign, our_sign);
	  });
#endif
	delete[] atp;
}