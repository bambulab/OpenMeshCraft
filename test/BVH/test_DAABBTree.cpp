#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "OpenMeshCraft/BVH/AABB/AABBTraits.h"
#include "OpenMeshCraft/BVH/AABB/AABBTraversalTraits.h"
#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTree.h"
#include "OpenMeshCraft/BVH/AABB/Instance/AABBTree_Triangle_Intersection.h"

#include "OpenMeshCraft/Utils/Macros.h"

#include "test_utils.h"

class test_DynamicAABBTree : public testing::Test
{
protected:
	using index_t = OMC::index_t;
	using APAC    = OMC::APAC;

	using Tree = OMC::DAABBTree<OMC::AABBTraits_Triangle_Intersection<APAC>>;
	using IndexedTriangle = OMC::PrimitiveWithAttribute<APAC::Triangle3, size_t>;

protected:
	TriPoints points;
	Triangles faces;

	void SetUp() override
	{
		TEST_GET_CONFIG(DynamicAABBTree, SetUp);
		std::string filename = config.get<std::string>("filename");

		IOOptions io_options;
		io_options.vertex_has_point = true;

		read_mesh(filename, points, faces, io_options);
	}

	void TearDown() override {}
};

TEST_F(test_DynamicAABBTree, Construct)
{
	TEST_OUTPUT_DIRECTORY(DynamicAABBTree, Construct);

	Tree tree;

	// construct an initial tree.
	std::vector<IndexedTriangle> triangles;
	index_t                      idx = 0;
	size_t                       n   = faces.size();

	for (size_t i = 0; i < n / 2; i++)
	{
		const auto &f = faces[i];
		triangles.push_back(IndexedTriangle(
		  APAC::Triangle3(points[f[0]], points[f[1]], points[f[2]]), idx++));
	}

	tree.insert(std::move(triangles));
	tree.build();

	// insert the remaining faces
	for (size_t i = n / 2; i < n; i++)
	{
		const auto &f = faces[i];
		tree.insert(IndexedTriangle(
		  APAC::Triangle3(points[f[0]], points[f[1]], points[f[2]]), idx++));
	}
	tree.rebuild();

	// delete some faces
	for (size_t i = n / 2; i < n; i++)
	{
		tree.remove(i);
	}
	tree.rebuild();

	// split some faces
	for (size_t i = 0; i < n / 2; i++)
	{
		const auto &f         = faces[i];
		const auto  mid_point = (points[f[0]] + points[f[1]]) * 0.5;
		const auto  tri0 = APAC::Triangle3(points[f[0]], mid_point, points[f[2]]);
		const auto  tri1 = APAC::Triangle3(mid_point, points[f[1]], points[f[2]]);

		tree.split(i, IndexedTriangle(tri0, idx++), IndexedTriangle(tri1, idx++));
	}
	tree.rebuild();
}