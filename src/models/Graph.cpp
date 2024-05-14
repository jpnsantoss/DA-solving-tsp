#include "Graph.h"
#include <map>

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