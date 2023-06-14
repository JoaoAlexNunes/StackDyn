#pragma once

#include "../pch.h"

#include "Block.h"

class Stack {
private:
    int StackID;
    int Weight;
    Block** Blocklist;
    int currentSize;
    int MaxHeight;
public:
    Stack(int sId, int w, int maxHeight);
    ~Stack();

    void AddBlock(Block* block);
    bool IsFull() const;
};
