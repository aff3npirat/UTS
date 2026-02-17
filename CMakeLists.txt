cmake_minimum_required(VERSION 3.10)
project(testsuite VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

add_library(testsuite ${CMAKE_CURRENT_SOURCE_DIR}/source/testsuite.cpp)
target_include_directories(
    testsuite
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_target_properties(testsuite PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/testsuite.h 
)

install(TARGETS testsuite
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testsuite-${CMAKE_PROJECT_VERSION}
)

option(UTS_BUILD_TESTS "Build tests" ON)
if (UTS_BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()