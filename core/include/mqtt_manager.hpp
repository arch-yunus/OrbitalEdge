#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "ephemeris_engine.hpp"

namespace orbital_edge {
namespace iot {

/**
 * @brief Astronomik verileri JSON formatına dönüştüren hafif yardımcı sınıf.
 */
class MQTTManager {
public:
    /**
     * @brief Gezegen verisini JSON string olarak döndürür.
     */
    static std::string serialize_planet_data(const std::string& name, const PlanetPosition& pos) {
        std::stringstream ss;
        ss << "{"
           << "\"gezegen\":\"" << name << "\","
           << "\"boylam\":" << pos.zodiac_degree << ","
           << "\"yukseklik\":" << pos.altitude << ","
           << "\"azimut\":" << pos.azimuth << ","
           << "\"burc\":\"" << pos.sign << "\""
           << "}";
        return ss.str();
    }

    /**
     * @brief Tüm gökyüzü durumunu bir JSON listesi olarak döndürür.
     */
    static std::string serialize_all(const std::vector<std::pair<std::string, PlanetPosition>>& data) {
        std::stringstream ss;
        ss << "{\"orbital_edge_telemetry\": [";
        for (size_t i = 0; i < data.size(); ++i) {
            ss << serialize_planet_data(data[i].first, data[i].second);
            if (i < data.size() - 1) ss << ",";
        }
        ss << "]}";
        return ss.str();
    }
};

} // namespace iot
} // namespace orbital_edge
