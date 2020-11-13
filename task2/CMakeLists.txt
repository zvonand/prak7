cmake_minimum_required(VERSION 3.7)
project(task2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -O3")

add_library(SolutionScheduling Solution/SolutionScheduler.h Solution/SolutionScheduler.cpp)
add_library(MutationScheduling Mutation/MutationScheduler.h Mutation/MutationScheduler.cpp)
add_library(XMLParse XMLParse/tinyxml2.cpp XMLParse/tinyxml2.h)

include_directories(XMLParse Solution Mutation Temperature AnnealingSim)

add_executable(task2 main.cpp)
target_link_libraries(task2 SolutionScheduling)
target_link_libraries(task2 MutationScheduling)
target_link_libraries(task2 XMLParse)
