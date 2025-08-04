cmake_minimum_required(VERSION 3.20)

project(Unit_Tests)

include(CTest)

if(BUILD_TESTING)

    add_executable(Unit_Tests Unit_Tests.cpp)
    target_link_libraries(Unit_Tests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(Unit_Tests)

endif()