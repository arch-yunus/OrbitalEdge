#pragma once

#include <cmath>
#include <string>

namespace orbital_edge {
namespace astronomy {

/**
 * @brief Ay (Lunar) hesaplama motoru için veri yapısı.
 */
struct LunarPosition {
    double lon; // Jeosentrik boylam (Ecliptic)
    double lat; // Jeosentrik enlem (Ecliptic)
    double distance; // Dünya-Ay mesafesi (km)
};

/**
 * @brief ELP-2000/82 teorisinden türetilmiş sadeleştirilmiş Ay efemeris motoru.
 */
class LunarEngine {
public:
    /**
     * @brief Belirli bir Julian Tarihi için Ay konumunu hesaplar.
     */
    static LunarPosition calculate_position(double jd);

private:
    static constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;
    static constexpr double RAD_TO_DEG = 180.0 / 3.14159265358979323846;
};

} // namespace astronomy
} // namespace orbital_edge
