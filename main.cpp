#include <iostream>
#include <memory>
#include <csignal>
#include "Maze/Maze.h"
#include "Maze/MazeGenerator.h"
#include "Output/MazeImage.h"
#include "Output/MazeVideo.h"
#include "opencv2/opencv.hpp"
#include "Helpers/Params.h"


using std::cout;
using std::endl;

int main(int argc, char** argv) {
    Params params = Params(argc, argv);
    Size maze_size = params.get_size();

    MazeGenerator mg = MazeGenerator(maze_size)
            .set_seed(params.get_seed())
            .set_algorithm(params.get_algorithm())
            .set_start(params.get_start())
            .set_end(params.get_end());


    std::unique_ptr<Maze> maze;

    if (params.is_video()) {
        std::shared_ptr<MazeVideo> mv = std::make_shared<MazeVideo>(params.get_output_video_name());
        mv->set_fps(params.get_video_fps());
        mv->set_background_color(params.get_background_color());
        mv->set_wall_color(params.get_wall_color());
        mv->set_start_color(params.get_start_color());
        mv->set_end_color(params.get_end_color());
        mv->set_current_cell_color(params.get_current_cell_color());
        mg.addObserver(mv);
        maze = mg.generate();
        mv->save_video();
    }
    else
        maze = mg.generate();



    maze->print();
    cout << "Algorithm: " << maze->get_algorithm() << endl;
    cout << "Size: " << maze->get_size().width << ", " << maze->get_size().height << endl;


    cout << "Time: " << maze->get_gen_time().count() << " milliseconds" << endl;
    cout << "Seed: " << maze->get_seed() << endl;
    cout << "Start: " << maze->get_start().x << ", " << maze->get_start().y << endl;
    cout << "End: " << maze->get_end().x << ", " << maze->get_end().y << endl;

    MazeImage maze_image = MazeImage(*maze);
    maze_image.set_cell_size(params.get_cell_size());
    maze_image.set_wall_size(params.get_wall_size());
    maze_image.set_wall_color(params.get_wall_color());
    maze_image.set_background_color(params.get_background_color());
    maze_image.set_start_color(params.get_start_color());
    maze_image.set_end_color(params.get_end_color());
    maze_image.generate();
    if (params.is_image())
        maze_image.save(params.get_output_image_name());
    auto maze_img = maze_image.get_image();
    cv::imshow("Maze", maze_img);
    cv::waitKey(0);


    return 0;
}
