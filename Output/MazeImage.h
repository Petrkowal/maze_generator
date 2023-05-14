#pragma once

#include "../Maze/Maze.h"
#include "opencv2/opencv.hpp"

class MazeImage {
public:
    MazeImage(const Maze& maze);
    MazeImage& set_maze(const Maze& maze);
    MazeImage& set_cell_size(int size);
    MazeImage& set_wall_size(int size);
    MazeImage& set_wall_color(const cv::Scalar& color);
    MazeImage& set_background_color(const cv::Scalar& color);

    cv::Mat get_image() const;

    void generate();
    void save(const std::string &filename);
private:
    std::unique_ptr<Maze> _maze;
    int _cell_size = 30;
    int _wall_size = 2;
    cv::Scalar _wall_color = cv::Scalar(255, 255, 255);
    cv::Scalar _background_color = cv::Scalar(0, 0, 0);
    cv::Mat _image;
};

