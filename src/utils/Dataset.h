#ifndef DA_ROUTINGALGORITHMS_DATASET_H
#define DA_ROUTINGALGORITHMS_DATASET_H

#include "Graph.h"
#include "string"

using namespace std;

struct Coordinates {
    double longitude;
    double latitude;

    bool operator<(const Coordinates& other) const {
        if (latitude < other.latitude)
            return true;
        if (latitude > other.latitude)
            return false;
        return longitude < other.longitude;
    }

    bool operator==(const Coordinates& other) const {
        return latitude == other.latitude && longitude == other.longitude;
    }
};

class Dataset {
private:
    static Dataset *dataset;

    //toy graphs
    Graph<int> shipping;
    Graph<int> stadiums;
    Graph<int> tourism;

    //extra graphs
    Graph<pair<int, Coordinates>> e25;
    Graph<pair<int, Coordinates>> e50;
    Graph<pair<int, Coordinates>> e75;
    Graph<pair<int, Coordinates>> e100;
    Graph<pair<int, Coordinates>> e200;
    Graph<pair<int, Coordinates>> e300;
    Graph<pair<int, Coordinates>> e400;
    Graph<pair<int, Coordinates>> e500;
    Graph<pair<int, Coordinates>> e600;
    Graph<pair<int, Coordinates>> e700;
    Graph<pair<int, Coordinates>> e800;
    Graph<pair<int, Coordinates>> e900;

    //real-world graphs
    Graph<pair<int, Coordinates>> graph1;
    Graph<pair<int, Coordinates>> graph2;
    Graph<pair<int, Coordinates>> graph3;

    Dataset();

    void loadToyGraphs();
    void loadExtraGraphs();
    void loadRealWorldGraphs();

public:
    static Dataset *getInstance();

    Dataset(const Dataset &) = delete;

    void operator=(const Dataset &) = delete;

    //my try to not repeat this code for every graph
    static void setToyGraph(const string& path, Graph<int> &graph);
    static void setExtraGraph(const string& path, Graph<pair<int, Coordinates>> &graph);
    static void setRealWorldGraph(const string& nodesPath, const string& edgesPath, Graph<pair<int, Coordinates>> &graph);

    static int extractNumNodesFromPath(const string& path);

    //getters
    Graph<int> getShipping();
    Graph<int> getStadiums();
    Graph<int> getTourism();

    Graph<pair<int, Coordinates>> getE25();
    Graph<pair<int, Coordinates>> getE50();
    Graph<pair<int, Coordinates>> getE75();
    Graph<pair<int, Coordinates>> getE100();
    Graph<pair<int, Coordinates>> getE200();
    Graph<pair<int, Coordinates>> getE300();
    Graph<pair<int, Coordinates>> getE400();
    Graph<pair<int, Coordinates>> getE500();
    Graph<pair<int, Coordinates>> getE600();
    Graph<pair<int, Coordinates>> getE700();
    Graph<pair<int, Coordinates>> getE800();
    Graph<pair<int, Coordinates>> getE900();

    Graph<pair<int, Coordinates>> getGraph1();
    Graph<pair<int, Coordinates>> getGraph2();
    Graph<pair<int, Coordinates>> getGraph3();
};


#endif //DA_ROUTINGALGORITHMS_DATASET_H
