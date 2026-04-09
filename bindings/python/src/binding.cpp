#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ephemeris_engine.hpp"

namespace py = pybind11;

PYBIND11_MODULE(orbital_edge_python, m) {
    m.doc() = "OrbitalEdge: Sifir Gecikmeli Astronomik Hesaplama Motoru Python Arayuzu";

    py::enum_<orbital_edge::Planets>(m, "Planets")
        .value("Gunes", orbital_edge::Planets::SUN)
        .value("Ay", orbital_edge::Planets::MOON)
        .value("Merkur", orbital_edge::Planets::MERCURY)
        .value("Venus", orbital_edge::Planets::VENUS)
        .value("Mars", orbital_edge::Planets::MARS)
        .value("Jupiter", orbital_edge::Planets::JUPITER)
        .value("Saturn", orbital_edge::Planets::SATURN)
        .export_values();

    py::class_<orbital_edge::PlanetPosition>(m, "PlanetPosition")
        .def_readwrite("zodiac_degree", &orbital_edge::PlanetPosition::zodiac_degree)
        .def_readwrite("altitude", &orbital_edge::PlanetPosition::altitude)
        .def_readwrite("azimuth", &orbital_edge::PlanetPosition::azimuth)
        .def_readwrite("sign", &orbital_edge::PlanetPosition::sign);

    py::class_<orbital_edge::EphemerisEngine>(m, "EphemerisEngine")
        .def(py::init<const std::string&>())
        .def("get_planet_pos", &orbital_edge::EphemerisEngine::get_planet_pos,
             py::arg("gezegen"), py::arg("enlem"), py::arg("boylam"),
             "Belirlenen gezegenin anlik konum verilerini dondurur.");
}
