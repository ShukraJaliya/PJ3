#ifndef UTIL_H
#define UTIL_H

#include "data_structures.h"
#include <iostream>
#include <vector>
#include <string>

class Util {
public:
    static void readGraph(const std::string& filename, Graph& graph, const std::string& graphType, int flag);
};

#endif // UTIL_H
