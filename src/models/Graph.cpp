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