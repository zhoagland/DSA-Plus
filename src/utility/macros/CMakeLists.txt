# This file defines the macros header library

# This INTERFACE library holds the header file.
# Any target that links to `dsa_macros_header` will get this include path automatically.
add_library(dsa_macros_header INTERFACE)

# Add the include directory for the macros header.
# The INTERFACE keyword means this include path is for any consumer of this library.
target_include_directories(dsa_macros_header INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# We explicitly list ONLY the public header in the PUBLIC_HEADER property.
set_target_properties(dsa_macros_header PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/macros.h"
)