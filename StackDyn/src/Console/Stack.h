#pragma once

#include <list>

class Stack {
public:
    int StackID, Weigth;     //tem que ser maios que 1
    int* Blocklist;

    Stack(int sId, int w);
    ~Stack();
};
