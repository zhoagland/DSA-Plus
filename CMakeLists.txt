#set cmake version
cmake_minimum_required(VERSION 3.29)

#set project name
project(Template_Project 
        VERSION 1.0 
        DESCRIPTION "Template Project Description"
        LANGUAGES C
)

#set language settings
set(CMAKE_C_STANDARD            11)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_EXTENSIONS          OFF)


add_executable(${PROJECT_NAME} ./src/main.c)

configure_file(config.h.in config.h)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" )
install(TARGETS ${PROJECT_NAME} DESTINATION bin COMPONENT out_component)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include )


add_subdirectory(docs)
add_subdirectory(external)

#CTest Settings
add_subdirectory(test)

#CPack Settings to make an installer
include(InstallRequiredSystemLibraries)
set(CPACK_COMPONENTS_ALL out_component)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "$(PROJECT_VERSION_MINOR)")
include(CPack)