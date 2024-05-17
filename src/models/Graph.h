#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
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

    void clearGraph();

    // Getters
    unordered_map<int, Vertex *> getVertexSet() const;

    double tspBacktracking(vector<int> &path);

    double tspNearestNeighbour(vector<int> &path);

protected:
    unordered_map<int, Vertex *> vertexSet;    // vertex set

    double tspBacktracking(vector<int> &path, int vertex, double sum, double bestSum, unsigned step);

    static double convert(double angle);

    static double calculate_distance(double latitude1, double latitude2, double longitude1, double longitude2);

    pair<vector<int>, double> TriangularApproximation();

    Vertex *findNearestNeighbour(Vertex *v);

    double calculateDistance(Coordinates c1, Coordinates c2);

    double haversineDistance(Coordinates c1, Coordinates c2);

    double calculateDistance(Vertex *v1, Vertex *v2);
};

#endif /* DA_TP_CLASSES_GRAPH */