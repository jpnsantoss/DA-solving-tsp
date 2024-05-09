#include <fstream>
#include <sstream>
#include "Dataset.h"

//toy graphs paths
string SHIPPING_PATH = "../data/Toy-Graphs/shipping.csv";
string STADIUMS_PATH = "../data/Toy-Graphs/stadiums.csv";
string TOURISM_PATH = "../data/Toy-Graphs/tourism.csv";

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
string Nodes_PATH = "../data/Extra_Fully_Connected_Graphs/nodes.csv";

//real world graphs paths
string GRAPH1_EDGESPATH = "../data/Real-world Graphs/graph1/edges.csv";
string GRAPH1_NODESPATH = "../data/Real-world Graphs/graph1/nodes.csv";

string GRAPH2_EDGESPATH = "../data/Real-world Graphs/graph2/edges.csv";
string GRAPH2_NODESPATH = "../data/Real-world Graphs/graph2/nodes.csv";

string GRAPH3_EDGESPATH = "../data/Real-world Graphs/graph3/edges.csv";
string GRAPH3_NODESPATH = "../data/Real-world Graphs/graph3/nodes.csv";


Dataset *Dataset::dataset = nullptr;

Dataset::Dataset() {
    /*cout << "Loading Toy Graphs...";
    loadToyGraphs();
    cout << " Finished Loading Toy Graphs!" << endl;

    cout << "Loading Extra Graphs..." << endl;
    loadExtraGraphs();
    cout << "Finished Loading Extra Graphs!" << endl;
    */
    cout << "Loading Real-World Graphs..." << endl;
    loadRealWorldGraphs();
    cout << "Finished Loading Real-World Graphs!" << endl;
}

Dataset *Dataset::getInstance() {
    if (dataset == nullptr) {
        dataset = new Dataset();
        return dataset;
    } else {
        return dataset;
    }
}

int Dataset::extractNumNodesFromPath(const string& path) {
    // Find the underscore in the path
    size_t underscore = path.find_last_of('_');

    // Find the dot in the path
    size_t dot = path.find('.', underscore);

    // Extract the substring between the underscore and the dot
    string numNodesString = path.substr(underscore + 1, dot - underscore - 1);

    // Convert the extracted substring to an integer
    int numNodes = stoi(numNodesString);

    return numNodes;
}

void Dataset::loadToyGraphs() {
    setToyGraph(SHIPPING_PATH, shipping);
    setToyGraph(STADIUMS_PATH, stadiums);
    setToyGraph(TOURISM_PATH, tourism);
}

void Dataset::loadExtraGraphs() {
    setExtraGraph(E25_PATH, e25);
    setExtraGraph(E50_PATH, e50);
    setExtraGraph(E75_PATH, e75);
    setExtraGraph(E100_PATH, e100);
    setExtraGraph(E200_PATH, e200);
    setExtraGraph(E300_PATH, e300);
    setExtraGraph(E400_PATH, e400);
    setExtraGraph(E500_PATH, e500);
    setExtraGraph(E600_PATH, e600);
    setExtraGraph(E700_PATH, e700);
    setExtraGraph(E800_PATH, e800);
    setExtraGraph(E900_PATH, e900);
}

void Dataset::loadRealWorldGraphs() {
    //setRealWorldGraph(GRAPH1_NODESPATH, GRAPH1_EDGESPATH, graph1);
    setRealWorldGraph(GRAPH2_NODESPATH, GRAPH2_EDGESPATH, graph2);
    //setRealWorldGraph(GRAPH3_NODESPATH, GRAPH3_EDGESPATH, graph3);
}

void Dataset::setToyGraph(const string& path, Graph<int> &graph) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: File " << path << " not opened." << endl;
        return;
    }

    string row, origin, destination, distance;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, origin, ',');
        getline(line, destination, ',');
        getline(line, distance, '\r');

        int value1 = stoi(origin);
        int value2 = stoi(destination);
        double weight = stod(distance);

        auto v1 = graph.findVertex(value1);
        auto v2 = graph.findVertex(value2);

        if(v1 == nullptr) {
            graph.addVertex(value1);
        }
        if(v2 == nullptr) {
            graph.addVertex(value2);
        }

        graph.addEdge(value1, value2, weight);
    }

    file.close();
}

void Dataset::setExtraGraph(const string& path, Graph<pair<int, Coordinates>> &graph) {
    int numNodes = extractNumNodesFromPath(path);

    ifstream nodeFile(Nodes_PATH);
    if (!nodeFile.is_open()) {
        cout << "Error: File " << Nodes_PATH << " not opened." << endl;
        return;
    }

    string row1, id, longitude, latitude;
    getline(nodeFile, row1);

    while (getline(nodeFile, row1) && numNodes > 0) {
        istringstream line(row1);
        getline(line, id, ',');
        getline(line, longitude, ',');
        getline(line, latitude, '\r');

        int nodeId = stoi(id);
        Coordinates cords = {stod(longitude), stod(latitude)};

        graph.addVertex(make_pair(nodeId, cords));

        numNodes--;
    }

    nodeFile.close();

    ifstream edgeFile(path);
    if (!edgeFile.is_open()) {
        cout << "Error: File " << path << " not opened." << endl;
        return;
    }

    string row2, origin, destination, distance;
    getline(edgeFile, row2);

    int currentOrigin = -1;
    Vertex<pair<int, Coordinates>>* currentVertex;

    while (getline(edgeFile, row2)) {
        istringstream line(row2);
        getline(line, origin, ',');
        getline(line, destination, ',');
        getline(line, distance, '\r');

        int node1 = stoi(origin);
        int node2 = stoi(destination);
        double w = stod(distance);

        if (node1 != currentOrigin) {
            currentOrigin = node1;
            for(auto v : graph.getVertexSet()) {
                if(v->getInfo().first == currentOrigin) {
                    currentVertex = v;
                    break;
                }
            }
        }

        Vertex<pair<int, Coordinates>>* v2;
        for(auto v : graph.getVertexSet()) {
            if(v->getInfo().first == node2) {
                v2 = v;
                break;
            }
        }

        graph.addEdge(currentVertex->getInfo(), v2->getInfo() , w);
    }

    edgeFile.close();
}

void Dataset::setRealWorldGraph(const string& nodesPath, const string& edgesPath, Graph<pair<int, Coordinates>> &graph) {
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

        graph.addVertex(make_pair(nodeId, cords));
    }

    nodeFile.close();

    ifstream edgeFile(edgesPath);
    if (!edgeFile.is_open()) {
        cout << "Error: File " << edgesPath << " not opened." << endl;
        return;
    }

    string row2, origin, destination, distance;
    getline(edgeFile, row2);

    int currentOrigin = -1;
    Vertex<pair<int, Coordinates>>* currentVertex;

    while (getline(edgeFile, row2)) {
        istringstream line(row2);
        getline(line, origin, ',');
        getline(line, destination, ',');
        getline(line, distance, '\r');

        int node1 = stoi(origin);
        int node2 = stoi(destination);
        double w = stod(distance);

        if (node1 != currentOrigin) {
            currentOrigin = node1;
            for(auto v : graph.getVertexSet()) {
                if(v->getInfo().first == currentOrigin) {
                    currentVertex = v;
                    break;
                }
            }
        }

        Vertex<pair<int, Coordinates>>* v2;
        for(auto v : graph.getVertexSet()) {
            if(v->getInfo().first == node2) {
                v2 = v;
                break;
            }
        }

        graph.addEdge(currentVertex->getInfo(), v2->getInfo() , w);
    }

    edgeFile.close();
}

Graph<int> Dataset::getShipping() {
    return this->shipping;
}

Graph<int> Dataset::getStadiums() {
    return this->stadiums;
}

Graph<int> Dataset::getTourism() {
    return this->tourism;
}

Graph<pair<int, Coordinates>> Dataset::getE25() {
    return this->e25;
}

Graph<pair<int, Coordinates>> Dataset::getE50() {
    return this->e50;
}

Graph<pair<int, Coordinates>> Dataset::getE75() {
    return this->e75;
}

Graph<pair<int, Coordinates>> Dataset::getE100() {
    return this->e100;
}

Graph<pair<int, Coordinates>> Dataset::getE200() {
    return this->e200;
}

Graph<pair<int, Coordinates>> Dataset::getE300() {
    return this->e300;
}

Graph<pair<int, Coordinates>> Dataset::getE400() {
    return this->e400;
}

Graph<pair<int, Coordinates>> Dataset::getE500() {
    return this->e500;
}

Graph<pair<int, Coordinates>> Dataset::getE600() {
    return this->e600;
}

Graph<pair<int, Coordinates>> Dataset::getE700() {
    return this->e700;
}

Graph<pair<int, Coordinates>> Dataset::getE800() {
    return this->e800;
}

Graph<pair<int, Coordinates>> Dataset::getE900() {
    return this->e900;
}

Graph<pair<int, Coordinates>> Dataset::getGraph1() {
    return this->graph1;
}

Graph<pair<int, Coordinates>> Dataset::getGraph2() {
    return this->graph2;
}

Graph<pair<int, Coordinates>> Dataset::getGraph3() {
    return this->graph3;
}
