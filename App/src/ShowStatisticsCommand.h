#ifndef SHOW_STATISTICS_COMMAND_H
#define SHOW_STATISTICS_COMMAND_H

#include "Command.h"
#include "StatisticsDecorator.h"

class ShowStatisticsCommand : public Command {
public:
    ShowStatisticsCommand(StatisticsDecorator* stats);
    void execute() override;
    
private:
    StatisticsDecorator* statistics;
};

#endif
