#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "ephemeris_engine.hpp"

using namespace orbital_edge;

/**
 * @brief Terminal tabanli interaktif gökyüzü dashboard'u.
 * (Gercek uygulamada ncurses kutuphanesi gerektirir, 
 * burada standart çıktı ile simüle edilmistir).
 */
void draw_ui(const std::vector<std::pair<std::string, PlanetPosition>>& planets) {
    std::cout << "\033[2J\033[1;1H"; // Ekranı temizle
    std::cout << "====================================================" << std::endl;
    std::cout << " || ORBITAL EDGE - Terminal Sky Dashboard (v1.2) ||" << std::endl;
    std::cout << "====================================================" << std::endl;
    
    for (const auto& p : planets) {
        std::cout << " [ " << p.first << " ] " 
                  << " Burc: " << p.second.sign
                  << " | Alt: " << p.second.altitude << " deg"
                  << " | Az: " << p.second.azimuth << " deg" << std::endl;
    }
    
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << " [Q] Cikis | [R] Yenile | [L] Konum Degistir" << std::endl;
}

int main() {
    EphemerisEngine engine("/tmp/data");
    double lat = 41.0, lon = 29.0;

    while (true) {
        std::vector<std::pair<std::string, PlanetPosition>> results;
        auto sun = engine.get_planet_pos(Planets::SUN, lat, lon);
        if (sun) results.push_back({"GUNES", *sun});

        auto moon = engine.get_planet_pos(Planets::MOON, lat, lon);
        if (moon) results.push_back({"AY", *moon});

        draw_ui(results);
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // Klavye girisi simulasyonu veya gercek ncurses input dongusu buraya gelir.
    }

    return 0;
}
