#pragma once

#include <cstdint>

enum class Direction : uint8_t {
    N = 0b1,
    E = 0b10,
    S = 0b100,
    W = 0b1000
};

struct Size {
    int x;
    int y;
};

using Coords = Size;

const Size DEFAULT_SIZE{10, 5};
