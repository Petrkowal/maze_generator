#pragma once
#include "../Maze/Maze.h"
#include "../Maze/MazeGenerator.h"
#include "opencv2/opencv.hpp"

class Observer{
public:
    virtual void update(const MazeGrid& grid) = 0;
};
#include <iostream>
class MazeVideo : public Observer {
public:
    MazeVideo();
    void update(const MazeGrid& grid) override {
        std::cout<< "update" << std::endl;
    };
private:
    Coords _size = {0, 0};

};
