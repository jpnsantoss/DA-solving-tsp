#ifndef DA_ROUTINGALGORITHMS_DATASET_H
#define DA_ROUTINGALGORITHMS_DATASET_H

#include "../models/Graph.h"
#include "string"

using namespace std;

class Dataset {
private:
    static Dataset *dataset;

    Graph graph;

    Dataset();

public:
    /**
     * Get the instance of the Dataset class
     * Complexity: O(1)
     * @return the instance of the Dataset class
     */
    static Dataset *getInstance();

    /**
     * Delete copy constructor (singleton)
     * Complexity: O(1)
     */
    Dataset(const Dataset &) = delete;

    /**
     * Delete assignment operator (singleton)
     * Complexity: O(1)
     */
    void operator=(const Dataset &) = delete;

    /**
     * Load a graph from a file
     * Complexity: O(E)
     * @param path the path of the file
     */
    void loadGraph(const string& path);

    /**
     * Load a real world graph from two files
     * Complexity: O(V + E)
     * @param nodesPath the path of the nodes file
     * @param edgesPath the path of the edges file
     */
    void loadRealWorldGraph(const string& nodesPath, const string& edgesPath);

    Graph &getGraph();
};


#endif //DA_ROUTINGALGORITHMS_DATASET_H
