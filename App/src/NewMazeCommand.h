#ifndef NEW_MAZE_COMMAND_H
#define NEW_MAZE_COMMAND_H

#include "Command.h"
#include "Labyrinth.h"
#include "LabyrinthGenerator.h"
#include "Visualizer.h"

class NewMazeCommand : public Command {
public:
    NewMazeCommand(Labyrinth& lab, LabyrinthGenerator*& generator, Visualizer& vis);
    void execute() override;
    
private:
    Labyrinth& labyrinth;
    LabyrinthGenerator*& generator;
    Visualizer& visualizer;
};

#endif
