#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include "../utils/DataStructures//MutablePriorityQueue.h"
#include "VertexEdge.h"

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();

    /**
     * Get the vertex set of a graph (this).
     * Complexity: O(1)
     * @return the vertex set
     */
    unordered_map<int, Vertex *> getVertexSet() const;

    /**
     * Finds a vertex with a given id in a graph (this).
     * Complexity: O(1)
     * @param id
     * @return a pointer to the vertex if it exists, and a nullptr otherwise
     */
    Vertex *findVertex(const int &id) const;

    /**
     * Adds a vertex to a graph (this).
     * Complexity: O(1)
     * @param v
     * @return true if the vertex was added, and false otherwise
     */
    bool addVertex(Vertex *v);

    /**
     * Adds a bidirectional edge between two vertices in a graph (this).
     * Complexity: O(1)
     * @param v1
     * @param v2
     * @param distance
     * @return true if the edge was added, and false otherwise
     */
    bool addBidirectionalEdge(Vertex* v1, Vertex* v2, double distance) const;

    /**
     * Runs the Prim's algorithm in a graph (this).
     * Complexity: O((V + E) log V)
     * @param v
     */
    void prim(Vertex* v);

    /**
     * Pre order traversal on the graph, starting from a given vertex. The path is stored in the path vector.
     * Complexity: O(V + E)
     * @param v the starting vertex
     * @param path the path vector
     * @param pathNum the number of vertices in the path
     */
    void preOrderTraversal(Vertex *v, vector<int> &path, int &pathNum);

    /**
     * Clear the graph.
     * Complexity: O(1)
     */
    void clearGraph();

    /**
     * Calls the TSP algorithm in a graph (this) using backtracking.
     * Complexity: O(V!) being V the number of vertices
     * @param path the path vector
     * @return total distance
     */
    double tspBacktracking(vector<int> &path);

    /**
     * Runs the TSP algorithm in a graph (this) using a triangular approximation.
     * Complexity: O(V^2) being V the number of vertices
     * @param path the path vector
     * @return total distance
     */
    double tspTriangularApproximation(vector<int> &path);

    /**
     * Runs the TSP algorithm in a graph (this) using the nearest neighbour heuristic.
     * Complexity: O(V^2) being V the number of vertices
     * @param path the path vector
     * @return total distance
     */
    double tspNearestNeighbour(vector<int> &path);

protected:
    unordered_map<int, Vertex *> vertexSet;    // vertex set

    /**
     * Calls the TSP algorithm in a graph (this) using backtracking.
     * Complexity: O(V!) being V the number of vertices
     * @param path the path vector
     * @param vertex id of the current vertex
     * @param sum sum of the current distance from the visited vertices
     * @param bestSum the best sum of distances in our path found so far
     * @param step number of vertices visited
     * @return best total distance
     */
    double tspBacktracking(vector<int> &path, int vertex, double sum, double bestSum, unsigned step);

    /**
     * Finds the nearest neighbour of a vertex in a graph (this).
     * Complexity: O(V) being V the number of vertices
     * @param v the source vertex
     * @return a Vertex pointer to the nearest neighbour
     */
    Vertex *findNearestNeighbour(Vertex *v);

    /**
     * Calculates the distance between two coordinates.
     * Complexity: O(1)
     * @param c1 the first coordinate
     * @param c2 the second coordinate
     * @return the distance between the two coordinates
     */
    double haversineDistance(Coordinates c1, Coordinates c2);

    /**
     * Calculates the distance between two vertices.
     * Complexity: O(n) being n the number of vertices adjacent to the first vertex
     * @param v1 the first vertex
     * @param v2 the second vertex
     * @return the distance between the two vertices
     */
    double calculateDistance(Vertex *v1, Vertex *v2);
};

#endif /* DA_TP_CLASSES_GRAPH */