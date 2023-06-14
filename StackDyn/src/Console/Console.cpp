#include "Console.h"

bool stopExecution = false;

std::chrono::milliseconds getRandomInterval(int minMilliseconds, int maxMilliseconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minMilliseconds, maxMilliseconds);
    return std::chrono::milliseconds(dis(gen));
}

Console::Console()
{
    CreateArrivalStack();
}

Console::~Console()
{
}

void Console::CreateArrivalStack()
{
    Stack* arrivalStack = new Stack(1, 400, 4);
    Stack buffer1(2, 800, 8);  // Create Stack objects for the three stack buffers
    Stack buffer2(3, 800, 8);
    Stack buffer3(4, 800, 8);
    Stack handover(5, 800, 1);

    int blockId = 1;
    while (true) {
        if (arrivalStack->IsFull()) {
            std::cout << "Arrival stack is full. Stopping the generation of new blocks." << std::endl;
            break;
        }

        // Create a new block
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now.time_since_epoch();
        double releaseTime = elapsed.count() * 1000; // Convert to milliseconds
        double dueDate = releaseTime + getRandomInterval(1000, 5000).count(); // Generate a random due date

        Block* newBlock = new Block(blockId, releaseTime, dueDate, "Not Ready");

        // Add the block to the arrival stack
        arrivalStack->AddBlock(newBlock);

        std::cout << "New block created and added to the arrival stack. Block ID: " << blockId << std::endl;

        // Move one container from the arrival stack to a stack buffer
        if (buffer1.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            buffer1.AddBlock(block);  // Move the block to buffer1
            buffer1.PrintBlocks();
        } 

        else if (buffer2.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            buffer2.AddBlock(block);  // Move the block to buffer2
            buffer2.PrintBlocks();
        }
        else if (buffer3.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            buffer3.AddBlock(block);  // Move the block to buffer3
            buffer3.PrintBlocks();
        }

        else if (handover.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            handover.AddBlock(block);  // Move the block to buffer3
            handover.PrintBlocks();
            handover.RemoveBlock();
            
        }


        blockId++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

