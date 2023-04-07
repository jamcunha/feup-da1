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
        getline(ss, line);
        line.pop_back(); // remove '\r' or '\n'

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
        getline(ss, service);
        service.pop_back(); // remove '\r' or '\n'

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

void Menu::maxTrainWithCost() {
    std::string station_a, station_b;

    std::cout << "Station A: ";
    getline(std::cin, station_a);
    Vertex* v = _graph.findVertex(station_a);
    if (v == nullptr) {
        std::cout << "Invalid station!\n";
        utils::waitEnter();
        return;
    }
    std::cout << "Station B: ";
    getline(std::cin, station_b);
    v = _graph.findVertex(station_b);
    if (v == nullptr) {
        std::cout << "Invalid station!\n";
        utils::waitEnter();
        return;
    }

    _graph.dijkstra(_graph.findVertex(station_a));
    int flow = std::numeric_limits<int>::max(), cost;
    v = _graph.findVertex(station_b);
    cost = v->getDistance();
    while(v->getStation().getName()!=station_a){
        if (flow > v->getPath()->getWeight()){
            flow = v->getPath()->getWeight();
        }
        v = v->getPath()->getOrigin();
    }
    std::cout<<"The minimum cost from "<<station_a<<" to "<<station_b<<" is "<<flow*cost<<"\n";
}


void Menu::showEdgeInfo(const Edge* edge) {
    int col_size = 50;

    std::stringstream ss;
    ss << edge->getOrigin()->getStation().getName() << " -> " << edge->getDest()->getStation().getName();
    std::string temp = ss.str();
    ss.str("");

    std::string info_title = "|";

    for (int i = 0; i < (col_size - temp.size()) / 2; i++) {
        info_title += " ";
    }

    info_title += temp;

    for (int i = 0; i < ((col_size - temp.size()) / 2) - 1; i++) {
        info_title += " ";
    }

    info_title.length() == col_size ? info_title += " |" : info_title += "|";

    ss << "Capacity: " << edge->getWeight();
    temp = ss.str();
    ss.str("");

    std::string info_capacity = "| " + temp;

    for (int i = 0; i < col_size - temp.size() - 3; i++) {
        info_capacity += " ";
    }

    info_capacity += "|";

    ss << "Service: " << edge->getService();
    temp = ss.str();
    ss.str("");

    std::string info_service = "| " + temp;

    for (int i = 0; i < col_size - temp.size() - 3; i++) {
        info_service += " ";
    }

    info_service += "|";

    for (int i = 0; i < col_size; i++) std::cout << '-'; std::cout << '\n';
    std::cout << info_title << '\n';
    for (int i = 0; i < col_size; i++) std::cout << '-'; std::cout << '\n';
    std::cout << info_capacity << '\n';
    std::cout << info_service << '\n';
    for (int i = 0; i < col_size; i++) std::cout << '-'; std::cout << '\n';
}

void Menu::maxTrainBetweenStations(const Graph& g) {
    std::string station_a, station_b;

    std::cout << "Station A: ";
    getline(std::cin, station_a);

    std::cout << "Station B: ";
    getline(std::cin, station_b);



    int max_trains = g.edmondsKarp(station_a, station_b);

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

void Menu::topKMunicipalitiesAndDistricts() {
    int k;

    std::cout << "Insert the number of minicipalities and districts you want to be shown: ";
    std::cin >> k;
    std::cin.ignore(); // ignore '\n' for waitEnter()

    if (k < 0 || k > _graph.getNumVertex()) {
        std::cout << "Input is either negative or bigger than the number of stations!\n";
        utils::waitEnter();
        return;
    }

    utils::clearScreen();

    std::vector<std::string> top_k_municipalities;
    std::vector<std::string> top_k_districts;

    _graph.findTopMunicipalitiesAndDistricts(k, top_k_municipalities, top_k_districts);

    std::cout << "Top " << k << " municipalities:\n";
    for (auto it = top_k_municipalities.begin(); it != top_k_municipalities.end(); it++) {
        std::cout << *it << "\n";
    }

    std::cout << "\nTop " << k << " districts:\n";
    for (auto it = top_k_districts.begin(); it != top_k_districts.end(); it++) {
        std::cout << *it << "\n";
    }

    utils::waitEnter();
}

void Menu::maxTrainArrivingStation() {
    std::string station_name;
    std::cout << "Enter the station: ";
    getline(std::cin, station_name);

    Vertex* target = _graph.findVertex(station_name);
    if (target == nullptr) {
        std::cout << "Invalid station!\n";
        utils::waitEnter();
        return;
    }

    Station super = Station("super","","","","");
    _graph.addVertex(super);

    for (Vertex* v : _graph.getVertexSet()) {
        if (!(v->getStation().getName() == station_name) && v->getAdj().size() == 1) {
            for (auto v: _graph.getVertexSet()) {
                for (auto e: v->getAdj()) {
                    e->setFlow(0);
                }
            }

            if (_graph.findAugmentingPath(v, target)) {
                _graph.addEdge(super.getName(),v->getStation().getName(),std::numeric_limits<int>::max(),"");
            }
        }
    }

    int value = _graph.edmondsKarp(super.getName(),station_name);
    _graph.removeVertex("super");
    std::cout << "The maximum number of trains arriving at the same time at " << station_name<< " is : " << value << "\n";

    utils::waitEnter();
}

Graph Menu::createReducedGraph() {
    Graph reduced_graph = Graph(_graph);
    std::string opt = "n";

    std::cout << "Do you want to remove a station? (y/N): ";
    getline(std::cin, opt);

    bool remove_stations = false;
    if (opt[0] == 'y' || opt[0] == 'Y') {
        remove_stations = true;
    }

    while (remove_stations) {
        std::cout << "Insert the name of the station you want to remove: ";
        std::string station_name;
        getline(std::cin, station_name);

        if (!reduced_graph.removeVertex(station_name)) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
        }

        opt = "n";
        std::cout << "Want to remove another station? (y/N): ";
        getline(std::cin, opt);

        if (opt[0] == 'n' || opt[0] == 'N') {
            break;
        }

        utils::clearScreen();
    }

    opt = "n";
    std::cout << "Do you want to remove a connection between 2 stations? (y/N): ";
    getline(std::cin, opt);

    bool remove_edges = false;
    if (opt[0] == 'y' || opt[0] == 'Y') {
        remove_edges = true;
    }

    while (remove_edges) {
        std::cout << "Insert the name of the origin station: ";
        std::string origin_name;
        getline(std::cin, origin_name);

        auto origin = reduced_graph.findVertex(origin_name);
        if (origin == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();

            opt = "n";
            std::cout << "Want to remove another connection? (y/N): ";
            getline(std::cin, opt);

            if (opt[0] == 'n' || opt[0] == 'N') {
                break;
            }

            utils::clearScreen();
            continue;
        }

        std::cout << "Insert the name of the destination station: ";
        std::string dest_name;
        getline(std::cin, dest_name);

        auto dest = reduced_graph.findVertex(dest_name);
        if (dest == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();

            opt = "n";
            std::cout << "Want to remove another connection? (y/N): ";
            getline(std::cin, opt);

            if (opt[0] == 'n' || opt[0] == 'N') {
                break;
            }

            utils::clearScreen();
            continue;
        }

        utils::clearScreen();

        bool found = false;
        for (auto e : origin->getAdj()) {
            if (e->getDest()->getStation().getName() == dest_name) {
                showEdgeInfo(e);

                std::cout << "\nConfirm? (y/N): ";

                opt = "n";
                getline(std::cin, opt);

                if (opt[0] == 'y' || opt[0] == 'Y') {
                    found = origin->removeEdge(dest->getStation());
                }
            }
        }

        if (!found) {
            std::cout << "Invalid connection!\n\n";
        }

        opt = "n";
        std::cout << "Want to remove another connection? (y/N): ";
        getline(std::cin, opt);

        if (opt[0] == 'n' || opt[0] == 'N') {
            break;
        }

        utils::clearScreen();
    }

    return reduced_graph;
}

void Menu::init() {
    while (true) {
        utils::clearScreen();
        std::cout << "-----------------------------------------------\n";
        std::cout << "|        Welcome to the Railway Manager       |\n";
        std::cout << "|                                             |\n";
        std::cout << "| 1. Max number of trains between 2 stations  |\n";
        std::cout << "| 2. Max train capacity of the network        |\n";
        std::cout << "| 3. Top k municipalities and districts       |\n";
        std::cout << "| 4. Max number of arriving at a station      |\n";
        std::cout << "| 5. Minimum Cost between 2 stations          |\n";
        std::cout << "| 6. Max number of trains with line failures  |\n";
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

            if (opt[0] >= '0' && opt[0] <= '6' ) {
                break;
            }

            std::cout << "Invalid option!\n";
        }

        utils::clearScreen();
        switch(opt[0]) {
            case '0':
                return;
            case '1':
                maxTrainBetweenStations(_graph);
                break;
            case '2':
                maxTrainCapacity();
                break;
            case '3':
                topKMunicipalitiesAndDistricts();
                break;
            case '4':
                maxTrainArrivingStation();
                break;
           /* case '5':
                maxTrainWi*/
            default:
                break;
        }
    }
}