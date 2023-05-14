#include "MazeVideo.h"

MazeVideo::MazeVideo(std::string &filename) {
    if (filename.empty())
        throw std::invalid_argument("Filename cannot be empty");
    _filename = filename;
    _fps = 30;
    _frame_size = {0, 0};
    _video = cv::VideoWriter();
}

MazeVideo &MazeVideo::set_fps(int fps) {
    _fps = fps;
    return *this;
}

void MazeVideo::update(const MazeGrid &grid, Coords current_point) {
    if (_frame_size == Size{0, 0}) {
        _frame_size = {static_cast<int>(grid.size()), static_cast<int>(grid[0].size())};
        _video.open(_filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), _fps,
                    cv::Size(_frame_size.width, _frame_size.height));
    }
    if (grid != _grid) {
        _grid = grid;
        _frame = generate_image(_grid, _cell_size, _wall_size, _wall_color, _background_color);
    }
    if (!_video.isOpened())
        return;
    _video.write(_frame);
}

void MazeVideo::save_video() {
    if (_video.isOpened())
        _video.release();
}
