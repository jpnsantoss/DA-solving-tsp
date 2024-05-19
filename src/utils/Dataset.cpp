#include <fstream>
#include <sstream>
#include "Dataset.h"

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

        graph.addBidirectionalEdge(v1, v2, distance);
    }

    edgeFile.close();
}

Graph &Dataset::getGraph() {
    return this->graph;
}