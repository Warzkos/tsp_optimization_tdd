cmake_minimum_required(VERSION 3.0.0)
project(
  tsp_optimization_tdd
  VERSION 0.1.0
  LANGUAGES C CXX)

include(cmake/UpdateSubmodules.cmake)
include(CTest)

add_subdirectory(external/googletest)

set(SOURCE)# src/Specimen.cpp)
set(HEADERS lib/Specimen.hpp)
set(TESTS tests/tests.cpp)


add_executable(${PROJECT_NAME} src/main.cpp)

enable_testing()

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}-ut ${TESTS} ${SOURCE} ${HEADERS})
    target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-ut)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
