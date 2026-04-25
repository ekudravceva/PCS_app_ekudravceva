#include "ShowStatisticsCommand.h"

ShowStatisticsCommand::ShowStatisticsCommand(StatisticsDecorator* stats) : statistics(stats) {}

void ShowStatisticsCommand::execute() {
    if (statistics) statistics->printStats();
}
