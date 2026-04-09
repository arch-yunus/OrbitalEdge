# OrbitalEdge Proje Ozeti (v1.0.0)

OrbitalEdge, uç birim cihazlar için optimize edilmiş, yüksek hassasiyetli bir astronomik hesaplama ekosistemidir.

### 🗺️ Yol Haritasi ve Mevcut Durum

*   **Aşama 1: Temel Motor**: Julian Tarihi, GMST ve Koordinat Dönüşüm araçları (Tamamlandı).
*   **Aşama 2: Çoklu Gezegen ve Python**: VSOP87 Tüm Gezegenler, Pybind11 ve CLI Aracı (Tamamlandı).
*   **Aşama 3: Hassasiyet ve IoT**: ELP-2000 Ay Motoru, Refraksiyon, MQTT ve Sky Map (Tamamlandı).
*   **Aşama 4: Görselleştirme ve Optimizasyon**: Web Dashboard, Sensör Arayüzü, Benchmarking (Tamamlandı).
*   **Aşama 5: Dağıtım ve Rust**: Dockerizasyon, Rust FFI, E-Ink HAL ve Logger (Tamamlandı).

### 🛠️ Teknik Standartlar

*   **Dil**: C++17, Python 3.10+, Rust 2021+.
*   **Mimari**: Modüler 7-Katmanlı Yapı.
*   **Hedef Donanim**: NVIDIA Jetson, Raspberry Pi, ARM64/AMD64.

## 00 - Meta ve Yönetişim
* [Giriş](README.md)
* [Lisans](LICENSE)
* [Katkıda Bulunma](CONTRIBUTING.md)

## 01 - Çekirdek Motor (C++17)
* [Mimari Genel Bakış](core/README.md)
* [Ephemeris Hesaplama Mantığı](core/include/astronomy_utils.hpp)
* [Bellek Yönetimi](core/memory.md)

## 02 - Arayüzler ve Bağlantılar
* [Python (Pybind11)](bindings/python/README.md)
* [Rust (cxx)](bindings/rust/README.md)

## 03 - Robotik Entegrasyon (ROS2)
* [Telemetri Düğümü](ros2_ws/src/orbital_edge_ros/src/telemetry_node.cpp)
* [Konu (Topic) Spesifikasyonları](docs/ros2/topics.md)

## 04 - Veri Ekosistemi
* [Ephemeris Veri Sıkıştırma](data/compression.md)
* [Çevrimdışı Veritabanı Yapısı](data/structure.md)

## 05 - Donanım Optimizasyonları
* [Jetson Nano / Orin](docs/hardware/jetson.md)
* [Raspberry Pi 4/5](docs/hardware/rpi.md)

## 06 - Araştırma ve Vakalar
* [Gök Cismleriyle Otonom Navigasyon](research/navigation.md)
* [Düşük Güçlü IoT Dağıtımları](research/iot.md)
