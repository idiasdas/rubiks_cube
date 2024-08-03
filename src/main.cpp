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

OpenGLContext *g_context = nullptr;
Cube *g_cube = nullptr;
Camera *g_camera = nullptr;
Model *g_ray = nullptr;

void event_manager(Event &event)
{
    g_cube->on_event(event);
    g_camera->on_event(event);

    if (event.get_event_type() == EventType::mouse_button_press)
    {
        if (((MouseButtonPressEvent *)&event)->get_button() == GLFW_MOUSE_BUTTON_1)
        {
            float xpos = ((MouseButtonPressEvent *)&event)->get_xpos();
            float ypos = ((MouseButtonPressEvent *)&event)->get_ypos();

            glm::vec4 ray_start_NDC((xpos / (float)g_context->get_window_width() - 0.5f) * 2.0f,
                                    -(ypos / (float)g_context->get_window_height() - 0.5f) * 2.0f,
                                    -1.f,
                                    1.0f);

            glm::vec4 ray_end_NDC((xpos / (float)g_context->get_window_width() - 0.5f) * 2.0f,
                                  -(ypos / (float)g_context->get_window_height() - 0.5f) * 2.0f,
                                  0.f,
                                  1.0f);

            glm::mat4 inverse_projection_view = glm::inverse(g_camera->get_projection_matrix() * g_camera->get_view_matrix());
            glm::vec4 ray_origin_world = inverse_projection_view * ray_start_NDC;
            ray_origin_world /= ray_origin_world.w;
            glm::vec4 ray_end_world = inverse_projection_view * ray_end_NDC;
            ray_end_world /= ray_end_world.w;

            ray_end_world = glm::normalize(ray_end_world - ray_origin_world);
            g_ray->update_buffer_vertices({ray_origin_world.x, ray_origin_world.y, ray_origin_world.z, 0.8f, 0.8f, 0.2f,
                                500.f * ray_end_world.x + ray_origin_world.x, 500.f * ray_end_world.y + ray_origin_world.y, 500.f * ray_end_world.z + ray_origin_world.z, 0.8f, 0.8f, 0.2f});

            RayEvent ray_event(ray_origin_world, ray_end_world);
            event_manager(ray_event);
        }
    }
}

int main()
{
    Log::init();

    OpenGLContext context("Rubik's Cube", 1280, 720);
    g_context = &context;

    context.set_events_callbacks(event_manager);

    Camera camera(&context);
    g_camera = &camera;

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

    Model ray;
    ray.buffer_vertices({0.0f, 0.0f, 0.0f, .8f, 0.8f, 0.2f,
                         10.0f, 10.0f, 0.0f, .8f, 0.8f, 0.2f});
    ray.buffer_indices({0, 1});

    g_ray = &ray;

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

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.on_update();
        cube.draw(color_shader, camera);
        axes_lines.draw_lines(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * axes_lines.get_model_matrix());
        ray.draw_lines(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * ray.get_model_matrix());

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
