#include "ray_picking.h"

IntersectionType test_ray_plane_intersection(const glm::vec3 ray_origin,
                                             const glm::vec3 ray_direction,
                                             const glm::mat4 plane_model_matrix,
                                             float *const intersection_distance)
{
    const glm::vec3 plane_center = glm::vec3(plane_model_matrix[3].x, plane_model_matrix[3].y, plane_model_matrix[3].z);
    const glm::vec3 ray_center_vec = ray_origin - plane_center;
    const glm::vec3 plane_normal = glm::vec3(plane_model_matrix[2].x, plane_model_matrix[2].y, plane_model_matrix[2].z);
    const double ray_center_dot_normal = glm::dot(ray_center_vec, plane_normal);
    const double ray_dir_normal_product = glm::dot(ray_direction, plane_normal);

    if (std::abs(ray_dir_normal_product) > EPS)
    {
        *intersection_distance = - ray_center_dot_normal / ray_dir_normal_product;
        return IntersectionType::intersection;
    }
    else if (std::abs(ray_center_dot_normal) <= EPS)
    {
        return IntersectionType::undefined;
    }

    return IntersectionType::no_intersection;
}

IntersectionType test_ray_cube_intersection(const glm::vec3 ray_origin,
                                            const glm::vec3 ray_direction,
                                            const glm::mat4 cube_model_matrix,
                                            float *const intersection_distance)
{
    const glm::vec3 cube_center = glm::vec3(cube_model_matrix[3].x, cube_model_matrix[3].y, cube_model_matrix[3].z);
    const glm::vec3 ray_center_vector = ray_origin - cube_center;

    float min_out_dist = 10000.0f;
    float max_in_dist = -10000.0f;

    for (int i = 0; i < 3; i++)
    {
        glm::vec3 normal_vector = glm::vec3(cube_model_matrix[i].x, cube_model_matrix[i].y, cube_model_matrix[i].z);
        float ray_normal_product = glm::dot(ray_direction, normal_vector);
        float ray_center_normal_dot = glm::dot(ray_center_vector, normal_vector);
        float f1 = - ray_center_normal_dot + 1.f; // assuming standard cube on origin with length 2.f
        float f2 = - ray_center_normal_dot - 1.f;
        if (std::abs(ray_normal_product) > EPS) // ray direction is not parallel to the faces
        {
            float in_dist = f1 / ray_normal_product;
            float out_dist = f2 / ray_normal_product;

            if (in_dist > out_dist)
            {
                std::swap(in_dist, out_dist);
            }

            max_in_dist = std::max(in_dist, max_in_dist);
            min_out_dist = std::min(out_dist, min_out_dist);

            if (max_in_dist > min_out_dist)
            {
                return IntersectionType::no_intersection;
            }
        }
        else // ray direction is parallel or almost parallel to the faces
        {
            if (f1 < -EPS || f2 > EPS)
            {
                // ray is parallalel to the face and outisde the cube
                return IntersectionType::no_intersection;
            }
            else if (std::abs(f1) <= EPS || std::abs(f2) <= EPS)
            {
                // ray is parallel to the face and on the face
                return IntersectionType::undefined;
            }
        }
    }

    *intersection_distance = max_in_dist;
    return IntersectionType::intersection;
}
