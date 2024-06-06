#include "builder.h"

/*
    colors = {z_axis_face, y_axis_face, x_axis_face, - z_axis_face, - y_axis_face, - x_axis_face}
*/
Model get_piece(const float (& colors)[][3], glm::vec3 position)
{
    Model piece;

    std::vector<float> buffer = {
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
