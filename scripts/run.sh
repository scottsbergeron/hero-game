#!/bin/bash
if [ -f "./build/game.exe" ]; then
    ./build/game.exe
else
    ./build/game
fi
