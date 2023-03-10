cmake_minimum_required(VERSION 3.12)
project(Poseidon)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES matrix.h matrix.cpp main.cpp sequence.h primenumber.h primenumber.cpp utilities.h graph.h graph.cpp tree.h tree.cpp dag.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} include)