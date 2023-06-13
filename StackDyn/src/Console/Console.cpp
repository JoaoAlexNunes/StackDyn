#include "Console.h"


// Function to execute
void myFunction()
{
    std::cout << "Executing function..." << std::endl;
}

// Function to generate random time intervals
std::chrono::milliseconds getRandomInterval(int minMilliseconds, int maxMilliseconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minMilliseconds, maxMilliseconds);
    return std::chrono::milliseconds(dis(gen));
}

// Asynchronous execution
void executeFunctionAsync(int interval)
{
    while (true)
    {
        std::this_thread::sleep_for(getRandomInterval(interval, interval * 4));
        myFunction();
    }
}
Console::Console()
{
    Draw();
    CreateArrivalStack();
}

Console::~Console()
{
}


void Console::Draw()
{
    SetConsoleTitle(TEXT("3.3.0 - Build 30.0.100.9805"));
    std::cout << "Test Console writing" << std::endl;

    // Start executing the function asynchronously
    std::thread t(executeFunctionAsync, 500);  // Interval of 1000 milliseconds (1 second)

    // Do other tasks in the main thread
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Let the execution run for 10 seconds

    // Stop the asynchronous execution
    t.join();

}

void Console::CreateArrivalStack()
{
	Stack* arrivalStack = new Stack(1, 4);
    std::cout << "Arrival Stack ID: " << arrivalStack->StackID << std::endl;
    std::cout << "Arrival Stack Weight: " << arrivalStack->Weigth << std::endl;

    // Accessing and modifying values in the arrival stack
    for (int i = 0; i < arrivalStack->Weigth; i++) {
        arrivalStack->Blocklist[i] = i * 2;
    }

    std::cout << "Arrival Stack Values: ";
    for (int i = 0; i < arrivalStack->Weigth; i++) {
        std::cout << arrivalStack->Blocklist[i] << " ";
    }

}

