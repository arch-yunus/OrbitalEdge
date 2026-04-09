#include "ephemeris_engine.hpp"
#include <iostream>
#include <chrono>
#include <vector>

using namespace orbital_edge;

int main() {
    std::cout << "--- OrbitalEdge Performans Kiyaslama (Benchmarking) ---" << std::endl;
    
    EphemerisEngine engine("/tmp/data");
    
    const int iterations = 10000;
    auto start = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < iterations; ++i) {
        // Rastgele (?) veri ile hesaplama yap
        engine.get_planet_pos(Planets::SUN, 40.0 + (i % 10), 30.0 + (i % 10));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double avg_latency = static_cast<double>(duration.count()) / iterations;
    
    std::cout << "[Sonuc] Toplam Sure: " << duration.count() << " us" << std::endl;
    std::cout << "[Sonuc] Iterasyon Sayisi: " << iterations << std::endl;
    std::cout << "[Sonuc] Ortalama Gecikme: " << avg_latency << " us" << std::endl;
    
    if (avg_latency < 50.0) {
        std::cout << "[INFO] Performans Seviyesi: KRITIK SIFIR GECIKME (Ultra-Fast)" << std::endl;
    }

    return 0;
}
