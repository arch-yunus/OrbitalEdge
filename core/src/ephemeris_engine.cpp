#include "ephemeris_engine.hpp"
#include "astronomy_utils.hpp"
#include "vsop87_coefficients.hpp"
#include "lunar_engine.hpp"
#include <iostream>
#include <cmath>

namespace orbital_edge {

using namespace astronomy;

/**
 * @brief Chebyshev Polinomu Yakınsaması.
 * Büyük veri setlerini az sayıda katsayı ile temsil ederek hafıza tasarrufu sağlar.
 */
double evaluate_chebyshev(const std::vector<double>& coeffs, double t) {
    double d = 0.0, dd = 0.0;
    double t2 = 2.0 * t;
    for (size_t j = coeffs.size() - 1; j >= 1; --j) {
        double tmp = d;
        d = t2 * d - dd + coeffs[j];
        dd = tmp;
    }
    return t * d - dd + coeffs[0];
}

EphemerisEngine::EphemerisEngine(const std::string& veri_yolu) : m_dataPath(veri_yolu) {
    // std::cout << "[OrbitalEdge] Motor baslatiliyor." << std::endl;
}

EphemerisEngine::~EphemerisEngine() {
    // std::cout << "[OrbitalEdge] Motor kapatiliyor." << std::endl;
}

/**
 * @brief VSOP87 katsayılarını kullanarak bir gezegenin heliosentrik boylamını hesaplar.
 * Kritik: Bu döngü derleyici tarafından SIMD (NEON/AVX) için optimize edilmeye müsaittir.
 */
double calculate_heliocentric_longitude(int planet_index, double t) {
    const auto& L0 = VSOPData::get_L0(planet_index);
    const auto& L1 = VSOPData::get_L1(planet_index);
    
    double lon_0 = 0.0;
    double lon_1 = 0.0;
    
    for (const auto& term : L0) {
        lon_0 += term.A * std::cos(term.B + term.C * t);
    }
    
    for (const auto& term : L1) {
        lon_1 += term.A * std::cos(term.B + term.C * t);
    }
    
    double result = lon_0 + (lon_1 * t);
    return std::fmod(result, TWO_PI) * RAD_TO_DEG;
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
