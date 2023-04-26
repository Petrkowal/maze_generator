#include "Maze.h"

Maze::Maze(const Size &size) : size(size) {
    init();
}

Maze::Maze(const int x, const int y) : size(Size{x, y}) {
    init();
}

void Maze::init() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_x(0, size.x);
    std::uniform_int_distribution<> random_y(0, size.y);
    maze.resize(size.x, std::vector<Cell>(size.y));
    for (auto &a: maze) {
        std::fill(a.begin(), a.begin(), Cell{});
    }
    for (auto &a: maze) {
        for (auto &b: a) {
            b.byte = 0b1111;
        }
    }
    start = {random_x(gen), random_y(gen)};
    path.push(start);
    maze[start.x][start.y].set_visited();
}


bool Maze::valid_coords(Coords c) const {
    return c.x >= 0 && c.x < this->size.x && c.y >= 0 && c.y < this->size.y;
}

void Maze::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    Coords new_point;
    Coords last_point;
    int dir;
    std::vector<int> unvisited_neighbors;
    while (path.size() > 0) {
        Sleep(500);
        this->print();
        unvisited_neighbors.clear();
        last_point = path.top();
        path.pop();

        new_point = last_point;
        new_point.y--;
        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].visited()) {
            unvisited_neighbors.push_back(N);
        }
        new_point = last_point;
        new_point.x++;
        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].visited()) {
            unvisited_neighbors.push_back(E);
        }
        new_point = last_point;
        new_point.y++;
        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].visited()) {
            unvisited_neighbors.push_back(S);
        }
        new_point = last_point;
        new_point.x--;
        if (valid_coords(new_point) && !maze[new_point.x][new_point.y].visited()) {
            unvisited_neighbors.push_back(W);
        }
        if (!unvisited_neighbors.empty()) {
            path.push(last_point);
            std::shuffle(unvisited_neighbors.begin(), unvisited_neighbors.end(), rd);

            new_point = last_point;
            switch (unvisited_neighbors[0]) {
                case N: // up
                    new_point.y--;
                    maze[last_point.x][last_point.y].remove_wall(N);
                    maze[new_point.x][new_point.y].remove_wall(S);
                    break;
                case E: // right
                    new_point.x++;
                    maze[last_point.x][last_point.y].remove_wall(E);
                    maze[new_point.x][new_point.y].remove_wall(W);
                    break;
                case S: // down
                    new_point.y++;
                    maze[last_point.x][last_point.y].remove_wall(S);
                    maze[new_point.x][new_point.y].remove_wall(N);
                    break;
                case W: // left
                    new_point.x--;
                    maze[last_point.x][last_point.y].remove_wall(W);
                    maze[new_point.x][new_point.y].remove_wall(E);
                    break;
                default:
                    break;
            }
            maze[new_point.x][new_point.y].set_visited();
            path.push(new_point);
        }
    }
}

void Maze::print() {
    int cols = maze.size();
    int rows = maze[0].size();

    std::cout << "+";
    for (int col = 0; col < cols; col++) {
        std::cout << "---+";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << "|";
        for (int col = 0; col < cols; col++) {
            if (maze[col][row].wall(E)) {
                if(col == start.x && row == start.y){
                    std::cout << " S |";
                }
                else if(col == path.top().x && row == path.top().y){
                    std::cout << " * |";
                }
                else{
                    std::cout << "   |";
                }
            } else {
                if(col == start.x && row == start.y){
                    std::cout << " S  ";
                }
                else if(col == path.top().x && row == path.top().y){
                    std::cout << " *  ";
                }
                else{
                    std::cout << "    ";
                }
            }
        }
        std::cout << std::endl;

        std::cout << "+";
        for (int col = 0; col < cols; col++) {
            if (maze[col][row].wall(S)) {
                std::cout << "---+";
            } else {
                std::cout << "   +";
            }
        }
        std::cout << std::endl;
    }
}
