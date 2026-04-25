#ifndef LABYRINTH_GENERATOR_H
#define LABYRINTH_GENERATOR_H

#include "Labyrinth.h"

class LabyrinthGenerator {
public:
    virtual ~LabyrinthGenerator() = default;
    virtual void generate(Labyrinth& lab) = 0;
};

#endif
