find_program(DOXYGEN_PATH doxygen REQUIRED)

if(DOXYGEN_PATH_NOTFOUND)
  message(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it on your system")

else()
    #message(STATUS "Doxygen found.")
    configure_file(Doxyfile.in Doxyfile)

    add_custom_target(documentation 
      COMMAND ${DOXYGEN_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
     
endif()