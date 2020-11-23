#include "graph.h"

#include <algorithm>

#include "../bitcoin/transaction.h"
#include "../bitcoin/user.h"

Graph::Graph() {
    //nothing to do here
}

bool Graph::edge_exists(User source, User target) {
    return vertex_exists(source) && adjList.at(source).find(/* find instance of transaction between s and t */) != adjList.at(source).end();
}

bool Graph::vertex_exists(User vertex) {
    return adjList.find(vertex) != adjList.end();
}

void Graph::insert_vertex(User vertex) {
    adjList[vertex] = std::vector<Transaction>();
}

void Graph::insert_edge(User source, User target, double weight) {
    if (!vertex_exists(source))
        insert_vertex(source);

    if (!vertex_exists(target))
        insert_vertex(target);

    //what do you do if a source interacts with a target more than once and gives a different rating?
    //Does this situation even exist in the dataset?
    adjList[source][target] = weight;
}

std::vector<User> Graph::get_adjacent(User vertex) {
    std::vector<User> adjacent;
    for (auto &obj : adjList[vertex])
        adjacent.push_back(obj.first);

    return adjacent;
}

double Graph::get_weight(User source, User target) {
    return adjList[source][target];
}