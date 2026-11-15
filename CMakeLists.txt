cmake_minimum_required(VERSION 3.10)
project(testsuite VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

add_library(testsuite ${CMAKE_CURRENT_SOURCE_DIR}/source/testsuite.cpp)
target_include_directories(
    testsuite
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(UTS_BUILD_TESTS "Build tests" OFF)
if (UTS_BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
