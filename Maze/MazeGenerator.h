#pragma once

#include <memory>
#include <utility>

#include "../types.h"
#include "Maze.h"
#include "../Output/Observer.h"
#include "../Structures/DisjointSet.h"

class MazeGeneratorException : public std::exception {
public:
    explicit MazeGeneratorException(std::string message) : message_(std::move(message)) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class MazeGenerator {
public:
    explicit MazeGenerator(Size& size);
    MazeGenerator(int width, int height);
    MazeGenerator(MazeGenerator& other);

    MazeGenerator& set_size(const Size& size);
    MazeGenerator& set_size(int width, int height);
    MazeGenerator& set_width(int width);
    MazeGenerator& set_height(int height);

    MazeGenerator& set_start(const Coords& start);
    MazeGenerator& set_start(int x, int y);

    MazeGenerator& set_end(const Coords& end);
    MazeGenerator& set_end(int x, int y);

    MazeGenerator& set_algorithm(const std::string& algorithm);

    MazeGenerator& set_seed(int seed);
    MazeGenerator& reset_seed();

    MazeGenerator& addObserver(const std::shared_ptr<Observer>& observer);
    std::unique_ptr<Maze> generate();

    static std::vector<std::string> get_algorithms();
private:
    std::unique_ptr<MazeGridBuilder> _maze_builder;

    bool generateDFS(bool notify_observers);
    bool generateKruskal(bool notify_observers);
//    bool generateWilson(bool notify_observers);


    bool valid_coords_settings(Coords c) const;
    bool validate_settings() const;
    std::vector<std::shared_ptr<Observer>> _observers;
    void notify_observers(Coords coords) const;

    Coords get_neigh_coords(const Coords& coords, Direction direction) const;

    Size _size = {10, 5};
    Coords _start = {0, 0};
    Coords _end = {_size.width - 1, _size.height - 1};
    std::string _algorithm = "dfs";
    int _seed = 0;

    static const std::vector<std::string> algorithms;

};
