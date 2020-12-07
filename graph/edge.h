/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include <limits.h>

#include <string>
#include <vector>

using std::string;

typedef int Vertex;

/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge {
   public:
    Vertex source; /**< The source of the edge **/
    Vertex target; /**< The destination of the edge **/

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     */
    Edge(Vertex u, Vertex v) : source(u), target(v), rating(INT_MIN) { /* nothing */
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param w - the rating of the edge
     */
    Edge(Vertex u, Vertex v, int w) : source(u), target(v), rating(w) { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(-1), target(-1), rating(INT_MIN) { /* nothing */
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const { return rating < other.rating; }

    /**
     * Compares two Edges.
     * operator> is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is greater than the parameter
     */
    bool operator>(const Edge& other) const { return rating > other.rating; }

    /**
     * Gets edge rating.
     */
    int getRating() const { return this->rating; }

    /**
     * Compares two edges' source and target.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const {
        if (this->source != other.source) return false;
        if (this->target != other.target) return false;
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        std::string src("Source: "), tar(", Target: "), rat(", Rating: ");
        os << src << std::to_string(e.source) << tar << std::to_string(e.target) << rat
           << std::to_string(e.getRating());
           
        return os;
    }

   private:
    int rating; /**< The edge rating (if in a weighed graph) **/
};
