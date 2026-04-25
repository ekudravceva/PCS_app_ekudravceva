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
    std::cout << "Enter maze width (5-100): ";
    std::cin >> width;
    std::cout << "Enter maze height (5-100): ";
    std::cin >> height;
    
    if (width < 5) width = 5;
    if (height < 5) height = 5;
    if (width > 100) width = 100;
    if (height > 100) height = 100;
    
    Labyrinth lab(width, height);
    Visualizer visualizer(false, 200);
    
    int genChoice, searchChoice;
    std::cout << "Select generator (1-DFS, 2-Kruskal): ";
    std::cin >> genChoice;
    std::cout << "Select pathfinder (1-BFS, 2-A*): ";
    std::cin >> searchChoice;
    
    LabyrinthGenerator* generator = nullptr;
    PathFinder* finder = nullptr;
    
    if (genChoice == 1) generator = new DFSGenerator();
    else generator = new KruskalGenerator();
    
    if (searchChoice == 1) finder = new BFSFinder();
    else finder = new AStarFinder();
    
    StatisticsDecorator stats(generator, finder);
    
    // Команды
    GenerateMazeCommand genCmd(lab, generator, visualizer);
    FindPathCommand findCmd(lab, finder, visualizer);
    ToggleModeCommand toggleCmd(visualizer);
    ShowStatisticsCommand statsCmd(&stats);
    NewMazeCommand newCmd(lab, generator, visualizer);
    ExitCommand exitCmd;
    
    std::map<int, Command*> commands;
    commands[1] = &genCmd;
    commands[2] = &findCmd;
    commands[3] = &toggleCmd;
    commands[4] = &statsCmd;
    commands[5] = &newCmd;
    commands[6] = &exitCmd;
    
    // Первичная генерация
    stats.generate(lab);
    visualizer.draw(lab);
    
    int choice;
    while (true) {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. Generate maze\n";
        std::cout << "2. Find path\n";
        std::cout << "3. Toggle auto mode\n";
        std::cout << "4. Show statistics\n";
        std::cout << "5. New maze\n";
        std::cout << "6. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (commands.find(choice) != commands.end()) {
            commands[choice]->execute();
        } else {
            std::cout << "Invalid choice!\n";
        }
    }
    
    delete generator;
    delete finder;
    return 0;
}
