cmake_minimum_required(VERSION 3.12)
project(Puzzle8)

set(CMAKE_CXX_STANDARD 14)

add_executable(Puzzle8 main.cpp position.hpp puzzle8.hpp puzzle8.cpp position.cpp)