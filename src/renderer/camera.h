#pragma once

#include "rubiks_cube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl-context.h"
#include "events.h"

enum class CameraState
{
    wait_input,
    move
};

class Camera
{
private:
    OpenGLContext *m_OpenGL_context;

    float m_horizontal_angle;
    float m_vertical_angle;
    float m_radius;
    float m_FoV;
    float m_mouse_sensitivity;

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
    glm::vec3 m_position;

public:
    Camera(OpenGLContext *const openGL_context);
    glm::mat4 get_view_matrix() const { return m_view_matrix; }
    glm::mat4 get_projection_matrix() const { return m_projection_matrix; }
    glm::vec3 get_camera_position() const { return m_position;}
    void on_event(Event& event);
    void spherical_move(double theta_move, double phy_move, double radius_move);
};
