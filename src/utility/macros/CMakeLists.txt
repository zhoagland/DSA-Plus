# This file defines the macros header library

# This INTERFACE library holds the header file.
# Any target that links to `dsa_macros_header` will get this include path automatically.
add_library(dsa_macros_header INTERFACE)

# Add the include directory for the macros header.
# The INTERFACE keyword means this include path is for any consumer of this library.
target_include_directories(dsa_macros_header INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# We explicitly list ONLY the public header in the PUBLIC_HEADER property.
set_target_properties(dsa_macros_header PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/macros.h"
)

# Set the public header for installation. This is the correct way to
# install headers linked via an INTERFACE library.
install(
    TARGETS dsa_macros_header
    EXPORT dsa_macros_export
    PUBLIC_HEADER
)

# This is a key step: install the generated export file.
install(
    EXPORT dsa_macros_export
    DESTINATION lib/cmake/dsa_macros_header
    NAMESPACE dsa::
)
