#include "ephemeris_engine.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace orbital_edge;

void print_banner() {
    std::cout << "========================================" << std::endl;
    std::cout << "   OrbitalEdge CLI - Gök Cismi Sorgu    " << std::endl;
    std::cout << "========================================" << std::endl;
}

int main(int argc, char** argv) {
    print_banner();

    double lat = 40.99; // Varsayılan: Trabzon
    double lon = 39.71;

    if (argc >= 3) {
        lat = std::stod(argv[1]);
        lon = std::stod(argv[2]);
    }

    std::cout << "[Bilgi] Konum: Enlem=" << lat << ", Boylam=" << lon << "\n" << std::endl;

    EphemerisEngine engine("/opt/orbital_edge/data");

    std::vector<std::pair<std::string, Planets>> target_planets = {
        {"Gunes", Planets::SUN},
        {"Merkur", Planets::MERCURY},
        {"Venus", Planets::VENUS},
        {"Mars", Planets::MARS},
        {"Jupiter", Planets::JUPITER},
        {"Saturn", Planets::SATURN}
    };

    std::cout << std::left << std::setw(10) << "Gezegen" 
              << std::setw(15) << "Zodyak Deg." 
              << std::setw(12) << "Yukseklik" 
              << std::setw(10) << "Burc" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    for (const auto& p : target_planets) {
        auto pos = engine.get_planet_pos(p.second, lat, lon);
        std::cout << std::left << std::setw(10) << p.first 
                  << std::setw(15) << std::fixed << std::setprecision(2) << pos.zodiac_degree 
                  << std::setw(12) << pos.altitude 
                  << std::setw(10) << pos.sign << std::endl;
    }

    std::cout << "\n[Tamamlandi] Tum hesaplamalar sifir gecikme ile yapildi." << std::endl;

    return 0;
}
