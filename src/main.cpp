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

    Cube cube({2, 0, 0}, 2.0f, 1.f, {BLUE, WHITE, RED, GREEN, YELLOW, ORANGE});

    // std::vector<Cube> cubes;

    // for (int i = 0; i < 10; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    //         Cube cube({i * 10.f, j * 10.f, 0.f}, 2.0f, 1.f, {BLUE, WHITE, RED, GREEN, YELLOW, ORANGE});
    //         cubes.push_back(cube);
    //     }
    // }

    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");
    Camera camera(&context, glm::vec3(0.0f, 0.0f, 5.0f));
    double last_time = glfwGetTime();
    int frames_count = 0;
    do
    {
        frames_count++;
        double cur_time = glfwGetTime();
        double delta = cur_time - last_time;

        if(delta > 1.0f)
        {
            std::cout << "FPS: " << frames_count / delta << "\n";
            last_time = cur_time;
            frames_count = 0;
        }

        cube.read_controls(&context);
        camera.read_controls();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.draw(color_shader, camera);
        // for (Cube cube : cubes)
        //     cube.draw(color_shader, camera);

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
