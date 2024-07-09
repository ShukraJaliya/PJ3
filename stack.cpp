#include "stack.h"
#include <stdexcept>

Stack::Stack(int capacity) : capacity(capacity), size(0) {
    stackArray = new pVERTEX[capacity];
}

Stack::~Stack() {
    delete[] stackArray;
}

void Stack::push(pVERTEX vertex) {
    if (size == capacity) {
        throw std::overflow_error("Stack is full");
    }
    stackArray[size++] = vertex;
}

pVERTEX Stack::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return stackArray[--size];
}
pVERTEX Stack::top() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return stackArray[size - 1];  // Return top element
}

bool Stack::isEmpty() const {
    return size == 0;
}
