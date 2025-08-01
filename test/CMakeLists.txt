cmake_minimum_required(VERSION 3.20)

project(test_code)
add_subdirectory(googletest)
include(CTest)

if(BUILD_TESTING)
    
    add_executable(test_code test.cpp)
    target_link_libraries(test_code PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(test_code)

endif()