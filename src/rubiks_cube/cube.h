#pragma once
#include "rubiks_cube.h"

#include <algorithm>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "renderer/model.h"
#include "renderer/camera.h"

enum Face
{
    right = 0, top, front, left, bottom, back
};

class Cube
{
public:
    /*
        Creates the cube. Each piece is a model loaded on the GPU.
    */
    Cube(const float piece_size, const float gap_size, const float (&colors)[6][3]);

    /*
        Calls OpenGL draw for each piece.
    */
    void draw(const Shader &shader, const Camera &camera) const;

    /*
        Updates the vector m_state with the new pieces positions.
        Applies the clockwise rotation and translation to the pieces moved.
        Every rotation is clockwise for now.
    */
    void rotate_face(const Face face_index, const int turns);

    /*
        Reades the keyboard inputs from OpenGL and apply the corresponding moves to the cube.
    */
    void read_controls(OpenGLContext *const openGL_context);

private:
    Model get_piece(const float (&colors)[][3], const glm::vec3 position);
    void set_piece_colors(float x, float y, float z, float (&colors)[6][3]);
    std::tuple<float, float, float> get_piece_coordinates(const int piece_state_index) const;

private:
    float m_piece_size;
    float m_piece_gap;
    float m_colors[6][3];
    int m_state[27];
    std::vector<Model> m_pieces;
};
