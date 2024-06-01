#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum class PieceType : int
{
    center, middle, corner,
};

std::vector<float> get_piece(PieceType piece_type, float color[][3]);
