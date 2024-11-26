#pragma once
#include "../interfaces/ILevel.h"
#include "Level.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <GL/glew.h>

class Game {
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unique_ptr<ILevel> currentLevel;
    
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

public:
    Game() {
        isRunning = false;
        window = nullptr;
        renderer = nullptr;
        currentLevel = std::make_unique<Level>();
    }

    bool Initialize() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window = SDL_CreateWindow(
            "3D Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        if (!window) {
            std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            std::cerr << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
            return false;
        }

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Error initializing GLEW" << std::endl;
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        
        currentLevel->Initialize();
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
        currentLevel->Update();
    }

    void Render() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentLevel->Render(renderer);

        SDL_GL_SwapWindow(window);
    }

    void Cleanup() {
        currentLevel->Cleanup();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool Running() const { return isRunning; }
};
