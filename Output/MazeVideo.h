#pragma once
#include "../Maze/Maze.h"
#include "opencv2/opencv.hpp"
#include "Observer.h"
#include "MazeImage.h"
#include "MazeOutput.h"


#include <iostream>
class MazeVideo : public Observer, public MazeOutput {
public:
    MazeVideo(const std::string& filename);
    ~MazeVideo() override;
    void update(const MazeGrid& grid, Coords current_point) override;

    MazeVideo& set_fps(int fps);
    MazeVideo& set_current_cell_color(const cv::Scalar& color);
    void save_video();

private:
    int _fps;
    cv::Scalar _current_cell_color;
    Size _frame_size{};
    cv::VideoWriter _video;
    cv::Mat _frame;
};
