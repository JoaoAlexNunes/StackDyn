#include "Console.h"
#include "KnapSack.h"

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
    Stack* buffer1 = new Stack(2, 800, 8);  // Create Stack objects for the three stack buffers
    Stack* buffer2 = new Stack(3, 800, 8);
    Stack* buffer3 = new Stack(4, 800, 8);
    Stack* handover = new Stack(5, 800, 1);
    Crane* crane = new Crane();

    int blockId = 1;
    std::vector<Block*> blocks;  // Vector to store the blocks

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
        else {
            // Add the block to the arrival stack
            arrivalStack->AddBlock(newBlock);
            crane->addToHistory(newBlock, "arrival");
            std::cout << "New Block with ID: " << newBlock->GetId() << " added" << std::endl;
            std::cout << "" << std::endl;
            blocks.push_back(newBlock);  // Add the block to the vector
        }


        // Move the block to the buffer with the least amount of blocks
        Stack* targetBuffer = nullptr;
        int minBufferSize = INT_MAX;

        if (buffer1->hasSpace() && buffer1->GetSize() < minBufferSize) {
            targetBuffer = buffer1;
            minBufferSize = buffer1->GetSize();
        }

        if (buffer2->hasSpace() && buffer2->GetSize() < minBufferSize) {
            targetBuffer = buffer2;
            minBufferSize = buffer2->GetSize();
        }

        if (buffer3->hasSpace() && buffer3->GetSize() < minBufferSize) {
            targetBuffer = buffer3;
            minBufferSize = buffer3->GetSize();
        }

        if (targetBuffer != nullptr) {
            Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
            targetBuffer->AddBlock(block);  // Move the block to the target buffer
            crane->addToHistory(newBlock, "buffer");
            targetBuffer->PrintBlocks();
        }
        else {
            std::cout << "No buffer available. Cannot move block." << std::endl;
        }

        blockId++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


        //if (buffer1.hasSpace() && buffer1.GetSize() < minBufferSize) {
        //    targetBuffer = &buffer1;
        //    minBufferSize = buffer1.GetSize();
        //}

        //if (buffer2.hasSpace() && buffer2.GetSize() < minBufferSize) {
        //    targetBuffer = &buffer2;
        //    minBufferSize = buffer2.GetSize();
        //}

        //if (buffer3.hasSpace() && buffer3.GetSize() < minBufferSize) {
        //    targetBuffer = &buffer3;
        //    minBufferSize = buffer3.GetSize();
        //}

        //if (targetBuffer != nullptr) {
        //    Block* block = arrivalStack->RemoveBlock();  // Remove a block from the arrival stack
        //    targetBuffer->AddBlock(block);  // Move the block to the target buffer
        //    crane->addToHistory(newBlock, "buffer");
        //    targetBuffer->PrintBlocks();
        //}
        //else {
        //    std::cout << "No buffer available. Cannot move block." << std::endl;
        //}

