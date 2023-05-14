#include "MazeVideo.h"

MazeVideo::MazeVideo(const std::string &filename) {
    if (filename.empty())
        throw std::invalid_argument("Filename cannot be empty");
    _filename = filename;
    _fps = 15;
    _frame_size = {0, 0};
    _current_cell_color = {255, 0, 0};
    _video = cv::VideoWriter();
}

MazeVideo &MazeVideo::set_fps(int fps) {
    _fps = fps;
    return *this;
}

MazeVideo &MazeVideo::set_current_cell_color(const cv::Scalar &color) {
    _current_cell_color = color;
    return *this;
}

void MazeVideo::update(const MazeGrid &grid, Coords current_point) {
    if (_frame_size == Size{0, 0}) {
        _frame = generate_image(grid, _cell_size, _wall_size, _wall_color, _background_color);
        _frame_size.width = _frame.cols;
        _frame_size.height = _frame.rows;
        _video = cv::VideoWriter(_filename + ".mp4", cv::VideoWriter::fourcc('a','v','c','1'), _fps,
                    cv::Size(_frame_size.width, _frame_size.height), true);
    }

    for(const auto& _inner : _grid){

    }

    _grid = grid;
    _frame = generate_image_with_current(_grid, _cell_size, _wall_size, _wall_color, _background_color, current_point,
                                         _current_cell_color);


    if (!_video.isOpened())
        return;
    _video.write(_frame);
}

void MazeVideo::save_video() {
    if (_video.isOpened()){
        _frame = generate_image(_grid, _cell_size, _wall_size, _wall_color, _background_color);
        _video.write(_frame);
        _video.release();
    }
}

MazeVideo::~MazeVideo() {
    if (_video.isOpened())
        _video.release();
}
