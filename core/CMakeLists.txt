# CMake for OrbitalEdge Core
add_library(orbital_edge_core SHARED
    src/ephemeris_engine.cpp
    src/lunar_engine.cpp
)

target_include_directories(orbital_edge_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Installation
install(TARGETS orbital_edge_core
    EXPORT OrbitalEdgeTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
