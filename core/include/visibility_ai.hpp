#pragma once

#include <vector>
#include <map>
#include <string>

namespace orbital_edge {
namespace analytics {

/**
 * @brief Görünürlük olasılığını hesaplayan yapay zeka modülü.
 */
class VisibilityAI {
public:
    /**
     * @brief Konum, saat ve atmosferik verilere göre gözlem kalitesini tahmin eder.
     * @return 0.0 - 1.0 arası olasılık değeri.
     */
    static double predict_observation_quality(double lat, double alt, double humidity) {
        // Basit bir karar agacı / MLP simülasyonu
        double score = 1.0;
        
        if (alt < 10.0) score *= 0.2; // Ufuk çizgisine çok yakınsa kalite düser
        if (humidity > 80.0) score *= 0.5; // Yüksek nem pus yaratır
        
        return score;
    }

    /**
     * @brief Gezegenler için anlık "Gözlemlenebilirlik" raporu üretir.
     */
    static std::string get_recommendation(double score) {
        if (score > 0.8) return "Kritik: Mükemmel Gözlem Koşulları!";
        if (score > 0.5) return "Uygun: Gözlem Yapılabilir.";
        return "Zayıf: Atmosferik Engeller Yüksek.";
    }
};

} // namespace analytics
} // namespace orbital_edge
