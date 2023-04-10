#include "Menu.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <queue>

// input files
const std::string Menu::STATIONS_INPUT = "../data/stations.csv";
const std::string Menu::NETWORK_INPUT = "../data/network.csv";

void Menu::readData() {
    std::ifstream station_input(STATIONS_INPUT);
    std::ifstream network_input(NETWORK_INPUT);

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

        if (line.back() == '\r' || line.back() == '\n') {
            line.pop_back(); // remove '\r' or '\n'
        }

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

        if (service.back() == '\r' || service.back() == '\n') {
            service.pop_back(); // remove '\r' or '\n'
        }

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

void Menu::showEdgeInfo(const Edge* edge) const {
    int col_size = 50;

    std::stringstream ss;
    ss << edge->getOrigin()->getStation().getName() << " -> " << edge->getDest()->getStation().getName();
    std::string temp = ss.str();
    ss.str("");

    std::string info_title = "|";

    for (int i = 0; i < (col_size - temp.length()) / 2; i++) {
        info_title += " ";
    }

    info_title += temp;

    for (int i = 0; i < ((col_size - temp.length()) / 2) - 1; i++) {
        info_title += " ";
    }

    info_title.length() == col_size ? info_title += " |" : info_title += "|";

    ss << "Capacity: " << edge->getWeight();
    temp = ss.str();
    ss.str("");

    std::string info_capacity = "| " + temp;

    while (info_capacity.length() < col_size - 1) {
        info_capacity += " ";
    }

    info_capacity += "|";

    ss << "Service: " << edge->getService();
    temp = ss.str();
    ss.str("");

    std::string info_service = "| " + temp;

    while (info_service.length() < col_size - 1) {
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

void Menu::showVertexInfo(const Vertex* vertex) const {
    int col_size = 50;

    std::stringstream ss;
    ss << "| Name: " << vertex->getStation().getName();
    std::string temp = ss.str();
    ss.str("");

    while (temp.length() < col_size - 1) {
        temp += " ";
    }
    temp += "|";

    std::string info_name = temp;

    ss << "| District: " << vertex->getStation().getDistrict();
    temp = ss.str();
    ss.str("");

    while (temp.length() < col_size - 1) {
        temp += " ";
    }
    temp += "|";

    std::string info_district = temp;

    ss << "| Municipality: " << vertex->getStation().getMunicipality();
    temp = ss.str();
    ss.str("");

    while (temp.length() < col_size - 1) {
        temp += " ";
    }
    temp += "|";

    std::string info_municipality = temp;

    ss << "| Township: " << vertex->getStation().getTownship();
    temp = ss.str();
    ss.str("");

    while (temp.length() < col_size - 1) {
        temp += " ";
    }
    temp += "|";

    std::string info_township = temp;

    ss << "| Line: " << vertex->getStation().getLine();
    temp = ss.str();
    ss.str("");

    while (temp.length() < col_size - 1) {
        temp += " ";
    }
    temp += "|";

    std::string info_line = temp;

    for (int i = 0; i < col_size; i++) std::cout << '-'; std::cout << '\n';
    std::cout << info_name << '\n';
    std::cout << info_district << '\n';
    std::cout << info_municipality << '\n';
    std::cout << info_township << '\n';
    std::cout << info_line << '\n';
    for (int i = 0; i < col_size; i++) std::cout << '-'; std::cout << '\n';
}

void Menu::maxTrainBetweenStations(const Graph& g) {
    std::string origin_station, dest_station;

    while (true) {
        std::cout << "Origin Station: ";
        getline(std::cin, origin_station);
        Vertex* v = g.findVertex(origin_station);
        if (v == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
            return;
        }

        utils::clearScreen();
        showVertexInfo(v);

        std::cout << "\nConfirm? (y/N): ";
        std::string opt = "n";
        getline(std::cin, opt);

        if (opt[0] == 'y' || opt[0] == 'Y') {
            break;
        }
    }

    utils::clearScreen();
    
    while (true) {
        std::cout << "Destination Station: ";
        getline(std::cin, dest_station);
        Vertex* v = g.findVertex(dest_station);
        if (v == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
            return;
        }

        utils::clearScreen();
        showVertexInfo(v);

        std::cout << "\nConfirm? (y/N): ";
        std::string opt = "n";
        getline(std::cin, opt);

        if (opt[0] == 'y' || opt[0] == 'Y') {
            break;
        }
    }

    int max_trains = g.edmondsKarp(origin_station, dest_station);

    utils::clearScreen();
    if (max_trains == -1) {
        std::cout << "Impossible path!\n";
        utils::waitEnter();
        return;
    }

    std::cout << "Max number of trains between " << origin_station << " and " << dest_station << ": " << max_trains << "\n";
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

    std::cout << "Top " << k << " municipalities:\n\n";
    for (auto it = top_k_municipalities.begin(); it != top_k_municipalities.end(); it++) {
        std::cout << *it << "\n";
    }

    std::cout << "\nTop " << k << " districts:\n\n";
    for (auto it = top_k_districts.begin(); it != top_k_districts.end(); it++) {
        std::cout << *it << "\n";
    }

    utils::waitEnter();
}

int Menu::maxTrainArrivingStationHelper(Graph& g, const std::string& station_name) {
    Vertex* target = g.findVertex(station_name);
    if (target == nullptr) {
        return -1;
    }

    Station super = Station("super","","","","");
    g.addVertex(super);

    for (Vertex* v : g.getVertexSet()) {
        if (!(v->getStation().getName() == station_name) && v->getAdj().size() == 1) {
            for (auto v: g.getVertexSet()) {
                for (auto e: v->getAdj()) {
                    e->setFlow(0);
                }
            }

            if (g.findAugmentingPath(v, target)) {
                g.addEdge(super.getName(),v->getStation().getName(),std::numeric_limits<int>::max(),"");
            }
        }
    }

    int val = g.edmondsKarp(super.getName(), station_name);
    g.removeVertex("super");
    return val;
}

void Menu::maxTrainArrivingStation() {
    std::string station_name;
    while (true) {
        std::cout << "Enter the station name: ";
        getline(std::cin, station_name);
        Vertex* v = _graph.findVertex(station_name);
        if (v == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
            return;
        }

        utils::clearScreen();
        showVertexInfo(v);

        std::cout << "\nConfirm? (y/N): ";
        std::string opt = "n";
        getline(std::cin, opt);

        if (opt[0] == 'y' || opt[0] == 'Y') {
            break;
        }
    }

    int max_arriving = maxTrainArrivingStationHelper(_graph, station_name);

    utils::clearScreen();
    if (max_arriving == -1) {
        std::cout << "Invalid station!\n";
        utils::waitEnter();
        return;
    }

    std::cout << "The maximum number of trains arriving at the same time at " << station_name << " is : " << max_arriving << '\n';

    utils::waitEnter();
}

void Menu::maxTrainWithCost() {
    std::string origin_station, dest_station;
    Vertex* source; Vertex* dest;

    while (true) {
        std::cout << "Origin Station: ";
        getline(std::cin, origin_station);
        source = _graph.findVertex(origin_station);
        if (source == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
            return;
        }

        utils::clearScreen();
        showVertexInfo(source);

        std::cout << "\nConfirm? (y/N): ";
        std::string opt = "n";
        getline(std::cin, opt);

        if (opt[0] == 'y' || opt[0] == 'Y') {
            break;
        }
    }

    utils::clearScreen();
    
    while (true) {
        std::cout << "Destination Station: ";
        getline(std::cin, dest_station);
        dest = _graph.findVertex(dest_station);
        if (dest == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
            return;
        }

        utils::clearScreen();
        showVertexInfo(dest);

        std::cout << "\nConfirm? (y/N): ";
        std::string opt = "n";
        getline(std::cin, opt);

        if (opt[0] == 'y' || opt[0] == 'Y') {
            break;
        }
    }

    _graph.dijkstra(source);
    int flow = std::numeric_limits<int>::max();
    int cost = dest->getDistance();

    Vertex* temp = dest;
    while (temp->getStation().getName() != origin_station) {
        if (flow > temp->getPath()->getWeight()) {
            flow = temp->getPath()->getWeight();
        }
        temp = temp->getPath()->getOrigin();
    }

    utils::clearScreen();
    std::cout << "The minimum cost from " << origin_station << " to " << dest_station << " is " << flow * cost << '\n';
    utils::waitEnter();
}

void Menu::mostAffectedStations(Graph& g) {
    int k;

    std::cout << "Insert the number of stations you want to be shown: ";
    std::cin >> k;
    std::cin.ignore(); // ignore '\n' for waitEnter()

    if (k < 0 || k > g.getNumVertex()) {
        std::cout << "Input is either negative or bigger than the number of stations!\n";
        utils::waitEnter();
        return;
    }

    std::vector<std::pair<std::string ,int>> diff;
    for (Vertex* v : _graph.getVertexSet()) {
        int original_max = maxTrainArrivingStationHelper(_graph, v->getStation().getName());
        original_max = original_max == -1 ? 0 : original_max; //? in case the station doesn't have flow
        int new_max = maxTrainArrivingStationHelper(g, v->getStation().getName());
        new_max = new_max == -1 ? 0 : new_max; //? in case the station is not in the new graph or doesn't have flow

        diff.push_back(std::make_pair(v->getStation().getName(), original_max - new_max));
    }

    auto cmp = [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second > b.second;
    };
    std::priority_queue<
            std::pair<std::string, int>,
            std::vector<std::pair<std::string, int>>,
            decltype(cmp)
    > pq(cmp);

    for (const auto &stations: diff) {
        pq.push(stations);
        if (pq.size() > k) {
            pq.pop();
        }
    }

    diff.clear();
    while (!pq.empty()) {
        diff.insert(diff.begin(), pq.top());
        pq.pop();
    }

    utils::clearScreen();
    std::cout << "Station -> Difference\n\n";
    for (const auto &stations: diff) {
        if (stations.second == 0) {
            break;
        }

        std::cout << stations.first << " -> " << stations.second << '\n';
    }

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
        std::string station_name;
        while (true) {
            utils::clearScreen();
            std::cout << "Insert the name of the station you want to remove: ";
            getline(std::cin, station_name);
            Vertex* v = _graph.findVertex(station_name);
            if (v == nullptr) {
                break;
            }

            utils::clearScreen();
            showVertexInfo(v);

            std::cout << "\nConfirm? (y/N): ";
            opt = "n";
            getline(std::cin, opt);

            if (opt[0] == 'y' || opt[0] == 'Y') {
                break;
            }
        }

        if (!reduced_graph.removeVertex(station_name)) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();
        }

        opt = "n";
        utils::clearScreen();
        std::cout << "Want to remove another station? (y/N): ";
        getline(std::cin, opt);

        if (opt[0] == 'n' || opt[0] == 'N') {
            break;
        }

        utils::clearScreen();
    }

    opt = "n";
    utils::clearScreen();
    std::cout << "Do you want to remove a connection between 2 stations? (y/N): ";
    getline(std::cin, opt);

    bool remove_edges = false;
    if (opt[0] == 'y' || opt[0] == 'Y') {
        remove_edges = true;
    }

    while (remove_edges) {
        std::string origin_name; Vertex* origin;
        while (true) {
            utils::clearScreen();
            std::cout << "Insert the name of the origin station: ";
            getline(std::cin, origin_name);
            origin = _graph.findVertex(origin_name);
            if (origin == nullptr) {
                break;
            }

            utils::clearScreen();
            showVertexInfo(origin);

            std::cout << "\nConfirm? (y/N): ";
            opt = "n";
            getline(std::cin, opt);

            if (opt[0] == 'y' || opt[0] == 'Y') {
                break;
            }
        }

        origin = reduced_graph.findVertex(origin_name);
        if (origin == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();

            opt = "n";
            utils::clearScreen();
            std::cout << "Want to remove another connection? (y/N): ";
            getline(std::cin, opt);

            if (opt[0] == 'n' || opt[0] == 'N') {
                break;
            }

            utils::clearScreen();
            continue;
        }

        std::string dest_name; Vertex* dest;
        while (true) {
            utils::clearScreen();
            std::cout << "Insert the name of the destination station: ";
            getline(std::cin, dest_name);
            dest = _graph.findVertex(dest_name);
            if (dest == nullptr) {
                break;
            }

            utils::clearScreen();
            showVertexInfo(dest);

            std::cout << "\nConfirm? (y/N): ";
            opt = "n";
            getline(std::cin, opt);

            if (opt[0] == 'y' || opt[0] == 'Y') {
                break;
            }
        }

        dest = reduced_graph.findVertex(dest_name);
        if (dest == nullptr) {
            std::cout << "Invalid station!\n";
            utils::waitEnter();

            opt = "n";
            utils::clearScreen();
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
        utils::clearScreen();
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
        std::cout << "| 6. Maintenance                              |\n";
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
            case '5':
                maxTrainWithCost();
                break;
            case '6':
                reducedGraphMenu();
                break;
            default:
                break;
        }
    }
}

void Menu::reducedGraphMenu() {
    Graph reduced_graph = createReducedGraph();

    while (true) {
        utils::clearScreen();
        std::cout << "-----------------------------------------------\n";
        std::cout << "|                 Maintenance                 |\n";
        std::cout << "|                                             |\n";
        std::cout << "| 1. Max number of trains with line failures  |\n";
        std::cout << "| 2. Most Affected Stations                   |\n";
        std::cout << "|                                             |\n";
        std::cout << "| 0. Return to Main Menu                      |\n";
        std::cout << "-----------------------------------------------\n";

        std::string opt;
        while (true) {
            std::cout << "\nOption: ";
            getline(std::cin, opt);

            if (opt.length() != 1) {
                std::cout << "Invalid option!\n";
                continue;
            }

            if (opt[0] >= '0' && opt[0] <= '2' ) {
                break;
            }

            std::cout << "Invalid option!\n";
        }

        utils::clearScreen();
        switch(opt[0]) {
            case '0':
                return;
            case '1':
                maxTrainBetweenStations(reduced_graph);
                break;
            case '2':
                mostAffectedStations(reduced_graph);
                break;
            default:
                break;
        }
    }
}
