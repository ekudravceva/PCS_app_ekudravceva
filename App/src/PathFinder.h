#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "Labyrinth.h"
#include <vector>
#include <utility>

class PathFinder {
public:
    virtual ~PathFinder() = default;
    virtual std::vector<std::pair<int,int>> findPath(Labyrinth& lab) = 0;
};

#endif
