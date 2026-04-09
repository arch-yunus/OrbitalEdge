# Özet

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
