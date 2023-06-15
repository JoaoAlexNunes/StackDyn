#pragma once

#include "Stack.h"
#include "Block.h"
#include <vector>

class KnapsackGeneticAlgorithm {
public:
    KnapsackGeneticAlgorithm();
    void Run(Stack* arrivalStack, Stack* buffer1, Stack* buffer2, Stack* buffer3, const std::vector<Block*>& blocks);
};
