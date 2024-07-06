#include "util.h"
#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Util::readGraph(const std::string& filename, Graph& graph, const std::string& graphType, int flag) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int n, m;
    inputFile >> n >> m;

    for (int i = 0; i < m; ++i) {
        int edgeIndex, u, v;
        double w;
        inputFile >> edgeIndex >> u >> v >> w;

        if (graphType == "DirectedGraph") {
            graph.addEdge(u, v, w);
        } else if (graphType == "UndirectedGraph") {
            graph.addEdge(u, v, w);
            graph.addEdge(v, u, w);
        }
    }

    inputFile.close();
}
