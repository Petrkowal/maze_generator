#include "Cell.h"

Cell::Cell() {
    _byte = 0b1111;
}

Cell::Cell(const Cell &orig) : _byte(orig._byte) {}

Cell::Cell(uint8_t byte) : _byte(byte) {}

bool Cell::is_visited() const {
    return (_byte & static_cast<uint8_t>(Cell::State::VISITED)) != 0;
}

Cell& Cell::set_visited() {
    _byte |= static_cast<uint8_t>(State::VISITED);
    return *this;
}

Cell& Cell::set_unvisited() {
    _byte &=~ static_cast<uint8_t>(State::VISITED);
    return *this;
}

bool Cell::has_wall(Direction dir) const {
    return (_byte & static_cast<uint8_t>(dir));
}

Cell& Cell::set_wall(enum Direction dir) {
    _byte |= static_cast<uint8_t>(dir);
    return *this;
}

Cell& Cell::remove_wall(enum Direction dir) {
    _byte &=~ static_cast<uint8_t>(dir);
    return *this;
}

bool Cell::is_start() const {
    return _byte & static_cast<uint8_t>(State::START);
}

Cell& Cell::set_start() {
    _byte |= static_cast<uint8_t>(State::START);
    return *this;
}

Cell& Cell::remove_start() {
    _byte &=~ static_cast<uint8_t>(State::START);
    return *this;
}

bool Cell::is_end() const {
    return _byte & static_cast<uint8_t>(State::END);
}

Cell& Cell::set_end() {
    _byte |= static_cast<uint8_t>(State::END);
    return *this;
}

Cell& Cell::remove_end() {
    _byte &=~ static_cast<uint8_t>(State::END);
    return *this;
}
