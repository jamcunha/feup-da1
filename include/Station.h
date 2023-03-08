#ifndef FEUP_DA1_STATION_H
#define FEUP_DA1_STATION_H

#include <string>

class Station {
private:
    std::string _name;
    std::string _district;
    std::string _municipality;
    std::string _township;
    std::string _line;

public:
    Station(
        const std::string& name,
        const std::string& district,
        const std::string& municipality,
        const std::string& township,
        const std::string& line
    );

    std::string getName() const;
    std::string getDistrict() const;
    std::string getMunicipality() const;
    std::string getTownship() const;
    std::string getLine() const;

    bool operator==(const Station& other) const;
};

#endif // FEUP_DA1_STATION_H