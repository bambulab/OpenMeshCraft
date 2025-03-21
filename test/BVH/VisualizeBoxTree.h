#pragma once

#include "OpenMeshCraft/Geometry/ApproxPredicatesApproxConstructions.h"

#include "test_utils.h"

#include <queue>

template <typename TreeT>
inline void visualizeBoxTree2D(const TreeT &tree, const std::string &filename)
{
	using APAC = OMC::APAC;
	TriPoints out_points;
	Triangles out_faces;

	std::queue<index_t> nodes_to_traverse;
	nodes_to_traverse.push(tree.root_node_idx());

	while (!nodes_to_traverse.empty())
	{
		index_t                  cur_node_idx = nodes_to_traverse.front();
		typename TreeT::NodeCRef cur_node     = tree.node(cur_node_idx);
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
		out_faces.emplace_back(v01, v11, out_points.size());
		out_points.push_back((p01 + p11) * 0.5);
		out_faces.emplace_back(v00, v10, out_points.size());
		out_points.push_back((p00 + p10) * 0.5);
		out_faces.emplace_back(v10, v11, out_points.size());
		out_points.push_back((p10 + p11) * 0.5);
	}
	IOOptions io_options;
	io_options.vertex_has_point = true;
	write_mesh(filename, out_points, out_faces, io_options);
}

template <typename TreeT>
inline void visualizeBoxTree3D(const TreeT &tree, const std::string &filename)
{
	using APAC = OMC::APAC;
	// visualize tree and save
	TriPoints out_points;
	Triangles out_faces;

	std::queue<index_t> nodes_to_traverse;
	nodes_to_traverse.push(tree.root_node_idx());

	while (!nodes_to_traverse.empty())
	{
		index_t                  cur_node_idx = nodes_to_traverse.front();
		typename TreeT::NodeCRef cur_node     = tree.node(cur_node_idx);
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
	}
	IOOptions io_options;
	io_options.vertex_has_point = true;
	write_mesh(filename, out_points, out_faces, io_options);
}