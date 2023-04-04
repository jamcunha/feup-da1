#ifndef FEUP_DA1_GRAPH_H
#define FEUP_DA1_GRAPH_H

#include "VertexEdge.h"

#include <vector>

/**
 * @brief Railway network
 */
class Graph {
private:
    /**
     * @brief Vector of graph vertexes
     */
    std::vector<Vertex *> vertexSet;

public:
    /**
     * @brief Find a vertex in the graph with the given id, if it does not exists return nullptr
     * 
     * @param stationName Vertex stationName
     * @return Vertex* vertex
     */
    Vertex* findVertex(const std::string& stationName) const;

    /**
     * @brief Add a vertex to the graph
     * 
     * @param station Vertex station
     * @return true Vertex was added
     * @return false Vertex with that id already exists
     */
    bool addVertex(const Station& station);

    /**
     * @brief Remove a vertex from the graph
     * 
     * @param station_name Name of the station to remove
     * @return true Vertex was removed
     * @return false Vertex was not found
     */
    bool removeVertex(const std::string& station_name);

    /**
     * @brief Add a edge to a vertex of the graph
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @param service Edge service
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addEdge(const std::string& source, const std::string& dest, int weight, const std::string& service);

    /**
     * @brief Add a edge from source to destination vertex and another edge the other way
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @param service Edge service
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addBidirectionalEdge(const std::string& source, const std::string& dest, int weight, const std::string& service);

    /**
     * @brief Find an augmenting path in the graph using BFS
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @return true Found augmenting path
     * @return false No augmenting path
     */
    bool findAugmentingPath(Vertex *source, Vertex *dest);

    /**
     * @brief Find the shortest path between source and destination vertex using Edmonds-Karp algorithm
     * Used to calculate the maximum number of trains that can simultaneously travel between two stations
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @return int max_flow or -1 if input error
     */
    int edmondsKarp(const std::string& source, const std::string& dest);

    /**
     * @brief Get graph's number of vertexes
     * 
     * @return int Number of vertexes
     */
    int getNumVertex() const;

    /**
     * @brief Get graph's vertexes
     * 
     * @return std::vector<Vertex *> vertexSet
     */
    std::vector<Vertex *> getVertexSet() const;
};

#endif // FEUP_DA1_GRAPH_H