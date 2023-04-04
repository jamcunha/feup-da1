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

    /**
     * @brief Find an augmenting path in the graph using BFS
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @return true Found augmenting path
     * @return false No augmenting path
     */
    bool findAugmentingPath(Vertex *source, Vertex *dest) const;

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
     * @brief Find the maximum flow between source and destination vertex using Edmonds-Karp algorithm
     * Used to calculate the maximum number of trains that can simultaneously travel between two stations
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @return int max_flow or -1 if input error
     */
    int edmondsKarp(const std::string& source, const std::string& dest) const;

    /**
     * @brief Get the pair of stations that require the maximum number of trains to travel between them
     * 
     * @return std::vector<std::pair<std::pair<std::string, std::string>, int>> Vector of pairs of stations and the maximum number
     * of trains that can simultaneously travel between them
     */
    std::vector<std::pair<std::pair<std::string, std::string>, int>> getMaxTrainCapacityPairs() const;

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