#pragma once
#include "rubiks_cube.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "renderer/model.h"
#include "renderer/camera.h"

enum FaceIndex
{
    right = 0, up, front, left, down, back
};

class Cube
{
public:
    Cube(const float piece_size, const float gap_size, const float (& colors)[6][3]);
    void draw(Shader &shader, Camera &camera) const;

private:
    Model get_piece(const float (&colors)[][3], glm::vec3 position);
    void set_piece_colors(float x, float y, float z, float (&colors)[6][3]);

private:
    float m_piece_size;
    float m_piece_gap;
    float m_colors[6][3];
    std::vector<Model> m_pieces;
};
