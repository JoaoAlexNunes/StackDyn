#include "Block.h"
#include "Stack.h"
#include "Knapsack.h"
#include <algorithm>
#include <iostream>
#include <chrono>

// Helper function for sorting blocks based on seconds left to due date
bool sortBySecondsLeft(const Block* block1, const Block* block2) {
    return block1->GetSecondsLeftToDueDate() < block2->GetSecondsLeftToDueDate();
}

KnapsackGeneticAlgorithm::KnapsackGeneticAlgorithm() {
    // Initialize member variables if needed
}

void KnapsackGeneticAlgorithm::Run(Stack& arrivalStack, Stack& buffer1, Stack& buffer2, Stack& buffer3, Crane* crane, int &chin_counter) {
    // Step 1: Sort blocks based on seconds left to due date
    //std::vector<Block*> sortedBlocks = blocks;
    //std::sort(sortedBlocks.begin(), sortedBlocks.end(), sortBySecondsLeft);
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now.time_since_epoch();
    double releaseTim = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count(); // Time in seconds

    std::list<Block*> blocksb1 = buffer1.GetBlocks();
    std::list<Block*> blocksb2 = buffer2.GetBlocks();
    std::list<Block*> blocksb3 = buffer3.GetBlocks();
    std::list<Block*> blocks = arrivalStack.GetBlocks();
    
    Block* block = nullptr;


    double timeOfTopBlockb1 = 100; double timeOfTopBlockb2 = 100; double timeOfTopBlockb3 = 100; 

    if (!blocksb1.empty()) {
        Block* topBlock = blocksb1.back();
        double timeOfTopBlock = topBlock->GetDueDate();
        timeOfTopBlockb1 = timeOfTopBlock - releaseTim;
        
        /*std::cout << "Tempo top bloco buffer2: " << timeOfTopBlockb1 << std::endl;*/
    }
    
    if (!blocksb2.empty()) {
        Block* topBlock = blocksb2.back();
        double timeOfTopBlock = topBlock->GetDueDate();
        timeOfTopBlockb2 = timeOfTopBlock - releaseTim;

        /*std::cout << "Tempo top bloco buffer3: " << timeOfTopBlockb2 << std::endl;*/
    }

    if (!blocksb3.empty()) {
        Block* topBlock = blocksb3.back();
        double timeOfTopBlock = topBlock->GetDueDate();
        timeOfTopBlockb3 = timeOfTopBlock - releaseTim;

        /*std::cout << "Tempo top bloco buffer4: " << timeOfTopBlockb3 << std::endl;
        std::cout << " " << std::endl;*/
    }
    if (!blocks.empty()) {
        block = blocks.back();
    }
    else {
        block = nullptr;
    }
    //arrivalStack.PrintBlocks();
    // Step 2: Perform container movements based on the sorted order
    //for (Block* block : blocks) {
        // Move the block to the buffer with the most available space


        //time_till_due_new_block
        //int tempo_bloco = arrivalStack.GetTopBlock();


        //std::cout << "Tempo bloco buffer: " << finalTime << std::endl;

    Handover(buffer1, buffer2, buffer3, timeOfTopBlockb1, timeOfTopBlockb2, timeOfTopBlockb3, crane, chin_counter);
    MoveBlockBuffers(arrivalStack, buffer1, buffer2, buffer3, blocksb1, blocksb2, blocksb3, crane, timeOfTopBlockb1, timeOfTopBlockb2, timeOfTopBlockb3, block);



    //}
}

Stack* KnapsackGeneticAlgorithm::getTargetBuffer(double timeOfTopBlockb1, double finalTime, Stack& buffer1, double timeOfTopBlockb2, Stack& buffer2, double timeOfTopBlockb3, Stack& buffer3)
{
    if ((timeOfTopBlockb1 > finalTime || finalTime - timeOfTopBlockb1 < 10) && buffer1.hasSpace()) {
        return &buffer1;
    }
    else if ((timeOfTopBlockb2 > finalTime || finalTime - timeOfTopBlockb2 < 10) && buffer2.hasSpace()) {
        return &buffer2;
    }
    else if ((timeOfTopBlockb3 > finalTime || finalTime - timeOfTopBlockb3 < 10) && buffer3.hasSpace()) {
        return &buffer3;
    }
    else
    {
        if (buffer1.hasSpace() && timeOfTopBlockb1 != 0) {
            return &buffer1;
        }
        else if (buffer2.hasSpace() && timeOfTopBlockb2 != 0)
        {
            return &buffer2;
        }
        else if (buffer3.hasSpace() && timeOfTopBlockb3 != 0) {
            return &buffer3;
        }
    }
    return &buffer3;
}


void KnapsackGeneticAlgorithm::Handover(Stack& buffer1, Stack& buffer2, Stack& buffer3, double timeOfTopBlockb1, double timeOfTopBlockb2, double timeOfTopBlockb3, Crane* crane, int& chin_counter) {

    if (timeOfTopBlockb1 <= 35) {
        chin_counter++;
        Block* block = buffer1.RemoveBlock();
        crane->addToHistory(block, "handover");
        double seconds = block->GetSecondsLeftToDueDate();
        std::cout << "Removed from buffer 2 with ID: " << block->GetId() << " and with: " << seconds << " seconds left! Removed: " << chin_counter << " in total" << std::endl;
        block->SetSecondsUntilDue(seconds);
        std::cout << std::endl;

    }
    else if (timeOfTopBlockb2 <= 35)
    {
        chin_counter++;
        Block* block = buffer2.RemoveBlock();
        crane->addToHistory(block, "handover");
        double seconds = block->GetSecondsLeftToDueDate();
        std::cout << "Removed from buffer 3 with ID: " << block->GetId() << " and with: " << seconds << " seconds left! Removed: " << chin_counter << " in total" << std::endl;
        block->SetSecondsUntilDue(seconds);
        std::cout << std::endl;

    }
    else if (timeOfTopBlockb3 <= 35) {
        chin_counter++;
        Block* block = buffer3.RemoveBlock();
        crane->addToHistory(block, "handover");
        double seconds = block->GetSecondsLeftToDueDate();
        std::cout << "Removed from buffer 4 with ID: " << block->GetId() << " and with: " << seconds << " seconds left! Removed: " << chin_counter << " in total" << std::endl;
        block->SetSecondsUntilDue(seconds);
        std::cout << std::endl;

    }


}

int KnapsackGeneticAlgorithm::MoveBlockBuffers(Stack& arrivalStack, Stack& buffer1, Stack& buffer2, Stack& buffer3, std::list<Block*> blocksb1, std::list<Block*> blocksb2, std::list<Block*> blocksb3, Crane* crane, int timeOfTopBlockb1, int timeOfTopBlockb2, int timeOfTopBlockb3, Block* block) {
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now.time_since_epoch();
    double releaseTim = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count(); // Time in seconds
    Stack* targetBuffer = nullptr;
    

    if (block != nullptr) {
        double tempo_bloco = block->GetDueDate();
        double finalTime = tempo_bloco - releaseTim;
        targetBuffer = getTargetBuffer(timeOfTopBlockb1, finalTime, buffer1, timeOfTopBlockb2, buffer2, timeOfTopBlockb3, buffer3);

        if (targetBuffer != nullptr) {
            // Move the block to the target buffer
            arrivalStack.RemoveBlock();  // Remove the block from the arrival stack
            targetBuffer->AddBlock(block);  // Add the block to the target buffer
            //targetBuffer->PrintBlocks();  // Print the updated blocks in the target buffer
        }
        else {
            std::cout << "No buffer available. Cannot add block." << std::endl;
        }
    }

    int i = 0;
    for (auto it = blocksb1.rbegin(); it != blocksb1.rend(); ++it) {
        Block* block = *it;
        double tim = block->GetDueDate() - releaseTim;
        if (i != 0 && tim < 30 && (buffer2.hasSpace() || buffer3.hasSpace())) {
            //temos que o tirar debaixo dos outros containers

            //mover os blocks que estao em cima para o buffer 2 ou 3 se tiver espaço
            //testar buffer2 e 3 se tem espaço

            Stack* targetBuffer = getTargetBuffer(0, tim, buffer1, timeOfTopBlockb2, buffer2, timeOfTopBlockb3, buffer3);

            
            block = buffer1.RemoveBlock();  // Remove the block from the arrival stack
            targetBuffer->AddBlock(block);  // Add the block to the target buffer
            std::cout << "MOVED from buffer 2 to buffer "<< targetBuffer->GetID() << " with ID : " << block->GetId() << std::endl;
            crane->addToHistory(block, "Buffer" + std::to_string(targetBuffer->GetID()));
            
            /*std::cout << std::endl;
            std::cout << "!!BUFFER 2 -> " << std::endl;
            buffer1.PrintBlocks();
            std::cout << std::endl;
            std::cout << "!!BUFFER targ -> " << std::endl;
            targetBuffer->PrintBlocks();*/
            return 0;
        } 
        i++;
    }

    i = 0;

    for (auto it = blocksb2.rbegin(); it != blocksb2.rend(); ++it) {
        Block* block = *it;
        double tim = block->GetDueDate() - releaseTim;
        if (i != 0  &&tim < 30 && (buffer1.hasSpace() || buffer3.hasSpace())) {
            //temos que o tirar debaixo dos outros containers

            //mover os blocks que estao em cima para o buffer 2 ou 3 se tiver espaço
            //testar buffer2 e 3 se tem espaço

            Stack* targetBuffer = getTargetBuffer(timeOfTopBlockb1, tim, buffer1, 0, buffer2, timeOfTopBlockb3, buffer3);


            block = buffer2.RemoveBlock();  // Remove the block from the arrival stack
            targetBuffer->AddBlock(block);  // Add the block to the target buffer
            std::cout << "MOVED from buffer 3 to buffer " << targetBuffer->GetID() << " with ID : " << block->GetId() << std::endl;
            crane->addToHistory(block, "Buffer" + std::to_string(targetBuffer->GetID()));
            /*std::cout << std::endl;
            std::cout << "!!BUFFER 3 -> " << std::endl;
            buffer2.PrintBlocks();
            std::cout << std::endl;
            std::cout << "!!BUFFER targ -> " << std::endl;
            targetBuffer->PrintBlocks();*/
            return 0;
        }
        i++;
    }

    i = 0;

    for (auto it = blocksb3.rbegin(); it != blocksb3.rend(); ++it) {
        Block* block = *it;
        double tim = block->GetDueDate() - releaseTim;
        if (i != 0 && tim < 30 && (buffer1.hasSpace() || buffer2.hasSpace())) {
            //temos que o tirar debaixo dos outros containers

            //mover os blocks que estao em cima para o buffer 2 ou 3 se tiver espaço
            //testar buffer2 e 3 se tem espaço

            Stack* targetBuffer = getTargetBuffer(timeOfTopBlockb1, tim, buffer1, timeOfTopBlockb2, buffer2, 0, buffer3);


            block = buffer3.RemoveBlock();  // Remove the block from the arrival stack
            targetBuffer->AddBlock(block);  // Add the block to the target buffer
            std::cout << "MOVED from buffer 4 to buffer " << targetBuffer->GetID() << " with ID : " << std::endl;
            crane->addToHistory(block, "Buffer" + std::to_string(targetBuffer->GetID()));

            /* std::cout << std::endl;
            std::cout << "!!BUFFER 4 -> " << std::endl;
            buffer3.PrintBlocks();
            std::cout << std::endl;
            std::cout << "!!BUFFER targ -> " << std::endl;
            targetBuffer->PrintBlocks();
            return 0;*/
        }
        i++;
    }
}