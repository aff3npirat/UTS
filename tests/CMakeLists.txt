add_executable(demo main.cpp class_under_test.cpp)
set_target_properties(demo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
target_link_options(demo PUBLIC -static -static-libgcc -static-libstdc++)
target_link_libraries(demo PUBLIC testsuite_lib)
target_include_directories(
    demo
    PUBLIC
    # add additional dirs to add to include path
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)