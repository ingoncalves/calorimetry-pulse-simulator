include(gtest) # Custom module

set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

include_directories(${GTEST_INCLUDE_DIR} ${INCLUDE_DIR})
link_directories(${GTEST_LIBRARY_PATH})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${PROJECT_NAME} ${GTEST_LIBRARY})
