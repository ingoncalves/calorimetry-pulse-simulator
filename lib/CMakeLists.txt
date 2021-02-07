include(GNUInstallDirs)

# Find source files
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ${INCLUDE_DIR}/**/*.h)

# Include header files
include_directories(${INCLUDE_DIR})

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER ${HEADERS})

# Install library
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
