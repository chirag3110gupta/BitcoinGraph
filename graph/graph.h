#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "edge.h"

class Graph {
   public:
    Graph();
    Graph(std::string filepath, bool hasHeader);
    ~Graph();

    bool edgeExists(Vertex source, Vertex target);
    bool vertexExists(Vertex vertex);
    void insertVertex(Vertex vertex);
    void insertEdge(Vertex source, Vertex target, double weight);
    std::vector<Vertex> getInAdjacent(Vertex vertex);
    std::vector<Vertex> getOutAjacent(Vertex vertex);
    int getRating(Vertex source, Vertex target);
    void BFS(int source);
    std::vector<std::vector<int>> LoadCSV(std::string filepath, bool hasHeader);

   private:

    std::unordered_map<
        int, std::pair<std::vector<Edge>, std::vector<Edge>>>
        adjList;
};