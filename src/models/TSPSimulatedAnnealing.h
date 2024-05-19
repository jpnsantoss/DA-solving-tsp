//
// Created by jpnsantos on 19/05/24.
//

#ifndef DA_ROUTINGALGORITHMS_TSPSIMULATEDANNEALING_H
#define DA_ROUTINGALGORITHMS_TSPSIMULATEDANNEALING_H


#include "Graph.h"

class TSPSimulatedAnnealing {
private:
    Graph graph;
    double temperature;
    double coolingRate;
    int maxIterations = 1000;

public:
    /**
     * Constructor of class TSPSimulatedAnnealing
     * @param graph
     * @param temperature
     * @param coolingRate
     */
    TSPSimulatedAnnealing(Graph &graph, double temperature, double coolingRate);

    /**
     * Runs the Annealing Algorithm
     * Complexity: O(V²)
     * @param bestDist
     * @param startingVertexId
     * @return vector<int> the best tour found
     */
    vector<int> tspOptimizationAlgorithm(double &bestDist, int startingVertexId);

    /**
     * Complexity: O(V!)
     * @param id
     * @return vector<int> hamiltonian cycle
     */
    vector<int> findInitialHamiltonianCycle(int id);

    /**
     * Calculates the path cost
     * Complexity: O(V)
     * @param path
     * @return path length
     */
    double calculatePathLength(const vector<int> &path);

    /**
     * Runs a algorithm to find an Hamiltonian Cycle in the graph
     * Complexity: O(V!)
     * @param currentVertex
     * @param path
     * @param visited
     * @param startingVertexId
     * @return
     */
    bool findHamiltonianPath(int currentVertex, vector<int> &path, vector<bool> &visited, int startingVertexId);

    /**
     * Tries to switch 2 vertexes
     * Complexity: O(V²)
     * @param currentTour
     * @return vector<int> returns a new tour
     */
    vector<int> generateNeighbor(const vector<int> &currentTour);

    /**
      * Complexity: O(1)
     * @param currentTourLength
     * @param newTourLength
     * @param temperature
     * @return
     */
    double acceptanceProbability(double currentTourLength, double newTourLength, double temperature);
};


#endif //DA_ROUTINGALGORITHMS_TSPSIMULATEDANNEALING_H
