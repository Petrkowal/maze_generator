#pragma once

#include "../types.h"
#include "Cell.h"

#include <random>
#include <cstdint>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <random>
#include <windows.h>


class Maze {
public:
    Maze(const Size &size);
    void print() const;
protected:
    Size _size;
    Coords _start_coords;
    Coords _current_coords;
    std::vector<std::vector<Cell>> _maze;

    bool valid_coords(Coords c) const;
};

// TODO: implement this
class MazeBuilder : public Maze {
public:

};
