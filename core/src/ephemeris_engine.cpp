#include "ephemeris_engine.hpp"
#include "astronomy_utils.hpp"
#include "vsop87_coefficients.hpp"
#include "lunar_engine.hpp"
#include <iostream>
#include <cmath>

namespace orbital_edge {

using namespace astronomy;

EphemerisEngine::EphemerisEngine(const std::string& veri_yolu) : m_dataPath(veri_yolu) {
    // std::cout << "[OrbitalEdge] Motor baslatiliyor." << std::endl;
}

EphemerisEngine::~EphemerisEngine() {
    // std::cout << "[OrbitalEdge] Motor kapatiliyor." << std::endl;
}

/**
 * @brief VSOP87 katsayılarını kullanarak bir gezegenin heliosentrik boylamını hesaplar.
 */
double calculate_heliocentric_longitude(int planet_index, double t) {
    auto series = VSOPData::get_planet_series(planet_index);
    double lon = 0;
    
    for (const auto& term : series.L0) {
        lon += term.A * std::cos(term.B + term.C * t);
    }
    
    for (const auto& term : series.L1) {
        lon += term.A * std::cos(term.B + term.C * t) * t;
    }
    
    return std::fmod(lon, TWO_PI) * RAD_TO_DEG;
}

std::optional<PlanetPosition> EphemerisEngine::get_planet_pos(Planets gezegen, double enlem, double boylam) {
    try {
        double jd = get_current_julian_date();
        double gmst = calculate_gmst(jd);
        double t = (jd - 2451545.0) / 365250.0;

        double planet_lon = 0.0;
        double planet_lat = 0.0;
        double epsilon = 23.4392911;

        if (gezegen == Planets::MOON) {
            auto moon_data = LunarEngine::calculate_position(jd);
            planet_lon = moon_data.lon;
            planet_lat = moon_data.lat;
        } else {
            double earth_lon = calculate_heliocentric_longitude(2, t);

            if (gezegen == Planets::SUN) {
                planet_lon = earth_lon + 180.0;
            } else {
                planet_lon = calculate_heliocentric_longitude(static_cast<int>(gezegen), t);
            }
        }

        PlanetPosition pos;
        double ra, dec;
        ecliptic_to_equatorial(planet_lon, planet_lat, epsilon, ra, dec);
        
        double alt, az;
        equatorial_to_horizontal(ra, dec, enlem, boylam, gmst, alt, az);

        pos.zodiac_degree = std::fmod(planet_lon, 360.0);
        if (pos.zodiac_degree < 0) pos.zodiac_degree += 360.0;
        pos.altitude = alt;
        pos.azimuth = az;

        static const std::string burclar[] = {
            "Koc", "Boga", "Ikizler", "Yengec", "Aslan", "Basak", 
            "Terazi", "Akrep", "Yay", "Oglak", "Kova", "Balik"
        };
        int index = static_cast<int>(pos.zodiac_degree / 30.0);
        pos.sign = burclar[index % 12];

        return pos;
    } catch (...) {
        return std::nullopt;
    }
}

} // namespace orbital_edge
