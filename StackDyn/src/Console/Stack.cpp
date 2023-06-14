
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

bool Stack::IsFull() const
{
    return currentSize >= MaxHeight;
}