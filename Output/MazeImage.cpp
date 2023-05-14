#include "MazeImage.h"


MazeImage::MazeImage(const Maze &maze) : _maze(std::make_unique<Maze>(maze)) {
    _image = cv::Mat();
}

MazeImage &MazeImage::set_maze(const Maze &maze) {
    _maze = std::make_unique<Maze>(maze);
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
    int height = _maze->get_size().height;
    int width = _maze->get_size().width;
    cv::Mat maze_img(height * (_cell_size + _wall_size) + _wall_size,
                     width * (_cell_size + _wall_size) + _wall_size,
                     CV_8UC3, _background_color);
    Coords start = _maze->get_start();
    Coords end = _maze->get_end();
    cv::rectangle(maze_img,
                  cv::Point(start.x * (_cell_size + _wall_size) + _wall_size,
                            start.y * (_cell_size + _wall_size) + _wall_size),
                  cv::Point(start.x * (_cell_size + _wall_size) + _wall_size + _cell_size,
                            start.y * (_cell_size + _wall_size) + _wall_size + _cell_size),
                  cv::Scalar(0, 255, 0),
                  cv::FILLED);
    cv::rectangle(maze_img,
                  cv::Point(end.x * (_cell_size + _wall_size) + _wall_size,
                            end.y * (_cell_size + _wall_size) + _wall_size),
                  cv::Point(end.x * (_cell_size + _wall_size) + _wall_size + _cell_size,
                            end.y * (_cell_size + _wall_size) + _wall_size + _cell_size),
                  cv::Scalar(0, 0, 255),
                  cv::FILLED);

    for (int x = 0; x < _maze->get_size().width; x++) {
        for (int y = 0; y < _maze->get_size().height; y++) {
            std::shared_ptr<Cell> cell = _maze->get_grid()[x][y];
            int cell_x = x * (_cell_size + _wall_size);
            int cell_y = y * (_cell_size + _wall_size);


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

