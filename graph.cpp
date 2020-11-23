#include "graph.h"
#include <algorithm>

graph::graph(){
        //nothing to do here
}

bool graph::edge_exists(std::string source, std::string target){
        if(vertex_exists(source) && adjList.at(source).find(target) != adjList.at(source).end()){
                return true;
        }
        return false;
}

bool graph::vertex_exists(std::string vertex){
        if(adjList.find(vertex) != adjList.end()){
                return true;
        }
        return false;
}

void graph::insert_vertex(std::string vertex){
        adjList[vertex] = std::unordered_map<std::string, int>();
}

void graph::insert_edge(std::string source, std::string target, int weight){
        if(!vertex_exists(source)){
                insert_vertex(source);
        }
        if(!vertex_exists(target)){
                insert_vertex(target);
        }
        //what do you do if a source interacts with a target more than once and gives a different rating?
        //Does this situation even exist in the dataset?
        adjList[source][target] = weight;
}

std::vector<std::string> graph::get_adjactent(std::string vertex){
        std::vector<std::string> adjacent;
        for(auto &obj : adjList[vertex]){
                adjacent.push_back(obj.first);
        }
        return adjacent;
}

int graph::get_weight(std::string source, std::string target){
        return adjList[source][target];
}