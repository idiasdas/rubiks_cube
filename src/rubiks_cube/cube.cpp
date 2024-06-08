#include "cube.h"

Cube::Cube(const float piece_size, const float gap_size, const float (&colors)[6][3])
{
    m_piece_size = piece_size;
    m_piece_gap = gap_size;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            m_colors[i][j] = colors[i][j];

    float step = m_piece_size + m_piece_gap;
    int piece_count = 0;
    float piece_colors[6][3];
    for (int y = 1; y >= -1; y--)
    {
        for (int z = 1; z >= -1; z--)
        {
            for (int x = -1; x <= 1; x++)
            {
                set_piece_colors(x, y, z, piece_colors);
                m_pieces.push_back(get_piece(piece_colors, glm::vec3(x * step, y * step, z * step)));
                std::cout << piece_count << "(" << x << ", " << y << ", " << z << ")\n";
                m_state[piece_count++] = piece_count;
            }
        }
    }
}

void Cube::set_piece_colors(float x, float y, float z, float (&colors)[6][3])
{
    // set all faces to black
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            colors[i][j] = 0.0f;

    // color piece right face
    if (x == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::right][i] = m_colors[Face::right][i];

    // color piece left face
    else if (x == -1)
        for (int i = 0; i < 3; i++)
            colors[Face::left][i] = m_colors[Face::left][i];

    // color piece up face
    if (y == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::top][i] = m_colors[Face::top][i];

    // color piece down face
    else if (y == -1)
        for (int i = 0; i < 3; i++)
            colors[Face::bottom][i] = m_colors[Face::bottom][i];

    // color piece front face
    if (z == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::front][i] = m_colors[Face::front][i];

    // color piece back face
    else if (z == -1)
        for (int i = 0; i < 3; i++)
            colors[Face::back][i] = m_colors[Face::back][i];
}

std::tuple<float, float, float> Cube::get_piece_coordinates(const int piece_state_index) const
{
    float y = piece_state_index / 9;
    float z = piece_state_index % 9 / 3;
    float x = piece_state_index % 9 % 3;
    y = (y - 1)*-1;
    z = (z - 1)*-1;
    x = (x - 1);
    return std::make_tuple(x, y, z);
}

Model Cube::get_piece(const float (& colors)[][3], const glm::vec3 position)
{
    Model piece;

    const std::vector<float> buffer = {
        // square facing x axis
        VB, colors[0][0], colors[0][1], colors[0][2],
        VD, colors[0][0], colors[0][1], colors[0][2],
        VF, colors[0][0], colors[0][1], colors[0][2],
        VD, colors[0][0], colors[0][1], colors[0][2],
        VF, colors[0][0], colors[0][1], colors[0][2],
        VH, colors[0][0], colors[0][1], colors[0][2],
        // square facing y axis
        VA, colors[1][0], colors[1][1], colors[1][2],
        VB, colors[1][0], colors[1][1], colors[1][2],
        VE, colors[1][0], colors[1][1], colors[1][2],
        VB, colors[1][0], colors[1][1], colors[1][2],
        VE, colors[1][0], colors[1][1], colors[1][2],
        VF, colors[1][0], colors[1][1], colors[1][2],
        // square facing z axis
        VA, colors[2][0], colors[2][1], colors[2][2],
        VB, colors[2][0], colors[2][1], colors[2][2],
        VC, colors[2][0], colors[2][1], colors[2][2],
        VB, colors[2][0], colors[2][1], colors[2][2],
        VC, colors[2][0], colors[2][1], colors[2][2],
        VD, colors[2][0], colors[2][1], colors[2][2],
        // square facing - x axis
        VA, colors[3][0], colors[3][1], colors[3][2],
        VE, colors[3][0], colors[3][1], colors[3][2],
        VC, colors[3][0], colors[3][1], colors[3][2],
        VE, colors[3][0], colors[3][1], colors[3][2],
        VC, colors[3][0], colors[3][1], colors[3][2],
        VG, colors[3][0], colors[3][1], colors[3][2],
        // square facing - y axis
        VC, colors[4][0], colors[4][1], colors[4][2],
        VG, colors[4][0], colors[4][1], colors[4][2],
        VD, colors[4][0], colors[4][1], colors[4][2],
        VG, colors[4][0], colors[4][1], colors[4][2],
        VD, colors[4][0], colors[4][1], colors[4][2],
        VH, colors[4][0], colors[4][1], colors[4][2],
        // square facing - z axis
        VE, colors[5][0], colors[5][1], colors[5][2],
        VF, colors[5][0], colors[5][1], colors[5][2],
        VG, colors[5][0], colors[5][1], colors[5][2],
        VF, colors[5][0], colors[5][1], colors[5][2],
        VG, colors[5][0], colors[5][1], colors[5][2],
        VH, colors[5][0], colors[5][1], colors[5][2],
    };

    std::vector<uint32_t> indices;
    for (int i = 0; i < buffer.size(); i++)
        indices.push_back(i);

    piece.buffer_vertices(buffer);
    piece.buffer_indices(indices);

    // TODO: Scale piece with m_piece_size
    piece.translate(position);

    return piece;
}

void Cube::draw(const Shader &shader, const Camera &camera) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, camera.get_projection_matrix() * camera.get_view_matrix() * piece.get_model_matrix());
}

void Cube::rotate_face(const Face face_index, const int turns)
{
    const float rotation_degrees = - turns * PI / 2.f;
    const int faces[6][3][3] = {RIGHT_FACE, TOP_FACE, FRONT_FACE, LEFT_FACE, BOTTOM_FACE, BACK_FACE};

    const int rotation_sign = (face_index < 3) ? -1 : 1;

    // change cube state
    for (int i = 0; i < turns; i++)
    {
        // rotate corners on state vector in 90 degrees clockwise
        int swap_piece_i = m_state[faces[face_index][2][0]];
        std::swap(m_state[faces[face_index][0][0]], swap_piece_i);
        std::swap(m_state[faces[face_index][0][2]], swap_piece_i);
        std::swap(m_state[faces[face_index][2][2]], swap_piece_i);
        std::swap(m_state[faces[face_index][2][0]], swap_piece_i);
        //rotate middle pieces on state vector in 90 degrees clockwise
        swap_piece_i = m_state[faces[face_index][1][0]];
        std::swap(m_state[faces[face_index][0][1]], swap_piece_i);
        std::swap(m_state[faces[face_index][1][2]], swap_piece_i);
        std::swap(m_state[faces[face_index][2][1]], swap_piece_i);
        std::swap(m_state[faces[face_index][1][0]], swap_piece_i);
    }

    const glm::vec3 axis[6] = {X_AXIS, Y_AXIS, Z_AXIS, X_AXIS, Y_AXIS, Z_AXIS};
    const glm::vec3 face_axis = axis[face_index];
    float axis_sign = 1;
    if (face_index > 2)
        axis_sign = -1;

    const float step = m_piece_size + m_piece_gap;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int piece_state_index = faces[face_index][i][j];
            auto[x, y, z] = get_piece_coordinates(piece_state_index);
            glm::vec3 piece_position = {x * step, y * step, z * step};

            m_pieces[m_state[piece_state_index]].set_translation_matrix(glm::mat4(1));
            m_pieces[m_state[piece_state_index]].rotate(rotation_degrees, axis_sign * face_axis);
            m_pieces[m_state[piece_state_index]].translate(piece_position);
        }
    }
}
