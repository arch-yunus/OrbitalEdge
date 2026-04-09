#include <iostream>
#include <cassert>
#include "astronomy_utils.hpp"

using namespace orbital_edge::astronomy;

void test_julian_date() {
    // J2000.0 (1 Ocak 2000, 12:00 UTC)
    double jd = calculate_julian_date(2000, 1, 1, 12.0);
    assert(std::abs(jd - 2451545.0) < 0.0001);
    std::cout << "[Test PASSED] Julian Tarihi (J2000.0) dogrulandi." << std::endl;
}

void test_coordinate_transform() {
    double ra, dec;
    // 0 derece boylam, 0 derece enlem, 23.44 derece epsilon
    ecliptic_to_equatorial(0.0, 0.0, 23.44, ra, dec);
    assert(std::abs(ra - 0.0) < 0.0001);
    assert(std::abs(dec - 0.0) < 0.0001);
    std::cout << "[Test PASSED] Koordinat donusumu (Ekinoks) dogrulandi." << std::endl;
}

int main() {
    test_julian_date();
    test_coordinate_transform();
    return 0;
}
