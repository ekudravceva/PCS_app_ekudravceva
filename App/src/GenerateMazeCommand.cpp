#include "GenerateMazeCommand.h"
#include <iostream>

GenerateMazeCommand::GenerateMazeCommand(Labyrinth& lab, LabyrinthGenerator*& gen, StatisticsDecorator& stats, Visualizer& vis)
    : labyrinth(lab), generator(gen), statistics(stats), visualizer(vis) {}

void GenerateMazeCommand::execute() {
    if (!generator) {
        std::cout << "No generator selected!\n";
        return;
    }
    std::cout << "Generating maze...\n";
    
    // Используем декоратор для замера времени
    statistics.generate(labyrinth);
    visualizer.draw(labyrinth);
    std::cout << "Maze generated!\n";
}
