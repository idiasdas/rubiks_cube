#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.14f

class Camera
{
private:
    GLFWwindow* m_window;
    float m_horizontal_angle;
    float m_vertical_angle;
    float m_FoV;
    float m_speed;
    float m_mouse_speed;

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
    glm::vec3 m_position;

public:
    Camera(GLFWwindow* window, glm::vec3 position);
    glm::mat4 get_view_matrix() const { return m_view_matrix;}
    glm::mat4 get_projection_matrix() const { return m_projection_matrix;}

    void update();
};
