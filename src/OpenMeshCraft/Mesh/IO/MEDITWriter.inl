#pragma once

#include "MEDITWriter.h"

#include <fstream>

namespace OMC {

template <typename Traits>
bool MEDITWriter<Traits>::write(const std::string &filename, IOOptions &opt,
                                std::streamsize precision)
{
  std::fstream out(filename.c_str(), std::ios_base::out);

  OMC_THROW_INVALID_ARGUMENT_IF(!out, "[MEDIT Writer] : cannot open file {}",
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
      msh_name = filename;
    }
    else
    {
      path     = filename.substr(0, dotposition + 1);
      msh_name = filename.substr(dotposition + 1);
    }

    // remove the file extension
    dotposition = msh_name.find_last_of(".");

    if (dotposition != std::string::npos)
      msh_name = msh_name.substr(0, dotposition);
  }

  bool result = save_to_stream(out);

  out.close();
  return result;
}

template <typename Traits>
void MEDITWriter<Traits>::clear()
{
  m_points.clear();
  m_tetrahedra.clear();
}

template <typename Traits>
bool MEDITWriter<Traits>::save_to_stream(std::ostream &out)
{
  bool write_vertex_point = user_options.vertex_has_point && !m_points.empty();

  out << "MeshVersionFormatted 2\nDimension\n3\n";

  out << "Vertices\n" << m_points.size() << "\n";

  for (size_t i = 0; i < m_points.size(); i++)
  {
    if (write_vertex_point)
    {
      const PointT &p = m_points[i];
      out << p[0] << " " << p[1] << " " << p[2] << " 1\n";
    }
  }

  out << "Tetrahedra\n" << m_tetrahedra.size() << "\n";

  for (size_t i = 0; i < m_tetrahedra.size(); i++)
  {
    const Tetrahedron &t = m_tetrahedra[i];
    out << t[0] + 1 << " " << t[1] + 1 << " " << t[2] + 1 << " " << t[3] + 1
        << " 1\n";
  }

  return true;
}

} // namespace OMC