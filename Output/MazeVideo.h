#pragma once
#include "../Maze/Maze.h"
#include "opencv2/opencv.hpp"
#include "Observer.h"
#include "MazeImage.h"


#include <iostream>
class MazeVideo : public Observer {
public:
    MazeVideo(std::string fname);
    void update(const MazeGrid& grid, Coords current_point) override;
private:

    void draw_frame(const MazeGrid& grid, Coords current_point);
    Size _frame_size = {0, 0};
    MazeGrid _last_grid = {};
    int _fps = 30;
    std::string _fname;
    cv::VideoWriter _video;
    cv::Mat _frame;

};
