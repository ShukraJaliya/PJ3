#include "heap.h"
#include <iostream>
#include <stdexcept>

MinHeap::MinHeap(int capacity) : capacity(capacity), size(0) {
    heapArray = new pVERTEX[capacity + 1];
    positionMap = new int[capacity + 1];
}
MinHeap::MinHeap() : capacity(0), size(0), heapArray(nullptr), positionMap(nullptr) {
    
}

MinHeap::~MinHeap() {
    delete[] heapArray;
    delete[] positionMap;
}

void MinHeap::insert(pVERTEX vertex) {
    if (size == capacity) {
        throw std::overflow_error("Heap is full");
    }
    heapArray[++size] = vertex;
    positionMap[vertex->index] = size;
    heapifyUp(size);
}

pVERTEX MinHeap::extractMin() {
    if (isEmpty()) {
        throw std::underflow_error("Heap is empty");
    }
    pVERTEX minVertex = heapArray[1];
    heapArray[1] = heapArray[size--];
    positionMap[heapArray[1]->index] = 1;
    heapifyDown(1);
    return minVertex;
}

void MinHeap::decreaseKey(int index, double newKey) {
    int pos = positionMap[index];
    heapArray[pos]->key = newKey;
    heapifyUp(pos);
}

bool MinHeap::isEmpty() const {
    return size == 0;
}

void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int leftChild = 2 * index;
    int rightChild = 2 * index + 1;

    if (leftChild <= size && heapArray[leftChild]->key < heapArray[smallest]->key) {
        smallest = leftChild;
    }
    if (rightChild <= size && heapArray[rightChild]->key < heapArray[smallest]->key) {
        smallest = rightChild;
    }
    if (smallest != index) {
        swapVertices(index, smallest);
        heapifyDown(smallest);
    }
}

void MinHeap::heapifyUp(int index) {
    while (index > 1 && heapArray[index / 2]->key > heapArray[index]->key) {
        swapVertices(index, index / 2);
        index /= 2;
    }
}

void MinHeap::swapVertices(int index1, int index2) {
    pVERTEX temp = heapArray[index1];
    heapArray[index1] = heapArray[index2];
    heapArray[index2] = temp;

    positionMap[heapArray[index1]->index] = index1;
    positionMap[heapArray[index2]->index] = index2;
}
