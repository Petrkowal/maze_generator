#include <iostream>
#include <memory>
#include "Maze/MazeGenerator.h"
#include "opencv2/opencv.hpp"


using std::cout;
using std::endl;

int main() {
    MazeGenerator mg = MazeGenerator(10, 5).setSeed(2);
    mg.setSeed(1);
    std::unique_ptr<Maze> maze = mg.generate();
    maze->print();
    cout << "Algorithm: " << maze->get_algorithm() << endl;
    cout << "Size: " << maze->get_size().width << ", " << maze->get_size().height << endl;


    cout << "Time: " << maze->get_gen_time().count() << " milliseconds" << endl;
    cout << "Seed: " << maze->get_seed() << endl;
    cout << "Start: " << maze->get_start().x << ", " << maze->get_start().y << endl;
    cout << "End: " << maze->get_end().x << ", " << maze->get_end().y << endl;

    // create opencv image
    cv::Mat img(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));
    // draw rectangle
    cv::rectangle(img, cv::Point(100, 50), cv::Point(280, 200), cv::Scalar(0, 0, 255), 2);
    // show image
    cv::imshow("Image", img);
    // wait for key to close window
    cv::waitKey(0);

//    cv::Mat img(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));
//    cv::rectangle(img, cv::Point(100, 50), cv::Point(280, 200), cv::Scalar(0, 0, 255), 2);
//    cv::imshow("Image", img);
//    cv::waitKey(0);

    return 0;
}
