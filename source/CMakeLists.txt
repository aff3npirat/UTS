add_library(testsuite_lib STATIC
    testsuite.cpp
)

target_include_directories(
    testsuite_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)