#include "collision.h"

bool ray_intersects_OBB(glm::vec3 ray_origin,
                        glm::vec3 ray_direction,
                        glm::vec3 mesh_min_coord,
                        glm::vec3 mesh_max_coord,
                        glm::mat4 model_matrix,
                        float &intersection_distance)
{
    float t_min = 0.0f;
    float t_max = 100000.0f;

    glm::vec3 OBB_world_position(model_matrix[3].x, model_matrix[3].y, model_matrix[3].z);
    glm::vec3 delta = OBB_world_position - ray_origin;

    {
        glm::vec3 x_axis(model_matrix[0].x, model_matrix[0].y, model_matrix[0].z);
        float e = glm::dot(x_axis, delta);
        float f = glm::dot(ray_direction, x_axis);

        if (fabs(f) > 0.001f)
        {
            float t1 = (e + mesh_min_coord.x) / f; // Intersection with the "left" plane
            float t2 = (e + mesh_max_coord.x) / f; // Intersection with the "right" plane
            if (t1 > t2)                           // if wrong order
            {
                float w = t1;
                t1 = t2;
                t2 = w;
            }

            // t_max is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
            if (t2 < t_max)
                t_max = t2;
            // t_min is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
            if (t1 > t_min)
                t_min = t1;

            if (t_max < t_min)
                return false;
        }
        else if (-e + mesh_min_coord.x > 0.0f || -e + mesh_max_coord.x < 0.0f)
            return false;
    }

    // Test intersection with the 2 planes perpendicular to the OBB's Y axis
    // Exactly the same thing than above.
    {
        glm::vec3 yaxis(model_matrix[1].x, model_matrix[1].y, model_matrix[1].z);
        float e = glm::dot(yaxis, delta);
        float f = glm::dot(ray_direction, yaxis);

        if (fabs(f) > 0.001f)
        {

            float t1 = (e + mesh_min_coord.y) / f;
            float t2 = (e + mesh_max_coord.y) / f;

            if (t1 > t2)
            {
                float w = t1;
                t1 = t2;
                t2 = w;
            }

            if (t2 < t_max)
                t_max = t2;
            if (t1 > t_min)
                t_min = t1;
            if (t_min > t_max)
                return false;
        }
        else
        {
            if (-e + mesh_min_coord.y > 0.0f || -e + mesh_max_coord.y < 0.0f)
                return false;
        }
    }

    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
    // Exactly the same thing than above.
    {
        glm::vec3 zaxis(model_matrix[2].x, model_matrix[2].y, model_matrix[2].z);
        float e = glm::dot(zaxis, delta);
        float f = glm::dot(ray_direction, zaxis);

        if (fabs(f) > 0.001f)
        {

            float t1 = (e + mesh_min_coord.z) / f;
            float t2 = (e + mesh_max_coord.z) / f;

            if (t1 > t2)
            {
                float w = t1;
                t1 = t2;
                t2 = w;
            }

            if (t2 < t_max)
                t_max = t2;
            if (t1 > t_min)
                t_min = t1;
            if (t_min > t_max)
                return false;
        }
        else
        {
            if (-e + mesh_min_coord.z > 0.0f || -e + mesh_max_coord.z < 0.0f)
                return false;
        }
    }

    intersection_distance = t_min;
    return true;
}
