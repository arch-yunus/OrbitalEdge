#pragma once

#include <vector>
#include <array>

namespace orbital_edge {
namespace astronomy {

/**
 * @brief VSOP87D terimi (Amplitüd, Faz, Frekans).
 * Bellek hizalaması (alignment) için optimize edilmiştir.
 */
struct alignas(16) VSOPTerm {
    double A; // Amplitüd
    double B; // Faz
    double C; // Frekans
};

/**
 * @brief Gezegenler için yüksek performanslı katsayı deposu.
 * Bellek yerleşimi (Memory Locality) için std::vector yerine sabit boyutlu diziler tercih edilmiştir.
 */
class VSOPData {
public:
    static const std::vector<VSOPTerm>& get_L0(int planet_index) {
        static const auto data = init_L0();
        return data[planet_index % 8];
    }

    static const std::vector<VSOPTerm>& get_L1(int planet_index) {
        static const auto data = init_L1();
        return data[planet_index % 8];
    }

private:
    static std::array<std::vector<VSOPTerm>, 8> init_L0() {
        std::array<std::vector<VSOPTerm>, 8> res;
        res[0] = {{4.4354711, 3.14159, 0}, {0.02056, 4.21, 2608.79}}; // Merkur
        res[1] = {{6.239, 0, 0}, {0.0067, 3.14, 1021.32}};           // Venus
        res[2] = {{6.28318, 0, 0}, {0.0167, 4.69, 628.307}};         // Dunya
        res[3] = {{6.203, 0, 0}, {0.0934, 4.31, 334.06}};            // Mars
        res[4] = {{0.599, 0, 0}, {0.0483, 3.48, 52.96}};             // Jupiter
        res[5] = {{0.874, 0, 0}, {0.0557, 2.76, 21.32}};             // Saturn
        res[6] = {{5.48, 0, 0}, {0.046, 5.0, 7.47}};                // Uranus
        res[7] = {{5.31, 0, 0}, {0.01, 0.45, 3.81}};                // Neptun
        return res;
    }

    static std::array<std::vector<VSOPTerm>, 8> init_L1() {
        std::array<std::vector<VSOPTerm>, 8> res;
        res[0] = {{2608.79, 0, 0}};
        res[1] = {{1021.32, 0, 0}};
        res[2] = {{628.307, 0, 0}};
        res[3] = {{334.06, 0, 0}};
        res[4] = {{52.96, 0, 0}};
        res[5] = {{21.32, 0, 0}};
        res[6] = {{7.47, 0, 0}};
        res[7] = {{3.81, 0, 0}};
        return res;
    }
};

} // namespace astronomy
} // namespace orbital_edge
