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
        Creates the cube. Each piece is a model loaded on the GPU. The cube is centered on the origin by default.

        piece_size: The size of each cube representing a piece.
        gap_size: The space between adjacent pieces.
        colors: The colors of each face in order (RIGHT, TOP, FRONT, LEFT, BOTTOM, BACK).
    */
    Cube(const float piece_size, const float gap_size, const float (&colors)[6][3]);

    /*
        Creates the cube on the defined position. Each piece is a model loaded on the GPU.

        position: Coordinates (x, y, z) of the cube's center.
        piece_size: The size of each cube representing a piece.
        gap_size: The space between adjacent pieces.
        colors: The colors of each face in order (RIGHT, TOP, FRONT, LEFT, BOTTOM, BACK).
    */
    Cube(const float (&position)[3], const float piece_size, const float gap_size, const float (&colors)[6][3]);

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

    /*
        Reset cube to initial (solved) state.
    */
    void reset();

    /*
        Resizes the cube to the piece_size and gap_size
    */
    void resize(const float piece_size, const float gap_size);

private:
    Model get_piece(const float (&colors)[6][3], const glm::vec3 position);
    void set_piece_colors(float x, float y, float z, float (&colors)[6][3]);

    /*
        Return the coordinates of the piece relative to the cube's center.
        For example, (-1, 1, 1) is the piece on the left upper corner of the front face.
        To obtain the real coordinates of the piece you must first multiplicate each
        coordinate by piece_size + gap_size and then add this vector to the position of the cube.
    */
    std::tuple<float, float, float> get_piece_coordinates(const int piece_state_index) const;

private:
    float m_piece_size;
    float m_gap_size;
    float m_colors[6][3];
    float m_position[3];
    int m_state[27];
    std::vector<Model> m_pieces;
};
