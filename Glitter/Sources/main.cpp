// Local Headers
#include "glitter.hpp"
#include "shader.hpp"
#include "model.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

int main()
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

    auto vertexShaderSource2 = LoadFileAsString("Resources/basic.vert");
    auto fragmentShaderSource2 = LoadFileAsString("Resources/basic.frag");

    Shader basicShader(vertexShaderSource2, fragmentShaderSource2);
    Model square(basicShader);

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

		auto delta = (float)glfwGetTime();
        glm::mat4 trans1(1.0f);
        trans1 = glm::translate(trans1, glm::vec3(0.5, -0.5f, 0.0f));
        trans1 = glm::rotate(trans1, delta, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 trans2(1.0f);
		trans2 = glm::translate(trans2, glm::vec3(-0.1, 0.2, 0.0));

        square.Render(trans1);
		square.Render(trans2);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
