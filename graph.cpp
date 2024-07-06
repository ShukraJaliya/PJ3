#include "graph.h"
#include <iostream>
#include <cfloat>
#include <cstring>

Graph::Graph(int n) : n(n) {
    vertices.resize(n + 1);
    adj.resize(n + 1, nullptr);
    minHeap = new MinHeap(n);
    stack = new Stack(n);
    for (int i = 1; i <= n; ++i) {
        vertices[i] = new VERTEX{i, WHITE, DBL_MAX, -1, -1};
    }
}

Graph::~Graph() {
    for (int i = 1; i <= n; ++i) {
        delete vertices[i];
        pNODE current = adj[i];
        while (current) {
            pNODE temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete minHeap;
    delete stack;
}

void Graph::addEdge(int u, int v, double w) {
    pNODE newNode = new NODE{v, u, v, w, adj[u]};
    adj[u] = newNode;
}

void Graph::printAdj() const {
    for (int i = 1; i <= n; ++i) {
        std::cout << "ADJ[" << i << "]:";
        pNODE current = adj[i];
        while (current) {
            std::cout << "-->" << "[" << current->u << " " << current->v << ": " << current->w << "]";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

void Graph::initializeSingleSource(int source) {
    for (int i = 1; i <= n; ++i) {
        vertices[i]->key = DBL_MAX;
        vertices[i]->pi = -1;
    }
    vertices[source]->key = 0;
    minHeap->insert(vertices[source]);
}

void Graph::relax(int u, int v, double w) {
    if (vertices[v]->key > vertices[u]->key + w) {
        vertices[v]->key = vertices[u]->key + w;
        vertices[v]->pi = u;
        minHeap->decreaseKey(v, vertices[v]->key);
    }
}

void Graph::singlePairShortestPath(int source, int destination) {
    initializeSingleSource(source);
    while (!minHeap->isEmpty()) {
        pVERTEX u = minHeap->extractMin();
        pNODE current = adj[u->index];
        while (current) {
            relax(u->index, current->v, current->w);
            current = current->next;
        }
    }
}

void Graph::singleSourceShortestPath(int source) {
    initializeSingleSource(source);
    while (!minHeap->isEmpty()) {
        pVERTEX u = minHeap->extractMin();
        pNODE current = adj[u->index];
        while (current) {
            relax(u->index, current->v, current->w);
            current = current->next;
        }
    }
}

void Graph::printLength(int s, int t) const {
    if (vertices[t]->pi != -1) {
        std::cout << "The length of the shortest path from " << s << " to " << t << " is: " << vertices[t]->key << std::endl;
    } else {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    }
}

void Graph::printPath(int s, int t) const {
    if (vertices[t]->pi != -1) {
        std::cout << "The shortest path from " << s << " to " << t << " is: ";
        int current = t;
        stack->push(vertices[current]);
        while (vertices[current]->pi != -1) {
            current = vertices[current]->pi;
            stack->push(vertices[current]);
        }
        while (!stack->isEmpty()) {
            pVERTEX v = stack->pop();
            std::cout << "[" << v->index << ": " << v->key << "]";
            if (!stack->isEmpty()) {
                std::cout << "-->";
            }
        }
        std::cout << "." << std::endl;
    } else {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    }
}
