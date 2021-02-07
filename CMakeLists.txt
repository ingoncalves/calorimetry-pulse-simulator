cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(CaloPulseSimulator VERSION 1.0.0 DESCRIPTION "Calorimeter Pulse Simulator C++ Library")

set(CMAKE_CXX_STANDARD 14)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(lib)
add_subdirectory(tests)

option(BUILD_PYTHON "Build Python SWIG module" ON)
if(BUILD_PYTHON)
  add_subdirectory(python)
endif()
