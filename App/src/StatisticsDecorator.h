#ifndef STATISTICS_DECORATOR_H
#define STATISTICS_DECORATOR_H

#include "LabyrinthGenerator.h"
#include "PathFinder.h"
#include <chrono>

struct Statistics {
    long long genTimeUs = 0;       // микросекунды для генерации
    long long searchTimeMs = 0;    // миллисекунды для поиска
    size_t pathLength = 0;
    size_t visitedCells = 0;
};

class StatisticsDecorator : public LabyrinthGenerator, public PathFinder {
public:
    StatisticsDecorator(LabyrinthGenerator* gen, PathFinder* finder);
    void generate(Labyrinth& lab) override;
    std::vector<std::pair<int,int>> findPath(Labyrinth& lab) override;
    void printStats() const;
    void reset();
    void updateStats(long long searchTimeMs, size_t pathLength, size_t visitedCells);
    
private:
    LabyrinthGenerator* generator;
    PathFinder* finder;
    Statistics stats;
};

#endif
