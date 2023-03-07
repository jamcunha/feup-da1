#include "VertexEdge.h"

/*===== Vertex =====*/

Vertex::Vertex(int id): id(id) {}

int Vertex::getId() const {
    return this->id;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

Edge* Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncomming() const {
    return this->incomming;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setPath(Edge* path) {
    this->path = path;
}

Edge* Vertex::addEdge(Vertex* dest, double weight) {
    auto newEdge = new Edge(this, dest, weight);
    adj.push_back(newEdge);
    dest->incomming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destId) {
    bool edgeRemoved = false;
    for (auto it = adj.begin(); it != adj.end();) {
        Edge* edge = *it;
        Vertex* dest = edge->getDest();
        if (dest->getId() == destId) {
            it = adj.erase(it);

            for (auto it2 = dest->incomming.begin(); it2 != dest->incomming.end();) {
                if ((*it2)->getOrigin()->getId() == id) {
                    it2 = dest->incomming.erase(it2);
                } else {
                    it2++;
                }
            }

            delete edge;
            edgeRemoved = true;
        } else {
            it++;
        }
    }

    return edgeRemoved;
}

/*===== Edge =====*/

Edge::Edge(Vertex* origin, Vertex* dest, double weight): origin(origin), dest(dest), weight(weight) {}

Vertex* Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex* Edge::getOrigin() const {
    return this->origin;
}

double Edge::getFlow() const {
    return this->flow;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}
