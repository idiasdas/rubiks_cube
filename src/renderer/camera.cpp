#include "camera.h"

Camera::Camera(GLFWwindow *window, glm::vec3 position)
{
    m_window = window;
    m_position = position;
    m_horizontal_angle = PI;
    m_vertical_angle = 0.0f;
    m_FoV = 45.0f;
    m_speed = 3.0f;
    m_mouse_speed = 0.005f;
}

void Camera::update()
{
    // glfwGetTime is called only once, the first time this function is called
    static double last_time = glfwGetTime();

    // Compute time difference between current and last frame
    double current_time = glfwGetTime();
    float delta_time = float(current_time - last_time);

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);

    // Reset mouse position for next frame
    glfwSetCursorPos(m_window, 1024 / 2, 768 / 2);

    // Compute new orientation
    m_horizontal_angle += m_mouse_speed * float(1024 / 2 - xpos);
    m_vertical_angle += m_mouse_speed * float(768 / 2 - ypos);

    if (m_vertical_angle > 3.14f / 2.0f)
        m_vertical_angle = 3.14f / 2.0f; // pi/2
    if (m_vertical_angle < -3.14f / 2.0f)
        m_vertical_angle = -3.14f / 2.0f; // pi/2

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
        cos(m_vertical_angle) * sin(m_horizontal_angle),
        sin(m_vertical_angle),
        cos(m_vertical_angle) * cos(m_horizontal_angle));

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(m_horizontal_angle - 3.14f / 2.0f),
        0,
        cos(m_horizontal_angle - 3.14f / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += direction * delta_time * m_speed;

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= direction * delta_time * m_speed;

    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += right * delta_time * m_speed;

    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= right * delta_time * m_speed;

    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += up * delta_time * m_speed;

    if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_position -= up * delta_time * m_speed;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    m_projection_matrix = glm::perspective(glm::radians(m_FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    m_view_matrix = glm::lookAt(
        m_position,             // Camera is here
        m_position + direction, // and looks here : at the same position, plus "direction"
        up                      // Head is up (set to 0,-1,0 to look upside-down)
    );

    // For the next frame, the "last time" will be "now"
    last_time = current_time;
}
