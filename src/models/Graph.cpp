#include "Graph.h"
#include <map>
#include <cmath>

unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex *Graph::findVertex(const int &id) const {
    auto v = vertexSet.find(id);

    if(v == vertexSet.end()) return nullptr;

    return v->second;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getId()) != nullptr)
        return false;
    vertexSet.insert({v->getId(), v});
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(Vertex* v1, Vertex* v2, double distance) const {
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, distance);

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

double Graph::tspBacktracking(vector<int> &path, int vertexId, double sum, double bestSum, uint step) {
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
//-------------------------------NearestNodes--------------------------------------------------//
Vertex* Graph::findNearestNeighbour(Vertex *v) {
    double minDistance = numeric_limits<double>::max();
    Vertex *res;

    auto latitude1 = v->getCords().latitude;
    auto longitude1 = v->getCords().longitude;

    for(auto vert : vertexSet) {
        if(vert.second->isVisited()) continue;
        if(v->getId() == vert.first) continue;

        double distance = calculate_distance(latitude1, vert.second->getCords().latitude, longitude1, vert.second->getCords().longitude);
        if(distance < minDistance) {
            minDistance = distance;
            res = vert.second;
        }
    }

    return res;
}

double Graph::tspNearestNeighbour( vector<int> &path) {
    for(auto vert : vertexSet) {
        vert.second->setVisited(false);
    }

    int visitedVertexes = 0;
    double totalDistance = 0;

    auto origin = findVertex(0);
    auto current = origin;
    Vertex* next;

    current->setVisited(true);

    path.push_back(current->getId());
    visitedVertexes++;

    while(visitedVertexes < vertexSet.size()) {
        double minDistance = numeric_limits<double>::max();

        for (auto edge : current->getAdj()) { //if it's not a real world graph
            if (!edge->getDest()->isVisited() && edge->getDistance() < minDistance) {
                minDistance = edge->getDistance();
                next = edge->getDest();
            }
        }

        if (current == next) { //since they are not fully connected
            next = findNearestNeighbour(current);
            minDistance = calculate_distance(current->getCords().latitude, next->getCords().latitude, current->getCords().longitude, next->getCords().longitude);
        }

        next->setVisited(true);
        path.push_back(next->getId());

        current = next;

        totalDistance += minDistance;
        visitedVertexes++;
    }

    //in the case it's not fully connected and a connection to origin doesn't exist
    for(auto edge : current->getAdj()) {
        if(edge->getDest()->getId() == 0) {
            totalDistance += edge->getDistance();
            break;
        }

        totalDistance += calculate_distance(current->getCords().latitude, origin->getCords().latitude, current->getCords().longitude, origin->getCords().longitude);
    }

    path.push_back(0);

    return totalDistance;
}

//-------------------------------Helpers--------------------------------------------------//
double Graph::convert(const double angle) {
    return angle * (M_PI/180);
}

double Graph::calculate_distance(const double latitude1, const double latitude2, const double longitude1, const double longitude2) {
    const double earths_radius = 6371;

    const auto lat_delta = convert(latitude2 - latitude1);
    const auto lon_delta = convert(longitude2 - longitude1);

    const auto converted_lat1 = convert(latitude1);
    const auto converted_lat2 = convert(latitude2);

    const auto a =
            pow(sin(lat_delta / 2), 2) + cos(converted_lat1) * cos(converted_lat2) * pow(sin(lon_delta / 2), 2);

    const auto c = 2 * atan2(sqrt(a), sqrt(1 - a));
    const auto d = earths_radius * c;

    return d;
}
