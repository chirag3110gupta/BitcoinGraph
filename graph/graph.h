#pragma once

#include <unordered_map>
#include <vector>

#include "../bitcoin/transaction.h"
#include "../bitcoin/user.h"

class Graph {
   public:
    Graph();
    ~Graph();

    bool edge_exists(int source, int target);
    bool vertex_exists(User vertex);
    void insert_vertex(User vertex);
    void insert_edge(User source, User target, double weight);
    std::vector<User> get_in_adjacent(User vertex);
    std::vector<User> get_out_ajacent(User vertex);
    double get_rating(int source, int target);
    void BFS(int source);

   private:
    std::unordered_map<
        User, std::pair<std::vector<Transaction>, std::vector<Transaction>>>
        adjList;
};