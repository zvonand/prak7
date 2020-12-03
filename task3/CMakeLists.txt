cmake_minimum_required(VERSION 3.17)
project(main)

set(CMAKE_CXX_STANDARD 14)
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(main CustomMath.h main.cpp)

TARGET_LINK_LIBRARIES(main LINK_PUBLIC ${Boost_LIBRARIES} )
