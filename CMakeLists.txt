cmake_minimum_required(VERSION 3.0.0)
project(
    tsp_optimization_tdd
    VERSION 0.1.0
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(USE_MULTITHREAD FALSE)

# uncomment lines below to enable testing
# include(CTest)
# enable_testing()

set(SOURCE src/Specimen.cpp src/Population.cpp)
set(HEADERS lib/Specimen.hpp lib/Population.hpp)
set(TESTS tests/tests.cpp)

if(USE_MULTITHREAD)
    add_executable(${PROJECT_NAME}-mt src/mainMultithread.cpp ${SOURCE} ${HEADERS})
else()
    add_executable(${PROJECT_NAME} src/main.cpp ${SOURCE} ${HEADERS})
endif()

if(BUILD_TESTING)
    include(cmake/UpdateSubmodules.cmake)
    add_subdirectory(external/googletest)
    add_executable(${PROJECT_NAME}-ut ${TESTS} ${SOURCE} ${HEADERS})
    target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::gtest_main)
    file(COPY tests/cities.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-ut)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
