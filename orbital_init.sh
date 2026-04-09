#!/bin/bash

echo "===================================================="
echo "   OrbitalEdge v1.2.0-STABLE Kurulum Betigi"
echo "===================================================="

# Bagimliliklari kontrol et
command -v cmake >/dev/null 2>&1 || { echo >&2 "Hata: cmake kurulu degil."; exit 1; }
command -v git >/dev/null 2>&1 || { echo >&2 "Hata: git kurulu degil."; exit 1; }

echo "[1/4] Derleme dizini olusturuluyor..."
mkdir -p build
cd build

echo "[2/4] CMake yapilandirmasi baslatiliyor..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo "[3/4] Proje derleniyor (Multi-core)..."
make -j$(nproc)

echo "[4/4] Testler calistiriliyor..."
ctest --output-on-failure

echo "===================================================="
echo " Kurulum Tamamlandi! './build/orbital_cli' ile baslayabilirsiniz."
echo "===================================================="
