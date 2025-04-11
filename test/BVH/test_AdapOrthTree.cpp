#include "OpenMeshCraft/BVH/AdaptiveOrthTree/AdapOcTree.h"
#include "OpenMeshCraft/BVH/AdaptiveOrthTree/AdapQuadTree.h"
#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "VisualizeBoxTree.h"
#include "test_utils.h"

class test_AdapOrthTree : public testing::Test
{
protected:
	using index_t = OMC::index_t;
	using APAC    = OMC::APAC;

	class AdapOrthSplitPred
	{
	public:
		template <typename OrthTree, typename OrthNode>
		bool operator()(OMC_UNUSED const OrthTree &tree, const OrthNode &node)
		{
			return node.size() > 1000;
		}
	};

	class AdapQuadShapeRefinePred
	{
	public:
		template <typename OrthTree, typename OrthNode>
		bool operator()(const OrthTree &tree, const OrthNode &node,
		                std::array<bool, 2> &partitionable)
		{
			auto diag_length =
			  (tree.box().max_bound() - tree.box().min_bound()).length();
			auto node_length = node.box().max_bound() - node.box().min_bound();
			partitionable[0] = node_length[0] > 0.05 * diag_length;
			partitionable[1] = node_length[1] > 0.05 * diag_length;
			return partitionable[0] || partitionable[1];
		}
	};

	class AdapOcShapeRefinePred
	{
	public:
		template <typename OrthTree, typename OrthNode>
		bool operator()(const OrthTree &tree, const OrthNode &node,
		                std::array<bool, 3> &partitionable)
		{
			auto diag_length =
			  (tree.box().max_bound() - tree.box().min_bound()).length();
			auto node_length = node.box().max_bound() - node.box().min_bound();
			partitionable[0] = node_length[0] > 0.05 * diag_length;
			partitionable[1] = node_length[1] > 0.05 * diag_length;
			partitionable[2] = node_length[2] > 0.05 * diag_length;
			return partitionable[0] || partitionable[1] || partitionable[2];
		}
	};

	class AdapQuadTraits
	{
	public:
		static constexpr size_t Dimension = 2;
		static constexpr size_t MaxDepth  = 16;

		using NT    = APAC::NT;
		using BboxT = APAC::BoundingBox2;

    using PrimAttrT = index_t;

		using SplitPred       = AdapOrthSplitPred;
		using ShapeRefinePred = AdapQuadShapeRefinePred;
		using DoIntersect     = APAC::DoIntersect;
		using CalcBbox        = APAC::CalcBoundingBox2;
	};

	using QuadTree =
	  OMC::AdapQuadTree<OMC::AdapOrthAutoDeduceTraits<AdapQuadTraits>>;

	class AdapOcTraits
	{
	public:
		static constexpr size_t Dimension = 3;
		static constexpr size_t MaxDepth  = 16;

		using NT    = APAC::NT;
		using BboxT = APAC::BoundingBox3;

    using PrimAttrT = index_t;

		using SplitPred       = AdapOrthSplitPred;
		using ShapeRefinePred = AdapOcShapeRefinePred;
		using DoIntersect     = APAC::DoIntersect;
		using CalcBbox        = APAC::CalcBoundingBox3;
	};

	using OcTree = OMC::AdapOcTree<OMC::AdapOrthAutoDeduceTraits<AdapOcTraits>>;

protected:
	TriPoints points;
	Triangles faces;

	void SetUp() override
	{
		TEST_GET_CONFIG(AdapOrthTree, SetUp);
		std::string filename = config.get<std::string>("filename");

		IOOptions io_options;
		io_options.vertex_has_point = true;

		read_mesh(filename, points, faces, io_options);
	}

	void TearDown() override {}
};

TEST_F(test_AdapOrthTree, ConstructQuadTree)
{
	TEST_OUTPUT_DIRECTORY(AdapOrthTree, ConstructQuadTree);

	QuadTree                     tree;
	std::vector<index_t>         indices;
	std::vector<APAC::Triangle2> triangles;

	for (const auto &f : faces)
	{
		APAC::Point2 p0(points[f[0]].x(), points[f[0]].y());
		APAC::Point2 p1(points[f[1]].x(), points[f[1]].y());
		APAC::Point2 p2(points[f[2]].x(), points[f[2]].y());

		triangles.push_back(APAC::Triangle2(p0, p1, p2));
		indices.push_back(indices.size());
	}

	tree.insert_primitives(triangles, indices);
	tree.construct(true, 1.01);
	// tree.shape_refine();

	// visualize tree and save
	visualizeBoxTree2D<QuadTree>(tree, outdir + "quadtree.obj");
}

TEST_F(test_AdapOrthTree, ConstructOcTree)
{
	TEST_OUTPUT_DIRECTORY(AdapOrthTree, ConstructOcTree);

	OcTree                       tree;
	std::vector<index_t>         indices;
	std::vector<APAC::Triangle3> triangles;

	for (const auto &f : faces)
	{
		triangles.push_back(
		  APAC::Triangle3(points[f[0]], points[f[1]], points[f[2]]));
		indices.push_back(indices.size());
	}

	tree.insert_primitives(triangles, indices);
	tree.construct(true, 1.01);
	// tree.shape_refine();

	// visualize tree and save
	visualizeBoxTree3D<OcTree>(tree, outdir + "octree.obj");
}