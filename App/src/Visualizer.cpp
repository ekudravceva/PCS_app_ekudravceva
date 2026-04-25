#include "Visualizer.h"
#include <iostream>
#include <thread>
#include <chrono>

Visualizer::Visualizer(bool autoMode, int delayMs)
    : autoMode(autoMode), delayMs(delayMs) {}

void Visualizer::draw(const Labyrinth& lab) {
    std::system("clear"); // or "cls" on Windows
    int w = lab.getWidth(), h = lab.getHeight();
    
    // верхняя граница
    for (int x = 0; x < w; x++) std::cout << "+---";
    std::cout << "+\n";
    
    for (int y = 0; y < h; y++) {
        // северные стены
        std::cout << "|";
        for (int x = 0; x < w; x++) {
            if (lab.getCell(x, y).walls[0]) std::cout << "---";
            else std::cout << "   ";
            std::cout << "|";
        }
        std::cout << "\n";
        
        // содержимое ячеек
        std::cout << "|";
        for (int x = 0; x < w; x++) {
            char c = ' ';
            if (lab.getCell(x, y).isStart) c = 'S';
            else if (lab.getCell(x, y).isFinish) c = 'F';
            else if (lab.getCell(x, y).inPath) c = '*';
            else if (lab.getCell(x, y).visitedDuringSearch) c = '.';
            std::cout << " " << c << " ";
            if (lab.getCell(x, y).walls[2]) std::cout << "|";
            else std::cout << " ";
        }
        std::cout << "\n";
        
        // южные стены
        std::cout << "|";
        for (int x = 0; x < w; x++) {
            if (y == h-1 || lab.getCell(x, y).walls[1]) std::cout << "---";
            else std::cout << "   ";
            std::cout << "|";
        }
        std::cout << "\n";
    }
    std::cout.flush();
}

void Visualizer::drawStep(const Labyrinth& lab) {
    draw(lab);
    if (autoMode) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    } else {
        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
}

void Visualizer::waitForStep() {
    if (!autoMode) {
        std::cin.get();
    }
}

void Visualizer::setAutoMode(bool mode) { autoMode = mode; }
void Visualizer::setDelay(int ms) { delayMs = ms; }
bool Visualizer::getAutoMode() const { return autoMode; }
