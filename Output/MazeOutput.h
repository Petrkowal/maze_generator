#pragma once

#include "opencv2/opencv.hpp"
#include "../types.h"
#include "../Maze/Maze.h"

class MazeOutput {
public:
    MazeOutput() = default;

    virtual ~MazeOutput() = default;

    MazeOutput &set_maze(const Maze &maze){
        _grid = maze.get_grid();
        return *this;
    }

    MazeOutput &set_cell_size(int size){
        _cell_size = size;
        return *this;
    }

    MazeOutput &set_wall_size(int size){
        _wall_size = size;
        return *this;
    }

    MazeOutput &set_wall_color(const cv::Scalar &color){
        _wall_color = color;
        return *this;
    }

    MazeOutput &set_background_color(const cv::Scalar &color){
        _background_color = color;
        return *this;
    }

    MazeOutput &set_filename(const std::string &filename){
        if (filename.empty()) {
            throw std::invalid_argument("Filename cannot be empty");
        }
        _filename = filename;
        return *this;
    }

protected:
    std::string _filename;
    int _cell_size = 30;
    int _wall_size = 2;
    cv::Scalar _wall_color = cv::Scalar(255, 255, 255);
    cv::Scalar _background_color = cv::Scalar(0, 0, 0);
    MazeGrid _grid;


    cv::Mat generate_image(const MazeGrid &grid, int cell_size, int wall_size, const cv::Scalar &wall_color,
                           const cv::Scalar &background_color) const {
        int width = grid.size();
        int height = grid[0].size();
        cv::Mat maze_img(height * (cell_size + wall_size) + wall_size,
                         width * (cell_size + wall_size) + wall_size,
                         CV_8UC3, background_color);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                std::shared_ptr<Cell> cell = grid[x][y];
                int cell_x = x * (cell_size + wall_size);
                int cell_y = y * (cell_size + wall_size);

                if (cell->is_start()) {
                    cv::rectangle(maze_img,
                                  cv::Point(cell_x, cell_y),
                                  cv::Point(cell_x + cell_size + wall_size * 2, cell_y + cell_size + wall_size * 2),
                                  cv::Scalar(0, 255, 0),
                                  cv::FILLED);

                }
                if (cell->is_end()) {
                    cv::rectangle(maze_img,
                                  cv::Point(cell_x, cell_y),
                                  cv::Point(cell_x + cell_size + wall_size * 2, cell_y + cell_size + wall_size * 2),
                                  cv::Scalar(0, 0, 255),
                                  cv::FILLED);
                }
                if (cell->has_wall(Direction::NORTH)) {
                    cv::rectangle(maze_img,
                                  cv::Point(cell_x, cell_y),
                                  cv::Point(cell_x + cell_size + wall_size * 2, cell_y + wall_size),
                                  wall_color,
                                  cv::FILLED);
                }
                if (cell->has_wall(Direction::EAST)) {
                    cv::rectangle(maze_img,
                                  cv::Point(cell_x + cell_size + wall_size, cell_y),
                                  cv::Point(cell_x + cell_size + wall_size * 2, cell_y + cell_size + wall_size * 2),
                                  wall_color,
                                  cv::FILLED);
                }
                if (cell->has_wall(Direction::SOUTH)) {
                    cv::rectangle(maze_img,
                                  cv::Point(cell_x, cell_y + cell_size + wall_size),
                                  cv::Point(cell_x + cell_size + wall_size * 2, cell_y + cell_size + wall_size * 2),
                                  wall_color,
                                  cv::FILLED);
                }
                if (cell->has_wall(Direction::WEST)) {
                    cv::rectangle(maze_img,
                                  cv::Point(cell_x, cell_y),
                                  cv::Point(cell_x + wall_size, cell_y + cell_size + wall_size * 2),
                                  wall_color,
                                  cv::FILLED);
                }

            }
        }
        return maze_img;
    }
};