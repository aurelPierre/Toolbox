cmake_minimum_required(VERSION 3.10)

project(Toolbox VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

configure_file(Config.h.in ../include/Config.h)

add_library(Toolbox)

file(GLOB_RECURSE SOURCES src/*)
target_sources(Toolbox PUBLIC ${SOURCES})
target_include_directories(Toolbox PUBLIC include/)

install(TARGETS Toolbox DESTINATION lib)

# unit test directory
add_subdirectory(test)

# packaging system
# linux supported
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/License.txt)
set(CPACK_PACKAGE_VERSION_MAJOR ${Toolbox_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${Toolbox_VERSION_MINOR})
include(CPack)
