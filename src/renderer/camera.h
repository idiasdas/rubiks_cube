#pragma once

#include "rubiks_cube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl-context.h"

enum class CameraConfig : int
{
    fly,
    debug
};

class Camera
{
private:
    OpenGLContext *m_OpenGL_context;
    float m_horizontal_angle;
    float m_vertical_angle;
    float m_FoV;
    float m_speed;
    float m_mouse_speed;

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
    glm::vec3 m_position;
    CameraConfig m_config;

public:
    Camera(OpenGLContext *const openGL_context, const glm::vec3 &position);
    glm::mat4 get_view_matrix() const { return m_view_matrix; }
    glm::mat4 get_projection_matrix() const { return m_projection_matrix; }

    void read_controls();
};
