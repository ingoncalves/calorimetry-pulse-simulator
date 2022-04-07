cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

# PYTHON
find_package(Python COMPONENTS Interpreter Development REQUIRED)
if(Python_VERSION MATCHES "^2.*$" )
  set(CMAKE_SWIG_FLAGS -classic)
else()
  set(CMAKE_SWIG_FLAGS -py3)
endif()

# SWIG
find_package(SWIG 4.0 COMPONENTS python)
if(SWIG_FOUND)
  message("SWIG found: ${SWIG_EXECUTABLE}")
endif()
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

message("CMAKE_SWIG_FLAGS: ${CMAKE_SWIG_FLAGS}")
message("Python_EXECUTABLE: ${Python_EXECUTABLE}")
message("Python_MODULE: py${PROJECT_NAME}")
message("Python_VERSION: ${Python_VERSION}")
message("Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
message("Python_SITELIB: ${Python_SITELIB}")
message("Python_LIBRARIES: ${Python_LIBRARIES}")

INCLUDE_DIRECTORIES(${Python_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${INCLUDE_DIR})

SET_SOURCE_FILES_PROPERTIES(PythonBindings.i PROPERTIES CPLUSPLUS ON)

swig_add_library(py${PROJECT_NAME} TYPE MODULE LANGUAGE python SOURCES PythonBindings.i)
swig_link_libraries(py${PROJECT_NAME} ${PROJECT_NAME} ${Python_LIBRARIES})

# Install library
install(
  TARGETS ${SWIG_MODULE_py${PROJECT_NAME}_REAL_NAME}
  LIBRARY DESTINATION ${Python_SITELIB})

# Install pyhton module
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/py${PROJECT_NAME}.py
  DESTINATION ${Python_SITELIB})

# Tests
add_test(NAME pyTest_${PROJECT_NAME} COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py)
