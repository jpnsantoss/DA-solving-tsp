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
    int maxIterations = 100;
public:
    TSPSimulatedAnnealing(Graph &graph, double temperature, double coolingRate);

    vector<int> solve(double &bestDist, int startingVertexId);

    vector<int> findInitialHamiltonianCycle(int id);

    double calculatePathLength(const vector<int> &path);

    bool findHamiltonianPath(int currentVertex, vector<int> &path, vector<bool> &visited, int startingVertexId);

    vector<int> generateNeighbor(const vector<int> &currentTour);

    double acceptanceProbability(double currentTourLength, double newTourLength, double temperature);
};


#endif //DA_ROUTINGALGORITHMS_TSPSIMULATEDANNEALING_H
