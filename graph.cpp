#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <limits>   // For std::numeric_limits
#include <algorithm> // For std::reverse
#include <vector>
#include <iomanip>
#include <string>
#include <queue>

#define DBL_MAX std::numeric_limits<double>::max()

Graph::Graph(int size, const std::string& type, int flag) 
    : flag(flag), lastSource(-1), lastDestination(-1), pathComputed(false), dist(nullptr), prev(nullptr) {
    initializeVertices(size);
    graphType = type;
}

void Graph::initializeVertices(int size) {
    this->size = size;
    vertices = new VERTEX[size];
    adj = new pNODE[size];
    for (int i = 0; i < size; ++i) {
        vertices[i].index = i + 1;
        vertices[i].color = WHITE;
        vertices[i].key = DBL_MAX;
        vertices[i].pi = -1;
        vertices[i].position = -1;
        adj[i] = nullptr;
    }
}

void Graph::addEdge(int u, int v, double w, int flag) {
    if (flag != 1 && flag != 2) {
        return; // Do nothing if flag is 3
    }
    int indexU = u - 1;
    int indexV = v - 1;
    
    // Check for duplicate edge from u to v
    pNODE current = adj[indexU];
    while (current != nullptr) {
        if (current->v == v) {
            // Update weight if edge already exists
            current->weight = w;
            //std::cout << "Edge already exists. Updating weight to: " << w << std::endl;
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
    if (flag != 1 && flag != 2) {
        return; // Do nothing if flag is 3
    }
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

void Graph::dijkstra(int source, double* dist, int* prev) const {
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    std::vector<bool> visited(size, false);

    for (int i = 0; i < size; ++i) {
        dist[i] = std::numeric_limits<double>::infinity();
        prev[i] = -1;
    }
    dist[source - 1] = 0;  // Adjust for 1-based indexing
    pq.push({0, source - 1});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        pNODE temp = adj[u];
        while (temp != nullptr) {
            int v = temp->v - 1;  // Adjust for 1-based indexing
            if (!visited[v] && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
            temp = temp->next;
        }
    }
}

void Graph::singlePairShortestPath(int source, int destination) {
    delete[] dist;
    delete[] prev;
    
    dist = new double[size];
    prev = new int[size];

    dijkstra(source, dist, prev);

    lastSource = source;
    lastDestination = destination;
    pathComputed = true;
}

void Graph::singleSourceShortestPath(int source) {
    delete[] dist;
    delete[] prev;
    
    dist = new double[size];
    prev = new int[size];

    dijkstra(source, dist, prev);

    lastSource = source;
    lastDestination = -1;  // Single source means we don't have a specific destination
    pathComputed = true;
}

void Graph::printLength(int s, int t) const {
    if (flag != 1 && flag != 2) {
        return; // Do nothing if flag is 3
    }

    if (pathComputed && lastSource == s) {
        // Use the already computed dist array
        if (dist[t-1] == std::numeric_limits<double>::infinity()) {
            std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
        } else {
            std::cout << "The length of the shortest path from " << s << " to " << t << " is: ";
            std::cout << std::fixed << std::setprecision(2) << std::setw(8) << dist[t-1] << std::endl;
        }
    } else {
        // Compute the path if it hasn't been computed yet
        double* tempDist = new double[size];
        int* tempPrev = new int[size];

        dijkstra(s, tempDist, tempPrev);

        if (tempDist[t-1] == std::numeric_limits<double>::infinity()) {
            std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
        } else {
            std::cout << "The length of the shortest path from " << s << " to " << t << " is: ";
            std::cout << std::fixed << std::setprecision(2) << std::setw(8) << tempDist[t-1] << std::endl;
        }

        delete[] tempDist;
        delete[] tempPrev;
    }
}

void Graph::printPath(int s, int t) const {
    if (!pathComputed || lastSource != s) {
        return;
    }

    if (t < 1 || t > size) {
        std::cout << "Invalid destination " << t << std::endl;
        return;
    }

    if (dist[t-1] == std::numeric_limits<double>::infinity()) {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    } else {
        std::vector<int> path;
        for (int at = t-1; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        std::cout << "The shortest path from " << s << " to " << t << " is:" << std::endl;
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << "[" << (path[i] + 1) << ": ";
            std::cout << std::fixed << std::setprecision(2) << std::setw(7) << std::right;
            std::cout << dist[path[i]];
            std::cout << "]";
            if (i < path.size() - 1) {
                std::cout << "-->";
            }
        }
        std::cout << "." << std::endl;
    }
}

Graph::~Graph() {
    delete[] dist;
    delete[] prev;
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
