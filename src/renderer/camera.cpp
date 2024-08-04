#include "camera.h"

Camera::Camera(OpenGLContext *const openGL_context)
{
    m_OpenGL_context = openGL_context;
    m_horizontal_angle = 0.0f;
    m_vertical_angle = 0.0f;
    m_radius = 15.0f;
    m_FoV = 45.0f;
    m_position = glm::vec3(0.f, 0.f, 15.f);
    float aspect = (float) openGL_context->get_window_width() / (float) openGL_context->get_window_height();
    m_projection_matrix = glm::perspective(glm::radians(m_FoV), aspect, 0.1f, 120.0f);
    m_mouse_sensitivity = 0.005f;
    spherical_move(0, 0, 0);
}

void Camera::on_event(Event &event)
{
    static CameraState s_state = CameraState::wait_input;
    static float s_mouse_xpos = 0.0f;
    static float s_mouse_ypos = 0.0f;

    if (event.get_event_type() == EventType::mouse_move)
    {
        if (s_state == CameraState::move)
        {
            float xpos = ((MouseMoveEvent *)&event)->get_x();
            float ypos = ((MouseMoveEvent *)&event)->get_y();
            spherical_move(m_mouse_sensitivity * (s_mouse_xpos - xpos), -m_mouse_sensitivity * (s_mouse_ypos - ypos), 0);
            s_mouse_xpos = xpos;
            s_mouse_ypos = ypos;
        }
    }
    else if (event.get_event_type() == EventType::mouse_button_release)
    {
        s_state = CameraState::wait_input;
    }
    else if (event.get_event_type() == EventType::mouse_button_press)
    {
        if (((MouseButtonPressEvent *)&event)->get_button() == GLFW_MOUSE_BUTTON_2)
        {
            s_state = CameraState::move;
            s_mouse_xpos = ((MouseButtonPressEvent *)&event)->get_xpos();
            s_mouse_ypos = ((MouseButtonPressEvent *)&event)->get_ypos();

        }
    }
    else if (event.get_event_type() == EventType::mouse_scroll)
    {
        spherical_move(0, 0, -((MouseScrollEvent *)&event)->get_yoffset());
    }
    else if (event.get_event_type() == EventType::window_resize)
    {
        float aspect = (float) m_OpenGL_context->get_window_width() / (float) m_OpenGL_context->get_window_height();
        m_projection_matrix = glm::perspective(glm::radians(m_FoV), aspect, 0.1f, 120.0f);
    }
}

void Camera::spherical_move(double horizontal_move, double vertical_move, double radius_move)
{
    m_horizontal_angle += horizontal_move;
    m_vertical_angle += vertical_move;
    m_radius += 2 * radius_move;
    m_vertical_angle = std::min(m_vertical_angle, PI / 2.f);
    m_vertical_angle = std::max(m_vertical_angle, -PI / 2.f);

    if (m_radius < 10.f)
        m_radius = 10.f;
    else if (m_radius > 100.f)
        m_radius = 100.f;

    m_position = glm::vec3(m_radius * cos(m_vertical_angle) * sin(m_horizontal_angle),
                           m_radius * sin(m_vertical_angle),
                           m_radius * cos(m_vertical_angle) * cos(m_horizontal_angle));

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(m_horizontal_angle - PI / 2.0f),
        0,
        cos(m_horizontal_angle - PI / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, glm::normalize(m_position));

    m_view_matrix = glm::lookAt(
        m_position,  // Camera is here
        -m_position, // and looks towards the origin
        up           // Head is up
    );
}
