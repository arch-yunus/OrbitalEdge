#pragma once

#include <string>
#include <vector>
#include "ephemeris_engine.hpp"

namespace orbital_edge {
namespace hardware {

/**
 * @brief E-Ink ve OLED ekranlar icin soyut surucu katmani.
 */
class DisplayDriver {
public:
    virtual ~DisplayDriver() = default;

    /**
     * @brief Ekrani temizler.
     */
    virtual void clear() = 0;

    /**
     * @brief Astronomik verileri ekrana cizer.
     */
    virtual void draw_celestial_data(const std::vector<std::pair<std::string, PlanetPosition>>& data) = 0;

    /**
     * @brief E-Ink ekranini gunceller (Refresh).
     */
    virtual void refresh() = 0;
};

/**
 * @brief Waveshare v.b. E-Ink ekranlar icin ornek kurgu.
 */
class EInkDriver : public DisplayDriver {
public:
    void clear() override {
        // Donanima ozel temizleme komutlari
    }

    void draw_celestial_data(const std::vector<std::pair<std::string, PlanetPosition>>& data) override {
        // Font Isleme ve Sembol Cizimi
    }

    void refresh() override {
        // E-Ink tam ekran tazeleme
    }
};

} // namespace hardware
} // namespace orbital_edge
