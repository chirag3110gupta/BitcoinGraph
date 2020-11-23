#pragma once

#include <unordered_map>
#include <vector>

#include "../bitcoin/transaction.h"
#include "../bitcoin/user.h"

class Graph {
   public:
    Graph();
    ~Graph();

    bool vertex_exists(User vertex);
    bool edge_exists(User source, User target);
    void insert_vertex(User vertex);
    void insert_edge(User source, User target, double weight);
    std::vector<User> get_adjacent(User vertex);
    double get_weight(User source, User target);

   private:
    std::unordered_map<User, std::vector<Transaction>> adjList;
};