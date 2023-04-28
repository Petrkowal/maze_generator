cmake_minimum_required(VERSION 3.21)
project(maze_generator)

set(CMAKE_CXX_STANDARD 20)

add_executable(maze_generator main.cpp Maze/Maze.cpp Maze/Cell.cpp MazeGenerator.cpp)

