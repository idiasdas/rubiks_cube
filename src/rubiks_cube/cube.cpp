#include "cube.h"

Cube::Cube(const float piece_size, const float gap_size, const float (&colors)[6][3])
{
    m_piece_size = piece_size;
    m_piece_gap = gap_size;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m_colors[i][j] = colors[i][j];

    float step = m_piece_size + m_piece_gap;

    Model piece;
    float piece_colors[6][3];
    for (int x = -1; x <= 1; x++)
    {
        for (int z = 1; z >= 1; z--)
        {
            for (int y = 1; y >= -1; y--)
            {
                set_piece_colors(x, y, z, piece_colors);
                m_pieces.push_back(get_piece(piece_colors, glm::vec3(x * step, y * step, z * step)));
            }
        }
    }
}

void Cube::set_piece_colors(float x, float y, float z, float (&colors)[6][3])
{
    // set all faces to black
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            colors[i][j] = 0.0f;

    // color piece right face
    if (x == 1)
        for (int i = 0; i < 3; i++)
            colors[FaceIndex::right][i] = m_colors[FaceIndex::right][i];

    // color piece left face
    else if (x == -1)
        for (int i = 0; i < 3; i++)
            colors[3][FaceIndex::left] = m_colors[FaceIndex::left][i];

    // color piece up face
    if (y == 1)
        for (int i = 0; i < 3; i++)
            colors[FaceIndex::up][i] = m_colors[FaceIndex::up][i];

    // color piece down face
    else if (y == -1)
        for (int i = 0; i < 3; i++)
            colors[FaceIndex::down][i] = m_colors[FaceIndex::down][i];

    // color piece front face
    if (z == 1)
        for (int i = 0; i < 3; i++)
            colors[FaceIndex::front][i] = m_colors[FaceIndex::front][i];

    // color piece back face
    else if (z == -1)
        for (int i = 0; i < 3; i++)
            colors[FaceIndex::back][i] = m_colors[FaceIndex::back][i];
}

void Cube::draw(Shader &shader, Camera &camera) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, camera.get_projection_matrix() * camera.get_view_matrix() * piece.get_model_matrix());
}

Model Cube::get_piece(const float (& colors)[][3], glm::vec3 position)
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
    piece.translate(position);

    return piece;
}
