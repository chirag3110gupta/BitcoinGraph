#include "graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "edge.h"

/**
 * This function creates an instance of the graph object with uninitialized
 * parameters
 **/
Graph::Graph() {
    // nothing to do here
}

/**
 * This is the constructor used to create a graph from a given CSV file. It calls on LoadCSV to parse the edge list, and
 * then inserts edges accordingly.
 *
 * @param filepath The filepath to the file with the edgelist relative to the current working directory
 * @param hasHeader A boolean for whether or not the CSV file contains headers
 **/
Graph::Graph(std::string filepath, bool hasHeader) {
    for (auto entry : LoadCSV(filepath, hasHeader)) insertEdge(entry[0], entry[1], entry[2]);
}

/**
 * Empty destructor
 **/
Graph::~Graph() {
    // Nothing to do here
}

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

    for (auto& edge : adjList.at(source).first) {
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

    for (auto& edge : adjList.at(vertex).second) adjacent.push_back(edge.source);

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
std::vector<Vertex> Graph::getOutAdjacent(Vertex vertex) {
    auto adjacent = std::vector<Vertex>();

    for (auto& edge : adjList.at(vertex).first) adjacent.push_back(edge.target);

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

    for (auto& edge : adjList.at(source).first)
        if (e == edge) return edge.getRating();

    return e.getRating();  // INT_MIN
}

/**
 * Traverses through the graph by going on breadth first traversal and tracks previous vertices
 *
 * @param source The source User through which we start BFS
 * @returns An unordered_map with the userID as key and previous vertex's ID as the value
 **/
std::unordered_map<int, int> Graph::BFS(int source) {
    std::unordered_map<int, int> toReturn;
    std::unordered_map<int, bool> visited(false);
    std::list<int> queue;
    visited[source] = true;
    queue.push_back(source);

    while (!queue.empty()) {
        int source = queue.front();
        queue.pop_front();

        for (auto& obj : getOutAdjacent(source)) {
            if (!visited[obj]) {
                visited[obj] = true;
                toReturn[obj] = source;
                queue.push_back(obj);
            }
        }
    }
    return toReturn;
}

/**
 * Gives the path from a source user to a target user using BFS traversal.
 *
 * @param source The base user to start the path from
 * @param target The end user to end the path at
 * @return A vector of integers (vertices) representing the shortest path between the two source and target
 **/
std::vector<int> Graph::findPath(int source, int target) {
    auto bfs = BFS(source);
    int curr = bfs[target];
    std::vector<int> toReturn;
    toReturn.push_back(target);
    int count = 0;
    std::cout << "The path is : \n";

    while (curr != 0 && count < getNumEdges()) {
        toReturn.push_back(curr);
        curr = bfs[curr];
        count++;
    }
    std::reverse(toReturn.begin(), toReturn.end());
    return toReturn;
}

/**
 * Function to load a csv into a vector format for the graph to use
 *
 * @param filepath path to csv file
 * @param hasHeader whether the csv file has a header row
 * @return std::vector<std::vector<int>> data from file as a vector
 */
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
    }

    else
        std::cerr << "Invalid csv filepath" << std::endl;

    data.close();
    return toReturn;
}

/**
 * Prints out the graph
 */
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

/**
 * Ranks the vertices based on their relative importance to each other. This gives the trust leavels of various bitcoin
 * users based on how many other nodes point to it and the trust of those nodes.
 *
 * @param iterations Represents the number of iterations the user wants the pagerank algorithm ot run for.
 * @return Returns an unordered map with a rank for each vertex
 **/
std::unordered_map<int, double> Graph::PageRank(int iterations) {
    double d = 0.85;
    std::unordered_map<int, int> oh;
    std::unordered_map<int, std::vector<int>> ih;
    std::unordered_map<int, double> opg, npg;
    int N = adjList.size();

    for (auto& pair : adjList) {
        oh[pair.first] = adjList[pair.first].first.size();
        ih[pair.first] = getInAdjacent(pair.first);
        opg[pair.first] = 1 / N;
    }

    while (iterations > 0) {
        double dp = 0;

        for (auto& pair : adjList) {
            int p = pair.first;

            if (oh[p] == 0) {
                dp = dp + d * opg[p] / N;
            }
        }

        for (auto& pair : adjList) {
            int p = pair.first;
            npg[p] = dp + (1 - d) / N;

            for (auto& ip : ih[p]) {
                npg[p] += d * opg[ip] / oh[ip];
            }
        }
        opg = npg;
        iterations--;
    }
    return npg;
}

/**
 * This function uses Brande's Algorithm to find the betweenness centrality number for each of the vertices. It does
 * this by calculating the dependency of the source to target path on the vertex, which is to say, it finds how
 * essential a vertex is to the paths between the source and the target.
 *
 * @return An unordered map with each vertex and its betweenness number.
 **/
std::unordered_map<int, double> Graph::betweennessCentrality() {
    std::unordered_map<int, double> centrality;
    for (auto& source : adjList) {
        centrality[source.first] = 0.0;
    }
    for (auto& source : adjList) {
        // This represents the list of predecessors on the shortest paths from the selected source vertex
        std::unordered_map<int, std::vector<int>> Pred;
        // Shortest distance of each vertex from the source
        std::unordered_map<int, int> Dist;
        // Number of shortest paths from source to given vertex
        std::unordered_map<int, double> sig;
        std::queue<int> Q;
        for (auto& mid : adjList) {
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

        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            S.push(v);

            for (auto& dest : adjList.at(v).second) {
                if (Dist.at(dest.source) == -1) {
                    // Distance to a vertex is the distance to its shortest path predecessor plus 1
                    Dist[dest.source] = Dist.at(v) + 1;
                    Q.push(dest.source);
                }

                if (Dist.at(dest.source) == Dist.at(v) + 1) {
                    // The number of shortest paths for a vertex is simply the sum of the shortest paths of its
                    // predecessors
                    sig[dest.source] = sig.at(v) + sig.at(dest.source);
                    Pred[dest.source].push_back(v);
                }
            }
        }

        std::unordered_map<int, double> delta;

        for (auto& vert : adjList) {
            delta[vert.first] = 0.0;
        }

        while (!S.empty()) {
            int w = S.top();
            S.pop();

            for (auto& obj : Pred.at(w)) {
                delta[obj] = delta.at(obj) + ((sig.at(obj) / sig.at(w)) * (1 + delta.at(w)));
            }

            if (w != source.first) {
                centrality[w] = centrality.at(w) + delta.at(w);
            }
        }
    }
    return centrality;
}