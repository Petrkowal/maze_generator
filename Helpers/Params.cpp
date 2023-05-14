#include "Params.h"

Params::Params(int argc, char **argv) {
    try {

        for (auto i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-h" || arg == "--help") {
                print_help();
                exit(0);
            } else if (arg == "-a" || arg == "--algorithm") {
                _algorithm = argv[++i];
            } else if (arg == "--seed") {
                _seed = std::stoi(argv[++i]);
            } else if (arg == "-s" || arg == "--size") {
                int w = std::stoi(argv[++i]);
                int h = std::stoi(argv[++i]);
                _size = {w, h};
            } else if (arg == "-b" || arg == "--begin") {
                _start = {std::stoi(argv[++i]), std::stoi(argv[++i])};
            } else if (arg == "-e" || arg == "--end") {
                _end = {std::stoi(argv[++i]), std::stoi(argv[++i])};
            } else if (arg == "--no-image") {
                _image = false;
            } else if (arg == "--no-video") {
                _video = false;
            } else if (arg == "--out-video") {
                _output_video_name = argv[++i];
            } else if (arg == "--out-image") {
                _output_image_name = argv[++i];
            } else if (arg == "-fps") {
                _video_fps = std::stoi(argv[++i]);
            } else if (arg == "--cell-size") {
                _cell_size = std::stoi(argv[++i]);
            } else if (arg == "--wall-width") {
                _wall_size = std::stoi(argv[++i]);
            } else if (arg == "--wall-color") {
                // Can't inline this, order of evaluation is not guaranteed! (++i)
                int r = std::stoi(argv[++i]);
                int g = std::stoi(argv[++i]);
                int b = std::stoi(argv[++i]);
                _wall_color = cv::Scalar(b, g, r);
            } else if (arg == "--background-color") {
                // Can't inline this, order of evaluation is not guaranteed! (++i)
                int r = std::stoi(argv[++i]);
                int g = std::stoi(argv[++i]);
                int b = std::stoi(argv[++i]);
                _background_color = cv::Scalar(b, g, r);
            } else if (arg == "--current-cell-color") {
                // Can't inline this, order of evaluation is not guaranteed! (++i)
                int r = std::stoi(argv[++i]);
                int g = std::stoi(argv[++i]);
                int b = std::stoi(argv[++i]);
                _current_cell_color_video = cv::Scalar(b, g, r);
            } else if (arg == "--start-color") {
                // Can't inline this, order of evaluation is not guaranteed! (++i)
                int r = std::stoi(argv[++i]);
                int g = std::stoi(argv[++i]);
                int b = std::stoi(argv[++i]);
                _start_cell_color = cv::Scalar(b, g, r);
            } else if (arg == "--end-color") {
                // Can't inline this, order of evaluation is not guaranteed! (++i)
                int r = std::stoi(argv[++i]);
                int g = std::stoi(argv[++i]);
                int b = std::stoi(argv[++i]);
                _end_cell_color = cv::Scalar(b, g, r);
            } else {
                std::cerr << "Unknown argument: " << arg << std::endl;
                print_help();
                exit(1);
            }
        }
        std::vector<std::string> algorithms = MazeGenerator::get_algorithms();
        if (_algorithm.empty()) {
            _algorithm = algorithms[0];
        }
        if (_end.x == -1 || _end.y == -1) {
            _end = {_size.width - 1, _size.height - 1};
        }
    }
    catch (std::exception &e) {
        std::cerr << "Error parsing arguments"<< std::endl;
        print_help();
        exit(1);
    }

}

void Params::print_help() {
    std::cout << "Usage: maze [options]\n"
                 "Options:\n"
                 "  -h, --help\t\t\t\tShow this help message and exit\n"
                 "  -a, --algorithm <alg>\t\t\tAlgorithm to use (dfs, kruskal)\n"
                 "  -s, --size <width> <height>\t\tSize of the maze in cells\n"
                 "  -b, --begin <x> <y>\t\t\tStart point of the maze\n"
                 "  -e, --end <x> <y>\t\t\tEnd point of the maze\n"
                 "  -fps <fps>\t\t\t\tFrames per second for video\n"
                 "  --seed <seed>\t\t\t\tSeed for random number generator\n"
                 "  --no-image\t\t\t\tDo not generate image\n"
                 "  --no-video\t\t\t\tDo not generate video\n"
                 "  --out-video <filename>\t\tOutput video name\n"
                 "  --out-image <filename>\t\tOutput image name\n"
                 "  --cell-size <size_in_px>\t\tSize of each cell in pixels\n"
                 "  --wall-width <size_in_px>\t\tWidth of the walls in pixels\n"
                 "  --wall-color <r> <g> <b>\t\tColor of the walls (r g b)\n"
                 "  --background-color <r> <g> <b>\tColor of the background (r g b)\n"
                "  --current-cell-color <r> <g> <b>\tColor of the current cell in video (r g b)\n";
}
