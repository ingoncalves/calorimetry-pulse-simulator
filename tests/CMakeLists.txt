# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})
set(BINARY ${CMAKE_PROJECT_NAME}_tst)

enable_testing()

add_executable(${BINARY} ${TEST_SOURCES})
include_directories(${INCLUDE_DIR})
target_link_libraries(${BINARY} PUBLIC ${PROJECT_NAME} gtest_main pthread)

include(GoogleTest)

# C++ tests
gtest_discover_tests(${BINARY} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
