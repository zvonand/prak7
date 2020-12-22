cmake_minimum_required(VERSION 3.17)
project(prak4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(prak4 main.cpp GoL.h Genetic.cpp Genetic.h HeadCycle.cpp HeadCycle.h)