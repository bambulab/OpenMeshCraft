#pragma once

#include "IOOptions.h"
#include "OpenMeshCraft/Mesh/TetSoup.h"

#include <string>
#include <type_traits>

namespace OMC {

/**
 * @brief Write tetrahedra soup to an VTK file.
 * @tparam Traits Traits define types for points, normals, and triangles.
 * VTK writer will define variables of these types to store results.
 */
template <typename Traits>
class VTKWriter
{
public:
	/** @brief Point type. */
	using PointT      = typename Traits::PointT;
	/** @brief Vector type. */
	using NormalT     = typename Traits::NormalT;
	/** @brief triangle. */
	using Triangle    = typename Traits::Triangle;
	/** @brief tetrahedron. */
	using Tetrahedron = typename Traits::Tetrahedron;
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using Points      = typename Traits::Points;
	/** @brief An array that stores normals. */
	using Normals     = typename Traits::Normals;
	/** @brief An array that stores indices of three vertices for all faces. */
	using Triangles   = typename Traits::Triangles;
	/** @brief An array that stores indices of four vertices for all cells. */
	using Tetrahedra  = typename Traits::Tetrahedra;

	using pn_t = std::remove_reference_t<decltype(std::declval<PointT>()[0])>;
	using nn_t = std::remove_reference_t<decltype(std::declval<NormalT>()[0])>;

public:
	/**
	 * @brief Write tetrahedra soup to file with given options and precison.
	 * @param opt Options to control which parts of tetrahedra soup are written to
	 * file.
	 * @param precision precision of floating point numbers.
	 * @return true if succeed to write the triangle soup.
	 * @note Tetrahedra soup must be stored in member variables of writer before
	 * writing.
	 */
	bool write(const std::string &filename, IOOptions &opt,
	           std::streamsize precision);

	/** @brief Clear data stored in writer */
	void clear();

	Points     m_points;     ///< point position
	Tetrahedra m_tetrahedra; ///< triangle faces

private:
	std::string get_extensions() const { return "vtk"; }

	bool save_to_stream(std::ostream &out);

private:
	std::string path, vtk_name;

	IOOptions user_options;
};

extern template class VTKWriter<TetSoupTraits>;

} // namespace OMC

#ifdef OMC_HAS_IMPL
	#include "VTKWriter.inl"
#endif