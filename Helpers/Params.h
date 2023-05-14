#pragma once

#include <string>
#include <random>
#include <opencv2/core/types.hpp>
#include "../types.h"
#include "../Maze/MazeGenerator.h"

class Params {
public:
    Params(int argc, char** argv);

    static void print_help();

    std::string get_algorithm() const { return _algorithm;}
    int get_seed() const { return _seed;}
    Size get_size() const { return _size;}
    Coords get_start() const { return _start;}
    Coords get_end() const { return _end;}
    bool is_image() const { return _image;}
    bool is_video() const { return _video;}
    std::string get_output_video_name() const { return _output_video_name;}
    std::string get_output_image_name() const { return _output_image_name;}
    int get_video_fps() const { return _video_fps;}
    int get_cell_size() const { return _cell_size;}
    int get_wall_size() const { return _wall_size;}
    cv::Scalar get_wall_color() const { return _wall_color;}
    cv::Scalar get_background_color() const { return _background_color;}
    cv::Scalar get_current_cell_color() const { return _current_cell_color_video;}
    cv::Scalar get_start_color() const { return _start_cell_color;}
    cv::Scalar get_end_color() const { return _end_cell_color;}

private:
    int _seed = 0;
    std::string _algorithm;
    Size _size = {10, 10};
    Coords _start = {0, 0};
    Coords _end = {-1, -1};
    bool _image = true;
    bool _video = true;
    std::string _output_video_name = "maze";
    std::string _output_image_name = "maze";
    int _video_fps = 15;
    int _cell_size = 30;
    int _wall_size = 2;
    cv::Scalar _wall_color = cv::Scalar(255, 255, 255);
    cv::Scalar _background_color = cv::Scalar(0, 0, 0);
    cv::Scalar _current_cell_color_video = cv::Scalar(255, 0, 0);
    cv::Scalar _start_cell_color = cv::Scalar(0, 255, 0);
    cv::Scalar _end_cell_color = cv::Scalar(0, 0, 255);
};

