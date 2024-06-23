#include "controller.h"

OpenGLContext* Controller::m_openGL_context = nullptr;
Cube* Controller::m_cube = nullptr;
Camera* Controller::m_camera = nullptr;
ControllerState Controller::m_state = ControllerState::wait_input;
std::queue<Move> Controller::m_moves;
float Controller::m_animation_speed = 5.0f; // rotations per second

void Controller::init(OpenGLContext* context, Cube* cube, Camera* camera)
{
    m_openGL_context = context;
    m_cube = cube;
    m_camera = camera;
    m_state = ControllerState::wait_input;
    m_moves = std::queue<Move>();

    // set up glfw callbacks
    glfwSetKeyCallback(m_openGL_context->get_window_handle(), key_callback);
}

void Controller::update()
{
    m_camera->read_controls();
    run_animation();
}

void Controller::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // ESC to close window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // Apply commands to cube
    read_cube_commands(key, action);
}

void Controller::read_cube_commands(int key, int action)
{
    static bool clockwise = true;

    // R to reset cube to initial (solved) state
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        m_moves.push({Face::front, 0});
    }
    // Hold Left Shift to rotate face counterclockwise
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
        clockwise = false;
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        clockwise = true;
    else
    {
        int keys[] = {GLFW_KEY_KP_8, GLFW_KEY_KP_2, GLFW_KEY_KP_4, GLFW_KEY_KP_6, GLFW_KEY_KP_0, GLFW_KEY_KP_5};
        Face faces[] = {Face::top, Face::bottom, Face::left, Face::right, Face::back, Face::front};

        for (int i = 0; i < 6; i++)
        {
            // Rotate face with number keys
            if (key == keys[i] && action == GLFW_PRESS)
            {
                if (clockwise)
                    m_moves.push({faces[i], 1});
                else
                    m_moves.push({faces[i], -1});
                break;
            }
        }
    }
}

void Controller::run_animation()
{
    if (m_moves.empty())
        return;

    static double last_time = glfwGetTime();
    static double total_angle = 0.0f;

    if (m_moves.front().direction == 0)
    {
        m_cube->reset();
        m_moves.pop();
        return;
    }

    if (m_state == ControllerState::wait_input)
    {
        m_state = ControllerState::rotate_face;
        last_time = glfwGetTime();
    }

    const double cur_time = glfwGetTime();
    const double delta_time = cur_time - last_time;

    if (delta_time < 1.f / 60.f)
        return;

    const double cur_angle = std::min((PI / 2.f) * delta_time * m_animation_speed * m_moves.size() , PI / 2.f - total_angle);
    total_angle += cur_angle;
    m_cube->rotate_face(m_moves.front().face, cur_angle * (float) m_moves.front().direction);

    if (total_angle >= PI / 2.f)
    {
        m_cube->round_pieces_positions();
        total_angle = 0.0f;
        m_moves.pop();
        m_state = ControllerState::wait_input;
    }

    last_time = cur_time;
}
