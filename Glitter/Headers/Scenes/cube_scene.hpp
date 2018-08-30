#pragma once

#include "scene.hpp"
#include "GameObjects/cube.hpp"

class CubeScene : Scene
{
public:
    CubeScene(glm::mat4 projection);

    void Render(glm::mat4 viewMatrix, float currentTime, float deltaTime) override;
private:
    glm::mat4 projection;
    Cube* cube;
    std::vector<glm::vec3> cubePositions = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };
};
