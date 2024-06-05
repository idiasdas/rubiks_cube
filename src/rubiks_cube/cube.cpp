#include "cube.h"

Cube::Cube()
{
    // top layer

    float colors_1[6][3] = {BLACK, WHITE, RED, GREEN, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_1, {-3.0f, 0.0f, 0.0f}));

    float colors_2[6][3] = {BLACK, WHITE, RED, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_2, {0.0f, 0.0f, 0.0f}));

    float colors_3[6][3] = {BLUE, WHITE, RED, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_3, {3.0f, 0.0f, 0.0f}));

    float colors_4[6][3] = {BLACK, WHITE, BLACK, GREEN, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_4, {-3.0f, 0.0f, -3.0f}));

    float colors_5[6][3] = {BLACK, WHITE, BLACK, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_5, {0.0f, 0.0f, -3.0f}));

    float colors_6[6][3] = {BLUE, WHITE, BLACK, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_6, {3.0f, 0.0f, -3.0f}));

    float colors_7[6][3] = {BLACK, WHITE, BLACK, GREEN, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_7, {-3.0f, 0.0f, -6.0f}));

    float colors_8[6][3] = {BLACK, WHITE, BLACK, BLACK, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_8, {0.0f, 0.0f, -6.0f}));

    float colors_9[6][3] = {BLUE, WHITE, BLACK, BLACK, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_9, {3.0f, 0.0f, -6.0f}));

    // middle layer

    float colors_10[6][3] = {BLACK, BLACK, RED, GREEN, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_10, {-3.0f, -3.0f, 0.0f}));

    float colors_11[6][3] = {BLACK, BLACK, RED, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_11, {0.0f, -3.0f, 0.0f}));

    float colors_12[6][3] = {BLUE, BLACK, RED, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_12, {3.0f, -3.0f, 0.0f}));

    float colors_13[6][3] = {BLACK, BLACK, BLACK, GREEN, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_13, {-3.0f, -3.0f, -3.0f}));

    float colors_14[6][3] = {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_14, {0.0f, -3.0f, -3.0f}));

    float colors_15[6][3] = {BLUE, BLACK, BLACK, BLACK, BLACK, BLACK};
    m_pieces.push_back(get_piece(colors_15, {3.0f, -3.0f, -3.0f}));

    float colors_16[6][3] = {BLACK, BLACK, BLACK, GREEN, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_16, {-3.0f, -3.0f, -6.0f}));

    float colors_17[6][3] = {BLACK, BLACK, BLACK, BLACK, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_17, {0.0f, -3.0f, -6.0f}));

    float colors_18[6][3] = {BLUE, BLACK, BLACK, BLACK, BLACK, ORANGE};
    m_pieces.push_back(get_piece(colors_18, {3.0f, -3.0f, -6.0f}));

    // bottom layer

    float colors_19[6][3] = {BLACK, BLACK, RED, GREEN, YELLOW, BLACK};
    m_pieces.push_back(get_piece(colors_19, {-3.0f, -6.0f, 0.0f}));

    float colors_20[6][3] = {BLACK, BLACK, RED, BLACK, YELLOW, BLACK};
    m_pieces.push_back(get_piece(colors_20, {0.0f, -6.0f, 0.0f}));

    float colors_21[6][3] = {BLUE, BLACK, RED, BLACK, YELLOW, BLACK};
    m_pieces.push_back(get_piece(colors_21, {3.0f, -6.0f, 0.0f}));

    float colors_22[6][3] = {BLACK, BLACK, BLACK, GREEN, YELLOW, BLACK};
    m_pieces.push_back(get_piece(colors_22, {-3.0f, -6.0f, -3.0f}));

    float colors_23[6][3] = {BLACK, BLACK, BLACK, BLACK, YELLOW, BLACK};
    m_pieces.push_back(get_piece(colors_23, {0.0f, -6.0f, -3.0f}));

    float colors_24[6][3] = {BLUE, BLACK, BLACK, BLACK, YELLOW, BLACK};
    m_pieces.push_back(get_piece(colors_24, {3.0f, -6.0f, -3.0f}));

    float colors_25[6][3] = {BLACK, BLACK, BLACK, GREEN, YELLOW, ORANGE};
    m_pieces.push_back(get_piece(colors_25, {-3.0f, -6.0f, -6.0f}));

    float colors_26[6][3] = {BLACK, BLACK, BLACK, BLACK, YELLOW, ORANGE};
    m_pieces.push_back(get_piece(colors_26, {0.0f, -6.0f, -6.0f}));

    float colors_27[6][3] = {BLUE, BLACK, BLACK, BLACK, YELLOW, ORANGE};
    m_pieces.push_back(get_piece(colors_27, {3.0f, -6.0f, -6.0f}));
}

void Cube::draw(Shader &shader, Camera &camera) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, camera.get_projection_matrix() * camera.get_view_matrix() * piece.get_model_matrix());
}
