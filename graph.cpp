#include "graph.h"
#include "heap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector> 
#include "graph.h"
#include <iomanip>
#include <string>

#define DBL_MAX std::numeric_limits<double>::max()

Graph::Graph(int size, const std::string& type) {
    initializeVertices(size);
    graphType = type;  // Initialize graph type
}

void Graph::initializeVertices(int size) {
    this->size = size;
    vertices = new VERTEX[size];
    adj = new pNODE[size];
    for (int i = 0; i < size; ++i) {
        vertices[i].index = i+1;
        vertices[i].color = WHITE;
        vertices[i].key = DBL_MAX;
        vertices[i].pi = -1;
        vertices[i].position = -1;
        adj[i] = nullptr;
    }
}

void Graph::addEdge(int u, int v, double w, int flag) {
    int indexU = u - 1;
    int indexV = v - 1;
    
    // Check for duplicate edge from u to v
    pNODE current = adj[indexU];
    while (current != nullptr) {
        if (current->v == v) {
            // Update weight if edge already exists
            current->weight = w;
            break;  // Exit loop if edge is found and updated
        }
        current = current->next;
    }

    // If no duplicate edge was found, create a new node for u to v
    if (current == nullptr) {
        pNODE newNode1 = new NODE();
        newNode1->v = v;
        newNode1->u = u;
        newNode1->weight = w;
        newNode1->next = nullptr;

        // Insert at the front or rear based on flag for adjacency list of u
        if (flag == 1) {
            newNode1->next = adj[indexU];
            adj[indexU] = newNode1;
        } else if (flag == 2) {
            if (adj[indexU] == nullptr) {
                adj[indexU] = newNode1;
            } else {
                pNODE temp = adj[indexU];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode1;
            }
        }
    }

    // If it's an undirected graph, create or update edge from v to u
    if (graphType == "UndirectedGraph") {
        current = adj[indexV];
        while (current != nullptr) {
            if (current->v == u) {
                // Update weight if edge already exists
                current->weight = w;
                return;  // Exit function after updating undirected edge
            }
            current = current->next;
        }

        // If no duplicate edge was found, create a new node for v to u
        pNODE newNode2 = new NODE();
        newNode2->v = u;
        newNode2->u = v;
        newNode2->weight = w;
        newNode2->next = nullptr;

        // Insert at the front or rear based on flag for adjacency list of v
        if (flag == 1) {
            newNode2->next = adj[indexV];
            adj[indexV] = newNode2;
        } else if (flag == 2) {
            if (adj[indexV] == nullptr) {
                adj[indexV] = newNode2;
            } else {
                pNODE temp = adj[indexV];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode2;
            }
        }
    }
}


void Graph::printGraph() const {
    for (int i = 0; i < size; ++i) {  // Adjusting loop to start from 0 to size - 1
        std::cout << "ADJ[" << i + 1 << "]:";  // Adjusting output to be 1-based index
        pNODE temp = adj[i];
        while (temp) {
            std::cout << "-->[" << i + 1  << " " << temp->v << ": ";
            // Print weight with fixed precision (two decimal places)
            std::cout << std::fixed << std::setprecision(2) << temp->weight << "]";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

void Graph::printAdj() const {
    printGraph();
}
void Graph::singlePairShortestPath(int source, int destination) {
    if (source <= 0 || source > size || destination <= 0 || destination > size) {
        std::cerr << "Source or destination out of bounds" << std::endl;
        return;
    }
    MinHeap minHeap(size);
    vertices[source - 1].key = 0;
    minHeap.insert(&vertices[source - 1]);

    while (!minHeap.isEmpty()) {
        pVERTEX u = minHeap.extractMin();
        int u_index = u->index - 1;

        pNODE temp = adj[u_index];
        while (temp != nullptr) {
            int v_index = temp->v - 1;
            double weight = temp->weight;

            if (vertices[v_index].key > vertices[u_index].key + weight) {
                vertices[v_index].key = vertices[u_index].key + weight;
                vertices[v_index].pi = u_index;
                minHeap.decreaseKey(vertices[v_index].index, vertices[v_index].key);
            }

            temp = temp->next;
        }
    }

    if (vertices[destination - 1].key == DBL_MAX) {
        vertices[destination - 1].pi = -1;
    }
}

void Graph::singleSourceShortestPath(int source) {
    // Initialize MinHeap and source vertex
    MinHeap minHeap(size);
    vertices[source - 1].key = 0.0;
    minHeap.insert(&vertices[source - 1]);

    while (!minHeap.isEmpty()) {
        VERTEX* u = minHeap.extractMin();
        int u_index = u->index - 1;

        pNODE temp = adj[u_index];
        while (temp != nullptr) {
            int v_index = temp->v - 1;
            double weight = temp->weight;

            // Relaxation step
            if (vertices[v_index].key > vertices[u_index].key + weight) {
                vertices[v_index].key = vertices[u_index].key + weight;
                vertices[v_index].pi = u_index;
                minHeap.decreaseKey(vertices[v_index].index, vertices[v_index].key);
            }

            temp = temp->next;
        }
    }
}


void Graph::printLength(int s, int t) const {
    if (vertices[t - 1].key == DBL_MAX) {
        std::cout << "No path exists between " << s << " and " << t << std::endl;
    } else {
        std::cout << "The length of the shortest path from " << s << " to " << t << " is: " << std::fixed << std::setprecision(2) << std::setw(7) << vertices[t - 1].key << std::endl;
    }
}

void Graph::printPath(int s, int t) const {
    if (vertices[t - 1].key == DBL_MAX) {
        std::cout << "There is no path from " << s << " to " << t << "." <<std::endl;
    } else {
        std::vector<int> path;
        for (int v = t - 1; v != -1; v = vertices[v].pi) {
            path.push_back(v + 1);
        }

        std::cout << "The shortest path from " << s << " to " << t << " is:" << std::endl;
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << "[" << *it << ": " << std::fixed << std::setprecision(2) << std::setw(6) << vertices[*it - 1].key << "]";
            if (it + 1 != path.rend()) {
                std::cout << "-->";
            }
        }
        std::cout << "." << std::endl;
    }
}

Graph::~Graph() {
    delete[] vertices;
    for (int i = 0; i < size; ++i) {
        pNODE current = adj[i];
        while (current != nullptr) {
            pNODE next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] adj;
}
