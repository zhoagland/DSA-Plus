cmake_minimum_required(VERSION 3.20)

project(Unit_Tests)

add_executable(Unit_Tests)

#add_subdirectory(algorithms_test)
add_subdirectory(data_structures_test)
#add_subdirectory(memory_test)
#add_subdirectory(utility_test)

target_link_libraries(Unit_Tests PRIVATE 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(Unit_Tests)

