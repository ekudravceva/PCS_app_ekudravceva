#include "Labyrinth.h"

Labyrinth::Labyrinth(int w, int h) : width(w), height(h), startX(0), startY(0), finishX(w-1), finishY(h-1) {
    grid.resize(height, std::vector<Cell>(width));
}

void Labyrinth::reset() {
    grid.clear();
    grid.resize(height, std::vector<Cell>(width));
    startX = 0; startY = 0;
    finishX = width-1; finishY = height-1;
}

Cell& Labyrinth::getCell(int x, int y) {
    return grid[y][x];
}

const Cell& Labyrinth::getCell(int x, int y) const {
    return grid[y][x];
}

int Labyrinth::getWidth() const { return width; }
int Labyrinth::getHeight() const { return height; }

void Labyrinth::setStart(int x, int y) {
    startX = x; startY = y;
    grid[y][x].isStart = true;
}

void Labyrinth::setFinish(int x, int y) {
    finishX = x; finishY = y;
    grid[y][x].isFinish = true;
}

std::pair<int,int> Labyrinth::getStart() const { return {startX, startY}; }
std::pair<int,int> Labyrinth::getFinish() const { return {finishX, finishY}; }

void Labyrinth::clearSearch() {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            grid[y][x].resetSearch();
}
