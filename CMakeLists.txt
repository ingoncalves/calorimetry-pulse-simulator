cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(cps VERSION 0.0.0 DESCRIPTION "Calorimeter Pulse Simulator Library")

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
