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

    Cube cube(3.0f, 0.5f, {BLUE, WHITE, RED, GREEN, YELLOW, ORANGE});
    // cube.rotate_face(Face::front, 1);
    // cube.rotate_face(Face::front, PI / 4.f);


    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");

    Camera camera(&context, glm::vec3(0.0f, 0.0f, 5.0f));
    double last_time = glfwGetTime();
    do
    {
        double cur_time = glfwGetTime();
        if (glfwGetKey(context.get_window_handle(), GLFW_KEY_KP_5) == GLFW_PRESS && cur_time - last_time > 0.2f)
        {
            last_time = cur_time;
            if (glfwGetKey(context.get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                cube.rotate_face(Face::front, 3);
            else
                cube.rotate_face(Face::front, 1);
        }
        if (glfwGetKey(context.get_window_handle(), GLFW_KEY_KP_6) == GLFW_PRESS && cur_time - last_time > 0.2f)
        {
            last_time = cur_time;
            if (glfwGetKey(context.get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                cube.rotate_face(Face::right, 3);
            else
                cube.rotate_face(Face::right, 1);
        }
        if (glfwGetKey(context.get_window_handle(), GLFW_KEY_KP_4) == GLFW_PRESS && cur_time - last_time > 0.2f)
        {
            last_time = cur_time;
            if (glfwGetKey(context.get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                cube.rotate_face(Face::left, 3);
            else
                cube.rotate_face(Face::left, 1);
        }
        if (glfwGetKey(context.get_window_handle(), GLFW_KEY_KP_0) == GLFW_PRESS && cur_time - last_time > 0.2f)
        {
            last_time = cur_time;
            if (glfwGetKey(context.get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                cube.rotate_face(Face::back, 3);
            else
                cube.rotate_face(Face::back, 1);
        }
        if (glfwGetKey(context.get_window_handle(), GLFW_KEY_KP_8) == GLFW_PRESS && cur_time - last_time > 0.2f)
        {
            last_time = cur_time;
            if (glfwGetKey(context.get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                cube.rotate_face(Face::top, 3);
            else
                cube.rotate_face(Face::top, 1);
        }
        if (glfwGetKey(context.get_window_handle(), GLFW_KEY_KP_2) == GLFW_PRESS && cur_time - last_time > 0.2f)
        {
            last_time = cur_time;
            if (glfwGetKey(context.get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                cube.rotate_face(Face::bottom, 3);
            else
                cube.rotate_face(Face::bottom, 1);
        }
        camera.update();

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
