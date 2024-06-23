#include "collision.h"

bool ray_intersects_OBB(glm::vec3 ray_origin,
                        glm::vec3 ray_direction,
                        glm::vec3 mesh_min_coord,
                        glm::vec3 mesh_max_coord,
                        glm::mat4 model_matrix,
                        float & intersection_distance)
{
    float t_min = 0.0f;
    float t_max = 100000.0f;

    glm::vec3 OBB_world_position(model_matrix[3].x, model_matrix[3].y, model_matrix[3].z);
    glm::vec3 delta = OBB_world_position - ray_origin;

    {
        glm::vec3 x_axis(model_matrix[0].x, model_matrix[0].y, model_matrix[0].z);
        float e = glm::dot(x_axis, delta);
        float f = glm::dot(ray_direction, x_axis);

        if ( fabs(f) > 0.001f )
        {
            float t1 = (e+mesh_min_coord.x)/f; // Intersection with the "left" plane
            float t2 = (e+mesh_max_coord.x)/f; // Intersection with the "right" plane
        }
        else return false;
    }

    return false;
}
