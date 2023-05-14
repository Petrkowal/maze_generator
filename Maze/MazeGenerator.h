#pragma once

#include <memory>
#include <utility>

#include "../types.h"
#include "Maze.h"

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
    MazeGenerator(Size& size);
    MazeGenerator(int width, int height);
    MazeGenerator(MazeGenerator& other);

    MazeGenerator& setSize(const Size& size);
    MazeGenerator& setSize(int width, int height);
    MazeGenerator& setWidth(int width);
    MazeGenerator& setHeight(int height);

    MazeGenerator& setStart(const Coords& start);
    MazeGenerator& setStart(int x, int y);

    MazeGenerator& setEnd(const Coords& end);
    MazeGenerator& setEnd(int x, int y);

    MazeGenerator& setAlgorithm(const std::string& algorithm);
    MazeGenerator& setSeed(int seed);
    MazeGenerator& resetSeed();
    std::unique_ptr<Maze> generate();
private:
    std::unique_ptr<MazeGridBuilder> _maze_builder;

    bool generateDFS();
    bool valid_coords_settings(Coords c) const;
    bool validate_settings() const;
    void print(const Coords& current) const;

    Coords get_neigh_coords(const Coords& coords, Direction direction) const;

    Size _size = {10, 5};
    Coords _start = {0, 0};
    Coords _end = {9, 4};
    std::string _algorithm = "dfs";
    int _seed = 0;

    std::vector<std::string> algorithms = {"dfs"};
};
