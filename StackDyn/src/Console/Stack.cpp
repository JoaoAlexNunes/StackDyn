#include "Stack.h"

Stack::Stack(int sId, int w, int maxHeight) : StackID(sId), Weight(w), MaxHeight(maxHeight), currentSize(0)
{
    Blocklist = new Block*[MaxHeight];
}

Stack::~Stack()
{
    delete[] Blocklist;
}

void Stack::AddBlock(Block* block)
{
    if (currentSize < MaxHeight) {
        Blocklist[currentSize] = block;
        currentSize++;
    }
    else {
        std::cout << "Stack is full. Cannot add block." << std::endl;
    }
}

Block* Stack::RemoveBlock()
{
    if (currentSize > 0) {
        Block* removedBlock = Blocklist[currentSize - 1]; // Get the top block to be removed
        currentSize--; // Update the current size of the stack
        return removedBlock;
        std::cout << "remove block." << std::endl;
    }
    else {
        std::cout << "Stack is empty. Cannot remove block." << std::endl;
        return nullptr;
    }
}

bool Stack::IsFull() const
{
    return currentSize >= MaxHeight;
}