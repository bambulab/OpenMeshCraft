#pragma once

#include "CDT.h"

/* Data structures of CDT */
// Tetrahedra mesh
#include "TetMesh.h"
// Piecewise linear complex
#include "PLC.h"

/* Sub-algorithms of CDT */
// Delaunay tetrahedralization
#include "DelaunayTet.h"
// Constraints recovery
#include "ConstrRecover.h"

/* Data structures, algorithms, and utils of arrangements */
#include "OpenMeshCraft/Arrangements/CleanMesh.h"
#include "OpenMeshCraft/Arrangements/Utils.h"

namespace OMC {

template <typename Kernel, typename Traits>
class ConstrDelTet<Kernel, Traits>::ConstrDelTetTraits
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

	using Segment     = typename K::Segment3;
	using Triangle    = typename K::Triangle3;
	using BoundingBox = typename K::BoundingBox3;

	using Orient2D           = typename K::Orient2D;
	using Orient3D           = typename K::Orient3D;
	using OrientOn2D         = typename K::OrientOn2D;
	using LessThan3D         = typename K::LessThan3D;
	using SquaredDistance3D  = typename K::SquaredDistance3D;
	using LongestAxis        = typename K::LongestAxis;
	using MaxCompInTriNormal = typename K::MaxCompInTriNormal;
	using InCircle           = typename K::InCircle;
	using InSphere           = typename K::InSphere;
	using DotProduct3D       = typename K::DotProductSign3D;
	using CollinearPoints3   = typename K::CollinearPoints3;

	using CalcBbox = typename K::CalcBoundingBox3;

	// clang-format off
	using DoIntersect = typename K::DoIntersect;
	using Segment3_Point3_DoIntersect        = typename K::Segment3_Point3_DoIntersect;
	using Segment3_Segment3_DoIntersect      = typename K::Segment3_Segment3_DoIntersect;
	using Triangle3_Point3_DoIntersect       = typename K::Triangle3_Point3_DoIntersect;
	using Triangle3_Segment3_DoIntersect     = typename K::Triangle3_Segment3_DoIntersect;
	using Triangle3_Triangle3_DoIntersect    = typename K::Triangle3_Triangle3_DoIntersect;
	using Tetrahedron3_Point3_DoIntersect    = typename K::Tetrahedron3_Point3_DoIntersect;
	using Tetrahedron3_Segment3_DoIntersect  = typename K::Tetrahedron3_Segment3_DoIntersect;
	using Tetrahedron3_Triangle3_DoIntersect = typename K::Tetrahedron3_Triangle3_DoIntersect;
	// clang-format on
};

/// @brief Implement class of ConstrDelTet
template <typename Traits>
class ConstrDelTet_Impl
{
public: /* Traits ************************************************************/
	// primitives
	using NT         = typename Traits::NT;
	using Vec2       = typename Traits::Vec2;
	using Vec3       = typename Traits::Vec3;
	using EPoint     = typename Traits::EPoint;
	using GPoint     = typename Traits::GPoint;
	using IPoint_SSI = typename Traits::IPoint_SSI;
	using IPoint_LNC = typename Traits::IPoint_LNC;
	using IPoint_LPI = typename Traits::IPoint_LPI;
	using IPoint_TPI = typename Traits::IPoint_TPI;

	using AsGP      = typename Traits::AsGP;
	using AsEP      = typename Traits::AsEP;
	using ToEP      = typename Traits::ToEP;
	using CreateSSI = typename Traits::CreateSSI;
	using CreateLNC = typename Traits::CreateLNC;
	using CreateLPI = typename Traits::CreateLPI;
	using CreateTPI = typename Traits::CreateTPI;

	using Segment  = typename Traits::Segment;
	using Triangle = typename Traits::Triangle;

	// predicates
	using Orient2D           = typename Traits::Orient2D;
	using Orient3D           = typename Traits::Orient3D;
	using OrientOn2D         = typename Traits::OrientOn2D;
	using LessThan3D         = typename Traits::LessThan3D;
	using CollinearPoints3   = typename Traits::CollinearPoints3;
	using MaxCompInTriNormal = typename Traits::MaxCompInTriNormal;
	using SquaredDistance3D  = typename Traits::SquaredDistance3D;
	using InCircle           = typename Traits::InCircle;
	using InSphere           = typename Traits::InSphere;

	// meshes
	using TetMesh = TetrahedralMesh<Traits>;
	// piecewise linear complex
	using PLC     = PiecewiseLinearComplex<Traits>;

public: /* Auxiliary data structures *****************************************/
	// point arena
	using PntArena = CDTPointArena<Traits>;

public: /* Constructors ******************************************************/
	ConstrDelTet_Impl(ConstrDelTet_Stats *_stats = nullptr)
	  : stats(_stats)
	{
	}

	/// @brief An interface to set varying parameters.
	void setConfig(ConstrDelTet_Config _config) { config = _config; }

public: /* Pipeline **********************************************************/
	void CDTPipeline();

	void collectCleanResults(ArrCleanMesh<Traits> &CM);

	template <typename iPoint, typename iPoints, typename iTet, typename iTets>
	void computeExplicitResult(iPoints &final_points, iTets &final_tets);

public:
	/* Input data */
	/// coordinates of all points
	std::vector<NT>      in_coords;
	/// constrained edges
	std::vector<index_t> in_edges;
	/// constrained triangles
	std::vector<index_t> in_tris;
	/// labels of all triangles
	std::vector<size_t>  in_labels;

	/* Middle data */
	/// remove erroneous edges in in_edges to get cdt_in_edges
	std::vector<index_t> cdt_in_edges;
	/// remove erroneous triangle in in_tris to get cdt_in_tris
	std::vector<index_t> cdt_in_tris;
	/// convert label id to bitset to get cdt_in_labels
	std::vector<Label>   cdt_in_labels;

	/* Output data */
	/// output vertices (pointers to points in arena)
	std::vector<GPoint *> cdt_out_verts;
	/// output tetrahedra
	std::vector<index_t>  cdt_out_tets;
	/// output labels for triangles
	ArrLabels             cdt_out_labels;

	/* Auxiliary data */
	/// information of removed duplicate triangles (maybe used again)
	std::vector<ArrDuplTriInfo> dupl_triangles;

	/* Configuration */
	ConstrDelTet_Config config;

	/* Statistics */
	ConstrDelTet_Stats *stats;

private: /* Private middle data *******************************************/
	/// Explicit points
	std::vector<EPoint>      exp_pnt;
	/// All generated points in algorithm are stored in pnt_arena
	std::vector<PntArena>    pnt_arenas;
	/// Tetrahedral mesh
	std::unique_ptr<TetMesh> tet_mesh;
	/// Piecewise linear complex
	std::unique_ptr<PLC>     plc;
};

template <typename Traits>
void ConstrDelTet_Impl<Traits>::CDTPipeline()
{
	OMC_ASSERT(!in_coords.empty() && !in_tris.empty(), "empty input.");
	OMC_ASSERT(in_tris.size() % 3 == 0, "triangle size error.");
	OMC_ASSERT(in_tris.size() / 3 == in_labels.size(),
	           "size of triangles and labels mismatche.");

	/***** Preprocessing *****/

	OMC_CDT_START_ELAPSE(start_pp);

	// clean input mesh
	ArrCleanMesh<Traits> CM(in_coords, in_tris, in_labels);
	CM.convertLabels();
	CM.mergeDuplicatedVertices();
	CM.removeDegenerateAndDuplicatedTriangles();
	CM.removeIsolatedVertices();
	collectCleanResults(CM);

	OMC_CDT_SAVE_ELAPSED(start_pp, pp_elapsed, "Preprocessing");

	/***** Delaunay tetrahedralization *****/

	tet_mesh = std::make_unique<TetMesh>(cdt_out_verts);
	DelaunayTet<Traits> DT(*tet_mesh);

	OMC_CDT_START_ELAPSE(start_dt);
	DT.tetrahedralize();
	OMC_CDT_SAVE_ELAPSED(start_dt, dt_elapsed, "Delaunay tetrahedralization");

	OMC_EXPENSIVE_ASSERT(DT.verify(),
	                     "The Delaunay tetrahedralization is incorrect.");

	/***** Constraints Recovery *****/

	pnt_arenas = std::vector<PntArena>(1);
	plc        = std::make_unique<PLC>(cdt_out_verts, cdt_in_edges, cdt_in_tris);
	ConstraintsRecover<Traits> CR(cdt_out_verts, pnt_arenas, *tet_mesh, *plc,
	                              config.verbose);

	OMC_CDT_START_ELAPSE(start_seg);
	CR.segmentRecovery();
	OMC_CDT_SAVE_ELAPSED(start_seg, seg_elapsed, "Segment recovery");

	OMC_CDT_START_ELAPSE(start_face);
	CR.faceRecovery();
	OMC_CDT_SAVE_ELAPSED(start_face, face_elapsed, "Face recovery");

	tet_mesh->markInfiniteTetsDeleted();
	tet_mesh->removeDeletedTets();
	cdt_out_tets = std::move(tet_mesh->tet_node);
}

template <typename Traits>
void ConstrDelTet_Impl<Traits>::collectCleanResults(ArrCleanMesh<Traits> &CM)
{
	// collect vertices
	cdt_out_verts.reserve(CM.out_coords.size() / 3);
	exp_pnt.reserve(CM.out_coords.size() / 3);
	for (index_t vi = 0; vi < CM.out_coords.size(); vi += 3)
		cdt_out_verts.push_back(&AsGP()(exp_pnt.emplace_back(&CM.out_coords[vi])));
	// collect triangles
	cdt_in_tris        = std::move(CM.out_tris);
	// collect labels
	cdt_in_labels      = std::move(CM.out_labels);
	cdt_out_labels.num = CM.num_labels;
	// collect info about duplicated triangles
	dupl_triangles     = std::move(CM.dupl_triangles);
}

/**
 * @brief Computes the explicit result for the constrained Delaunay
 * tetrahedralization.
 *
 * This function processes the output vertices and tetrahedra, fixes vertex
 * indices, and populates the final points and tetrahedra containers.
 *
 * @tparam Traits The traits class providing necessary types and utilities.
 * @tparam iPoint The type representing a point in the final result.
 * @tparam iPoints The container type for storing the final points.
 * @tparam iTet The type representing a tetrahedron in the final result.
 * @tparam iTets The container type for storing the final tetrahedra.
 * @param final_points The container to store the final points.
 * @param final_tets The container to store the final tetrahedra.
 */
template <typename Traits>
template <typename iPoint, typename iPoints, typename iTet, typename iTets>
void ConstrDelTet_Impl<Traits>::computeExplicitResult(iPoints &final_points,
                                                      iTets   &final_tets)
{
	// Clear the final points and tets containers
	final_points.clear();
	final_tets.clear();

	// Resize the final tets container to match the number of output tets
	final_tets.resize(cdt_out_tets.size() / 4);

	// Initialize a vertex index mapping and a counter for the number of vertices
	size_t               num_vertices = 0;
	std::vector<index_t> vertex_index(cdt_out_verts.size(), InvalidIndex);

	// Loop over the output tets and fix vertex indices
	for (index_t t_id = 0; t_id < cdt_out_tets.size(); t_id += 4)
	{
		const index_t         *tet = &cdt_out_tets[t_id];
		std::array<index_t, 4> out_tet;
		for (size_t i = 0; i < 4; i++)
		{
			index_t old_vid = tet[i];
			if (!is_valid_idx(vertex_index[old_vid]))
			{
				vertex_index[old_vid] = num_vertices++;
			}
			out_tet[i] = vertex_index[old_vid];
		}

		// Assign the fixed vertex indices to the final tets
		final_tets[t_id / 4] = iTet(out_tet[0], out_tet[1], out_tet[2], out_tet[3]);
	}

	// Resize the final points container to match the number of vertices
	final_points.resize(num_vertices);

	// Parallel loop over the output vertices to populate the final points
	tbb::parallel_for(index_t(0), cdt_out_verts.size(),
	                  [this, &vertex_index, &final_points](index_t v_id)
	                  {
		                  if (!is_valid_idx(vertex_index[v_id]))
			                  return;
		                  const GPoint *gp = cdt_out_verts[v_id];
		                  EPoint        ep = ToEP()(*gp);
		                  final_points[vertex_index[v_id]] =
		                    iPoint(ep.x(), ep.y(), ep.z());
	                  });
}

/*****************************************************************************/
/*************** Implementations of interface class **************************/
/*****************************************************************************/

template <typename Kernel, typename Traits>
ConstrDelTet<Kernel, Traits>::ConstrDelTet()
{
}

template <typename Kernel, typename Traits>
ConstrDelTet<Kernel, Traits>::~ConstrDelTet()
{
}

template <typename Kernel, typename Traits>
index_t
ConstrDelTet<Kernel, Traits>::addTriMeshAsInput(const iPoints    &points,
                                                const iTriangles &triangles)
{
	input_meshes.emplace_back();
	input_meshes.back().points    = &points;
	input_meshes.back().triangles = &triangles;
	if (input_meshes.size() == LABEL_NBIT)
		OMC_THROW_OUT_OF_RANGE("Input meshes for arrangments are too much, limit "
		                       "the number to less than {}.",
		                       LABEL_NBIT);
	return input_meshes.size() - 1;
}

template <typename Kernel, typename Traits>
void ConstrDelTet<Kernel, Traits>::setTetMeshAsOutput(iPoints     &points,
                                                      iTetrahedra &tetrahedra)
{
	output_points     = &points;
	output_tetrahedra = &tetrahedra;
}

template <typename Kernel, typename Traits>
void ConstrDelTet<Kernel, Traits>::clear()
{
	input_meshes.clear();
	output_points     = nullptr;
	output_tetrahedra = nullptr;
	m_impl            = nullptr;
}

template <typename Kernel, typename Traits>
void ConstrDelTet<Kernel, Traits>::CDT()
{
	m_impl = std::make_unique<ConstrDelTet_Impl<ConstrDelTetTraits>>(&cdt_stats);

	if (!loadMultipleMeshes()(input_meshes, m_impl->in_coords, m_impl->in_tris,
	                          m_impl->in_labels))
	{
		OMC_THROW_DOMAIN_ERROR("Empty input meshes.");
		return;
	}

	m_impl->setConfig(config);
	m_impl->CDTPipeline();

	if (config.output_explicit_result)
	{
		OMC_THROW_DOMAIN_ERROR_IF(output_points == nullptr ||
		                            output_tetrahedra == nullptr,
		                          "Output mesh is not set.");
		m_impl->template computeExplicitResult<iPoint, iPoints, iTetrahedron,
		                                       iTetrahedra>(*output_points,
		                                                    *output_tetrahedra);
		m_impl = nullptr;
	}
}

template <typename Kernel, typename Traits>
void ConstrDelTet<Kernel, Traits>::setConfig(ConstrDelTet_Config _config)
{
	config = _config;
}

template <typename Kernel, typename Traits>
ConstrDelTet_Stats &ConstrDelTet<Kernel, Traits>::stats()
{
	return cdt_stats;
}

template <typename Kernel, typename Traits>
class ConstrDelTet<Kernel, Traits>::loadMultipleMeshes
{
public:
	bool operator()(const std::vector<iTriSoup>      &input_meshes,
	                std::vector<typename Kernel::NT> &coords,
	                std::vector<index_t> &tris, std::vector<size_t> &labels)
	{
		for (size_t mesh_id = 0; mesh_id < input_meshes.size(); mesh_id++)
		{
			load(*input_meshes[mesh_id].points, *input_meshes[mesh_id].triangles,
			     mesh_id, coords, tris, labels);
		}
		return !coords.empty() && !tris.empty();
	}

private:
	template <typename Points, typename Triangles, typename NT>
	void load(const Points &points, const Triangles &triangles,
	          const size_t label, std::vector<NT> &coords,
	          std::vector<index_t> &flat_tris, std::vector<size_t> &labels)
	{
		size_t p_off = coords.size() / 3; // prev num verts
		coords.resize(coords.size() + points.size() * 3);
		tbb::parallel_for(size_t(0), points.size(),
		                  [&coords, &points, &p_off](size_t p_id)
		                  {
			                  coords[(p_off + p_id) * 3]     = points[p_id][0];
			                  coords[(p_off + p_id) * 3 + 1] = points[p_id][1];
			                  coords[(p_off + p_id) * 3 + 2] = points[p_id][2];
		                  });

		size_t t_off = flat_tris.size() / 3; // prev num tris
		flat_tris.resize(flat_tris.size() + triangles.size() * 3);
		tbb::parallel_for(
		  size_t(0), triangles.size(),
		  [&flat_tris, &triangles, &t_off, &p_off](size_t t_id)
		  {
			  flat_tris[(t_off + t_id) * 3]     = p_off + triangles[t_id][0];
			  flat_tris[(t_off + t_id) * 3 + 1] = p_off + triangles[t_id][1];
			  flat_tris[(t_off + t_id) * 3 + 2] = p_off + triangles[t_id][2];
		  });

		size_t l_off = labels.size();
		labels.resize(labels.size() + triangles.size());
		std::fill(std::execution::par_unseq, labels.begin() + l_off, labels.end(),
		          label);
	}
};

} // namespace OMC
