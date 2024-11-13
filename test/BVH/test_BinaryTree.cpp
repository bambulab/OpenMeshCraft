#include "OpenMeshCraft/BVH/BinaryTree/BinarySplitManner.h"
#include "OpenMeshCraft/BVH/BinaryTree/BinaryTree.h"
#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "VisualizeBoxTree.h"
#include "test_utils.h"

class test_BinaryTree : public testing::Test
{
protected:
	using index_t = OMC::index_t;
	using APAC    = OMC::APAC;

	class BinarySplitPred
	{
	public:
		template <typename BinaryTree, typename BinaryNode>
		bool operator()(OMC_UNUSED const BinaryTree &tree, const BinaryNode &node)
		{
			return node.size() > 50;
		}
	};

	class BinaryShapeRefinePred2D
	{
	public:
		template <typename BinaryTree, typename BinaryNode>
		bool operator()(const BinaryTree &tree, const BinaryNode &node,
		                std::array<bool, 3> &partitionable)
		{
			auto diag_length =
			  (tree.box().max_bound() - tree.box().min_bound()).length();
			auto node_length = node.box().max_bound() - node.box().min_bound();
			partitionable[0] = node_length[0] > 0.05 * diag_length;
			partitionable[1] = node_length[1] > 0.05 * diag_length;
			return partitionable[0] || partitionable[1];
		}
	};

	class BinaryShapeRefinePred3D
	{
	public:
		template <typename BinaryTree, typename BinaryNode>
		bool operator()(const BinaryTree &tree, const BinaryNode &node,
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

	class BinaryTraits2D
	{
	public:
		static constexpr size_t Dimension = 2;
		static constexpr size_t MaxDepth  = 32;

		using NT    = APAC::NT;
		using BboxT = APAC::BoundingBox2;

		using SplitPred       = BinarySplitPred;
		using SplitManner     = OMC::BinarySplitManner;
		using ShapeRefinePred = BinaryShapeRefinePred2D;
		using DoIntersect     = APAC::DoIntersect;
		using CalcBbox        = APAC::CalcBoundingBox2;
	};

	using Tree2D = OMC::BinaryTree<OMC::BinaryAutoDeduceTraits<BinaryTraits2D>>;

	class BinaryTraits3D
	{
	public:
		static constexpr size_t Dimension = 3;
		static constexpr size_t MaxDepth  = 32;

		using NT    = APAC::NT;
		using BboxT = APAC::BoundingBox3;

		using SplitPred       = BinarySplitPred;
		using SplitManner     = OMC::BinarySplitManner;
		using ShapeRefinePred = BinaryShapeRefinePred3D;
		using DoIntersect     = APAC::DoIntersect;
		using CalcBbox        = APAC::CalcBoundingBox3;
	};

	using Tree3D = OMC::BinaryTree<OMC::BinaryAutoDeduceTraits<BinaryTraits3D>>;

protected:
	TriPoints points;
	Triangles faces;

	void SetUp() override
	{
		TEST_GET_CONFIG(BinaryTree, SetUp);
		std::string filename = config.get<std::string>("filename");

		IOOptions io_options;
		io_options.vertex_has_point = true;

		read_mesh(filename, points, faces, io_options);
	}

	void TearDown() override {}
};

TEST_F(test_BinaryTree, Construct2D)
{
	TEST_OUTPUT_DIRECTORY(BinaryTree, Construct2D);

	Tree2D                       tree;
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
	visualizeBoxTree2D<Tree2D>(tree, outdir + "tree.obj");
}

TEST_F(test_BinaryTree, Construct3D)
{
	TEST_OUTPUT_DIRECTORY(BinaryTree, Construct3D);

	Tree3D                       tree;
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
	visualizeBoxTree3D<Tree3D>(tree, outdir + "tree.obj");
}