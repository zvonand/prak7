cmake_minimum_required(VERSION 3.17)
project(funcFactory)

set(CMAKE_CXX_STANDARD 14)

add_library(funcFactory library.cpp library.h Function/Function.cpp Function/Function.h)