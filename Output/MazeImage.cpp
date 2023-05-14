#include "MazeImage.h"

#include <utility>


MazeImage::MazeImage(const Maze &maze) : _grid(maze.get_grid()) {
    _image = cv::Mat();
}

MazeImage::MazeImage(MazeGrid grid) : _grid(std::move(grid)) {
    _image = cv::Mat();
}

MazeImage &MazeImage::set_maze(const Maze &maze) {
    _grid = maze.get_grid();
    return *this;
}

MazeImage &MazeImage::set_cell_size(int size) {
    _cell_size = size;
    return *this;
}

MazeImage &MazeImage::set_wall_size(int size) {
    _wall_size = size;
    return *this;
}

MazeImage &MazeImage::set_wall_color(const cv::Scalar &color) {
    _wall_color = color;
    return *this;
}

MazeImage &MazeImage::set_background_color(const cv::Scalar &color) {
    _background_color = color;
    return *this;
}

void MazeImage::generate() {
    int width = _grid.size();
    int height = _grid[0].size();
    cv::Mat maze_img(height * (_cell_size + _wall_size) + _wall_size,
                     width * (_cell_size + _wall_size) + _wall_size,
                     CV_8UC3, _background_color);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            std::shared_ptr<Cell> cell = _grid[x][y];
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


void MazeImage::save(const std::string &filename) {

}

cv::Mat MazeImage::get_image() const {
    return {_image};
}

