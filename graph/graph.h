#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "edge.h"

class Graph {
   public:
    /**
     * This function creates an instance of the graph object with uninitialized
     *parameters
     **/
    Graph();

    /**
     * This is the constructor used to create a graph from a given CSV file. It calls on LoadCSV to parse the edge list,
     *and then inserts edges accordingly.
     *
     * @param filepath The filepath to the file with the edgelist relative to the current working directory
     * @param hasHeader A boolean for whether or not the CSV file contains headers
     **/
    Graph(std::string filepath, bool hasHeader);

    /**
     * Empty destructor
     **/
    ~Graph();

    /**
     * Tells whether or not an edge exists between two specified integer value ID's
     *
     * @param source The integer starting/base vertex for expected edge
     * @param target The integer ending/final vertex for expected edge
     * @returns A bool where true implies that the edge exists and vice versa
     **/
    bool edgeExists(Vertex source, Vertex target);

    /**
     * Tells whether or not a vertex with a specified ID exists within the graph
     *structure
     *
     * @param vertex The user object who's existence needs to be checked
     * @returns A bool where true implies that the vertex exists and vice versa
     **/
    bool vertexExists(Vertex vertex);

    /**
     * Inserts a vertex into the adjacency list
     *
     * @param vertex The user object that needs to be inserted into the graph
     * @returns void
     **/
    void insertVertex(Vertex vertex);

    /**
     * Inserts an edge into the adjacency list
     *
     * @param source The user object that the edge should begin from
     * @param target The user object that the edge should be directed towards
     * @param rating The source user rating of the target that acts as the weights
     *for the directed edges
     * @returns void
     **/
    void insertEdge(Vertex source, Vertex target, int weight);

    /**
     * Finds the adjacent vertices that have an incoming directed edge to a
     *specified vertex
     *
     * @param vertex The vertex who's incoming adjacent vertices need to be found
     * @returns A vector of Users that have an incoming edge to the specified
     *vertex
     **/
    std::vector<Vertex> getInAdjacent(Vertex vertex);

    /**
     * Finds the adjacent vertices that have an outgoing directed edge from a
     *specified vertex
     *
     * @param vertex The vertex who's outgoing adjacent vertices need to be found
     * @returns A vector of Users that have an ougoing edge from the specified
     *vertex
     **/
    std::vector<Vertex> getOutAdjacent(Vertex vertex);

    /**
     * Gets the rating of a target User given by the source User. Assumes that the
     *edge exists, thus the onus of managing exceptions is on the future user.
     *
     * @param source The integer ID of the source User
     * @param target The integer ID of the target User
     * @returns A double representing the rating given by a source User to a target
     *User
     **/
    int getRating(Vertex source, Vertex target);

    /**
     * Traverses through the graph by going on breadth first traversal and tracks previous vertices
     *
     * @param source The source User through which we start BFS
     * @returns An unordered_map with the userID as key and previous vertex's ID as the value
     **/
    std::unordered_map<int, int> BFS(int source);

    /**
     * Gives the path from a source user to a target user using BFS traversal.
     *
     * @param source The base user to start the path from
     * @param target The end user to end the path at
     * @return A vector of integers (vertices) representing the shortest path between the two source and target
     **/
    std::vector<int> findPath(int source, int target);

    /**
     * Function to load a csv into a vector format for the graph to use
     *
     * @param filepath path to csv file
     * @param hasHeader whether the csv file has a header row
     * @return std::vector<std::vector<int>> data from file as a vector
     */
    std::vector<std::vector<int>> LoadCSV(std::string filepath, bool hasHeader);

    /**
     * Prints out the graph
     */
    void printGraph();

    /**
     * Ranks the vertices based on their relative importance to each other. This gives the trust leavels of various
     *bitcoin users based on how many other nodes point to it and the trust of those nodes.
     *
     * @param iterations Represents the number of iterations the user wants the pagerank algorithm ot run for.
     * @return Returns an unordered map with a rank for each vertex
     **/
    std::unordered_map<int, double> PageRank(int iterations);

    /**
     * This function uses Brande's Algorithm to find the betweenness centrality number for each of the vertices. It does
     * this by calculating the dependency of the source to target path on the vertex, which is to say, it finds how
     * essential a vertex is to the paths between the source and the target.
     *
     * @return An unordered map with each vertex and its betweenness number.
     **/
    std::unordered_map<int, double> betweennessCentrality();

    /**
     * Get the number of Edges in the graph
     *
     * @return int
     */
    int getNumVertices() { return numVertices; }

    /**
     * Get the number of Edges in the graph
     *
     * @return int
     */
    int getNumEdges() { return numEdges; }

   private:
    int numVertices{0}, numEdges{0};
    std::unordered_map<int, std::pair<std::vector<Edge>, std::vector<Edge>>> adjList;
};