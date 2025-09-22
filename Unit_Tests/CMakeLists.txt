cmake_minimum_required(VERSION 3.20)

project(Unit_Tests)

add_executable(Unit_Tests Unit_Tests.cpp)
target_link_libraries(Unit_Tests PRIVATE DSA_Plus gtest_main)
target_include_directories(Unit_Tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../src/include
    ${PROJECT_BINARY_DIR}/../
)

include(GoogleTest)
gtest_discover_tests(Unit_Tests)

