#include "Graph.h"
#include <map>
#include <cmath>
#include <set>
#include <stack>

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

pair<vector<int>, double> Graph::TriangularApproximation() {
    set<Edge*> mst;
    double cost = 0;

    for (auto vertex : vertexSet) {
        vertex.second->setDist(std::numeric_limits<double>::max());
        vertex.second->setPath(nullptr);
        vertex.second->setVisited(false);
    }

    Vertex* root = vertexSet.begin()->second;
    root->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(root);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if (e->getDistance() < oldDist) {
                    w->setDist(e->getDistance());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
        if (v->getPath() != nullptr) {
            mst.insert(v->getPath());
            v->getPath()->getDest()->incrementmstdegree();
            v->getPath()->getOrig()->incrementmstdegree();
        }
    }

    vector<int> preorder;
    int lastId;
    stack<Vertex*> stack;
    stack.push(findVertex(0));
    bool child;
    while (!stack.empty()) {
        Vertex* current = stack.top();
        stack.pop();
        preorder.push_back(current->getId());
        lastId = current->getId();
        child = true;
        for (auto e : current->getAdj()) {
            Vertex* nextVertex = e->getDest();
            if (nextVertex->getId() != 0 && nextVertex->getId() != lastId) {
                cost += e->getDistance();
                stack.push(nextVertex);
                child = false;
            }
        }
        if (child && !stack.empty()) {
            cost += stack.top()->getAdj()[0]->getDistance();
        }
    }

    preorder.push_back(0);

    for (auto vertexPair : vertexSet) {
        if (vertexPair.second->getId() == lastId) {
            cost += vertexPair.second->getAdj()[0]->getDistance();
        }
    }

    return make_pair(preorder, cost);
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

    cout << "Nearest: " << nearest->getId() << endl;

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
