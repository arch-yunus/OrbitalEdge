#include "lunar_engine.hpp"
#include <cmath>

namespace orbital_edge {
namespace astronomy {

LunarPosition LunarEngine::calculate_position(double jd) {
    // T = (JD - 2451545.0) / 36525.0
    double T = (jd - 2451545.0) / 36525.0;

    // Ay'ın ortalama parametreleri (derece)
    double L0 = 218.3164477 + 481267.8812338 * T;
    double M = 134.9633964 + 477198.8675055 * T;
    double Mp = 357.5291092 + 35999.0502909 * T;
    double F = 93.2720950 + 483202.0175233 * T;
    double D = 297.8501921 + 445267.1114034 * T;

    // Ana periyodik terimler (Boylam için) - Sadeleştirilmiş ELP
    double lon = L0 + 6.288774 * std::sin(M * DEG_TO_RAD)
                   + 1.274027 * std::sin((2 * D - M) * DEG_TO_RAD)
                   + 0.658314 * std::sin(2 * D * DEG_TO_RAD)
                   + 0.213618 * std::sin(2 * M * DEG_TO_RAD)
                   - 0.185116 * std::sin(Mp * DEG_TO_RAD)
                   - 0.114332 * std::sin(2 * F * DEG_TO_RAD);

    // Enlem için ana terimler
    double lat = 5.128122 * std::sin(F * DEG_TO_RAD)
                   + 0.280602 * std::sin((M + F) * DEG_TO_RAD)
                   + 0.277693 * std::sin((M - F) * DEG_TO_RAD);

    // Mesafe (Paralaks üzerinden km bazında yaklaşıktır)
    double distance = 385000.56; // Ortalama mesafe

    LunarPosition pos;
    pos.lon = std::fmod(lon, 360.0);
    if (pos.lon < 0) pos.lon += 360.0;
    pos.lat = lat;
    pos.distance = distance;

    return pos;
}

} // namespace astronomy
} // namespace orbital_edge
