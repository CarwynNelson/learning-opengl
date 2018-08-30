// Local Headers

#include "glitter.hpp"

#include "shader.hpp"
#include "camera.hpp"
#include "window.hpp"
#include "game_object.hpp"
#include "Scenes/cube_scene.hpp"

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
// to do next
// * add texturing back

static void processInput(Window& gameWindow);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
    try {
        Window gameWindow(mWidth, mHeight, "OpenGL");
        gameWindow.SetCursorCallback(mouse_callback);
        gameWindow.SetScrollCallback(scroll_callback);

        // here is an opengl / "graphics api" context
        // and here are the settings we are going to set on it
        // or maybe more of a gl utility that inits opengl
        // and in the future we could pass it a GLSettings struct type thing
        gladLoadGL();
        fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
        glEnable(GL_DEPTH_TEST);

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);

        CubeScene scene(projection);

        while (gameWindow.IsOpen())
        {
            // Background Fill Color
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view = camera.GetViewMatrix();

            scene.Render(view, glfwGetTime(), gameWindow.GetDeltaTime());

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
