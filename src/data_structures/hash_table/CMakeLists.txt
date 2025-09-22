# This file defines the dsa_hash_table library

# Build the main static library. Only list source files here.
add_library(dsa_hash_table STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/hash_table.c"
)

# Add the required include paths for the dsa_hash_table source file.
# The `PRIVATE` keyword means this include path is for internal use only.
target_include_directories(dsa_hash_table PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# This INTERFACE library holds the public header file.
# Any target that links to `dsa_hash_table` will get this include path automatically.
add_library(dsa_hash_table_public_headers INTERFACE)
# We explicitly list ONLY the public header in the PUBLIC_HEADER property.
set_target_properties(dsa_hash_table_public_headers PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/hash_table.h"
)

# This INTERFACE library holds the headers for unit testing purposes.
add_library(dsa_hash_table_test_headers INTERFACE)
target_include_directories(dsa_hash_table_test_headers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link the static library to its public headers.
target_link_libraries(dsa_hash_table PUBLIC 
    dsa_hash_table_public_headers
    dsa_macros_header
)

# Set the public header for installation (optional, but good practice)
install(TARGETS dsa_hash_table PUBLIC_HEADER DESTINATION include)