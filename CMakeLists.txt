cmake_minimum_required(VERSION 2.8)
project(rivlib-utils)

find_package(RiVLib COMPONENTS scanlib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(
    ${RiVLib_INCLUDE_DIRS}
    )

add_subdirectory(src)
