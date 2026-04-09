cmake_minimum_required(VERSION 3.10)
project(OrbitalEdge VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization for ARM64 (Jetson / RPi)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    add_compile_options(-march=armv8-a+simd -O3)
    message(STATUS "Optimizing for ARM64 architecture")
endif()

# Core Engine
add_subdirectory(core)

# Bindings (Optional / Placeholder)
# add_subdirectory(bindings)

# Installation
install(EXPORT OrbitalEdgeTargets
    FILE OrbitalEdgeTargets.cmake
    NAMESPACE OrbitalEdge::
    DESTINATION lib/cmake/OrbitalEdge
)
