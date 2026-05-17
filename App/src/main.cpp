#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "Labyrinth.h"
#include "DFSGenerator.h"
#include "KruskalGenerator.h"
#include "BFSFinder.h"
#include "AStarFinder.h"
#include "Visualizer.h"
#include "StatisticsDecorator.h"
#include "GenerateMazeCommand.h"
#include "FindPathCommand.h"
#include "ToggleModeCommand.h"
#include "ShowStatisticsCommand.h"
#include "NewMazeCommand.h"
#include "ExitCommand.h"

int main() {
    int width, height;
    std::cout << "Enter maze width (5-50): ";
    std::cin >> width;
    std::cout << "Enter maze height (5-50): ";
    std::cin >> height;
    
    if (width < 5) width = 5;
    if (height < 5) height = 5;
    if (width > 50) width = 50;
    if (height > 50) height = 50;
    
    Labyrinth lab(width, height);
    Visualizer visualizer(false, 300);
    
    int genChoice, searchChoice;
    std::cout << "Select generator (1-DFS, 2-Kruskal): ";
    std::cin >> genChoice;
    std::cout << "Select pathfinder (1-BFS, 2-A*): ";
    std::cin >> searchChoice;
    
    LabyrinthGenerator* generator = nullptr;
    PathFinder* finder = nullptr;
    
    if (genChoice == 1) {
        generator = new DFSGenerator();
    } else {
        generator = new KruskalGenerator();
    }
    
    if (searchChoice == 1) {
        finder = new BFSFinder();
    } else {
        finder = new AStarFinder();
    }
    
    StatisticsDecorator stats(generator, finder);
    
    GenerateMazeCommand genCmd(lab, generator, stats, visualizer);
    FindPathCommand findCmd(lab, stats, visualizer, searchChoice);
    ToggleModeCommand toggleCmd(visualizer);
    ShowStatisticsCommand statsCmd(&stats);
    NewMazeCommand newCmd(lab, generator, stats, visualizer);
    ExitCommand exitCmd;
    
    std::map<int, Command*> commands;
    commands[1] = &genCmd;
    commands[2] = &findCmd;
    commands[3] = &toggleCmd;
    commands[4] = &statsCmd;
    commands[5] = &newCmd;
    commands[6] = &exitCmd;
    
    // Первичная генерация (через декоратор)
    std::cout << "\nGenerating initial maze...\n";
    stats.generate(lab);
    visualizer.draw(lab);
    
    int choice;
    while (true) {
        std::cout << "\nMENU\n";
        std::cout << "1. Generate maze\n";
        std::cout << "2. Find path (step by step)\n";
        std::cout << "3. Toggle auto mode (ON/OFF)\n";
        std::cout << "4. Show statistics\n";
        std::cout << "5. New maze\n";
        std::cout << "6. Exit\n";
        std::cout << "Current auto mode: " << (visualizer.getAutoMode() ? "ON" : "OFF") << "\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        auto it = commands.find(choice);
        if (it != commands.end()) {
            it->second->execute();
        } else {
            std::cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}
