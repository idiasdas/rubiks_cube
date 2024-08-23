#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class Model
{
public:
    Model();

    void buffer_vertices(const std::vector<float> buffer);
    void update_buffer_vertices(const std::vector<float> buffer);
    void buffer_indices(const std::vector<uint32_t> buffer);
    void draw(const Shader &shader, const glm::mat4 MVP) const;
    void draw_lines(const Shader &shader, const glm::mat4 MVP) const;
    void scale(const glm::vec3 &scale_vector);
    void rotate(const float rotation_degree, const glm::vec3 &rotation_axis);
    void translate(const glm::vec3 &translation_vector);
    void set_scale_matrix(const glm::mat4 &scale_matrix) { m_scale_matrix = scale_matrix; }
    void set_rotation_matrix(const glm::mat4 &rotation_matrix) { m_rotation_matrix = rotation_matrix; }
    void set_translation_matrix(const glm::mat4 &translation_matrix) { m_translation_matrix = translation_matrix; }

    glm::mat4 get_scale_matrix() const { return m_scale_matrix; }
    glm::mat4 get_rotation_matrix() const { return m_rotation_matrix; }
    glm::mat4 get_translation_matrix() const { return m_translation_matrix; }
    glm::mat4 get_model_matrix() const { return m_translation_matrix * m_rotation_matrix * m_scale_matrix; }

private:
    uint32_t m_vertex_array_ID;
    uint32_t m_vertex_buffer_ID;
    uint32_t m_index_buffer_ID;

    uint32_t m_indices_count;

    glm::mat4 m_scale_matrix;
    glm::mat4 m_rotation_matrix;
    glm::mat4 m_translation_matrix;
};
