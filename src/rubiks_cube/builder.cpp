#include "builder.h"

/*
    This function returns the 3 different types of pieces in the rubik's cube:
        - center: one square facing the z-axis
        - middle: one square facing the z-axis + one square facing the y-axis
        - corner: one square facing the z-axis + one square facing the y-axis + one square facing the x-axis

    The output vector contain each vertex xyz coordinates followed by its corresponding color.

    ABCD -> cube's front face
    EFGH -> cube's back face

            E----F
    A----B  |    |
    |    |  G----H
    C----D
*/
std::vector<float> get_piece(PieceType piece_type, float color[][3])
{
    std::vector<float> vertices_positions = {
        // square facing z-axis
        -1.0f,  1.0f,  1.0f, //A
         1.0f,  1.0f,  1.0f, //B
        -1.0f, -1.0f,  1.0f, //C
         1.0f,  1.0f,  1.0f, //B
        -1.0f, -1.0f,  1.0f, //C
         1.0f, -1.0f,  1.0f, //D
        // square facing y-axis
        -1.0f,  1.0f,  1.0f, //A
         1.0f,  1.0f,  1.0f, //B
        -1.0f,  1.0f, -1.0f, //E
         1.0f,  1.0f,  1.0f, //B
        -1.0f,  1.0f, -1.0f, //E
         1.0f,  1.0f, -1.0f, //F
        // square facing x-axis
         1.0f,  1.0f,  1.0f, //B
         1.0f, -1.0f,  1.0f, //D
         1.0f,  1.0f, -1.0f, //F
         1.0f, -1.0f,  1.0f, //D
         1.0f,  1.0f, -1.0f, //F
         1.0f, -1.0f, -1.0f, //D
    };

    std::vector<float> buffer;

    // add square facing z-axis to buffer with color[0]
    for (int i = 0; i < 3*6; i = i + 3)
    {
        buffer.push_back(vertices_positions[i]);
        buffer.push_back(vertices_positions[i + 1]);
        buffer.push_back(vertices_positions[i + 2]);

        buffer.push_back(color[0][0]);
        buffer.push_back(color[0][1]);
        buffer.push_back(color[0][2]);
    }

    // add square facing y-axis with color[1]
    if (piece_type == PieceType::middle || piece_type == PieceType::corner)
    {
        for (int i = 3*6; i < 3*12; i = i + 3)
        {
            buffer.push_back(vertices_positions[i]);
            buffer.push_back(vertices_positions[i + 1]);
            buffer.push_back(vertices_positions[i + 2]);

            buffer.push_back(color[1][0]);
            buffer.push_back(color[1][1]);
            buffer.push_back(color[1][2]);
        }
    }

    // add square facing x-axis with color[2]
    if (piece_type == PieceType::corner)
    {
        for (int i = 3*12; i < 3*18; i = i + 3)
        {
            buffer.push_back(vertices_positions[i]);
            buffer.push_back(vertices_positions[i + 1]);
            buffer.push_back(vertices_positions[i + 2]);

            buffer.push_back(color[2][0]);
            buffer.push_back(color[2][1]);
            buffer.push_back(color[2][2]);
        }
    }

    return buffer;
}
