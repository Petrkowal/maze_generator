#include <chrono>
#include <algorithm>
#include "MazeGenerator.h"

const std::vector<std::string> MazeGenerator::algorithms = {"dfs", "kruskal"};

MazeGenerator::MazeGenerator(Size &size) : _size(size) {
    validate_settings();
    _maze_builder = std::make_unique<MazeGridBuilder>(_size);
}

MazeGenerator::MazeGenerator(int width, int height) : _size({width, height}) {
    validate_settings();
    _maze_builder = std::make_unique<MazeGridBuilder>(_size);
}

MazeGenerator::MazeGenerator(MazeGenerator &other) : _size(other._size), _start(other._start), _end(other._end),
                                                     _algorithm(other._algorithm), _seed(other._seed) {
    _maze_builder = std::move(other._maze_builder);
}

MazeGenerator &MazeGenerator::set_size(const Size &size) {
    _size = size;
    validate_settings();
    return *this;
}

MazeGenerator &MazeGenerator::set_size(int width, int height) {
    return set_size({width, height});
}

MazeGenerator &MazeGenerator::set_width(int width) {
    return set_size({width, _size.height});
}

MazeGenerator &MazeGenerator::set_height(int height) {
    return set_size({_size.width, height});
}

MazeGenerator &MazeGenerator::set_start(const Coords &start) {
    _start = start;
    validate_settings();
    return *this;
}

MazeGenerator &MazeGenerator::set_start(int x, int y) {
    return set_start({x, y});
}

MazeGenerator &MazeGenerator::set_end(const Coords &end) {
    _end = end;
    validate_settings();
    return *this;
}

MazeGenerator &MazeGenerator::set_end(const int x, const int y) {
    return set_end({x, y});
}

MazeGenerator &MazeGenerator::set_algorithm(const std::string &algorithm) {
    std::string algo = algorithm;
    std::transform(algo.begin(), algo.end(), algo.begin(), ::tolower);
    algo.erase(std::remove_if(algo.begin(), algo.end(), [](char c) { return !isprint(c); }), algo.end());
    _algorithm = algo;
    validate_settings();
    return *this;
}

MazeGenerator &MazeGenerator::set_seed(const int seed) {
    _seed = seed;
    validate_settings();
    return *this;
}

MazeGenerator &MazeGenerator::reset_seed() {
    _seed = 0;
    validate_settings();
    return *this;
}

bool MazeGenerator::validate_settings() const {
    if (_size.width < 2 || _size.height < 2) {
        throw MazeGeneratorException("Size must be greater than 1");
    }
    if (!valid_coords_settings(_start)) {
        throw MazeGeneratorException(
                "Start coordinates must be within the maze: (0, 0) - (" + std::to_string(_size.width) + ", " +
                std::to_string(_size.height) + ")");
    }
    if (!valid_coords_settings(_end)) {
        throw MazeGeneratorException(
                "End coordinates must be within the maze: (0, 0) - " + std::to_string(_size.width) + ", " +
                std::to_string(_size.height) + ")");
    }
    if (_start == _end) {
        throw MazeGeneratorException("Start and end coordinates must be different");
    }
    if (_seed < 0) {
        throw MazeGeneratorException("Seed must be greater than 0");
    }
    if (std::find(algorithms.begin(), algorithms.end(), _algorithm) == algorithms.end()) {
        throw MazeGeneratorException(
                "Algorithm must be one of: " + std::accumulate(std::next(algorithms.begin()), algorithms.end(),
                                                               algorithms[0],
                                                               [](const std::string& a, const std::string& b) {
                                                                   return a + ", " + b;
                                                               }));
    }

    return true;
}

Coords MazeGenerator::get_neigh_coords(const Coords &coords, Direction direction) const {
    switch (direction) {
        case Direction::NORTH:
            return {coords.x, coords.y - 1};
        case Direction::EAST:
            return {coords.x + 1, coords.y};
        case Direction::SOUTH:
            return {coords.x, coords.y + 1};
        case Direction::WEST:
            return {coords.x - 1, coords.y};
    }
    return {-1, -1};
}

std::unique_ptr<Maze> MazeGenerator::generate() {
    validate_settings(); // should be valid... just in case
    if (_seed == 0) {
        _seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    _maze_builder->create_empty_grid();
    _maze_builder->get_cell(_start)->set_start().set_visited();
    _maze_builder->get_cell(_end)->set_end();

    auto start = std::chrono::high_resolution_clock::now();
    if (_algorithm == "dfs") {
        generateDFS(false);
    }
    if (_algorithm == "kruskal") {
        generateKruskal(false);
    }
//    if (_algorithm == "wilson") {
//        generateWilson(false);
//    }
    auto end = std::chrono::high_resolution_clock::now();
    auto gen_time = std::chrono::duration<double>(end - start);
    auto maze = std::make_unique<Maze>(_size, _start, _end, _seed, _algorithm, gen_time, _maze_builder->get_grid());

    _maze_builder->create_empty_grid();
    _maze_builder->get_cell(_start)->set_start().set_visited();
    _maze_builder->get_cell(_end)->set_end();

    if (!_observers.empty()) { // generate again for the video
        if (_algorithm == "dfs")
            generateDFS(true);
        if (_algorithm == "kruskal")
            generateKruskal(true);
//        if (_algorithm == "wilson")
//            generateWilson(true);
    }

    return maze;
}

bool MazeGenerator::generateDFS(bool notify) {
    std::default_random_engine rd(_seed);
    std::uniform_int_distribution<int> distribution(0, 3);
    Coords current_point = _start;
    std::vector<Direction> unvisited_neighbors;
    std::stack<Coords> gen_path;
    gen_path.push(current_point);

    while (!gen_path.empty()) {
        unvisited_neighbors.clear();
        current_point = gen_path.top();
        gen_path.pop();

        unvisited_neighbors = _maze_builder->get_unvisited_directions(current_point);
        if (unvisited_neighbors.empty())
            continue;
        gen_path.push(current_point);
        std::shuffle(unvisited_neighbors.begin(), unvisited_neighbors.end(), rd);

        _maze_builder->remove_wall(current_point, unvisited_neighbors[0]);
        _maze_builder->get_neighbor_cell(current_point, unvisited_neighbors[0])->set_visited();
        current_point = get_neigh_coords(current_point, unvisited_neighbors[0]);
        if (notify)
            notify_observers(current_point);
        gen_path.push(current_point);
    }
    return true;
}


bool MazeGenerator::generateKruskal(bool notify) {
    int cells = _size.width * _size.height;
    std::vector<std::pair<std::shared_ptr<Cell>, Direction>> walls;

    for (int row = 0; row < _size.height; row++) {
        for (int col = 0; col < _size.width; col++) {
            auto cell = _maze_builder->get_cell({col, row});
            if (row > 0) {
                walls.emplace_back(cell, Direction::NORTH);
            }
            if (col > 0) {
                walls.emplace_back(cell, Direction::WEST);
            }
        }
    }
    std::shuffle(walls.begin(), walls.end(), std::default_random_engine(_seed));

    DisjointSet ds(cells);
    int connected_cells = 1;
    for (const auto &wall: walls) {
        auto cell = wall.first;
        auto direction = wall.second;
        auto cell_coords = _maze_builder->get_cell_coords(cell);
        if (cell_coords == Coords{-1, -1}) {
            throw MazeGeneratorException("Cell not found");
        }
        auto neighbor = _maze_builder->get_neighbor_cell(cell_coords, direction);
        if (!neighbor) {
            continue;
        }
        auto neighbor_coords = _maze_builder->get_cell_coords(neighbor);
        if (neighbor_coords == Coords{-1, -1}) {
            throw MazeGeneratorException("Neighbor not found");
        }

        if (!ds.is_connected(
                cell_coords.y * _size.width + cell_coords.x,
                neighbor_coords.y * _size.width + neighbor_coords.x)) {
            _maze_builder->remove_wall(cell_coords, direction);
            ds.union_sets(cell_coords.y * _size.width + cell_coords.x,
                          neighbor_coords.y * _size.width + neighbor_coords.x);
            connected_cells++;
            if (notify)
                notify_observers(neighbor_coords);
        }

        if (connected_cells == cells) {
            break;
        }

    }
    return true;

}

bool MazeGenerator::valid_coords_settings(Coords c) const {
    return c.x >= 0 && c.x < _size.width && c.y >= 0 && c.y < _size.height;
}

MazeGenerator &MazeGenerator::addObserver(const std::shared_ptr<Observer> &observer) {
    _observers.push_back(observer);
    return *this;
}

void MazeGenerator::notify_observers(Coords coords) const {
    for (auto &observer: _observers) {
        observer->update(_maze_builder->get_grid(), coords);
    }
}

std::vector<std::string> MazeGenerator::get_algorithms() {
    return algorithms;
}