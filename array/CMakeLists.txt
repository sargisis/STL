cmake_minimum_required(VERSION 3.10)

project(Array)

set(CMAKE_CXX_STANDARD 20)

add_executable(Array 
    ArraySrc/main.cpp 
    ArrayHeader/Array.h 
    ArrayHeader/Array.cpp
)
