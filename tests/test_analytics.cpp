#include <gtest/gtest.h>
#include "astronomy_utils.hpp"
#include "ephemeris_engine.hpp"

using namespace orbital_edge;
using namespace orbital_edge::astronomy;

/**
 * @brief Temel koordinat dönüsum testleri.
 */
TEST(AstronomyUtilsTest, EclipticToEquatorial) {
    double ra, dec;
    // 0,0 koordinatlari 0,0 dönmeli (epsilon dikkate alinarak)
    ecliptic_to_equatorial(0.0, 0.0, 23.439, ra, dec);
    EXPECT_NEAR(ra, 0.0, 0.001);
    EXPECT_NEAR(dec, 0.0, 0.001);
}

/**
 * @brief Julian Tarihi hesaplama dogrulugu.
 */
TEST(AstronomyUtilsTest, JulianDateCurrent) {
    double jd = get_current_julian_date();
    EXPECT_GT(jd, 2460000.0); // 2024+ yillari icin makul bir deger
}

/**
 * @brief Motorun gezegen konumlarini dondurup gondermediginin testi.
 */
TEST(EphemerisEngineTest, GetPlanetPosition) {
    EphemerisEngine engine("/tmp/data");
    auto pos = engine.get_planet_pos(Planets::SUN, 41.0, 29.0);
    
    ASSERT_TRUE(pos.has_value());
    EXPECT_GE(pos->zodiac_degree, 0.0);
    EXPECT_LT(pos->zodiac_degree, 360.0);
    EXPECT_FALSE(pos->sign.empty());
}
