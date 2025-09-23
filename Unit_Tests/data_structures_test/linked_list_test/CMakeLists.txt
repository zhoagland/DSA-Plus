file(GLOB SOURCES "*.cpp" "*.hpp")

target_sources(unit_tests PRIVATE 
    ${SOURCES}
)

target_include_directories(unit_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(unit_tests PRIVATE 
    dsa_linked_list
    dsa_linked_list_test_headers
    dsa_macros_header
    gtest_main
)

