# This file defines the dsa_linked_list library

# Build the main static library. Only list source files here.
add_library(dsa_linked_list STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/linked_list.c"
)

# Add the required include paths for the dsa_linked_list source file.
# The `PRIVATE` keyword means this include path is for internal use only.
target_include_directories(dsa_linked_list PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# This INTERFACE library holds the public header file.
# Any target that links to `dsa_linked_list` will get this include path automatically.
add_library(dsa_linked_list_public_headers INTERFACE)

# We explicitly list ONLY the public header in the PUBLIC_HEADER property.
set_target_properties(dsa_linked_list_public_headers PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/linked_list.h"
)

# This INTERFACE library holds the headers for unit testing purposes.
add_library(dsa_linked_list_test_headers INTERFACE)
target_include_directories(dsa_linked_list_test_headers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link the static library to its public headers.
target_link_libraries(dsa_linked_list PUBLIC 
    dsa_linked_list_public_headers
    dsa_macros_header
)

if(LABWINDOWS_CVI_COMPATIBILITY)
    target_include_directories(dsa_linked_list PRIVATE
      "C:/Program Files (x86)/National Instruments/CVI2020/include"  
    )

    target_link_libraries(dsa_linked_list PRIVATE
        "C:/Program Files (x86)/National Instruments/CVI2020/extlib/msvc/cvirt.lib"
        "C:/Program Files (x86)/National Instruments/CVI2020/extlib/msvc/cvisupp.lib"
    )
endif()

# Set the public header for installation. This is the correct way to
# install headers linked via an INTERFACE library.
install(
    TARGETS dsa_linked_list dsa_linked_list_public_headers dsa_macros_header
    EXPORT dsa_linked_list_export
    PUBLIC_HEADER
    ARCHIVE DESTINATION lib
)

# This is a key step: install the generated export file.
install(
    EXPORT dsa_linked_list_export
    DESTINATION lib/cmake/dsa_linked_list
    NAMESPACE dsa::
)
