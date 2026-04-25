#include "StatisticsDecorator.h"
#include <iostream>

StatisticsDecorator::StatisticsDecorator(LabyrinthGenerator* gen, PathFinder* finder)
    : generator(gen), finder(finder) {}

void StatisticsDecorator::generate(Labyrinth& lab) {
    auto start = std::chrono::high_resolution_clock::now();
    generator->generate(lab);
    auto end = std::chrono::high_resolution_clock::now();
    stats.genTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

std::vector<std::pair<int,int>> StatisticsDecorator::findPath(Labyrinth& lab) {
    auto start = std::chrono::high_resolution_clock::now();
    auto path = finder->findPath(lab);
    auto end = std::chrono::high_resolution_clock::now();
    stats.searchTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    stats.pathLength = path.size();
    
    // подсчёт посещённых ячеек
    stats.visitedCells = 0;
    for (int y = 0; y < lab.getHeight(); y++)
        for (int x = 0; x < lab.getWidth(); x++)
            if (lab.getCell(x, y).visitedDuringSearch)
                stats.visitedCells++;
    
    return path;
}

void StatisticsDecorator::printStats() const {
    std::cout << "\n=== STATISTICS ===\n";
    std::cout << "Generation time: " << stats.genTimeMs << " ms\n";
    std::cout << "Search time: " << stats.searchTimeMs << " ms\n";
    std::cout << "Path length: " << stats.pathLength << " steps\n";
    std::cout << "Visited cells: " << stats.visitedCells << "\n";
    std::cout << "==================\n";
}
