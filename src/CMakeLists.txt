# ##############################################################################
# cmake settings
# ##############################################################################

cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)

# ##############################################################################
# add subdirectory/sub-projects
# ##############################################################################

add_subdirectory(OpenMeshCraft)

if(NOT DEFINED OMC_BUILD_PREDICATES_GENERATOR)
  set(OMC_BUILD_PREDICATES_GENERATOR OFF)
endif()
if(OMC_MASTER_PROJECT AND OMC_BUILD_PREDICATES_GENERATOR)
  add_subdirectory(PredicatesGenerator)
endif()
