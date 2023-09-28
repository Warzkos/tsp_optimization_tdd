cmake_minimum_required(VERSION 3.0.0)
project(
  tsp_optimization_tdd
  VERSION 0.1.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(cmake/UpdateSubmodules.cmake)
include(CTest)

add_subdirectory(external/googletest)

set(SOURCE src/Specimen.cpp src/Population.cpp)
set(HEADERS lib/Specimen.hpp lib/Population.hpp)
set(TESTS tests/tests.cpp)


add_executable(${PROJECT_NAME} src/main.cpp)

enable_testing()

if(BUILD_TESTING)
    add_executable(${PROJECT_NAME}-ut ${TESTS} ${SOURCE} ${HEADERS})
    target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-ut)
endif()

# set(FLAGS -Wall -Wextra -Werror -pedantic -Wconversion -O3)

# target_compile_options(${PROJECT_NAME} ${FLAGS})
# target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
