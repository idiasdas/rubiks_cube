#pragma once

#include <queue>

#include "renderer/opengl-context.h"
#include "renderer/camera.h"
#include "rubiks_cube/cube.h"

enum class ControllerState
{
    wait_input,
    move_camera,
    rotate_face
};

struct Move
{
    Face face;
    int direction; // 1 for clockwise, -1 for counterclockwise
};

class Controller
{
public:
    static void init(OpenGLContext *context, Cube *cube, Camera *camera);
    static void update();
    static void set_animation_speed(float speed) { m_animation_speed = speed; }
    static glm::vec3 get_ray_origin() { return m_ray_origin;}
    static glm::vec3 get_ray_direction() { return m_ray_end - m_ray_origin;}

private:
    static OpenGLContext *m_openGL_context;
    static Cube *m_cube;
    static Camera *m_camera;
    static ControllerState m_state;
    static std::queue<Move> m_moves;
    static float m_animation_speed;
    static double m_xpos;
    static double m_ypos;
    static float m_mouse_sensitivity;
    static glm::vec3 m_ray_origin;
    static glm::vec3 m_ray_end;

private:
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_pos_callback(GLFWwindow *window, double xpos, double ypos);
    static void mouse_buttom_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void read_cube_commands(int key, int action);
    static void run_animation();
};
