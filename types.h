#pragma once

#include <cstdint>
#include <memory>
#include <vector>

enum class Direction : uint8_t {
    N = 0b1,
    E = 0b10,
    S = 0b100,
    W = 0b1000,
    NORTH = N,
    EAST = E,
    SOUTH = S,
    WEST = W
};

struct Coords {
    int x;
    int y;

    bool operator==(const Coords &other) const {
        return x == other.x && y == other.y;
    }
};

struct Size {
    int width;
    int height;

    bool operator==(const Size &other) const {
        return width == other.width && height == other.height;
    }
};


const Size DEFAULT_SIZE{10, 5};
struct Cell;
using MazeGrid = std::vector<std::vector<std::shared_ptr<Cell>>>;

