#include "Visualizer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

Visualizer::Visualizer(bool autoMode, int delayMs)
    : autoMode(autoMode), delayMs(delayMs) {}

void Visualizer::draw(const Labyrinth& lab) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    int w = lab.getWidth();
    int h = lab.getHeight();

    // Верхняя граница
    for (int x = 0; x < w; x++) {
        std::cout << "+---";
    }
    std::cout << "+\n";

    for (int y = 0; y < h; y++) {
        // Верхние стены ячеек (северные)
        for (int x = 0; x < w; x++) {
            if (lab.getCell(x, y).walls[0]) {
                std::cout << "+---";
            } else {
                std::cout << "+   ";
            }
        }
        std::cout << "+\n";

        // Содержимое ячеек и боковые стены
        for (int x = 0; x < w; x++) {
            // Левая стена (западная)
            if (x == 0 || lab.getCell(x, y).walls[3]) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            
            // Содержимое ячейки
            char c = ' ';
            const Cell& cell = lab.getCell(x, y);
            if (cell.isStart) c = 'S';
            else if (cell.isFinish) c = 'F';
            else if (cell.inPath) c = '*';
            else if (cell.visitedDuringSearch) c = '.';
            
            std::cout << " " << c << " ";
        }
        // Правая граница
        std::cout << "|\n";
    }

    // Нижняя граница
    for (int x = 0; x < w; x++) {
        std::cout << "+---";
    }
    std::cout << "+\n";
    
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
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void Visualizer::setAutoMode(bool mode) { autoMode = mode; }
void Visualizer::setDelay(int ms) { delayMs = ms; }
bool Visualizer::getAutoMode() const { return autoMode; }
