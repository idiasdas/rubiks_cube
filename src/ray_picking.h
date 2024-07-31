#pragma once

#include <rubiks_cube.h>

enum class IntersectionType : unsigned char
{
    undefined,
    intersection,
    no_intersection
};

IntersectionType test_ray_plane_intersection(const glm::vec3 ray_origin,
                                             const glm::vec3 ray_direction,
                                             const glm::mat4 plane_model_matrix,
                                             float * const intersection_distance);

/*
This function determines the intersection distance between the ray and the planes of the cube's faces.
Finally, it returns whether the ray passes within the cube or not.
In some edge cases, the result can be undefined, such as when the ray is parallel to some face. In practice, this should rarely happen.

This function returns whether the intersection happens or not and when it does, it writes the distance on the intersection_distance parameter.

Ray-plane intersection can be determined as follows:

                           * P -> ray_origin
                           |
                           ∨ -> ray_direction

                   ______________
                  /        * P_0 /
                 /  n           /
                /   ^          /
               /    |         /
              /     * Q      / Q is a point on the plane and n is the normal vector (not necessarily unitary)
             /              /
            /_____________ /   P_0 is the intersection point

            P_0 = P + v*t, such that t is the distance from the ray origin to the intersection point P_0

            P_0 - Q if a vector on the plane and therefore, ortogonal to n:

            (P_0 - Q).n = 0
            (P + v*t - Q).n = 0
            (P - Q).n + (v*t).n = 0

            t = (Q - P).n / (v.n)

When v.n is near zero, if means the ray_direction is almost parallel to the face with normal n.
We must then check whether the ray's origin is outside the cube or inside.
If it is on the cube's face, the the result is undefined.

*/
IntersectionType test_ray_cube_intersection(const glm::vec3 ray_origin,
                                            const glm::vec3 ray_direction,
                                            const float cube_size, // size of side / 2
                                            const glm::mat4 cube_model_matrix,
                                            float * const intersection_distance
                                            );
