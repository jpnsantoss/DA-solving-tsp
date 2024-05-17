#include "VertexEdge.h"

//-----------------------Vertex-----------------------------------
Vertex::Vertex(int id) {
    this->id = id;
}

Vertex::Vertex(int id, Coordinates cords) {
    this->id = id;
    this->cords = cords;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge *Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}


/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        } else {
            it++;
        }
    }
    delete edge;
}

// Getters
int Vertex::getId() const {
    return this->id;
}

Coordinates Vertex::getCords() const {
    return this->cords;
}

void Vertex::incrementmstdegree() {
    mstdegree++;
}

//-----------------------Edge-----------------------------------

Edge::Edge(Vertex *orig, Vertex *dest, double distance) {
    this->orig = orig;
    this->dest = dest;
    this->distance = distance;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

double Edge::getDistance() const {
    return this->distance;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

