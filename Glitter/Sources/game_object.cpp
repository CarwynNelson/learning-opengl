#include "game_object.hpp"

GameObject::GameObject(const Shader &shader, const Vao& vao, glm::mat4 projection)
        : shader(shader), vao(vao), model(glm::mat4(1.0f)), projection(projection)
{

}

void GameObject::Translate(glm::vec3 translation)
{
    model = glm::translate(model, translation);
}

void GameObject::Rotate(float angleInRadians, glm::vec3 axis)
{
    model = glm::rotate(model, angleInRadians, axis);
}

void GameObject::Render(glm::mat4 viewMatrix)
{
    shader.Use();
    shader.SetMat4("view", viewMatrix);
    shader.SetMat4("model", model);
    shader.SetMat4("projection", projection);
    // activating the texture will need to happen here

    glBindVertexArray(vao.id);
    glDrawArrays(GL_TRIANGLES, 0, 36); // magic-number 36
    glBindVertexArray(0);

    model = glm::mat4(1.0f); // works for now but might have unintended consequences
}
