#include <iostream>
#include <random>

#include "MazeGenerator.h"

using std::cout;
using std::endl;

int main() {
   MazeGenerator mg = MazeGenerator();
   Maze* maze = mg.generate_maze();
   maze->print();
//    Maze m(10,5);
//    m.generate();
}
