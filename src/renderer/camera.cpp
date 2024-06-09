#include "camera.h"

Camera::Camera(OpenGLContext *const openGL_context, const glm::vec3 &position)
{
    m_OpenGL_context = openGL_context;
    m_position = position;
    m_horizontal_angle = PI;
    m_vertical_angle = 0.0f;
    m_FoV = 120.0f;
    m_speed = 15.0f;
    m_mouse_speed = 0.005f;
    m_config = CameraConfig::fly;
}

void Camera::read_controls()
{
    static double last_time = glfwGetTime();

    double current_time = glfwGetTime();
    float delta_time = float(current_time - last_time);

    // limit camera update to 60 fps
    if (delta_time < 1.f / 60.f)
        return;

    // Get mouse position
    double x_pos, y_pos;
    glfwGetCursorPos(m_OpenGL_context->get_window_handle(), &x_pos, &y_pos);

    // Reset mouse position for next frame
    glfwSetCursorPos(m_OpenGL_context->get_window_handle(), m_OpenGL_context->get_window_width() / 2, m_OpenGL_context->get_window_height() / 2);

    // Compute new orientation
    m_horizontal_angle += m_mouse_speed * float(m_OpenGL_context->get_window_width() / 2 - x_pos);
    m_vertical_angle += m_mouse_speed * float(m_OpenGL_context->get_window_height() / 2 - y_pos);

    if (m_vertical_angle > PI / 2.0f)
        m_vertical_angle = PI / 2.0f; // pi/2
    if (m_vertical_angle < -PI / 2.0f)
        m_vertical_angle = -PI / 2.0f; // pi/2

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
        cos(m_vertical_angle) * sin(m_horizontal_angle),
        sin(m_vertical_angle),
        cos(m_vertical_angle) * cos(m_horizontal_angle));

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(m_horizontal_angle - PI / 2.0f),
        0,
        cos(m_horizontal_angle - PI / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(m_OpenGL_context->get_window_handle(), GLFW_KEY_W) == GLFW_PRESS)
        m_position += direction * delta_time * m_speed;

    if (glfwGetKey(m_OpenGL_context->get_window_handle(), GLFW_KEY_S) == GLFW_PRESS)
        m_position -= direction * delta_time * m_speed;

    if (glfwGetKey(m_OpenGL_context->get_window_handle(), GLFW_KEY_D) == GLFW_PRESS)
        m_position += right * delta_time * m_speed;

    if (glfwGetKey(m_OpenGL_context->get_window_handle(), GLFW_KEY_A) == GLFW_PRESS)
        m_position -= right * delta_time * m_speed;

    if (glfwGetKey(m_OpenGL_context->get_window_handle(), GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += up * delta_time * m_speed;

    if (glfwGetKey(m_OpenGL_context->get_window_handle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_position -= up * delta_time * m_speed;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    m_projection_matrix = glm::perspective(glm::radians(m_FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    m_view_matrix = glm::lookAt(
        m_position,             // Camera is here
        m_position + direction, // and looks here : at the same position, plus "direction"
        up                      // Head is up (set to 0,-1,0 to look upside-down)
    );

    last_time = current_time;
}
