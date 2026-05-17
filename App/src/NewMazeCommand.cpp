#include "NewMazeCommand.h"
#include <iostream>

NewMazeCommand::NewMazeCommand(Labyrinth& lab, LabyrinthGenerator*& gen, StatisticsDecorator& stats, Visualizer& vis)
    : labyrinth(lab), generator(gen), statistics(stats), visualizer(vis) {}

void NewMazeCommand::execute() {
    if (!generator) {
        std::cout << "No generator selected!\n";
        return;
    }
    std::cout << "Generating new maze...\n";
    
    // Используем декоратор для замера времени
    statistics.generate(labyrinth);
    visualizer.draw(labyrinth);
    std::cout << "New maze generated!\n";
}
