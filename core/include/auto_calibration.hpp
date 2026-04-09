#pragma once

#include <iostream>
#include <string>
#include <functional>
#include "sensor_interface.hpp"
#include "logger.hpp"

namespace orbital_edge {
namespace services {

/**
 * @brief Otonom Kalibrasyon Servisi.
 * Ağ üzerinden veya GPS modüllerinden gelen veriye göre motoru konfigüre eder.
 */
class AutoCalibrationService {
public:
    AutoCalibrationService(hardware::SensorInterface& sensors) : m_sensors(sensors) {}

    /**
     * @brief Uzak bir API'den (veya GPS) konumu cekip sensör katmanini günceller.
     */
    void sync_location(double mock_lat, double mock_lon) {
        utils::Logger::log(utils::LogLevel::INFO, "Otonom konum senkronizasyonu baslatıldı...");
        
        hardware::SensorData data;
        data.latitude = mock_lat;
        data.longitude = mock_lon;
        
        m_sensors.update_data(data);
        
        utils::Logger::log(utils::LogLevel::INFO, "Konum basarıyla guncellendi: " + 
                          std::to_string(mock_lat) + ", " + std::to_string(mock_lon));
    }

private:
    hardware::SensorInterface& m_sensors;
};

} // namespace services
} // namespace orbital_edge
