#include "FindPathCommand.h"
#include <iostream>
#include <chrono>

FindPathCommand::FindPathCommand(Labyrinth& lab, StatisticsDecorator& stats, Visualizer& vis, int searchChoice)
    : labyrinth(lab), statistics(stats), visualizer(vis), searchAlgo(searchChoice) {}

void FindPathCommand::execute() {
    
    if (!visualizer.getAutoMode()) {
        std::cin.get();
    }
    
    // Замер времени в миллисекундах
    auto startTime = std::chrono::high_resolution_clock::now();
    
    // Пошаговый поиск
    StepByStepFinder stepFinder(labyrinth, searchAlgo);
    
    while (stepFinder.hasNext()) {
        stepFinder.nextStep(visualizer);
        visualizer.waitForStep();
    }
    
    auto path = stepFinder.getPath();
    visualizer.draw(labyrinth);
    
    // Замер времени окончания
    auto endTime = std::chrono::high_resolution_clock::now();
    long long searchTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    // Подсчёт посещённых ячеек
    size_t visitedCells = 0;
    for (int y = 0; y < labyrinth.getHeight(); y++) {
        for (int x = 0; x < labyrinth.getWidth(); x++) {
            if (labyrinth.getCell(x, y).visitedDuringSearch) {
                visitedCells++;
            }
        }
    }
    // Обновляем статистику в декораторе
    statistics.updateStats(searchTimeMs, path.size(), visitedCells);
}
