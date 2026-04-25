#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include "Command.h"
#include <iostream>

class ExitCommand : public Command {
public:
    void execute() override {
        std::cout << "Goodbye!\n";
        exit(0);
    }
};

#endif
