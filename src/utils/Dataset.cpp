#include <fstream>
#include <sstream>
#include "Dataset.h"

//toy graphs paths
string SHIPPING_PATH = "../data/Toy_Graphs/shipping.csv";
string STADIUMS_PATH = "../data/Toy_Graphs/stadiums.csv";
string TOURISM_PATH = "../data/Toy_Graphs/tourism.csv";

//extra graphs paths
string E25_PATH = "../data/Extra_Fully_Connected_Graphs/edges_25.csv";
string E50_PATH = "../data/Extra_Fully_Connected_Graphs/edges_50.csv";
string E75_PATH = "../data/Extra_Fully_Connected_Graphs/edges_75.csv";
string E100_PATH = "../data/Extra_Fully_Connected_Graphs/edges_100.csv";
string E200_PATH = "../data/Extra_Fully_Connected_Graphs/edges_200.csv";
string E300_PATH = "../data/Extra_Fully_Connected_Graphs/edges_300.csv";
string E400_PATH = "../data/Extra_Fully_Connected_Graphs/edges_400.csv";
string E500_PATH = "../data/Extra_Fully_Connected_Graphs/edges_500.csv";
string E600_PATH = "../data/Extra_Fully_Connected_Graphs/edges_600.csv";
string E700_PATH = "../data/Extra_Fully_Connected_Graphs/edges_700.csv";
string E800_PATH = "../data/Extra_Fully_Connected_Graphs/edges_800.csv";
string E900_PATH = "../data/Extra_Fully_Connected_Graphs/edges_900.csv";

//real world graphs paths
string GRAPH1_EDGESPATH = "../data/Real_World_Graphs/graph1/edges.csv";
string GRAPH1_NODESPATH = "../data/Real_World_Graphs/graph1/nodes.csv";

string GRAPH2_EDGESPATH = "../data/Real_World_Graphs/graph2/edges.csv";
string GRAPH2_NODESPATH = "../data/Real_World_Graphs/graph2/nodes.csv";

string GRAPH3_EDGESPATH = "../data/Real_World_Graphs/graph3/edges.csv";
string GRAPH3_NODESPATH = "../data/Real_World_Graphs/graph3/nodes.csv";


Dataset *Dataset::dataset = nullptr;

Dataset::Dataset() = default;

Dataset *Dataset::getInstance() {
    if (dataset == nullptr) {
        dataset = new Dataset();
        return dataset;
    } else {
        return dataset;
    }
}

void Dataset::loadGraph(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: File " << path << " not opened." << endl;
        return;
    }

    string row, origin, destination, dist;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, origin, ',');
        getline(line, destination, ',');
        getline(line, dist, '\r');

        int value1 = stoi(origin);
        int value2 = stoi(destination);
        double distance = stod(dist);

        auto v1 = graph.findVertex(value1);
        auto v2 = graph.findVertex(value2);

        if(v1 == nullptr) {
            v1 = new Vertex(value1);
            graph.addVertex(v1);
        }
        if(v2 == nullptr) {
            v2 = new Vertex(value2);
            graph.addVertex(v2);
        }

        graph.addBidirectionalEdge(v1, v2, distance);
    }

    file.close();
}

void Dataset::loadRealWorldGraph(const string& nodesPath, const string& edgesPath) {
    ifstream nodeFile(nodesPath);
    if (!nodeFile.is_open()) {
        cout << "Error: File " << nodesPath << " not opened." << endl;
        return;
    }

    string row1, id, longitude, latitude;
    getline(nodeFile, row1);

    while (getline(nodeFile, row1)) {
        istringstream line(row1);
        getline(line, id, ',');
        getline(line, longitude, ',');
        getline(line, latitude, '\r');

        int nodeId = stoi(id);
        Coordinates cords = {stod(longitude), stod(latitude)};

        auto v = new Vertex(nodeId, cords);
        graph.addVertex(v);
    }

    nodeFile.close();

    ifstream edgeFile(edgesPath);
    if (!edgeFile.is_open()) {
        cout << "Error: File " << edgesPath << " not opened." << endl;
        return;
    }

    string row2, origin, destination, dist;
    getline(edgeFile, row2);

    while (getline(edgeFile, row2)) {
        istringstream line(row2);
        getline(line, origin, ',');
        getline(line, destination, ',');
        getline(line, dist, '\r');

        int node1 = stoi(origin);
        int node2 = stoi(destination);
        double distance = stod(dist);

        auto v1 = graph.findVertex(node1);
        auto v2 = graph.findVertex(node2);

        graph.addEdge(v1, v2, distance);
    }

    edgeFile.close();
}

Graph &Dataset::getGraph() {
    return this->graph;
}