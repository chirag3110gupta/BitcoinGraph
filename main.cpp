#include <iostream>

#include "bitcoin/user.h"
#include "graph/graph.h"
#include "loadcsv/loadcsv.h"

int main() {
    auto g = Graph("assets/datasets/data.csv", true);
    // auto b = g.LoadCSV("assets/datasets/data.csv", true);
    // for (auto j : b)
    //     std::cout<<j<<std::endl;
}