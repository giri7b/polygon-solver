cmake_minimum_required(VERSION 3.10)
project(polygon_solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2")

add_executable(polygon_solver src/main.cpp)