#include "OpenMeshCraft/BVH/AdaptiveOrthTree/AdapOcTree.h"
#include "OpenMeshCraft/BVH/AdaptiveOrthTree/AdapQuadTree.h"
#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

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
	TriPoints out_points;
	Triangles out_faces;

	std::queue<index_t> nodes_to_traverse;
	nodes_to_traverse.push(tree.root_node_idx());

	out_points.clear();
	out_faces.clear();

	while (!nodes_to_traverse.empty())
	{
		index_t            cur_node_idx = nodes_to_traverse.front();
		QuadTree::NodeCRef cur_node     = tree.node(cur_node_idx);
		nodes_to_traverse.pop();

		if (!cur_node.is_leaf())
		{
			// process each of its children
			for (index_t i = 0; i < cur_node.children_size(); ++i)
				nodes_to_traverse.push(cur_node.child(i));
			continue;
		}

		APAC::Point2 minb = cur_node.box().min_bound();
		APAC::Point2 maxb = cur_node.box().max_bound();

		//            xy
		APAC::Point3 p00(minb.x(), minb.y(), 0.0);
		APAC::Point3 p11(maxb.x(), maxb.y(), 0.0);
		APAC::Point3 p01 = p00, p10 = p00;
		p01.x() = p11.x();
		p10.y() = p11.y();

		index_t v00 = out_points.size();
		out_points.push_back(p00);
		index_t v01 = out_points.size();
		out_points.push_back(p01);
		index_t v10 = out_points.size();
		out_points.push_back(p10);
		index_t v11 = out_points.size();
		out_points.push_back(p11);

		out_faces.emplace_back(v00, v01, out_points.size());
		out_points.push_back((p00 + p01) * 0.5);
		out_faces.emplace_back(v00, v10, out_points.size());
		out_points.push_back((p00 + p10) * 0.5);
		out_faces.emplace_back(v01, v11, out_points.size());
		out_points.push_back((p01 + p11.as_vec()) * 0.5);
		out_faces.emplace_back(v10, v11, out_points.size());
		out_points.push_back((p10 + p11.as_vec()) * 0.5);
	}
	IOOptions io_options;
	io_options.vertex_has_point = true;
	write_mesh(outdir + "quadtree.obj", out_points, out_faces, io_options);
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
	TriPoints out_points;
	Triangles out_faces;

	std::queue<index_t> nodes_to_traverse;
	nodes_to_traverse.push(tree.root_node_idx());

	out_points.clear();
	out_faces.clear();

	while (!nodes_to_traverse.empty())
	{
		index_t          cur_node_idx = nodes_to_traverse.front();
		OcTree::NodeCRef cur_node     = tree.node(cur_node_idx);
		nodes_to_traverse.pop();

		if (!cur_node.is_leaf())
		{
			// process each of its children
			for (index_t i = 0; i < cur_node.children_size(); ++i)
				nodes_to_traverse.push(cur_node.child(i));
			continue;
		}

		//            xyz
		APAC::Point3 p000 = cur_node.box().min_bound();
		APAC::Point3 p111 = cur_node.box().max_bound();
		APAC::Point3 p001 = p000, p010 = p000, p011 = p111, p100 = p000,
		             p101 = p111, p110 = p111;
		p001.z() = p111.z();
		p010.y() = p111.y();
		p011.x() = p000.x();
		p100.x() = p111.x();
		p101.y() = p000.y();
		p110.z() = p000.z();

		index_t v000 = out_points.size();
		out_points.push_back(p000);
		index_t v001 = out_points.size();
		out_points.push_back(p001);
		index_t v010 = out_points.size();
		out_points.push_back(p010);
		index_t v011 = out_points.size();
		out_points.push_back(p011);
		index_t v100 = out_points.size();
		out_points.push_back(p100);
		index_t v101 = out_points.size();
		out_points.push_back(p101);
		index_t v110 = out_points.size();
		out_points.push_back(p110);
		index_t v111 = out_points.size();
		out_points.push_back(p111);

		out_faces.emplace_back(v000, v100, out_points.size());
		out_points.push_back((p000 + p100.as_vec()) * 0.5);
		out_faces.emplace_back(v000, v010, out_points.size());
		out_points.push_back((p000 + p010.as_vec()) * 0.5);
		out_faces.emplace_back(v000, v001, out_points.size());
		out_points.push_back((p000 + p001.as_vec()) * 0.5);
		out_faces.emplace_back(v100, v110, out_points.size());
		out_points.push_back((p100 + p110.as_vec()) * 0.5);
		out_faces.emplace_back(v100, v101, out_points.size());
		out_points.push_back((p100 + p101.as_vec()) * 0.5);
		out_faces.emplace_back(v010, v110, out_points.size());
		out_points.push_back((p010 + p110.as_vec()) * 0.5);
		out_faces.emplace_back(v010, v011, out_points.size());
		out_points.push_back((p010 + p011.as_vec()) * 0.5);
		out_faces.emplace_back(v110, v111, out_points.size());
		out_points.push_back((p110 + p111.as_vec()) * 0.5);
		out_faces.emplace_back(v001, v101, out_points.size());
		out_points.push_back((p001 + p101.as_vec()) * 0.5);
		out_faces.emplace_back(v001, v011, out_points.size());
		out_points.push_back((p001 + p011.as_vec()) * 0.5);
		out_faces.emplace_back(v101, v111, out_points.size());
		out_points.push_back((p101 + p111.as_vec()) * 0.5);
		out_faces.emplace_back(v011, v111, out_points.size());
		out_points.push_back((p011 + p111.as_vec()) * 0.5);
	}
	IOOptions io_options;
	io_options.vertex_has_point = true;
	write_mesh(outdir + "octree.obj", out_points, out_faces, io_options);
}