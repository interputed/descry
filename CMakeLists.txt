cmake_minimum_required(VERSION 3.0)
project(descry CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

include_directories(
        "src"
        "src/inc"
)

# This project should use *.cpp or *.hpp for all C++ files.
file(GLOB SOURCES
        "*.c"
        "*.cc"
        "*.cpp"
        "*.cxx"
        "*.h"
        "*.hh"
        "*.hpp"
        "*.hxx"
)

add_executable(descry ${SOURCES})

set_target_properties(descry PROPERTIES LINKER_LANGUAGE CXX)


