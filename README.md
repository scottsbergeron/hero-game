# Hero Game

A game built using SDL2 (Simple DirectMedia Layer 2), a cross-platform development library designed to provide low-level access to audio, keyboard, mouse, joystick, and graphics hardware.

## Development Requirements

- Docker Desktop
- Git
- Visual Studio Code (recommended)
- PowerShell (Windows)
- X Server for Windows (VcXsrv recommended)

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

