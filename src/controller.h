#pragma once
#include "renderer/opengl-context.h"
#include "renderer/camera.h"
#include "rubiks_cube/cube.h"

enum class ControllerState
{
    wait_input,
    move_camera,
    rotate_face
};

class Controller
{
public:
    static void init(OpenGLContext* context, Cube* cube, Camera* camera);
    static void update();
private:
    static OpenGLContext* m_openGL_context;
    static Cube* m_cube;
    static Camera* m_camera;
    static ControllerState m_state;

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void control_cube(int key, int action);
};
