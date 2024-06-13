#include "controller.h"

OpenGLContext* Controller::m_openGL_context = nullptr;
Cube* Controller::m_cube = nullptr;
Camera* Controller::m_camera = nullptr;
ControllerState Controller::m_state = ControllerState::wait_input;

void Controller::init(OpenGLContext* context, Cube* cube, Camera* camera)
{
    m_openGL_context = context;
    m_cube = cube;
    m_camera = camera;
    m_state = ControllerState::wait_input;

    // set up glfw callbacks
    glfwSetKeyCallback(m_openGL_context->get_window_handle(), key_callback);
}

void Controller::update()
{
    if (m_state == ControllerState::wait_input)
        m_camera->read_controls();
    // m_cube->run_animations();
}

void Controller::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // ESC to close window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // Apply commands to cube
    control_cube(key, action);
}

void Controller::control_cube(int key, int action)
{
    static bool clockwise = true;

    // R to reset cube to initial (solved) state
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        m_cube->reset();
    }

    // Hold Left Shift to rotate face counterclockwise
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
        clockwise = false;
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        clockwise = true;

    // Rotate face with numpad keys
    else if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
    {
        if (clockwise)
            m_cube->rotate_face(Face::top, PI / 2.f);
        else
            m_cube->rotate_face(Face::top, -PI / 2.f);
    }

    else if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
    {
        if (clockwise)
            m_cube->rotate_face(Face::bottom, PI / 2.f);
        else
            m_cube->rotate_face(Face::bottom, -PI / 2.f);
    }

    else if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS)
    {
        if (clockwise)
            m_cube->rotate_face(Face::left, PI / 2.f);
        else
            m_cube->rotate_face(Face::left, -PI / 2.f);
    }

    else if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS)
    {
        if (clockwise)
            m_cube->rotate_face(Face::right, PI / 2.f);
        else
            m_cube->rotate_face(Face::right, -PI / 2.f);
    }

    else if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
    {
        if (clockwise)
            m_cube->rotate_face(Face::back, PI / 2.f);
        else
            m_cube->rotate_face(Face::back, -PI / 2.f);
    }

    else if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
    {
        if (clockwise)
            m_cube->rotate_face(Face::front, PI / 2.f);
        else
            m_cube->rotate_face(Face::front, -PI / 2.f);
    }
    m_cube->round_pieces_positions();
}
