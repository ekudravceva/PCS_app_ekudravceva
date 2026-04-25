#ifndef CELL_H
#define CELL_H

struct Cell {
    bool walls[4] = {true, true, true, true}; // N, S, W, E
    bool visited = false;
    bool isStart = false;
    bool isFinish = false;
    bool inPath = false;
    bool visitedDuringSearch = false;

    void resetSearch() {
        visitedDuringSearch = false;
        inPath = false;
    }
};

#endif
