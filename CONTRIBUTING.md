# OrbitalEdge'e Katkıda Bulunma

OrbitalEdge geliştirici topluluğuna hoş geldiniz! Çevrimdışı, uç birim tabanlı astronomik zekanın geleceğini inşa ediyoruz.

## Geliştirme Standartları
- **Çekirdek Motor (C++17)**: Performans kritiktir. Sıcak yollarda (hot path) gereksiz heap ayırmalarından (allocation) kaçının.
- **Mikro-Ayak İzi**: Bellek kullanımının gömülü sistemler için öngörülebilir olduğundan emin olun.
- **Donanım Uyumluluğu**: ARM64 (Jetson/RPi) için optimize etsek de, çekirdek mantığı taşınabilir kalmalıdır.

## İş Akışı
1. Depoyu forklayın.
2. Özellik dalınızı oluşturun (`git checkout -b ozellik/HarikaOzellik`).
3. Değişikliklerinizi commit edin (`git commit -m 'HarikaOzellik Ekle'`).
4. Dalınıza pushlayın (`git push origin ozellik/HarikaOzellik`).
5. Bir Çekme İsteği (Pull Request) açın.

## Kod Stili
- C++ için `clang-format` (LLVM stili) kullanın.
- Python için `flake8` kurallarına uyun.
- Rust için `cargo fmt` ve `clippy` kullanın.
