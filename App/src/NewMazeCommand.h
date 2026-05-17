#ifndef NEW_MAZE_COMMAND_H
#define NEW_MAZE_COMMAND_H

#include "Command.h"
#include "Labyrinth.h"
#include "LabyrinthGenerator.h"
#include "Visualizer.h"
#include "StatisticsDecorator.h"

class NewMazeCommand : public Command {
public:
    NewMazeCommand(Labyrinth& lab, LabyrinthGenerator*& generator, StatisticsDecorator& stats, Visualizer& vis);
    void execute() override;
    
private:
    Labyrinth& labyrinth;
    LabyrinthGenerator*& generator;
    StatisticsDecorator& statistics;
    Visualizer& visualizer;
};

#endif
