#pragma once

#include <vector>

namespace orbital_edge {
namespace astronomy {

struct VSOPTerm {
    double A; // Amplitüd
    double B; // Faz
    double C; // Frekans
};

/**
 * @brief VSOP87D teorisi (Heliosentrik küresel koordinatlar) için basitleştirilmiş veri yapısı.
 * L (Boylam), B (Enlem), R (Yarıçap) serileri.
 */
struct VSOPSeries {
    std::vector<VSOPTerm> L0;
    std::vector<VSOPTerm> L1;
    // ... Diğer seriler (L2, L3, B0, B1, R0, R1)
};

/**
 * @brief Örnek: Dünya (veya Güneş için tersi) L0 serisi katsayıları.
 * Not: Bu değerler sadece örnektir, gerçek yüksek doğruluklu hesaplama için 
 * tam VSOP87 tablosu kullanılır.
 */
inline VSOPSeries get_earth_series() {
    VSOPSeries earth;
    // L0: Ortalama boylam terimleri
    earth.L0 = {
        {6.283185307, 0, 0},         // Const
        {0.033416, 4.691, 628.307},  // Solar influence
        {0.000349, 4.53, 1256.61}
    };
    earth.L1 = {
        {628.307584, 0, 0}
    };
    return earth;
}

} // namespace astronomy
} // namespace orbital_edge
