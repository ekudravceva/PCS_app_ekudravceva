#ifndef BFS_FINDER_H
#define BFS_FINDER_H

#include "PathFinder.h"

class BFSFinder : public PathFinder {
public:
    std::vector<std::pair<int,int>> findPath(Labyrinth& lab) override;
};

#endif
