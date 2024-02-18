cmake_minimum_required(VERSION 3.0.0)
project(senti_model_flow VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files with src/main.cpp
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Build executable
add_executable(senti_model_flow ${SOURCES})

find_package(Armadillo REQUIRED)
find_package(Ensmallen REQUIRED)
find_package(cereal REQUIRED)

# Link libraries
target_link_libraries(senti_model_flow PRIVATE -larmadillo -lmlpack -lz -fopenmp)

# Set compilation flags
target_compile_options(senti_model_flow PRIVATE -Wconversion -fpermissive)

# Set output directory
set_target_properties(senti_model_flow PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)
