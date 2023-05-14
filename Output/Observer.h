#pragma once

#include "../types.h"

class Observer {
public:
    virtual void update(const MazeGrid& grid, Coords ) = 0;
};
