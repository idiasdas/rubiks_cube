#pragma once
#include "rubiks_cube.h"

#include <algorithm>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cmath>
#include <queue>

#include "events.h"
#include "renderer/model.h"
#include "renderer/camera.h"
#include "ray_picking.h"


enum Face
{
    right = 0, top, front, left, bottom, back, none
};

enum class CubeState
{
    wait_input,
    rotate_face
};

struct PieceCoordinates
{
    float x;
    float y;
    float z;
};

struct Move
{
    Face face;
    int direction; // 1 for clockwise, -1 for counterclockwise
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
        Calls OpenGL draw for each piece.
    */
    void draw(const Shader &shader, const Camera &camera) const;

    /*
        Applies the rotation and translation to the pieces moved.
        A positve rotation degree leads to a clockwise face rotation.
        Althought this can be counterintuitive from a linear algebra perspective,
        it is easier to consider the standard cube rotation to be clockwise.
    */
    void rotate_face(const Face face_index, const float rotation_degrees);

    /*
        Reset cube to initial (solved) state.
    */
    void reset();

    /*
        Every frame it runs the animations for the movement queue.
    */
    void on_update();

    /*
        If a face has been rotated in between 0 and 90 degress. It completes the rotation to the nearest angle.
    */
    void round_pieces_positions();

    /*
        Treats input events.
    */
    void on_event(Event& event);

    /*
        Resizes the cube to the piece_size and gap_size
    */
    void resize(const float piece_size, const float gap_size);

    Face ray_pick(glm::vec3 ray_origin, glm::vec3 ray_direction) const;


private:
    Model get_piece(const float (&colors)[6][3], const glm::vec3 position);
    void set_piece_colors(const PieceCoordinates& piece_coordinates, float (&colors)[6][3]);
    bool is_piece_on_face(const PieceCoordinates& piece_coordinates, const Face face_index) const;
    void cube_control(const int key, const int action);
    void run_animation();

    /*
        Return the coordinates of the piece relative to the cube's center.
        For example, (-1, 1, 1) is the piece on the left upper corner of the front face.
        To obtain the real coordinates of the piece you must first multiplicate each
        coordinate by piece_size + gap_size and then add this vector to the position of the cube.
    */
    PieceCoordinates get_original_piece_coordinates(const int piece_index) const;


private:
    float m_piece_size;
    float m_gap_size;
    float m_colors[6][3];
    std::vector<Model> m_pieces;
    std::vector<PieceCoordinates> m_pieces_coordinates;
    std::queue<Move> m_moves;
    float m_animation_speed;
};
