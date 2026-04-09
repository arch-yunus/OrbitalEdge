# Contributing to OrbitalEdge

Welcome to the OrbitalEdge developer community! We are building the future of offline, edge-based astronomical intelligence.

## Development Standards
- **Core Engine (C++17)**: Performance is critical. Avoid unnecessary heap allocations in the hot path.
- **Micro-footprint**: Ensure that memory usage remains predictable for embedded systems.
- **Hardware Agnostic**: While we optimize for ARM64 (Jetson/RPi), the core logic should remain portable.

## Workflow
1. Fork the repo.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

## Code Style
- Use `clang-format` (LLVM style) for C++.
- Follow `flake8` for Python.
- Use `cargo fmt` and `clippy` for Rust.
