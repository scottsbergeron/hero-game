#pragma once
#include "../interfaces/ILevel.h"
#include "Player.h"
#include <memory>
#include <vector>
#include "../rendering/LightSource.h"

class Level : public ILevel {
private:
    std::vector<std::unique_ptr<IGameObject>> gameObjects;
    std::unique_ptr<Player> player;
    std::unique_ptr<LightSource> sun;

public:
    void Initialize() override {
        // Create sun light source
        sun = std::make_unique<LightSource>(
            glm::vec3(10.0f, 10.0f, 10.0f),  // Position high in the sky
            glm::vec3(1.0f, 0.95f, 0.8f),    // Slightly warm sunlight color
            0.2f,                             // Ambient strength
            0.6f,                             // Diffuse strength
            0.8f                              // Specular strength
        );

        // Create player at center of screen with z=0
        player = std::make_unique<Player>(0.0f, 0.0f, 0.0f);
        gameObjects.push_back(std::make_unique<Player>(*player));
    }

    void Update() override {
        for (auto& obj : gameObjects) {
            obj->Update();
        }
    }

    void Render(SDL_Renderer* renderer) override {
        for (auto& obj : gameObjects) {
            if (sun) {
                // Apply lighting to each object before rendering
                dynamic_cast<Player*>(obj.get())->applyLighting(*sun);
            }
            obj->Render(renderer);
        }
    }

    void Cleanup() override {
        gameObjects.clear();
    }
};
