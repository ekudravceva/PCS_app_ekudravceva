#ifndef FIND_PATH_COMMAND_H
#define FIND_PATH_COMMAND_H

#include "Command.h"
#include "Labyrinth.h"
#include "PathFinder.h"
#include "Visualizer.h"

class FindPathCommand : public Command {
public:
    FindPathCommand(Labyrinth& lab, PathFinder*& finder, Visualizer& vis);
    void execute() override;
    
private:
    Labyrinth& labyrinth;
    PathFinder*& finder;
    Visualizer& visualizer;
};

#endif
