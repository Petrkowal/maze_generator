#include "MazeVideo.h"

MazeVideo::MazeVideo(std::string fname) {
    if (fname.empty()) {
        _fname = "maze.avi";
    }
}

void MazeVideo::update(const MazeGrid &grid, Coords current_point) {
    if (_frame_size == Size{0, 0}) {
        _frame_size = {static_cast<int>(grid.size()), static_cast<int>(grid[0].size())};
        _video.open(_fname, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), _fps,
                    cv::Size(_frame_size.width, _frame_size.height));

    }
    if (grid != _last_grid) {
        _last_grid = grid;
    } else {

    }
}

void MazeVideo::draw_frame(const MazeGrid &grid, Coords current_point) {

    int width = grid.size();
    int height = grid[0].size();
    cv::Mat maze_img(height * (_cell_size + _wall_size) + _wall_size,
                     width * (_cell_size + _wall_size) + _wall_size,
                     CV_8UC3, _background_color);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            std::shared_ptr<Cell> cell = grid[x][y];
            int cell_x = x * (_cell_size + _wall_size);
            int cell_y = y * (_cell_size + _wall_size);

            if (cell->is_start()) {
                cv::rectangle(maze_img,
                              cv::Point(cell_x, cell_y),
                              cv::Point(cell_x + _cell_size + _wall_size * 2, cell_y + _cell_size + _wall_size * 2),
                              cv::Scalar(0, 255, 0),
                              cv::FILLED);

            }
            if (cell->is_end()) {
                cv::rectangle(maze_img,
                              cv::Point(cell_x, cell_y),
                              cv::Point(cell_x + _cell_size + _wall_size * 2, cell_y + _cell_size + _wall_size * 2),
                              cv::Scalar(0, 0, 255),
                              cv::FILLED);
            }
            if (cell->has_wall(Direction::NORTH)) {
                cv::rectangle(maze_img,
                              cv::Point(cell_x, cell_y),
                              cv::Point(cell_x + _cell_size + _wall_size * 2, cell_y + _wall_size),
                              _wall_color,
                              cv::FILLED);
            }
            if (cell->has_wall(Direction::EAST)) {
                cv::rectangle(maze_img,
                              cv::Point(cell_x + _cell_size + _wall_size, cell_y),
                              cv::Point(cell_x + _cell_size + _wall_size * 2, cell_y + _cell_size + _wall_size * 2),
                              _wall_color,
                              cv::FILLED);
            }
            if (cell->has_wall(Direction::SOUTH)) {
                cv::rectangle(maze_img,
                              cv::Point(cell_x, cell_y + _cell_size + _wall_size),
                              cv::Point(cell_x + _cell_size + _wall_size * 2, cell_y + _cell_size + _wall_size * 2),
                              _wall_color,
                              cv::FILLED);
            }
            if (cell->has_wall(Direction::WEST)) {
                cv::rectangle(maze_img,
                              cv::Point(cell_x, cell_y),
                              cv::Point(cell_x + _wall_size, cell_y + _cell_size + _wall_size * 2),
                              _wall_color,
                              cv::FILLED);
            }

        }
    }

    _image = maze_img;
}
