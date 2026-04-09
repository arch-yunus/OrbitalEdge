#include "satellite_engine.hpp"
#include <cmath>
#include <iostream>

namespace orbital_edge {
namespace satellites {

SatelliteEngine::SatelliteEngine() {}

TLE SatelliteEngine::get_iss_tle() {
    return {
        "ISS (ZARYA)",
        "1 25544U 98067A   24099.55462560  .00016584  00000-0  30048-3 0  9997",
        "2 25544  51.6416  24.3851 0004456  40.4561  54.6712 15.49528456448201"
    };
}

SatellitePosition SatelliteEngine::calculate_position(const TLE& tle, double jd, double obs_lat, double obs_lon) {
    SatellitePosition pos;
    
    // Basitlestirilmis yorunge hesabi (SGP4 iskeleti)
    // TLE verisinden egiklik, az boylam ve eksantriklik cikarilir.
    
    pos.latitude = 51.6; // Örnek ISS enlemi
    pos.longitude = -2.3;
    pos.altitude_km = 420.0;
    pos.azimuth = 180.0;
    pos.elevation = 45.0;
    
    return pos;
}

} // namespace satellites
} // namespace orbital_edge
