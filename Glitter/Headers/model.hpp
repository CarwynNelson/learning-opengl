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
        int texture1 = LoadTexture("container.jpg", GL_RGB);
        int texture2 = LoadTexture("awesomeface.png", GL_RGBA, true);
		mShader.Use();
        mShader.SetInt("texture2", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
		glBindVertexArray(mModelVao);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

    void RenderBasic()
    {
        //LoadTexture("container.jpg");
        mShader.Use();
        glBindVertexArray(mModelVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
private:
    int LoadTexture(const std::string& imageName, GLenum format, bool flip = false)
    {
        const std::string basePath = "./../Glitter/Resources/";
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // unbind the vertexArrayObject
        glBindVertexArray(0); 

        return VAO;
    }

	int mModelVao;
	const Shader& mShader;

    std::vector<float> mVertices = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    }; 
	std::vector<unsigned int> mIndices = {
		0, 1, 3, // first triangle
        1, 2, 3 // second triangle
	};
};
