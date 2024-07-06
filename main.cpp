#include "main.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFile = argv[1];
    std::string graphType = argv[2];
    int flag = std::stoi(argv[3]);

    Graph graph(0); // Initial size will be updated while reading the graph

    Util::readGraph(inputFile, graph, graphType, flag);

    std::string instruction;
    while (std::cin >> instruction) {
        if (instruction == "Stop") {
            break;
        } else if (instruction == "PrintADJ") {
            graph.printAdj();
        } else if (instruction == "SinglePair") {
            int source, destination;
            std::cin >> source >> destination;
            graph.singlePairShortestPath(source, destination);
        } else if (instruction == "SingleSource") {
            int source;
            std::cin >> source;
            graph.singleSourceShortestPath(source);
        } else if (instruction == "PrintLength") {
            int s, t;
            std::cin >> s >> t;
            graph.printLength(s, t);
        } else if (instruction == "PrintPath") {
            int s, t;
            std::cin >> s >> t;
            graph.printPath(s, t);
        } else {
            std::cerr << "Invalid instruction." << std::endl;
        }
    }

    return 0;
}
