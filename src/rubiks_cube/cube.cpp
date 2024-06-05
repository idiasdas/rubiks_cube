#include "cube.h"

Cube::Cube()
{
    Model piece_1;

    float colors_1[6][3] = {BLACK, WHITE, RED, GREEN, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_1, {-3.0f, 0.0f, 0.0f}));

    float colors_2[6][3] = {BLACK, WHITE, RED};
    m_pieces.push_back(get_piece(colors_2, {0.0f, 0.0f, 0.0f}));

    float colors_3[6][3] = {BLUE, WHITE, RED};
    m_pieces.push_back(get_piece(colors_3, {3.0f, 0.0f, 0.0f}));

    float colors_4[6][3] = {BLACK, WHITE, BLACK, GREEN};
    m_pieces.push_back(get_piece(colors_4, {-3.0f, 0.0f, -3.0f}));

    float colors_5[6][3] = {BLACK, WHITE};
    m_pieces.push_back(get_piece(colors_5, {0.0f, 0.0f, -3.0f}));

    float colors_6[6][3] = {BLUE, WHITE};
    m_pieces.push_back(get_piece(colors_6, {3.0f, 0.0f, -3.0f}));

    float colors_7[6][3] = {BLACK, WHITE, BLACK, GREEN, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_7, {-3.0f, 0.0f, -6.0f}));

    float colors_8[6][3] = {BLACK, WHITE, BLACK, BLACK, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_8, {0.0f, 0.0f, -6.0f}));

    float colors_9[6][3] = {BLUE, WHITE, BLACK, BLACK, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_9, {3.0f, 0.0f, -6.0f}));
}

void Cube::draw(Shader &shader, Camera &camera) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, camera.get_projection_matrix() * camera.get_view_matrix() * piece.get_model_matrix());
}
