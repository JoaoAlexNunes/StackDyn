#pragma once

#include <list>
#include <iostream>
#include "Block.h"


// Define a struct to hold the Block and buffer information
struct BlockData {
    Block* block;
    std::string buffer;
};


class Crane {
private:
    int countMoves;
    BlockData data;
    std::list<BlockData> history;

public:
    Crane();
    ~Crane();

    void addToHistory(Block* block, std::string buffer);
};