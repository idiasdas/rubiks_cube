#include <iostream>
#include <string>

#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "renderer/model.h"
#include "renderer/builder.h"

int main(int argc, char *argv[])
{
    OpenGLContext context("Rubik's Cube", 1280, 720);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    float color[3] = {1.0f, 0.0f, 0.0f};
    std::vector<float> square_buffer = get_piece(PieceType::center, &color);

    Model square;
    square.buffer_vertices(square_buffer);

    std::vector<uint32_t> square_indices(square_buffer.size() / 6);
    for (int i = 0; i < square_indices.size(); i++)
        square_indices[i] = i;

    square.buffer_indices(square_indices);

    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");

    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        square.draw(color_shader);

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
