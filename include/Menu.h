#ifndef FEUP_DA1_MENU_H
#define FEUP_DA1_MENU_H

#include "Graph.h"

class Menu {
private:
    Graph _graph;

    void readData();

    /* Show Vertex and Edge Info */
    void showEdgeInfo(const Edge* edge);

    /* Basic Service Metrics */
    void maxTrainBetweenStations(const Graph& g);
    void maxTrainCapacity();
    void topKMunicipalitiesAndDistricts();
    void maxTrainArrivingStation();

    /* Operation Cost Optimization */
    void maxTrainWithCost();

    /* Reliability and Sensitivity to line failures */
    Graph createReducedGraph();

public:
    Menu();

    void init();
};

#endif // FEUP_DA1_MENU_H
