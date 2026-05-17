#ifndef FIND_PATH_COMMAND_H
#define FIND_PATH_COMMAND_H

#include "Command.h"
#include "Labyrinth.h"
#include "PathFinder.h"
#include "Visualizer.h"
#include "StepByStepFinder.h"
#include "StatisticsDecorator.h"

class FindPathCommand : public Command {
public:
    FindPathCommand(Labyrinth& lab, StatisticsDecorator& stats, Visualizer& vis, int searchChoice);
    void execute() override;
    
private:
    Labyrinth& labyrinth;
    StatisticsDecorator& statistics;
    Visualizer& visualizer;
    int searchAlgo;
};

#endif
