#ifndef DFS_GENERATOR_H
#define DFS_GENERATOR_H

#include "LabyrinthGenerator.h"

class DFSGenerator : public LabyrinthGenerator {
public:
    void generate(Labyrinth& lab) override;
};

#endif
