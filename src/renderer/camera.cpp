#include "camera.h"

Camera::Camera(OpenGLContext *const openGL_context)
{
    m_OpenGL_context = openGL_context;
    m_horizontal_angle = 0.0f;
    m_vertical_angle = 0.0f;
    m_radius = 15.0f;
    m_FoV = 45.0f;
    m_position = glm::vec3(0.f, 0.f, 15.f);
    m_projection_matrix = glm::perspective(glm::radians(m_FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    spherical_move(0, 0, 0);
}

void Camera::spherical_move(double horizontal_move, double vertical_move, double radius_move)
{
    m_horizontal_angle += horizontal_move;
    m_vertical_angle += vertical_move;
    m_radius += radius_move;
    if (radius_move > 0)
        LOG_INFO("Radius move {0}", radius_move);

    m_vertical_angle = std::min(m_vertical_angle, PI / 2.f);
    m_vertical_angle = std::max(m_vertical_angle, - PI / 2.f);

    if (m_radius < 10.f) m_radius = 10.f;

    m_position = glm::vec3(m_radius*cos(m_vertical_angle) * sin(m_horizontal_angle),
                           m_radius*sin(m_vertical_angle),
                           m_radius*cos(m_vertical_angle) * cos(m_horizontal_angle));

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(m_horizontal_angle - PI / 2.0f),
        0,
        cos(m_horizontal_angle - PI / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, glm::normalize(m_position));

    m_view_matrix = glm::lookAt(
        m_position,             // Camera is here
        -m_position,            // and looks towards the origin
        up                      // Head is up
    );

}
