#pragma once

#include <vector>
#include <string>
#include <optional>
#include "ephemeris_engine.hpp"

namespace orbital_edge {
namespace analytics {

/**
 * @brief Astronomik olayların (Retrograt, Kavuşum vb.) türleri.
 */
enum class EventType {
    RETROGRADE_START, // Geri hareket başlangıcı
    RETROGRADE_END,   // Geri hareket bitişi
    CONJUNCTION,      // Kavuşum (Gezegenlerin hizalanması)
    MAX_ELONGATION    // Maksimum uzanım
};

struct AstroEvent {
    EventType type;
    double jd;         // Olayın gerçekleştiği Julian Tarihi
    std::string description; // Olay açıklaması
};

/**
 * @brief Gelecekteki astronomik olayları tahmin eden analitik motor.
 */
class EventPredictor {
public:
    EventPredictor(EphemerisEngine& engine);

    /**
     * @brief Belirli bir zaman aralığındaki retrograt (geri hareket) dönemlerini bulur.
     */
    std::vector<AstroEvent> find_retrogrades(Planets planet, double start_jd, double duration_days);

    /**
     * @brief İki gezegen arasındaki kavuşum (conjunction) anlarını tespit eder.
     */
    std::optional<AstroEvent> find_next_conjunction(Planets p1, Planets p2, double start_jd);

private:
    EphemerisEngine& m_engine;
};

} // namespace analytics
} // namespace orbital_edge
