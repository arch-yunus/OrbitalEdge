# --- Builder Stage ---
FROM ubuntu:22.04 AS builder

LABEL maintainer="Yunus <arch-yunus>"
ENV DEBIAN_FRONTEND=noninteractive

# Bagimliliklari kur
RUN apt-get update && apt-get install -y \
    cmake build-essential git python3-dev \
    libssl-dev pkg-config

WORKDIR /app
COPY . .

# OrbitalEdge Core ve Bindings derle
RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make -j$(nproc)

# --- Runtime Stage ---
FROM ubuntu:22.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    python3 python3-pip libssl3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/orbital_edge

# Binaries ve kutuphaneleri builder'dan kopyala
COPY --from=builder /app/build/orbital_cli ./bin/
COPY --from=builder /app/build/orbital_bench ./bin/
COPY --from=builder /app/build/*.so ./lib/
COPY --from=builder /app/web ./web

# Portlar (Dashboard icin)
EXPOSE 8080

ENV PATH="/opt/orbital_edge/bin:${PATH}"
ENV LD_LIBRARY_PATH="/opt/orbital_edge/lib:${LD_LIBRARY_PATH}"

CMD ["orbital_cli", "40.99", "39.71"]
