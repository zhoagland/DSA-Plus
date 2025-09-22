# This file defines the dsa_tree library

# Build the main static library. Only list source files here.
add_library(dsa_tree STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/tree.c"
)

# Add the required include paths for the dsa_tree source file.
# The `PRIVATE` keyword means this include path is for internal use only.
target_include_directories(dsa_tree PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# This INTERFACE library holds the public header file.
# Any target that links to `dsa_tree` will get this include path automatically.
add_library(dsa_tree_public_headers INTERFACE)
# We explicitly list ONLY the public header in the PUBLIC_HEADER property.
set_target_properties(dsa_tree_public_headers PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/tree.h"
)

# This INTERFACE library holds the headers for unit testing purposes.
add_library(dsa_tree_test_headers INTERFACE)
target_include_directories(dsa_tree_test_headers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link the static library to its public headers.
target_link_libraries(dsa_tree PUBLIC 
    dsa_tree_public_headers
    dsa_macros_header
)

# Set the public header for installation (optional, but good practice)
install(TARGETS dsa_tree PUBLIC_HEADER DESTINATION include)