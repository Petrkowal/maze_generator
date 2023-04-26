#pragma once

#include "../types.h"
#include <cstdint>

class Cell {
public:
    uint8_t byte;
    Cell(){byte = 0x0;}
    Cell(uint8_t byte) : byte(byte) {}

    bool visited() {
        return (byte & VISITED) != 0;
    }
    void set_visited() {
        byte |= VISITED;
    }
    void set_unvisited(){
        byte &= ~VISITED;
    }
    bool wall(int d){
        switch (d) {
            case N: // up
                return (byte & WALL_N) != 0;
            case E: // right
                return (byte & WALL_E) != 0;
            case S: // down
                return (byte & WALL_S) != 0;
            case W: // left
                return (byte & WALL_W) != 0;
            default:
                return false;
        }
    }
    void set_wall(int d){
        switch (d) {
            case N: // up
                byte |= WALL_N;
                return;
            case E: // right
                byte |= WALL_E;
                return;
            case S: // down
                byte |= WALL_S;
                return;
            case W: // left
                byte |= WALL_W;
                return;
            default:
                return;
        }
    }
    void remove_wall(int d) {
        switch (d) {
            case N: // up
                byte &= ~WALL_N;
                return;
            case E: // right
                byte &= ~WALL_E;
                return;
            case S: // down
                byte &= ~WALL_S;
                return;
            case W: // left
                byte &= ~WALL_W;
                return;
            default:
                return;
        }
    }

};

