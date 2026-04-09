#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

namespace orbital_edge {
namespace utils {

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

/**
 * @brief Uç birimler için optimize edilmiş, hafif loglama sınıfı.
 */
class Logger {
public:
    static void log(LogLevel level, const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::cout << "[" << std::put_time(std::localtime(&time), "%H:%M:%S") << "] ";
        
        switch (level) {
            case LogLevel::INFO:    std::cout << "[INFO]    "; break;
            case LogLevel::WARNING: std::cout << "[WARNING] "; break;
            case LogLevel::ERROR:   std::cout << "[ERROR]   "; break;
            case LogLevel::DEBUG:   std::cout << "[DEBUG]   "; break;
        }
        
        std::cout << message << std::endl;
    }
};

} // namespace utils
} // namespace orbital_edge
