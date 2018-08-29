// Local Headers
#include "glitter.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "window.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = mWidth / 2.0f;
float lastY = mWidth / 2.0f;
bool firstMouse = true;

// to think about
// * event system
// * non-glfw input system
// * replacement for glfwGetTime
// * some better "Model" abstraction

static void processInput(Window& gameWindow);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
    try {
        Window gameWindow(mWidth, mHeight, "OpenGL");
        gameWindow.SetCursorCallback(mouse_callback);
        gameWindow.SetScrollCallback(scroll_callback);

        fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

        // I'm not sure this should be a part of Window
        // Since this isn't strictly to do with the window itself
        // but rather the rendering of the graphics - which are then
        // later "sent to the window" if you will
        glEnable(GL_DEPTH_TEST);

        auto vertexShaderSource2 = LoadFileAsString("Resources/basic.vert");
        auto fragmentShaderSource2 = LoadFileAsString("Resources/basic.frag");

        Shader basicShader(vertexShaderSource2, fragmentShaderSource2);
        Model square(basicShader);

        glm::vec3 cubePositions[] = {
                glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
        basicShader.Use();
        basicShader.SetMat4("projection", projection);

        while (gameWindow.IsOpen())
        {
            // Background Fill Color
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view = camera.GetViewMatrix();
            basicShader.Use();
            basicShader.SetMat4("view", view);

            for (auto i = 0; i < 10; i++) {
                float angle = 20.0f * i;
                if (i % 3 == 0)
                    angle = glfwGetTime() * 25.0f;

                glm::mat4 model(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                basicShader.SetMat4("model", model);

                square.Render();
            }

            gameWindow.SwapBuffers();
            processInput(gameWindow);
        }
    } catch (const char* e) {
        fprintf(stderr, e);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void processInput(Window& gameWindow)
{
    auto window = gameWindow.GetWindow();
    auto deltaTime = gameWindow.GetDeltaTime();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // maybe this should be a function/config on Window?
    // ExitKey
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
