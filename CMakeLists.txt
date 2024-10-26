cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(cps VERSION 1.1.0 DESCRIPTION "Calorimeter Pulse Simulator Library")
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_DOCS "Build docs" OFF)
option(BUILD_PYTHON "Build Python SWIG module" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(lib)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(BUILD_DOCS)
  add_subdirectory(docs)
endif()

if(BUILD_PYTHON)
  add_subdirectory(python)
endif()
