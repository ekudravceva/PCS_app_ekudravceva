#ifndef GENERATE_MAZE_COMMAND_H
#define GENERATE_MAZE_COMMAND_H

#include "Command.h"
#include "Labyrinth.h"
#include "LabyrinthGenerator.h"
#include "Visualizer.h"

class GenerateMazeCommand : public Command {
public:
    GenerateMazeCommand(Labyrinth& lab, LabyrinthGenerator*& generator, Visualizer& vis);
    void execute() override;
    
private:
    Labyrinth& labyrinth;
    LabyrinthGenerator*& generator;
    Visualizer& visualizer;
};

#endif
