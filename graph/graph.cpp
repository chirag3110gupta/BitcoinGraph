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
    auto data = LoadCSV(filepath, hasHeader);
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
        if (edge == e)
            return true;
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
bool Graph::vertexExists(Vertex vertex) {
    return adjList.find(vertex) != adjList.end();
}

/**
 * Inserts a vertex into the adjacency list
 *
 * @param vertex The user object that needs to be inserted into the graph
 * @returns void
 **/
void Graph::insertVertex(Vertex vertex) {
    adjList[vertex] =
        std::pair<std::vector<Edge>, std::vector<Edge>>();
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
// void Graph::insert_edge(User source, User target, double rating) {
// if (!vertex_exists(source)) insert_vertex(source);

// if (!vertex_exists(target)) insert_vertex(target);

// User *heapSource = new User(source);
// User *heapTarget = new User(target);

// // cannot use addresses of keys as parameters for transaction class
// Transaction edge(heapSource, heapTarget, rating);
// // heapSource->newTransaction(edge);
// // heapTarget->newTransaction(edge);
// adjList[source].first.push_back(edge);
// adjList[target].second.push_back(edge);
// }

/**
 * Finds the adjacent vertices that have an incoming directed edge to a
 *specified vertex
 *
 * @param vertex The vertex who's incoming adjacent vertices need to be found
 * @returns A vector of Users that have an incoming edge to the specified
 *vertex
 **/
// std::vector<User> Graph::get_in_adjacent(User vertex) {
// std::vector<User> adjacent;
// for (auto &obj : adjList.at(vertex).second)
//     adjacent.push_back(obj.source()->getUserID());

// return adjacent;
// }

/**
 * Finds the adjacent vertices that have an outgoing directed edge from a
 *specified vertex
 *
 * @param vertex The vertex who's outgoing adjacent vertices need to be found
 * @returns A vector of Users that have an ougoing edge from the specified
 *vertex
 **/
// std::vector<User> Graph::get_out_ajacent(User vertex) {
// std::vector<User> adjacent;
// for (auto &obj : adjList.at(vertex).first)
//     adjacent.push_back(obj.source()->getUserID());

// return adjacent;
// }

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
    for (auto &edge : adjList.at(source).first) {
        if (e == edge)
            return edge.getRating();
    }

    return e.getRating();  // INT_MIN
}

// void Graph::BFS(int source) {
// vector<bool> visited;
// std::list<int> queue;
// visited[source] = true;
// queue.push_back(source);

// while (!queue.empty()) {
//     int source = queue.front();
//     queue.pop_front();

//     for (auto &obj : adjList.at(source).first) {
//         /**
//          *  explanation
//          **/
//         if (!visited[(*obj.target()).getUserID()]) {
//             visited[(*obj.target()).getUserID()] = true;
//             queue.push_back((*obj.target()).getUserID());
//         }
//     }
// }
// }

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
    } else {
        std::cerr << "Invalid csv filepath" << std::endl;
    }

    data.close();
    return toReturn;
}