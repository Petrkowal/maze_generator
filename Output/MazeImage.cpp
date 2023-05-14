#include "MazeImage.h"

#include <utility>


MazeImage::MazeImage(const Maze &maze) {
    _grid = maze.get_grid();
    _image = cv::Mat();
}

MazeImage::MazeImage(MazeGrid grid) {
    _grid = std::move(grid);
    _image = cv::Mat();
}


void MazeImage::generate() {
    _image = generate_image(_grid, _cell_size, _wall_size, _wall_color, _background_color);
}


void MazeImage::save(const std::string &filename) {
    if (_image.empty()) {
        return;
    }
    // add .png
    std::string file = filename;
    if (file.size() < 4 || file.substr(file.size() - 4) != ".png") {
        file += ".png";
    }
    cv::imwrite(file, _image);
}

cv::Mat MazeImage::get_image() const {
    return {_image};
}

