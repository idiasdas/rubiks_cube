#pragma once
#include "rubiks_cube.h"
#include "renderer/model.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

Model get_piece(const float (& colors)[][3], glm::vec3 positions);
