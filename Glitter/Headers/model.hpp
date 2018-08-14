#pragma once

#include "glitter.hpp"

class Model
{
public:
	Model(const Shader& shader) : mShader(shader)
	{
		mModelVao = Load();
	}
	
	void Render()
	{
		mShader.Use();
		glBindVertexArray(mModelVao);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
private:
    int Load()
    {
        // generate our buffers
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // bind a vertexArrayObject that we can save our data to
        glBindVertexArray(VAO);

        // bind the array buffer and save the vertices data to it
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * 4, mVertices.data(), GL_STATIC_DRAW);

        // bind the element array buffer and save the indices to it
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);

        // describe the layout of our vertex data to the shader program
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);

        // unbind the vertexArrayObject
        glBindVertexArray(0); 

        return VAO;
    }

	int mModelVao;
	const Shader& mShader;

    std::vector<float> mVertices = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    }; 
	std::vector<unsigned int> mIndices = {
		0, 1, 3, // first triangle
		//1, 2, 3 // second triangle
	};
};
