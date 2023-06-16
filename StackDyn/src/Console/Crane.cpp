#include "Crane.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>

Crane::Crane()
{
}

Crane::~Crane()
{
}

void Crane::addToHistory(Block* block, std::string buffer)
{
    data.block = block;
    data.buffer = buffer;
    history.push_back(data);
    countMoves++;
}

void Crane::PrintHistory()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << "output_" << time << ".txt";
    std::string filename = ss.str();

    std::ofstream outputFile(filename); // Open the file for writing

    if (outputFile.is_open()) { // Check if the file was successfully opened
        std::streambuf* originalBuffer = std::cout.rdbuf(); // Save the original buffer of std::cout
        std::cout.rdbuf(outputFile.rdbuf()); // Redirect std::cout to the file stream

        // Output the text
        std::cout << "Crane History:" << std::endl;
        for (const auto& blockData : history) {
            std::cout << "Block ID: " << blockData.block->BlockID << std::endl;
            std::cout << "Due Time: " << blockData.block->secondsUntilDue << std::endl;
            std::cout << "Buffer: " << blockData.buffer << std::endl;
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Moves realized by the Crane: " << countMoves << " IN 50 Created Containers." << std::endl;

        std::cout.rdbuf(originalBuffer); // Restore the original buffer of std::cout
        outputFile.close(); // Close the file
        std::cout << "Text successfully outputted to the file." << std::endl;
    }
    else {
        std::cout << "Unable to open the file." << std::endl;
    }
}
