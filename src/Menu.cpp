#include "Menu.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>


void Menu::readData() {
    std::ifstream station_input("../data/stations.csv");
    std::ifstream network_input("../data/network.csv");

    std::string line;

    // discard fist line of the files
    getline(station_input, line);
    getline(network_input, line);

    while (getline(station_input, line)) {
        std::stringstream ss(line);

        std::string name, district, municipality, township, line;

        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, line, '\n');

        _graph.addVertex(Station(
            name,
            district,
            municipality,
            township,
            line
        ));
    }

    while (getline(network_input, line)) {
        std::stringstream ss(line);

        std::string station_a, station_b, capacity_string, service;

        getline(ss, station_a, ',');
        getline(ss, station_b, ',');
        getline(ss, capacity_string, ',');
        getline(ss, service, '\n');

        _graph.addBidirectionalEdge(
            station_a,
            station_b,
            std::stoi(capacity_string) / 2,
            service
        );
    }
}

Menu::Menu(): _graph(Graph()) {
    readData();
}

void Menu::maxTrainArrivingStation() {
    std::string station;
    std::cout << "Enter the station: ";
    getline(std::cin, station);

    Vertex* target = _graph.findVertex(station);
    std::vector<Vertex*> vertexSet = _graph.getVertexSet();

    Station super = Station("super","","","","");
    _graph.addVertex(super);

    for (Vertex* v : vertexSet) {
        if (v->getAdj().size() == 1 && _graph.findAugmentingPath(v, target)){
            _graph.addBidirectionalEdge(super.getName(),v->getStation().getName(),std::numeric_limits<int>::max(),"");
        }
    }

    int value = _graph.edmondsKarp(super.getName(),station);
    _graph.removeVertex("super");
    std::cout << "The maximum number of trains arriving at the same time at " << station<< " is : " << value << "\n";

    utils::waitEnter();
}

void Menu::maxTrainBetweenStations() {
    std::string station_a, station_b;

    std::cout << "Station A: ";
    getline(std::cin, station_a);

    std::cout << "Station B: ";
    getline(std::cin, station_b);



    int max_trains = _graph.edmondsKarp(station_a, station_b);

    if (max_trains == -1) {
        std::cout << "Invalid stations!\n";
        utils::waitEnter();
        return;
    }

    std::cout << "Max number of trains between " << station_a << " and " << station_b << ": " << max_trains << "\n";
    utils::waitEnter();
}

void Menu::maxTrainCapacity() {
    std::vector<std::pair<std::pair<std::string, std::string>, int>> max_trains = _graph.getMaxTrainCapacityPairs();

    for (const auto& pair : max_trains) {
        std::cout << "Max number of trains between " << pair.first.first << " and " << pair.first.second << ": " << pair.second << "\n";
    }

    utils::waitEnter();
}

void Menu::init() {
    while (true) {
        utils::clearScreen();
        std::cout << "-----------------------------------------------\n";
        std::cout << "|        Welcome to the Railway Manager       |\n";
        std::cout << "|                                             |\n";
        std::cout << "| 1. Max number of trains between 2 stations  |\n";
        std::cout << "| 2. Max train capacity of the network        |\n";
        std::cout << "| 3. Max number of arriving at a station      |\n";
        std::cout << "|                                             |\n";
        std::cout << "| 0. Exit                                     |\n";
        std::cout << "-----------------------------------------------\n";

        std::string opt;
        while (true) {
            std::cout << "\nOption: ";
            getline(std::cin, opt);

            if (opt.length() != 1) {
                std::cout << "Invalid option!\n";
                continue;
            }

            if (opt[0] >= '0' && opt[0] <= '3' ) {
                break;
            }

            std::cout << "Invalid option!\n";
        }

        utils::clearScreen();
        switch(opt[0]) {
            case '0':
                return;
            case '1':
                maxTrainBetweenStations();
                break;
            case '2':
                maxTrainCapacity();
                break;
            case '3':
                maxTrainArrivingStation();
                break;
            default:
                break;
        }
    }
}
