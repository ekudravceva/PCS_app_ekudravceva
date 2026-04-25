#ifndef ASTAR_FINDER_H
#define ASTAR_FINDER_H

#include "PathFinder.h"

class AStarFinder : public PathFinder {
public:
    std::vector<std::pair<int,int>> findPath(Labyrinth& lab) override;
};

#endif
