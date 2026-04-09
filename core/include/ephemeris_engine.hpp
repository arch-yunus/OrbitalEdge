#pragma once

#include <string>
#include <vector>
#include <optional>

namespace orbital_edge {

enum class Planets {
    SUN = 0,
    MOON = 1,
    MERCURY = 2,
    VENUS = 3,
    EARTH = 4, // Dunya (Heliocentric icin)
    MARS = 5,
    JUPITER = 6,
    SATURN = 7,
    URANUS = 8,
    NEPTUNE = 9,
    PLUTO = 10
};

struct PlanetPosition {
    double zodiac_degree;
    double altitude;
    double azimuth;
    std::string sign;
};

class EphemerisEngine {
public:
    EphemerisEngine(const std::string& data_path);
    ~EphemerisEngine();

    /**
     * @brief Gezegen konumunu hesaplar.
     * C++17 std::optional ile hata yonetimi yapilir.
     */
    std::optional<PlanetPosition> get_planet_pos(Planets planet, double lat, double lon);

private:
    std::string m_dataPath;
};

} // namespace orbital_edge
