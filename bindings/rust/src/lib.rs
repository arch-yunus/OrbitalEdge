#[cxx::bridge(namespace = "orbital_edge")]
mod ffi {
    struct PlanetPosition {
        zodiac_degree: f64,
        altitude: f64,
        azimuth: f64,
        sign: String,
    }

    unsafe extern "C++" {
        include!("orbital_edge/core/include/ephemeris_engine.hpp");

        type EphemerisEngine;

        fn new_ephemeris_engine(data_path: &str) -> UniquePtr<EphemerisEngine>;
        fn get_planet_pos(
            self: &EphemerisEngine,
            planet: i32,
            lat: f64,
            lon: f64,
        ) -> PlanetPosition;
    }
}

pub fn calculate_sun(engine: &ffi::EphemerisEngine, lat: f64, lon: f64) -> ffi::PlanetPosition {
    engine.get_planet_pos(0, lat, lon)
}
