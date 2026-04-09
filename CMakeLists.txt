cmake_minimum_required(VERSION 3.10)
project(OrbitalEdge VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11
  GIT_TAG        v2.10.4
)
FetchContent_MakeAvailable(pybind11)

# Optimization for ARM64 (Jetson / RPi)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    add_compile_options(-march=armv8-a+simd -O3)
    message(STATUS "Optimizing for ARM64 architecture")
endif()

# Core Engine
add_subdirectory(core)

# Tests
enable_testing()
add_executable(test_astronomy tests/test_astronomy.cpp)
target_include_directories(test_astronomy PRIVATE core/include)
add_test(NAME AstronomyTest COMMAND test_astronomy)

# Python Bindings
pybind11_add_module(orbital_edge_python bindings/python/src/binding.cpp)
target_link_libraries(orbital_edge_python PRIVATE orbital_edge_core)
target_include_directories(orbital_edge_python PRIVATE core/include)

# CLI Tool
add_executable(orbital_cli tools/orbital_cli.cpp)
target_link_libraries(orbital_cli PRIVATE orbital_edge_core)
target_include_directories(orbital_cli PRIVATE core/include)

# Installation
install(EXPORT OrbitalEdgeTargets
    FILE OrbitalEdgeTargets.cmake
    NAMESPACE OrbitalEdge::
    DESTINATION lib/cmake/OrbitalEdge
)
