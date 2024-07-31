#include <iostream>
#include <string>

#include "rubiks_cube.h"

#include "log.h"
#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "renderer/model.h"
#include "renderer/camera.h"
#include "rubiks_cube/cube.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    Log::init();
    OpenGLContext context("Rubik's Cube", 1280, 720);
    Cube cube(2.0f, 1.f, {BLUE, WHITE, RED, GREEN, YELLOW, ORANGE});
    Camera camera(&context);
    Controller::init(&context, &cube, &camera);
    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");
    double last_time = glfwGetTime();
    int frames_count = 0;
    do
    {
        frames_count++;
        double cur_time = glfwGetTime();
        double delta = cur_time - last_time;

        if(delta > 1.0f)
        {
            LOG_INFO("FPS: {0}", frames_count / delta);
            last_time = cur_time;
            frames_count = 0;
        }

        Controller::update();

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
