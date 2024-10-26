// Kernel
#include "OpenMeshCraft/Geometry/ExactIndirectPredicatesApproxConstructions.h"
// Tetrahedra soup traits
#include "OpenMeshCraft/Mesh/TetSoup.h"
// Constrained Delaunay Tetrahedralization (CDT)
#include "OpenMeshCraft/ConstrDelTet/CDT.h"

#include "test_utils.h"

/*
 * All tests about CDT are put here,
 * until it's better to separate tests :D.
 */

class test_ConstrDelTet : public testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

protected:
	using index_t       = OMC::index_t;
	using EIAC          = OMC::EIAC;
	using TriSoupTraits = OMC::TriSoupTraits;
	using TetSoupTraits = OMC::TetSoupTraits;

	using Points     = typename TriSoupTraits::Points;
	using Triangles  = typename TriSoupTraits::Triangles;
	using Tetrahedra = typename TetSoupTraits::Tetrahedra;

	using CDT       = OMC::ConstrDelTet<EIAC, TetSoupTraits>;
	using CDTConfig = OMC::ConstrDelTet_Config;
	using CDTStats  = OMC::ConstrDelTet_Stats;
};

/**
 * @brief check if it will crash.
 */
TEST_F(test_ConstrDelTet, TestIfCrash)
{
	TEST_OUTPUT_DIRECTORY(ConstrDelTet, TestIfCrash);
	TEST_GET_CONFIG(ConstrDelTet, TestIfCrash);

	// Define IO
	IOOptions io_options;
	io_options.vertex_has_point = true;

	// Define mesh
	Points     input_points, result_points;
	Triangles  input_triangles;
	Tetrahedra result_tetrahedra;

	// read mesh
	std::string dir      = config.get<std::string>("dir");
	std::string filename = config.get<std::string>("filename");

	read_mesh(dir + filename, input_points, input_triangles, io_options);

	// configure
	CDTConfig cdt_cfg;
	cdt_cfg.verbose                = config.get<bool>("verbose");
	cdt_cfg.output_explicit_result = config.get<bool>("explicit");

	tbb::global_control tbb_gc(
	  tbb::global_control::max_allowed_parallelism,
	  config.get<size_t>("thread_num", tbb::this_task_arena::max_concurrency()));

	auto start = OMC::Logger::elapse_reset();

	CDT cdt;

	cdt.addTriMeshAsInput(input_points, input_triangles);
	cdt.setTetMeshAsOutput(result_points, result_tetrahedra);
	cdt.setConfig(cdt_cfg);
	cdt.CDT();

	std::cout << std::format(
	  "constrained Delaunay tetrahedralization uses {} s\n",
	  OMC::Logger::elapsed(start).count());
	std::cout << std::format("result vertices {} result tetrahedra {}\n",
	                         result_points.size(), result_tetrahedra.size());

	if (config.get<bool>("write"))
	{
		// The desired extension
		std::string extension    = ".vtk";
		// Extract the file stem (filename without extension)
		std::string file_stem    = std::filesystem::path(filename).stem().string();
		// Create the new filename with the desired extension
		std::string new_filename = file_stem + extension;
		// Write the mesh
		write_mesh(outdir + new_filename, result_points, result_tetrahedra,
		           io_options);
	}
}

/**
 * @brief Test CDT on datasets to check if it will crash.
 */
TEST_F(test_ConstrDelTet, TestDataSet)
{
	TEST_OUTPUT_DIRECTORY(ConstrDelTet, TestDataSet);
	TEST_GET_CONFIG(ConstrDelTet, TestDataSet);

	// Define IO options for reading mesh
	OMC::IOOptions io_options;
	io_options.vertex_has_point = true;

	// Define containers for mesh data
	Points     input_points, result_points;
	Triangles  input_triangles;
	Tetrahedra result_tetrahedra;

	// Open log file for writing statistics
	std::string  log_path = outdir + "stats.txt";
	std::fstream log_file;
	log_file.open(log_path, std::ios::out | std::ios::app);
	log_file << "filename,time\n";

	// Read models' directory from configuration
	std::string           models_dir = config.get<std::string>("models_dir");
	std::filesystem::path model_dir_path(models_dir);
	std::filesystem::directory_iterator endIter;

	// Read CDT configuration from configuration file
	CDTConfig cdt_cfg;
	cdt_cfg.verbose                = config.get<bool>("verbose");
	cdt_cfg.output_explicit_result = config.get<bool>("explicit");

	// Read additional parameters if set in configuration
	bool set_parameter = config.get<bool>("set_parameter", false);
	if (set_parameter)
	{
		[[maybe_unused]] boost::property_tree::ptree &parameters =
		  config.get_child("parameters");
	}

	// Set the number of threads for parallel processing
	tbb::global_control tbb_gc(
	  tbb::global_control::max_allowed_parallelism,
	  config.get<size_t>("thread_num", tbb::this_task_arena::max_concurrency()));

	// Read models from directory and process each file
	size_t skip_step   = config.get<size_t>("skip_step", 0);
	size_t process_cnt = 0;
	for (std::filesystem::directory_iterator iter(model_dir_path);
	     iter != endIter; iter++)
	{
		if (std::filesystem::is_directory(*iter))
		{
			// Skip directories
			continue;
		}
		else
		{
			process_cnt += 1;
			if (skip_step != 0 && process_cnt % skip_step != 0)
				continue;

			std::cout << "processing " << iter->path().filename().string()
			          << std::endl;

			// Read mesh from file
			read_mesh(iter->path().string(), input_points, input_triangles,
			          io_options);

			// Initialize CDT and set input/output
			CDT cdt;
			cdt.addTriMeshAsInput(input_points, input_triangles);
			cdt.setTetMeshAsOutput(result_points, result_tetrahedra);
			cdt.setConfig(cdt_cfg);

			// Get CDT statistics
			CDTStats stats = cdt.stats();

			// Start timer
			auto start = OMC::Logger::elapse_reset();

			// Perform constrained Delaunay tetrahedralization
			cdt.CDT();

			// Calculate elapsed time
			double total_time = OMC::Logger::elapsed(start).count();
			std::cout << total_time << " s\n";

			// Log the filename and processing time
			log_file << std::fixed;
			log_file << iter->path().filename().string();
			log_file << "," << total_time << std::endl;
		}
	}
	// Close the log file
	log_file.close();
}
