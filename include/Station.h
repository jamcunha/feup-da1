#ifndef FEUP_DA1_STATION_H
#define FEUP_DA1_STATION_H

#include <string>

/**
 * @brief Represents a station 
 */
class Station {
private:
    /**
     * @brief Station name 
     */
    std::string _name;

    /**
     * @brief Station district
     */
    std::string _district;

    /**
     * @brief Station municipality 
     */
    std::string _municipality;

    /**
     * @brief Station township 
     */
    std::string _township;

    /**
     * @brief Station line 
     */
    std::string _line;

public:
    Station(
        const std::string& name,
        const std::string& district,
        const std::string& municipality,
        const std::string& township,
        const std::string& line
    );
    Station();
    /**
     * @brief Get the station name
     * 
     * @return std::string stationName
     */
    std::string getName() const;

    /**
     * @brief Get the station district
     * 
     * @return std::string stationDistrict
     */
    std::string getDistrict() const;

    /**
     * @brief Get the station municipality
     * 
     * @return std::string stationMunicipality
     */
    std::string getMunicipality() const;

    /**
     * @brief Get the station township
     * 
     * @return std::string stationTownship
     */
    std::string getTownship() const;

    /**
     * @brief Get the stationLine
     * 
     * @return std::string stationLine
     */
    std::string getLine() const;

    /**
     * @brief Checks stations equality
     * 
     * @param other station
     * @return true are the same station
     * @return false are not the same station
     */
    bool operator==(const Station& other) const;
};

#endif // FEUP_DA1_STATION_H