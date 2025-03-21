#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "OpenMeshCraft/BVH/AABB/Dynamic/DAABBTree.h"
#include "OpenMeshCraft/BVH/AABB/Instance/AABBTree_SegSphere_Intersection.h"

#include "test_utils.h"

class test_DynamicAABBTree : public testing::Test
{
protected:
	using index_t = OMC::index_t;
	using APAC    = OMC::APAC;

	using Tree    = OMC::DAABBTree<OMC::DAABBTraits_SegSphere_Intersection<
	     APAC::Segment3, APAC::CalcBoundingBox3>>;
	using Segment = APAC::Segment3;

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
	std::vector<Segment> segments;
	std::vector<index_t> indices;
	index_t              idx = 0;
	size_t               n   = faces.size();

	for (size_t i = 0; i < n / 2; i++)
	{
		const auto &f = faces[i];
		segments.push_back(Segment(points[f[0]], points[f[1]]));
		indices.push_back(idx++);
	}

	tree.insert(segments.begin(), segments.end(), indices.begin(), indices.end());
	tree.build();

	// insert the remaining faces
	for (size_t i = n / 2; i < n; i++)
	{
		const auto &f = faces[i];
		tree.insert(Segment(points[f[0]], points[f[1]]), idx++);
	}
	tree.build();

	// delete some faces
	for (size_t i = 1; i < n; i += 2)
	{
		tree.remove(i);
	}
	tree.collect_garbage();

	// split some faces
	for (size_t i = 0; i < n; i += 2)
	{
		const auto &f         = faces[i];
		const auto  mid_point = (points[f[0]] + points[f[1]]) * 0.5;
		const auto  seg0      = Segment(points[f[0]], mid_point);
		const auto  seg1      = Segment(mid_point, points[f[1]]);

		tree.split(i, idx, seg0, idx + 1, seg1);
		idx += 2;
	}
	tree.build();
}