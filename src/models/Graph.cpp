#include "Graph.h"
#include <cmath>
#include "unordered_set"

unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex *Graph::findVertex(const int &id) const {
    auto v = vertexSet.find(id);

    if(v == vertexSet.end()) return nullptr;

    return v->second;
}

Edge *Graph::findEdge(const int &id1, const int &id2) const {
    Vertex *v1 = findVertex(id1);
    Vertex *v2 = findVertex(id2);

    if(v1 == nullptr || v2 == nullptr) return nullptr;

    for(auto e: v1->getAdj()) {
        if(e->getDest() == v2) return e;
    }

    return nullptr;

}

bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getId()) != nullptr)
        return false;
    vertexSet.insert({v->getId(), v});
    return true;
}

bool Graph::addBidirectionalEdge(Vertex* v1, Vertex* v2, double distance) const {
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, distance);
    auto e2 = v2->addEdge(v1, distance);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::prim(Vertex* v) {
    if (vertexSet.empty()) return;

    MutablePriorityQueue<Vertex> q;

    for(auto vert : vertexSet) {
        vert.second->setDist(INF);
        vert.second->setPath(nullptr);
        vert.second->setVisited(false);
        q.insert(vert.second);
        for(auto e: vert.second->getAdj()) {
            e->setSelected(false);
            e->getReverse()->setSelected(false);
        }
    }

    v->setDist(0);
    q.decreaseKey(v);

    vector<Vertex*> preOrderTraversal;

    while(!q.empty() ) {
        auto aux = q.extractMin();
        aux->setVisited(true);

        for(auto &edge : aux->getAdj()) {
            Vertex* dest = edge->getDest();

            if (!dest->isVisited() && edge->getDistance() < dest->getDist()){
                Edge *prevPath = dest->getPath();
                if(prevPath != nullptr) {
                    prevPath->setSelected(false);
                    prevPath->getReverse()->setSelected(false);
                }
                dest->setDist(edge->getDistance());
                dest->setPath(edge);
                q.decreaseKey(dest);
                edge->setSelected(true);
                edge->getReverse()->setSelected(true);
            }
        }
    }
}

void Graph::preOrderTraversal(Vertex *v, vector<int> &path, int &pathNum) {
    v->setVisited(true);

    path[pathNum++] = v->getId();

    for (auto& edge : v->getAdj()) {
        Vertex* dest = edge->getDest();
        if (!dest->isVisited() && edge == dest->getPath()) {
            preOrderTraversal(dest, path, pathNum);
        }
    }
}

void Graph::clearGraph() {
    vertexSet.clear();
}

Graph::~Graph() = default;

//-------------------------------Backtracking--------------------------------------------------//
double Graph::tspBacktracking(vector<int> &path) {
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    findVertex(0)->setVisited(true);

    double bestDist = tspBacktracking(path, 0, 0, INF, 1);

    path.push_back(0);
    return bestDist;
}

double Graph::tspBacktracking(vector<int> &path, int vertexId, double sum, double bestSum, unsigned step) {
    double currentSum = 0;
    Vertex *vertex = findVertex(vertexId);

    if (step == vertexSet.size()) {
        for(auto e: vertex->getAdj()) {
            if(e->getDest()->getId() == 0) {
                return sum + e->getDistance();
            }
            return bestSum;
        }
    }

    for(auto v: vertexSet) {
        Vertex *dest = v.second;

        if(dest->isVisited()) continue;

        for (Edge *e: vertex->getAdj()) {
            if (e->getDest() == dest) {
               double dist = e->getDistance();

               if(sum + dist < bestSum) {
                   dest->setVisited(true);
                   currentSum = tspBacktracking(path, dest->getId(), sum + dist, bestSum, step + 1);
                   if(currentSum < bestSum) {
                       bestSum = currentSum;
                       path[step] = v.first;
                   }
                   dest->setVisited(false);
               }
            }
        }
    }
    return bestSum;
}

//-------------------------------Triangular Approximation--------------------------------------------------//
double Graph::tspTriangularApproximation(vector<int> &path) {
    auto origin = vertexSet.find(0);
    prim(origin->second);
    cout << "Prim done" << endl;
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    int pathNum = 0;
    preOrderTraversal(origin->second, path, pathNum);

    double cost = 0;
    for(int i = 0; i < path.size() - 1; i++) {
        cost += calculateDistance(findVertex(path[i]), findVertex(path[i + 1]));
    }

    cost += calculateDistance(findVertex(path[path.back()]), findVertex(0));

    return cost;
}

//-------------------------------NearestNodes--------------------------------------------------//
Vertex* Graph::findNearestNeighbour(Vertex *source) {
    double min = INF;
    Vertex *nearest = nullptr;

    for(auto v: vertexSet) {
        if(v.second->getId() == source->getId() || v.second->isVisited()) continue;
        double d = calculateDistance(source, v.second);
        if(d < min) {
            min = d;
            nearest = v.second;
        }
    }

    return nearest;
}

double Graph::tspNearestNeighbour( vector<int> &path) {
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    Vertex *v = findVertex(0);
    v->setVisited(true);
    path.push_back(0);

    double sum = 0;
    for(unsigned i = 1; i < vertexSet.size(); i++) {
        Vertex *nearest = findNearestNeighbour(v);
        nearest->setVisited(true);
        path.push_back(nearest->getId());
        sum += calculateDistance(v, nearest);
        v = nearest;
    }

    sum += calculateDistance(v, findVertex(0));
    path.push_back(0);

    return sum;
}



//-------------------------------Helpers--------------------------------------------------//
double Graph::haversineDistance(Coordinates c1, Coordinates c2)
{
    double dLat = (c2.latitude - c1.latitude) * M_PI / 180.0;
    double dLon = (c2.longitude - c1.longitude) * M_PI / 180.0;

    c1.latitude = c1.latitude * M_PI / 180.0;
    c2.latitude = c2.latitude * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) * cos(c1.latitude) * cos(c2.latitude);
    double rad = 6371000;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

double Graph::calculateDistance(Vertex* v1, Vertex* v2) {
    for(auto e: v1->getAdj()) {
        if(e->getDest() == v2) {
            return e->getDistance();
        }
    }
    return haversineDistance(v1->getCords(), v2->getCords());
}



