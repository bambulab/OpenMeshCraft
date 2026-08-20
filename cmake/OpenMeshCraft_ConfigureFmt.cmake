# Prefer C++20 std::format when the compiler actually provides it.
# GCC 9 / older Apple libc++ fail the check and use header-only {fmt} 10.2.1.

if(NOT DEFINED OMC_USE_STD_FORMAT)
  if(MSVC)
    set(OMC_USE_STD_FORMAT ON)
  else()
    set(OMC_USE_STD_FORMAT OFF)
  endif()
endif()

set(_OMC_HAS_STD_FORMAT OFF)
if(OMC_USE_STD_FORMAT)
  set(_OMC_HAS_STD_FORMAT ON)
else()
  include(CheckCXXSourceCompiles)
  set(_omc_saved_required_flags "${CMAKE_REQUIRED_FLAGS}")
  if(MSVC)
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} /std:c++20")
  else()
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -std=c++20")
  endif()
  check_cxx_source_compiles(
    "
    #include <format>
    int main() {
      (void)std::format(\"{}\", 1);
      return 0;
    }
    "
    OMC_STD_FORMAT_WORKS)
  set(CMAKE_REQUIRED_FLAGS "${_omc_saved_required_flags}")
  if(OMC_STD_FORMAT_WORKS)
    set(_OMC_HAS_STD_FORMAT ON)
  endif()
endif()

if(_OMC_HAS_STD_FORMAT)
  target_compile_definitions(${OMC_CONFIG_TARGET} PUBLIC OMC_HAS_STD_FORMAT)
  message(STATUS "[OpenMeshCraft] Using std::format")
  return()
endif()

set(_OMC_FMT_INCLUDE "")

if(EXISTS
   "${CMAKE_CURRENT_SOURCE_DIR}/../../external/fmt/include/fmt/format.h")
  set(_OMC_FMT_INCLUDE
      "${CMAKE_CURRENT_SOURCE_DIR}/../../external/fmt/include")
  message(STATUS "[OpenMeshCraft] Using vendored {fmt} in external/fmt")
elseif(TARGET fmt::fmt-header-only)
  target_link_libraries(${OMC_CONFIG_TARGET} PUBLIC fmt::fmt-header-only)
  target_compile_definitions(${OMC_CONFIG_TARGET} PUBLIC FMT_HEADER_ONLY
                                                         FMT_CONSTEVAL=)
  message(STATUS "[OpenMeshCraft] Using existing fmt::fmt-header-only")
  return()
else()
  include(FetchContent)
  FetchContent_Declare(
    omc_fmt
    URL https://github.com/fmtlib/fmt/archive/refs/tags/10.2.1.zip
    URL_HASH
      SHA256=D368F9C39A33A3AEF800F5BE372EC1DF1C12AD57ADA1F60ADC62F24C0E348469)
  FetchContent_GetProperties(omc_fmt)
  if(NOT omc_fmt_POPULATED)
    message(STATUS "[OpenMeshCraft] Fetching {fmt} 10.2.1")
    FetchContent_Populate(omc_fmt)
  endif()
  set(_OMC_FMT_INCLUDE "${omc_fmt_SOURCE_DIR}/include")
endif()

# FMT_CONSTEVAL= must be defined before any fmt header is parsed.
target_compile_definitions(${OMC_CONFIG_TARGET} PUBLIC FMT_HEADER_ONLY
                                                       FMT_CONSTEVAL=)
target_include_directories(
  ${OMC_CONFIG_TARGET}
  PUBLIC $<BUILD_INTERFACE:${_OMC_FMT_INCLUDE}>)
message(STATUS "[OpenMeshCraft] Using header-only {fmt}: ${_OMC_FMT_INCLUDE}")
