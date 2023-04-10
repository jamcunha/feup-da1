#ifndef FEUP_DA1_MENU_H
#define FEUP_DA1_MENU_H

#include "Graph.h"

#include <string>

/**
 * @brief Friendly user menu
 */

class Menu {
private:
    /**
     * @brief Graph of the railway network
     */
    Graph _graph;

    /**
     * @brief File name of station input in csv format
     */
    static const std::string STATIONS_INPUT;
    
    /**
     * @brief File name of network input in csv format
     */
    static const std::string NETWORK_INPUT;

    /**
     * @brief Open and read the files
     * @details Time Complexity: O(n+m) where n is the number of lines in the stations file and m is the number of lines in the network file.
     */
    void readData();

    /**
     * @brief Show Edge Info
     * @details Time Complexity: O(1)
     * 
     * @param edge Edge that we want to see the info
     */
    void showEdgeInfo(const Edge* edge);

    /**
     * @brief Show Vertex Info (without adjacent and incomming edges info)
     * @details Time Complexity: O(1)
     * 
     * @param vertex Vertex that we want to see the info
     */
    void showVertexInfo(const Vertex* vertex); // TODO: implement

    /* Basic Service Metrics */
    /**
     * @brief Calculate the max number of trains that can travel at the same time between stations
     * @details Time Complexity: O(|V||E|²)
     * @param g Graph that is used to calculate
     */
    void maxTrainBetweenStations(const Graph& g);

    /**
     * @brief Calculate the pair(s) of stations that takes full advantage of the network capacity
     * @details Time Complexity: O(|V|³|E|²)
     */
    void maxTrainCapacity();

    /**
     * @brief Calculate the top minicipalities and districts with most flow
     * @details Time Complexity: O(|V|³|E|²))
     */
    void topKMunicipalitiesAndDistricts();

    /**
     * @brief Calculate the maximum number of trains that can arrive simultaneously ate one station
     * @details Time Complexity: O(|V|²|E|)
     * 
     * @param g Graph that is used to calculate
     * @param station_name Name of the station
     */
    int maxTrainArrivingStationHelper(Graph& g, const std::string& station_name);

    /**
     * @brief Show the maximum number of trains that can arrive simultaneously ate one station
     * @details Time Complexity: O(|V|²|E|)
     */
    void maxTrainArrivingStation();

    /* Operation Cost Optimization */
    /**
     * @brief Calculate the minimum cost of a travel with maximum flow
     * @details Time Complexity: O(|V|+|E|log(|V|))
     */
    void maxTrainWithCost();

    /* Reliability and Sensitivity to line failures */
    /**
     * @brief Create a reduced graph of the original one
     * @details Time Complexity: O(|V||E|²)
     * 
     * return Reduced Graph
     */
    Graph createReducedGraph();

    /**
     * @brief Calculate the stations that are most affected with the reduction
     * @details Time Complexity: O(|V|³|E|))
     * @param g Graph that is used to calculate
     */
    void mostAffectedStations(Graph& g);

public:
    /**
     * @brief Construct a new Menu object.
     */
    Menu();

    /**
     * @brief Shows a friendly menu and read the option from the user.
     */
    void init();

    /**
     * @brief Shows a submenu with options regarding a reduced graph.
     */
    void reducedGraphMenu();
};

#endif // FEUP_DA1_MENU_H
