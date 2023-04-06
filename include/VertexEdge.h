#ifndef FEUP_DA1_VERTEXEDGE_H
#define FEUP_DA1_VERTEXEDGE_H

#include "Station.h"

#include <vector>

class Edge;

/**
 * @brief Represents a station in the railway network 
 */
class Vertex {
private:
    /**
     * @brief Vertex station
     */
    Station _station;

    /**
     * @brief Adjacency list of edges
     */
    std::vector<Edge *> _adj;

    /**
     * @brief If vertex was visited
     */
    bool _visited = false;
    
    /**
     * @brief If vertex is processing (used for DAGs)
     */
    bool _processing = false;
    
    /**
     * @brief Vertex indegree (used for topsort)
     */
    unsigned int _indegree;

    /**
     * @brief Path traveled until this vertex
     */
    Edge* _path = nullptr;

    /**
     * @brief Incomming edges to the vertex
     */
    std::vector<Edge *> _incomming;

    /**
     * @brief Distance to the source
     */
     int _distance = 0;

public:
    Vertex(const Station& station);

    /**
     * @brief Get the vertex station
     * 
     * @return Station station
     */
    const Station& getStation() const;

    /**
     * @brief Get the adjacency list of edges
     * 
     * @return std::vector<Edge*> adjacencyList
     */
    std::vector<Edge *> getAdj() const;

    /**
     * @brief If the vertex was visited
     * 
     * @return true Vertex was visited
     * @return false Vertex was not visited
     */
    bool isVisited() const;

    /**
     * @brief If the vertex is processing
     * 
     * @return true Vertex is processing
     * @return false Vertex is not processing
     */
    bool isProcessing() const;

    /**
     * @brief Get vertex indegree
     * 
     * @return unsigned int indegree
     */
    unsigned int getIndegree() const;

    /**
     * @brief Get vertex path
     * 
     * @return Edge* path
     */
    Edge* getPath() const;

    /**
     * @brief Get incomming edges to the vertex
     * 
     * @return std::vector<Edge*> incommingEdges
     */
    std::vector<Edge *> getIncomming() const;

    /**
     * @brief Set vertex station
     * 
     * @param Station station
     */
    void setStation(const Station& station);

    /**
     * @brief Set vertex to visited/unvisited
     * 
     * @param visited 
     */
    void setVisited(bool visited);

    /**
     * @brief Set vertex to (not) processing
     * 
     * @param processing 
     */
    void setProcessing(bool processing);

    /**
     * @brief Set vertex indegree
     * 
     * @param indegree 
     */
    void setIndegree(unsigned int indegree);

    /**
     * @brief Set source distance
     *
     * @param distance
     */
    void setDistance(int distance);

    /**
     * @brief Set path to vertex
     * 
     * @param path 
     */
    void setPath(Edge* path);



    /**
     * @brief Add an edge with vertex as origin
     * 
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @param service Edge service
     * @return Edge* New edge
     */
    Edge* addEdge(Vertex* dest, int weight, const std::string& service);

    /**
     * @brief Remove an edge with the vertex as origin
     * 
     * @param destStation Station of the destination vertex
     * @return true Vertex was removed
     * @return false Vertex does not exist
     */
    bool removeEdge(const Station& destStation);

    int getDistance() const;
};

/**
 * @brief Represents the path from a station to another in the railway network 
 */
class Edge {
private:
    /**
     * @brief Destination vertex
     */
    Vertex* _dest;
    
    /**
     * @brief Represents number of trains that can be simultainiously be in the edge
     */
    int _weight;
    
    /**
     * @brief Origin vertex
     */
    Vertex* _origin;

    /**
     * @brief Reverse edge (default is nullptr)
     */
    Edge* _reverse = nullptr;

    /**
     * @brief Represent number of trains that are simultainiously in the edge
     */
    int _flow;

    /**
     * @brief Type of service of the edge
     */
    std::string _service;

public:
    Edge(Vertex* origin, Vertex* dest, int weight, const std::string& service);

    /**
     * @brief Get the destination vertex
     * 
     * @return Vertex* destination
     */
    Vertex* getDest() const;

    /**
     * @brief Get the edge's weight
     * 
     * @return int weight
     */
    int getWeight() const;

    /**
     * @brief Get the origin vertex
     * 
     * @return Vertex* origin
     */
    Vertex* getOrigin() const;

    /**
     * @brief Get reverse edge
     * 
     * @return Edge* reverse
     */
    Edge* getReverse() const;

    /**
     * @brief Get the edge's flow
     * 
     * @return int Edge flow
     */
    int getFlow() const;

    /**
     * @brief Get trip's service
     * 
     * @return const std::string& service
     */
    const std::string& getService() const;

    /**
     * @brief Set reverse edge
     * 
     * @param reverse reverse
     */
    void setReverse(Edge* reverse);

    /**
     * @brief Set the flow
     * 
     * @param flow Edge flow
     */
    void setFlow(int flow);
};

#endif // FEUP_DA1_VERTEXEDGE_H
