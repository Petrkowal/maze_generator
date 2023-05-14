#pragma once

#include <vector>

class DisjointSet {
public:
    DisjointSet(int n);
    int find(int x);
    void union_sets(int x, int y);
    bool is_connected(int x, int y);


private:
    std::vector<int> parent;
    std::vector<int> rank;
};
