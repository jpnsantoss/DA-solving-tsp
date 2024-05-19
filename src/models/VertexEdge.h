#ifndef DA_ROUTINGALGORITHMS_VERTEXEDGE_H
#define DA_ROUTINGALGORITHMS_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <optional>
#include "../utils/DataStructures/MutablePriorityQueue.h"


using namespace std;

#define INF std::numeric_limits<double>::max()

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

//-----------------------Vertex-----------------------------------

// Forward declaration of Edge
class Edge;

class Vertex {
private:
    int id; // unique identifier
    Coordinates cords;

    vector<Edge *> adj;  // outgoing edges
    vector<Edge *> incoming; // incoming edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    Edge *path = nullptr;

    double dist = 0;
    int queueIndex = 0;

    void deleteEdge(Edge *edge) const;

     int mstdegree = 0;

public:
    // Constructor for a VertexEdge
    Vertex(int id);

    Vertex(int id, Coordinates cords);

    // Getters
    int getId() const;

    Coordinates getCords() const;

    bool operator<(Vertex &vertex) const; // required by MutablePriorityQueue

    vector<Edge *> getAdj() const;

    bool isVisited() const;

    Edge *getPath() const;

    void setDist(double dist);

    vector<Edge *> getIncoming() const;

    void setVisited(bool visited);

    void setPath(Edge *path);

    double getDist() const;

    Edge *addEdge(Vertex *dest, double w);

    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;

    void incrementmstdegree();
};

//-----------------------Edge-----------------------------------
class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double distance);

    Vertex *getDest() const;

    double getDistance() const;

    bool isSelected() const;

    Vertex *getOrig() const;

    Edge *getReverse() const;

    void setSelected(bool selected);

    void setReverse(Edge *reverse);
protected:
    Vertex *orig;
    Edge *reverse = nullptr;

    Vertex *dest;
    double distance;

    bool selected = false;

    Edge *findEdge(Vertex *orig, Vertex *dest);
};


#endif //DA_ROUTINGALGORITHMS_VERTEXEDGE_H