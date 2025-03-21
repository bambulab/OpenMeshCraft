#include "OpenMeshCraft/Geometry/ExactIndirectPredicatesApproxConstructions.h"
#include "OpenMeshCraft/Tetrahedralization/DelaunayTet.h"

#include "OpenMeshCraft/Utils/DisableWarnings.h"

#include <CGAL/Epick_d.h>
#include <CGAL/Regular_triangulation.h>
#include <CGAL/point_generators_d.h>

#include "OpenMeshCraft/Utils/EnableWarnings.h"

#include "test_utils.h"

#include <random>

/*
 * All tests about CDT are put here,
 * until it's better to separate tests :D.
 */

class test_WeightedDelTet : public testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

protected:
	/* IO */
	using index_t       = OMC::index_t;
	using TriSoupTraits = OMC::TriSoupTraits;
	using TetSoupTraits = OMC::TetSoupTraits;

	using Points     = typename TriSoupTraits::Points;
	using Triangles  = typename TriSoupTraits::Triangles;
	using Tetrahedra = typename TetSoupTraits::Tetrahedra;

	/* Ours */

	using Kernel = OMC::EIAC;

	class DelTetTraits
	{
	public:
		using K = Kernel;

		using NT         = typename K::NT;
		using Vec2       = typename K::Vec2;
		using Vec3       = typename K::Vec3;
		using EPoint     = typename K::EPoint3;
		using GPoint     = typename K::GPoint3;
		using IPoint_SSI = typename K::IPoint3T_SSI;
		using IPoint_LNC = typename K::IPoint3T_LNC;
		using IPoint_LPI = typename K::IPoint3T_LPI;
		using IPoint_TPI = typename K::IPoint3T_TPI;

		using AsGP      = typename K::AsGP;
		using AsEP      = typename K::AsEP;
		using ToEP      = typename K::ToEP;
		using CreateSSI = typename K::CreateSSI3;
		using CreateLNC = typename K::CreateLNC;
		using CreateLPI = typename K::CreateLPI;
		using CreateTPI = typename K::CreateTPI;

		using Sphere      = typename K::Sphere3;
		using Segment     = typename K::Segment3;
		using Triangle    = typename K::Triangle3;
		using BoundingBox = typename K::BoundingBox3;

		// predicates
		using Orient2D           = typename K::Orient2D;
		using Orient3D           = typename K::Orient3D;
		using OrientOn2D         = typename K::OrientOn2D;
		using LessThan3D         = typename K::LessThan3D;
		using SquaredDistance3D  = typename K::SquaredDistance3D;
		using LongestAxis        = typename K::LongestAxis;
		using MaxCompInTriNormal = typename K::MaxCompInTriNormal;
		using InCircle           = typename K::InCircle;
		using InSphere           = typename K::InSphere;
		using InPowerSphere      = typename K::InPowerSphere;
		using DotProduct3D       = typename K::DotProductSign3D;
		using CollinearPoints3   = typename K::CollinearPoints3;
		// constructions
		using CalcBbox           = typename K::CalcBoundingBox3;
		using ProjectPoint       = typename K::ProjectPoint3;

		// clang-format off
		using DoIntersect                        = typename K::DoIntersect;
		using Segment3_Point3_DoIntersect        = typename K::Segment3_Point3_DoIntersect;
		using Segment3_Segment3_DoIntersect      = typename K::Segment3_Segment3_DoIntersect;
		using Triangle3_Point3_DoIntersect       = typename K::Triangle3_Point3_DoIntersect;
		using Triangle3_Segment3_DoIntersect     = typename K::Triangle3_Segment3_DoIntersect;
		using Triangle3_Triangle3_DoIntersect    = typename K::Triangle3_Triangle3_DoIntersect;
		using Tetrahedron3_Point3_DoIntersect    = typename K::Tetrahedron3_Point3_DoIntersect;
		using Tetrahedron3_Segment3_DoIntersect  = typename K::Tetrahedron3_Segment3_DoIntersect;
		using Tetrahedron3_Triangle3_DoIntersect = typename K::Tetrahedron3_Triangle3_DoIntersect;
		// clang-format on

		// Tetrahedral mesh settings
		const static bool WEIGHTED = true;
	};

	using TetMesh = OMC::TetrahedralMesh<DelTetTraits>;
	using DelTet  = OMC::DelaunayTet<DelTetTraits>;

	/* CGAL */
	const static int                               D = 3; // Dimension
	typedef CGAL::Epick_d<CGAL::Dimension_tag<D> > K;
	typedef CGAL::Regular_triangulation<K>         T;
	typedef K::Point_d                             Bare_point;
	typedef K::Weighted_point_d                    Weighted_point;
};

/**
 * @brief check if it will crash.
 */
TEST_F(test_WeightedDelTet, TestIfCrash)
{
	TEST_OUTPUT_DIRECTORY(WeightedDelTet, TestIfCrash);
	TEST_GET_CONFIG(WeightedDelTet, TestIfCrash);

	// Define IO
	IOOptions io_options;
	io_options.vertex_has_point = true;

	// Define mesh
	Points     input_points, result_points;
	Triangles  input_triangles;
	Tetrahedra result_tetrahedra;

	// read mesh
	std::string dir      = config.get<std::string>("dir");
	std::string filename = config.get<std::string>("filename");

	read_mesh(dir + filename, input_points, input_triangles, io_options);

	// convert to generic points
	std::deque<typename DelTetTraits::EPoint>    points;
	std::vector<typename DelTetTraits::GPoint *> vertices;

	for (const auto &p : input_points)
	{
		points.emplace_back(p.x(), p.y(), p.z());
		vertices.push_back(&points.back());
	}

	// generate random weights between 1.0 and 10.0
	std::vector<double> weights;

	std::random_device rd;
	std::mt19937       gen(rd());
	for (size_t i = 0; i < vertices.size(); i++)
	{
		weights.push_back(std::generate_canonical<double, 10>(gen) * 9.0 + 1.0);
	}

	// Ours Delaunay tetrahedralization

	auto start = OMC::Logger::elapse_reset();

	TetMesh mesh(vertices, &weights);

	DelTet dt(mesh);

	dt.tetrahedralize();

	double elapsed = OMC::Logger::elapsed(start).count();
	std::cout << std::format("weighted Delaunay tetrahedralization uses {} s\n",
	                         elapsed);
	std::cout << std::format("result tetrahedra {}\n", mesh.sizeTets());

	// convert to CGAL weighted points
	std::vector<Weighted_point> cgal_points;
	cgal_points.reserve(input_points.size());
	for (size_t i = 0; i < input_points.size(); i++)
	{
		const auto &p = input_points[i];
		cgal_points.push_back(
		  Weighted_point(Bare_point(p.x(), p.y(), p.z()), weights[i]));
	}

	// CGAL Regular triangulation

	start = OMC::Logger::elapse_reset();

	T t(D);

	// Insert the points in the triangulation
	t.insert(cgal_points.begin(), cgal_points.end());

	elapsed = OMC::Logger::elapsed(start).count();
	std::cout << std::format("Regular triangulation uses {} s\n", elapsed);
	std::cout << "Regular triangulation successfully computed: "
	          << t.number_of_vertices() << " vertices, "
	          << t.number_of_full_cells() << " cells." << std::endl;
}
