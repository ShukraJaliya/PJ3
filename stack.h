#ifndef STACK_H
#define STACK_H

#include "data_structures.h"

class Stack {
public:
    Stack(int capacity);
    ~Stack();
    void push(pVERTEX vertex);
    pVERTEX pop();
    pVERTEX top() const;
    bool isEmpty() const;

private:
    int capacity;
    int size;
    pVERTEX* stackArray;
};

#endif // STACK_H
