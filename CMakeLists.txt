cmake_minimum_required(VERSION 3.16)
project(TreeSort)

set(CMAKE_CXX_STANDARD 17)

add_executable(TreeSort main.cpp BinaryTree.h Sorter.h)
add_executable(RandGen randgen.cpp)
add_executable(Checker checker.cpp)