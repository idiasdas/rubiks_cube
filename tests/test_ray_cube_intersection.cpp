/*
    Testing external modules initialization.
*/

#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "rubiks_cube.h"
#include "ray_picking.h"
#include "rubiks_cube/cube.h"

int main(int argc, char *argv[])
{
    float intersection_dist = -100.0f;
    glm::vec3 ray_origin = glm::vec3({0.0f, 0.0f, 3.f});
    glm::vec3 ray_direction = glm::vec3({0.0f, 0.0f, -1.0f});
    glm::mat4 model_mat(1.0f);
    IntersectionType inter_type = test_ray_cube_intersection(ray_origin, ray_direction, model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist == 2.f);

    ray_origin = glm::vec3({0.0f, 0.0f, 100.f});
    inter_type = test_ray_cube_intersection(ray_origin, ray_direction, model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist == 99.f);

    ray_origin = glm::vec3({0.0f, 0.0f, 1.f});
    ray_direction = glm::vec3({1.0f, 0.0f, 0.0f});
    inter_type = test_ray_cube_intersection(ray_origin, ray_direction, model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::undefined);

    ray_origin = glm::vec3({0.0f, 0.0f, 0.f});
    ray_direction = glm::vec3({1.0f, 0.0f, 0.0f});
    inter_type = test_ray_cube_intersection(ray_origin, ray_direction, model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist == -1.f);

    ray_origin = glm::vec3({0.0f, 0.0f, 1.5f});
    ray_direction = glm::vec3({1.0f, 0.0f, 0.0f});
    inter_type = test_ray_cube_intersection(ray_origin, ray_direction, model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::no_intersection);
}
