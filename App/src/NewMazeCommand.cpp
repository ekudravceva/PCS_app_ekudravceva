#include "NewMazeCommand.h"
#include <iostream>

NewMazeCommand::NewMazeCommand(Labyrinth& lab, LabyrinthGenerator*& gen, Visualizer& vis)
    : labyrinth(lab), generator(gen), visualizer(vis) {}

void NewMazeCommand::execute() {
    if (!generator) {
        std::cout << "No generator selected!\n";
        return;
    }
    generator->generate(labyrinth);
    visualizer.draw(labyrinth);
    std::cout << "New maze generated!\n";
}
