#ifndef FEUP_DA1_GRAPH_H
#define FEUP_DA1_GRAPH_H

#include "VertexEdge.h"

#include <vector>

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
     * @param id Vertex id
     * @return Vertex* vertex
     */
    Vertex* findVertex(const int &id) const;

    /**
     * @brief Add a vertex to the graph
     * 
     * @param id Vertex id
     * @return true Vertex was added
     * @return false Vertex with that id already exists
     */
    bool addVertex(const int &id);

    /**
     * @brief Add a edge to a vertex of the graph
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addEdge(const int &source, const int &dest, double weight);

    /**
     * @brief Add a edge from source to destination vertex and another edge the other way
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addBidirectionalEdge(const int &source, const int &dest, double weight);

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