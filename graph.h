#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "data_structures.h"
#include <vector> 
#include <string>

class Graph {
public:
    Graph(int size, const std::string& type) ;
    ~Graph();

    void addEdge(int u, int v, double w, int flag);
    void addEdgeToFront(int u, int v, double w);
    void addEdgeToRear(int u, int v, double w);
    void printGraph() const;
    void printAdj() const;
    void singleSourceShortestPath(int source);
    void printLength(int s, int t) const;
    void printPath(int s, int t) const;

    void initializeVertices(int size);

private:
    VERTEX* vertices;
    pNODE* adj;
    int size;
    std::string graphType;
};

#endif // GRAPH_H
