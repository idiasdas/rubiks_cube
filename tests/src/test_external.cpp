/*
    Testing external modules initialization.
*/

#include <gtest/gtest.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

TEST(External, GLFW_GLAD_INIT)
{
    EXPECT_TRUE(glfwInit() != 0) << "Failed to initialize GLFW.";

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 660, "Window Features", NULL, NULL);

    EXPECT_TRUE(window != 0) << "Failed to create GLFWwindow.";

    glfwSetInputMode(window, GLFW_UNLIMITED_MOUSE_BUTTONS, GLFW_TRUE);

    glfwMakeContextCurrent(window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    EXPECT_TRUE(status != 0) << "Glad could not load from GLFW context.\n";
}
