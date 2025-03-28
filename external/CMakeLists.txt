# GMP ##########################################################################
# ##############################################################################
# The target GMP can be linked to other targets.

# set dir to variable, it will be used by find_package()
if(CMAKE_HOST_WIN32)
  set(GMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gmp/windows")
  list(APPEND CMAKE_PREFIX_PATH
       "${CMAKE_CURRENT_SOURCE_DIR}/gmp/windows/lib/cmake")
elseif(CMAKE_HOST_UNIX)
  set(GMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gmp/unix")
  list(APPEND CMAKE_PREFIX_PATH
       "${CMAKE_CURRENT_SOURCE_DIR}/gmp/unix/lib/cmake")
else()
  message(FATAL_ERROR "[OpenMeshCraft] Unsupported host for GMP:"
                      "${CMAKE_HOST_SYSTEM_NAME}.")
endif()

if(NOT GMP_FOUND AND NOT TARGET GMP)

  # find GMP and create target GMP
  find_package(GMP REQUIRED NO_MODULE)

  if(TARGET GMP) # if found, set GMP_FOUND to TRUE
    set(GMP_FOUND
        TRUE
        CACHE BOOL "Set GMP as found")
    message(STATUS "[OpenMeshCraft] Found GMP and create target GMP.")
  else() # if not found, report error
    message(FATAL_ERROR "[OpenMeshCraft] GMP target not found.")
  endif()

elseif(GMP_FOUND AND NOT TARGET GMP)

  # GMP already found, create target GMP
  message(STATUS "[OpenMeshCraft] GMP already found. Create imported target.")
  message(STATUS "     GMP_INCLUDE_DIR: ${GMP_INCLUDE_DIR}")
  message(STATUS "     GMP_LIBRARIES: ${GMP_LIBRARIES}")
  message(STATUS "     GMP_SHARED_LIBRARIES: ${GMP_SHARED_LIBRARIES}")

  add_library(GMP SHARED IMPORTED GLOBAL)
  set_target_properties(
    GMP
    PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
               IMPORTED_LOCATION "${GMP_SHARED_LIBRARIES}"
               IMPORTED_IMPLIB "${GMP_LIBRARIES}")

endif() # GMP_FOUND

# MPFR #########################################################################
# ##############################################################################
# Target MPFR can be linked to other targets.

# set dir to variable, it will be used by find_package()
if(CMAKE_HOST_WIN32)
  set(MPFR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mpfr/windows")
  list(APPEND CMAKE_PREFIX_PATH
       "${CMAKE_CURRENT_SOURCE_DIR}/mpfr/windows/lib/cmake")
elseif(CMAKE_HOST_UNIX)
  set(MPFR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mpfr/unix")
  list(APPEND CMAKE_PREFIX_PATH
       "${CMAKE_CURRENT_SOURCE_DIR}/mpfr/unix/lib/cmake")
else()
  message(FATAL_ERROR "[OpenMeshCraft] Unsupported host for MPFR:"
                      "${CMAKE_HOST_SYSTEM_NAME}.")
endif()

if(NOT MPFR_FOUND AND NOT TARGET MPFR)

  # find MPFR and create target MPFR
  find_package(MPFR REQUIRED NO_MODULE)

  if(TARGET MPFR) # if found, set MPFR_FOUND to TRUE
    set(MPFR_FOUND
        TRUE
        CACHE BOOL "Set MPFR as found")
    message(STATUS "[OpenMeshCraft] Found MPFR and create target MPFR.")
  else() # if not found, report error
    message(FATAL_ERROR "[OpenMeshCraft] MPFR target not found.")
  endif()

elseif(MPFR_FOUND AND NOT TARGET MPFR)

  # MPFR already found, create target MPFR
  message(STATUS "[OpenMeshCraft] MPFR already found. Create imported target.")
  message(STATUS "     MPFR_INCLUDE_DIR: ${MPFR_INCLUDE_DIR}")
  message(STATUS "     MPFR_LIBRARIES: ${MPFR_LIBRARIES}")
  message(STATUS "     MPFR_SHARED_LIBRARIES: ${MPFR_SHARED_LIBRARIES}")

  add_library(MPFR SHARED IMPORTED GLOBAL)
  set_target_properties(
    MPFR
    PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${MPFR_INCLUDE_DIR}"
               IMPORTED_LOCATION "${MPFR_SHARED_LIBRARIES}"
               IMPORTED_IMPLIB "${MPFR_LIBRARIES}")

endif() # MPFR_FOUND

# CGAL #########################################################################
# ##############################################################################
# The target CGAL::CGAL can be linked to other targets.

if(OMC_BUILD_TEST)
  # CGAL is required for test

  if(NOT CGAL_FOUND) # CGAL not found

    # CGAL_DIR will be used by find_pacakge(CGAL ...)
    set(CGAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cgal)

    # find boost before finding CGAL
    set(Boost_DEBUG OFF)
    set(Boost_NO_WARN_NEW_VERSIONS ON)
    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost 1.78.0 CONFIG REQUIRED)

    # find CGAL. This procedure should be executed after finding boost.
    set(CGAL_Boost_USE_STATIC_LIBS ON)
    find_package(CGAL)
    if(CGAL_FOUND)
      message(STATUS "[OpenMeshCraft] Found CGAL.")
    else()
      message(FATAL_ERROR "[OpenMeshCraft] Can't find CGAL.")
    endif()

  elseif(NOT TARGET CGAL::CGAL) # CGAL found but target does not exists

    message(STATUS "[OpenMeshCraft] CGAL already found.")
    message(STATUS "     CGAL_INCLUDE_DIRS: ${CGAL_INCLUDE_DIRS}")
    message(STATUS "     CGAL_LIBRARIES: ${CGAL_LIBRARIES}")
    # create imported target CGAL::CGAL
    add_library(CGAL::CGAL INTERFACE IMPORTED GLOBAL)
    set_target_properties(
      CGAL PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CGAL_INCLUDE_DIR}"
                      IMPORTED_IMPLIB "${CGAL_LIBRARIES}")

  else() # CGAL found and target exists

    message(
      STATUS "[OpenMeshCraft] CGAL already found and target CGAL::CGAL exists.")

  endif() # CGAL_FOUND

endif() # OMC_BUILD_TEST

# Eigen ########################################################################
# ##############################################################################
# Header-only library, set EIGEN3_INCLUDE_DIR for further find_package. We also
# add its FindEigen3.cmake to module path. If an installed shared Eigen3 lib is
# provided, add the lib/cmake to CMAKE_PREFIX_PATH.


if (NOT EIGEN3_FOUND)

  # find eigen3
  set(EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/eigen)
  set(EIGEN3_FOUND TRUE CACHE BOOL "Set Eigen3 as found")
  # create target
  add_library(Eigen3 INTERFACE IMPORTED GLOBAL)
  set_target_properties(Eigen3 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                          "${EIGEN3_INCLUDE_DIR}")
  message(STATUS "[OpenMeshCraft] Eigen3 found. Create target Eigen3.")

elseif(EIGEN3_FOUND AND NOT Eigen3)

  add_library(Eigen3 INTERFACE IMPORTED GLOBAL)
  set_target_properties(Eigen3 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                          "${EIGEN3_INCLUDE_DIR}")
  message(STATUS "[OpenMeshCraft] Eigen3 found. Create target Eigen3.")

else()

  message(STATUS "[OpenMeshCraft] Eigen3 already found.")

endif() # EIGEN3_FOUND

# Google test ##################################################################
# ##############################################################################
# Target gtest_main can be linked to other targets.
#
# After linking it, run below commands:
#
# * include(GoogleTest)
# * gtest_discover_tests(YOUR_TARGET)

if(OMC_BUILD_TEST)

  if(NOT TARGET gtest_main) # gtest_main not found

    if(CMAKE_HOST_WIN32)
      set(gtest_force_shared_crt
          ON
          CACHE BOOL "")
    endif()
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest EXCLUDE_FROM_ALL)

  endif() # gtest_main

endif() # OMC_BUILD_TEST

# parallel-hashmap #############################################################
# ##############################################################################
# Target phmap can be linked to other targets.

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/parallel-hashmap EXCLUDE_FROM_ALL)

# shewchuk-predicates ##########################################################
# ##############################################################################
# A very simple C lib. Target shewchuk_predicates can be linked to other
# targets.

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/shewchuk-predicates
                 EXCLUDE_FROM_ALL)

# TBB ##########################################################################
# ##############################################################################
# Target tbb can be linked to other targets.

# cmake-format: off
set(TBB_TEST OFF CACHE BOOL "")
set(TBBMALLOC_BUILD OFF CACHE BOOL "")
# cmake-format: on

if(WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # When compile tbb by gcc (mingw64) on Windows, compiler complains a lot of
  # warnings. It's ok to compile tbb by MSVC on Windows or by gcc on Unix* OS.
  set(TBB_WARNING_SUPPRESS -Wno-stringop-overflow -Wno-unused-value
                           -Wno-array-bounds)
endif()

# always build TBB to shared lib

if(NOT BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/oneTBB EXCLUDE_FROM_ALL)
  set(BUILD_SHARED_LIBS OFF)
else()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/oneTBB EXCLUDE_FROM_ALL)
endif()

# prevent generating versioned .so files.
set_property(TARGET tbb PROPERTY VERSION)
set_property(TARGET tbb PROPERTY SOVERSION)

# Pass variabls to parent scope
set(CMAKE_PREFIX_PATH
    ${CMAKE_PREFIX_PATH}
    PARENT_SCOPE)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    PARENT_SCOPE)
