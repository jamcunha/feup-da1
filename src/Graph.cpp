#include "Graph.h"

#include <limits>
#include <queue>

Vertex* Graph::findVertex(const std::string& stationName) const {
    for (auto v: vertexSet) {
        if (v->getStation().getName() == stationName) {
            return v;
        }
    }

    return nullptr;
}

bool Graph::addVertex(const Station& station) {
    if (findVertex(station.getName()) != nullptr) {
        return false;
    }

    vertexSet.push_back(new Vertex(station));
    return true;
}

bool Graph::removeVertex(const Station& station) {
    Vertex* v1 = findVertex(station.getName());
    if (v1 == nullptr) {
        return false;
    }
    for (auto e : v1->getAdj()){
        Vertex* v2 = findVertex(e->getDest()->getStation().getName());
        v2->removeEdge(v1->getStation());
    }
    for (auto v = vertexSet.begin(); v!=vertexSet.end(); v++){
        if ((*v)->getStation()==station){
            vertexSet.erase(v);
            break;
        }
    }
    delete v1;
}

bool Graph::addEdge(const std::string& source, const std::string& dest, int weight, const std::string& service) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight, service);
    return true;
}

bool Graph::addBidirectionalEdge(const std::string& source, const std::string& dest, int weight, const std::string& service) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    auto e1 = v1->addEdge(v2, weight, service);
    auto e2 = v2->addEdge(v1, weight, service);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

int Graph::edmondsKarp(const std::string& source, const std::string& dest) {
    auto s = findVertex(source);
    auto t = findVertex(dest);

    // Check if source and destination are valid
    if (s == nullptr || t == nullptr || s == t) {
        return -1;
    }

    // Reset the flow in the edges
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    int max_flow = 0;

    while (findAugmentingPath(s, t)) {
        int pathFlow = std::numeric_limits<int>::max();

        // Find the minimum flow in the path
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                pathFlow = std::min(pathFlow, e->getWeight() - e->getFlow());
                v = e->getOrigin();
            } else {
                pathFlow = std::min(pathFlow, e->getFlow());
                v = e->getDest();
            }
        }

        // Update the flow in the path
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                e->setFlow(e->getFlow() + pathFlow);
                v = e->getOrigin();
            } else {
                e->setFlow(e->getFlow() - pathFlow);
                v = e->getDest();
            }
        }

        max_flow += pathFlow;
    }

    return (max_flow ? max_flow : -1);
}

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

/* Utils */

bool Graph::findAugmentingPath(Vertex *source, Vertex *dest) {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }

    source->setVisited(true);
    std::queue<Vertex *> q;
    q.push(source);

    while (!q.empty() && !dest->isVisited()) {
        auto v = q.front(); q.pop();

        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getWeight() - e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e: v->getIncomming()) {
            auto w = e->getOrigin();
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return dest->isVisited();
}

