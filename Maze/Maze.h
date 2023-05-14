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
#include <memory>
#include <vector>
#include <chrono>

using MazeGrid = std::vector<std::vector<std::shared_ptr<Cell>>>;

class Maze {
public:
    Maze(const Size &size, const Coords &start_coords, const Coords &end_coords, int seed, std::string algorithm,
         std::chrono::duration<double> time, MazeGrid maze);

    MazeGrid get_grid() const;
    Coords get_start() const;
    Coords get_end() const;
    Size get_size() const;
    std::string get_algorithm() const;
    int get_seed() const;
    const std::chrono::duration<double, std::milli> get_gen_time() const;
    void print() const;
protected:
    std::chrono::duration<double> _gen_time;
    std::string _algorithm;
    int _seed;
    Size _size;
    Coords _start;
    Coords _end;
    MazeGrid _maze;
};

class MazeGridBuilder {
public:
    explicit MazeGridBuilder(const Size &size);
    ~MazeGridBuilder();


    MazeGridBuilder& create_empty_grid();
    std::shared_ptr<Cell> get_cell(const Coords& coords);
    std::shared_ptr<Cell> get_neighbor_cell(const Coords& coords, Direction direction);
    std::vector<std::shared_ptr<Cell>> get_neighbors(const Coords& coords);
    std::vector<std::shared_ptr<Cell>> get_unvisited_neighbors(const Coords& coords);
    std::vector<std::shared_ptr<Cell>> get_visited_neighbors(const Coords& coords);
    std::vector<Direction> get_unvisited_directions(const Coords& coords);
    bool remove_wall(const Coords& coords, Direction direction);
    bool remove_wall(const Coords& coords, const Coords& neighbor);
    bool validate_coords(const Coords &c) const;
    MazeGrid get_grid() const;
private:
    Size _size;
    MazeGrid _maze;
};
