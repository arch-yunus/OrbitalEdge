#include "ephemeris_engine.hpp"
#include "astronomy_utils.hpp"
#include "vsop87_coefficients.hpp"
#include <iostream>
#include <cmath>

namespace orbital_edge {

using namespace astronomy;

EphemerisEngine::EphemerisEngine(const std::string& veri_yolu) : m_dataPath(veri_yolu) {
    std::cout << "[OrbitalEdge] Motor baslatiliyor. Veri yolu: " << m_dataPath << std::endl;
}

EphemerisEngine::~EphemerisEngine() {
    std::cout << "[OrbitalEdge] Motor kapatiliyor." << std::endl;
}

PlanetPosition EphemerisEngine::get_planet_pos(Planets gezegen, double enlem, double boylam) {
    double jd = get_current_julian_date();
    double gmst = calculate_gmst(jd);

    // Basitleştirilmiş boylam hesaplama (Güneş/Dünya için örnek)
    // T = (JD - 2451545.0) / 36525.0
    double T = (jd - 2451545.0) / 36525.0;
    
    // Güneş boylamı (yaklaşık)
    double L0 = 280.46646 + 36000.76983 * T + 0.0003032 * T * T;
    double M = 357.52911 + 35999.05029 * T - 0.0001537 * T * T;
    double e = 0.016708634 - 0.000042037 * T - 0.0000001267 * T * T;
    
    double C = (1.914602 - 0.004817 * T - 0.000014 * T * T) * std::sin(M * DEG_TO_RAD) +
               (0.019993 - 0.000101 * T) * std::sin(2 * M * DEG_TO_RAD) +
               0.000289 * std::sin(3 * M * DEG_TO_RAD);
    
    double sun_lon = L0 + C;
    double sun_lat = 0.0; // Ekliptik boylamda Güneş enlemi yaklaşıktır
    double epsilon = 23.4392911; // Ecliptic obliquity

    PlanetPosition pos;
    double ra, dec;
    ecliptic_to_equatorial(sun_lon, sun_lat, epsilon, ra, dec);
    
    double alt, az;
    equatorial_to_horizontal(ra, dec, enlem, boylam, gmst, alt, az);

    pos.zodiac_degree = std::fmod(sun_lon, 360.0);
    pos.altitude = alt;
    pos.azimuth = az;

    // Burç hesaplama
    static const std::string burclar[] = {
        "Koc", "Boga", "Ikizler", "Yengec", "Aslan", "Basak", 
        "Terazi", "Akrep", "Yay", "Oglak", "Kova", "Balik"
    };
    int index = static_cast<int>(pos.zodiac_degree / 30.0);
    pos.sign = burclar[index];

    return pos;
}

} // namespace orbital_edge
