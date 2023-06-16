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

    int GetSize() const {
        return currentSize;
    }

    void PrintBlocks() const {
        std::cout << "Buffer: " << StackID << std::endl;
        for (int i = 0; i < currentSize; i++) {
            Block* block = Blocklist[i];
            std::cout << "Block ID: " << block->GetId() << " Due Date: " << block->GetSecondsLeftToDueDate() << std::endl;
            // Print other block information as needed
        }
    }

    std::list<Block*> GetBlocks() const {
        std::list<Block*> block_list = {};
        for (int i = 0; i < currentSize; i++) {
            Block* block = Blocklist[i];
            block_list.push_back(block);
            //std::cout << "Block ID: " << block->GetId() << " Due Date: " << block->GetSecondsLeftToDueDate() << std::endl;
            // Print other block information as needed
        }

        return block_list;
    }

    Block* GetTopBlock() const {
        Block* block = Blocklist[currentSize];
        return block;
    }

    Block* GetBlock(int i) const {
        Block* block = Blocklist[i];
        return block;
    }

    int GetID() {
        return StackID;
    }

    void AddBlock(Block* block);
    Block* RemoveBlock();
    bool IsFull() const;
};
