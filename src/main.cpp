#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_main.h>
#include <iostream>

class Game {
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

public:
    Game() {
        isRunning = false;
        window = nullptr;
        renderer = nullptr;
        font = nullptr;
        textSurface = nullptr;
        textTexture = nullptr;
    }

    bool Initialize() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        // Initialize SDL_ttf
        if (TTF_Init() != 0) {
            std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
            return false;
        }

        // Create window
        window = SDL_CreateWindow(
            "Hello World",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (!window) {
            std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
            return false;
        }

        // Create renderer
        renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

        if (!renderer) {
            std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
            return false;
        }

        isRunning = true;
        return true;
    }

    void ProcessInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        isRunning = false;
                    break;
                default:
                    break;
            }
        }
    }

    void Update() {
        // Add game logic here
    }

    void Render() {
        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Add rendering code here

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    void Cleanup() {
        // Cleanup SDL resources
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool Running() const { 
        return isRunning; 
    }
};

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
