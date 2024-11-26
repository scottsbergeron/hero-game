# Hero Game

A 3D game built using SDL2 and OpenGL, featuring modern graphics programming concepts including shader-based rendering and dynamic lighting.

## Features

- 3D Rendering with OpenGL
- Player-controlled cube with WASD movement
- Dynamic lighting system with a simulated sun
- Modern shader-based graphics pipeline
- Cross-platform support (Windows/Linux)

## Technical Stack

- SDL2 for window management and input handling
- OpenGL 3.3 Core Profile for 3D graphics
- GLEW for OpenGL extension loading
- GLM for mathematics and 3D transformations
- Modern C++ with smart pointers and RAII

## Development Requirements

- Docker Desktop
- Git
- Visual Studio Code (recommended)
- PowerShell (Windows)
- X Server for Windows (VcXsrv recommended)

## Project Structure

- `src/` - Source code
  - `game/` - Game logic and objects
  - `rendering/` - Graphics and shader systems
  - `interfaces/` - Abstract interfaces
- `assets/` - Game resources
  - `shaders/` - GLSL shader programs
- `scripts/` - Build and run scripts

## Getting Started

1. Start the build server:
```bash
docker-compose up -d
```
2. Build the game:
```bash
docker-compose exec game-dev bash
./scripts/build.sh
```

## Running the Game

### Windows

```powershell
.\build\game.exe
```

## Controls

- W - Move forward
- S - Move backward
- A - Move left
- D - Move right
- ESC - Exit game

## Current Development Status

The game currently features a 3D cube that can be moved around in a 3D space, with a sun-like light source providing dynamic lighting. The rendering system uses modern OpenGL features with vertex and fragment shaders for realistic lighting calculations.

