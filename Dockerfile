FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    mingw-w64 \
    pkg-config \
    wget \
    gcc-mingw-w64-x86-64 \
    g++-mingw-w64-x86-64 \
    && rm -rf /var/lib/apt/lists/*

# Download and install SDL2 for MinGW
RUN wget https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-mingw.tar.gz && \
    tar xzf SDL2-devel-2.28.5-mingw.tar.gz && \
    cp -r SDL2-2.28.5/x86_64-w64-mingw32 /usr && \
    rm -rf SDL2-2.28.5 SDL2-devel-2.28.5-mingw.tar.gz

# Download and install SDL2_ttf for MinGW
RUN wget https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-mingw.tar.gz && \
    tar xzf SDL2_ttf-devel-2.20.2-mingw.tar.gz && \
    cp -r SDL2_ttf-2.20.2/x86_64-w64-mingw32 /usr && \
    rm -rf SDL2_ttf-2.20.2 SDL2_ttf-devel-2.20.2-mingw.tar.gz

WORKDIR /game
