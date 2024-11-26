#pragma once
#include "../interfaces/IGameObject.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../rendering/Shader.h"
#include "../rendering/LightSource.h"

class Player : public IGameObject {
private:
    glm::vec3 position;
    GLuint VBO, VAO;
    Shader shader;
    float speed;

    void setupCube() {
        float vertices[] = {
            // Front face
            -0.5f, -0.5f,  0.5f,  // Bottom-left
             0.5f, -0.5f,  0.5f,  // Bottom-right
             0.5f,  0.5f,  0.5f,  // Top-right
             0.5f,  0.5f,  0.5f,  // Top-right
            -0.5f,  0.5f,  0.5f,  // Top-left
            -0.5f, -0.5f,  0.5f,  // Bottom-left
            
            // Back face
            -0.5f, -0.5f, -0.5f,  // Bottom-left
             0.5f, -0.5f, -0.5f,  // Bottom-right
             0.5f,  0.5f, -0.5f,  // Top-right
             0.5f,  0.5f, -0.5f,  // Top-right
            -0.5f,  0.5f, -0.5f,  // Top-left
            -0.5f, -0.5f, -0.5f,  // Bottom-left

            // Left face
            -0.5f,  0.5f,  0.5f,  // Top-right
            -0.5f,  0.5f, -0.5f,  // Top-left
            -0.5f, -0.5f, -0.5f,  // Bottom-left
            -0.5f, -0.5f, -0.5f,  // Bottom-left
            -0.5f, -0.5f,  0.5f,  // Bottom-right
            -0.5f,  0.5f,  0.5f,  // Top-right

            // Right face
             0.5f,  0.5f,  0.5f,  // Top-left
             0.5f,  0.5f, -0.5f,  // Top-right
             0.5f, -0.5f, -0.5f,  // Bottom-right
             0.5f, -0.5f, -0.5f,  // Bottom-right
             0.5f, -0.5f,  0.5f,  // Bottom-left
             0.5f,  0.5f,  0.5f,  // Top-left

            // Bottom face
            -0.5f, -0.5f, -0.5f,  // Top-right
             0.5f, -0.5f, -0.5f,  // Top-left
             0.5f, -0.5f,  0.5f,  // Bottom-left
             0.5f, -0.5f,  0.5f,  // Bottom-left
            -0.5f, -0.5f,  0.5f,  // Bottom-right
            -0.5f, -0.5f, -0.5f,  // Top-right

            // Top face
            -0.5f,  0.5f, -0.5f,  // Top-right
             0.5f,  0.5f, -0.5f,  // Top-left
             0.5f,  0.5f,  0.5f,  // Bottom-left
             0.5f,  0.5f,  0.5f,  // Bottom-left
            -0.5f,  0.5f,  0.5f,  // Bottom-right
            -0.5f,  0.5f, -0.5f   // Top-right
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

public:
    Player(float x, float y, float z) 
        : position(x, y, z), 
          shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"),
          speed(0.1f) {
        setupCube();
    }

    void Update() override {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        
        if (state[SDL_SCANCODE_W]) position.z -= speed;
        if (state[SDL_SCANCODE_S]) position.z += speed;
        if (state[SDL_SCANCODE_A]) position.x -= speed;
        if (state[SDL_SCANCODE_D]) position.x += speed;
    }

    void Render(SDL_Renderer* renderer) override {
        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);

        glm::mat4 view = glm::lookAt(
            glm::vec3(2.0f, 2.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void applyLighting(const LightSource& light) {
        shader.use();
        light.applyToShader(shader);
    }

    ~Player() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};
