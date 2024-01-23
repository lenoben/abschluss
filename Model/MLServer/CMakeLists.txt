# Server CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MLSERVER)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include/uWebSockets/uSockets/src)
include_directories(${CMAKE_SOURCE_DIR}/include/uWebSockets/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Build uSockets library
add_subdirectory(include/uWebSockets/uSockets/)

# Add source files with src/main.cpp
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Build executable
add_executable(MLSERVER ${SOURCES})

# Compiler flags for the executable
target_compile_options(MLSERVER PRIVATE
    -march=native
    -O3
    -Wpedantic
    -Wall
    -Wextra
    -Wsign-conversion
    -Wconversion
    -std=c++20
    -flto
)

# Link with uSockets library and zlib
target_link_libraries(MLSERVER PRIVATE
    uSockets
    -lz
)

# Link libraries
target_link_libraries(MLSERVER PRIVATE -lz -lpqxx -lpq -larmadillo -lmlpack -fopenmp)

# Set compilation flags
target_compile_options(MLSERVER PRIVATE -flto -Wconversion -fopenmp)

# Set output directory
set_target_properties(MLSERVER PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)