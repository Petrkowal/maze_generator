#pragma once

#include "../types.h"
#include <cstdint>

class Cell {
public:
    Cell();
    Cell(uint8_t byte);

    bool is_visited() const;
    void set_visited();
    void set_unvisited();

    bool has_wall(enum Direction dir) const;
    void add_wall(enum Direction dir);
    void remove_wall(enum Direction dir);

    bool is_start() const;
    void remove_start();
    void set_start();

    bool is_end() const;
    void remove_end();
    void set_end();
private:
    uint8_t _byte;

    enum class State : uint8_t {
        VISITED = 0b10000,
        START   = 0b100000,
        END     = 0b1000000
    };
};

