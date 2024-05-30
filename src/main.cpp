#include <iostream>
#include <string>

#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "renderer/model.h"

int main(int argc, char *argv[])
{
    OpenGLContext context("Rubik's Cube", 1280, 720);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    Model triangle;

    std::vector<float> triangle_buffer = {
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    triangle.buffer_data(triangle_buffer);

    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");

    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        triangle.draw(color_shader);

        // Swap buffers
        glfwSwapBuffers(context.get_window_handle());
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(context.get_window_handle(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(context.get_window_handle()) == 0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
