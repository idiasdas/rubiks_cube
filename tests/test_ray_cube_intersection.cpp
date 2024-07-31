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
    glm::vec3 ray_origin = glm::vec3({0.0f, 0.0f, 20.f});
    glm::vec3 ray_direction = glm::vec3({0.0f, 0.0f, 1.0f});
    glm::mat4 model_mat(1.0f);

    IntersectionType inter_type = test_ray_cube_intersection(ray_origin, ray_direction,
                                                             1.0f, model_mat, &intersection_dist);

    assert(inter_type == IntersectionType::intersection);

    // if (intersection_dist != -19.f)
    // {
    //     std::cout << "Check 2 - Unexpected intersection distance: " << intersection_dist << std::endl;
    //     exit(EXIT_FAILURE);
    // }

    // ray_direction = glm::vec3({0.0f, 0.0f, -1.0f});

    // inter_type = test_ray_cube_intersection(ray_origin, ray_direction,
    //                                         1.0f, model_mat, &intersection_dist);

    // if (inter_type != IntersectionType::intersection)
    // {
    //     std::cout << "Check 3 - No intersection.";
    //     exit(EXIT_FAILURE);
    // }

    // if (intersection_dist != 19.f)
    // {
    //     std::cout << "Check 4 - Unexpected intersection distance: " << intersection_dist << std::endl;
    //     exit(EXIT_FAILURE);
    // }
}
