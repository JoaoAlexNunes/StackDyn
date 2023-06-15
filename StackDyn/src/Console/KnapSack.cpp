#include "Knapsack.h"
#include <algorithm>
#include <iostream>

// Helper function for sorting blocks based on seconds left to due date
bool sortBySecondsLeft(const Block* block1, const Block* block2) {
    return block1->GetSecondsLeftToDueDate() < block2->GetSecondsLeftToDueDate();
}

KnapsackGeneticAlgorithm::KnapsackGeneticAlgorithm() {
    // Initialize member variables if needed
}

void KnapsackGeneticAlgorithm::Run(Stack* arrivalStack, Stack* buffer1, Stack* buffer2, Stack* buffer3, const std::vector<Block*>& blocks) {
    // Step 1: Sort blocks based on seconds left to due date
    std::vector<Block*> sortedBlocks = blocks;
    std::sort(sortedBlocks.begin(), sortedBlocks.end(), sortBySecondsLeft);

    // Step 2: Perform container movements based on the sorted order
    for (Block* block : sortedBlocks) {
        // Move the block to the buffer with the most available space
        Stack* targetBuffer = nullptr;
        int maxAvailableSpace = 0;

        if (buffer1->hasSpace() && buffer1->GetSize() < maxAvailableSpace) {
            targetBuffer = buffer1;
            maxAvailableSpace = buffer1->GetSize();
        }

        if (buffer2->hasSpace() && buffer2->GetSize() < maxAvailableSpace) {
            targetBuffer = buffer2;
            maxAvailableSpace = buffer2->GetSize();
        }

        if (buffer3->hasSpace() && buffer3->GetSize() < maxAvailableSpace) {
            targetBuffer = buffer3;
            maxAvailableSpace = buffer3->GetSize();
        }

        if (targetBuffer != nullptr) {
            // Move the block to the target buffer
            arrivalStack->RemoveBlock();  // Remove the block from the arrival stack
            targetBuffer->AddBlock(block);  // Add the block to the target buffer
            targetBuffer->PrintBlocks();  // Print the updated blocks in the target buffer
        }
        else {
            std::cout << "No buffer available. Cannot move block." << std::endl;
        }
    }
}
