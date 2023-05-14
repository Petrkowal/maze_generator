#pragma once
#include "../Maze/Maze.h"
#include "opencv2/opencv.hpp"
#include "Observer.h"
#include "MazeImage.h"
#include "MazeOutput.h"


#include <iostream>
class MazeVideo : public Observer, public MazeOutput {
public:
    MazeVideo(std::string &filename);
    void update(const MazeGrid& grid, Coords current_point) override;

    MazeVideo& set_fps(int fps);
    void save_video();
private:
    int _fps;
    Size _frame_size{};
    cv::VideoWriter _video;
    cv::Mat _frame;
};
