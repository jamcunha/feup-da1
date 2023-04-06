#ifndef FEUP_DA1_MENU_H
#define FEUP_DA1_MENU_H

#include "Graph.h"

class Menu {
private:
    Graph _graph;

    void readData();

    /* Basic Service Metrics */
    void maxTrainBetweenStations(const Graph& g);
    void maxTrainCapacity();
    void topKMunicipalitiesAndDistricts();
    void maxTrainArrivingStation();

    /* Reliability and Sensitivity to line failures */
    Graph createReducedGraph();

public:
    Menu();

    void init();
};

#endif // FEUP_DA1_MENU_H