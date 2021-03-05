cmake_minimum_required(VERSION 3.10)

project(Toolbox VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

configure_file(Config.h.in ../include/Config.h)

add_library(Toolbox)

file(GLOB_RECURSE SOURCES src/*)
target_sources(Toolbox PUBLIC ${SOURCES})
target_include_directories(Toolbox PUBLIC include/)

target_link_libraries(Toolbox PUBLIC coverage_config)

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
