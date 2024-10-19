#include "cube.h"

Cube::Cube(const float piece_size, const float gap_size, const float (&colors)[6][3], Camera& camera, OpenGLContext& openGLContext)
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;
    m_moves = std::queue<Move>();
    m_animation_speed = 5.f;
    m_camera = &camera;
    m_openGLContext = &openGLContext;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            m_colors[i][j] = colors[i][j];

    float step = m_piece_size + m_gap_size;
    float piece_colors[6][3];
    for (int z = -1; z <= 1; z++) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                PieceCoordinates piece_coordinates = { (float)x, (float)y, (float)z };
                set_piece_colors(piece_coordinates, piece_colors);
                m_pieces.push_back(get_piece(piece_colors, glm::vec3({ x * step, y * step, z * step })));
                m_pieces_relative_coordinates.push_back(piece_coordinates);
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
    switch (face_index) {
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

void Cube::cube_control(const int key, const int action)
{
    static bool clockwise = true;

    // R to reset cube to initial (solved) state
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        m_moves.push({ Face::none, 0 });
    }
    // Hold Left Shift to rotate face counterclockwise
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
        clockwise = false;
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        clockwise = true;
    else {
        int numpad_keys[] = { GLFW_KEY_KP_8, GLFW_KEY_KP_2, GLFW_KEY_KP_4, GLFW_KEY_KP_6, GLFW_KEY_KP_0, GLFW_KEY_KP_5 };
        int num_keys[] = { GLFW_KEY_8, GLFW_KEY_2, GLFW_KEY_4, GLFW_KEY_6, GLFW_KEY_0, GLFW_KEY_5 };
        Face faces[] = { Face::top, Face::bottom, Face::left, Face::right, Face::back, Face::front };

        for (int i = 0; i < 6; i++) {
            // Rotate face with number keys
            if ((key == numpad_keys[i] || key == num_keys[i]) && action == GLFW_PRESS) {
                if (clockwise)
                    m_moves.push({ faces[i], PI / 2.f });
                else
                    m_moves.push({ faces[i], -PI / 2.f });
                break;
            }
        }
    }
}

PieceCoordinates Cube::get_original_piece_relative_coordinates(const int piece_index) const
{
    PieceCoordinates piece_coordinates;
    piece_coordinates.x = (float)(piece_index % 3) - 1;
    piece_coordinates.y = (float)((piece_index / 3) % 3) - 1;
    piece_coordinates.z = (float)(piece_index / 9) - 1;
    return piece_coordinates;
}

Face Cube::ray_pick(glm::vec3 ray_origin, glm::vec3 ray_direction) const
{
    IntersectionType intersection_result;
    float dist = 10000.0f;
    float closest_dist = 10000.0f;

    int closest_piece_hit = -1;
    for (int i = 0; i < (int)m_pieces.size(); i++) {
        intersection_result = test_ray_cube_intersection(ray_origin, ray_direction, m_pieces[i].get_model_matrix(), &dist);
        if (intersection_result == IntersectionType::intersection && dist < closest_dist) {
            closest_piece_hit = i;
            closest_dist = dist;
        }
    }

    Face intersec_face = Face::none;
    std::string face_str = "none";

    if (closest_piece_hit == -1)
        return intersec_face;

    glm::vec3 intersec_point = ray_origin + closest_dist * ray_direction;

    float cube_size = m_gap_size + 1.5f * m_piece_size;

    if (std::abs(intersec_point.x - cube_size) < 100 * EPS) {
        intersec_face = Face::right;
        face_str = "right";
    } else if (std::abs(intersec_point.x + cube_size) < 100 * EPS) {
        intersec_face = Face::left;
        face_str = "left";
    } else if (std::abs(intersec_point.y - cube_size) < 100 * EPS) {
        intersec_face = Face::top;
        face_str = "top";
    } else if (std::abs(intersec_point.y + cube_size) < 100 * EPS) {
        intersec_face = Face::bottom;
        face_str = "bottom";
    } else if (std::abs(intersec_point.z - cube_size) < 100 * EPS) {
        intersec_face = Face::front;
        face_str = "front";
    } else if (std::abs(intersec_point.z + cube_size) < 100 * EPS) {
        intersec_face = Face::back;
        face_str = "back";
    }

    LOG_INFO("Intersection with piece {0}. Intersection point: ({1}, {2}, {3}). Intersection face: {4}",
        closest_piece_hit,
        intersec_point.x,
        intersec_point.y,
        intersec_point.z,
        face_str);

    return intersec_face;
}

void Cube::reset()
{
    float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++) {
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].set_rotation_matrix(glm::mat4(1));
        auto [x, y, z] = get_original_piece_relative_coordinates(i);
        m_pieces_relative_coordinates[i] = { x, y, z };
        m_pieces[i].translate({ x * step, y * step, z * step });
    }
}

void Cube::on_update()
{
    run_animation();
}

void Cube::round_pieces_world_positions()
{
    const float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++) {
        auto [x, y, z] = m_pieces_relative_coordinates[i];
        m_pieces_relative_coordinates[i] = { std::round(x), std::round(y), std::round(z) };
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].translate({ std::round(x) * step, std::round(y) * step, std::round(z) * step });
    }
}

void Cube::on_event(Event& event)
{
    static CubeState s_state = CubeState::wait_input;
    static Face s_selected_face = Face::none;
    static float s_mouse_xpos = 0.0f;
    static int s_mouse_ypos = 0.0f;
    static float s_cur_angle = 0.0f;
    static int s_move_dir = 1.f;

    if (event.get_event_type() == EventType::key_press) {
        cube_control(((KeyPressEvent*)&event)->get_key(), GLFW_PRESS);
    } else if (event.get_event_type() == EventType::key_release) {
        cube_control(((KeyReleaseEvent*)&event)->get_key(), GLFW_RELEASE);
    } else if (event.get_event_type() == EventType::ray && s_state == CubeState::wait_input && m_moves.empty()) {
        glm::vec3 origin = ((RayEvent*)&event)->get_origin();
        glm::vec3 direction = ((RayEvent*)&event)->get_direction();
        s_selected_face = ray_pick(origin, direction);
        if (s_selected_face != Face::none) {
            s_state = CubeState::rotate_face;
        }
    } else if (event.get_event_type() == EventType::mouse_button_press && s_state == CubeState::wait_input) {
        s_mouse_xpos = ((MouseButtonPressEvent*)&event)->get_xpos();
        s_mouse_ypos = ((MouseButtonPressEvent*)&event)->get_ypos();
        s_cur_angle = 0.0f;
    } else if (event.get_event_type() == EventType::mouse_button_release) {
        if (((MouseButtonReleaseEvent*)&event)->get_button() == GLFW_MOUSE_BUTTON_1) {
            if (s_state == CubeState::rotate_face) {
                float complete_angle = -s_cur_angle;
                if (s_cur_angle > PI / 7.f && s_cur_angle <= PI / 2.f)
                    complete_angle = PI / 2.f - s_cur_angle;
                if (s_cur_angle < -PI / 7.f && s_cur_angle > -PI / 2.f)
                    complete_angle = -PI / 2.f - s_cur_angle;
                m_moves.push({ s_selected_face, complete_angle });
                m_moves.push({ s_selected_face, 0.0f });
                s_cur_angle = 0.f;
                s_state = CubeState::wait_input;
            }
        }
    } else if (event.get_event_type() == EventType::mouse_move && s_state == CubeState::rotate_face) {
        glm::vec4 face_center_world_coords = get_face_center_world_coord(s_selected_face);

        float xpos = ((MouseMoveEvent*)&event)->get_x();
        float ypos = ((MouseMoveEvent*)&event)->get_y();

        glm::vec4 mouse_screen_coord((xpos / (float)m_openGLContext->get_window_width() - 0.5f) * 2.0f,
            -(ypos / (float)m_openGLContext->get_window_height() - 0.5f) * 2.0f,
            -1.f,
            1.0f);

        glm::vec4 previous_mouse_screen_coord((s_mouse_xpos / (float)m_openGLContext->get_window_width() - 0.5f) * 2.0f,
            -(s_mouse_ypos / (float)m_openGLContext->get_window_height() - 0.5f) * 2.0f,
            -1.f,
            1.0f);

        glm::vec4 face_center_screen_coord = m_camera->get_projection_matrix() * m_camera->get_view_matrix() * face_center_world_coords;
        face_center_screen_coord = face_center_screen_coord / face_center_screen_coord.w;
        glm::vec3 previous_vec = (previous_mouse_screen_coord - face_center_screen_coord);
        glm::vec3 cur_vec = (mouse_screen_coord - face_center_screen_coord);

        s_mouse_xpos = xpos;
        s_mouse_ypos = ypos;

        s_move_dir = (glm::cross(glm::normalize(previous_vec), glm::normalize(cur_vec)).z <= 0.0) ? 1 : -1;

        float move_sensitivity = std::min((float)m_openGLContext->get_window_width(), (float)m_openGLContext->get_window_width());
        move_sensitivity *= 4.f / 1280.f;
        float move_radians_clockwise = std::min(glm::distance(previous_vec, cur_vec) * move_sensitivity, .2f);

        s_cur_angle += move_radians_clockwise * s_move_dir;

        if (s_cur_angle >= PI / 2.f)
            s_cur_angle -= PI / 2.f;
        if (s_cur_angle <= -PI / 2.f)
            s_cur_angle += PI / 2.f;

        rotate_face(s_selected_face, move_radians_clockwise * s_move_dir);
    }
}

void Cube::resize(const float piece_size, const float gap_size)
{
    m_piece_size = piece_size;
    m_gap_size = gap_size;
    const float step = m_piece_size + m_gap_size;
    for (int i = 0; i < 27; i++) {
        m_pieces[i].set_translation_matrix(glm::mat4(1));
        m_pieces[i].set_scale_matrix(glm::mat4(1));
        auto [x, y, z] = m_pieces_relative_coordinates[i];
        m_pieces[i].scale({ m_piece_size / 2.f, m_piece_size / 2.f, m_piece_size / 2.f });
        m_pieces[i].translate({ x * step, y * step, z * step });
    }
}

Model Cube::get_piece(const float (&colors)[6][3], const glm::vec3 position)
{
    Model piece;

    const std::vector<float> buffer = {
        // square facing x axis
        VB,
        colors[0][0],
        colors[0][1],
        colors[0][2],
        VD,
        colors[0][0],
        colors[0][1],
        colors[0][2],
        VF,
        colors[0][0],
        colors[0][1],
        colors[0][2],
        VF,
        colors[0][0],
        colors[0][1],
        colors[0][2],
        VD,
        colors[0][0],
        colors[0][1],
        colors[0][2],
        VH,
        colors[0][0],
        colors[0][1],
        colors[0][2],
        // square facing y axis
        VA,
        colors[1][0],
        colors[1][1],
        colors[1][2],
        VB,
        colors[1][0],
        colors[1][1],
        colors[1][2],
        VE,
        colors[1][0],
        colors[1][1],
        colors[1][2],
        VE,
        colors[1][0],
        colors[1][1],
        colors[1][2],
        VB,
        colors[1][0],
        colors[1][1],
        colors[1][2],
        VF,
        colors[1][0],
        colors[1][1],
        colors[1][2],
        // square facing z axis
        VA,
        colors[2][0],
        colors[2][1],
        colors[2][2],
        VC,
        colors[2][0],
        colors[2][1],
        colors[2][2],
        VB,
        colors[2][0],
        colors[2][1],
        colors[2][2],
        VB,
        colors[2][0],
        colors[2][1],
        colors[2][2],
        VC,
        colors[2][0],
        colors[2][1],
        colors[2][2],
        VD,
        colors[2][0],
        colors[2][1],
        colors[2][2],
        // square facing - x axis
        VA,
        colors[3][0],
        colors[3][1],
        colors[3][2],
        VE,
        colors[3][0],
        colors[3][1],
        colors[3][2],
        VC,
        colors[3][0],
        colors[3][1],
        colors[3][2],
        VC,
        colors[3][0],
        colors[3][1],
        colors[3][2],
        VE,
        colors[3][0],
        colors[3][1],
        colors[3][2],
        VG,
        colors[3][0],
        colors[3][1],
        colors[3][2],
        // square facing - y axis
        VC,
        colors[4][0],
        colors[4][1],
        colors[4][2],
        VG,
        colors[4][0],
        colors[4][1],
        colors[4][2],
        VD,
        colors[4][0],
        colors[4][1],
        colors[4][2],
        VD,
        colors[4][0],
        colors[4][1],
        colors[4][2],
        VG,
        colors[4][0],
        colors[4][1],
        colors[4][2],
        VH,
        colors[4][0],
        colors[4][1],
        colors[4][2],
        // square facing - z axis
        VE,
        colors[5][0],
        colors[5][1],
        colors[5][2],
        VF,
        colors[5][0],
        colors[5][1],
        colors[5][2],
        VG,
        colors[5][0],
        colors[5][1],
        colors[5][2],
        VG,
        colors[5][0],
        colors[5][1],
        colors[5][2],
        VF,
        colors[5][0],
        colors[5][1],
        colors[5][2],
        VH,
        colors[5][0],
        colors[5][1],
        colors[5][2],
    };

    std::vector<uint32_t> indices;
    for (size_t i = 0; i < buffer.size() / 6; i++)
        indices.push_back(i);

    piece.buffer_vertices(buffer);
    piece.buffer_indices(indices);
    piece.scale({ m_piece_size / 2.f, m_piece_size / 2.f, m_piece_size / 2.f });
    piece.translate(position);

    return piece;
}

void Cube::draw(const Shader& shader) const
{
    for (Model piece : m_pieces)
        piece.draw(shader, m_camera->get_projection_matrix() * m_camera->get_view_matrix() * piece.get_model_matrix());
}

void Cube::rotate_face(const Face face_index, const float rotation_degrees)
{
    const float correct_rotation_degrees = -rotation_degrees;
    const glm::vec3 axis[6] = { X_AXIS, Y_AXIS, Z_AXIS, X_AXIS, Y_AXIS, Z_AXIS };
    const glm::vec3 face_axis = axis[face_index];
    // if the face is left, bottom or back, the rotation is counter-clockwise along the standard axis
    const float axis_sign = (face_index > 2) ? -1 : 1;
    const float step = m_piece_size + m_gap_size;

    for (int i = 0; i < 27; i++) {
        if (is_piece_on_face(m_pieces_relative_coordinates[i], face_index)) {
            // send piece to the origin
            m_pieces[i].set_translation_matrix(glm::mat4(1));
            // rotate piece
            m_pieces[i].rotate(correct_rotation_degrees, face_axis * axis_sign);

            // update piece coordinates
            glm::vec4 new_coordinates = { m_pieces_relative_coordinates[i].x, m_pieces_relative_coordinates[i].y, m_pieces_relative_coordinates[i].z, 1 };
            new_coordinates = glm::rotate(glm::mat4(1), correct_rotation_degrees, face_axis * axis_sign) * new_coordinates;
            m_pieces_relative_coordinates[i] = { new_coordinates.x, new_coordinates.y, new_coordinates.z };

            // round piece coordinates on the face axis so that we can elimitate floating point errors and correctly identify the pieces on the face
            switch (face_index) {
            case Face::right:
                m_pieces_relative_coordinates[i].x = 1.f;
                break;
            case Face::left:
                m_pieces_relative_coordinates[i].x = -1.f;
                break;
            case Face::top:
                m_pieces_relative_coordinates[i].y = 1.f;
                break;
            case Face::bottom:
                m_pieces_relative_coordinates[i].y = -1.f;
                break;
            case Face::front:
                m_pieces_relative_coordinates[i].z = 1.f;
                break;
            case Face::back:
                m_pieces_relative_coordinates[i].z = -1.f;
                break;

            default:
                break;
            }

            m_pieces[i].translate({ m_pieces_relative_coordinates[i].x * step, m_pieces_relative_coordinates[i].y * step, m_pieces_relative_coordinates[i].z * step });
        }
    }
}

void Cube::run_animation()
{
    static CubeState s_state = CubeState::wait_input;

    if (m_moves.empty())
        return;

    static double s_last_time = glfwGetTime();
    static double s_total_angle = 0.0f;
    static double s_final_angle = 0.0f;
    static int direction = 0;

    if (m_moves.front().face == Face::none) {
        reset();
        m_moves.pop();
        return;
    }

    if (m_moves.front().radians_clockwise == 0.0f) {
        round_pieces_world_positions();
        s_total_angle = 0.0f;
        m_moves.pop();
        s_state = CubeState::wait_input;
        return;
    }

    if (s_state == CubeState::wait_input) {
        s_state = CubeState::rotate_face;
        s_last_time = glfwGetTime();
        s_final_angle = std::abs(m_moves.front().radians_clockwise);
        direction = (m_moves.front().radians_clockwise >= 0) ? 1 : -1;
    }

    const double cur_time = glfwGetTime();
    const double delta_time = cur_time - s_last_time;

    if (delta_time < 1.f / 60.f)
        return;

    const double cur_angle = std::min(s_final_angle * delta_time * m_animation_speed * m_moves.size(), s_final_angle - s_total_angle);
    s_total_angle += cur_angle;
    rotate_face(m_moves.front().face, cur_angle * (float)direction);

    if (s_total_angle >= s_final_angle) {
        round_pieces_world_positions();
        s_total_angle = 0.0f;
        m_moves.pop();
        s_state = CubeState::wait_input;
    }

    s_last_time = cur_time;
}

glm::vec4 Cube::get_face_center_world_coord(const Face face)
{
    int piece_index = -1;
    switch (face) {
    case Face::front:
        piece_index = 22;
        break;
    case Face::right:
        piece_index = 14;
        break;
    case Face::top:
        piece_index = 16;
        break;
    case Face::back:
        piece_index = 4;
        break;
    case Face::left:
        piece_index = 12;
        break;
    case Face::bottom:
        piece_index = 10;
        break;
    default:
        piece_index = -1;
    }

    if (piece_index == -1)
        return glm::vec4(0);

    float step = m_piece_size + m_gap_size;
    return m_pieces[piece_index].get_model_matrix() * glm::vec4(m_pieces_relative_coordinates[piece_index].x * step, m_pieces_relative_coordinates[piece_index].y * step, m_pieces_relative_coordinates[piece_index].z * step, 1.0f);
}
