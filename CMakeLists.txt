cmake_minimum_required(VERSION 3.10)
project(Poseidon VERSION 0.1.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

aux_source_directory(src SRC_FILES)
aux_source_directory(src/utils UTILS_FILES)
MESSAGE(STATUS ${SRC_FILES})
add_library(Poseidon SHARED ${SRC_FILES} ${UTILS_FILES})
target_include_directories(Poseidon PUBLIC include/ include/utils/)

