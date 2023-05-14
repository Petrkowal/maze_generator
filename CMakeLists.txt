cmake_minimum_required(VERSION 3.21)
project(maze_generator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "*.cpp" "*/*.cpp")

add_executable(maze_generator ${SOURCES})

