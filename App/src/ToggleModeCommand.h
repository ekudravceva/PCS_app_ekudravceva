#ifndef TOGGLE_MODE_COMMAND_H
#define TOGGLE_MODE_COMMAND_H

#include "Command.h"
#include "Visualizer.h"

class ToggleModeCommand : public Command {
public:
    ToggleModeCommand(Visualizer& vis);
    void execute() override;
    
private:
    Visualizer& visualizer;
};

#endif
