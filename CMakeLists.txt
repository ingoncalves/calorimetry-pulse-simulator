# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(CaloPulseSimulator VERSION 0.0.0 DESCRIPTION "Calorimeter Pulse Simulator C++ Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(docs)

option(BUILD_PYTHON "Build Python SWIG module" ON)
if(BUILD_PYTHON)
  add_subdirectory(python)
endif()
