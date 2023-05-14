#include "Maze.h"

#include <utility>

Maze::Maze(const Size &size, const Coords &start_coords, const Coords& end_coords, int seed, std::string algorithm,
           std::chrono::duration<double> time, MazeGrid maze) : _size(size),
                                          _start(start_coords),
                                          _end(end_coords),
                                          _seed(0),
                                          _algorithm(algorithm),
                                          _gen_time(time),
                                          _maze(std::move(maze)) {

}

MazeGrid Maze::get_grid() const {
    return {_maze};
}

Coords Maze::get_start() const {
    return {_start};
}

Coords Maze::get_end() const {
    return {_end};
}

Size Maze::get_size() const {
    return {_size};
}

std::string Maze::get_algorithm() const {
    return _algorithm;
}

int Maze::get_seed() const {
    return _seed;
}

const std::chrono::duration<double, std::milli> Maze::get_gen_time() const {
    return std::chrono::duration<double, std::milli>(_gen_time);
}

void Maze::print() const {
    int cols = _maze.size();
    int rows = _maze[0].size();

    for (int i = 0; i < 30; i++) {
        std::cout << std::endl;
    }

    std::cout << "+";
    for (int col = 0; col < cols; col++) {
        std::cout << "---+";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << "|";
        for (int col = 0; col < cols; col++) {
            if (_maze[col][row]->has_wall(Direction::E)) {
                if (_maze[col][row]->is_start()) {
                    std::cout << " S |";
                } else if (_maze[col][row]->is_end()) {
                    std::cout << " E |";
                } else {
                    std::cout << "   |";
                }
            } else {
                if (_maze[col][row]->is_start()) {
                    std::cout << " S  ";
                } else {
                    std::cout << "    ";
                }
            }
        }
        std::cout << std::endl;

        std::cout << "+";
        for (int col = 0; col < cols; col++) {
            if (_maze[col][row]->has_wall(Direction::S)) {
                std::cout << "---+";
            } else {
                std::cout << "   +";
            }
        }
        std::cout << std::endl;
    }
}




MazeGridBuilder::MazeGridBuilder(const Size &size) : _size(size) {


}

MazeGridBuilder::~MazeGridBuilder() {

}

MazeGridBuilder &MazeGridBuilder::create_empty_grid() {
    _maze = MazeGrid(_size.width, std::vector<std::shared_ptr<Cell>>(_size.height));
    for (auto &col: _maze) {
        for (auto &cell: col) {
            cell = std::make_shared<Cell>(0b1111);
        }
    }
    return *this;
}

bool MazeGridBuilder::validate_coords(const Coords &c) const {
    int cols = _maze.size();
    if (cols == 0) {
        return false;
    }
    int rows = _maze[0].size();
    if (rows == 0) {
        return false;
    }
    if (c.x < 0 || c.x >= cols) {
        return false;
    }
    if (c.y < 0 || c.y >= rows) {
        return false;
    }
    if (_maze[c.x].empty()) {
        return false;
    }
    if (c.y >= _maze[c.x].size()) {
        return false;
    }
    return true;
}

std::shared_ptr<Cell> MazeGridBuilder::get_cell(const Coords &coords) {
    if (validate_coords(coords)) {
        return _maze[coords.x][coords.y];
    }
    return nullptr;
}

std::shared_ptr<Cell> MazeGridBuilder::get_neighbor_cell(const Coords &coords, Direction direction) {
    if (!validate_coords(coords)) {
        return nullptr;
    }
    switch (direction) {
        case Direction::N:
            return get_cell({coords.x, coords.y - 1});
        case Direction::E:
            return get_cell({coords.x + 1, coords.y});
        case Direction::S:
            return get_cell({coords.x, coords.y + 1});
        case Direction::W:
            return get_cell({coords.x - 1, coords.y});
    }
    return nullptr;
}

std::vector<std::shared_ptr<Cell>> MazeGridBuilder::get_neighbors(const Coords &coords) {
    if (!validate_coords(coords)) {
        return {};
    }
    std::vector<std::shared_ptr<Cell>> neighbors;
    Coords neigh_c = {coords.x, coords.y - 1};
    if (validate_coords(neigh_c))
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x + 1, coords.y};
    if (validate_coords(neigh_c))
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x, coords.y + 1};
    if (validate_coords(neigh_c))
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x - 1, coords.y};
    if (validate_coords(neigh_c))
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    return neighbors;
}

std::vector<std::shared_ptr<Cell>> MazeGridBuilder::get_unvisited_neighbors(const Coords &coords) {
    if (!validate_coords(coords)) {
        return {};
    }
    std::vector<std::shared_ptr<Cell>> neighbors;
    Coords neigh_c = {coords.x, coords.y - 1};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x + 1, coords.y};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x, coords.y + 1};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x - 1, coords.y};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    return neighbors;
}

std::vector<std::shared_ptr<Cell>> MazeGridBuilder::get_visited_neighbors(const Coords &coords) {
    if (!validate_coords(coords)) {
        return {};
    }
    std::vector<std::shared_ptr<Cell>> neighbors;
    Coords neigh_c = {coords.x, coords.y - 1};
    if (validate_coords(neigh_c) && _maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x + 1, coords.y};
    if (validate_coords(neigh_c) && _maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x, coords.y + 1};
    if (validate_coords(neigh_c) && _maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    neigh_c = {coords.x - 1, coords.y};
    if (validate_coords(neigh_c) && _maze[neigh_c.x][neigh_c.y]->is_visited())
        neighbors.push_back(_maze[neigh_c.x][neigh_c.y]);
    return neighbors;
}

std::vector<Direction> MazeGridBuilder::get_unvisited_directions(const Coords &coords) {
    if (!validate_coords(coords)) {
        return {};
    }
    std::vector<Direction> directions;
    Coords neigh_c = {coords.x, coords.y - 1};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        directions.push_back(Direction::NORTH);
    neigh_c = {coords.x + 1, coords.y};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        directions.push_back(Direction::EAST);
    neigh_c = {coords.x, coords.y + 1};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        directions.push_back(Direction::SOUTH);
    neigh_c = {coords.x - 1, coords.y};
    if (validate_coords(neigh_c) && !_maze[neigh_c.x][neigh_c.y]->is_visited())
        directions.push_back(Direction::WEST);
    return directions;
}

bool MazeGridBuilder::remove_wall(const Coords &coords, Direction direction) {
    if (!validate_coords(coords)) {
        return false;
    }
    switch (direction) {
        case Direction::NORTH:
            if (!validate_coords({coords.x, coords.y - 1})) {
                return false;
            }
            _maze[coords.x][coords.y]->remove_wall(Direction::NORTH);
            _maze[coords.x][coords.y - 1]->remove_wall(Direction::SOUTH);
            return true;
        case Direction::EAST:
            if (!validate_coords({coords.x + 1, coords.y})) {
                return false;
            }
            _maze[coords.x][coords.y]->remove_wall(Direction::EAST);
            _maze[coords.x + 1][coords.y]->remove_wall(Direction::WEST);
            return true;
        case Direction::SOUTH:
            if (!validate_coords({coords.x, coords.y + 1})) {
                return false;
            }
            _maze[coords.x][coords.y]->remove_wall(Direction::SOUTH);
            _maze[coords.x][coords.y + 1]->remove_wall(Direction::NORTH);
            return true;
        case Direction::WEST:
            if (!validate_coords({coords.x - 1, coords.y})) {
                return false;
            }
            _maze[coords.x][coords.y]->remove_wall(Direction::WEST);
            _maze[coords.x - 1][coords.y]->remove_wall(Direction::EAST);
            return true;
        default:
            return false;
    }
}

bool MazeGridBuilder::remove_wall(const Coords &coords, const Coords &neighbor) {
    if (coords == neighbor) {
        return false;
    }
    // check if coords and neighbor are adjacent
    if (abs(coords.x - neighbor.x) > 1 && coords.y != neighbor.y ||
        abs(coords.y - neighbor.y) > 1 && coords.x != neighbor.x
            ) {
        return false;
    }

    if (!validate_coords(coords) || !validate_coords(neighbor)) {
        return false;
    }

    // remove the walls
    if (coords.x < neighbor.x) {
        _maze[coords.x][coords.y]->remove_wall(Direction::EAST);
        _maze[neighbor.x][neighbor.y]->remove_wall(Direction::WEST);
        return true;
    } else if (coords.x > neighbor.x) {
        _maze[coords.x][coords.y]->remove_wall(Direction::WEST);
        _maze[neighbor.x][neighbor.y]->remove_wall(Direction::EAST);
        return true;
    } else if (coords.y < neighbor.y) {
        _maze[coords.x][coords.y]->remove_wall(Direction::SOUTH);
        _maze[neighbor.x][neighbor.y]->remove_wall(Direction::NORTH);
        return true;
    } else if (coords.y > neighbor.y) {
        _maze[coords.x][coords.y]->remove_wall(Direction::NORTH);
        _maze[neighbor.x][neighbor.y]->remove_wall(Direction::SOUTH);
        return true;
    }
    return false;
}

MazeGrid MazeGridBuilder::get_grid() const {
    return {_maze};
}
