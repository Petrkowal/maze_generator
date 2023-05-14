cmake_minimum_required(VERSION 3.21)
project(maze_generator)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "*.cpp" "*/*.cpp")

add_executable(maze_generator ${SOURCES} Output/MazeVideo.cpp Output/MazeVideo.h Output/Observer.cpp Output/Observer.h)

target_link_libraries(maze_generator ${OpenCV_LIBS})