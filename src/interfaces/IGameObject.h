#pragma once
#include <SDL2/SDL.h>

class IGameObject {
public:
    virtual ~IGameObject() = default;
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
};
