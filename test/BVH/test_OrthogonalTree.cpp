#include "OpenMeshCraft/BVH/OrthogonalTree/OcTree.h"
#include "OpenMeshCraft/BVH/OrthogonalTree/QuadTree.h"
#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

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
	static constexpr double dupl_thres = 2.5;

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
	tree.construct(true, 1.5, dupl_thres, 64);

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

		APAC::Point2 center_2           = tree.node_center(cur_node);
		APAC::Point2 half_side_length_2 = tree.node_side_length(cur_node) * 0.5;

		APAC::Point3 center(center_2.x(), center_2.y(), 0.);
		APAC::Point3 half_side_length(half_side_length_2.x(),
		                              half_side_length_2.y(), 0.);

		//            xy
		APAC::Point3 p00 = center - half_side_length;
		APAC::Point3 p11 = center + half_side_length;
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
		out_faces.emplace_back(v01, v11, out_points.size());
		out_points.push_back((p01 + p11) * 0.5);
		out_faces.emplace_back(v00, v10, out_points.size());
		out_points.push_back((p00 + p10) * 0.5);
		out_faces.emplace_back(v10, v11, out_points.size());
		out_points.push_back((p10 + p11) * 0.5);

		if (!cur_node.is_leaf())
		{
			// process each of its children
			for (index_t i = 0; i < QuadTree::Degree; ++i)
				nodes_to_traverse.push(cur_node.child(i));
		}
	}
	IOOptions io_options;
	io_options.vertex_has_point = true;
	write_mesh(outdir + "quadtree.obj", out_points, out_faces, io_options);
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
	tree.construct(true, 1.5, dupl_thres, 64);

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

		APAC::Point3 center           = tree.node_center(cur_node);
		APAC::Point3 half_side_length = tree.node_side_length(cur_node) * 0.5;

		//            xyz
		APAC::Point3 p000 = center - half_side_length;
		APAC::Point3 p111 = center + half_side_length;
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
		out_points.push_back((p000 + p100) * 0.5);
		out_faces.emplace_back(v000, v010, out_points.size());
		out_points.push_back((p000 + p010) * 0.5);
		out_faces.emplace_back(v000, v001, out_points.size());
		out_points.push_back((p000 + p001) * 0.5);
		out_faces.emplace_back(v100, v110, out_points.size());
		out_points.push_back((p100 + p110) * 0.5);
		out_faces.emplace_back(v100, v101, out_points.size());
		out_points.push_back((p100 + p101) * 0.5);
		out_faces.emplace_back(v010, v110, out_points.size());
		out_points.push_back((p010 + p110) * 0.5);
		out_faces.emplace_back(v010, v011, out_points.size());
		out_points.push_back((p010 + p011) * 0.5);
		out_faces.emplace_back(v110, v111, out_points.size());
		out_points.push_back((p110 + p111) * 0.5);
		out_faces.emplace_back(v001, v101, out_points.size());
		out_points.push_back((p001 + p101) * 0.5);
		out_faces.emplace_back(v001, v011, out_points.size());
		out_points.push_back((p001 + p011) * 0.5);
		out_faces.emplace_back(v101, v111, out_points.size());
		out_points.push_back((p101 + p111) * 0.5);
		out_faces.emplace_back(v011, v111, out_points.size());
		out_points.push_back((p011 + p111) * 0.5);

		if (!cur_node.is_leaf())
		{
			// process each of its children
			for (index_t i = 0; i < OcTree::Degree; ++i)
				nodes_to_traverse.push(cur_node.child(i));
		}
	}
	IOOptions io_options;
	io_options.vertex_has_point = true;
	write_mesh(outdir + "octree.obj", out_points, out_faces, io_options);
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
	tree.construct(true, 1.5, dupl_thres, 64);

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

		APAC::Point3 center = tree.node_center(cur_node);

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