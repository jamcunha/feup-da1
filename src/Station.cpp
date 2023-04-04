#include "Station.h"

Station::Station(){}

Station::Station(
    const std::string& name,
    const std::string& district,
    const std::string& municipality,
    const std::string& township,
    const std::string& line
): _name(name), _district(district), _municipality(municipality), _township(township), _line(line) {}

std::string Station::getName() const {
    return this->_name;
}

std::string Station::getDistrict() const {
    return this->_district;
}

std::string Station::getMunicipality() const {
    return this->_municipality;
}

std::string Station::getTownship() const {
    return this->_township;
}

std::string Station::getLine() const {
    return this->_line;
}

bool Station::operator==(const Station& other) const {
    return this->_name == other._name;
}
