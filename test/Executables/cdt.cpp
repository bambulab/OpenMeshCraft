/**
 * @file cdt.cpp
 * @brief An independent executable file to run constrained Delaunay
 * tetrahedralization.
 */
#include <chrono>
#include <iostream>

// Kernel
#include "OpenMeshCraft/Geometry/ExactIndirectPredicatesApproxConstructions.h"
// Traits
#include "OpenMeshCraft/Mesh/TetSoup.h"
// Arrangements
#include "OpenMeshCraft/Tetrahedralization/CDT.h"

#include "test_utils.h"

using EIAC          = OMC::EIAC;
using TetSoupTraits = OMC::TetSoupTraits;

using Points     = typename TetSoupTraits::Points;
using Triangles  = typename TetSoupTraits::Triangles;
using Tetrahedra = typename TetSoupTraits::Tetrahedra;

using CDT       = OMC::ConstrDelTet<EIAC, TetSoupTraits>;
using CDTConfig = OMC::ConstrDelTet_Config;

boost::property_tree::ptree omc_test_config;

int main(int argc, char *argv[])
{
	std::string filename;
	bool        output_stats = false;

	CDTConfig cdt_config;

	auto print_help = []()
	{
		std::cout << "exe input_file -v -s -r -p=n\n"
		             "-v verbose\n"
		             "-s output stats to default file\n"
		             "-r output result model to default file\n"
		             "-p=n parallel threads number, n is an integer\n";
		exit(1);
	};

	if (argc > 1)
		filename = argv[1];
	else
		print_help();
	for (int i = 2; i < argc; i++)
	{
		std::string param(argv[i]);
		if (param == "-v")
			cdt_config.verbose = true;
		else if (param == "-s")
			output_stats = true;
		else if (param == "-r")
			cdt_config.output_explicit_result = true;
		else if (OMC::starts_with(param, "-p="))
		{
			int                 threads_num = std::stoi(param.substr(3));
			tbb::global_control tbb_gc(tbb::global_control::max_allowed_parallelism,
			                           threads_num);
		}
		else
			print_help();
	}

	// Define IO
	IOOptions io_options;
	io_options.vertex_has_point = true;
	io_options.stl_binary       = true;

	// Define mesh
	Points     input_points, result_points;
	Triangles  input_triangles;
	Tetrahedra result_tetrahedra;

	// read mesh
	read_mesh(filename, input_points, input_triangles, io_options);
	// prepare to output stats
	filename = filename.substr(filename.find_last_of("/\\") + 1);

	// set config, input and output
	CDT cdt;
	cdt.setConfig(cdt_config);
	cdt.addTriMeshAsInput(input_points, input_triangles);
	cdt.setTetMeshAsOutput(result_points, result_tetrahedra);
	// get stats
	OMC::ConstrDelTet_Stats &stats = cdt.stats();

	// run the algorithm
	auto start = OMC::Logger::elapse_reset();
	cdt.CDT();
	double time = OMC::Logger::elapsed(start).count();

	// output stats
	if (output_stats)
	{
		std::fstream fout;
		fout.open("./ours_time.txt", std::ios::out | std::ios::app);
		fout << std::fixed;
		fout << filename << "," << stats.pp_elapsed << "," << stats.dt_elapsed
		     << "," << stats.seg_elapsed << "," << stats.face_elapsed << "," << time
		     << "," << OMC::getPeakMegabytesUsed() << "," << result_points.size()
		     << "," << result_tetrahedra.size() << "," << stats.seg_steiner << "\n";
		std::cout << filename << ": " << time << "s, "
		          << OMC::getPeakMegabytesUsed() << " MB\n";
		fout.close();
	}
	// output result
	if (cdt_config.output_explicit_result)
	{
		// The desired extension
		std::string extension    = ".vtk";
		// Extract the file stem (filename without extension)
		std::string file_stem    = std::filesystem::path(filename).stem().string();
		// Create the new filename with the desired extension
		std::string new_filename = file_stem + extension;
		// Write the mesh
		write_mesh(new_filename, result_points, result_tetrahedra, io_options);
	}
	return 0;
}