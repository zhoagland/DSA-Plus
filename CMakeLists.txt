#set cmake version
cmake_minimum_required(VERSION 3.28)

#set language settings
set(CMAKE_C_STANDARD            11)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_EXTENSIONS          OFF)

#set project name
project(DSA_Plus
        VERSION 1.0
        DESCRIPTION "Data Structure and Algorithms Library for C, Plus More."
        LANGUAGES C
)

option(LABWINDOWS_CVI_COMPATIBILITY "Make the lib link against the cvirte not msvc rte" OFF)

if(LABWINDOWS_CVI_COMPATIBILITY)
       add_definitions(-D__CVI_LIB__=1)
endif()

# Assuming your logo and icon are in an assets directory relative to your project root.
set(PROJECT_LOGO_PATH "${CMAKE_SOURCE_DIR}/assets/logo.png")
set(PROJECT_ICON_PATH "${CMAKE_SOURCE_DIR}/assets/icon.ico")

# Source code for all the libraries
add_subdirectory(src)

# Add docs package
add_subdirectory(docs)

# Add unit test package
add_subdirectory(unit_tests)

