#pragma once

#include "../types.h"
#include <cstdint>

class Cell {
public:
    Cell();
    Cell(const Cell &orig);
    Cell(uint8_t byte);

    bool is_visited() const;
    Cell& set_visited();
    Cell& set_unvisited();

    bool has_wall(enum Direction dir) const;
    Cell& set_wall(enum Direction dir);
    Cell& remove_wall(enum Direction dir);

    bool is_start() const;
    Cell& remove_start();
    Cell& set_start();

    bool is_end() const;
    Cell& remove_end();
    Cell& set_end();
private:
    uint8_t _byte;

    enum class State : uint8_t {
        VISITED   = 0b10000,
        START    = 0b100000,
        END     = 0b1000000
    };
};

