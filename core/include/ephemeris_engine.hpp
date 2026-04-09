#pragma once

#include <string>
#include <vector>

namespace orbital_edge {

enum class Planets {
    SUN = 0,
    MOON = 1,
    MERCURY = 2,
    VENUS = 3,
    MARS = 4,
    JUPITER = 5,
    SATURN = 6,
    URANUS = 7,
    NEPTUNE = 8,
    PLUTO = 9
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

    PlanetPosition get_planet_pos(Planets planet, double lat, double lon);

private:
    std::string m_dataPath;
    // Internal ephemeris data structures
};

} // namespace orbital_edge
