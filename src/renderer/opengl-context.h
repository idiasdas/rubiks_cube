#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "log.h"

class OpenGLContext
{
public:
    /*
        Initializes GLFW, creates a window, makes window the current OpenGL context, loads OpenGL with glad.
        Exits with EXIT_FAILURE if any errors occur.
        Every interaction with GLFW requires the GLFWwindow* m_window.
    */
    OpenGLContext(const std::string& window_name, const int window_width, const int window_height);

    inline std::string get_window_name() const { return m_window_name; }
    inline int get_window_width() const { return m_window_width; }
    inline int get_window_height() const { return m_window_height; }
    inline GLFWwindow *get_window_handle() const { return m_window; }

private:
    GLFWwindow *m_window;
    std::string m_window_name;
    int m_window_width;
    int m_window_height;
};
