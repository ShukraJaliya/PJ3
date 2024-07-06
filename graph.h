#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include "heap.h"
#include "stack.h"
#include <vector>

class Graph {
public:
    Graph(int n);
    ~Graph();
    void addEdge(int u, int v, double w);
    void printAdj() const;
    void singlePairShortestPath(int source, int destination);
    void singleSourceShortestPath(int source);
    void printLength(int s, int t) const;
    void printPath(int s, int t) const;

private:
    int n;
    std::vector<pVERTEX> vertices;
    std::vector<pNODE> adj;
    MinHeap* minHeap;
    Stack* stack;
    void initializeSingleSource(int source);
    void relax(int u, int v, double w);
};

#endif // GRAPH_H
