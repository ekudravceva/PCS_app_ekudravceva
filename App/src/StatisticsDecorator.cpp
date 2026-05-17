#include "StatisticsDecorator.h"
#include <iostream>
#include <chrono>

StatisticsDecorator::StatisticsDecorator(LabyrinthGenerator* gen, PathFinder* finder)
    : generator(gen), finder(finder) {}

void StatisticsDecorator::reset() {
    stats = Statistics();
}

void StatisticsDecorator::updateStats(long long searchTimeMs, size_t pathLength, size_t visitedCells) {
    stats.searchTimeMs = searchTimeMs;
    stats.pathLength = pathLength;
    stats.visitedCells = visitedCells;
}

void StatisticsDecorator::generate(Labyrinth& lab) {
    auto start = std::chrono::high_resolution_clock::now();
    generator->generate(lab);
    auto end = std::chrono::high_resolution_clock::now();
    // Генерация в микросекундах
    stats.genTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

std::vector<std::pair<int,int>> StatisticsDecorator::findPath(Labyrinth& lab) {
    auto start = std::chrono::high_resolution_clock::now();
    auto path = finder->findPath(lab);
    auto end = std::chrono::high_resolution_clock::now();
    
    // Поиск в миллисекундах
    stats.searchTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    stats.pathLength = path.size();
    
    // Подсчёт посещённых ячеек
    stats.visitedCells = 0;
    for (int y = 0; y < lab.getHeight(); y++) {
        for (int x = 0; x < lab.getWidth(); x++) {
            if (lab.getCell(x, y).visitedDuringSearch) {
                stats.visitedCells++;
            }
        }
    }
    
    return path;
}

void StatisticsDecorator::printStats() const {
    std::cout << "\nSTATISTICS\n";
    std::cout << "Generation time: " << stats.genTimeUs << " microseconds\n";
    std::cout << "Search time: " << stats.searchTimeMs << " miliseconds\n";
    std::cout << "Path length: " << stats.pathLength << " steps\n";
    std::cout << "Visited cells: " << stats.visitedCells << "\n";
}
