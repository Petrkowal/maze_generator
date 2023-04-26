#include <iostream>
#include <random>
#include "Maze/Maze.h"

using std::cout;
using std::endl;

int main() {
    Maze m(10,5);
    m.generate();
}
