#include "ephemeris_engine.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace orbital_edge;

void print_banner() {
    std::cout << "========================================" << std::endl;
    std::cout << "   OrbitalEdge CLI - Gök Cismi Sorgu    " << std::endl;
    std::cout << "========================================" << std::endl;
}

/**
 * @brief ASCII Gökyüzü Haritası (Sky Map) oluşturur.
 */
void print_sky_map(const std::vector<std::pair<std::string, PlanetPosition>>& planets) {
    const int width = 60;
    const int height = 20;
    std::vector<std::string> map(height, std::string(width, ' '));

    // Ufuk çizgisi (Horizon)
    for (int x = 0; x < width; ++x) map[height - 1][x] = '_';

    for (const auto& p : planets) {
        if (p.second.altitude < 0) continue; // Ufuk altı görünmez

        // Azimut (0-360) -> X (0-width)
        int x = static_cast<int>((p.second.azimuth / 360.0) * (width - 1));
        // Yükseklik (0-90) -> Y (height-1 -> 0)
        int y = static_cast<int>((height - 1) - (p.second.altitude / 90.0) * (height - 1));

        if (x >= 0 && x < width && y >= 0 && y < height) {
            map[y][x] = p.first[0]; // Gezegenin ilk harfini koy
        }
    }

    std::cout << "\n--- ASCII GOKYUZU HARITASI (N-E-S-W) ---" << std::endl;
    for (const auto& row : map) {
        std::cout << "| " << row << " |" << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}

int main(int argc, char** argv) {
    print_banner();

    double lat = 40.99;
    double lon = 39.71;

    if (argc >= 3) {
        lat = std::stod(argv[1]);
        lon = std::stod(argv[2]);
    }

    std::cout << "[Bilgi] Konum: Enlem=" << lat << ", Boylam=" << lon << "\n" << std::endl;

    EphemerisEngine engine("/opt/orbital_edge/data");

    std::vector<std::pair<std::string, Planets>> target_keys = {
        {"Gunes", Planets::SUN},
        {"Ay", Planets::MOON},
        {"Merkur", Planets::MERCURY},
        {"Venus", Planets::VENUS},
        {"Mars", Planets::MARS},
        {"Jupiter", Planets::JUPITER},
        {"Saturn", Planets::SATURN}
    };

    std::vector<std::pair<std::string, PlanetPosition>> results;
    std::cout << std::left << std::setw(10) << "Gezegen" 
              << std::setw(15) << "Zodyak Deg." 
              << std::setw(12) << "Yukseklik" 
              << std::setw(10) << "Burc" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    for (const auto& p : target_keys) {
        auto pos = engine.get_planet_pos(p.second, lat, lon);
        results.push_back({p.first, pos});
        std::cout << std::left << std::setw(10) << p.first 
                  << std::setw(15) << std::fixed << std::setprecision(2) << pos.zodiac_degree 
                  << std::setw(12) << pos.altitude 
                  << std::setw(10) << pos.sign << std::endl;
    }

    print_sky_map(results);

    std::cout << "\n[Tamamlandi] Tum hesaplamalar sifir gecikme ile yapildi." << std::endl;

    return 0;
}
