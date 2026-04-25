#include "FindPathCommand.h"
#include <iostream>

FindPathCommand::FindPathCommand(Labyrinth& lab, PathFinder*& finder, Visualizer& vis)
    : labyrinth(lab), finder(finder), visualizer(vis) {}

void FindPathCommand::execute() {
    if (!finder) {
        std::cout << "No pathfinder selected!\n";
        return;
    }
    std::cout << "Finding path...\n";
    auto path = finder->findPath(labyrinth);
    visualizer.draw(labyrinth);
    std::cout << "Path found! Length: " << path.size() << " steps\n";
}
