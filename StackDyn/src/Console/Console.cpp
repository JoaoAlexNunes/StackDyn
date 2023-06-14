

#include "Console.h"

bool stopExecution = false;

//// Function to execute
//void myFunction()
//{
//    std::cout << "Executing function..." << std::endl;
//}
//
// Function to generate random time intervals

std::chrono::milliseconds getRandomInterval(int minMilliseconds, int maxMilliseconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minMilliseconds, maxMilliseconds);
    return std::chrono::milliseconds(dis(gen));
}

// Asynchronous execution
//void executeFunctionAsync(int interval)
//{
//    while (!stopExecution)
//    {
//        std::this_thread::sleep_for(getRandomInterval(interval, interval * 4));
//        myFunction();
//    }
//}

Console::Console()
{
    CreateArrivalStack();
}

Console::~Console()
{
}


//void Console::Draw()
//{
//    SetConsoleTitle(TEXT("3.3.0 - Build 30.0.100.9805"));
//    std::cout << "Test Console writing" << std::endl;
//
//    // Start executing the function asynchronously
//    std::thread t(executeFunctionAsync, 500);  // Interval of 1000 milliseconds (1 second)
//
//    // Do other tasks in the main thread
//    std::this_thread::sleep_for(std::chrono::seconds(10));  // Let the execution run for 10 seconds
//
//    // Stop the asynchronous execution
//    stopExecution = true;
//    t.join();
//
//}

void Console::CreateArrivalStack()
{
    Stack* arrivalStack = new Stack(1, 400, 4);

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

        blockId++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}