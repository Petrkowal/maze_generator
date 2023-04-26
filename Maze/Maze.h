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

struct Size {
    int x;
    int y;
};

using Coords = Size;


class Maze {
public:
    Maze(const Size &size);
    Maze(const int x, const int y);
    void init();
    void generate();
    void print();
private:
    bool valid_coords(Coords coords) const;

    Size size;
    Coords start;
    std::stack<Coords> path;
    std::vector<std::vector<Cell>> maze;
};

