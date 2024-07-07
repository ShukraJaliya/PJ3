#include <iostream>
#include <string>
#include "graph.h"
#include "util.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <InputFile> <GraphType> <Flag>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string graphType = argv[2];
    int flag = std::stoi(argv[3]);

    Graph graph(0, graphType);  // Initial size will be updated while reading the graph
    Util::readGraph(inputFile, graph, graphType, flag);

    std::string operation;
    while (std::cin >> operation) {
        if (operation == "PrintADJ") {
            graph.printAdj();
        // } else if (operation == "SinglePairShortestPath") {
        //     int source, destination;
        //     std::cin >> source >> destination;
        //     graph.singlePairShortestPath(source, destination);
        } else if (operation == "SingleSourceShortestPath") {
            int source;
            std::cin >> source;
            graph.singleSourceShortestPath(source);
        } else if (operation == "PrintLength") {
            int s, t;
            std::cin >> s >> t;
            graph.printLength(s, t);
        } else if (operation == "PrintPath") {
            int s, t;
            std::cin >> s >> t;
            graph.printPath(s, t);
        } else if (operation == "Stop") {
            break;
        } else {
            std::cerr << "Invalid instruction." << std::endl;
        }
    }

    return 0;
}
