#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "Labyrinth.h"
#include <string>

class Visualizer {
public:
    Visualizer(bool autoMode = false, int delayMs = 100);
    void draw(const Labyrinth& lab);
    void drawStep(const Labyrinth& lab);
    void waitForStep();
    void setAutoMode(bool mode);
    void setDelay(int ms);
    bool getAutoMode() const;
    
private:
    bool autoMode;
    int delayMs;
};

#endif
