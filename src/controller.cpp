// #include "controller.h"

// OpenGLContext *Controller::m_openGL_context = nullptr;
// Cube *Controller::m_cube = nullptr;
// Camera *Controller::m_camera = nullptr;
// ControllerState Controller::m_state = ControllerState::wait_input;
// std::queue<Move> Controller::m_moves;
// float Controller::m_animation_speed = 5.0f; // rotations per second
// double Controller::m_xpos = 0.f;
// double Controller::m_ypos = 0.f;
// float Controller::m_mouse_sensitivity = 0.005f;
// glm::vec3 Controller::m_ray_origin = {0.f, 0.f, 0.f};
// glm::vec3 Controller::m_ray_end = {0.f, 0.f, 0.f};
// void (*Controller::m_func_event_handler)(Event& event) = nullptr;

// void Controller::init(OpenGLContext *context, Cube *cube, Camera *camera, void (* func_event_handler)(Event& event))
// {
//     m_openGL_context = context;
//     m_cube = cube;
//     m_camera = camera;
//     m_state = ControllerState::wait_input;
//     m_moves = std::queue<Move>();
//     m_func_event_handler = func_event_handler;

//     // set up glfw callbacks
//     glfwSetKeyCallback(m_openGL_context->get_window_handle(), key_callback);
//     glfwSetCursorPosCallback(m_openGL_context->get_window_handle(), mouse_pos_callback);
//     glfwSetMouseButtonCallback(m_openGL_context->get_window_handle(), mouse_buttom_callback);
//     glfwSetScrollCallback(m_openGL_context->get_window_handle(), mouse_scroll_callback);
// }

// void Controller::update()
// {
//     // m_camera->read_controls();
//     run_animation();
// }

// void Controller::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
// {
//     (void) scancode;
//     (void) mods;

//     // ESC to close window
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//     {
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
//         WindowCloseEvent event;
//         m_func_event_handler(event);
//     }

//     if (action == GLFW_PRESS)
//     {
//         KeyPressEvent event(key);
//         m_func_event_handler(event);
//     }
//     else if (action == GLFW_RELEASE)
//     {
//         KeyReleaseEvent event(key);
//         m_func_event_handler(event);
//     }

//     // Apply commands to cube
//     read_cube_commands(key, action);
// }

// void Controller::mouse_pos_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     (void) window;

//     if (m_state == ControllerState::move_camera)
//     {
//         m_camera->spherical_move(m_mouse_sensitivity * (m_xpos - xpos), -m_mouse_sensitivity * (m_ypos - ypos), 0);
//     }
//     m_xpos = xpos;
//     m_ypos = ypos;
// }

// void Controller::mouse_buttom_callback(GLFWwindow *window, int button, int action, int mods)
// {
//     (void) window;
//     (void) mods;

//     if (action == GLFW_RELEASE)
//     {
//         LOG_INFO(" Wait input mode.");
//         m_state = ControllerState::wait_input;
//     }
//     else
//     {
//         if (button == GLFW_MOUSE_BUTTON_1)
//         {
//             glfwGetCursorPos(m_openGL_context->get_window_handle(), &m_xpos, &m_ypos);

//             glm::vec4 ray_start_NDC(((float)m_xpos / (float)m_openGL_context->get_window_width() - 0.5f) * 2.0f,
//                                     -((float)m_ypos / (float)m_openGL_context->get_window_height() - 0.5f) * 2.0f,
//                                     -1.f,
//                                     1.0f);

//             glm::vec4 ray_end_NDC(((float)m_xpos / (float)m_openGL_context->get_window_width() - 0.5f) * 2.0f,
//                                   -((float)m_ypos / (float)m_openGL_context->get_window_height() - 0.5f) * 2.0f,
//                                   0.f,
//                                   1.0f);

//             glm::mat4 inverse_projection_view = glm::inverse(m_camera->get_projection_matrix() * m_camera->get_view_matrix());
//             glm::vec4 ray_origin_world = inverse_projection_view * ray_start_NDC;
//             ray_origin_world /= ray_origin_world.w;
//             glm::vec4 ray_end_world = inverse_projection_view * ray_end_NDC;
//             ray_end_world /= ray_end_world.w;

//             m_ray_origin = ray_origin_world;
//             m_ray_end = ray_end_world;

//             m_cube->ray_pick(m_ray_origin, glm::normalize(m_ray_end - m_ray_origin));
//         }

//         else if (button == GLFW_MOUSE_BUTTON_2)
//         {
//             LOG_INFO("Move camera mode.");
//             m_state = ControllerState::move_camera;
//             glfwGetCursorPos(m_openGL_context->get_window_handle(), &m_xpos, &m_ypos);
//         }
//         else
//         {
//             LOG_WARN("Unkown mouse button: {0}.", button);
//         }
//     }
// }

// void Controller::mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//     (void) window;
//     (void) xoffset;

//     m_camera->spherical_move(0, 0, -yoffset);
// }

// void Controller::read_cube_commands(int key, int action)
// {
//     static bool clockwise = true;

//     // R to reset cube to initial (solved) state
//     if (key == GLFW_KEY_R && action == GLFW_PRESS)
//     {
//         m_moves.push({Face::front, 0});
//     }
//     // Hold Left Shift to rotate face counterclockwise
//     else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
//         clockwise = false;
//     else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
//         clockwise = true;
//     else
//     {
//         int keys[] = {GLFW_KEY_KP_8, GLFW_KEY_KP_2, GLFW_KEY_KP_4, GLFW_KEY_KP_6, GLFW_KEY_KP_0, GLFW_KEY_KP_5};
//         Face faces[] = {Face::top, Face::bottom, Face::left, Face::right, Face::back, Face::front};

//         for (int i = 0; i < 6; i++)
//         {
//             // Rotate face with number keys
//             if (key == keys[i] && action == GLFW_PRESS)
//             {
//                 if (clockwise)
//                     m_moves.push({faces[i], 1});
//                 else
//                     m_moves.push({faces[i], -1});
//                 break;
//             }
//         }
//     }
// }

// void Controller::run_animation()
// {
//     if (m_moves.empty())
//         return;

//     static double last_time = glfwGetTime();
//     static double total_angle = 0.0f;

//     if (m_moves.front().direction == 0)
//     {
//         m_cube->reset();
//         m_moves.pop();
//         return;
//     }

//     if (m_state == ControllerState::wait_input)
//     {
//         m_state = ControllerState::rotate_face;
//         last_time = glfwGetTime();
//     }

//     const double cur_time = glfwGetTime();
//     const double delta_time = cur_time - last_time;

//     if (delta_time < 1.f / 60.f)
//         return;

//     const double cur_angle = std::min((PI / 2.f) * delta_time * m_animation_speed * m_moves.size(), PI / 2.f - total_angle);
//     total_angle += cur_angle;
//     m_cube->rotate_face(m_moves.front().face, cur_angle * (float)m_moves.front().direction);

//     if (total_angle >= PI / 2.f)
//     {
//         m_cube->round_pieces_positions();
//         total_angle = 0.0f;
//         m_moves.pop();
//         m_state = ControllerState::wait_input;
//     }

//     last_time = cur_time;
// }
