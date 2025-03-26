#pragma once

#include "Utils.h"

#include "OpenMeshCraft/Utils/IndexDef.h"

namespace OMC {

template <typename Traits>
class ConstrDelTet_Impl;

template <typename Kernel, typename Traits>
class ConstrDelTet
{
public: /* Traits about input data ********************************************/
  /** @brief Point type.
   * E.g., Vec3d from any library or a wrapper of it.
   */
  using iPoint       = typename Traits::PointT;
  /** @brief Triangle type. */
  using iTriangle    = typename Traits::Triangle;
  /** @brief Tetrahedron type. */
  using iTetrahedron = typename Traits::Tetrahedron;
  /** @brief Number type in PointT.
   * We also expect that PointT provides x(), y() and z().
   */
  using iNT = std::remove_reference_t<decltype(std::declval<iPoint>().x())>;
  /** @brief index type in triangle and tetrahedron */
  using iIT = std::remove_reference_t<decltype(std::declval<iTriangle>()[0])>;
  /** @brief An array that stores points for vertices.
   * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
   */
  using iPoints     = typename Traits::Points;
  /** @brief An array that stores indices of three vertices for all faces.
   * E.g., std::vector<std::array<index_t,3>> or
   * Eigen::VectorX<Eigen::Vector3i>.
   */
  using iTriangles  = typename Traits::Triangles;
  /** @brief An array that stores indices of four vertices for all cells.
   * E.g., std::vector<std::array<index_t,4>> or
   * Eigen::VectorX<Eigen::Vector4i>.
   */
  using iTetrahedra = typename Traits::Tetrahedra;

public: /* Constructors ******************************************************/
  ConstrDelTet();
  ~ConstrDelTet();

  ConstrDelTet(const ConstrDelTet &) = delete;
  ConstrDelTet(ConstrDelTet &&)      = delete;

public: /* Interfaces ********************************************************/
  /**
   * @brief Adds a triangle mesh (triangle soup) as an input.
   * @param points The points of the mesh.
   * @param triangles The triangles of the mesh.
   * @return index_t The internal index of the newly added mesh.
   * @note We only store pointers to the input; we do not store a copy.
   */
  index_t addTriMeshAsInput(const iPoints &points, const iTriangles &triangles);

  /**
   * @brief Sets the tetrahedra mesh (tetrahedra soup) as the output
   * destination.
   * @param points The points of the mesh.
   * @param tetrahedra The tetrahedra of the mesh.
   * @note We store pointers to the output and write to them without any checks.
   */
  void setTetMeshAsOutput(iPoints &points, iTetrahedra &tetrahedra);

  /// @brief Clear input meshes and output mesh.
  void clear();

  /// @brief Run the constrained Delaunay tetrahedralization.
  void CDT();

  /// @brief An interface to set configuration (including flags and parameters).
  void setConfig(ConstrDelTet_Config _config);

  ConstrDelTet_Stats &stats();

private:
  /// Input data
  struct iTriSoup
  {
    const iPoints    *points    = nullptr;
    const iTriangles *triangles = nullptr;
  };
  std::vector<iTriSoup> input_meshes;
  /// Output data
  iPoints              *output_points     = nullptr;
  iTetrahedra          *output_tetrahedra = nullptr;

  /* configuration */
  ConstrDelTet_Config config;

  /* statistics */
  ConstrDelTet_Stats cdt_stats;

private:
  class ConstrDelTetTraits;

  /// Implement class
  std::unique_ptr<ConstrDelTet_Impl<ConstrDelTetTraits>> m_impl;

  class loadMultipleMeshes;
};

} // namespace OMC

#ifdef OMC_HAS_IMPL
  #include "CDT.inl"
#endif

// Tetrahedra soup
#include "OpenMeshCraft/Mesh/TetSoup.h"
// Geometry kernel
#include "OpenMeshCraft/Geometry/ExactIndirectPredicatesApproxConstructions.h"

namespace OMC {
extern template class ConstrDelTet<EIAC, TetSoupTraits>;
}