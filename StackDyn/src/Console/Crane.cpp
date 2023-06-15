#include "Crane.h"

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

    std::cout << "Crane History:" << std::endl;
    for (const auto& blockData : history) {
        std::cout << "Block ID: " << blockData.block->BlockID << std::endl;
        std::cout << "Buffer: " << blockData.buffer << std::endl;
        std::cout << std::endl;
    }
}