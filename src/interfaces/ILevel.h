#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "IGameObject.h"

class ILevel {
public:
    virtual ~ILevel() = default;
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void Cleanup() = 0;
};
