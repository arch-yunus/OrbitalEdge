#pragma once

#include <vector>
#include <map>

namespace orbital_edge {
namespace astronomy {

/**
 * @brief VSOP87D terimi (Amplitüd, Faz, Frekans).
 */
struct VSOPTerm {
    double A; // Amplitüd
    double B; // Faz
    double C; // Frekans
};

/**
 * @brief Her gezegen için L (Boylam), B (Enlem), R (Yarıçap) serileri.
 * Bellek tasarrufu için sadece temel L0 ve L1 serileri tutulmaktadır.
 */
struct VSOPSeries {
    std::vector<VSOPTerm> L0;
    std::vector<VSOPTerm> L1;
};

/**
 * @brief Gezegenler için basitleştirilmiş VSOP87 katsayıları matrisi.
 */
class VSOPData {
public:
    static VSOPSeries get_planet_series(int planet_index) {
        // İndeksler: 0=Merkür, 1=Venüs, 2=Dünya, 3=Mars, 4=Jüpiter, 5=Satürn, 6=Uranüs, 7=Neptün
        static const std::map<int, VSOPSeries> global_data = {
            {0, { // Merkur
                {{4.4354711, 3.14159, 0}, {0.02056, 4.21, 2608.79}}, // L0
                {{2608.79, 0, 0}} // L1
            }},
            {1, { // Venüs
                {{6.239, 0, 0}, {0.0067, 3.14, 1021.32}}, // L0
                {{1021.32, 0, 0}} // L1
            }},
            {2, { // Dünya (Güneş hesaplamalarında kullanılır)
                {{6.28318, 0, 0}, {0.0167, 4.69, 628.307}}, // L0
                {{628.307, 0, 0}} // L1
            }},
            {3, { // Mars
                {{6.203, 0, 0}, {0.0934, 4.31, 334.06}}, // L0
                {{334.06, 0, 0}} // L1
            }},
            {4, { // Jüpiter
                {{0.599, 0, 0}, {0.0483, 3.48, 52.96}}, // L0
                {{52.96, 0, 0}} // L1
            }},
            {5, { // Satürn
                {{0.874, 0, 0}, {0.0557, 2.76, 21.32}}, // L0
                {{21.32, 0, 0}} // L1
            }}
            // ... Diğer gezegenler benzer yapıda eklenebilir
        };

        if (global_data.count(planet_index)) {
            return global_data.at(planet_index);
        }
        return global_data.at(2); // Varsayılan: Dünya
    }
};

} // namespace astronomy
} // namespace orbital_edge
