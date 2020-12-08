#include "graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

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

std::unordered_map<int, double> Graph::PageRank(int iterations) {
    std::unordered_map<int, double> oldPageRank, newPageRank;
    double sizeOfGraph = adjList.size();
    double dampingFactor = 0.85;

    for (auto& pair : adjList) {
        int curr = pair.first;
        oldPageRank[curr] = 1/sizeOfGraph;
    }

    while (iterations > 0) {
        double dp = 0;

        for (auto& pair : adjList) {
            int curr = pair.first;
            if (adjList[curr].second.size() == 0) {                             // Transactions from user
                dp = dp + (dampingFactor * oldPageRank[curr]/sizeOfGraph);
            }
        }

        for (auto& pair : adjList) {
            int curr = pair.first;
            newPageRank[curr] = dp + ((1 - dampingFactor)/sizeOfGraph);
            for (Edge& transaction : adjList[curr].second) {
                newPageRank[curr] += dampingFactor * oldPageRank[transaction.source]/adjList[transaction.source].second.size(); // Transactions from user
            }
        }
        oldPageRank = newPageRank;
        iterations--;
    }

    return newPageRank;
}

std::unordered_map<int, double> Graph::betweennessCentrality(){
    std::unordered_map<int, double> centrality;
    for(auto & source : adjList) {
        centrality[source.first] = 0.0;
    }
    // int count = 0;
    for(auto & source : adjList) {
        // This represents the list of predecessors on the shortest paths from the selected source vertex 
        std::unordered_map<int, std::vector<int>> Pred; 
        // Shortest distance of each vertex from the source
        std::unordered_map<int, int> Dist;
        // Number of shortest paths from source to given vertex
        std::unordered_map<int, int> sig;
        std::queue<int> Q;
        for(auto & mid : adjList) {
            std::vector<int> list;
            Pred[mid.first] = list;
            // -1 implies infinite
            Dist[mid.first] = -1;
            sig[mid.first] = 0;
        }
        Dist[source.first] = 0;
        sig[source.first] = 1;
        Q.push(source.first);

        std::stack<int> S;
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            S.push(v);
            for(auto & dest : adjList.at(v).first) {
                if(Dist.at(dest.target) == -1){
                    Dist[dest.target] = Dist.at(v) + 1;
                    Q.push(dest.target);
                }

                if(Dist.at(dest.target) == Dist.at(v) + 1) {
                    sig[dest.target] = sig.at(v) + sig.at(dest.target);
                    Pred[dest.target].push_back(v);
                }
            }
        }

        std::unordered_map<int, double> delta;
        for(auto & vert : adjList) {
            delta[vert.first] = 0.0;
        }
        while(!S.empty()) {
            int w = S.top();
            S.pop();
            for(auto & obj : Pred.at(w)) {
                delta[obj] = delta.at(obj) + ((sig.at(obj)/sig.at(w))*(1+delta.at(w)));
                if(w != source.first) {
                    centrality[w] = centrality.at(w) + delta.at(w);
                }
            }
        }
        // count += sig.size();
    }
    // std::cout << count << std::endl;
    return centrality;
}