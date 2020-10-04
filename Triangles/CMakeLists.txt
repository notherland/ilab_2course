cmake_minimum_required(VERSION 3.17)
project(Triangle)

set(CMAKE_CXX_STANDARD 14)

add_executable(Triangle Triangles.cpp main.cpp Check_crossing.cpp)