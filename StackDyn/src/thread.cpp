#include <iostream>
#include <chrono>
#include <thread>
#include <random>

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
        std::this_thread::sleep_for(getRandomInterval(interval, interval * 2));
        myFunction();
    }
}

int main()
{
    // Start executing the function asynchronously
    std::thread t(executeFunctionAsync, 1000);  // Interval of 1000 milliseconds (1 second)

    // Do other tasks in the main thread
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Let the execution run for 10 seconds

    // Stop the asynchronous execution
    t.join();

    return 0;
}