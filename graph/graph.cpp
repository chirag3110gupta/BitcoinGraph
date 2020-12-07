#include "graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "edge.h"

/**
 * This function creates an instance of the graph object with uninitialized
 *parameters
 **/
Graph::Graph() {
    // nothing to do here
}

Graph::Graph(std::string filepath, bool hasHeader) {
    for (auto entry : LoadCSV(filepath, hasHeader)) insertEdge(entry[0], entry[1], entry[2]);
}

Graph::~Graph() {}

/**
 * Tells whether or not an edge exists between two specified integer value ID's
 *
 * @param source The integer starting/base vertex for expected edge
 * @param target The integer ending/final vertex for expected edge
 * @returns A bool where true implies that the edge exists and vice versa
 **/
bool Graph::edgeExists(Vertex source, Vertex target) {
    auto e = Edge(source, target);
    if (!vertexExists(source)) return false;

    for (auto &edge : adjList.at(source).first) {
        if (edge == e) return true;
    }

    return false;
}

/**
 * Tells whether or not a vertex with a specified ID exists within the graph
 *structure
 *
 * @param vertex The user object who's existence needs to be checked
 * @returns A bool where true implies that the vertex exists and vice versa
 **/
bool Graph::vertexExists(Vertex vertex) { return adjList.find(vertex) != adjList.end(); }

/**
 * Inserts a vertex into the adjacency list
 *
 * @param vertex The user object that needs to be inserted into the graph
 * @returns void
 **/
void Graph::insertVertex(Vertex vertex) {
    adjList[vertex] = std::pair<std::vector<Edge>, std::vector<Edge>>();
    numVertices++;
}

/**
 * Inserts an edge into the adjacency list
 *
 * @param source The user object that the edge should begin from
 * @param target The user object that the edge should be directed towards
 * @param rating The source user rating of the target that acts as the weights
 *for the directed edges
 * @returns void
 **/

void Graph::insertEdge(Vertex source, Vertex target, int rating) {
    if (!vertexExists(source)) insertVertex(source);

    if (!vertexExists(target)) insertVertex(target);

    adjList[source].first.emplace_back(Edge(source, target, rating));
    adjList[target].second.emplace_back(Edge(source, target, rating));

    numEdges++;
}

/**
 * Finds the adjacent vertices that have an incoming directed edge to a
 *specified vertex
 *
 * @param vertex The vertex who's incoming adjacent vertices need to be found
 * @returns A vector of Users that have an incoming edge to the specified
 *vertex
 **/
std::vector<Vertex> Graph::getInAdjacent(Vertex vertex) {
    auto adjacent = std::vector<Vertex>();
    for (auto &edge : adjList.at(vertex).second) adjacent.push_back(edge.source);

    return adjacent;
}

/**
 * Finds the adjacent vertices that have an outgoing directed edge from a
 *specified vertex
 *
 * @param vertex The vertex who's outgoing adjacent vertices need to be found
 * @returns A vector of Users that have an ougoing edge from the specified
 *vertex
 **/
std::vector<Vertex> Graph::getOutAjacent(Vertex vertex) {
    auto adjacent = std::vector<Vertex>();
    for (auto &edge : adjList.at(vertex).first) adjacent.push_back(edge.source);

    return adjacent;
}

/**
 * Gets the rating of a target User given by the source User. Assumes that the
 *edge exists, thus the onus of managing exceptions is on the future user.
 *
 * @param source The integer ID of the source User
 * @param target The integer ID of the target User
 * @returns A double representing the rating given by a source User to a target
 *User
 **/
int Graph::getRating(Vertex source, Vertex target) {
    auto e = Edge(source, target);
    for (auto &edge : adjList.at(source).first)
        if (e == edge) return edge.getRating();

    return e.getRating();  // INT_MIN
}

/*
void Graph::BFS(int source) {
vector<bool> visited;
std::list<int> queue;
visited[source] = true;
queue.push_back(source);

while (!queue.empty()) {
    int source = queue.front();
    queue.pop_front();

    for (auto &obj : adjList.at(source).first) {

        // TODO:explanation

        if (!visited[(*obj.target()).getUserID()]) {
            visited[(*obj.target()).getUserID()] = true;
            queue.push_back((*obj.target()).getUserID());
        }
    }
}
}
**/

std::vector<std::vector<int>> Graph::LoadCSV(std::string filepath, bool hasHeader) {
    std::vector<std::vector<int>> toReturn;
    std::ifstream data(filepath);
    std::string line;

    if (data.is_open()) {
        if (hasHeader)  // Ignore the headers of the csv
            getline(data, line);

        while (getline(data, line)) {
            std::stringstream ss(line);
            std::string intermediate;
            auto tempVec = std::vector<int>();

            while (getline(ss, intermediate, ',')) {  // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
                std::stringstream tempSS(intermediate);
                int tempInt = 0;
                tempSS >> tempInt;  // https://www.geeksforgeeks.org/converting-strings-numbers-cc/
                tempVec.push_back(tempInt);
            }

            toReturn.push_back(tempVec);
        }
    } else
        std::cerr << "Invalid csv filepath" << std::endl;

    data.close();
    return toReturn;
}

void Graph::printGraph() {
    for (auto entry : adjList) {
        for (auto f : entry.second.first) std::cout << f << std::endl;
        std::cout << std::endl;

        for (auto f : entry.second.second) std::cout << f << std::endl;
        std::cout << std::endl << std::endl;
    }

    std::cout << std::endl
              << "Created graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
}