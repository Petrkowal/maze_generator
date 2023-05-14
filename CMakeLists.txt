cmake_minimum_required(VERSION 3.21)
project(maze_generator)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "*.cpp" "*/*.cpp")

add_executable(maze ${SOURCES}
        Helpers/Params.cpp
        Helpers/Params.h)

target_link_libraries(maze ${OpenCV_LIBS})