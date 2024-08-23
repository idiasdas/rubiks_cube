#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ray_picking.h"
#include "rubiks_cube/cube.h"

int main(int argc, char *argv[])
{
    float intersection_dist = -100.0f;
    glm::vec3 ray_origin = glm::vec3({0.0f, 0.0f, 20.f});
    glm::vec3 ray_direction = glm::vec3({0.0f, 0.0f, -1.0f});
    glm::mat4 model_mat(1.0f);

    IntersectionType inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                                              model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist == 20.f);

    ray_direction = glm::vec3({0.0f, 0.0f, 1.0f});

    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist == -20.f);

    ray_origin = glm::vec3(0.0f, 0.0f, 20.f);
    ray_direction = glm::vec3(1.0f, 0.0f, 0.0f);
    intersection_dist = -100.0f;

    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::no_intersection);
    assert(intersection_dist == -100.f);

    ray_origin = glm::vec3(0.0f, 0.0f, 20.f);
    ray_direction = glm::vec3(-1.0f, 0.0f, -1.0f);
    model_mat = glm::rotate(glm::mat4(1), PI / 4.f, glm::vec3(1, 0, 0)) * model_mat;

    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist > 0.0f);

    ray_origin = glm::vec3(0.0f, 0.0f, 20.f);
    ray_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    model_mat = glm::translate(glm::mat4(1), glm::vec3(0, 0, 5));
    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);
    assert(intersection_dist == 15.f);

    ray_origin = glm::vec3(0.0f, 0.0f, 5.1f);
    ray_direction = glm::vec3(-1.0f, -1.0f, 0.0f);
    model_mat = glm::translate(glm::mat4(1), glm::vec3(0, 0, 5));
    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::no_intersection);

    ray_origin = glm::vec3(0.0f, 0.0f, 4.9f);
    ray_direction = glm::vec3(-1.0f, -1.0f, 0.0f);
    model_mat = glm::translate(glm::mat4(1), glm::vec3(0, 0, 5));
    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::no_intersection);

    ray_origin = glm::vec3(0.0f, 0.0f, 5.f);
    ray_direction = glm::vec3(1.0f, 1.0f, 0.0f);

    inter_type = test_ray_plane_intersection(ray_origin, ray_direction,
                                             model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::undefined);
}
