#include <iostream>
#include <memory>
#include "Maze/Maze.h"
#include "Maze/MazeGenerator.h"
#include "Output/MazeImage.h"
#include "opencv2/opencv.hpp"


using std::cout;
using std::endl;


int main() {
    MazeGenerator mg = MazeGenerator(50, 50).set_seed(2);
    std::shared_ptr<MazeVideo> mv = std::make_shared<MazeVideo>();
    mg.addObserver(mv);
    mg.set_seed(1);
    std::unique_ptr<Maze> maze = mg.generate();
    maze->print();
    cout << "Algorithm: " << maze->get_algorithm() << endl;
    cout << "Size: " << maze->get_size().width << ", " << maze->get_size().height << endl;


    cout << "Time: " << maze->get_gen_time().count() << " milliseconds" << endl;
    cout << "Seed: " << maze->get_seed() << endl;
    cout << "Start: " << maze->get_start().x << ", " << maze->get_start().y << endl;
    cout << "End: " << maze->get_end().x << ", " << maze->get_end().y << endl;

    MazeImage maze_image = MazeImage(*maze);
    maze_image.set_cell_size(15);
    maze_image.set_wall_size(1);
    maze_image.set_wall_color(cv::Scalar(255, 255, 255));
    maze_image.set_background_color(cv::Scalar(0, 0, 0));
    maze_image.generate();
    auto maze_img = maze_image.get_image();
    cv::imshow("Maze", maze_img);
    cv::waitKey(0);

    return 0;
}
