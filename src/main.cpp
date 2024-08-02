#include <iostream>
#include <string>

#include "rubiks_cube.h"

#include "log.h"
#include "events.h"
#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "renderer/model.h"
#include "renderer/camera.h"
#include "rubiks_cube/cube.h"
#include "controller.h"

OpenGLContext *g_context = nullptr;
Cube *g_cube = nullptr;
Camera *g_camera = nullptr;

void manage_events(Event &event)
{
    LOG_INFO("Event log: {0}", event.to_string());
    g_cube->on_event(event);
    g_camera->on_event(event);

    if (event.get_event_type() == EventType::mouse_button_press)
    {
        if (((MouseButtonPressEvent *)&event)->get_button() == GLFW_MOUSE_BUTTON_1)
        {
            // create ray
        }
    }
}

void set_glfw_callbacks()
{
    glfwSetKeyCallback(g_context->get_window_handle(), [](GLFWwindow *window, int key, int scancode, int action, int mods){
        if (action == GLFW_PRESS)
        {
            KeyPressEvent event(key);
            manage_events(event);
        }
        else if (action == GLFW_RELEASE)
        {
            KeyReleaseEvent event(key);
            manage_events(event);
        }
    });

    glfwSetCursorPosCallback(g_context->get_window_handle(), [](GLFWwindow *window, double xpos, double ypos){
        MouseMoveEvent event(xpos, ypos);
        manage_events(event);
    });

    glfwSetMouseButtonCallback(g_context->get_window_handle(), [](GLFWwindow *window, int button, int action, int mods){
        if (action == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(g_context->get_window_handle(), &xpos, &ypos);
            MouseButtonPressEvent event(button, xpos, ypos);
            manage_events(event);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseButtonReleaseEvent event(button);
            manage_events(event);
        }
    });

    glfwSetScrollCallback(g_context->get_window_handle(), [](GLFWwindow *window, double xoffset, double yoffset){
        MouseScrollEvent event(yoffset);
        manage_events(event);
    });
}


int main()
{
    Log::init();

    OpenGLContext context("Rubik's Cube", 1280, 720);
    g_context = &context;

    set_glfw_callbacks();

    Cube cube(2.f, 1.f, {BLUE, WHITE, RED, GREEN, YELLOW, ORANGE});
    g_cube = &cube;

    Model axes_lines;
    std::vector<float> buffer_lines = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f};

    axes_lines.buffer_vertices(buffer_lines);

    axes_lines.buffer_indices({0, 1, 2, 3, 4, 5});

    // Model ray;
    // glm::vec3 ray_origin = {1.f, 0.f, 0.f};
    // glm::vec3 ray_direction = {0.f, 0.f, 0.f};
    // ray.buffer_vertices({0.0f, 0.0f, 0.0f, .8f, 0.8f, 0.2f,
                        //  10.0f, 10.0f, 0.0f, .8f, 0.8f, 0.2f});
    // ray.buffer_indices({0, 1});

    Camera camera(&context);
    g_camera = &camera;

    // Controller::init(&context, &cube, &camera, manage_events);

    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");
    double last_time = glfwGetTime();
    int frames_count = 0;

    do
    {
        frames_count++;
        double cur_time = glfwGetTime();
        double delta = cur_time - last_time;

        if (delta > 1.0f)
        {
            LOG_INFO("FPS: {0}", frames_count / delta);
            last_time = cur_time;
            frames_count = 0;
        }

        // Controller::update();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.draw(color_shader, camera);
        axes_lines.draw_lines(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * axes_lines.get_model_matrix());

        cube.on_update();

        // glm::vec3 new_ray_origin = Controller::get_ray_origin();

        // if (new_ray_origin != ray_origin)
        // {
        //     LOG_INFO("Update ray origin");
        //     ray_direction = Controller::get_ray_direction();
        //     ray_origin = new_ray_origin;

        //     ray.update_buffer_vertices({ray_origin.x, ray_origin.y, ray_origin.z, 0.8f, 0.8f, 0.2f,
        //                                 500.f * ray_direction.x + ray_origin.x, 500.f * ray_direction.y + ray_origin.y, 500.f * ray_direction.z + ray_origin.z, 0.8f, 0.8f, 0.2f});
        // }

        // if (ray_origin != glm::vec3(0.f, 0.f, 0.f))
        // {
        //     ray.draw_lines(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * ray.get_model_matrix());
        // }

        // Swap buffers
        glfwSwapBuffers(context.get_window_handle());
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(context.get_window_handle(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(context.get_window_handle()) == 0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
