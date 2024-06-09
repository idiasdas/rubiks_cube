#include <iostream>
#include <string>

#include "rubiks_cube.h"

#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "renderer/model.h"
#include "renderer/camera.h"
#include "rubiks_cube/cube.h"

int main(int argc, char *argv[])
{
    OpenGLContext context("Rubik's Cube", 1280, 720);
    Cube cube(2.0f, 1.f, {BLUE, WHITE, RED, GREEN, YELLOW, ORANGE});
    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");
    Camera camera(&context, glm::vec3(0.0f, 0.0f, 5.0f));

    do
    {
        cube.read_controls(&context);
        camera.read_controls();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.draw(color_shader, camera);

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
