#pragma once

#include "../Maze/Maze.h"
#include "opencv2/opencv.hpp"
#include "MazeOutput.h"

class MazeImage : public MazeOutput{
public:
    MazeImage(const Maze& maze);
    MazeImage(MazeGrid  grid);

    cv::Mat get_image() const;

    void generate();
    void save(const std::string &filename);
private:
    cv::Mat _image;
};

