#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "Cell.h"
#include <vector>
#include <utility>

class Labyrinth {
public:
    Labyrinth(int width, int height);
    void reset();
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
    void setStart(int x, int y);
    void setFinish(int x, int y);
    std::pair<int,int> getStart() const;
    std::pair<int,int> getFinish() const;
    void clearSearch();

private:
    int width, height;
    std::vector<std::vector<Cell>> grid;
    int startX, startY, finishX, finishY;
};

#endif
