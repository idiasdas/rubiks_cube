#include "cube.h"

Cube::Cube()
{
    // top layer

    m_pieces.push_back(get_piece({BLACK, WHITE, RED, GREEN, BLACK, BLACK},      {-3.0f, 0.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLACK, WHITE, RED, BLACK, BLACK, BLACK},      {0.0f,  0.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLUE, WHITE, RED, BLACK, BLACK, BLACK},       {3.0f,  0.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLACK, WHITE, BLACK, GREEN, BLACK, BLACK},    {-3.0f, 0.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLACK, WHITE, BLACK, BLACK, BLACK, BLACK},    {0.0f,  0.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLUE, WHITE, BLACK, BLACK, BLACK, BLACK},     {3.0f,  0.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLACK, WHITE, BLACK, GREEN, BLACK, ORANGE},   {-3.0f, 0.0f, -6.0f}));
    m_pieces.push_back(get_piece({BLACK, WHITE, BLACK, BLACK, BLACK, ORANGE},   {0.0f,  0.0f, -6.0f}));
    m_pieces.push_back(get_piece({BLUE, WHITE, BLACK, BLACK, BLACK, ORANGE},    {3.0f,  0.0f, -6.0f}));

    // middle layer

    m_pieces.push_back(get_piece({BLACK, BLACK, RED, GREEN, BLACK, BLACK},      {-3.0f, -3.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, RED, BLACK, BLACK, BLACK},      {0.0f,  -3.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLUE, BLACK, RED, BLACK, BLACK, BLACK},       {3.0f,  -3.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, GREEN, BLACK, BLACK},    {-3.0f, -3.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},    {0.0f,  -3.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLUE, BLACK, BLACK, BLACK, BLACK, BLACK},     {3.0f,  -3.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, GREEN, BLACK, ORANGE},   {-3.0f, -3.0f, -6.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, BLACK, BLACK, ORANGE},   {0.0f,  -3.0f, -6.0f}));
    m_pieces.push_back(get_piece({BLUE, BLACK, BLACK, BLACK, BLACK, ORANGE},    {3.0f,  -3.0f, -6.0f}));
  
    // bottom layer

    m_pieces.push_back(get_piece({BLACK, BLACK, RED, GREEN, YELLOW, BLACK},     {-3.0f, -6.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, RED, BLACK, YELLOW, BLACK},     {0.0f,  -6.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLUE, BLACK, RED, BLACK, YELLOW, BLACK},      {3.0f,  -6.0f,  0.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, GREEN, YELLOW, BLACK},   {-3.0f, -6.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, BLACK, YELLOW, BLACK},   {0.0f,  -6.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLUE, BLACK, BLACK, BLACK, YELLOW, BLACK},    {3.0f,  -6.0f, -3.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, GREEN, YELLOW, ORANGE},  {-3.0f, -6.0f, -6.0f}));
    m_pieces.push_back(get_piece({BLACK, BLACK, BLACK, BLACK, YELLOW, ORANGE},  {0.0f,  -6.0f, -6.0f}));
    m_pieces.push_back(get_piece({BLUE, BLACK, BLACK, BLACK, YELLOW, ORANGE},   {3.0f,  -6.0f, -6.0f}));
}

void Cube::draw(Shader &shader, Camera &camera) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, camera.get_projection_matrix() * camera.get_view_matrix() * piece.get_model_matrix());
}
