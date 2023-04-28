#include "MazeGenerator.h"


MazeGenerator::MazeGenerator() {

}

Maze *MazeGenerator::generate_maze() {
    return generate(DEFAULT_SIZE);
}

Maze *MazeGenerator::generate(Size size) {
    Size s = size;
    auto *maze = new Maze(size);

    return maze;
    //return new Maze(size);
}
