#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class graph{
        private:
                std::unordered_map<std::string, std::unordered_map<std::string, int>> adjList;
        public:
                graph();
                ~graph();
                bool vertex_exists(std::string vertex);
                bool edge_exists(std::string source, std::string target);
                void insert_vertex(std::string vertex);
                void insert_edge(std::string source, std::string target, int weight);
                std::vector<std::string> get_adjactent(std::string vertex);
                int get_weight(std::string source, std::string target);
                
};