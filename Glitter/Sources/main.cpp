// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int CompileShader(GLenum shaderType, const char* shaderSource)
{
    int shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shaderId;
}

int LinkShaderProgram(int shader1, int shader2)
{
    int success;
    char infoLog[512];

    int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, shader1);
    glAttachShader(shaderProgram, shader2);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(shader1);
    glDeleteShader(shader2);

    return shaderProgram;
}

int LoadModel(std::vector<float> vertices, std::vector<unsigned int> indices)
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertices.data(), GL_STATIC_DRAW);

	// bind the element array buffer and save the indices to it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// describe the layout of our vertex data to the shader program
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// unbind the vertexArrayObject
    glBindVertexArray(0); 

    return VAO;
}

class ShaderProgram
{
	const char* mVertexShaderSource;
	const char* mFragmentShaderSource;
	int mShaderId;
public:
	ShaderProgram(const char* vertexSource, const char* fragmentSource)
		: mVertexShaderSource(vertexSource)
		, mFragmentShaderSource(fragmentSource)
	{
		int vertexShader = CompileShader(GL_VERTEX_SHADER, mVertexShaderSource);
		int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, mFragmentShaderSource);
		mShaderId = LinkShaderProgram(vertexShader, fragmentShader);
	}

	void Use() const
	{
		glUseProgram(mShaderId);
	}
};

class Model
{
public:
	Model(const ShaderProgram& program) : mProgram(program)
	{
		mModelVao = LoadModel(mVertices, mIndices);
	}
	
	void Render()
	{
		mProgram.Use();
		glBindVertexArray(mModelVao);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
private:
	int mModelVao;
	const ShaderProgram& mProgram;

    std::vector<float> mVertices = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
    }; 
	std::vector<unsigned int> mIndices = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};
};


int main(int argc, char * argv[])
{
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

	ShaderProgram program(vertexShaderSource, fragmentShaderSource);
	Model square(program);

    while (glfwWindowShouldClose(mWindow) == false)
    {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(mWindow, true);
        }

		if (glfwGetKey(mWindow, GLFW_KEY_P) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (glfwGetKey(mWindow, GLFW_KEY_F) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		square.Render();

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
