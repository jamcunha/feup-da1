#ifndef FEUP_DA1_MENU_H
#define FEUP_DA1_MENU_H

#include "Graph.h"

class Menu {
private:
    Graph _graph;

    void readData();

public:
    Menu();

    void init();
};

#endif // FEUP_DA1_MENU_H