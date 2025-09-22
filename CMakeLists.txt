#set cmake version
cmake_minimum_required(VERSION 3.28)

#set project name
project(DSA_Plus
        VERSION 1.0
        DESCRIPTION "Data Structure and Algorithms Library for C, Plus More."
        LANGUAGES C
)

#set language settings
set(CMAKE_C_STANDARD            11)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_EXTENSIONS          OFF)


#add_library(${PROJECT_NAME} STATIC "./src/data structures/linear/linked_list.c")
add_subdirectory(src)

configure_file(config.h.in config.h)

#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" )
#install(TARGETS ${PROJECT_NAME} DESTINATION bin COMPONENT out_component)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include )

# --- Start of FetchContent configuration ---
include(FetchContent)

# Declare the content to be fetched. We use the official GoogleTest git repository.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)

# Make the content available. This downloads and adds it to the build.
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  doxygen-awesome-css
  GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
  GIT_TAG        568f56cde6ac78b6dfcc14acd380b2e745c301ea
)

FetchContent_MakeAvailable(doxygen-awesome-css)
# --- End of FetchContent configuration ---

add_subdirectory(docs)

#CTest Settings
add_subdirectory(Unit_Tests)
