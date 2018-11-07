cmake_minimum_required(VERSION 3.4.1)

project(leetcode)

add_definitions(-std=c++11)
add_definitions(-frtti)
add_definitions(-fexceptions)

aux_source_directory(${CMAKE_SOURCE_DIR}/cc srcs)

add_executable(leetcode ${srcs})
