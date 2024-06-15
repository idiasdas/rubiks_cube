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
    static void init(OpenGLContext* context, Cube* cube, Camera* camera);
    static void update();
    static void set_animation_speed(float speed) { m_animation_speed = speed; }
private:
    static OpenGLContext* m_openGL_context;
    static Cube* m_cube;
    static Camera* m_camera;
    static ControllerState m_state;
    static std::queue<Move> m_moves;
    static float m_animation_speed;

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void read_cube_commands(int key, int action);
    static void run_animation();
};
