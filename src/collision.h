#pragma once

#include "rubiks_cube.h"

#include "glm/glm.hpp"

bool ray_intersects_OBB(
    glm::vec3 ray_origin,        // Ray origin, in world space
	glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
	glm::vec3 mesh_min_coord,    // Minimum X,Y,Z coords of the mesh when not transformed at all.
	glm::vec3 mesh_max_coord,    // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
	glm::mat4 model_matrix,      // Transformation applied to the mesh (which will thus be also applied to its bounding box)
	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
);
