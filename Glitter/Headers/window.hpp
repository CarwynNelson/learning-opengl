#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool IsOpen() const;
    void SwapBuffers() const;

    GLFWwindow* GetWindow() const;
    void SetCursorCallback(GLFWcursorposfun callback) const;
    void SetScrollCallback(GLFWscrollfun callback) const;

    float GetDeltaTime(); // maybe this should be const?
private:
    float lastTime;
    GLFWwindow* window;
};