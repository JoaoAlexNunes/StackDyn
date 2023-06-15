#include "Console.h"

bool stopExecution = false;

std::chrono::seconds getRandomInterval(int minSeconds, int maxSeconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minSeconds, maxSeconds);
    int randomSeconds = dis(gen);
    return std::chrono::seconds(randomSeconds);
}

Console::Console()
{
}

Console::~Console()
{
}

void Console::Init()
{
    Stack* arrivalStack = new Stack(1, 400, 4);
    Stack buffer1(2, 800, 8);  // Create Stack objects for the three stack buffers
    Stack buffer2(3, 800, 8);
    Stack buffer3(4, 800, 8);
    Stack handover(5, 800, 1);
    Crane* crane = new Crane();

    int blockId = 1;
    while (true) {

        // Create a new block
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now.time_since_epoch();
        double releaseTime = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count(); // Time in seconds
        double dueDate = releaseTime + getRandomInterval(10, 100).count(); // Generate a random due date in seconds + releaseTime para depois calcular o tempo atual
        Block* newBlock = new Block(blockId, releaseTime, dueDate, "Not Ready");
        if (arrivalStack->IsFull()) {
            std::cout << "Arrival stack is full. Stopping the generation of new blocks." << std::endl;
            crane->addToHistory(newBlock, "null");
            break; // add to history
        }


        // Add the block to the arrival stack
        arrivalStack->AddBlock(newBlock);
        crane->addToHistory(newBlock, "arrival");

        //std::cout << "New block created and added to the arrival stack. Block ID: " << blockId << std::endl;

        // Move one container from the arrival stack to a stack buffer
        if (buffer1.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            buffer1.AddBlock(block);  // Move the block to buffer1
            crane->addToHistory(newBlock, "buffer 1");
            buffer1.PrintBlocks();
        }
        else if (buffer2.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            buffer2.AddBlock(block);  // Move the block to buffer2
            crane->addToHistory(newBlock, "buffer 2");
            buffer2.PrintBlocks();
        }
        else if (buffer3.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            buffer3.AddBlock(block);  // Move the block to buffer3
            crane->addToHistory(newBlock, "buffer 3");
            buffer3.PrintBlocks();
        }
        else if (handover.hasSpace()) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            handover.AddBlock(block);  // Move the block to buffer3
            handover.PrintBlocks();
            crane->addToHistory(newBlock, "delivered");
            handover.RemoveBlock();
        }

        blockId++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
