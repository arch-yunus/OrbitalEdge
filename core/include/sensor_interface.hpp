#pragma once

#include <string>
#include <optional>

namespace orbital_edge {
namespace hardware {

/**
 * @brief Donanim sensorlerinden (GPS/IMU) veri besleme arayuzu.
 */
struct SensorData {
    std::optional<double> latitude;
    std::optional<double> longitude;
    std::optional<double> altitude_meters;
    
    // IMU Verileri (Euler Acilari)
    std::optional<double> roll;
    std::optional<double> pitch;
    std::optional<double> yaw; // Azimut kalibrasyonu icin kritik
};

class SensorInterface {
public:
    /**
     * @brief Sensör verilerini günceller.
     */
    void update_data(const SensorData& data) {
        m_currentData = data;
    }

    /**
     * @brief Mevcut enlemi döndürür (eğer varsa).
     */
    std::optional<double> get_latitude() const { return m_currentData.latitude; }

private:
    SensorData m_currentData;
};

} // namespace hardware
} // namespace orbital_edge
