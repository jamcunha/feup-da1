#ifndef FEUP_DA1_MENU_H
#define FEUP_DA1_MENU_H

#include "Graph.h"

/**
 * @brief Friendly user menu
 */

class Menu {
private:
    Graph _graph;

    /**
     * @brief Open and read the files
     * @details Complexity: O(n+m)
     */
    void readData();

    /**
     * @brief Show Vertex and Edge Info
     * @details Complexity: O(1)
     * @param edge Edge that we want to see the info
     */
    void showEdgeInfo(const Edge* edge);

    /* Basic Service Metrics */
    /**
     * @brief Calculate the max number of trains that can travel at the same time between stations
     * @details Complexity: O(VE²)
     * @param g Graph that is used to calculate
     */
    void maxTrainBetweenStations(const Graph& g);

    /**
     * @brief Calculate the pair(s) of stations that takes full advantage of the network capacity
     * @details Complexity: O(|V|³*|E|)
     */
    void maxTrainCapacity();

    /**
     * @brief Calculate the top minicipalities and districts with most flow
     * @details Complexity: O(|V|³*|E|))
     */
    void topKMunicipalitiesAndDistricts();

    /**
     * @brief Calculate the maximum number of trains that can arrive simultaneously ate one station
     * @details Complexity: O(VE²)
     * @param g Graph that is used to calculate
     * @param station_name Name of the station
     */
    int maxTrainArrivingStationHelper(Graph& g, const std::string& station_name);

    /**
     * @brief Show the maximum number of trains that can arrive simultaneously ate one station
     * @details Complexity: O(VE²)
     */
    void maxTrainArrivingStation();

    /* Operation Cost Optimization */
    /**
     * @brief Calculate the minimum cost of a travel with maximum flow
     * @details Complexity: O(|E|+|V|log|V|)
     */
    void maxTrainWithCost();

    /* Reliability and Sensitivity to line failures */
    /**
     * @brief Create a reduced graph of the original one
     * @details Complexity: O()
     * return Graph
     */
    Graph createReducedGraph();

    /**
     * @brief Calculate the stations that are most affected with the reduction
     * @details Complexity: O()
     * @param g Graph that is used to calculate
     */
    void mostAffectedStations(Graph& g);

public:
    Menu();

    void init();


};

#endif // FEUP_DA1_MENU_H
