#include <iostream>
#include <string>

#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "renderer/model.h"
#include "renderer/builder.h"
#include "renderer/camera.h"

#include <glm/glm.hpp>

int main(int argc, char *argv[])
{
    OpenGLContext context("Rubik's Cube", 1280, 720);

    float colors[][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};
    std::vector<float> square_buffer = get_piece(PieceType::middle, colors);

    Model square;
    square.buffer_vertices(square_buffer);

    std::vector<uint32_t> square_indices(square_buffer.size() / 6);
    for (int i = 0; i < square_indices.size(); i++)
        square_indices[i] = i;


    square.buffer_indices(square_indices);
    glm::mat4 initial_model_matrix(1);
    square.set_model_matrix(initial_model_matrix);

    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");

    Camera camera(&context, glm::vec3(0.0f, 0.0f, 5.0f));

    do
    {
        camera.update();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        square.draw(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * square.get_model_matrix());

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
