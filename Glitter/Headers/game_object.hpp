#pragma once

#include "glitter.hpp"
#include "shader.hpp"
#include <utility>

struct Vao
{
    unsigned int id;
    const std::vector<float> vertices;

    // it might not make sense to load the vertex data to the gpu
    // in the constructor.
    Vao(const std::vector<float> vertices) : vertices(vertices)
    {
        // generate our buffers
        unsigned int VBO, EBO;
        glGenVertexArrays(1, &id);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // bind a vertexArrayObject that we can save our data to
        glBindVertexArray(id);

        // bind the array buffer and save the vertices data to it
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertices.data(), GL_STATIC_DRAW);

        // bind the element array buffer and save the indices to it
        // we are not using indices at the moment
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);

        // describe the layout of our vertex data to the shader program
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // unbind the vertexArrayObject
        glBindVertexArray(0);
    }
};

class GameObject
{
public:
    GameObject(Shader* shader, Vao* vao, glm::mat4 projection);

    void Translate(glm::vec3 translation);
    virtual void Rotate(float angle, glm::vec3 axis);
    void Render(glm::mat4 viewMatrix);
protected:
    explicit GameObject(glm::mat4 projection);

    Shader* shader;
    Vao* vao;
    glm::mat4 model;
    glm::mat4 projection;
    std::vector<std::pair<std::string, int> > uniformToTexture;
};
