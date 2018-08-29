#include <window.hpp>

Window::Window(int width, int height, const std::string &title)
    : lastTime(0.0f)
{
    glfwInit();

    // Note: In a more robust system - maybe we would create
    // a WindowSettings data structure to contain all of these
    // options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        // this is probably bad c++
        throw "Failed to Create OpenGL Context";
    }

    // Create Context and Load OpenGL Functions
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);
    gladLoadGL(); // is this the right place for this to exist?
}

Window::~Window()
{
    glfwTerminate();
}

GLFWwindow* Window::GetWindow() const
{
    return window;
}

bool Window::IsOpen() const
{
    return glfwWindowShouldClose(window) == false;
}

void Window::SetCursorCallback(GLFWcursorposfun callback) const
{
    glfwSetCursorPosCallback(window, callback);
}

void Window::SetScrollCallback(GLFWscrollfun callback) const
{
    glfwSetScrollCallback(window, callback);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// Returns the delta time
// * From the last time this method was called
// Should only really be called on each iteration
// of the game loop
float Window::GetDeltaTime()
{
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;

    lastTime = currentTime;

    return deltaTime;
}
