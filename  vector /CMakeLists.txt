cmake_minimum_required(VERSION 3.10)

project(Vector)  

set(CMAKE_CXX_STANDARD 20) 

# Include directories
include_directories(VectorHeader)  
include_directories(VectorSrc)

add_executable(Vector 
    VectorSrc/main.cpp 
    VectorHeader/Vector.h 
    VectorSrc/Vector.hpp
)
