#include <emscripten/bind.h>
#include "ephemeris_engine.hpp"
#include "satellite_engine.hpp"

using namespace emscripten;
using namespace orbital_edge;

/**
 * @brief WebAssembly (Wasm) icin JavaScript köprüsü.
 */
EMSCRIPTEN_BINDINGS(orbital_edge_wasm) {
    
    value_object<PlanetPosition>("PlanetPosition")
        .field("zodiacDegree", &PlanetPosition::zodiac_degree)
        .field("altitude", &PlanetPosition::altitude)
        .field("azimuth", &PlanetPosition::azimuth)
        .field("sign", &PlanetPosition::sign);

    class_<EphemerisEngine>("EphemerisEngine")
        .constructor<std::string>()
        .function("getPlanetPos", &EphemerisEngine::get_planet_pos);
        
    class_<satellites::SatelliteEngine>("SatelliteEngine")
        .constructor<>()
        .function("getIssTle", &satellites::SatelliteEngine::get_iss_tle)
        .function("calculatePosition", &satellites::SatelliteEngine::calculate_position);
}
