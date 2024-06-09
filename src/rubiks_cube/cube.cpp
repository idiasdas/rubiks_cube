#include "cube.h"

Cube::Cube(const float piece_size, const float gap_size, const float (&colors)[6][3])
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;
    m_position[0] = 0.0f;
    m_position[1] = 0.0f;
    m_position[2] = 0.0f;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            m_colors[i][j] = colors[i][j];

    float step = m_piece_size + m_gap_size;
    int piece_count = 0;
    float piece_colors[6][3];
    for (int y = 1; y >= -1; y--)
    {
        for (int z = 1; z >= -1; z--)
        {
            for (int x = -1; x <= 1; x++)
            {
                set_piece_colors(x, y, z, piece_colors);
                m_pieces.push_back(get_piece(piece_colors, glm::vec3({x * step + m_position[0], y * step + m_position[1], z * step + m_position[2]})));
                m_state[piece_count++] = piece_count;
            }
        }
    }
}

Cube::Cube(const float (&position)[3], const float piece_size, const float gap_size, const float (&colors)[6][3])
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;
    m_position[0] = position[0];
    m_position[1] = position[1];
    m_position[2] = position[2];

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            m_colors[i][j] = colors[i][j];

    float step = m_piece_size + m_gap_size;
    int piece_count = 0;
    float piece_colors[6][3];
    for (int y = 1; y >= -1; y--)
    {
        for (int z = 1; z >= -1; z--)
        {
            for (int x = -1; x <= 1; x++)
            {
                set_piece_colors(x, y, z, piece_colors);
                m_pieces.push_back(get_piece(piece_colors, glm::vec3({x * step + m_position[0], y * step + m_position[1], z * step + m_position[2]})));
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

    // color piece top face
    if (y == 1)
        for (int i = 0; i < 3; i++)
            colors[Face::top][i] = m_colors[Face::top][i];

    // color piece bottom face
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
    const float y = -piece_state_index / 9 + 1;
    const float z = -piece_state_index % 9 / 3 + 1;
    const float x =  piece_state_index % 9 % 3 - 1;
    return std::make_tuple(x, y, z);
}

void Cube::reset()
{
    float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++)
    {
        m_state[i] = i;
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].set_rotation_matrix(glm::mat4(1));

        auto[x, y, z] = get_piece_coordinates(i);
        m_pieces[i].translate({x * step + m_position[0], y * step + m_position[1], z * step + m_position[2]});
    }
}

void Cube::resize(const float piece_size, const float gap_size)
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;
    float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++)
    {
        const int piece_i = m_state[i];
        m_pieces[piece_i].set_translation_matrix(glm::mat4(1));
        m_pieces[piece_i].set_rotation_matrix(glm::mat4(1));
        m_pieces[piece_i].set_scale_matrix(glm::mat4(1));

        auto[x, y, z] = get_piece_coordinates(i);
        m_pieces[piece_i].scale({m_piece_size / 2.f, m_piece_size / 2.f, m_piece_size / 2.f});
        m_pieces[piece_i].translate({x * step + m_position[0], y * step + m_position[1], z * step + m_position[2]});
    }
}

Model Cube::get_piece(const float (&colors)[][3], const glm::vec3 position)
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
    for (int i = 0; i < buffer.size(); i++)
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

    const float step = m_piece_size + m_gap_size;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int piece_state_index = faces[face_index][i][j];
            auto[x, y, z] = get_piece_coordinates(piece_state_index);
            glm::vec3 piece_position = {x * step + m_position[0], y * step + m_position[1], z * step + m_position[2]};

            m_pieces[m_state[piece_state_index]].set_translation_matrix(glm::mat4(1));
            m_pieces[m_state[piece_state_index]].rotate(rotation_degrees, axis_sign * face_axis);
            m_pieces[m_state[piece_state_index]].translate(piece_position);
        }
    }
}

void Cube::read_controls(OpenGLContext *const openGL_context)
{
    float input_delay = 0.2f;
    static double last_time = glfwGetTime();
    double cur_time = glfwGetTime();
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_KP_5) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            rotate_face(Face::front, 3);
        else
            rotate_face(Face::front, 1);
    }
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_KP_6) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            rotate_face(Face::right, 3);
        else
            rotate_face(Face::right, 1);
    }
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_KP_4) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            rotate_face(Face::left, 3);
        else
            rotate_face(Face::left, 1);
    }
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_KP_0) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            rotate_face(Face::back, 3);
        else
            rotate_face(Face::back, 1);
    }
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_KP_8) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            rotate_face(Face::top, 3);
        else
            rotate_face(Face::top, 1);
    }
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_KP_2) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            rotate_face(Face::bottom, 3);
        else
            rotate_face(Face::bottom, 1);
    }
    if (glfwGetKey(openGL_context->get_window_handle(), GLFW_KEY_R) == GLFW_PRESS && cur_time - last_time > input_delay)
    {
        last_time = cur_time;
        reset();
    }
}
