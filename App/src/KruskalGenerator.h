#ifndef KRUSKAL_GENERATOR_H
#define KRUSKAL_GENERATOR_H

#include "LabyrinthGenerator.h"

class KruskalGenerator : public LabyrinthGenerator {
public:
    void generate(Labyrinth& lab) override;
};

#endif
