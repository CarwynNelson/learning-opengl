#include <Scenes/cube_scene.hpp>

CubeScene::CubeScene(glm::mat4 projection)
    : projection(projection)
{
    cube = new Cube(projection);
}

void CubeScene::Render(glm::mat4 viewMatrix, float currentTime, float deltaTime)
{
    for (auto i = 0; i < 10; i++) {
        float angle = 20.0f * i;
        if (i % 3 == 0)
            angle = currentTime * 25.0f;

        cube->Translate(cubePositions[i]);
        cube->Rotate(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        cube->Render(viewMatrix);
    }
}
