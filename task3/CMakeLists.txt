cmake_minimum_required(VERSION 3.17)
project(main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O2")
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(regression regression.cpp)
target_link_libraries(regression gtest gtest_main)
add_test(regression regression)

add_executable(main CustomMath.h main.cpp)

TARGET_LINK_LIBRARIES(main LINK_PUBLIC ${Boost_LIBRARIES} )

