# This file defines the dsa_vector library

# Build the main static library. Only list source files here.
add_library(dsa_vector STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/vector.c"
)

# Add the required include paths for the dsa_vector source file.
# The `PRIVATE` keyword means this include path is for internal use only.
target_include_directories(dsa_vector PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# This INTERFACE library holds the public header file.
# Any target that links to `dsa_vector` will get this include path automatically.
add_library(dsa_vector_public_headers INTERFACE)
# We explicitly list ONLY the public header in the PUBLIC_HEADER property.
set_target_properties(dsa_vector_public_headers PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/vector.h"
)

# This INTERFACE library holds the headers for unit testing purposes.
add_library(dsa_vector_test_headers INTERFACE)
target_include_directories(dsa_vector_test_headers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link the static library to its public headers.
target_link_libraries(dsa_vector PUBLIC 
    dsa_vector_public_headers
    dsa_macros_header
)

# Set the public header for installation (optional, but good practice)
install(TARGETS dsa_vector PUBLIC_HEADER DESTINATION include)