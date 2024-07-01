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

void screen_pos_to_world_ray(
	int mouse_x, int mouse_y,             // Mouse position, in pixels, from bottom-left corner of the window
	int screen_width, int screen_height,  // Window size, in pixels
	glm::mat4 view_matrix,                // Camera position and orientation
	glm::mat4 projection_matrix,          // Camera parameters (ratio, field of view, near and far planes)
	glm::vec3& out_origin,                // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	glm::vec3& out_direction              // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
){

	// The ray Start and End positions, in Normalized Device Coordinates
	glm::vec4 ray_start_NDC(
		((float)mouse_x/(float)screen_width  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)mouse_y/(float)screen_height - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
	);
	glm::vec4 ray_end_NDC(
		((float)mouse_x/(float)screen_width  - 0.5f) * 2.0f,
		((float)mouse_y/(float)screen_height - 0.5f) * 2.0f,
		0.0,
		1.0f
	);

	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	glm::mat4 inverse_projection_matrix = glm::inverse(projection_matrix);

	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	glm::mat4 inverse_view_matrix = glm::inverse(view_matrix);

	glm::vec4 ray_start_camera = inverse_projection_matrix * ray_start_NDC;    ray_start_camera/=ray_start_camera.w;
	glm::vec4 ray_start_world  = inverse_view_matrix       * ray_start_camera; ray_start_world /=ray_start_world .w;
	glm::vec4 ray_end_camera   = inverse_projection_matrix * ray_end_NDC;      ray_end_camera  /=ray_end_camera  .w;
	glm::vec4 ray_end_world    = inverse_view_matrix       * ray_end_camera;   ray_end_world   /=ray_end_world   .w;

	// Faster way (just one inverse)
	//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;

	glm::vec3 ray_dir_world(ray_end_world - ray_start_world);
	ray_dir_world = glm::normalize(ray_dir_world);

	out_origin = glm::vec3(ray_start_world);
	out_direction = glm::normalize(ray_dir_world);
}
