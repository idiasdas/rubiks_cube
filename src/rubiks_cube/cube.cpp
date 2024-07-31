#include "cube.h"

Cube::Cube(const float piece_size, const float gap_size, const float (&colors)[6][3])
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            m_colors[i][j] = colors[i][j];

    float step = m_piece_size + m_gap_size;
    float piece_colors[6][3];
    for (int z = -1; z <= 1; z++)
    {
        for (int y = -1; y <= 1; y++)
        {
            for (int x = -1; x <= 1; x++)
            {
                PieceCoordinates piece_coordinates = {(float) x, (float) y, (float) z};
                set_piece_colors(piece_coordinates, piece_colors);
                m_pieces.push_back(get_piece(piece_colors, glm::vec3({x * step, y * step, z * step})));
                m_pieces_coordinates.push_back(piece_coordinates);
            }
        }
    }
}

void Cube::set_piece_colors(const PieceCoordinates& piece_coordinates, float (&colors)[6][3])
{
    // set all faces to black
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            colors[i][j] = 0.0f;

    // color piece right face
    if (piece_coordinates.x == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::right][i] = m_colors[Face::right][i];

    // color piece left face
    else if (piece_coordinates.x == -1)
        for (int i = 0; i < 3; i++)
            colors[Face::left][i] = m_colors[Face::left][i];

    // color piece top face
    if (piece_coordinates.y == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::top][i] = m_colors[Face::top][i];

    // color piece bottom face
    else if (piece_coordinates.y == -1)
        for (int i = 0; i < 3; i++)
            colors[Face::bottom][i] = m_colors[Face::bottom][i];

    // color piece front face
    if (piece_coordinates.z == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::front][i] = m_colors[Face::front][i];

    // color piece back face
    else if (piece_coordinates.z == -1)
        for (int i = 0; i < 3; i++)
            colors[Face::back][i] = m_colors[Face::back][i];
}

bool Cube::is_piece_on_face(const PieceCoordinates& piece_coordinates, const Face face_index) const
{
    switch (face_index)
    {
    case Face::right:
        return piece_coordinates.x == 1.f;
    case Face::top:
        return piece_coordinates.y == 1.f;
    case Face::front:
        return piece_coordinates.z == 1.f;
    case Face::left:
        return piece_coordinates.x == -1.f;
    case Face::bottom:
        return piece_coordinates.y == -1.f;
    case Face::back:
        return piece_coordinates.z == -1.f;
    default:
        return false;
    }
}

PieceCoordinates Cube::get_original_piece_coordinates(const int piece_index) const
{
    PieceCoordinates piece_coordinates;
    piece_coordinates.x = (float) (piece_index % 3) - 1;
    piece_coordinates.y = (float) ((piece_index / 3) % 3) - 1;
    piece_coordinates.z = (float) (piece_index / 9) - 1;
    return piece_coordinates;
}

Face Cube::ray_pick(glm::vec3 ray_origin, glm::vec3 ray_direction) const
{
    IntersectionType intersection_result;
    float dist = 10000.0f;
    float closest_dist = 10000.0f;


    int closest_piece_hit = -1;
    for (int i = 0; i < (int) m_pieces.size(); i++)
    {
        intersection_result = test_ray_cube_intersection(ray_origin, ray_direction, m_pieces[i].get_model_matrix(), &dist);
        if (intersection_result == IntersectionType::intersection && dist < closest_dist)
        {
            closest_piece_hit = i;
            closest_dist = dist;
        }
    }

    if (closest_piece_hit == -1)
        return Face::none;

    LOG_INFO("Intersection with piece {0} ({1}, {2}, {3})", closest_piece_hit, m_pieces_coordinates[closest_piece_hit].x, m_pieces_coordinates[closest_piece_hit].y, m_pieces_coordinates[closest_piece_hit].z);

    return Face::none;
}

void Cube::reset()
{
    float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++)
    {
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].set_rotation_matrix(glm::mat4(1));
        auto[x, y, z] = get_original_piece_coordinates(i);
        m_pieces_coordinates[i] = {x, y, z};
        m_pieces[i].translate({x * step, y * step, z * step});
    }
}

void Cube::round_pieces_positions()
{
    const float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++)
    {
        auto[x, y, z] = m_pieces_coordinates[i];
        m_pieces_coordinates[i] = {std::round(x), std::round(y), std::round(z)};
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].translate({std::round(x) * step, std::round(y) * step, std::round(z) * step});
    }
}

void Cube::resize(const float piece_size, const float gap_size)
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;
    const float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++)
    {
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].set_scale_matrix(glm::mat4(1));
        auto[x, y, z] = m_pieces_coordinates[i];
        m_pieces[i].scale({m_piece_size / 2.f, m_piece_size / 2.f, m_piece_size / 2.f});
        m_pieces[i].translate({x * step, y * step, z * step});
    }
}

Model Cube::get_piece(const float (&colors)[6][3], const glm::vec3 position)
{
    Model piece;

    const std::vector<float> buffer = {
        // square facing x axis
        VB, colors[0][0], colors[0][1], colors[0][2],
        VD, colors[0][0], colors[0][1], colors[0][2],
        VF, colors[0][0], colors[0][1], colors[0][2],
        VF, colors[0][0], colors[0][1], colors[0][2],
        VD, colors[0][0], colors[0][1], colors[0][2],
        VH, colors[0][0], colors[0][1], colors[0][2],
        // square facing y axis
        VA, colors[1][0], colors[1][1], colors[1][2],
        VB, colors[1][0], colors[1][1], colors[1][2],
        VE, colors[1][0], colors[1][1], colors[1][2],
        VE, colors[1][0], colors[1][1], colors[1][2],
        VB, colors[1][0], colors[1][1], colors[1][2],
        VF, colors[1][0], colors[1][1], colors[1][2],
        // square facing z axis
        VA, colors[2][0], colors[2][1], colors[2][2],
        VC, colors[2][0], colors[2][1], colors[2][2],
        VB, colors[2][0], colors[2][1], colors[2][2],
        VB, colors[2][0], colors[2][1], colors[2][2],
        VC, colors[2][0], colors[2][1], colors[2][2],
        VD, colors[2][0], colors[2][1], colors[2][2],
        // square facing - x axis
        VA, colors[3][0], colors[3][1], colors[3][2],
        VE, colors[3][0], colors[3][1], colors[3][2],
        VC, colors[3][0], colors[3][1], colors[3][2],
        VC, colors[3][0], colors[3][1], colors[3][2],
        VE, colors[3][0], colors[3][1], colors[3][2],
        VG, colors[3][0], colors[3][1], colors[3][2],
        // square facing - y axis
        VC, colors[4][0], colors[4][1], colors[4][2],
        VG, colors[4][0], colors[4][1], colors[4][2],
        VD, colors[4][0], colors[4][1], colors[4][2],
        VD, colors[4][0], colors[4][1], colors[4][2],
        VG, colors[4][0], colors[4][1], colors[4][2],
        VH, colors[4][0], colors[4][1], colors[4][2],
        // square facing - z axis
        VE, colors[5][0], colors[5][1], colors[5][2],
        VF, colors[5][0], colors[5][1], colors[5][2],
        VG, colors[5][0], colors[5][1], colors[5][2],
        VG, colors[5][0], colors[5][1], colors[5][2],
        VF, colors[5][0], colors[5][1], colors[5][2],
        VH, colors[5][0], colors[5][1], colors[5][2],
    };

    std::vector<uint32_t> indices;
    for (size_t i = 0; i < buffer.size() / 6; i++)
        indices.push_back(i);

    piece.buffer_vertices(buffer);
    piece.buffer_indices(indices);
    piece.scale({m_piece_size / 2.f, m_piece_size / 2.f, m_piece_size / 2.f});
    piece.translate(position);

    return piece;
}

void Cube::draw(const Shader &shader, const Camera &camera) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, camera.get_projection_matrix() * camera.get_view_matrix() * piece.get_model_matrix());
}

void Cube::rotate_face(const Face face_index, const float rotation_degrees)
{
    const float correct_rotation_degrees = -rotation_degrees;
    const glm::vec3 axis[6] = {X_AXIS, Y_AXIS, Z_AXIS, X_AXIS, Y_AXIS, Z_AXIS};
    const glm::vec3 face_axis = axis[face_index];
    // if the face is left, bottom or back, the rotation is counter-clockwise along the standard axis
    const float axis_sign = (face_index > 2) ? -1 : 1;
    const float step = m_piece_size + m_gap_size;

    for (int i = 0; i < 27; i++)
    {
        if (is_piece_on_face(m_pieces_coordinates[i], face_index))
        {
            // send piece to the origin
            m_pieces[i].set_translation_matrix(glm::mat4(1));
            // rotate piece
            m_pieces[i].rotate(correct_rotation_degrees, face_axis * axis_sign);

            // update piece coordinates
            glm::vec4 new_coordinates = {m_pieces_coordinates[i].x, m_pieces_coordinates[i].y, m_pieces_coordinates[i].z, 1};
            new_coordinates = glm::rotate(glm::mat4(1), correct_rotation_degrees, face_axis * axis_sign) * new_coordinates;
            m_pieces_coordinates[i] = {new_coordinates.x, new_coordinates.y, new_coordinates.z};

            // round piece coordinates on the face axis so that we can elimitate floating point errors and correctly identify the pieces on the face
            switch (face_index)
            {
            case Face::right:
                m_pieces_coordinates[i].x = 1.f;
                break;
            case Face::left:
                m_pieces_coordinates[i].x = -1.f;
                break;
            case Face::top:
                m_pieces_coordinates[i].y = 1.f;
                break;
            case Face::bottom:
                m_pieces_coordinates[i].y = -1.f;
                break;
            case Face::front:
                m_pieces_coordinates[i].z = 1.f;
                break;
            case Face::back:
                m_pieces_coordinates[i].z = -1.f;
                break;

            default:
                break;
            }

            // translate piece to its new position
            m_pieces[i].translate({m_pieces_coordinates[i].x * step, m_pieces_coordinates[i].y * step, m_pieces_coordinates[i].z * step});
        }
    }
}
