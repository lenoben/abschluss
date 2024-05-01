# Server CMakeLists.txt
cmake_minimum_required(VERSION 3.10.0)
project(senti_mlserver VERSION 0.1.0 LANGUAGES C CXX)

# Set required standard to C++20.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include/uWebSockets/uSockets/src)
include_directories(${CMAKE_SOURCE_DIR}/include/uWebSockets/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Build uSockets library
add_subdirectory(include/uWebSockets/uSockets/)

# Add source files with src/main.cpp
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Build executable
add_executable(senti_mlserver ${SOURCES})

find_package(Armadillo REQUIRED)
find_package(cereal REQUIRED)

# Compiler flags for the executable
target_compile_options(senti_mlserver PRIVATE
    -march=native
    -Wpedantic
    -Wall
    -Wextra
    -Wsign-conversion
    -Wconversion
)

# Link with uSockets library and zlib
target_link_libraries(senti_mlserver PRIVATE
    uSockets
    -lz
)

# Link libraries
target_link_libraries(senti_mlserver PRIVATE -larmadillo -lmlpack -fopenmp)

# Set output directory
set_target_properties(senti_mlserver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)