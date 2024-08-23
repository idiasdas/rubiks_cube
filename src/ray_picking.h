#pragma once

#include <rubiks_cube.h>

#include "renderer/opengl-context.h"
#include "renderer/camera.h"

enum class IntersectionType : unsigned char {
    undefined,
    intersection,
    no_intersection
};

IntersectionType test_ray_plane_intersection(const glm::vec3 ray_origin,
                                             const glm::vec3 ray_direction,
                                             const glm::mat4 plane_model_matrix,
                                             float * const intersection_distance);

IntersectionType test_ray_cube_intersection(const glm::vec3 ray_origin,
                                            const glm::vec3 ray_direction,
                                            const glm::mat4 cube_model_matrix,
                                            float * const intersection_distance
                                            );

void create_ray_from_screen(float xpos, float ypos, OpenGLContext* context, Camera* camera, glm::vec3 &ray_origin, glm::vec3 &ray_direction);
