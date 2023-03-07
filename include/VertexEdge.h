#ifndef FEUP_DA1_VERTEXEDGE_H
#define FEUP_DA1_VERTEXEDGE_H

#include <vector>

class Edge;

class Vertex {
private:
    /**
     * @brief Vertex id
     */
    int id;

    /**
     * @brief Adjacency list of edges
     */
    std::vector<Edge *> adj;

    /**
     * @brief If vertex was visited
     */
    bool visited = false;
    
    /**
     * @brief If vertex is processing (used for DAGs)
     */
    bool processing = false;
    
    /**
     * @brief Vertex indegree (used for topsort)
     */
    unsigned int indegree;

    /**
     * @brief Path traveled until this vertex
     */
    Edge* path = nullptr;

    /**
     * @brief Incomming edges to the vertex
     */
    std::vector<Edge *> incomming;

public:
    Vertex(int id);

    /**
     * @brief Get the vertex id
     * 
     * @return int id
     */
    int getId() const;

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
     * @brief Set vertex id
     * 
     * @param id 
     */
    void setId(int id);

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
     * @return Edge* New edge
     */
    Edge* addEdge(Vertex* dest, double weight);

    /**
     * @brief Remove an edge with the vertex as origin
     * 
     * @param destId Id of the destination vertex
     * @return true Vertex was removed
     * @return false Vertex does not exist
     */
    bool removeEdge(int destId);
};

class Edge {
private:
    /**
     * @brief Destination vertex
     */
    Vertex* dest;
    
    /**
     * @brief Weight of the edge
     */
    double weight;
    
    /**
     * @brief Origin vertex
     */
    Vertex* origin;

    /**
     * @brief Reverse edge (default is nullptr)
     */
    Edge* reverse = nullptr;

    /**
     * @brief Flow of the edge
     */
    double flow;

public:
    Edge(Vertex* origin, Vertex* dest, double weight);

    /**
     * @brief Get the destination vertex
     * 
     * @return Vertex* destination
     */
    Vertex* getDest() const;

    /**
     * @brief Get the edge's weight
     * 
     * @return double weight
     */
    double getWeight() const;

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
     * @return double Edge flow
     */
    double getFlow() const;

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
    void setFlow(double flow);
};

#endif // FEUP_DA1_VERTEXEDGE_H
