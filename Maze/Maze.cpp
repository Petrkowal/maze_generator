#include "Maze.h"

Maze::Maze(const Size &size) : _size(size) {
    _maze.resize(_size.x, std::vector<Cell>(_size.y));
    for (auto& col : _maze){
        for (auto& cell : col){
            cell = Cell{0b1111};
        }
    }
}

bool Maze::valid_coords(Coords c) const {
    return c.x >= 0 && c.x < _size.x && c.y >= 0 && c.y < _size.y;
}

void Maze::print() const {
    int cols = _maze.size();
    int rows = _maze[0].size();

    for(int i = 0;i < 30; i++){
        std::cout << std::endl;
    }

    std::cout << "+";
    for (int col = 0; col < cols; col++) {
        std::cout << "---+";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << "|";
        for (int col = 0; col < cols; col++) {
            if (_maze[col][row].has_wall(Direction::E)) {
                if (col == _start_coords.x && row == _start_coords.y) {
                    std::cout << " S |";
                }
                else if(col == _current_coords.x && row == _current_coords.y){
                    std::cout << " * |";
                }
                else {
                    std::cout << "   |";
                }
            } else {
                if (col == _start_coords.x && row == _start_coords.y) {
                    std::cout << " S  ";
                }
                else if(col == _current_coords.x && row == _current_coords.y){
                    std::cout << " *  ";
                }
                else {
                    std::cout << "    ";
                }
            }
        }
        std::cout << std::endl;

        std::cout << "+";
        for (int col = 0; col < cols; col++) {
            if (_maze[col][row].has_wall(Direction::S)) {
                std::cout << "---+";
            } else {
                std::cout << "   +";
            }
        }
        std::cout << std::endl;
    }
}

//void Maze::generate() {
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(1, 10);
//    Coords new_point;
//    Coords last_point;
//    int dir;
//    std::vector<int> unvisited_neighbors;
//    while (path.size() > 0) {
//        Sleep(500);
//        this->print();
//        unvisited_neighbors.clear();
//        last_point = path.top();
//        path.pop();
//
//        new_point = last_point;
//        new_point.y--;
//        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].is_visited()) {
//            unvisited_neighbors.push_back(0);
//        }
//        new_point = last_point;
//        new_point.x++;
//        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].is_visited()) {
//            unvisited_neighbors.push_back(1);
//        }
//        new_point = last_point;
//        new_point.y++;
//        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].is_visited()) {
//            unvisited_neighbors.push_back(2);
//        }
//        new_point = last_point;
//        new_point.x--;
//        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].is_visited()) {
//            unvisited_neighbors.push_back(3);
//        }
//        if (!unvisited_neighbors.empty()) {
//            path.push(last_point);
//            std::shuffle(unvisited_neighbors.begin(), unvisited_neighbors.end(), rd);
//
//            new_point = last_point;
//            switch (unvisited_neighbors[0]) {
//                case 0: // up
//                    new_point.y--;
//                    maze[last_point.x][last_point.y].remove_wall(Direction::N);
//                    maze[new_point.x][new_point.y].remove_wall(Direction::S);
//                    break;
//                case 1: // right
//                    new_point.x++;
//                    maze[last_point.x][last_point.y].remove_wall(Direction::E);
//                    maze[new_point.x][new_point.y].remove_wall(Direction::W);
//                    break;
//                case 2: // down
//                    new_point.y++;
//                    maze[last_point.x][last_point.y].remove_wall(Direction::S);
//                    maze[new_point.x][new_point.y].remove_wall(Direction::N);
//                    break;
//                case 3: // left
//                    new_point.x--;
//                    maze[last_point.x][last_point.y].remove_wall(Direction::W);
//                    maze[new_point.x][new_point.y].remove_wall(Direction::E);
//                    break;
//                default:
//                    break;
//            }
//            maze[new_point.x][new_point.y].set_visited();
//            path.push(new_point);
//        }
//    }
//}
//
