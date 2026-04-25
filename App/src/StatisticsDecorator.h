#ifndef STATISTICS_DECORATOR_H
#define STATISTICS_DECORATOR_H

#include "LabyrinthGenerator.h"
#include "PathFinder.h"
#include <chrono>

struct Statistics {
    long long genTimeMs = 0;
    long long searchTimeMs = 0;
    size_t pathLength = 0;
    size_t visitedCells = 0;
};

class StatisticsDecorator : public LabyrinthGenerator, public PathFinder {
public:
    StatisticsDecorator(LabyrinthGenerator* gen, PathFinder* finder);
    void generate(Labyrinth& lab) override;
    std::vector<std::pair<int,int>> findPath(Labyrinth& lab) override;
    void printStats() const;
    
private:
    LabyrinthGenerator* generator;
    PathFinder* finder;
    Statistics stats;
};

#endif
