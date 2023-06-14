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
    bool hasSpace() const {
        return currentSize < MaxHeight;
    }
    void PrintBlocks() const {
        for (int i = 0; i < currentSize; i++) {
            Block* block = Blocklist[i];
            std::cout << "Block ID: " << block->GetId() <<" Due Date: " << block->GetDueDate() << std::endl;
            // Print other block information as needed
        }
    }
    void AddBlock(Block* block);
    Block* RemoveBlock();
    bool IsFull() const;
};
