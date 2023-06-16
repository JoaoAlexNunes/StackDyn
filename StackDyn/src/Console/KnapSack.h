#pragma once

#include "Stack.h"
#include "Block.h"
#include "Crane.h"
#include <vector>

class KnapsackGeneticAlgorithm {
public:
    KnapsackGeneticAlgorithm();
    void Run(Stack& arrivalStack, Stack& buffer1, Stack& buffer2, Stack& buffer3, Crane* crane, int &chin_counter);
    Stack* getTargetBuffer(double timeOfTopBlockb1, double finalTime, Stack& buffer1, double timeOfTopBlockb2, Stack& buffer2, double timeOfTopBlockb3, Stack& buffer3);
    void Handover(Stack& buffer1, Stack& buffer2, Stack& buffer3, double timeOfTopBlockb1, double timeOfTopBlockb2, double timeOfTopBlockb3, Crane* crane, int &chin_counter);
    void MoveBlockBuffers(Stack& buffer1, Stack& buffer2, Stack& buffer3, std::list<Block*> blocksb1, std::list<Block*> blocksb2, std::list<Block*> blocksb3, Crane* crane);
};
