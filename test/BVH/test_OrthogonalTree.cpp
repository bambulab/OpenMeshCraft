#include "OpenMeshCraft/BVH/OrthogonalTree/OcTree.h"
#include "OpenMeshCraft/BVH/OrthogonalTree/QuadTree.h"
#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "VisualizeBoxTree.h"
#include "test_utils.h"

class test_OrthogonalTree : public testing::Test
{
protected:
	using index_t = OMC::index_t;
	using APAC    = OMC::APAC;

	class OrthogonalSplitPred
	{
	public:
		template <typename OrthTree, typename OrthNode>
		bool operator()(OMC_UNUSED const OrthTree &tree, const OrthNode &node)
		{
			return node.size() > 1000;
		}
	};

	class QuadTreeTraits
	{
	public:
		static constexpr size_t Dimension      = 2;
		static constexpr size_t MaxDepth       = 8;
		static constexpr bool   EnableVertices = true;

		using NT    = APAC::NT;
		using BboxT = APAC::BoundingBox2;

		struct VA
		{
			APAC::Point2 closest_p;
			double       dis;
		};
		using VertexAttrT = VA;

		using SplitPred   = OrthogonalSplitPred;
		using DoIntersect = APAC::DoIntersect;
		using CalcBbox    = APAC::CalcBoundingBox2;
	};

	using QuadTree = OMC::QuadTree<OMC::OrthAutoDeduceTraits<QuadTreeTraits>>;

	class OcTreeTraits
	{
	public:
		static constexpr size_t Dimension      = 3;
		static constexpr size_t MaxDepth       = 8;
		static constexpr bool   EnableGrade    = true;
		static constexpr bool   EnableVertices = true;

		using NT    = APAC::NT;
		using BboxT = APAC::BoundingBox3;

		struct VA
		{
			APAC::Point3 closest_p;
			double       dis;
		};
		using VertexAttrT = VA;

		using SplitPred   = OrthogonalSplitPred;
		using DoIntersect = APAC::DoIntersect;
		using CalcBbox    = APAC::CalcBoundingBox3;
	};

	using OcTree = OMC::OcTree<OMC::OrthAutoDeduceTraits<OcTreeTraits>>;

protected:
	TriPoints points;
	Triangles faces;

	void SetUp() override
	{
		TEST_GET_CONFIG(OrthogonalTree, SetUp);
		std::string filename = config.get<std::string>("filename");
		IOOptions   io_options;
		io_options.vertex_has_point = true;

		read_mesh(filename, points, faces, io_options);
	}

	void TearDown() override {}
};

TEST_F(test_OrthogonalTree, ConstructQuadTree)
{
	TEST_OUTPUT_DIRECTORY(OrthogonalTree, ConstructQuadTree);

	QuadTree tree;

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
	tree.construct(true, 1.5, 64);

	// visualize tree and save
	visualizeBoxTree2D<QuadTree>(tree, outdir + "quadtree.obj");
}

TEST_F(test_OrthogonalTree, ConstructOcTree)
{
	TEST_OUTPUT_DIRECTORY(OrthogonalTree, ConstructOcTree);

	OcTree tree;

	std::vector<index_t>         indices;
	std::vector<APAC::Triangle3> triangles;

	for (const auto &f : faces)
	{
		triangles.push_back(
		  APAC::Triangle3(points[f[0]], points[f[1]], points[f[2]]));
		indices.push_back(indices.size());
	}

	tree.insert_primitives(triangles, indices);
	tree.construct(true, 1.5, 64);

	// visualize tree and save
	visualizeBoxTree3D<OcTree>(tree, outdir + "octree.obj");
}

TEST_F(test_OrthogonalTree, OcTreeVertex)
{
	TEST_OUTPUT_DIRECTORY(OrthogonalTree, OcTreeVertex);

	OcTree tree;

	std::vector<index_t>         indices;
	std::vector<APAC::Triangle3> triangles;

	for (const auto &f : faces)
	{
		triangles.push_back(
		  APAC::Triangle3(points[f[0]], points[f[1]], points[f[2]]));
		indices.push_back(indices.size());
	}

	tree.insert_primitives(triangles, indices);
	tree.construct(true, 1.5, 64);

	// find closest point for each vertex and save them as mesh to visualize.
	for (auto &v : tree.vertices())
	{
		v.attribute().dis = DBL_MAX;
	}

	std::queue<index_t> nodes_to_traverse;
	nodes_to_traverse.push(tree.root_node_idx());
	while (!nodes_to_traverse.empty())
	{
		index_t         cur_node_idx = nodes_to_traverse.front();
		OcTree::NodeRef cur_node     = tree.node(cur_node_idx);
		nodes_to_traverse.pop();

		if (cur_node.is_leaf())
		{
			for (index_t i = 0; i < OcTree::Degree; i++)
			{
				const APAC::Point3 &vp = tree.vertex(cur_node.vertex(i)).position();
				for (auto it : cur_node.boxes())
				{
					index_t fid = it->id();
					for (index_t j = 0; j < 3; j++)
					{
						double dis = (points[faces[fid][j]] - vp).length();
						if (dis < tree.vertex(cur_node.vertex(i)).attribute().dis)
						{
							tree.vertex(cur_node.vertex(i)).attribute().dis = dis;
							tree.vertex(cur_node.vertex(i)).attribute().closest_p =
							  points[faces[fid][j]];
						}
					}
				}
			}
		}

		if (!cur_node.is_leaf())
		{
			// process each of its children
			for (index_t i = 0; i < OcTree::Degree; ++i)
				nodes_to_traverse.push(cur_node.child(i));
		}
	}

	// visualize and save
	IOOptions io_options;
	io_options.vertex_has_point = true;
	OBJWriter obj_writer;
	obj_writer.clear();
	for (auto v : tree.vertices())
	{
		if (v.attribute().dis < DBL_MAX)
		{
			index_t v0 = obj_writer.m_points.size();
			obj_writer.m_points.push_back(v.position());
			index_t v1 = obj_writer.m_points.size();
			obj_writer.m_points.push_back(v.attribute().closest_p);
			index_t v2 = obj_writer.m_points.size();
			obj_writer.m_points.push_back(
			  (v.position() + v.attribute().closest_p.as_vec()) * 0.5);
			obj_writer.m_triangles.emplace_back(v0, v1, v2);
		}
	}

	obj_writer.write(outdir + "vertices.obj", io_options, 10);
}