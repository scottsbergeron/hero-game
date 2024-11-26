#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_main.h>
#include <iostream>
#include "game/Game.h"

int SDL_main(int argc, char* argv[]) {
    Game game;

    if (!game.Initialize()) {
        return 1;
    }

    // Game loop
    while (game.Running()) {
        game.ProcessInput();
        game.Update();
        game.Render();
    }

    game.Cleanup();
    return 0;
}
