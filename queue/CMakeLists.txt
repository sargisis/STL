cmake_minimum_required(VERSION 3.10)

project(Queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(Queue QueueHeader/Queue.h QueueHeader/Queue.hpp QueueSrc/main.cpp)
