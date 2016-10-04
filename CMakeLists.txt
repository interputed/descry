cmake_minimum_required(VERSION 3.0)
project(descry CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(descry_VERSION_MAJOR 0)
set(descry_VERSION_MINOR 1)
set(CXX_OPTIMIZATION_FLAGS "-g -O2 -std=c++11")
set(CXX_ERROR_FLAGS "-Wall -Werror -pedantic")

set(CMAKE_CXX_FLAGS "${CXX_OPTIMIZATION_FLAGS} ${CXX_ERROR_FLAGS}")

# For passing version number into executable.
configure_file(
    "${PROJECT_SOURCE_DIR}/src/descryConfig.h.in"
    "${PROJECT_SOURCE_DIR}/src/inc/descryConfig.h"
)

# src/CMakeLists.txt is where to add additional project files.
add_subdirectory(src)











