#include "Cell.h"

Cell::Cell() {
    _byte = 0b1111;
}

Cell::Cell(uint8_t byte) : _byte(byte) {}

bool Cell::is_visited() const {
    return (_byte & static_cast<uint8_t>(Cell::State::VISITED)) != 0;
}

void Cell::set_visited() {
    _byte |= static_cast<uint8_t>(State::VISITED);
}

void Cell::set_unvisited() {
    _byte &=~ static_cast<uint8_t>(State::VISITED);
}

bool Cell::has_wall(Direction dir) const {
    return (_byte & static_cast<uint8_t>(dir));
}

void Cell::add_wall(enum Direction dir) {
    _byte |= static_cast<uint8_t>(dir);
}

void Cell::remove_wall(enum Direction dir) {
    _byte &=~ static_cast<uint8_t>(dir);
}

bool Cell::is_start() const {
    return _byte & static_cast<uint8_t>(State::START);
}

void Cell::set_start() {
    _byte |= static_cast<uint8_t>(State::START);
}

void Cell::remove_start() {
    _byte &=~ static_cast<uint8_t>(State::START);
}

bool Cell::is_end() const {
    return _byte & static_cast<uint8_t>(State::END);
}

void Cell::set_end() {
    _byte |= static_cast<uint8_t>(State::END);
}

void Cell::remove_end() {
    _byte &=~ static_cast<uint8_t>(State::END);
}
