#include "GameObjects/cube.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}

Cube::Cube(glm::mat4 projection) : GameObject(projection)
{
    auto vertexShaderSource2 = LoadFileAsString("Resources/basic.vert");
    auto fragmentShaderSource2 = LoadFileAsString("Resources/basic.frag");

    this->shader = new Shader(vertexShaderSource2, fragmentShaderSource2);
    this->vao = new Vao(cubeVertices);

    auto textureId2 = LoadTexture("container.jpg", GL_RGB);
    uniformToTexture.emplace_back(std::make_pair("texture1", textureId2));
    auto textureId1 = LoadTexture("awesomeface.png", GL_RGBA, true);
    uniformToTexture.emplace_back(std::make_pair("texture2", textureId1));
}
