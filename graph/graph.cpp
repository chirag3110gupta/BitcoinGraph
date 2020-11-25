#include "graph.h"

#include <algorithm>

#include "../bitcoin/transaction.h"
#include "../bitcoin/user.h"

// hi this is aliva

Graph::Graph() {
    // nothing to do here
}

Graph::~Graph() {}

bool Graph::edge_exists(int source, int target) {
    if (!vertex_exists(source)) return false;

    for (auto &obj : adjList.at(source).first) {
        if (obj.source()->getUserID() == source &&
            obj.target()->getUserID() == target)
            return true;
    }
    return false;
}

bool Graph::vertex_exists(User vertex) {
    return adjList.find(vertex) != adjList.end();
}

void Graph::insert_vertex(User vertex) {
    adjList[vertex] =
        std::pair<std::vector<Transaction>, std::vector<Transaction>>();
}

void Graph::insert_edge(User source, User target, double weight) {
    if (!vertex_exists(source)) insert_vertex(source);

    if (!vertex_exists(target)) insert_vertex(target);

    User *heapSource = new User(source);
    User *heapTarget = new User(target);

    // cannot use addresses of keys as parameters for transaction class
    Transaction edge(heapSource, heapTarget, weight);
    heapSource->newTransaction(edge);
    heapTarget->newTransaction(edge);
    adjList[source].first.push_back(edge);
    adjList[target].second.push_back(edge);
}

std::vector<User> Graph::get_in_adjacent(User vertex) {
    std::vector<User> adjacent;
    for (auto &obj : adjList.at(vertex).second)
        adjacent.push_back(obj.source()->getUserID());

    return adjacent;
}

std::vector<User> Graph::get_out_ajacent(User vertex) {
    std::vector<User> adjacent;
    for (auto &obj : adjList.at(vertex).first)
        adjacent.push_back(obj.source()->getUserID());

    return adjacent;
}

double Graph::get_weight(int source, int target) {
    // TODO: Need to complete this function
    for (auto &obj : adjList.at(source).first) {
        if (obj.source()->getUserID() == source &&
            obj.target()->getUserID() == target)
    }
}