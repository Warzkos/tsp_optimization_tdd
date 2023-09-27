cmake_minimum_required(VERSION 3.0.0)
project(
  tsp_optimization_tdd
  VERSION 0.1.0
  LANGUAGES C CXX)

include(cmake/UpdateSubmodules.cmake)
include(CTest)

add_subdirectory(external/googletest)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}-ut tests/tests.cpp)
    target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-ut)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
