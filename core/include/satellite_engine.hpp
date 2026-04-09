#pragma once

#include <string>
#include <vector>
#include <optional>
#include "ephemeris_engine.hpp"

namespace orbital_edge {
namespace satellites {

/**
 * @brief TLE (Two-Line Element) verisi yapisi.
 */
struct TLE {
    std::string name;
    std::string line1;
    std::string line2;
};

/**
 * @brief Uydu pozisyon verisi.
 */
struct SatellitePosition {
    double latitude;
    double longitude;
    double altitude_km;
    double azimuth;
    double elevation;
};

/**
 * @brief SGP4 algoritması ile uydu takibi yapan motor.
 */
class SatelliteEngine {
public:
    SatelliteEngine();

    /**
     * @brief TLE verisi ile bir uydunun anlık konumunu hesaplar.
     */
    SatellitePosition calculate_position(const TLE& tle, double jd, double obs_lat, double obs_lon);

    /**
     * @brief ISS (Uluslararasi Uzay Istasyonu) icin guncel TLE ornegi dondurur.
     */
    static TLE get_iss_tle();
};

} // namespace satellites
} // namespace orbital_edge
