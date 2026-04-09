#[cxx::bridge(namespace = "orbital_edge")]
mod ffi {
    /// Gezegen konum verilerini tutan yapı.
    struct PlanetPosition {
        zodiac_degree: f64, // Zodyak boylamı (derece)
        altitude: f64,      // Yükseklik
        azimuth: f64,       // Azimut
        sign: String,       // Burç adı
    }

    unsafe extern "C++" {
        include!("orbital_edge/core/include/ephemeris_engine.hpp");

        /// C++ EphemerisEngine sınıfının Rust yansıması.
        type EphemerisEngine;

        /// Yeni bir EphemerisEngine örneği oluşturur.
        fn new_ephemeris_engine(data_path: &str) -> UniquePtr<EphemerisEngine>;

        /// Belirli bir gezegenin konumunu hesaplar.
        fn get_planet_pos(
            self: &EphemerisEngine,
            planet: i32,
            lat: f64,
            lon: f64,
        ) -> PlanetPosition;
    }
}

/// Güneş konumunu hesaplamak için Rust yardımcı fonksiyonu.
pub fn calculate_sun(engine: &ffi::EphemerisEngine, lat: f64, lon: f64) -> ffi::PlanetPosition {
    engine.get_planet_pos(0, lat, lon)
}
