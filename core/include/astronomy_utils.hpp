#pragma once

#include <cmath>
#include <ctime>

namespace orbital_edge {
namespace astronomy {

constexpr double PI = 3.14159265358979323846;
constexpr double TWO_PI = 2.0 * PI;
constexpr double DEG_TO_RAD = PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / PI;

/**
 * @brief Julian Tarihi (JD) hesaplar.
 */
inline double calculate_julian_date(int year, int month, int day, double hours = 0.0) {
    if (month <= 2) {
        year -= 1;
        month += 12;
    }
    int A = year / 100;
    int B = 2 - A + (A / 4);
    double jd = std::floor(365.25 * (year + 4716)) + std::floor(30.6001 * (month + 1)) + day + B - 1524.5;
    return jd + (hours / 24.0);
}

/**
 * @brief Mevcut sistem zamanı için Julian Tarihi döndürür.
 */
inline double get_current_julian_date() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::gmtime(&t);
    return calculate_julian_date(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
                                now->tm_hour + now->tm_min / 60.0 + now->tm_sec / 3600.0);
}

/**
 * @brief Greenwich Ortalama Yıldız Zamanı (GMST) hesaplar (derece cinsinden).
 */
inline double calculate_gmst(double jd) {
    double T = (jd - 2451545.0) / 36525.0;
    double gmst = 280.46061837 + 360.98564736629 * (jd - 2451545.0) + T * T * (0.000387933 - T / 38710000.0);
    gmst = std::fmod(gmst, 360.0);
    if (gmst < 0) gmst += 360.0;
    return gmst;
}

/**
 * @brief Ekliptik koordinatları Ekvatoral koordinatlara dönüştürür.
 */
inline void ecliptic_to_equatorial(double lon, double lat, double epsilon, double& ra, double& dec) {
    double L = lon * DEG_TO_RAD;
    double B = lat * DEG_TO_RAD;
    double E = epsilon * DEG_TO_RAD;

    double x = std::cos(B) * std::cos(L);
    double y = std::cos(E) * std::cos(B) * std::sin(L) - std::sin(E) * std::sin(B);
    double z = std::sin(E) * std::cos(B) * std::sin(L) + std::cos(E) * std::sin(B);

    ra = std::atan2(y, x) * RAD_TO_DEG;
    dec = std::asin(z) * RAD_TO_DEG;
    if (ra < 0) ra += 360.0;
}

/**
 * @brief Ekvatoral koordinatları Yatay (Alt/Az) koordinatlara dönüştürür.
 */
inline void equatorial_to_horizontal(double ra, double dec, double lat_observer, double lon_observer, double gmst, double& alt, double& az) {
    double LST = gmst + lon_observer; // Local Sidereal Time
    double H = (LST - ra) * DEG_TO_RAD; // Hour Angle
    double D = dec * DEG_TO_RAD;
    double PHI = lat_observer * DEG_TO_RAD;

    double sin_alt = std::sin(D) * std::sin(PHI) + std::cos(D) * std::cos(PHI) * std::cos(H);
    alt = std::asin(sin_alt) * RAD_TO_DEG;

    double cos_az = (std::sin(D) - std::sin(PHI) * sin_alt) / (std::cos(PHI) * std::cos(std::asin(sin_alt)));
    az = std::acos(cos_az) * RAD_TO_DEG;

    if (std::sin(H) > 0) {
        az = 360.0 - az;
    }
}

} // namespace astronomy
} // namespace orbital_edge
