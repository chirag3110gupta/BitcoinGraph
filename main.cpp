#include <iostream>


#include "graph/graph.h"


int main() {
    auto g = Graph("assets/data.csv", true);
    // auto g = Graph("assets/data.csv", true);
    g.printGraph();
}