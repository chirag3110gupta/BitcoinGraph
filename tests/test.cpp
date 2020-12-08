#include <vector>

#include "../graph/edge.h"
#include "../graph/graph.h"
#include "catch/catch.hpp"

TEST_CASE("Graph::Number of vertices (with heading)", "[weight=1][part=1][valgrind]") {
    Graph g = Graph("tests/test_data_headings.csv", true);
    REQUIRE(g.getNumVertices() == 34);
}

TEST_CASE("Graph::Number of edges (with heading)", "[weight=1][part=1][valgrind]") {
    Graph g = Graph("tests/test_data_headings.csv", true);
    REQUIRE(g.getNumEdges() == 81);
}

TEST_CASE("Graph::Number of vertices (without heading)", "[weight=1][part=1][valgrind]") {
    Graph g = Graph("tests/test_data_noheadings.csv", false);
    REQUIRE(g.getNumVertices() == 34);
}

TEST_CASE("Graph::Number of edges (without heading)", "[weight=1][part=1][valgrind]") {
    Graph g = Graph("tests/test_data_noheadings.csv", false);
    REQUIRE(g.getNumEdges() == 81);
}

TEST_CASE("Graph::LoadCSV::With headings)", "[weight=1][part=1][valgrind]") {
    Graph g = Graph();
    auto given_vec = std::vector<std::vector<int>>();
    given_vec.emplace_back(std::vector<int>{1, 2, 7});
    given_vec.emplace_back(std::vector<int>{2, 5, -7});
    given_vec.emplace_back(std::vector<int>{4, 7, 2});
    REQUIRE(g.LoadCSV("tests/test_loadCSV.csv", true) == given_vec);
}

TEST_CASE("Graph::LoadCSV::Without headings)", "[weight=1][part=1][valgrind]") {
    Graph g = Graph();
    auto given_vec = std::vector<std::vector<int>>();
    given_vec.emplace_back(std::vector<int>{1, 2, 7});
    given_vec.emplace_back(std::vector<int>{2, 5, -7});
    given_vec.emplace_back(std::vector<int>{4, 7, 2});

    REQUIRE(g.LoadCSV("tests/test_loadCSV_noheadings.csv", false) == given_vec);
}

TEST_CASE("Betweenness Centrality # 1", "[weigh=1][part=2]") {
    Graph g = Graph("tests/test_data_headings.csv", true);
    std::unordered_map<int, double> cent = g.betweennessCentrality();
    REQUIRE(cent[6] < cent[1]);
}

TEST_CASE("Betweenness Centrality # 2", "[weigh=1][part=2]") {
    Graph g = Graph("tests/test_data_headings.csv", true);
    std::unordered_map<int, double> cent = g.betweennessCentrality();
    REQUIRE(cent[52] == 0);
}