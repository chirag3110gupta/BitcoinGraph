#include "graph.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "../bitcoin/transaction.h"
#include "../bitcoin/user.h"

using namespace std;

/**
 * This function creates an instance of the graph object with uninitialized
 *parameters
 **/
Graph::Graph() {
    // nothing to do here
}

Graph::~Graph() {}

/**
 * Tells whether or not an edge exists between two specified integer value ID's
 *
 * @param source The integer starting/base vertex for expected edge
 * @param target The integer ending/final vertex for expected edge
 * @returns A bool where true implies that the edge exists and vice versa
 **/
bool Graph::edge_exists(int source, int target) {
    if (!vertex_exists(source)) return false;

    for (auto &obj : adjList.at(source).first) {
        if (obj.source()->getUserID() == source &&
            obj.target()->getUserID() == target)
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
bool Graph::vertex_exists(User vertex) {
    return adjList.find(vertex) != adjList.end();
}

/**
 * Inserts a vertex into the adjacency list
 *
 * @param vertex The user object that needs to be inserted into the graph
 * @returns void
 **/
void Graph::insert_vertex(User vertex) {
    adjList[vertex] =
        std::pair<std::vector<Transaction>, std::vector<Transaction>>();
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
void Graph::insert_edge(User source, User target, double rating) {
    if (!vertex_exists(source)) insert_vertex(source);

    if (!vertex_exists(target)) insert_vertex(target);

    User *heapSource = new User(source);
    User *heapTarget = new User(target);

    // cannot use addresses of keys as parameters for transaction class
    Transaction edge(heapSource, heapTarget, rating);
    heapSource->newTransaction(edge);
    heapTarget->newTransaction(edge);
    adjList[source].first.push_back(edge);
    adjList[target].second.push_back(edge);
}

/**
 * Finds the adjacent vertices that have an incoming directed edge to a
 *specified vertex
 *
 * @param vertex The vertex who's incoming adjacent vertices need to be found
 * @returns A vector of Users that have an incoming edge to the specified
 *vertex
 **/
std::vector<User> Graph::get_in_adjacent(User vertex) {
    std::vector<User> adjacent;
    for (auto &obj : adjList.at(vertex).second)
        adjacent.push_back(obj.source()->getUserID());

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
std::vector<User> Graph::get_out_ajacent(User vertex) {
    std::vector<User> adjacent;
    for (auto &obj : adjList.at(vertex).first)
        adjacent.push_back(obj.source()->getUserID());

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
double Graph::get_rating(int source, int target) {
    for (auto &obj : adjList.at(source).first) {
        if (obj.source()->getUserID() == source &&
            obj.target()->getUserID() == target)
            return obj.rating();
    }
}

void Graph::BFS(int source) {
    vector<bool> visited;
    std::list<int> queue;
    visited[source] = true;
    queue.push_back(source);

    while (!queue.empty()) {
        int source = queue.front();
        queue.pop_front();

        for (auto &obj : adjList.at(source).first) {
            /**
             *  explanation
             **/
            if (!visited[(*obj.target()).getUserID()]) {
                visited[(*obj.target()).getUserID()] = true;
                queue.push_back((*obj.target()).getUserID());
            }
        }
    }
}

void Graph::PageRank(int iterations) {

    std::unordered_map<User, double> oldPageRank, newPageRank;
    double sizeOfGraph = adjList.size();
    double dampingFactor = 0.85;

    for (auto& pair : adjList) {
        User curr = pair.first;
        oldPageRank[curr] = 1/sizeOfGraph;
    }

    while (iterations > 0) {
        double dp = 0;

        for (auto& pair : adjList) {
            User curr = pair.first;
            if (curr.transactionsFromUser() == 0) {
                dp = dp + (dampingFactor * oldPageRank[curr]/sizeOfGraph);
            }
        }

        for (auto& pair : adjList) {
            User curr = pair.first;
            newPageRank[curr] = dp + ((1 - dampingFactor)/sizeOfGraph);
            for (Transaction& transaction : adjList[curr].second) {
                newPageRank[curr] += dampingFactor * oldPageRank[*transaction.source()]/transaction.source()->transactionsFromUser();
            }
        }
        oldPageRank = newPageRank;
        iterations--;
    }

    pagerank = newPageRank;
}