#include "GenerateMazeCommand.h"
#include <iostream>

GenerateMazeCommand::GenerateMazeCommand(Labyrinth& lab, LabyrinthGenerator*& gen, Visualizer& vis)
    : labyrinth(lab), generator(gen), visualizer(vis) {}

void GenerateMazeCommand::execute() {
    if (!generator) {
        std::cout << "No generator selected!\n";
        return;
    }
    std::cout << "Generating maze...\n";
    generator->generate(labyrinth);
    visualizer.draw(labyrinth);
    std::cout << "Maze generated!\n";
}
