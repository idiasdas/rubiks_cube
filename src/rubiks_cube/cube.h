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
    Cube(const float piece_size, const float gap_size, const float (&colors)[6][3], Camera & camera);
    void draw(const Shader &shader) const;
    void rotate_face(const Face face_index, const float rotation_degrees);
    void reset();
    void on_update();
    void round_pieces_world_positions();
    void on_event(Event& event);
    void resize(const float piece_size, const float gap_size);
    Face ray_pick(glm::vec3 ray_origin, glm::vec3 ray_direction) const;

private:
    Model get_piece(const float (&colors)[6][3], const glm::vec3 position);
    void set_piece_colors(const PieceCoordinates& piece_coordinates, float (&colors)[6][3]);
    bool is_piece_on_face(const PieceCoordinates& piece_coordinates, const Face face_index) const;
    void cube_control(const int key, const int action);
    void run_animation();
    PieceCoordinates get_original_piece_relative_coordinates(const int piece_index) const;

private:
    float m_piece_size;
    float m_gap_size;
    float m_colors[6][3];
    std::vector<Model> m_pieces;
    std::vector<PieceCoordinates> m_pieces_relative_coordinates;
    std::queue<Move> m_moves;
    float m_animation_speed;
    Camera* m_camera;
};
