#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/opengl-context.h"

int main(int argc, char* argv[])
{
    OpenGLContext context("Rubik's Cube", 1248, 720);

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(context.get_window_handle());
        glfwPollEvents();
    } while(glfwGetKey(context.get_window_handle(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(context.get_window_handle()) == 0);

    return 0;
}
