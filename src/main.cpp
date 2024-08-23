#include <iostream>
#include <string>

#include "rubiks_cube.h"

#include "events.h"
#include "log.h"
#include "renderer/camera.h"
#include "renderer/model.h"
#include "renderer/opengl-context.h"
#include "renderer/shader.h"
#include "rubiks_cube/cube.h"

OpenGLContext* g_context = nullptr;
Cube* g_cube = nullptr;
Camera* g_camera = nullptr;
Model* g_ray = nullptr;

void event_manager(Event& event) {
    g_cube->on_event(event);
    g_camera->on_event(event);

    if (event.get_event_type() == EventType::mouse_button_press) {
        if (((MouseButtonPressEvent*)&event)->get_button() == GLFW_MOUSE_BUTTON_1) {
            float xpos = ((MouseButtonPressEvent*)&event)->get_xpos();
            float ypos = ((MouseButtonPressEvent*)&event)->get_ypos();
            glm::vec3 ray_origin, ray_direction;
            create_ray_from_screen(xpos, ypos, g_context, g_camera, ray_origin, ray_direction);

            g_ray->update_buffer_vertices({ ray_origin.x, ray_origin.y, ray_origin.z, 0.8f, 0.8f, 0.2f,
                500.f * ray_direction.x + ray_origin.x, 500.f * ray_direction.y + ray_origin.y, 500.f * ray_direction.z + ray_origin.z, 0.8f, 0.8f, 0.2f });

            RayEvent ray_event(ray_origin, ray_direction);
            event_manager(ray_event);
        }
    }
}

int main() {
    Log::init();

    OpenGLContext context("Rubik's Cube", 1280, 720, event_manager);
    g_context = &context;

    Camera camera(&context);
    g_camera = &camera;

    Cube cube(2.f, 1.f, { BLUE, WHITE, RED, GREEN, YELLOW, ORANGE }, camera);
    g_cube = &cube;

    Model axes_lines;
    std::vector<float> buffer_lines = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f
    };

    axes_lines.buffer_vertices(buffer_lines);

    axes_lines.buffer_indices({ 0, 1, 2, 3, 4, 5 });

    Model ray;
    ray.buffer_vertices({ 0.0f, 0.0f, 0.0f, .8f, 0.8f, 0.2f,
        10.0f, 10.0f, 0.0f, .8f, 0.8f, 0.2f });
    ray.buffer_indices({ 0, 1 });

    g_ray = &ray;

    Shader color_shader("shaders/color.vertexShader", "shaders/color.fragmentShader");
    double last_time = glfwGetTime();
    int frames_count = 0;

    do {
        frames_count++;
        double cur_time = glfwGetTime();
        double delta = cur_time - last_time;

        if (delta > 1.0f) {
            LOG_INFO("FPS: {0}", frames_count / delta);
            last_time = cur_time;
            frames_count = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.on_update();
        cube.draw(color_shader);
        axes_lines.draw_lines(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * axes_lines.get_model_matrix());
        ray.draw_lines(color_shader, camera.get_projection_matrix() * camera.get_view_matrix() * ray.get_model_matrix());

        glfwSwapBuffers(context.get_window_handle());
        glfwPollEvents();

    } while (glfwGetKey(context.get_window_handle(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(context.get_window_handle()) == 0);

    glfwTerminate();

    return 0;
}
