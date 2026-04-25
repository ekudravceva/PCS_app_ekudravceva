#include "ToggleModeCommand.h"
#include <iostream>

ToggleModeCommand::ToggleModeCommand(Visualizer& vis) : visualizer(vis) {}

void ToggleModeCommand::execute() {
    visualizer.setAutoMode(!visualizer.getAutoMode());
    std::cout << "Auto mode: " << (visualizer.getAutoMode() ? "ON" : "OFF") << "\n";
}
