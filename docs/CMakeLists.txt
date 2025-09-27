option(BUILD_DOCS "Build Documentation" ON)

if(BUILD_DOCS)
    # Allow fetching content.
    include(FetchContent)    

    # Fetch awesome css for doxygen.
    FetchContent_Declare(
      doxygen-awesome-css
      GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
      GIT_TAG        568f56cde6ac78b6dfcc14acd380b2e745c301ea
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)    

    find_program(DOXYGEN_PATH doxygen REQUIRED)

    if(DOXYGEN_PATH_NOTFOUND)
      message(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it on your system")
    else()
 
    set(DOXYGEN_AWESOME_CSS_PATH "${doxygen-awesome-css_SOURCE_DIR}")


    # Configure the Doxyfile with the correct paths.
    configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    # Add the custom target for documentation. This is a separate build artifact.
    add_custom_target(documentation
        COMMAND ${DOXYGEN_PATH} Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
    )

    # Install the generated documentation to the 'docs' folder.
    # The 'documentation' target must be built before this install step can run.
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/
            DESTINATION docs
            COMPONENT documentation
    )

    endif()

endif()