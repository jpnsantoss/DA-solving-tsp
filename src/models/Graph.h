#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "../utils/DataStructures//MutablePriorityQueue.h"
#include "VertexEdge.h"

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();

    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const int &id) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Vertex *v);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(Vertex* v1, Vertex* v2, double distance) const;

    bool addBidirectionalEdge(Vertex* v1, Vertex* v2, double distance) const;

    // Getters
    unordered_map<int, Vertex *> getVertexSet() const;

protected:
    unordered_map<int, Vertex *> vertexSet;    // vertex set
};

#endif /* DA_TP_CLASSES_GRAPH */