file(GLOB SOURCES "*.cpp" "*.hpp")

target_sources(Unit_Tests PRIVATE 
    ${SOURCES}
)


target_include_directories(Unit_Tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Unit_Tests PRIVATE 
    dsa_graph_algos
    dsa_graph_algos_test_headers
    dsa_macros_header
    gtest_main
)

