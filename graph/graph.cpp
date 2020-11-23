#include "graph.h"

#include <algorithm>

Graph::Graph() {
    //nothing to do here
}

bool Graph::edge_exists(std::string source, std::string target) {
    return vertex_exists(source) && adjList.at(source).find(target) != adjList.at(source).end();
}

bool Graph::vertex_exists(std::string vertex) {
    return adjList.find(vertex) != adjList.end();
}

void Graph::insert_vertex(std::string vertex) {
    adjList[vertex] = std::unordered_map<std::string, int>();
}

void Graph::insert_edge(std::string source, std::string target, int weight) {
    if (!vertex_exists(source)) 
        insert_vertex(source);
    
    if (!vertex_exists(target)) 
        insert_vertex(target);
    
    //what do you do if a source interacts with a target more than once and gives a different rating?
    //Does this situation even exist in the dataset?
    adjList[source][target] = weight;
}

std::vector<std::string> Graph::get_adjacent(std::string vertex) {
    std::vector<std::string> adjacent;
    for (auto &obj : adjList[vertex]) 
        adjacent.push_back(obj.first);
    
    return adjacent;
}

int Graph::get_weight(std::string source, std::string target) {
    return adjList[source][target];
}