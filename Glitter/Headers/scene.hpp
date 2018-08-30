#pragma once

#include "game_object.hpp"
#include <glm/glm.hpp>
#include <vector>

class Scene
{
public:
    virtual void Render(glm::mat4 viewMatrix, float currentTime, float deltaTime) = 0;
protected:
};
