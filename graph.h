#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "data_structures.h"
#include "heap.h"
#include <vector> 
#include <string>

class Graph {
public:
     Graph(int size, const std::string& type, int flag); ;
    ~Graph();

    void addEdge(int u, int v, double w, int flag);
    void printGraph() const;
    void printAdj() const;
    void singlePairShortestPath(int source, int destination);
    void singleSourceShortestPath(int source);
    void printLength(int s, int t) const;
    void printPath(int s, int t) const;

    void initializeVertices(int size);

private:
    VERTEX* vertices;
    pNODE* adj;
    int size;
    std::string graphType;
    MinHeap minHeap;
    void initializeMinHeap();
    int flag;
    void dijkstra(int source, double* dist, int* prev)const;
    int lastSource;
    int lastDestination;
    bool pathComputed;

    double* dist;  // Declare dist as a private member
    int* prev;  
    
};

#endif // GRAPH_H
