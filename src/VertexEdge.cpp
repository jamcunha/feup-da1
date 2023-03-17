#include "VertexEdge.h"

/*===== Vertex =====*/

Vertex::Vertex(const Station& station): _station(station) {}

const Station& Vertex::getStation() const {
    return this->_station;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->_adj;
}

bool Vertex::isVisited() const {
    return this->_visited;
}

bool Vertex::isProcessing() const {
    return this->_processing;
}

unsigned int Vertex::getIndegree() const {
    return this->_indegree;
}

Edge* Vertex::getPath() const {
    return this->_path;
}

std::vector<Edge *> Vertex::getIncomming() const {
    return this->_incomming;
}

void Vertex::setStation(const Station& station) {
    this->_station = station;
}

void Vertex::setVisited(bool visited) {
    this->_visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->_processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->_indegree = indegree;
}

void Vertex::setPath(Edge* path) {
    this->_path = path;
}

Edge* Vertex::addEdge(Vertex* dest, double weight, const std::string& service) {
    auto newEdge = new Edge(this, dest, weight, service);
    _adj.push_back(newEdge);
    dest->_incomming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(const Station& destStation) {
    bool edgeRemoved = false;
    for (auto it = _adj.begin(); it != _adj.end();) {
        Edge* edge = *it;
        Vertex* dest = edge->getDest();
        if (dest->getStation() == destStation) {
            it = _adj.erase(it);

            for (auto it2 = dest->_incomming.begin(); it2 != dest->_incomming.end();) {
                if ((*it2)->getOrigin()->getStation() == _station) {
                    it2 = dest->_incomming.erase(it2);
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

Edge::Edge(Vertex* origin, Vertex* dest, double weight, const std::string& service)
    : _origin(origin), _dest(dest), _weight(weight), _service(service) {}

Vertex* Edge::getDest() const {
    return this->_dest;
}

double Edge::getWeight() const {
    return this->_weight;
}

Vertex* Edge::getOrigin() const {
    return this->_origin;
}

Edge* Edge::getReverse() const {
    return this->_reverse;
}

double Edge::getFlow() const {
    return this->_flow;
}

const std::string& Edge::getService() const {
    return this->_service;
}

void Edge::setReverse(Edge* reverse) {
    this->_reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->_flow = flow;
}
