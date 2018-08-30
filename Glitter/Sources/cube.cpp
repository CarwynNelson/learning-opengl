#include "GameObjects/cube.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GameObjects/cube.hpp>


static int LoadTexture(const std::string& imageName, GLenum format, bool flip = false)
{
    const std::string basePath = "./../../Glitter/Resources/";
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    unsigned char* data = stbi_load((basePath + imageName).c_str(), &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return textureId;
}

Cube::Cube(glm::mat4 projection) : GameObject(projection)
{
    auto vertexShaderSource2 = LoadFileAsString("Resources/basic.vert");
    auto fragmentShaderSource2 = LoadFileAsString("Resources/basic.frag");

    this->shader = new Shader(vertexShaderSource2, fragmentShaderSource2);
    this->vao = new Vao(cubeVertices);

    this->texture1 = LoadTexture("container.jpg", GL_RGB);
    this->texture2 = LoadTexture("awesomeface.png", GL_RGBA, true);
}

void Cube::Render(glm::mat4 viewMatrix)
{
    shader->Use();
    shader->SetInt("texture1", 0);
    shader->SetInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture2);

    GameObject::Render(viewMatrix);
}
