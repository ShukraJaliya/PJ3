#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

class MinHeap {
public:
    MinHeap(int capacity);
    ~MinHeap();
    void insert(pVERTEX vertex);
    pVERTEX extractMin();
    void decreaseKey(int index, double newKey);
    bool isEmpty() const;

private:
    int capacity;
    int size;
    pVERTEX* heapArray;
    int* positionMap;

    void heapifyDown(int index);
    void heapifyUp(int index);
    void swapVertices(int index1, int index2);
};

#endif // HEAP_H
