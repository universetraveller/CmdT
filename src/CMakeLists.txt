cmake_minimum_required(VERSION 3.21)
project(ct)

set(CMAKE_CXX_STANDARD 17)

add_executable(ct main.cpp cmdline.h Editor.cpp Editor.h depends.h depends.cpp)
