//
// Created by jpnsantos on 19/05/24.
//

#include "TSPSimulatedAnnealing.h"
#include <algorithm>
#include <ctime>
#include <cmath>

TSPSimulatedAnnealing::TSPSimulatedAnnealing(Graph &graph, double temperature, double coolingRate) {
    this->graph = graph;
    this->temperature = temperature;
    this->coolingRate = coolingRate;
}

vector<int> TSPSimulatedAnnealing::tspOptimizationAlgorithm(double &bestDist, int startingVertexId) {
    double averageCostIncrease = 0.0;
    int step = 0;
    vector<int> currentTour = findInitialHamiltonianCycle(startingVertexId);

    if (currentTour.empty()) return currentTour;

    vector<int> bestTour = currentTour;

    double bestTourLength = calculatePathLength(bestTour);

    srand(time(NULL));


    for (int i = 0; i < maxIterations; i++) {
        vector<int> newTour = generateNeighbor(currentTour);
        double currentTourLength = calculatePathLength(currentTour);
        double newTourLength = calculatePathLength(newTour);

        if (acceptanceProbability(currentTourLength, newTourLength, temperature) > ((double) rand() / RAND_MAX)) {
            currentTour = newTour;
            if (newTourLength < bestTourLength) {
                bestTour = newTour;
                bestTourLength = newTourLength;
            }
        }
        temperature *= coolingRate;
        averageCostIncrease += newTourLength - currentTourLength;

        step = i;
    }
    cout << endl << "Average cost increase: " << averageCostIncrease / step << endl;
    bestDist = bestTourLength;

    return bestTour;
}

vector<int> TSPSimulatedAnnealing::findInitialHamiltonianCycle(int startingVertexId) {
    vector<int> path;
    vector<bool> visited(graph.getVertexSet().size(), false);

    if (findHamiltonianPath(startingVertexId, path, visited, startingVertexId)) {
        return path;
    }

    cout << "No Hamiltonian cycle found" << endl;
    path.clear();
    fill(visited.begin(), visited.end(), false);

    return vector<int>();
}

double TSPSimulatedAnnealing::calculatePathLength(const vector<int> &path) {
    double totalDistance = 0.0;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalDistance += graph.findEdge(path[i], path[i + 1])->getDistance();
    }

    return totalDistance;
}

bool TSPSimulatedAnnealing::findHamiltonianPath(int currentVertex, vector<int> &path, vector<bool> &visited, int startingVertexId) {
    path.push_back(currentVertex);
    visited[currentVertex] = true;

    if (path.size() == graph.getVertexSet().size()) {
        if (graph.findEdge(currentVertex, startingVertexId) != nullptr) {
            path.push_back(startingVertexId);
            return true;
        }
        path.pop_back();
        visited[currentVertex] = false;
        return false;
    }

    for (auto edge: graph.findVertex(currentVertex)->getAdj()) {
        if (!visited[edge->getDest()->getId()]) {
            if (findHamiltonianPath(edge->getDest()->getId(), path, visited, startingVertexId)) {
                return true;
            }
        double TSPSimulatedAnnealing::calculatePathLength(const vector<int> &path) {
    double totalDistance = 0.0;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalDistance += graph.findEdge(path[i], path[i + 1])->getDistance();
    }

    return totalDistance;
}
}
    }

    path.pop_back();
    visited[currentVertex] = false;
    return false;
}

vector<int> TSPSimulatedAnnealing::generateNeighbor(const vector<int> &currentTour) {
    vector<int> newTour = currentTour;

    for (int i = 1; i < newTour.size() - 1; i++) {
        for (int j = i + 1; j < newTour.size(); j++) {
            int a = newTour[i - 1], b = newTour[i];
            int c = newTour[j], d = (j + 1 == newTour.size()) ? newTour[0] : newTour[j + 1];

            Edge *edgeAC = graph.findEdge(a, c);
            Edge *edgeBD = graph.findEdge(b, d);
            Edge *edgeAB = graph.findEdge(a, b);
            Edge *edgeCD = graph.findEdge(c, d);

            if (edgeAC && edgeBD && edgeAB && edgeCD) {
                double oldLength = edgeAB->getDistance() + edgeCD->getDistance();
                double newLength = edgeAC->getDistance() + edgeBD->getDistance();

                if (newLength < oldLength) {
                    vector<int> tempTour = currentTour;
                    reverse(tempTour.begin() + i, tempTour.begin() + j + 1);

                    // Corrected edge existence check
                    if (j + 1 < newTour.size() || graph.findEdge(tempTour.back(), tempTour.front()) != nullptr) {
                        return tempTour;
                    }
                }
            }
        }
    }
    return newTour;
}

double
TSPSimulatedAnnealing::acceptanceProbability(double currentTourLength, double newTourLength, double temperature) {
    if (newTourLength < currentTourLength) {
        return 1.0;
    }
    return exp((currentTourLength - newTourLength) / temperature);
}