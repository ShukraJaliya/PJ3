#ifndef UTIL_H
#define UTIL_H

#include <string>

class Graph;

class Util {
public:
    static void readGraph(const std::string& filename, Graph& graph, const std::string& graphType, int flag);
};

#endif // UTIL_H
