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
    static Dataset *getInstance();

    Dataset(const Dataset &) = delete;

    void operator=(const Dataset &) = delete;

    void loadGraph(const string& path);
    void loadRealWorldGraph(const string& nodesPath, const string& edgesPath);

    //getters
    Graph &getGraph();
};


#endif //DA_ROUTINGALGORITHMS_DATASET_H
