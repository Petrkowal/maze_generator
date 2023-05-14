#include "DisjointSet.h"


DisjointSet::DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

}

int DisjointSet::find(int x) {
    if(parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void DisjointSet::union_sets(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);

    if (x_root == y_root) {
        return;
    }
    if(rank[x_root] < rank[y_root]) {
        parent[x_root] = y_root;
    } else if (rank[x_root] > rank[y_root]) {
        parent[y_root] = x_root;
    } else {
        parent[y_root] = x_root;
        rank[x_root]++;
    }
}

bool DisjointSet::is_connected(int x, int y) {
    return find(x) == find(y);
}
