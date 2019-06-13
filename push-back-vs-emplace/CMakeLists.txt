cmake_minimum_required(VERSION 3.12)
project(push_back_vs_emplace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")


add_executable(push_back_vs_emplace main.cpp)