FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    mingw-w64 \
    pkg-config \
    wget \
    unzip \
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

# Download and install GLEW for MinGW
RUN wget https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip && \
    unzip glew-2.2.0-win32.zip && \
    cp -r glew-2.2.0/include/GL /usr/x86_64-w64-mingw32/include/ && \
    cp glew-2.2.0/bin/Release/x64/glew32.dll /usr/x86_64-w64-mingw32/bin/ && \
    cp glew-2.2.0/lib/Release/x64/glew32.lib /usr/x86_64-w64-mingw32/lib/libglew32.dll.a && \
    rm -rf glew-2.2.0 glew-2.2.0-win32.zip

# Download and install GLM (header-only library)
RUN wget https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip && \
    unzip glm-0.9.9.8.zip && \
    cp -r glm/glm /usr/x86_64-w64-mingw32/include/ && \
    rm -rf glm glm-0.9.9.8.zip

WORKDIR /game
