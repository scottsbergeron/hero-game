#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.h"

class LightSource {
private:
    glm::vec3 position;
    glm::vec3 color;
    float ambient;
    float diffuse;
    float specular;

public:
    LightSource(
        const glm::vec3& pos = glm::vec3(10.0f, 10.0f, 10.0f),
        const glm::vec3& col = glm::vec3(1.0f, 1.0f, 1.0f),
        float amb = 0.2f,
        float diff = 0.5f,
        float spec = 1.0f
    ) : position(pos), color(col), ambient(amb), diffuse(diff), specular(spec) {}

    void applyToShader(const Shader& shader) const {
        shader.setVec3("lightPos", position);
        shader.setVec3("lightColor", color);
        shader.setFloat("ambientStrength", ambient);
        shader.setFloat("diffuseStrength", diffuse);
        shader.setFloat("specularStrength", specular);
    }
};
