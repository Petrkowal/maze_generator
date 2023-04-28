#pragma once

#include "types.h"
#include "Maze/Maze.h"

class MazeGenerator {
public:
    MazeGenerator();
    Maze* generate_maze();
private:
    Maze* generate(Size size);
    Size _size;
};
