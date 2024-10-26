#pragma once

#include "VTKWriter.h"

namespace OMC {

template <typename Traits>
bool VTKWriter<Traits>::write(const std::string &filename, IOOptions &opt,
                              std::streamsize precision)
{
	std::fstream out(filename.c_str(), std::ios_base::out);

	OMC_THROW_INVALID_ARGUMENT_IF(!out, "[VTKWriter] : cannot open file {}",
	                              filename);

	user_options = opt;

	// Set precision on output stream. The default is set via IOManager and passed
	// through to all writers.
	out.precision(precision);

	// Set fixed output to avoid problems with programs not reading scientific
	// notation correctly
	out << std::fixed;

#if 0
	// check for unsupported writer features
	if ()
	{
		OMC_THROW_NOT_IMPLEMENTED();
	}
#endif

	{
#if defined(WIN32)
		std::string::size_type dotposition = filename.find_last_of("\\/");
#else
		std::string::size_type dotposition = filename.rfind("/");
#endif

		if (dotposition == std::string::npos)
		{
			path     = "./";
			vtk_name = filename;
		}
		else
		{
			path     = filename.substr(0, dotposition + 1);
			vtk_name = filename.substr(dotposition + 1);
		}

		// remove the file extension
		dotposition = vtk_name.find_last_of(".");

		if (dotposition != std::string::npos)
			vtk_name = vtk_name.substr(0, dotposition);
	}

	bool result = save_to_stream(out);

	out.close();
	return result;
}

template <typename Traits>
void VTKWriter<Traits>::clear()
{
	m_points.clear();
	m_tetrahedra.clear();
}

template <typename Traits>
bool VTKWriter<Traits>::save_to_stream(std::ostream &out)
{
	bool write_vertex_point = user_options.vertex_has_point && !m_points.empty();

	// header
	out << "# vtk DataFile Version 2.0\n";
	out << vtk_name << ", Created by OpenMeshCraft\n";
	out << "ASCII\n";
	out << "DATASET UNSTRUCTURED_GRID\n";

	// vertex data (point)
	out << "POINTS " << m_points.size() << " double\n";
	for (size_t i = 0; i < m_points.size(); ++i)
	{
		if (write_vertex_point)
		{
			const PointT &v = m_points[i];
			out << v[0] << " " << v[1] << " " << v[2] << '\n';
		}
		else
		{
			out << "v 0 0 0" << '\n'; // avoid generate invalid vtk files
		}
	}

	// m_tetrahedra (indices starting at 0)
	out << "CELLS " << m_tetrahedra.size() << " " << 5 * m_tetrahedra.size()
	    << '\n';
	for (size_t i = 0; i < m_tetrahedra.size(); ++i)
	{
		const Tetrahedron &t = m_tetrahedra[i];
		out << "4 " << t[0] << " " << t[1] << " " << t[2] << " " << t[3] << '\n';
	}

  // cell types
  out << "CELL_TYPES " << m_tetrahedra.size() << '\n';
	for (size_t i = 0; i < m_tetrahedra.size(); ++i)
	{
    out << "10\n"; // VTK_TETRA
  }

	return true;
}

} // namespace OMC